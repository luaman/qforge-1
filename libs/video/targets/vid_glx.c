/*
	vid_glx.c

	OpenGL GLX video driver

	Copyright (C) 1996-1997  Id Software, Inc.
	Copyright (C) 2000       Marcus Sundberg [mackan@stacken.kth.se]

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

static __attribute__ ((used)) const char rcsid[] = 
	"$Id$";

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif
#ifdef HAVE_DLOPEN
# include <dlfcn.h>
#endif

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>

#ifdef HAVE_DGA
# ifdef DGA_OLD_HEADERS
#  include <X11/extensions/xf86dga.h>
# else
#  include <X11/extensions/Xxf86dga.h>
# endif
#endif

#include "QF/cmd.h"
#include "QF/cvar.h"
#include "QF/input.h"
#include "QF/qargs.h"
#include "QF/qendian.h"
#include "QF/sys.h"
#include "QF/va.h"
#include "QF/vid.h"
#include "QF/GL/funcs.h"
#include "QF/GL/qf_vid.h"

#include "compat.h"
#include "context_x11.h"
#include "r_cvar.h"
#include "sbar.h"

#define WARP_WIDTH		320
#define WARP_HEIGHT 	200

// GLXContext is a pointer to opaque data
typedef struct __GLXcontextRec *GLXContext;

#define GLX_RGBA				4		// true if RGBA mode
#define GLX_DOUBLEBUFFER		5		// double buffering supported
#define GLX_RED_SIZE			8		// number of red component bits
#define GLX_GREEN_SIZE			9		// number of green component bits
#define GLX_BLUE_SIZE			10		// number of blue component bits
#define GLX_DEPTH_SIZE			12		// number of depth bits

static GLXContext ctx = NULL;
typedef XID GLXDrawable;

void (*qfglXSwapBuffers) (Display *dpy, GLXDrawable drawable);
XVisualInfo* (*qfglXChooseVisual) (Display *dpy, int screen, int *attribList);
GLXContext (*qfglXCreateContext) (Display *dpy, XVisualInfo *vis,
								  GLXContext shareList, Bool direct);
Bool (*qfglXMakeCurrent) (Display *dpy, GLXDrawable drawable, GLXContext ctx);


// ============================================================================

static int use_gl_procaddress = 0;

#if defined(HAVE_DLOPEN)

void * (* glGetProcAddress) (const char *symbol) = NULL;

void *
QFGL_GetProcAddress (void *handle, const char *name)
{
	void       *glfunc = NULL;

	if (use_gl_procaddress && glGetProcAddress)
		glfunc = glGetProcAddress (name);
	if (!glfunc)
		glfunc = dlsym (handle, name);
	return glfunc;
}

void *
QFGL_LoadLibrary (void)
{
	void		*handle;
	int          flags = RTLD_NOW;

#ifdef RTLD_GLOBAL
	flags |= RTLD_GLOBAL;
#endif
	if (!(handle = dlopen (gl_driver->string, flags))) {
		Sys_Error ("Couldn't load OpenGL library %s: %s", gl_driver->string,
				   dlerror ());
	}
	glGetProcAddress = dlsym (handle, "glXGetProcAddress");
	if (!glGetProcAddress)
		glGetProcAddress = dlsym (handle, "glXGetProcAddressARB");
	return handle;
}
#else

# error "Cannot load libraries: %s was not configured with DSO support"

// the following is to avoid other compiler errors
void *
QFGL_GetProcAddress (void *handle, const char *name)
{
	return 0;
}

void *
QFGL_LoadLibrary (void)
{
	return 0;
}
#endif	// HAVE_DLOPEN

static void
glx_get_functions (void)
{
	GLF_Init ();

	qfglXSwapBuffers = QFGL_ProcAddress (libgl_handle, "glXSwapBuffers", true);
	qfglXChooseVisual = QFGL_ProcAddress (libgl_handle, "glXChooseVisual",
										  true);
	qfglXCreateContext = QFGL_ProcAddress (libgl_handle, "glXCreateContext",
										 true);
	qfglXMakeCurrent = QFGL_ProcAddress (libgl_handle, "glXMakeCurrent", true);

	use_gl_procaddress = 1;
}


void
VID_Shutdown (void)
{
	Sys_MaskPrintf (SYS_VID, "VID_Shutdown\n");
	X11_CloseDisplay ();
}

static void
GL_Init (void)
{
	GL_Init_Common ();
}

VISIBLE void
GL_EndRendering (void)
{
	qfglFinish ();
	qfglXSwapBuffers (x_disp, x_win);
	Sbar_Changed ();
}

void
VID_Init (byte *palette, byte *colormap)
{
	int         attrib[] = {
		GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE, 1,
		None
	};

	glx_get_functions ();

	VID_GetWindowSize (640, 480);

	vid.maxwarpwidth = WARP_WIDTH;
	vid.maxwarpheight = WARP_HEIGHT;
	vid.colormap8 = vid_colormap = colormap;
	vid.fullbright = 256 - vid.colormap8[256 * VID_GRADES];

	X11_OpenDisplay ();

	x_visinfo = qfglXChooseVisual (x_disp, x_screen, attrib);
	if (!x_visinfo) {
		Sys_Error ("Error couldn't get an RGB, Double-buffered, Depth visual");
	}
	x_vis = x_visinfo->visual;

	X11_SetVidMode (vid.width, vid.height);
	X11_CreateWindow (vid.width, vid.height);
	X11_CreateNullCursor ();	// hide mouse pointer

	XSync (x_disp, 0);

	ctx = qfglXCreateContext (x_disp, x_visinfo, NULL, True);

	qfglXMakeCurrent (x_disp, x_win, ctx);

	vid.numpages = 2;

	GL_Init ();

	VID_InitGamma (palette);

	// Check for 8-bit extension and initialize if present
	VID_Init8bitPalette ();
	VID_SetPalette (vid.palette);

	Sys_MaskPrintf (SYS_VID, "Video mode %dx%d initialized.\n",
					vid.width, vid.height);

	vid.initialized = true;

	vid.recalc_refdef = 1;				// force a surface cache flush
}

void
VID_Init_Cvars ()
{
	X11_Init_Cvars ();
}

void
VID_SetCaption (const char *text)
{
	if (text && *text) {
		char	*temp = strdup (text);

		X11_SetCaption (va ("%s: %s", PACKAGE_STRING, temp));
		free (temp);
	} else {
		X11_SetCaption (va ("%s", PACKAGE_STRING));
	}
}

qboolean
VID_SetGamma (double gamma)
{
	return X11_SetGamma (gamma);
}
