/*
	gl_funcs_list.h

	QF GL function list.

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

#ifndef QFGL_DONT_NEED
#define QFGL_DONT_NEED(ret, func, params)
#define UNDEF_QFGL_DONT_NEED
#endif

#ifndef QFGL_NEED
#define QFGL_NEED(ret, func, params)
#define UNDEF_QFGL_NEED
#endif

QFGL_DONT_NEED (void, glAccum, (GLenum op, GLfloat value));
QFGL_NEED (void, glAlphaFunc, (GLenum func, GLclampf ref));
QFGL_DONT_NEED (GLboolean, glAreTexturesResident, (GLsizei n, const GLuint * textures, GLboolean * residences));
QFGL_DONT_NEED (void, glArrayElement, (GLint i));
QFGL_NEED (void, glBegin, (GLenum mode));
QFGL_NEED (void, glBindTexture, (GLenum target, GLuint texture));
QFGL_DONT_NEED (void, glBitmap, (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap));
QFGL_DONT_NEED (void, glBlendColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
QFGL_DONT_NEED (void, glBlendEquation, (GLenum mode));
QFGL_NEED (void, glBlendFunc, (GLenum sfactor, GLenum dfactor));
QFGL_DONT_NEED (void, glCallList, (GLuint list));
QFGL_DONT_NEED (void, glCallLists, (GLsizei n, GLenum type, const GLvoid * lists));
QFGL_NEED (void, glClear, (GLbitfield mask));
QFGL_NEED (void, glClearAccum, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha));
QFGL_NEED (void, glClearColor, (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha));
QFGL_NEED (void, glClearDepth, (GLclampd depth));
QFGL_NEED (void, glClearIndex, (GLfloat c));
QFGL_NEED (void, glClearStencil, (GLint s));
QFGL_DONT_NEED (void, glClipPlane, (GLenum plane, const GLdouble * equation));
QFGL_DONT_NEED (void, glColor3b, (GLbyte red, GLbyte green, GLbyte blue));
QFGL_DONT_NEED (void, glColor3bv, (const GLbyte * v));
QFGL_DONT_NEED (void, glColor3d, (GLdouble red, GLdouble green, GLdouble blue));
QFGL_DONT_NEED (void, glColor3dv, (const GLdouble * v));
QFGL_NEED (void, glColor3f, (GLfloat red, GLfloat green, GLfloat blue));
QFGL_NEED (void, glColor3fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glColor3i, (GLint red, GLint green, GLint blue));
QFGL_DONT_NEED (void, glColor3iv, (const GLint * v));
QFGL_DONT_NEED (void, glColor3s, (GLshort red, GLshort green, GLshort blue));
QFGL_DONT_NEED (void, glColor3sv, (const GLshort * v));
QFGL_DONT_NEED (void, glColor3ub, (GLubyte red, GLubyte green, GLubyte blue));
QFGL_NEED (void, glColor3ubv, (const GLubyte * v));
QFGL_DONT_NEED (void, glColor3ui, (GLuint red, GLuint green, GLuint blue));
QFGL_DONT_NEED (void, glColor3uiv, (const GLuint * v));
QFGL_DONT_NEED (void, glColor3us, (GLushort red, GLushort green, GLushort blue));
QFGL_DONT_NEED (void, glColor3usv, (const GLushort * v));
QFGL_DONT_NEED (void, glColor4b, (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha));
QFGL_DONT_NEED (void, glColor4bv, (const GLbyte * v));
QFGL_DONT_NEED (void, glColor4d, (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha));
QFGL_DONT_NEED (void, glColor4dv, (const GLdouble * v));
QFGL_NEED (void, glColor4f, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha));
QFGL_NEED (void, glColor4fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glColor4i, (GLint red, GLint green, GLint blue, GLint alpha));
QFGL_DONT_NEED (void, glColor4iv, (const GLint * v));
QFGL_DONT_NEED (void, glColor4s, (GLshort red, GLshort green, GLshort blue, GLshort alpha));
QFGL_DONT_NEED (void, glColor4sv, (const GLshort * v));
QFGL_NEED (void, glColor4ub, (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha));
QFGL_NEED (void, glColor4ubv, (const GLubyte * v));
QFGL_DONT_NEED (void, glColor4ui, (GLuint red, GLuint green, GLuint blue, GLuint alpha));
QFGL_DONT_NEED (void, glColor4uiv, (const GLuint * v));
QFGL_DONT_NEED (void, glColor4us, (GLushort red, GLushort green, GLushort blue, GLushort alpha));
QFGL_DONT_NEED (void, glColor4usv, (const GLushort * v));
QFGL_NEED (void, glColorMask, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha));
QFGL_DONT_NEED (void, glColorMaterial, (GLenum face, GLenum mode));
QFGL_NEED (void, glColorPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid * ptr));
QFGL_DONT_NEED (void, glColorSubTable, (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid * data));
QFGL_DONT_NEED (void, glColorTable, (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * table));
QFGL_DONT_NEED (void, glColorTableParameterfv, (GLenum target, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glColorTableParameteriv, (GLenum target, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glConvolutionFilter1D, (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid * image));
QFGL_DONT_NEED (void, glConvolutionFilter2D, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * image));
QFGL_DONT_NEED (void, glConvolutionParameterf, (GLenum target, GLenum pname, GLfloat params));
QFGL_DONT_NEED (void, glConvolutionParameterfv, (GLenum target, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glConvolutionParameteri, (GLenum target, GLenum pname, GLint params));
QFGL_DONT_NEED (void, glConvolutionParameteriv, (GLenum target, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glCopyColorSubTable, (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width));
QFGL_DONT_NEED (void, glCopyColorTable, (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width));
QFGL_DONT_NEED (void, glCopyConvolutionFilter1D, (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width));
QFGL_DONT_NEED (void, glCopyConvolutionFilter2D, (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height));
QFGL_DONT_NEED (void, glCopyPixels, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type));
QFGL_DONT_NEED (void, glCopyTexImage1D, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border));
QFGL_DONT_NEED (void, glCopyTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border));
QFGL_DONT_NEED (void, glCopyTexSubImage1D, (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width));
QFGL_DONT_NEED (void, glCopyTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height));
QFGL_DONT_NEED (void, glCopyTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height));
QFGL_NEED (void, glCullFace, (GLenum mode));
QFGL_DONT_NEED (void, glDeleteLists, (GLuint list, GLsizei range));
QFGL_NEED (void, glDeleteTextures, (GLsizei n, const GLuint * textures));
QFGL_NEED (void, glDepthFunc, (GLenum func));
QFGL_NEED (void, glDepthMask, (GLboolean flag));
QFGL_NEED (void, glDepthRange, (GLclampd near_val, GLclampd far_val));
QFGL_NEED (void, glDisable, (GLenum cap));
QFGL_NEED (void, glDisableClientState, (GLenum cap));
QFGL_NEED (void, glDrawArrays, (GLenum mode, GLint first, GLsizei count));
QFGL_NEED (void, glDrawBuffer, (GLenum mode));
QFGL_NEED (void, glDrawElements, (GLenum mode, GLsizei count, GLenum type, const GLvoid * indices));
QFGL_DONT_NEED (void, glDrawPixels, (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_DONT_NEED (void, glDrawRangeElements, (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices));
QFGL_DONT_NEED (void, glEdgeFlag, (GLboolean flag));
QFGL_DONT_NEED (void, glEdgeFlagPointer, (GLsizei stride, const GLvoid * ptr));
QFGL_DONT_NEED (void, glEdgeFlagv, (const GLboolean * flag));
QFGL_NEED (void, glEnable, (GLenum cap));
QFGL_NEED (void, glEnableClientState, (GLenum cap));
QFGL_NEED (void, glEnd, (void));
QFGL_NEED (void, glEndList, (void));
QFGL_DONT_NEED (void, glEvalCoord1d, (GLdouble u));
QFGL_DONT_NEED (void, glEvalCoord1dv, (const GLdouble * u));
QFGL_DONT_NEED (void, glEvalCoord1f, (GLfloat u));
QFGL_DONT_NEED (void, glEvalCoord1fv, (const GLfloat * u));
QFGL_DONT_NEED (void, glEvalCoord2d, (GLdouble u, GLdouble v));
QFGL_DONT_NEED (void, glEvalCoord2dv, (const GLdouble * u));
QFGL_DONT_NEED (void, glEvalCoord2f, (GLfloat u, GLfloat v));
QFGL_DONT_NEED (void, glEvalCoord2fv, (const GLfloat * u));
QFGL_DONT_NEED (void, glEvalMesh1, (GLenum mode, GLint i1, GLint i2));
QFGL_DONT_NEED (void, glEvalMesh2, (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2));
QFGL_DONT_NEED (void, glEvalPoint1, (GLint i));
QFGL_DONT_NEED (void, glEvalPoint2, (GLint i, GLint j));
QFGL_DONT_NEED (void, glFeedbackBuffer, (GLsizei size, GLenum type, GLfloat * buffer));
QFGL_NEED (void, glFinish, (void));
QFGL_NEED (void, glFlush, (void));
QFGL_DONT_NEED (void, glFogf, (GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glFogfv, (GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glFogi, (GLenum pname, GLint param));
QFGL_DONT_NEED (void, glFogiv, (GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glFrontFace, (GLenum mode));
QFGL_NEED (void, glFrustum, (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val));
QFGL_DONT_NEED (GLuint, glGenLists, (GLsizei range));
QFGL_DONT_NEED (void, glGenTextures, (GLsizei n, GLuint * textures));
QFGL_DONT_NEED (void, glGetBooleanv, (GLenum pname, GLboolean * params));
QFGL_DONT_NEED (void, glGetClipPlane, (GLenum plane, GLdouble * equation));
QFGL_DONT_NEED (void, glGetColorTable, (GLenum target, GLenum format, GLenum type, GLvoid * table));
QFGL_DONT_NEED (void, glGetColorTableParameterfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetColorTableParameteriv, (GLenum target, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetConvolutionFilter, (GLenum target, GLenum format, GLenum type, GLvoid * image));
QFGL_DONT_NEED (void, glGetConvolutionParameterfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetConvolutionParameteriv, (GLenum target, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetDoublev, (GLenum pname, GLdouble * params));
QFGL_DONT_NEED (GLenum, glGetError, (void));
QFGL_NEED (void, glGetFloatv, (GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetHistogram, (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid * values));
QFGL_DONT_NEED (void, glGetHistogramParameterfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetHistogramParameteriv, (GLenum target, GLenum pname, GLint * params));
QFGL_NEED (void, glGetIntegerv, (GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetLightfv, (GLenum light, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetLightiv, (GLenum light, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetMapdv, (GLenum target, GLenum query, GLdouble * v));
QFGL_DONT_NEED (void, glGetMapfv, (GLenum target, GLenum query, GLfloat * v));
QFGL_DONT_NEED (void, glGetMapiv, (GLenum target, GLenum query, GLint * v));
QFGL_DONT_NEED (void, glGetMaterialfv, (GLenum face, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetMaterialiv, (GLenum face, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetMinmax, (GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid * values));
QFGL_DONT_NEED (void, glGetMinmaxParameterfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetMinmaxParameteriv, (GLenum target, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetPixelMapfv, (GLenum map, GLfloat * values));
QFGL_DONT_NEED (void, glGetPixelMapuiv, (GLenum map, GLuint * values));
QFGL_DONT_NEED (void, glGetPixelMapusv, (GLenum map, GLushort * values));
QFGL_DONT_NEED (void, glGetPointerv, (GLenum pname, void **params));
QFGL_DONT_NEED (void, glGetPolygonStipple, (GLubyte * mask));
QFGL_DONT_NEED (void, glGetSeparableFilter, (GLenum target, GLenum format, GLenum type, GLvoid * row, GLvoid * column, GLvoid * span));
QFGL_NEED (const GLubyte *, glGetString, (GLenum name));
QFGL_DONT_NEED (void, glGetTexEnvfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetTexEnviv, (GLenum target, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetTexGendv, (GLenum coord, GLenum pname, GLdouble * params));
QFGL_DONT_NEED (void, glGetTexGenfv, (GLenum coord, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetTexGeniv, (GLenum coord, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetTexImage, (GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels));
QFGL_DONT_NEED (void, glGetTexLevelParameterfv, (GLenum target, GLint level, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetTexLevelParameteriv, (GLenum target, GLint level, GLenum pname, GLint * params));
QFGL_DONT_NEED (void, glGetTexParameterfv, (GLenum target, GLenum pname, GLfloat * params));
QFGL_DONT_NEED (void, glGetTexParameteriv, (GLenum target, GLenum pname, GLint * params));
QFGL_NEED (void, glHint, (GLenum target, GLenum mode));
QFGL_DONT_NEED (void, glHistogram, (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink));
QFGL_DONT_NEED (void, glIndexMask, (GLuint mask));
QFGL_DONT_NEED (void, glIndexPointer, (GLenum type, GLsizei stride, const GLvoid * ptr));
QFGL_DONT_NEED (void, glIndexd, (GLdouble c));
QFGL_DONT_NEED (void, glIndexdv, (const GLdouble * c));
QFGL_DONT_NEED (void, glIndexf, (GLfloat c));
QFGL_DONT_NEED (void, glIndexfv, (const GLfloat * c));
QFGL_DONT_NEED (void, glIndexi, (GLint c));
QFGL_DONT_NEED (void, glIndexiv, (const GLint * c));
QFGL_DONT_NEED (void, glIndexs, (GLshort c));
QFGL_DONT_NEED (void, glIndexsv, (const GLshort * c));
QFGL_DONT_NEED (void, glIndexub, (GLubyte c));
QFGL_DONT_NEED (void, glIndexubv, (const GLubyte * c));
QFGL_DONT_NEED (void, glInitNames, (void));
QFGL_NEED (void, glInterleavedArrays, (GLenum format, GLsizei stride, const GLvoid * pointer));
QFGL_DONT_NEED (GLboolean, glIsEnabled, (GLenum cap));
QFGL_DONT_NEED (GLboolean, glIsList, (GLuint list));
QFGL_DONT_NEED (GLboolean, glIsTexture, (GLuint texture));
QFGL_DONT_NEED (void, glLightModelf, (GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glLightModelfv, (GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glLightModeli, (GLenum pname, GLint param));
QFGL_DONT_NEED (void, glLightModeliv, (GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glLightf, (GLenum light, GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glLightfv, (GLenum light, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glLighti, (GLenum light, GLenum pname, GLint param));
QFGL_DONT_NEED (void, glLightiv, (GLenum light, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glLineStipple, (GLint factor, GLushort pattern));
QFGL_DONT_NEED (void, glLineWidth, (GLfloat width));
QFGL_DONT_NEED (void, glListBase, (GLuint base));
QFGL_NEED (void, glLoadIdentity, (void));
QFGL_DONT_NEED (void, glLoadMatrixd, (const GLdouble * m));
QFGL_NEED (void, glLoadMatrixf, (const GLfloat * m));
QFGL_DONT_NEED (void, glLoadName, (GLuint name));
QFGL_DONT_NEED (void, glLogicOp, (GLenum opcode));
QFGL_DONT_NEED (void, glMap1d, (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points));
QFGL_DONT_NEED (void, glMap1f, (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points));
QFGL_DONT_NEED (void, glMap2d, (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points));
QFGL_DONT_NEED (void, glMap2f, (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points));
QFGL_DONT_NEED (void, glMapGrid1d, (GLint un, GLdouble u1, GLdouble u2));
QFGL_DONT_NEED (void, glMapGrid1f, (GLint un, GLfloat u1, GLfloat u2));
QFGL_DONT_NEED (void, glMapGrid2d, (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2));
QFGL_DONT_NEED (void, glMapGrid2f, (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2));
QFGL_DONT_NEED (void, glMaterialf, (GLenum face, GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glMaterialfv, (GLenum face, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glMateriali, (GLenum face, GLenum pname, GLint param));
QFGL_DONT_NEED (void, glMaterialiv, (GLenum face, GLenum pname, const GLint * params));
QFGL_NEED (void, glMatrixMode, (GLenum mode));
QFGL_DONT_NEED (void, glMinmax, (GLenum target, GLenum internalformat, GLboolean sink));
QFGL_DONT_NEED (void, glMultMatrixd, (const GLdouble * m));
QFGL_DONT_NEED (void, glMultMatrixf, (const GLfloat * m));
QFGL_DONT_NEED (void, glNewList, (GLuint list, GLenum mode));
QFGL_DONT_NEED (void, glNormal3b, (GLbyte nx, GLbyte ny, GLbyte nz));
QFGL_DONT_NEED (void, glNormal3bv, (const GLbyte * v));
QFGL_DONT_NEED (void, glNormal3d, (GLdouble nx, GLdouble ny, GLdouble nz));
QFGL_DONT_NEED (void, glNormal3dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glNormal3f, (GLfloat nx, GLfloat ny, GLfloat nz));
QFGL_DONT_NEED (void, glNormal3fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glNormal3i, (GLint nx, GLint ny, GLint nz));
QFGL_DONT_NEED (void, glNormal3iv, (const GLint * v));
QFGL_DONT_NEED (void, glNormal3s, (GLshort nx, GLshort ny, GLshort nz));
QFGL_DONT_NEED (void, glNormal3sv, (const GLshort * v));
QFGL_DONT_NEED (void, glNormalPointer, (GLenum type, GLsizei stride, const GLvoid * ptr));
QFGL_NEED (void, glOrtho, (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val));
QFGL_DONT_NEED (void, glPassThrough, (GLfloat token));
QFGL_DONT_NEED (void, glPixelMapfv, (GLenum map, GLint mapsize, const GLfloat * values));
QFGL_DONT_NEED (void, glPixelMapuiv, (GLenum map, GLint mapsize, const GLuint * values));
QFGL_DONT_NEED (void, glPixelMapusv, (GLenum map, GLint mapsize, const GLushort * values));
QFGL_DONT_NEED (void, glPixelStoref, (GLenum pname, GLfloat param));
QFGL_NEED (void, glPixelStorei, (GLenum pname, GLint param));
QFGL_DONT_NEED (void, glPixelTransferf, (GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glPixelTransferi, (GLenum pname, GLint param));
QFGL_DONT_NEED (void, glPixelZoom, (GLfloat xfactor, GLfloat yfactor));
QFGL_DONT_NEED (void, glPointSize, (GLfloat size));
QFGL_NEED (void, glPolygonMode, (GLenum face, GLenum mode));
QFGL_DONT_NEED (void, glPolygonOffset, (GLfloat factor, GLfloat units));
QFGL_DONT_NEED (void, glPolygonStipple, (const GLubyte * mask));
QFGL_DONT_NEED (void, glPopAttrib, (void));
QFGL_DONT_NEED (void, glPopClientAttrib, (void));
QFGL_NEED (void, glPopMatrix, (void));
QFGL_DONT_NEED (void, glPopName, (void));
QFGL_DONT_NEED (void, glPrioritizeTextures, (GLsizei n, const GLuint * textures, const GLclampf * priorities));
QFGL_DONT_NEED (void, glPushAttrib, (GLbitfield mask));
QFGL_DONT_NEED (void, glPushClientAttrib, (GLbitfield mask));
QFGL_NEED (void, glPushMatrix, (void));
QFGL_DONT_NEED (void, glPushName, (GLuint name));
QFGL_DONT_NEED (void, glRasterPos2d, (GLdouble x, GLdouble y));
QFGL_DONT_NEED (void, glRasterPos2dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glRasterPos2f, (GLfloat x, GLfloat y));
QFGL_DONT_NEED (void, glRasterPos2fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glRasterPos2i, (GLint x, GLint y));
QFGL_DONT_NEED (void, glRasterPos2iv, (const GLint * v));
QFGL_DONT_NEED (void, glRasterPos2s, (GLshort x, GLshort y));
QFGL_DONT_NEED (void, glRasterPos2sv, (const GLshort * v));
QFGL_DONT_NEED (void, glRasterPos3d, (GLdouble x, GLdouble y, GLdouble z));
QFGL_DONT_NEED (void, glRasterPos3dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glRasterPos3f, (GLfloat x, GLfloat y, GLfloat z));
QFGL_DONT_NEED (void, glRasterPos3fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glRasterPos3i, (GLint x, GLint y, GLint z));
QFGL_DONT_NEED (void, glRasterPos3iv, (const GLint * v));
QFGL_DONT_NEED (void, glRasterPos3s, (GLshort x, GLshort y, GLshort z));
QFGL_DONT_NEED (void, glRasterPos3sv, (const GLshort * v));
QFGL_DONT_NEED (void, glRasterPos4d, (GLdouble x, GLdouble y, GLdouble z, GLdouble w));
QFGL_DONT_NEED (void, glRasterPos4dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glRasterPos4f, (GLfloat x, GLfloat y, GLfloat z, GLfloat w));
QFGL_DONT_NEED (void, glRasterPos4fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glRasterPos4i, (GLint x, GLint y, GLint z, GLint w));
QFGL_DONT_NEED (void, glRasterPos4iv, (const GLint * v));
QFGL_DONT_NEED (void, glRasterPos4s, (GLshort x, GLshort y, GLshort z, GLshort w));
QFGL_DONT_NEED (void, glRasterPos4sv, (const GLshort * v));
QFGL_NEED (void, glReadBuffer, (GLenum mode));
QFGL_NEED (void, glReadPixels, (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels));
QFGL_DONT_NEED (void, glRectd, (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2));
QFGL_DONT_NEED (void, glRectdv, (const GLdouble * v1, const GLdouble * v2));
QFGL_DONT_NEED (void, glRectf, (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2));
QFGL_DONT_NEED (void, glRectfv, (const GLfloat * v1, const GLfloat * v2));
QFGL_DONT_NEED (void, glRecti, (GLint x1, GLint y1, GLint x2, GLint y2));
QFGL_DONT_NEED (void, glRectiv, (const GLint * v1, const GLint * v2));
QFGL_DONT_NEED (void, glRects, (GLshort x1, GLshort y1, GLshort x2, GLshort y2));
QFGL_DONT_NEED (void, glRectsv, (const GLshort * v1, const GLshort * v2));
QFGL_DONT_NEED (GLint, glRenderMode, (GLenum mode));
QFGL_DONT_NEED (void, glResetHistogram, (GLenum target));
QFGL_DONT_NEED (void, glResetMinmax, (GLenum target));
QFGL_DONT_NEED (void, glRotated, (GLdouble angle, GLdouble x, GLdouble y, GLdouble z));
QFGL_NEED (void, glRotatef, (GLfloat angle, GLfloat x, GLfloat y, GLfloat z));
QFGL_DONT_NEED (void, glScaled, (GLdouble x, GLdouble y, GLdouble z));
QFGL_NEED (void, glScalef, (GLfloat x, GLfloat y, GLfloat z));
QFGL_DONT_NEED (void, glScissor, (GLint x, GLint y, GLsizei width, GLsizei height));
QFGL_DONT_NEED (void, glSelectBuffer, (GLsizei size, GLuint * buffer));
QFGL_DONT_NEED (void, glSeparableFilter2D, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * row, const GLvoid * column));
QFGL_NEED (void, glShadeModel, (GLenum mode));
QFGL_DONT_NEED (void, glStencilFunc, (GLenum func, GLint ref, GLuint mask));
QFGL_DONT_NEED (void, glStencilMask, (GLuint mask));
QFGL_DONT_NEED (void, glStencilOp, (GLenum fail, GLenum zfail, GLenum zpass));
QFGL_DONT_NEED (void, glTexCoord1d, (GLdouble s));
QFGL_DONT_NEED (void, glTexCoord1dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glTexCoord1f, (GLfloat s));
QFGL_DONT_NEED (void, glTexCoord1fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glTexCoord1i, (GLint s));
QFGL_DONT_NEED (void, glTexCoord1iv, (const GLint * v));
QFGL_DONT_NEED (void, glTexCoord1s, (GLshort s));
QFGL_DONT_NEED (void, glTexCoord1sv, (const GLshort * v));
QFGL_DONT_NEED (void, glTexCoord2d, (GLdouble s, GLdouble t));
QFGL_DONT_NEED (void, glTexCoord2dv, (const GLdouble * v));
QFGL_NEED (void, glTexCoord2f, (GLfloat s, GLfloat t));
QFGL_NEED (void, glTexCoord2fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glTexCoord2i, (GLint s, GLint t));
QFGL_DONT_NEED (void, glTexCoord2iv, (const GLint * v));
QFGL_DONT_NEED (void, glTexCoord2s, (GLshort s, GLshort t));
QFGL_DONT_NEED (void, glTexCoord2sv, (const GLshort * v));
QFGL_DONT_NEED (void, glTexCoord3d, (GLdouble s, GLdouble t, GLdouble r));
QFGL_DONT_NEED (void, glTexCoord3dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glTexCoord3f, (GLfloat s, GLfloat t, GLfloat r));
QFGL_DONT_NEED (void, glTexCoord3fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glTexCoord3i, (GLint s, GLint t, GLint r));
QFGL_DONT_NEED (void, glTexCoord3iv, (const GLint * v));
QFGL_DONT_NEED (void, glTexCoord3s, (GLshort s, GLshort t, GLshort r));
QFGL_DONT_NEED (void, glTexCoord3sv, (const GLshort * v));
QFGL_DONT_NEED (void, glTexCoord4d, (GLdouble s, GLdouble t, GLdouble r, GLdouble q));
QFGL_DONT_NEED (void, glTexCoord4dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glTexCoord4f, (GLfloat s, GLfloat t, GLfloat r, GLfloat q));
QFGL_DONT_NEED (void, glTexCoord4fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glTexCoord4i, (GLint s, GLint t, GLint r, GLint q));
QFGL_DONT_NEED (void, glTexCoord4iv, (const GLint * v));
QFGL_DONT_NEED (void, glTexCoord4s, (GLshort s, GLshort t, GLshort r, GLshort q));
QFGL_DONT_NEED (void, glTexCoord4sv, (const GLshort * v));
QFGL_NEED (void, glTexCoordPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid * ptr));
QFGL_NEED (void, glTexEnvf, (GLenum target, GLenum pname, GLfloat param));
QFGL_NEED (void, glTexEnvfv, (GLenum target, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glTexEnvi, (GLenum target, GLenum pname, GLint param));
QFGL_DONT_NEED (void, glTexEnviv, (GLenum target, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glTexGend, (GLenum coord, GLenum pname, GLdouble param));
QFGL_DONT_NEED (void, glTexGendv, (GLenum coord, GLenum pname, const GLdouble * params));
QFGL_DONT_NEED (void, glTexGenf, (GLenum coord, GLenum pname, GLfloat param));
QFGL_DONT_NEED (void, glTexGenfv, (GLenum coord, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glTexGeni, (GLenum coord, GLenum pname, GLint param));
QFGL_DONT_NEED (void, glTexGeniv, (GLenum coord, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glTexImage1D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_NEED (void, glTexImage2D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_DONT_NEED (void, glTexImage3D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_NEED (void, glTexParameterf, (GLenum target, GLenum pname, GLfloat param));
QFGL_NEED (void, glTexParameterfv, (GLenum target, GLenum pname, const GLfloat * params));
QFGL_DONT_NEED (void, glTexParameteri, (GLenum target, GLenum pname, GLint param));
QFGL_DONT_NEED (void, glTexParameteriv, (GLenum target, GLenum pname, const GLint * params));
QFGL_DONT_NEED (void, glTexSubImage1D, (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_NEED (void, glTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_DONT_NEED (void, glTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels));
QFGL_DONT_NEED (void, glTranslated, (GLdouble x, GLdouble y, GLdouble z));
QFGL_NEED (void, glTranslatef, (GLfloat x, GLfloat y, GLfloat z));
QFGL_DONT_NEED (void, glVertex2d, (GLdouble x, GLdouble y));
QFGL_DONT_NEED (void, glVertex2dv, (const GLdouble * v));
QFGL_NEED (void, glVertex2f, (GLfloat x, GLfloat y));
QFGL_NEED (void, glVertex2fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glVertex2i, (GLint x, GLint y));
QFGL_DONT_NEED (void, glVertex2iv, (const GLint * v));
QFGL_DONT_NEED (void, glVertex2s, (GLshort x, GLshort y));
QFGL_DONT_NEED (void, glVertex2sv, (const GLshort * v));
QFGL_DONT_NEED (void, glVertex3d, (GLdouble x, GLdouble y, GLdouble z));
QFGL_DONT_NEED (void, glVertex3dv, (const GLdouble * v));
QFGL_NEED (void, glVertex3f, (GLfloat x, GLfloat y, GLfloat z));
QFGL_NEED (void, glVertex3fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glVertex3i, (GLint x, GLint y, GLint z));
QFGL_DONT_NEED (void, glVertex3iv, (const GLint * v));
QFGL_DONT_NEED (void, glVertex3s, (GLshort x, GLshort y, GLshort z));
QFGL_DONT_NEED (void, glVertex3sv, (const GLshort * v));
QFGL_DONT_NEED (void, glVertex4d, (GLdouble x, GLdouble y, GLdouble z, GLdouble w));
QFGL_DONT_NEED (void, glVertex4dv, (const GLdouble * v));
QFGL_DONT_NEED (void, glVertex4f, (GLfloat x, GLfloat y, GLfloat z, GLfloat w));
QFGL_DONT_NEED (void, glVertex4fv, (const GLfloat * v));
QFGL_DONT_NEED (void, glVertex4i, (GLint x, GLint y, GLint z, GLint w));
QFGL_DONT_NEED (void, glVertex4iv, (const GLint * v));
QFGL_DONT_NEED (void, glVertex4s, (GLshort x, GLshort y, GLshort z, GLshort w));
QFGL_DONT_NEED (void, glVertex4sv, (const GLshort * v));
QFGL_NEED (void, glVertexPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid * ptr));
QFGL_NEED (void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height));

#ifdef UNDEF_QFGL_DONT_NEED
#undef QFGL_DONT_NEED
#endif

#ifdef UNDEF_QFGL_NEED
#undef QFGL_DONT_NEED
#endif
