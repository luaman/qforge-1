/*
	glsl_skin.c

	GLSL rendering

	Copyright (C) 2012 Bill Currie <bill@taniwha.org>

	Author: Bill Currie <bill@taniwha.org>
	Date: 2012/1/13

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
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

static __attribute__ ((used)) const char rcsid[] = "$Id$";

#include "QF/image.h"
#include "QF/model.h"
#include "QF/skin.h"

VISIBLE void
Skin_Player_Model (model_t *model)
{
}

VISIBLE void
Skin_Set_Translate (int top, int bottom, void *_dest)
{
}

VISIBLE void
Skin_Do_Translation (skin_t *player_skin, int slot, skin_t *skin)
{
}

VISIBLE void
Skin_Do_Translation_Model (model_t *model, int skinnum, int slot,
						   skin_t *skin)
{
}

VISIBLE void
Skin_Process (skin_t *skin, tex_t *tex)
{
}

VISIBLE void
Skin_Init_Translation (void)
{
}
