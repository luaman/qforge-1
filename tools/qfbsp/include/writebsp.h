/*
	Copyright (C) 1996-1997  Id Software, Inc.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

	See file, 'COPYING', for details.

	$Id$
*/

#ifndef qfbsp_writebsp_h
#define qfbsp_writebsp_h

#include "QF/bspfile.h"

/**	\defgroup qfbsp_writebsp BSP Writing Functions
	\ingroup qfbsp
*/
//@{

struct node_s;

void WriteNodePlanes (struct node_s *headnode);
void WriteClipNodes (struct node_s *headnode);
void WriteDrawNodes (struct node_s *headnode);

void BumpModel (int hullnum);
int FindFinalPlane (dplane_t *p);

void BeginBSPFile (void);
void FinishBSPFile (void);

//@}

#endif//qfbsp_writebsp_h
