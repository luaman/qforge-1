/*
	QF/plugin/cd.h

	CDAudio plugin data types

	Copyright (C) 2001 Jeff Teunissen <deek@quakeforge.net>

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
#ifndef __QF_plugin_cd_h_
#define __QF_plugin_cd_h_

#include <QF/qtypes.h>
#include <QF/plugin.h>

/*
	All CDAudio plugins must export these functions
*/
typedef void (QFPLUGIN *P_CDAudio_CD_f) (void); //
typedef void (QFPLUGIN *P_CDAudio_Pause) (void);
typedef void (QFPLUGIN *P_CDAudio_Play) (byte, qboolean);
typedef void (QFPLUGIN *P_CDAudio_Resume) (void);
typedef void (QFPLUGIN *P_CDAudio_Shutdown) (void);
typedef void (QFPLUGIN *P_CDAudio_Update) (void);
typedef void (QFPLUGIN *P_CDAudio_Init) (void);

typedef struct cd_funcs_s {
	P_CDAudio_CD_f			pCD_f; //
	P_CDAudio_Pause			pCDAudio_Pause;
	P_CDAudio_Play			pCDAudio_Play;
	P_CDAudio_Resume		pCDAudio_Resume;
	P_CDAudio_Shutdown		pCDAudio_Shutdown;
	P_CDAudio_Update		pCDAudio_Update;
	P_CDAudio_Init			pCDAudio_Init;
} cd_funcs_t;

typedef struct cd_data_s {
} cd_data_t;

#endif // __QF_plugin_cd_h_
