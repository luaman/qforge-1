/*
	d_init.c

	rasterization driver initialization

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

	$Id$
*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "QF/cvar.h"
#include "QF/render.h"
#include "QF/vid.h"

#include "compat.h"
#include "d_local.h"
#include "r_cvar.h"

#define NUM_MIPS	4

surfcache_t *d_initial_rover;
qboolean     d_roverwrapped;
int          d_minmip;
float        d_scalemip[NUM_MIPS - 1];

static float basemip[NUM_MIPS - 1] = { 1.0, 0.5 * 0.8, 0.25 * 0.8 };

extern int   d_aflatcolor;

void        (*d_drawspans) (espan_t *pspan);


void
D_Init (void)
{
	r_skydirect = 1;

	r_drawpolys = false;
	r_worldpolysbacktofront = false;
	r_recursiveaffinetriangles = true;
	r_pixbytes = 1;
	r_aliasuvscale = 1.0;

	vid.surf_cache_size = D_SurfaceCacheForRes;
	vid.flush_caches = D_FlushCaches;
	vid.init_caches = D_InitCaches;

	VID_InitBuffers ();
}

void
D_CopyRects (vrect_t *prects, int transparent)
{
/*
  this function is only required if the CPU doesn't have direct access to the
  back buffer, and there's some driver interface function that the driver
  doesn't support and requires Quake to do in software (such as drawing the
  console); Quake will then draw into wherever the driver points vid.buffer
  and will call this function before swapping buffers
*/
}

void
D_EnableBackBufferAccess (void)
{
	VID_LockBuffer ();
}

void
D_TurnZOn (void)
{
	// not needed for software version
}

void
D_DisableBackBufferAccess (void)
{
	VID_UnlockBuffer ();
}

void
D_SetupFrame (void)
{
	int         i;

	if (r_dowarp)
		d_viewbuffer = r_warpbuffer;
	else
		d_viewbuffer = (void *) (byte *) vid.buffer;

	if (r_dowarp)
		screenwidth = WARP_WIDTH;
	else
		screenwidth = vid.rowbytes;

	d_roverwrapped = false;
	d_initial_rover = sc_rover;

	d_minmip = bound (0, d_mipcap->value, 3);

	for (i = 0; i < (NUM_MIPS - 1); i++)
		d_scalemip[i] = basemip[i] * d_mipscale->value;

#ifdef PIC
#undef USE_INTEL_ASM //XXX asm pic hack
#endif

#ifdef USE_INTEL_ASM
	if (d_subdiv16->int_val)
		d_drawspans = D_DrawSpans16;
	else
		d_drawspans = D_DrawSpans8;
#else
	d_drawspans = D_DrawSpans8;
#endif

	d_aflatcolor = 0;
}

void
D_UpdateRects (vrect_t *prect)
{
	// the software driver draws these directly to the vid buffer
}
