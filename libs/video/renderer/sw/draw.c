/*
	draw.c

	this is the only file outside the refresh that touches the vid buffer

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

#include "QF/console.h"
#include "QF/cvar.h"
#include "QF/draw.h"
#include "QF/sound.h"
#include "QF/sys.h"
#include "QF/vfs.h"

#include "d_iface.h"
#include "r_cvar.h"

typedef struct {
	vrect_t     rect;
	int         width;
	int         height;
	byte       *ptexbytes;
	int         rowbytes;
} rectdesc_t;

static rectdesc_t r_rectdesc;

byte       *draw_chars;					// 8*8 graphic characters
qpic_t     *draw_disc;
qpic_t     *draw_backtile;


/* Support Routines */

typedef struct cachepic_s {
	char        name[MAX_QPATH];
	cache_user_t cache;
} cachepic_t;

#define	MAX_CACHED_PICS		128
cachepic_t  cachepics[MAX_CACHED_PICS];
int         numcachepics;


qpic_t *
Draw_PicFromWad (const char *name)
{
	return W_GetLumpName (name);
}


void
Draw_ClearCache (void)
{
}


qpic_t *
Draw_CachePic (const char *path, qboolean alpha)
{
	cachepic_t *pic;
	int         i;
	qpic_t     *dat;

	for (pic = cachepics, i = 0; i < numcachepics; pic++, i++)
		if (!strcmp (path, pic->name))
			break;

	if (i == numcachepics) {
		if (numcachepics == MAX_CACHED_PICS)
			Sys_Error ("numcachepics == MAX_CACHED_PICS");
		numcachepics++;
		strcpy (pic->name, path);
	}

	dat = Cache_Check (&pic->cache);

	if (dat)
		return dat;

	// load the pic from disk
	COM_LoadCacheFile (path, &pic->cache);

	dat = (qpic_t *) pic->cache.data;
	if (!dat) {
		Sys_Error ("Draw_CachePic: failed to load %s", path);
	}

	SwapPic (dat);

	return dat;
}


void
Draw_TextBox (int x, int y, int width, int lines, byte alpha)
{
	qpic_t     *p;
	int         cx, cy;
	int         n;

	// draw left side
	cx = x;
	cy = y;
	p = Draw_CachePic ("gfx/box_tl.lmp", true);
	Draw_Pic (cx, cy, p);
	p = Draw_CachePic ("gfx/box_ml.lmp", true);
	for (n = 0; n < lines; n++) {
		cy += 8;
		Draw_Pic (cx, cy, p);
	}
	p = Draw_CachePic ("gfx/box_bl.lmp", true);
	Draw_Pic (cx, cy + 8, p);

	// draw middle
	cx += 8;
	while (width > 0) {
		cy = y;
		p = Draw_CachePic ("gfx/box_tm.lmp", true);
		Draw_Pic (cx, cy, p);
		p = Draw_CachePic ("gfx/box_mm.lmp", true);
		for (n = 0; n < lines; n++) {
			cy += 8;
			if (n == 1)
				p = Draw_CachePic ("gfx/box_mm2.lmp", true);
			Draw_Pic (cx, cy, p);
		}
		p = Draw_CachePic ("gfx/box_bm.lmp", true);
		Draw_Pic (cx, cy + 8, p);
		width -= 2;
		cx += 16;
	}

	// draw right side
	cy = y;
	p = Draw_CachePic ("gfx/box_tr.lmp", true);
	Draw_Pic (cx, cy, p);
	p = Draw_CachePic ("gfx/box_mr.lmp", true);
	for (n = 0; n < lines; n++) {
		cy += 8;
		Draw_Pic (cx, cy, p);
	}
	p = Draw_CachePic ("gfx/box_br.lmp", true);
	Draw_Pic (cx, cy + 8, p);
}


void
Draw_Init (void)
{
	draw_chars = W_GetLumpName ("conchars");
	draw_disc = W_GetLumpName ("disc");
	draw_backtile = W_GetLumpName ("backtile");

	r_rectdesc.width = draw_backtile->width;
	r_rectdesc.height = draw_backtile->height;
	r_rectdesc.ptexbytes = draw_backtile->data;
	r_rectdesc.rowbytes = draw_backtile->width;
}


/*
	Draw_Character

	Draws one 8*8 graphics character with 0 being transparent.
	It can be clipped to the top of the screen to allow the console to be
	smoothly scrolled off.
*/
inline void
Draw_Character (int x, int y, unsigned int num)
{
	byte       *dest;
	byte       *source;
	int         drawline;
	int         row, col;

	num &= 255;

	if (y <= -8)
		return;							// totally off screen

	if (y > vid.height - 8 || x < 0 || x > vid.width - 8)
		return;
	if (num < 0 || num > 255)
		return;

	row = num >> 4;
	col = num & 15;
	source = draw_chars + (row << 10) + (col << 3);

	if (y < 0) {						// clipped
		drawline = 8 + y;
		source -= 128 * y;
		y = 0;
	} else
		drawline = 8;

	dest = vid.conbuffer + y * vid.conrowbytes + x;

	while (drawline--) {
		if (source[0])
			dest[0] = source[0];
		if (source[1])
			dest[1] = source[1];
		if (source[2])
			dest[2] = source[2];
		if (source[3])
			dest[3] = source[3];
		if (source[4])
			dest[4] = source[4];
		if (source[5])
			dest[5] = source[5];
		if (source[6])
			dest[6] = source[6];
		if (source[7])
			dest[7] = source[7];
		source += 128;
		dest += vid.conrowbytes;
	}
}


void
Draw_String (int x, int y, const char *str)
{
	while (*str) {
		Draw_Character (x, y, *str++);
		x += 8;
	}
}


void
Draw_nString (int x, int y, const char *str, int count)
{
	while (count-- && *str) {
		Draw_Character (x, y, *str++);
		x += 8;
	}
}


void
Draw_AltString (int x, int y, const char *str)
{
	while (*str) {
		Draw_Character (x, y, (*str++) | 0x80);
		x += 8;
	}
}


void
Draw_Pixel (int x, int y, byte color)
{
	byte       *dest;

	dest = vid.conbuffer + y * vid.conrowbytes + x;
	*dest = color;
}


void
Draw_Crosshair (void)
{
	int         x, y;
	byte        c = crosshaircolor->int_val;

	if (crosshair->int_val == 2) {
		x = scr_vrect.x + scr_vrect.width / 2 + cl_crossx->int_val;
		y = scr_vrect.y + scr_vrect.height / 2 + cl_crossy->int_val;
		Draw_Pixel (x - 1, y, c);
		Draw_Pixel (x - 3, y, c);
		Draw_Pixel (x + 1, y, c);
		Draw_Pixel (x + 3, y, c);
		Draw_Pixel (x, y - 1, c);
		Draw_Pixel (x, y - 3, c);
		Draw_Pixel (x, y + 1, c);
		Draw_Pixel (x, y + 3, c);
	} else if (crosshair->int_val)
		Draw_Character (scr_vrect.x + scr_vrect.width / 2 - 4 +
						cl_crossx->int_val,
						scr_vrect.y + scr_vrect.height / 2 - 4 +
						cl_crossy->int_val, '+');
}


void
Draw_Pic (int x, int y, qpic_t *pic)
{
	byte       *dest, *source, tbyte;
	int         v, u;

	if (x < 0 || (unsigned int) (x + pic->width) > vid.width || y < 0 ||
		(unsigned int) (y + pic->height) > vid.height) {
		Sys_Error ("Draw_Pic: bad coordinates");
	}

	source = pic->data;

	dest = vid.buffer + y * vid.rowbytes + x;

	if (pic->width & 7) {			// general
		for (v = 0; v < pic->height; v++) {
			for (u = 0; u < pic->width; u++)
				if ((tbyte = source[u]) != TRANSPARENT_COLOR)
					dest[u] = tbyte;

			dest += vid.rowbytes;
			source += pic->width;
		}
	} else {						// unwound
		for (v = 0; v < pic->height; v++) {
			for (u = 0; u < pic->width; u += 8) {
				if ((tbyte = source[u]) != TRANSPARENT_COLOR)
					dest[u] = tbyte;
				if ((tbyte = source[u + 1]) != TRANSPARENT_COLOR)
					dest[u + 1] = tbyte;
				if ((tbyte = source[u + 2]) != TRANSPARENT_COLOR)
					dest[u + 2] = tbyte;
				if ((tbyte = source[u + 3]) != TRANSPARENT_COLOR)
					dest[u + 3] = tbyte;
				if ((tbyte = source[u + 4]) != TRANSPARENT_COLOR)
					dest[u + 4] = tbyte;
				if ((tbyte = source[u + 5]) != TRANSPARENT_COLOR)
					dest[u + 5] = tbyte;
				if ((tbyte = source[u + 6]) != TRANSPARENT_COLOR)
					dest[u + 6] = tbyte;
				if ((tbyte = source[u + 7]) != TRANSPARENT_COLOR)
					dest[u + 7] = tbyte;
			}
			dest += vid.rowbytes;
			source += pic->width;
		}
	}
}


void
Draw_SubPic (int x, int y, qpic_t *pic, int srcx, int srcy, int width,
			 int height)
{
	byte       *dest, *source;
	int         v;

	if ((x < 0) ||
		(x + width > vid.width) || (y < 0) || (y + height > vid.height)) {
		Sys_Error ("Draw_SubPic: bad coordinates");
	}

	source = pic->data + srcy * pic->width + srcx;

	dest = vid.buffer + y * vid.rowbytes + x;

	for (v = 0; v < height; v++) {
		memcpy (dest, source, width);
		dest += vid.rowbytes;
		source += pic->width;
	}
}


void
Draw_TransPicTranslate (int x, int y, qpic_t *pic, byte * translation)
{
	byte       *dest, *source, tbyte;
	int         v, u;

	if (x < 0 || (unsigned int) (x + pic->width) > vid.width || y < 0 ||
		(unsigned int) (y + pic->height) > vid.height) {
		Sys_Error ("Draw_TransPic: bad coordinates");
	}

	source = pic->data;

	dest = vid.buffer + y * vid.rowbytes + x;

	if (pic->width & 7) {			// general
		for (v = 0; v < pic->height; v++) {
			for (u = 0; u < pic->width; u++)
				if ((tbyte = source[u]) != TRANSPARENT_COLOR)
					dest[u] = translation[tbyte];

			dest += vid.rowbytes;
			source += pic->width;
		}
	} else {						// unwound
		for (v = 0; v < pic->height; v++) {
			for (u = 0; u < pic->width; u += 8) {
				if ((tbyte = source[u]) != TRANSPARENT_COLOR)
					dest[u] = translation[tbyte];
				if ((tbyte = source[u + 1]) != TRANSPARENT_COLOR)
					dest[u + 1] = translation[tbyte];
				if ((tbyte = source[u + 2]) != TRANSPARENT_COLOR)
					dest[u + 2] = translation[tbyte];
				if ((tbyte = source[u + 3]) != TRANSPARENT_COLOR)
					dest[u + 3] = translation[tbyte];
				if ((tbyte = source[u + 4]) != TRANSPARENT_COLOR)
					dest[u + 4] = translation[tbyte];
				if ((tbyte = source[u + 5]) != TRANSPARENT_COLOR)
					dest[u + 5] = translation[tbyte];
				if ((tbyte = source[u + 6]) != TRANSPARENT_COLOR)
					dest[u + 6] = translation[tbyte];
				if ((tbyte = source[u + 7]) != TRANSPARENT_COLOR)
					dest[u + 7] = translation[tbyte];
			}
			dest += vid.rowbytes;
			source += pic->width;
		}
	}
}


void
Draw_ConsoleBackground (int lines)
{
	int         x, y, v;
	byte       *src, *dest;
	int         f, fstep;
	qpic_t     *conback;

	conback = Draw_CachePic ("gfx/conback.lmp", false);

	// draw the pic
	dest = vid.conbuffer;

	for (y = 0; y < lines; y++, dest += vid.conrowbytes) {
		v = (vid.conheight - lines + y) * 200 / vid.conheight;
		src = conback->data + v * 320;
		if (vid.conwidth == 320)
			memcpy (dest, src, vid.conwidth);
		else {
			f = 0;
			fstep = 320 * 0x10000 / vid.conwidth;
			for (x = 0; x < vid.conwidth; x += 4) {
				dest[x] = src[f >> 16];
				f += fstep;
				dest[x + 1] = src[f >> 16];
				f += fstep;
				dest[x + 2] = src[f >> 16];
				f += fstep;
				dest[x + 3] = src[f >> 16];
				f += fstep;
			}
		}
	}

	Draw_AltString (vid.conwidth - strlen (cl_verstring->string) * 8 - 11,
					lines - 14, cl_verstring->string);
}

void
R_DrawRect (vrect_t *prect, int rowbytes, byte * psrc, int transparent)
{
	byte        t;
	int         i, j, srcdelta, destdelta;
	byte       *pdest;

	pdest = vid.buffer + (prect->y * vid.rowbytes) + prect->x;

	srcdelta = rowbytes - prect->width;
	destdelta = vid.rowbytes - prect->width;

	if (transparent) {
		for (i = 0; i < prect->height; i++) {
			for (j = 0; j < prect->width; j++) {
				t = *psrc;
				if (t != TRANSPARENT_COLOR) {
					*pdest = t;
				}

				psrc++;
				pdest++;
			}

			psrc += srcdelta;
			pdest += destdelta;
		}
	} else {
		for (i = 0; i < prect->height; i++) {
			memcpy (pdest, psrc, prect->width);
			psrc += rowbytes;
			pdest += vid.rowbytes;
		}
	}
}


/*
	Draw_TileClear

	This repeats a 64*64 tile graphic to fill the screen around a sized down
	refresh window.
*/
void
Draw_TileClear (int x, int y, int w, int h)
{
	int         width, height, tileoffsetx, tileoffsety;
	byte       *psrc;
	vrect_t     vr;

	r_rectdesc.rect.x = x;
	r_rectdesc.rect.y = y;
	r_rectdesc.rect.width = w;
	r_rectdesc.rect.height = h;

	vr.y = r_rectdesc.rect.y;
	height = r_rectdesc.rect.height;

	tileoffsety = vr.y % r_rectdesc.height;

	while (height > 0) {
		vr.x = r_rectdesc.rect.x;
		width = r_rectdesc.rect.width;

		if (tileoffsety != 0)
			vr.height = r_rectdesc.height - tileoffsety;
		else
			vr.height = r_rectdesc.height;

		if (vr.height > height)
			vr.height = height;

		tileoffsetx = vr.x % r_rectdesc.width;

		while (width > 0) {
			if (tileoffsetx != 0)
				vr.width = r_rectdesc.width - tileoffsetx;
			else
				vr.width = r_rectdesc.width;

			if (vr.width > width)
				vr.width = width;

			psrc = r_rectdesc.ptexbytes +
				(tileoffsety * r_rectdesc.rowbytes) + tileoffsetx;

			R_DrawRect (&vr, r_rectdesc.rowbytes, psrc, 0);

			vr.x += vr.width;
			width -= vr.width;
			tileoffsetx = 0;	// only the left tile can be left-clipped
		}

		vr.y += vr.height;
		height -= vr.height;
		tileoffsety = 0;		// only the top tile can be top-clipped
	}
}


/*
	Draw_Fill

	Fills a box of pixels with a single color
*/
void
Draw_Fill (int x, int y, int w, int h, int c)
{
	byte       *dest;
	int         u, v;

	if (x < 0 || x + w > vid.width || y < 0 || y + h > vid.height) {
		Con_Printf ("Bad Draw_Fill(%d, %d, %d, %d, %c)\n", x, y, w, h, c);
		return;
	}

	dest = vid.buffer + y * vid.rowbytes + x;
	for (v = 0; v < h; v++, dest += vid.rowbytes)
		for (u = 0; u < w; u++)
			dest[u] = c;
}


void
Draw_FadeScreen (void)
{
	int         x, y;
	byte       *pbuf;

	VID_UnlockBuffer ();
	S_ExtraUpdate ();
	VID_LockBuffer ();

	for (y = 0; y < vid.height; y++) {
		int         t;

		pbuf = (byte *) (vid.buffer + vid.rowbytes * y);
		t = (y & 1) << 1;

		for (x = 0; x < vid.width; x++) {
			if ((x & 3) != t)
				pbuf[x] = 0;
		}
	}

	VID_UnlockBuffer ();
	S_ExtraUpdate ();
	VID_LockBuffer ();
}


/*
	Draw_BeginDisc

	Draws the little blue disc in the corner of the screen.
	Call before beginning any disc IO.
*/
void
Draw_BeginDisc (void)
{
	D_BeginDirectRect (vid.width - 24, 0, draw_disc->data, 24, 24);
}


/*
	Draw_EndDisc

	Erases the disc icon.
	Call after completing any disc IO
*/
void
Draw_EndDisc (void)
{
	D_EndDirectRect (vid.width - 24, 0, 24, 24);
}
