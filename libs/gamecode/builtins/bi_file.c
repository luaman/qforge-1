/*
	bi_file.c

	CSQC file builtins

	Copyright (C) 1996-1997  Id Software, Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
static const char rcsid[] = 
	"$Id$";

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#ifdef HAVE_FNMATCH_H
# define model_t sunmodel_t
# include <fnmatch.h>
# undef model_t
#else
# ifdef WIN32
# include "fnmatch.h"
# endif
#endif

#ifndef HAVE_FNMATCH_PROTO
int         fnmatch (const char *__pattern, const char *__string, int __flags);
#endif

#include "QF/progs.h"
#include "QF/va.h"
#include "QF/vfs.h"
#include "QF/zone.h"

#define MAX_HANDLES 20
static VFile *handles[MAX_HANDLES];

static const char *file_ban_list[] = {
	"default.cfg{,.gz}",
	"demo1.dem{,.gz}",
	"demo2.dem{,.gz}",
	"demo3.dem{,.gz}",
	"end1.bin{,.gz}",
	"end2.bin{,.gz}",
	"gfx.wad{,.gz}",
	"progs.dat{,.gz}",
	"quake.rc{,.gz}",
	0,
};

static const char *dir_ban_list[] = {
	"gfx",
	"maps",
	"progs",
	"skins",
	"sound",
	0,
};

static int
file_readable (char *path)
{
	char        t;
	char       *p = strchr (path, '/');
	const char **match;

	if (p) {
		t = *p;
		*p = 0;
		for (match = dir_ban_list; *match; match++) {
			if (fnmatch (*match, path, FNM_PATHNAME) == 0) {
				*p = t;
				return 0;
			}
		}
	} else {
		for (match = file_ban_list; *match; match++) {
			if (fnmatch (*match, path, FNM_PATHNAME) == 0) {
				return 0;
			}
		}
	}
	return 1;
}

static int
file_writeable (char *path)
{
	return file_readable (path);
}

static void
bi_File_Open (progs_t *pr)
{
	const char *pth = G_STRING (pr, OFS_PARM0);
	const char *mode = G_STRING (pr, OFS_PARM1);
	char       *path= Hunk_TempAlloc (strlen (pth) + 1);
	char       *p, *d;
	int         h;
	int         do_write = 0;
	int         do_read = 0;

	p = strchr (mode, 'r');
	if (p) {
		do_read |= 1;
		if (p[1] == '+')
			do_write |= 1;
	}

	p = strchr (mode, 'w');
	if (p) {
		do_write |= 1;
		if (p[1] == '+')
			do_read |= 1;
	}

	p = strchr (mode, 'a');
	if (p) {
		do_write |= 1;
		if (p[1] == '+')
			do_read |= 1;
	}

	for (d = path; *pth; d++, pth++) {
		if (*pth == '\\')
			*d = '/';
		else
			*d = *pth;
	}
	*d = 0;

	p = path;
	while (*p) {
		if (p[0] == '.') {
			if (p[1] == '.') {
				if (p[2] == '/' || p[2] == 0) {
					d = p;
					if (d > path)
						d--;
					while (d > path && d[-1] != '/')
						d--;
					if (d == path
						&& d[0] == '.' && d[1] == '.'
						&& (d[2] == '/' || d[2] == '0')) {
						p += 2 + (p[2] == '/');
						continue;
					}
					strcpy (d, p + 2 + (p[2] == '/'));
					p = d + (d != path);
				}
			} else if (p[1] == '/') {
				strcpy (p, p + 2);
				continue;
			} else if (p[1] == 0) {
				p[0] = 0;
			}
		}
		while (*p && *p != '/')
			p++;
		if (*p == '/')
			p++;
	}
	//printf ("'%s'  '%s'\n", G_STRING (pr, OFS_PARM0), path);
	if (!path[0])
		goto error;
	if (path[0] == '.' && path[1] == '.' && (path[2] == '/' || path [2] == 0))
		goto error;
	if (path[strlen (path) - 1] =='/')
		goto error;
	if (!do_read && !do_write)
		goto error;
	if (do_read && !file_readable (path))
		goto error;
	if (do_write && !file_writeable (path))
		goto error;
	for (h = 0; h < MAX_HANDLES && handles[h]; h++)
		;
	if (h == MAX_HANDLES)
		goto error;
	if (!(handles[h] = Qopen (va ("%s/%s", com_gamedir, path), mode)))
		goto error;
	G_INT (pr, OFS_RETURN) = h + 1;
	return;
error:
	G_INT (pr, OFS_RETURN) = 0;
}

static void
bi_File_Close (progs_t *pr)
{
	int         h = G_INT (pr, OFS_PARM0) - 1;

	if (h < 0 || h >= MAX_HANDLES || !handles[h])
		return;
	Qclose (handles[h]);
	handles[h] = 0;
}

static void
bi_File_GetLine (progs_t *pr)
{
	int         h = G_INT (pr, OFS_PARM0) - 1;
	const char *s;

	if (h < 0 || h >= MAX_HANDLES || !handles[h]) {
		G_INT (pr, OFS_RETURN) = 0;
		return;
	}
	s = Qgetline (handles[h]);
	RETURN_STRING (pr, s);
}

void
File_Progs_Init (progs_t *pr)
{
	PR_AddBuiltin (pr, "File_Open", bi_File_Open, -1);
	PR_AddBuiltin (pr, "File_Close", bi_File_Close, -1);
	PR_AddBuiltin (pr, "File_GetLine", bi_File_GetLine, -1);
}
