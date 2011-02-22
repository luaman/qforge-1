/*
	qfcc.h

	QuakeForge Code Compiler (main program)

	Copyright (C) 1996-1997 id Software, Inc.
	Copyright (C) 2001 Jeff Teunissen <deek@quakeforge.net>
	Copyright (C) 2001 Bill Currie <bill@taniwha.org>

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

	$Id$
*/

#ifndef __qfcc_h
#define __qfcc_h

/** \defgroup qfcc QuakeC compiler
*/

#include <stdio.h>
#include "QF/pr_comp.h"

/** \defgroup qfcc_general General functions
	\ingroup qfcc
*/
//@{

typedef struct srcline_s srcline_t;
struct srcline_s {
	srcline_t  *next;
	string_t    source_file;
	int         source_line;
};

/**	Output generated by prog parsing.
*/
typedef struct pr_info_s {
	struct type_s	*types;

	struct function_s *func_head;
	struct function_s **func_tail;
	dfunction_t		*functions;
	int				num_functions;

	struct strpool_s *strings;			///< progs string data
	struct codespace_s *code;			///< progs code data
	struct defspace_s *data;			///< combined near and far data
	struct defspace_s *near_data;		///< data directly addressable by
										///< statments (address < 64k)
	struct defspace_s *far_data;		///< data that might not be directly
										///< addressabe by statements (address
										///< possibly > 64k)
	struct defspace_s *entity_data;		///< entity field address space. no
										///< data is stored in the progs file
	struct defspace_s *type_data;		///< encoded type information.

	struct symtab_s *symtab;

	srcline_t      *srcline_stack;
	string_t        source_file;
	int             source_line;
	int             error_count;

	struct reloc_s *relocs;

	struct pr_auxfunction_s *auxfunctions;
	int             auxfunctions_size;
	int             num_auxfunctions;

	struct pr_lineno_s *linenos;
	int             linenos_size;
	int             num_linenos;

	ddef_t         *locals;
	int             locals_size;
	int             num_locals;
} pr_info_t;

extern	pr_info_t	pr;


extern	char		destfile[];

extern	struct symtab_s *current_symtab;

#define GETSTR(s)			(pr.strings->strings + (s))
#define D_var(t, d)			((d)->space->data[(d)->offset].t##_var)
#define	D_FLOAT(d)			D_var (float, d)
#define	D_INT(d)			D_var (integer, d)
#define	D_VECTOR(d)			D_var (vector, d)
#define	D_STRING(d)			GETSTR (D_var (string, d))
#define	D_FUNCTION(d)		D_var (func, d)
#define D_POINTER(t,d)		((t *)((d)->space->data + (d)->offset))
#define D_STRUCT(t,d)		(*D_POINTER (t, d))

#define G_POINTER(s,t,o)	((t *)((s)->data + o))
#define G_STRUCT(s,t,o)		(*G_POINTER (s, t, o))

#define POINTER_OFS(s,p)	((pr_type_t *) (p) - (s)->data)

const char *strip_path (const char *filename);

void clear_frame_macros (void);
extern FILE *yyin;
int yyparse (void);
extern int yydebug;

#ifdef _WIN32
char *fix_backslash (char *path);
#define NORMALIZE(x) fix_backslash (x)
#else
#define NORMALIZE(x) x
#endif

/**	High-tide structure allocator for use in linked lists.

	Using a free-list with the name of \c free_NAME, return a single element.
	The type of the element must be a structure with a field named \c next.
	When the free-list is empty, memory is claimed from the system in blocks.
	elements may be returned to the pool by linking them into the free-list.

	\param s		The number of structures in the block.
	\param t		The structure type.
	\param n		The \c NAME portion of the \c free_NAME free-list.
	\param v		The destination of the pointer to the allocated
					element. The contents of the allocated element will be
					memset to 0.

	\hideinitializer
*/
#define ALLOC(s, t, n, v)							\
	do {											\
		if (!free_##n) {							\
			int         i;							\
			free_##n = malloc ((s) * sizeof (t));	\
			for (i = 0; i < (s) - 1; i++)			\
				free_##n[i].next = &free_##n[i + 1];\
			free_##n[i].next = 0;					\
		}											\
		v = free_##n;								\
		free_##n = free_##n->next;					\
		memset (v, 0, sizeof (*v));					\
	} while (0)

/**	Round \a x up to the next multiple of \a a.
	\note \a a must be a power of two or this will break.
	\note There are no side effects on \a x.
	\param x		The value to be rounded up.
	\param a		The rounding factor.
	\return			The rounded value.
*/
#define RUP(x,a) (((x) + ((a) - 1)) & ~((a) - 1))

//@}

#endif//__qfcc_h
