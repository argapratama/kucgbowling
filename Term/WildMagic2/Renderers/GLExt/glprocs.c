/*
** GLprocs utility for getting function addresses for OpenGL(R) 1.2, 
** OpenGL 1.3 and OpenGL extension functions.
**
** Version:  1.1
**
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.1 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: This software was created using the
** OpenGL(R) version 1.2.1 Sample Implementation published by SGI, but has
** not been independently verified as being compliant with the OpenGL(R)
** version 1.2.1 Specification.
**
** Initial version of glprocs.{c,h} contributed by Intel(R) Corporation.
**
** 11/30/2001 Revised by Hans Weber (hans@the-webers.org) to provide
**            support for glext.h version 9. (v 1.1)
*/

#include <assert.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <windows.h>
  #include "GL/gl.h"  /* Include local "gl.h". Don't include vc32 <GL/gl.h>. */
  #include "GL/glprocs.h"
#else /* GLX */
  #include <GL/gl.h>
  #include <GL/glx.h>
  #include <GL/glprocs.h>
  #define wglGetProcAddress glXGetProcAddressARB
#endif

#define _ASSERT(a) assert(a)

static void APIENTRY InitBlendColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendColor");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendColor = extproc;

	glBlendColor(red, green, blue, alpha);
}

static void APIENTRY InitBlendEquation (GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendEquation");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendEquation = extproc;

	glBlendEquation(mode);
}

static void APIENTRY InitDrawRangeElements (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDrawRangeElements");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDrawRangeElements = extproc;

	glDrawRangeElements(mode, start, end, count, type, indices);
}

static void APIENTRY InitColorTable (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTable");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTable = extproc;

	glColorTable(target, internalformat, width, format, type, table);
}

static void APIENTRY InitColorTableParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableParameterfv = extproc;

	glColorTableParameterfv(target, pname, params);
}

static void APIENTRY InitColorTableParameteriv (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableParameteriv = extproc;

	glColorTableParameteriv(target, pname, params);
}

static void APIENTRY InitCopyColorTable (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyColorTable");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyColorTable = extproc;

	glCopyColorTable(target, internalformat, x, y, width);
}

static void APIENTRY InitGetColorTable (GLenum target, GLenum format, GLenum type, GLvoid *table)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTable");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTable = extproc;

	glGetColorTable(target, format, type, table);
}

static void APIENTRY InitGetColorTableParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameterfv = extproc;

	glGetColorTableParameterfv(target, pname, params);
}

static void APIENTRY InitGetColorTableParameteriv (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameteriv = extproc;

	glGetColorTableParameteriv(target, pname, params);
}

static void APIENTRY InitColorSubTable (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorSubTable");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorSubTable = extproc;

	glColorSubTable(target, start, count, format, type, data);
}

static void APIENTRY InitCopyColorSubTable (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyColorSubTable");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyColorSubTable = extproc;

	glCopyColorSubTable(target, start, x, y, width);
}

static void APIENTRY InitConvolutionFilter1D (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionFilter1D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionFilter1D = extproc;

	glConvolutionFilter1D(target, internalformat, width, format, type, image);
}

static void APIENTRY InitConvolutionFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionFilter2D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionFilter2D = extproc;

	glConvolutionFilter2D(target, internalformat, width, height, format, type, image);
}

static void APIENTRY InitConvolutionParameterf (GLenum target, GLenum pname, GLfloat params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameterf");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameterf = extproc;

	glConvolutionParameterf(target, pname, params);
}

static void APIENTRY InitConvolutionParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameterfv = extproc;

	glConvolutionParameterfv(target, pname, params);
}

static void APIENTRY InitConvolutionParameteri (GLenum target, GLenum pname, GLint params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameteri");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameteri = extproc;

	glConvolutionParameteri(target, pname, params);
}

static void APIENTRY InitConvolutionParameteriv (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameteriv = extproc;

	glConvolutionParameteriv(target, pname, params);
}

static void APIENTRY InitCopyConvolutionFilter1D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyConvolutionFilter1D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyConvolutionFilter1D = extproc;

	glCopyConvolutionFilter1D(target, internalformat, x, y, width);
}

static void APIENTRY InitCopyConvolutionFilter2D (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyConvolutionFilter2D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyConvolutionFilter2D = extproc;

	glCopyConvolutionFilter2D(target, internalformat, x, y, width, height);
}

static void APIENTRY InitGetConvolutionFilter (GLenum target, GLenum format, GLenum type, GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionFilter");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionFilter = extproc;

	glGetConvolutionFilter(target, format, type, image);
}

static void APIENTRY InitGetConvolutionParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionParameterfv = extproc;

	glGetConvolutionParameterfv(target, pname, params);
}

static void APIENTRY InitGetConvolutionParameteriv (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionParameteriv = extproc;

	glGetConvolutionParameteriv(target, pname, params);
}

static void APIENTRY InitGetSeparableFilter (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetSeparableFilter");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetSeparableFilter = extproc;

	glGetSeparableFilter(target, format, type, row, column, span);
}

static void APIENTRY InitSeparableFilter2D (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSeparableFilter2D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSeparableFilter2D = extproc;

	glSeparableFilter2D(target, internalformat, width, height, format, type, row, column);
}

static void APIENTRY InitGetHistogram (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogram");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogram = extproc;

	glGetHistogram(target, reset, format, type, values);
}

static void APIENTRY InitGetHistogramParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogramParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogramParameterfv = extproc;

	glGetHistogramParameterfv(target, pname, params);
}

static void APIENTRY InitGetHistogramParameteriv (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogramParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogramParameteriv = extproc;

	glGetHistogramParameteriv(target, pname, params);
}

static void APIENTRY InitGetMinmax (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmax");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmax = extproc;

	glGetMinmax(target, reset, format, type, values);
}

static void APIENTRY InitGetMinmaxParameterfv (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmaxParameterfv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmaxParameterfv = extproc;

	glGetMinmaxParameterfv(target, pname, params);
}

static void APIENTRY InitGetMinmaxParameteriv (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmaxParameteriv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmaxParameteriv = extproc;

	glGetMinmaxParameteriv(target, pname, params);
}

static void APIENTRY InitHistogram (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glHistogram");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glHistogram = extproc;

	glHistogram(target, width, internalformat, sink);
}

static void APIENTRY InitMinmax (GLenum target, GLenum internalformat, GLboolean sink)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMinmax");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMinmax = extproc;

	glMinmax(target, internalformat, sink);
}

static void APIENTRY InitResetHistogram (GLenum target)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glResetHistogram");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glResetHistogram = extproc;

	glResetHistogram(target);
}

static void APIENTRY InitResetMinmax (GLenum target)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glResetMinmax");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glResetMinmax = extproc;

	glResetMinmax(target);
}

static void APIENTRY InitTexImage3D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexImage3D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexImage3D = extproc;

	glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static void APIENTRY InitTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexSubImage3D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexSubImage3D = extproc;

	glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

static void APIENTRY InitCopyTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexSubImage3D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexSubImage3D = extproc;

	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void APIENTRY InitActiveTexture (GLenum texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glActiveTexture");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glActiveTexture = extproc;
	glActiveTexture(texture);
}

static void APIENTRY InitClientActiveTexture (GLenum texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glClientActiveTexture");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glClientActiveTexture = extproc;

	glClientActiveTexture(texture);
}

static void APIENTRY InitMultiTexCoord1d (GLenum target, GLdouble s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1d");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1d = extproc;

	glMultiTexCoord1d(target, s);
}

static void APIENTRY InitMultiTexCoord1dv (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1dv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1dv = extproc;

	glMultiTexCoord1dv(target, v);
}

static void APIENTRY InitMultiTexCoord1f (GLenum target, GLfloat s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1f");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1f = extproc;

	glMultiTexCoord1f(target, s);
}

static void APIENTRY InitMultiTexCoord1fv (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1fv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1fv = extproc;

	glMultiTexCoord1fv(target, v);
}

static void APIENTRY InitMultiTexCoord1i (GLenum target, GLint s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1i");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1i = extproc;

	glMultiTexCoord1i(target, s);
}

static void APIENTRY InitMultiTexCoord1iv (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1iv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1iv = extproc;

	glMultiTexCoord1iv(target, v);
}

static void APIENTRY InitMultiTexCoord1s (GLenum target, GLshort s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1s");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1s = extproc;

	glMultiTexCoord1s(target, s);
}

static void APIENTRY InitMultiTexCoord1sv (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1sv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1sv = extproc;

	glMultiTexCoord1sv(target, v);
}

static void APIENTRY InitMultiTexCoord2d (GLenum target, GLdouble s, GLdouble t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2d");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2d = extproc;

	glMultiTexCoord2d(target, s, t);
}

static void APIENTRY InitMultiTexCoord2dv (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2dv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2dv = extproc;

	glMultiTexCoord2dv(target, v);
}

static void APIENTRY InitMultiTexCoord2f (GLenum target, GLfloat s, GLfloat t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2f");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2f = extproc;

	glMultiTexCoord2f(target, s, t);
}

static void APIENTRY InitMultiTexCoord2fv (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2fv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2fv = extproc;

	glMultiTexCoord2fv(target, v);
}

static void APIENTRY InitMultiTexCoord2i (GLenum target, GLint s, GLint t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2i");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2i = extproc;

	glMultiTexCoord2i(target, s, t);
}

static void APIENTRY InitMultiTexCoord2iv (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2iv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2iv = extproc;

	glMultiTexCoord2iv(target, v);
}

static void APIENTRY InitMultiTexCoord2s (GLenum target, GLshort s, GLshort t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2s");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2s = extproc;

	glMultiTexCoord2s(target, s, t);
}

static void APIENTRY InitMultiTexCoord2sv (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2sv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2sv = extproc;

	glMultiTexCoord2sv(target, v);
}

static void APIENTRY InitMultiTexCoord3d (GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3d");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3d = extproc;

	glMultiTexCoord3d(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3dv (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3dv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3dv = extproc;

	glMultiTexCoord3dv(target, v);
}

static void APIENTRY InitMultiTexCoord3f (GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3f");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3f = extproc;

	glMultiTexCoord3f(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3fv (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3fv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3fv = extproc;

	glMultiTexCoord3fv(target, v);
}

static void APIENTRY InitMultiTexCoord3i (GLenum target, GLint s, GLint t, GLint r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3i");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3i = extproc;

	glMultiTexCoord3i(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3iv (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3iv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3iv = extproc;

	glMultiTexCoord3iv(target, v);
}

static void APIENTRY InitMultiTexCoord3s (GLenum target, GLshort s, GLshort t, GLshort r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3s");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3s = extproc;

	glMultiTexCoord3s(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3sv (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3sv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3sv = extproc;

	glMultiTexCoord3sv(target, v);
}

static void APIENTRY InitMultiTexCoord4d (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4d");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4d = extproc;

	glMultiTexCoord4d(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4dv (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4dv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4dv = extproc;

	glMultiTexCoord4dv(target, v);
}

static void APIENTRY InitMultiTexCoord4f (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4f");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4f = extproc;

	glMultiTexCoord4f(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4fv (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4fv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4fv = extproc;

	glMultiTexCoord4fv(target, v);
}

static void APIENTRY InitMultiTexCoord4i (GLenum target, GLint s, GLint t, GLint r, GLint q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4i");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4i = extproc;

	glMultiTexCoord4i(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4iv (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4iv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4iv = extproc;

	glMultiTexCoord4iv(target, v);
}

static void APIENTRY InitMultiTexCoord4s (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4s");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4s = extproc;

	glMultiTexCoord4s(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4sv (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4sv");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4sv = extproc;

	glMultiTexCoord4sv(target, v);
}

static void APIENTRY InitLoadTransposeMatrixf (const GLfloat *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadTransposeMatrixf");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadTransposeMatrixf = extproc;

	glLoadTransposeMatrixf(m);
}

static void APIENTRY InitLoadTransposeMatrixd (const GLdouble *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadTransposeMatrixd");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadTransposeMatrixd = extproc;

	glLoadTransposeMatrixd(m);
}

static void APIENTRY InitMultTransposeMatrixf (const GLfloat *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultTransposeMatrixf");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultTransposeMatrixf = extproc;

	glMultTransposeMatrixf(m);
}

static void APIENTRY InitMultTransposeMatrixd (const GLdouble *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultTransposeMatrixd");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultTransposeMatrixd = extproc;

	glMultTransposeMatrixd(m);
}

static void APIENTRY InitSampleCoverage (GLclampf value, GLboolean invert)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSampleCoverage");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSampleCoverage = extproc;

	glSampleCoverage(value, invert);
}

static void APIENTRY InitCompressedTexImage3D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage3D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage3D = extproc;

	glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

static void APIENTRY InitCompressedTexImage2D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage2D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage2D = extproc;

	glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

static void APIENTRY InitCompressedTexImage1D (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage1D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage1D = extproc;

	glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage3D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage3D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage3D = extproc;

	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage2D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage2D = extproc;

	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage1D");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage1D = extproc;

	glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

static void APIENTRY InitGetCompressedTexImage (GLenum target, GLint level, void *img)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCompressedTexImage");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCompressedTexImage = extproc;

	glGetCompressedTexImage(target, level, img);
}

static void APIENTRY InitActiveTextureARB (GLenum texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glActiveTextureARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glActiveTextureARB = extproc;

	glActiveTextureARB(texture);
}

static void APIENTRY InitClientActiveTextureARB (GLenum texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glClientActiveTextureARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glClientActiveTextureARB = extproc;

	glClientActiveTextureARB(texture);
}

static void APIENTRY InitMultiTexCoord1dARB (GLenum target, GLdouble s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1dARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1dARB = extproc;

	glMultiTexCoord1dARB(target, s);
}

static void APIENTRY InitMultiTexCoord1dvARB (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1dvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1dvARB = extproc;

	glMultiTexCoord1dvARB(target, v);
}

static void APIENTRY InitMultiTexCoord1fARB (GLenum target, GLfloat s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1fARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1fARB = extproc;

	glMultiTexCoord1fARB(target, s);
}

static void APIENTRY InitMultiTexCoord1fvARB (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1fvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1fvARB = extproc;

	glMultiTexCoord1fvARB(target, v);
}

static void APIENTRY InitMultiTexCoord1iARB (GLenum target, GLint s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1iARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1iARB = extproc;

	glMultiTexCoord1iARB(target, s);
}

static void APIENTRY InitMultiTexCoord1ivARB (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1ivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1ivARB = extproc;

	glMultiTexCoord1ivARB(target, v);
}

static void APIENTRY InitMultiTexCoord1sARB (GLenum target, GLshort s)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1sARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1sARB = extproc;

	glMultiTexCoord1sARB(target, s);
}

static void APIENTRY InitMultiTexCoord1svARB (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord1svARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord1svARB = extproc;

	glMultiTexCoord1svARB(target, v);
}

static void APIENTRY InitMultiTexCoord2dARB (GLenum target, GLdouble s, GLdouble t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2dARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2dARB = extproc;

	glMultiTexCoord2dARB(target, s, t);
}

static void APIENTRY InitMultiTexCoord2dvARB (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2dvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2dvARB = extproc;

	glMultiTexCoord2dvARB(target, v);
}

static void APIENTRY InitMultiTexCoord2fARB (GLenum target, GLfloat s, GLfloat t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2fARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2fARB = extproc;

	glMultiTexCoord2fARB(target, s, t);
}

static void APIENTRY InitMultiTexCoord2fvARB (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2fvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2fvARB = extproc;

	glMultiTexCoord2fvARB(target, v);
}

static void APIENTRY InitMultiTexCoord2iARB (GLenum target, GLint s, GLint t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2iARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2iARB = extproc;

	glMultiTexCoord2iARB(target, s, t);
}

static void APIENTRY InitMultiTexCoord2ivARB (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2ivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2ivARB = extproc;

	glMultiTexCoord2ivARB(target, v);
}

static void APIENTRY InitMultiTexCoord2sARB (GLenum target, GLshort s, GLshort t)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2sARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2sARB = extproc;

	glMultiTexCoord2sARB(target, s, t);
}

static void APIENTRY InitMultiTexCoord2svARB (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord2svARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord2svARB = extproc;

	glMultiTexCoord2svARB(target, v);
}

static void APIENTRY InitMultiTexCoord3dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3dARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3dARB = extproc;

	glMultiTexCoord3dARB(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3dvARB (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3dvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3dvARB = extproc;

	glMultiTexCoord3dvARB(target, v);
}

static void APIENTRY InitMultiTexCoord3fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3fARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3fARB = extproc;

	glMultiTexCoord3fARB(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3fvARB (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3fvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3fvARB = extproc;

	glMultiTexCoord3fvARB(target, v);
}

static void APIENTRY InitMultiTexCoord3iARB (GLenum target, GLint s, GLint t, GLint r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3iARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3iARB = extproc;

	glMultiTexCoord3iARB(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3ivARB (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3ivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3ivARB = extproc;

	glMultiTexCoord3ivARB(target, v);
}

static void APIENTRY InitMultiTexCoord3sARB (GLenum target, GLshort s, GLshort t, GLshort r)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3sARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3sARB = extproc;

	glMultiTexCoord3sARB(target, s, t, r);
}

static void APIENTRY InitMultiTexCoord3svARB (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord3svARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord3svARB = extproc;

	glMultiTexCoord3svARB(target, v);
}

static void APIENTRY InitMultiTexCoord4dARB (GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4dARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4dARB = extproc;

	glMultiTexCoord4dARB(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4dvARB (GLenum target, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4dvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4dvARB = extproc;

	glMultiTexCoord4dvARB(target, v);
}

static void APIENTRY InitMultiTexCoord4fARB (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4fARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4fARB = extproc;

	glMultiTexCoord4fARB(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4fvARB (GLenum target, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4fvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4fvARB = extproc;

	glMultiTexCoord4fvARB(target, v);
}

static void APIENTRY InitMultiTexCoord4iARB (GLenum target, GLint s, GLint t, GLint r, GLint q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4iARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4iARB = extproc;

	glMultiTexCoord4iARB(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4ivARB (GLenum target, const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4ivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4ivARB = extproc;

	glMultiTexCoord4ivARB(target, v);
}

static void APIENTRY InitMultiTexCoord4sARB (GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4sARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4sARB = extproc;

	glMultiTexCoord4sARB(target, s, t, r, q);
}

static void APIENTRY InitMultiTexCoord4svARB (GLenum target, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiTexCoord4svARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiTexCoord4svARB = extproc;

	glMultiTexCoord4svARB(target, v);
}

static void APIENTRY InitLoadTransposeMatrixfARB (const GLfloat *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadTransposeMatrixfARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadTransposeMatrixfARB = extproc;

	glLoadTransposeMatrixfARB(m);
}

static void APIENTRY InitLoadTransposeMatrixdARB (const GLdouble *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadTransposeMatrixdARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadTransposeMatrixdARB = extproc;

	glLoadTransposeMatrixdARB(m);
}

static void APIENTRY InitMultTransposeMatrixfARB (const GLfloat *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultTransposeMatrixfARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultTransposeMatrixfARB = extproc;

	glMultTransposeMatrixfARB(m);
}

static void APIENTRY InitMultTransposeMatrixdARB (const GLdouble *m)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultTransposeMatrixdARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultTransposeMatrixdARB = extproc;

	glMultTransposeMatrixdARB(m);
}

static void APIENTRY InitSampleCoverageARB (GLclampf value, GLboolean invert)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSampleCoverageARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSampleCoverageARB = extproc;

	glSampleCoverageARB(value, invert);
}

static void APIENTRY InitCompressedTexImage3DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage3DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage3DARB = extproc;

	glCompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data);
}

static void APIENTRY InitCompressedTexImage2DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage2DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage2DARB = extproc;

	glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);
}

static void APIENTRY InitCompressedTexImage1DARB (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexImage1DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexImage1DARB = extproc;

	glCompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage3DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage3DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage3DARB = extproc;

	glCompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage2DARB (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage2DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage2DARB = extproc;

	glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static void APIENTRY InitCompressedTexSubImage1DARB (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCompressedTexSubImage1DARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCompressedTexSubImage1DARB = extproc;

	glCompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data);
}

static void APIENTRY InitGetCompressedTexImageARB (GLenum target, GLint level, void *img)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCompressedTexImageARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCompressedTexImageARB = extproc;

	glGetCompressedTexImageARB(target, level, img);
}

static void APIENTRY InitWeightbvARB (GLint size, const GLbyte *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightbvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightbvARB = extproc;

	glWeightbvARB(size, weights);
}

static void APIENTRY InitWeightsvARB (GLint size, const GLshort *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightsvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightsvARB = extproc;

	glWeightsvARB(size, weights);
}

static void APIENTRY InitWeightivARB (GLint size, const GLint *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightivARB = extproc;

	glWeightivARB(size, weights);
}

static void APIENTRY InitWeightfvARB (GLint size, const GLfloat *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightfvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightfvARB = extproc;

	glWeightfvARB(size, weights);
}

static void APIENTRY InitWeightdvARB (GLint size, const GLdouble *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightdvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightdvARB = extproc;

	glWeightdvARB(size, weights);
}

static void APIENTRY InitWeightubvARB (GLint size, const GLubyte *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightubvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightubvARB = extproc;

	glWeightubvARB(size, weights);
}

static void APIENTRY InitWeightusvARB (GLint size, const GLushort *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightusvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightusvARB = extproc;

	glWeightusvARB(size, weights);
}

static void APIENTRY InitWeightuivARB (GLint size, const GLuint *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightuivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightuivARB = extproc;

	glWeightuivARB(size, weights);
}

static void APIENTRY InitWeightPointerARB (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWeightPointerARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWeightPointerARB = extproc;

	glWeightPointerARB(size, type, stride, pointer);
}

static void APIENTRY InitVertexBlendARB (GLint count)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexBlendARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexBlendARB = extproc;

	glVertexBlendARB(count);
}

static void APIENTRY InitCurrentPaletteMatrixARB (GLint index)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCurrentPaletteMatrixARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCurrentPaletteMatrixARB = extproc;

	glCurrentPaletteMatrixARB(index);
}

static void APIENTRY InitMatrixIndexubvARB (GLint size, const GLubyte *indices)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMatrixIndexubvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMatrixIndexubvARB = extproc;

	glMatrixIndexubvARB(size, indices);
}

static void APIENTRY InitMatrixIndexusvARB (GLint size, const GLushort *indices)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMatrixIndexusvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMatrixIndexusvARB = extproc;

	glMatrixIndexusvARB(size, indices);
}

static void APIENTRY InitMatrixIndexuivARB (GLint size, const GLuint *indices)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMatrixIndexuivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMatrixIndexuivARB = extproc;

	glMatrixIndexuivARB(size, indices);
}

static void APIENTRY InitMatrixIndexPointerARB (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMatrixIndexPointerARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMatrixIndexPointerARB = extproc;

	glMatrixIndexPointerARB(size, type, stride, pointer);
}

static void APIENTRY InitBlendColorEXT (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendColorEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendColorEXT = extproc;

	glBlendColorEXT(red, green, blue, alpha);
}

static void APIENTRY InitPolygonOffsetEXT (GLfloat factor, GLfloat bias)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPolygonOffsetEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPolygonOffsetEXT = extproc;

	glPolygonOffsetEXT(factor, bias);
}

static void APIENTRY InitTexImage3DEXT (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexImage3DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexImage3DEXT = extproc;

	glTexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static void APIENTRY InitTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexSubImage3DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexSubImage3DEXT = extproc;

	glTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

static void APIENTRY InitGetTexFilterFuncSGIS (GLenum target, GLenum filter, GLfloat *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetTexFilterFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetTexFilterFuncSGIS = extproc;

	glGetTexFilterFuncSGIS(target, filter, weights);
}

static void APIENTRY InitTexFilterFuncSGIS (GLenum target, GLenum filter, GLsizei n, const GLfloat *weights)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexFilterFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexFilterFuncSGIS = extproc;

	glTexFilterFuncSGIS(target, filter, n, weights);
}

static void APIENTRY InitTexSubImage1DEXT (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexSubImage1DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexSubImage1DEXT = extproc;

	glTexSubImage1DEXT(target, level, xoffset, width, format, type, pixels);
}

static void APIENTRY InitTexSubImage2DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexSubImage2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexSubImage2DEXT = extproc;

	glTexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

static void APIENTRY InitCopyTexImage1DEXT (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexImage1DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexImage1DEXT = extproc;

	glCopyTexImage1DEXT(target, level, internalformat, x, y, width, border);
}

static void APIENTRY InitCopyTexImage2DEXT (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexImage2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexImage2DEXT = extproc;

	glCopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border);
}

static void APIENTRY InitCopyTexSubImage1DEXT (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexSubImage1DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexSubImage1DEXT = extproc;

	glCopyTexSubImage1DEXT(target, level, xoffset, x, y, width);
}

static void APIENTRY InitCopyTexSubImage2DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexSubImage2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexSubImage2DEXT = extproc;

	glCopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height);
}

static void APIENTRY InitCopyTexSubImage3DEXT (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyTexSubImage3DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyTexSubImage3DEXT = extproc;

	glCopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void APIENTRY InitGetHistogramEXT (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogramEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogramEXT = extproc;

	glGetHistogramEXT(target, reset, format, type, values);
}

static void APIENTRY InitGetHistogramParameterfvEXT (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogramParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogramParameterfvEXT = extproc;

	glGetHistogramParameterfvEXT(target, pname, params);
}

static void APIENTRY InitGetHistogramParameterivEXT (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetHistogramParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetHistogramParameterivEXT = extproc;

	glGetHistogramParameterivEXT(target, pname, params);
}

static void APIENTRY InitGetMinmaxEXT (GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmaxEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmaxEXT = extproc;

	glGetMinmaxEXT(target, reset, format, type, values);
}

static void APIENTRY InitGetMinmaxParameterfvEXT (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmaxParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmaxParameterfvEXT = extproc;

	glGetMinmaxParameterfvEXT(target, pname, params);
}

static void APIENTRY InitGetMinmaxParameterivEXT (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMinmaxParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMinmaxParameterivEXT = extproc;

	glGetMinmaxParameterivEXT(target, pname, params);
}

static void APIENTRY InitHistogramEXT (GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glHistogramEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glHistogramEXT = extproc;

	glHistogramEXT(target, width, internalformat, sink);
}

static void APIENTRY InitMinmaxEXT (GLenum target, GLenum internalformat, GLboolean sink)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMinmaxEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMinmaxEXT = extproc;

	glMinmaxEXT(target, internalformat, sink);
}

static void APIENTRY InitResetHistogramEXT (GLenum target)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glResetHistogramEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glResetHistogramEXT = extproc;

	glResetHistogramEXT(target);
}

static void APIENTRY InitResetMinmaxEXT (GLenum target)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glResetMinmaxEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glResetMinmaxEXT = extproc;

	glResetMinmaxEXT(target);
}

static void APIENTRY InitConvolutionFilter1DEXT (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionFilter1DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionFilter1DEXT = extproc;

	glConvolutionFilter1DEXT(target, internalformat, width, format, type, image);
}

static void APIENTRY InitConvolutionFilter2DEXT (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionFilter2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionFilter2DEXT = extproc;

	glConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image);
}

static void APIENTRY InitConvolutionParameterfEXT (GLenum target, GLenum pname, GLfloat params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameterfEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameterfEXT = extproc;

	glConvolutionParameterfEXT(target, pname, params);
}

static void APIENTRY InitConvolutionParameterfvEXT (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameterfvEXT = extproc;

	glConvolutionParameterfvEXT(target, pname, params);
}

static void APIENTRY InitConvolutionParameteriEXT (GLenum target, GLenum pname, GLint params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameteriEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameteriEXT = extproc;

	glConvolutionParameteriEXT(target, pname, params);
}

static void APIENTRY InitConvolutionParameterivEXT (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glConvolutionParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glConvolutionParameterivEXT = extproc;

	glConvolutionParameterivEXT(target, pname, params);
}

static void APIENTRY InitCopyConvolutionFilter1DEXT (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyConvolutionFilter1DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyConvolutionFilter1DEXT = extproc;

	glCopyConvolutionFilter1DEXT(target, internalformat, x, y, width);
}

static void APIENTRY InitCopyConvolutionFilter2DEXT (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyConvolutionFilter2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyConvolutionFilter2DEXT = extproc;

	glCopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height);
}

static void APIENTRY InitGetConvolutionFilterEXT (GLenum target, GLenum format, GLenum type, GLvoid *image)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionFilterEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionFilterEXT = extproc;

	glGetConvolutionFilterEXT(target, format, type, image);
}

static void APIENTRY InitGetConvolutionParameterfvEXT (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionParameterfvEXT = extproc;

	glGetConvolutionParameterfvEXT(target, pname, params);
}

static void APIENTRY InitGetConvolutionParameterivEXT (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetConvolutionParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetConvolutionParameterivEXT = extproc;

	glGetConvolutionParameterivEXT(target, pname, params);
}

static void APIENTRY InitGetSeparableFilterEXT (GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetSeparableFilterEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetSeparableFilterEXT = extproc;

	glGetSeparableFilterEXT(target, format, type, row, column, span);
}

static void APIENTRY InitSeparableFilter2DEXT (GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSeparableFilter2DEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSeparableFilter2DEXT = extproc;

	glSeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column);
}

static void APIENTRY InitColorTableSGI (GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableSGI = extproc;

	glColorTableSGI(target, internalformat, width, format, type, table);
}

static void APIENTRY InitColorTableParameterfvSGI (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableParameterfvSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableParameterfvSGI = extproc;

	glColorTableParameterfvSGI(target, pname, params);
}

static void APIENTRY InitColorTableParameterivSGI (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableParameterivSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableParameterivSGI = extproc;

	glColorTableParameterivSGI(target, pname, params);
}

static void APIENTRY InitCopyColorTableSGI (GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyColorTableSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyColorTableSGI = extproc;

	glCopyColorTableSGI(target, internalformat, x, y, width);
}

static void APIENTRY InitGetColorTableSGI (GLenum target, GLenum format, GLenum type, GLvoid *table)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableSGI = extproc;

	glGetColorTableSGI(target, format, type, table);
}

static void APIENTRY InitGetColorTableParameterfvSGI (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameterfvSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameterfvSGI = extproc;

	glGetColorTableParameterfvSGI(target, pname, params);
}

static void APIENTRY InitGetColorTableParameterivSGI (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameterivSGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameterivSGI = extproc;

	glGetColorTableParameterivSGI(target, pname, params);
}

static void APIENTRY InitPixelTexGenSGIX (GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTexGenSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTexGenSGIX = extproc;

	glPixelTexGenSGIX(mode);
}

static void APIENTRY InitPixelTexGenParameteriSGIS (GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTexGenParameteriSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTexGenParameteriSGIS = extproc;

	glPixelTexGenParameteriSGIS(pname, param);
}

static void APIENTRY InitPixelTexGenParameterivSGIS (GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTexGenParameterivSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTexGenParameterivSGIS = extproc;

	glPixelTexGenParameterivSGIS(pname, params);
}

static void APIENTRY InitPixelTexGenParameterfSGIS (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTexGenParameterfSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTexGenParameterfSGIS = extproc;

	glPixelTexGenParameterfSGIS(pname, param);
}

static void APIENTRY InitPixelTexGenParameterfvSGIS (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTexGenParameterfvSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTexGenParameterfvSGIS = extproc;

	glPixelTexGenParameterfvSGIS(pname, params);
}

static void APIENTRY InitGetPixelTexGenParameterivSGIS (GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetPixelTexGenParameterivSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetPixelTexGenParameterivSGIS = extproc;

	glGetPixelTexGenParameterivSGIS(pname, params);
}

static void APIENTRY InitGetPixelTexGenParameterfvSGIS (GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetPixelTexGenParameterfvSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetPixelTexGenParameterfvSGIS = extproc;

	glGetPixelTexGenParameterfvSGIS(pname, params);
}

static void APIENTRY InitTexImage4DSGIS (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexImage4DSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexImage4DSGIS = extproc;

	glTexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels);
}

static void APIENTRY InitTexSubImage4DSGIS (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const GLvoid *pixels)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexSubImage4DSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexSubImage4DSGIS = extproc;

	glTexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels);
}

static GLboolean APIENTRY InitAreTexturesResidentEXT (GLsizei n, const GLuint *textures, GLboolean *residences)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glAreTexturesResidentEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glAreTexturesResidentEXT = extproc;

	return glAreTexturesResidentEXT(n, textures, residences);
}

static void APIENTRY InitBindTextureEXT (GLenum target, GLuint texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBindTextureEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBindTextureEXT = extproc;

	glBindTextureEXT(target, texture);
}

static void APIENTRY InitDeleteTexturesEXT (GLsizei n, const GLuint *textures)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeleteTexturesEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeleteTexturesEXT = extproc;

	glDeleteTexturesEXT(n, textures);
}

static void APIENTRY InitGenTexturesEXT (GLsizei n, GLuint *textures)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGenTexturesEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGenTexturesEXT = extproc;

	glGenTexturesEXT(n, textures);
}

static GLboolean APIENTRY InitIsTextureEXT (GLuint texture)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIsTextureEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glIsTextureEXT = extproc;

	return glIsTextureEXT(texture);
}

static void APIENTRY InitPrioritizeTexturesEXT (GLsizei n, const GLuint *textures, const GLclampf *priorities)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPrioritizeTexturesEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPrioritizeTexturesEXT = extproc;

	glPrioritizeTexturesEXT(n, textures, priorities);
}

static void APIENTRY InitDetailTexFuncSGIS (GLenum target, GLsizei n, const GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDetailTexFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDetailTexFuncSGIS = extproc;

	glDetailTexFuncSGIS(target, n, points);
}

static void APIENTRY InitGetDetailTexFuncSGIS (GLenum target, GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetDetailTexFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetDetailTexFuncSGIS = extproc;

	glGetDetailTexFuncSGIS(target, points);
}

static void APIENTRY InitSharpenTexFuncSGIS (GLenum target, GLsizei n, const GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSharpenTexFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSharpenTexFuncSGIS = extproc;

	glSharpenTexFuncSGIS(target, n, points);
}

static void APIENTRY InitGetSharpenTexFuncSGIS (GLenum target, GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetSharpenTexFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetSharpenTexFuncSGIS = extproc;

	glGetSharpenTexFuncSGIS(target, points);
}

static void APIENTRY InitSampleMaskSGIS (GLclampf value, GLboolean invert)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSampleMaskSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSampleMaskSGIS = extproc;

	glSampleMaskSGIS(value, invert);
}

static void APIENTRY InitSamplePatternSGIS (GLenum pattern)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSamplePatternSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSamplePatternSGIS = extproc;

	glSamplePatternSGIS(pattern);
}

static void APIENTRY InitArrayElementEXT (GLint i)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glArrayElementEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glArrayElementEXT = extproc;

	glArrayElementEXT(i);
}

static void APIENTRY InitColorPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorPointerEXT = extproc;

	glColorPointerEXT(size, type, stride, count, pointer);
}

static void APIENTRY InitDrawArraysEXT (GLenum mode, GLint first, GLsizei count)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDrawArraysEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDrawArraysEXT = extproc;

	glDrawArraysEXT(mode, first, count);
}

static void APIENTRY InitEdgeFlagPointerEXT (GLsizei stride, GLsizei count, const GLboolean *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glEdgeFlagPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glEdgeFlagPointerEXT = extproc;

	glEdgeFlagPointerEXT(stride, count, pointer);
}

static void APIENTRY InitGetPointervEXT (GLenum pname, GLvoid* *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetPointervEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetPointervEXT = extproc;

	glGetPointervEXT(pname, params);
}

static void APIENTRY InitIndexPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIndexPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glIndexPointerEXT = extproc;

	glIndexPointerEXT(type, stride, count, pointer);
}

static void APIENTRY InitNormalPointerEXT (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glNormalPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glNormalPointerEXT = extproc;

	glNormalPointerEXT(type, stride, count, pointer);
}

static void APIENTRY InitTexCoordPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoordPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoordPointerEXT = extproc;

	glTexCoordPointerEXT(size, type, stride, count, pointer);
}

static void APIENTRY InitVertexPointerEXT (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexPointerEXT = extproc;

	glVertexPointerEXT(size, type, stride, count, pointer);
}

static void APIENTRY InitBlendEquationEXT (GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendEquationEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendEquationEXT = extproc;

	glBlendEquationEXT(mode);
}

static void APIENTRY InitSpriteParameterfSGIX (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSpriteParameterfSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSpriteParameterfSGIX = extproc;

	glSpriteParameterfSGIX(pname, param);
}

static void APIENTRY InitSpriteParameterfvSGIX (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSpriteParameterfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSpriteParameterfvSGIX = extproc;

	glSpriteParameterfvSGIX(pname, params);
}

static void APIENTRY InitSpriteParameteriSGIX (GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSpriteParameteriSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSpriteParameteriSGIX = extproc;

	glSpriteParameteriSGIX(pname, param);
}

static void APIENTRY InitSpriteParameterivSGIX (GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSpriteParameterivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSpriteParameterivSGIX = extproc;

	glSpriteParameterivSGIX(pname, params);
}

static void APIENTRY InitPointParameterfARB (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfARB = extproc;

	glPointParameterfARB(pname, param);
}

static void APIENTRY InitPointParameterfvARB (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfvARB = extproc;

	glPointParameterfvARB(pname, params);
}

static void APIENTRY InitPointParameterfEXT (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfEXT = extproc;

	glPointParameterfEXT(pname, param);
}

static void APIENTRY InitPointParameterfvEXT (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfvEXT = extproc;

	glPointParameterfvEXT(pname, params);
}

static void APIENTRY InitPointParameterfSGIS (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfSGIS = extproc;

	glPointParameterfSGIS(pname, param);
}

static void APIENTRY InitPointParameterfvSGIS (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPointParameterfvSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPointParameterfvSGIS = extproc;

	glPointParameterfvSGIS(pname, params);
}

static GLint APIENTRY InitGetInstrumentsSGIX (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetInstrumentsSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glGetInstrumentsSGIX = extproc;

	return glGetInstrumentsSGIX();
}

static void APIENTRY InitInstrumentsBufferSGIX (GLsizei size, GLint *buffer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glInstrumentsBufferSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glInstrumentsBufferSGIX = extproc;

	glInstrumentsBufferSGIX(size, buffer);
}

static GLint APIENTRY InitPollInstrumentsSGIX (GLint *marker_p)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPollInstrumentsSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glPollInstrumentsSGIX = extproc;

	return glPollInstrumentsSGIX(marker_p);
}

static void APIENTRY InitReadInstrumentsSGIX (GLint marker)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReadInstrumentsSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReadInstrumentsSGIX = extproc;

	glReadInstrumentsSGIX(marker);
}

static void APIENTRY InitStartInstrumentsSGIX (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glStartInstrumentsSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glStartInstrumentsSGIX = extproc;

	glStartInstrumentsSGIX();
}

static void APIENTRY InitStopInstrumentsSGIX (GLint marker)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glStopInstrumentsSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glStopInstrumentsSGIX = extproc;

	glStopInstrumentsSGIX(marker);
}

static void APIENTRY InitFrameZoomSGIX (GLint factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFrameZoomSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFrameZoomSGIX = extproc;

	glFrameZoomSGIX(factor);
}

static void APIENTRY InitTagSampleBufferSGIX (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTagSampleBufferSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTagSampleBufferSGIX = extproc;

	glTagSampleBufferSGIX();
}

static void APIENTRY InitDeformationMap3dSGIX (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeformationMap3dSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeformationMap3dSGIX = extproc;

	glDeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
}

static void APIENTRY InitDeformationMap3fSGIX (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeformationMap3fSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeformationMap3fSGIX = extproc;

	glDeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
}

static void APIENTRY InitDeformSGIX (GLbitfield mask)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeformSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeformSGIX = extproc;

	glDeformSGIX(mask);
}

static void APIENTRY InitLoadIdentityDeformationMapSGIX (GLbitfield mask)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadIdentityDeformationMapSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadIdentityDeformationMapSGIX = extproc;

	glLoadIdentityDeformationMapSGIX(mask);
}

static void APIENTRY InitReferencePlaneSGIX (const GLdouble *equation)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReferencePlaneSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReferencePlaneSGIX = extproc;

	glReferencePlaneSGIX(equation);
}

static void APIENTRY InitFlushRasterSGIX (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFlushRasterSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFlushRasterSGIX = extproc;

	glFlushRasterSGIX();
}

static void APIENTRY InitFogFuncSGIS (GLsizei n, const GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogFuncSGIS = extproc;

	glFogFuncSGIS(n, points);
}

static void APIENTRY InitGetFogFuncSGIS (GLfloat *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFogFuncSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFogFuncSGIS = extproc;

	glGetFogFuncSGIS(points);
}

static void APIENTRY InitImageTransformParameteriHP (GLenum target, GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glImageTransformParameteriHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glImageTransformParameteriHP = extproc;

	glImageTransformParameteriHP(target, pname, param);
}

static void APIENTRY InitImageTransformParameterfHP (GLenum target, GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glImageTransformParameterfHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glImageTransformParameterfHP = extproc;

	glImageTransformParameterfHP(target, pname, param);
}

static void APIENTRY InitImageTransformParameterivHP (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glImageTransformParameterivHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glImageTransformParameterivHP = extproc;

	glImageTransformParameterivHP(target, pname, params);
}

static void APIENTRY InitImageTransformParameterfvHP (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glImageTransformParameterfvHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glImageTransformParameterfvHP = extproc;

	glImageTransformParameterfvHP(target, pname, params);
}

static void APIENTRY InitGetImageTransformParameterivHP (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetImageTransformParameterivHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetImageTransformParameterivHP = extproc;

	glGetImageTransformParameterivHP(target, pname, params);
}

static void APIENTRY InitGetImageTransformParameterfvHP (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetImageTransformParameterfvHP");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetImageTransformParameterfvHP = extproc;

	glGetImageTransformParameterfvHP(target, pname, params);
}

static void APIENTRY InitColorSubTableEXT (GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorSubTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorSubTableEXT = extproc;

	glColorSubTableEXT(target, start, count, format, type, data);
}

static void APIENTRY InitCopyColorSubTableEXT (GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCopyColorSubTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCopyColorSubTableEXT = extproc;

	glCopyColorSubTableEXT(target, start, x, y, width);
}

static void APIENTRY InitHintPGI (GLenum target, GLint mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glHintPGI");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glHintPGI = extproc;

	glHintPGI(target, mode);
}

static void APIENTRY InitColorTableEXT (GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid *table)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorTableEXT = extproc;

	glColorTableEXT(target, internalFormat, width, format, type, table);
}

static void APIENTRY InitGetColorTableEXT (GLenum target, GLenum format, GLenum type, GLvoid *data)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableEXT = extproc;

	glGetColorTableEXT(target, format, type, data);
}

static void APIENTRY InitGetColorTableParameterivEXT (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameterivEXT = extproc;

	glGetColorTableParameterivEXT(target, pname, params);
}

static void APIENTRY InitGetColorTableParameterfvEXT (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetColorTableParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetColorTableParameterfvEXT = extproc;

	glGetColorTableParameterfvEXT(target, pname, params);
}

static void APIENTRY InitGetListParameterfvSGIX (GLuint list, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetListParameterfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetListParameterfvSGIX = extproc;

	glGetListParameterfvSGIX(list, pname, params);
}

static void APIENTRY InitGetListParameterivSGIX (GLuint list, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetListParameterivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetListParameterivSGIX = extproc;

	glGetListParameterivSGIX(list, pname, params);
}

static void APIENTRY InitListParameterfSGIX (GLuint list, GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glListParameterfSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glListParameterfSGIX = extproc;

	glListParameterfSGIX(list, pname, param);
}

static void APIENTRY InitListParameterfvSGIX (GLuint list, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glListParameterfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glListParameterfvSGIX = extproc;

	glListParameterfvSGIX(list, pname, params);
}

static void APIENTRY InitListParameteriSGIX (GLuint list, GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glListParameteriSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glListParameteriSGIX = extproc;

	glListParameteriSGIX(list, pname, param);
}

static void APIENTRY InitListParameterivSGIX (GLuint list, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glListParameterivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glListParameterivSGIX = extproc;

	glListParameterivSGIX(list, pname, params);
}

static void APIENTRY InitIndexMaterialEXT (GLenum face, GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIndexMaterialEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glIndexMaterialEXT = extproc;

	glIndexMaterialEXT(face, mode);
}

static void APIENTRY InitIndexFuncEXT (GLenum func, GLclampf ref)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIndexFuncEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glIndexFuncEXT = extproc;

	glIndexFuncEXT(func, ref);
}

static void APIENTRY InitLockArraysEXT (GLint first, GLsizei count)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLockArraysEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLockArraysEXT = extproc;

	glLockArraysEXT(first, count);
}

static void APIENTRY InitUnlockArraysEXT (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glUnlockArraysEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glUnlockArraysEXT = extproc;

	glUnlockArraysEXT();
}

static void APIENTRY InitCullParameterdvEXT (GLenum pname, GLdouble *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCullParameterdvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCullParameterdvEXT = extproc;

	glCullParameterdvEXT(pname, params);
}

static void APIENTRY InitCullParameterfvEXT (GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCullParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCullParameterfvEXT = extproc;

	glCullParameterfvEXT(pname, params);
}

static void APIENTRY InitFragmentColorMaterialSGIX (GLenum face, GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentColorMaterialSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentColorMaterialSGIX = extproc;

	glFragmentColorMaterialSGIX(face, mode);
}

static void APIENTRY InitFragmentLightfSGIX (GLenum light, GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightfSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightfSGIX = extproc;

	glFragmentLightfSGIX(light, pname, param);
}

static void APIENTRY InitFragmentLightfvSGIX (GLenum light, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightfvSGIX = extproc;

	glFragmentLightfvSGIX(light, pname, params);
}

static void APIENTRY InitFragmentLightiSGIX (GLenum light, GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightiSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightiSGIX = extproc;

	glFragmentLightiSGIX(light, pname, param);
}

static void APIENTRY InitFragmentLightivSGIX (GLenum light, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightivSGIX = extproc;

	glFragmentLightivSGIX(light, pname, params);
}

static void APIENTRY InitFragmentLightModelfSGIX (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightModelfSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightModelfSGIX = extproc;

	glFragmentLightModelfSGIX(pname, param);
}

static void APIENTRY InitFragmentLightModelfvSGIX (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightModelfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightModelfvSGIX = extproc;

	glFragmentLightModelfvSGIX(pname, params);
}

static void APIENTRY InitFragmentLightModeliSGIX (GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightModeliSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightModeliSGIX = extproc;

	glFragmentLightModeliSGIX(pname, param);
}

static void APIENTRY InitFragmentLightModelivSGIX (GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentLightModelivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentLightModelivSGIX = extproc;

	glFragmentLightModelivSGIX(pname, params);
}

static void APIENTRY InitFragmentMaterialfSGIX (GLenum face, GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentMaterialfSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentMaterialfSGIX = extproc;

	glFragmentMaterialfSGIX(face, pname, param);
}

static void APIENTRY InitFragmentMaterialfvSGIX (GLenum face, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentMaterialfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentMaterialfvSGIX = extproc;

	glFragmentMaterialfvSGIX(face, pname, params);
}

static void APIENTRY InitFragmentMaterialiSGIX (GLenum face, GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentMaterialiSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentMaterialiSGIX = extproc;

	glFragmentMaterialiSGIX(face, pname, param);
}

static void APIENTRY InitFragmentMaterialivSGIX (GLenum face, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFragmentMaterialivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFragmentMaterialivSGIX = extproc;

	glFragmentMaterialivSGIX(face, pname, params);
}

static void APIENTRY InitGetFragmentLightfvSGIX (GLenum light, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFragmentLightfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFragmentLightfvSGIX = extproc;

	glGetFragmentLightfvSGIX(light, pname, params);
}

static void APIENTRY InitGetFragmentLightivSGIX (GLenum light, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFragmentLightivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFragmentLightivSGIX = extproc;

	glGetFragmentLightivSGIX(light, pname, params);
}

static void APIENTRY InitGetFragmentMaterialfvSGIX (GLenum face, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFragmentMaterialfvSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFragmentMaterialfvSGIX = extproc;

	glGetFragmentMaterialfvSGIX(face, pname, params);
}

static void APIENTRY InitGetFragmentMaterialivSGIX (GLenum face, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFragmentMaterialivSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFragmentMaterialivSGIX = extproc;

	glGetFragmentMaterialivSGIX(face, pname, params);
}

static void APIENTRY InitLightEnviSGIX (GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLightEnviSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLightEnviSGIX = extproc;

	glLightEnviSGIX(pname, param);
}

static void APIENTRY InitDrawRangeElementsEXT (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDrawRangeElementsEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDrawRangeElementsEXT = extproc;

	glDrawRangeElementsEXT(mode, start, end, count, type, indices);
}

static void APIENTRY InitApplyTextureEXT (GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glApplyTextureEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glApplyTextureEXT = extproc;

	glApplyTextureEXT(mode);
}

static void APIENTRY InitTextureLightEXT (GLenum pname)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTextureLightEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTextureLightEXT = extproc;

	glTextureLightEXT(pname);
}

static void APIENTRY InitTextureMaterialEXT (GLenum face, GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTextureMaterialEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTextureMaterialEXT = extproc;

	glTextureMaterialEXT(face, mode);
}

static void APIENTRY InitAsyncMarkerSGIX (GLuint marker)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glAsyncMarkerSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glAsyncMarkerSGIX = extproc;

	glAsyncMarkerSGIX(marker);
}

static GLint APIENTRY InitFinishAsyncSGIX (GLuint *markerp)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFinishAsyncSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glFinishAsyncSGIX = extproc;

	return glFinishAsyncSGIX(markerp);
}

static GLint APIENTRY InitPollAsyncSGIX (GLuint *markerp)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPollAsyncSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glPollAsyncSGIX = extproc;

	return glPollAsyncSGIX(markerp);
}

static GLuint APIENTRY InitGenAsyncMarkersSGIX (GLsizei range)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGenAsyncMarkersSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glGenAsyncMarkersSGIX = extproc;

	return glGenAsyncMarkersSGIX(range);
}

static void APIENTRY InitDeleteAsyncMarkersSGIX (GLuint marker, GLsizei range)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeleteAsyncMarkersSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeleteAsyncMarkersSGIX = extproc;

	glDeleteAsyncMarkersSGIX(marker, range);
}

static GLboolean APIENTRY InitIsAsyncMarkerSGIX (GLuint marker)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIsAsyncMarkerSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glIsAsyncMarkerSGIX = extproc;

	return glIsAsyncMarkerSGIX(marker);
}

static void APIENTRY InitVertexPointervINTEL (GLint size, GLenum type, const GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexPointervINTEL");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexPointervINTEL = extproc;

	glVertexPointervINTEL(size, type, pointer);
}

static void APIENTRY InitNormalPointervINTEL (GLenum type, const GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glNormalPointervINTEL");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glNormalPointervINTEL = extproc;

	glNormalPointervINTEL(type, pointer);
}

static void APIENTRY InitColorPointervINTEL (GLint size, GLenum type, const GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorPointervINTEL");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorPointervINTEL = extproc;

	glColorPointervINTEL(size, type, pointer);
}

static void APIENTRY InitTexCoordPointervINTEL (GLint size, GLenum type, const GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoordPointervINTEL");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoordPointervINTEL = extproc;

	glTexCoordPointervINTEL(size, type, pointer);
}

static void APIENTRY InitPixelTransformParameteriEXT (GLenum target, GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTransformParameteriEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTransformParameteriEXT = extproc;

	glPixelTransformParameteriEXT(target, pname, param);
}

static void APIENTRY InitPixelTransformParameterfEXT (GLenum target, GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTransformParameterfEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTransformParameterfEXT = extproc;

	glPixelTransformParameterfEXT(target, pname, param);
}

static void APIENTRY InitPixelTransformParameterivEXT (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTransformParameterivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTransformParameterivEXT = extproc;

	glPixelTransformParameterivEXT(target, pname, params);
}

static void APIENTRY InitPixelTransformParameterfvEXT (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glPixelTransformParameterfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glPixelTransformParameterfvEXT = extproc;

	glPixelTransformParameterfvEXT(target, pname, params);
}

static void APIENTRY InitSecondaryColor3bEXT (GLbyte red, GLbyte green, GLbyte blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3bEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3bEXT = extproc;

	glSecondaryColor3bEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3bvEXT (const GLbyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3bvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3bvEXT = extproc;

	glSecondaryColor3bvEXT(v);
}

static void APIENTRY InitSecondaryColor3dEXT (GLdouble red, GLdouble green, GLdouble blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3dEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3dEXT = extproc;

	glSecondaryColor3dEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3dvEXT (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3dvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3dvEXT = extproc;

	glSecondaryColor3dvEXT(v);
}

static void APIENTRY InitSecondaryColor3fEXT (GLfloat red, GLfloat green, GLfloat blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3fEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3fEXT = extproc;

	glSecondaryColor3fEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3fvEXT (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3fvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3fvEXT = extproc;

	glSecondaryColor3fvEXT(v);
}

static void APIENTRY InitSecondaryColor3iEXT (GLint red, GLint green, GLint blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3iEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3iEXT = extproc;

	glSecondaryColor3iEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3ivEXT (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3ivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3ivEXT = extproc;

	glSecondaryColor3ivEXT(v);
}

static void APIENTRY InitSecondaryColor3sEXT (GLshort red, GLshort green, GLshort blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3sEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3sEXT = extproc;

	glSecondaryColor3sEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3svEXT (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3svEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3svEXT = extproc;

	glSecondaryColor3svEXT(v);
}

static void APIENTRY InitSecondaryColor3ubEXT (GLubyte red, GLubyte green, GLubyte blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3ubEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3ubEXT = extproc;

	glSecondaryColor3ubEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3ubvEXT (const GLubyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3ubvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3ubvEXT = extproc;

	glSecondaryColor3ubvEXT(v);
}

static void APIENTRY InitSecondaryColor3uiEXT (GLuint red, GLuint green, GLuint blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3uiEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3uiEXT = extproc;

	glSecondaryColor3uiEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3uivEXT (const GLuint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3uivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3uivEXT = extproc;

	glSecondaryColor3uivEXT(v);
}

static void APIENTRY InitSecondaryColor3usEXT (GLushort red, GLushort green, GLushort blue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3usEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3usEXT = extproc;

	glSecondaryColor3usEXT(red, green, blue);
}

static void APIENTRY InitSecondaryColor3usvEXT (const GLushort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColor3usvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColor3usvEXT = extproc;

	glSecondaryColor3usvEXT(v);
}

static void APIENTRY InitSecondaryColorPointerEXT (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColorPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColorPointerEXT = extproc;

	glSecondaryColorPointerEXT(size, type, stride, pointer);
}

static void APIENTRY InitTextureNormalEXT (GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTextureNormalEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTextureNormalEXT = extproc;

	glTextureNormalEXT(mode);
}

static void APIENTRY InitMultiDrawArraysEXT (GLenum mode, GLint *first, GLsizei *count, GLsizei primcount)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiDrawArraysEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiDrawArraysEXT = extproc;

	glMultiDrawArraysEXT(mode, first, count, primcount);
}

static void APIENTRY InitMultiDrawElementsEXT (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiDrawElementsEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiDrawElementsEXT = extproc;

	glMultiDrawElementsEXT(mode, count, type, indices, primcount);
}

static void APIENTRY InitFogCoordfEXT (GLfloat coord)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoordfEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoordfEXT = extproc;

	glFogCoordfEXT(coord);
}

static void APIENTRY InitFogCoordfvEXT (const GLfloat *coord)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoordfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoordfvEXT = extproc;

	glFogCoordfvEXT(coord);
}

static void APIENTRY InitFogCoorddEXT (GLdouble coord)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoorddEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoorddEXT = extproc;

	glFogCoorddEXT(coord);
}

static void APIENTRY InitFogCoorddvEXT (const GLdouble *coord)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoorddvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoorddvEXT = extproc;

	glFogCoorddvEXT(coord);
}

static void APIENTRY InitFogCoordPointerEXT (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoordPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoordPointerEXT = extproc;

	glFogCoordPointerEXT(type, stride, pointer);
}

static void APIENTRY InitTangent3bEXT (GLbyte tx, GLbyte ty, GLbyte tz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3bEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3bEXT = extproc;

	glTangent3bEXT(tx, ty, tz);
}

static void APIENTRY InitTangent3bvEXT (const GLbyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3bvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3bvEXT = extproc;

	glTangent3bvEXT(v);
}

static void APIENTRY InitTangent3dEXT (GLdouble tx, GLdouble ty, GLdouble tz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3dEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3dEXT = extproc;

	glTangent3dEXT(tx, ty, tz);
}

static void APIENTRY InitTangent3dvEXT (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3dvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3dvEXT = extproc;

	glTangent3dvEXT(v);
}

static void APIENTRY InitTangent3fEXT (GLfloat tx, GLfloat ty, GLfloat tz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3fEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3fEXT = extproc;

	glTangent3fEXT(tx, ty, tz);
}

static void APIENTRY InitTangent3fvEXT (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3fvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3fvEXT = extproc;

	glTangent3fvEXT(v);
}

static void APIENTRY InitTangent3iEXT (GLint tx, GLint ty, GLint tz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3iEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3iEXT = extproc;

	glTangent3iEXT(tx, ty, tz);
}

static void APIENTRY InitTangent3ivEXT (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3ivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3ivEXT = extproc;

	glTangent3ivEXT(v);
}

static void APIENTRY InitTangent3sEXT (GLshort tx, GLshort ty, GLshort tz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3sEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3sEXT = extproc;

	glTangent3sEXT(tx, ty, tz);
}

static void APIENTRY InitTangent3svEXT (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangent3svEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangent3svEXT = extproc;

	glTangent3svEXT(v);
}

static void APIENTRY InitBinormal3bEXT (GLbyte bx, GLbyte by, GLbyte bz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3bEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3bEXT = extproc;

	glBinormal3bEXT(bx, by, bz);
}

static void APIENTRY InitBinormal3bvEXT (const GLbyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3bvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3bvEXT = extproc;

	glBinormal3bvEXT(v);
}

static void APIENTRY InitBinormal3dEXT (GLdouble bx, GLdouble by, GLdouble bz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3dEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3dEXT = extproc;

	glBinormal3dEXT(bx, by, bz);
}

static void APIENTRY InitBinormal3dvEXT (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3dvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3dvEXT = extproc;

	glBinormal3dvEXT(v);
}

static void APIENTRY InitBinormal3fEXT (GLfloat bx, GLfloat by, GLfloat bz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3fEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3fEXT = extproc;

	glBinormal3fEXT(bx, by, bz);
}

static void APIENTRY InitBinormal3fvEXT (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3fvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3fvEXT = extproc;

	glBinormal3fvEXT(v);
}

static void APIENTRY InitBinormal3iEXT (GLint bx, GLint by, GLint bz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3iEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3iEXT = extproc;

	glBinormal3iEXT(bx, by, bz);
}

static void APIENTRY InitBinormal3ivEXT (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3ivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3ivEXT = extproc;

	glBinormal3ivEXT(v);
}

static void APIENTRY InitBinormal3sEXT (GLshort bx, GLshort by, GLshort bz)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3sEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3sEXT = extproc;

	glBinormal3sEXT(bx, by, bz);
}

static void APIENTRY InitBinormal3svEXT (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormal3svEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormal3svEXT = extproc;

	glBinormal3svEXT(v);
}

static void APIENTRY InitTangentPointerEXT (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTangentPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTangentPointerEXT = extproc;

	glTangentPointerEXT(type, stride, pointer);
}

static void APIENTRY InitBinormalPointerEXT (GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBinormalPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBinormalPointerEXT = extproc;

	glBinormalPointerEXT(type, stride, pointer);
}

static void APIENTRY InitFinishTextureSUNX (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFinishTextureSUNX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFinishTextureSUNX = extproc;

	glFinishTextureSUNX();
}

static void APIENTRY InitGlobalAlphaFactorbSUN (GLbyte factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactorbSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactorbSUN = extproc;

	glGlobalAlphaFactorbSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactorsSUN (GLshort factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactorsSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactorsSUN = extproc;

	glGlobalAlphaFactorsSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactoriSUN (GLint factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactoriSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactoriSUN = extproc;

	glGlobalAlphaFactoriSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactorfSUN (GLfloat factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactorfSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactorfSUN = extproc;

	glGlobalAlphaFactorfSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactordSUN (GLdouble factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactordSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactordSUN = extproc;

	glGlobalAlphaFactordSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactorubSUN (GLubyte factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactorubSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactorubSUN = extproc;

	glGlobalAlphaFactorubSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactorusSUN (GLushort factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactorusSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactorusSUN = extproc;

	glGlobalAlphaFactorusSUN(factor);
}

static void APIENTRY InitGlobalAlphaFactoruiSUN (GLuint factor)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGlobalAlphaFactoruiSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGlobalAlphaFactoruiSUN = extproc;

	glGlobalAlphaFactoruiSUN(factor);
}

static void APIENTRY InitReplacementCodeuiSUN (GLuint code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiSUN = extproc;

	glReplacementCodeuiSUN(code);
}

static void APIENTRY InitReplacementCodeusSUN (GLushort code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeusSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeusSUN = extproc;

	glReplacementCodeusSUN(code);
}

static void APIENTRY InitReplacementCodeubSUN (GLubyte code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeubSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeubSUN = extproc;

	glReplacementCodeubSUN(code);
}

static void APIENTRY InitReplacementCodeuivSUN (const GLuint *code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuivSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuivSUN = extproc;

	glReplacementCodeuivSUN(code);
}

static void APIENTRY InitReplacementCodeusvSUN (const GLushort *code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeusvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeusvSUN = extproc;

	glReplacementCodeusvSUN(code);
}

static void APIENTRY InitReplacementCodeubvSUN (const GLubyte *code)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeubvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeubvSUN = extproc;

	glReplacementCodeubvSUN(code);
}

static void APIENTRY InitReplacementCodePointerSUN (GLenum type, GLsizei stride, const GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodePointerSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodePointerSUN = extproc;

	glReplacementCodePointerSUN(type, stride, pointer);
}

static void APIENTRY InitColor4ubVertex2fSUN (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4ubVertex2fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4ubVertex2fSUN = extproc;

	glColor4ubVertex2fSUN(r, g, b, a, x, y);
}

static void APIENTRY InitColor4ubVertex2fvSUN (const GLubyte *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4ubVertex2fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4ubVertex2fvSUN = extproc;

	glColor4ubVertex2fvSUN(c, v);
}

static void APIENTRY InitColor4ubVertex3fSUN (GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4ubVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4ubVertex3fSUN = extproc;

	glColor4ubVertex3fSUN(r, g, b, a, x, y, z);
}

static void APIENTRY InitColor4ubVertex3fvSUN (const GLubyte *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4ubVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4ubVertex3fvSUN = extproc;

	glColor4ubVertex3fvSUN(c, v);
}

static void APIENTRY InitColor3fVertex3fSUN (GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor3fVertex3fSUN = extproc;

	glColor3fVertex3fSUN(r, g, b, x, y, z);
}

static void APIENTRY InitColor3fVertex3fvSUN (const GLfloat *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor3fVertex3fvSUN = extproc;

	glColor3fVertex3fvSUN(c, v);
}

static void APIENTRY InitNormal3fVertex3fSUN (GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glNormal3fVertex3fSUN = extproc;

	glNormal3fVertex3fSUN(nx, ny, nz, x, y, z);
}

static void APIENTRY InitNormal3fVertex3fvSUN (const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glNormal3fVertex3fvSUN = extproc;

	glNormal3fVertex3fvSUN(n, v);
}

static void APIENTRY InitColor4fNormal3fVertex3fSUN (GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4fNormal3fVertex3fSUN = extproc;

	glColor4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z);
}

static void APIENTRY InitColor4fNormal3fVertex3fvSUN (const GLfloat *c, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColor4fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColor4fNormal3fVertex3fvSUN = extproc;

	glColor4fNormal3fVertex3fvSUN(c, n, v);
}

static void APIENTRY InitTexCoord2fVertex3fSUN (GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fVertex3fSUN = extproc;

	glTexCoord2fVertex3fSUN(s, t, x, y, z);
}

static void APIENTRY InitTexCoord2fVertex3fvSUN (const GLfloat *tc, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fVertex3fvSUN = extproc;

	glTexCoord2fVertex3fvSUN(tc, v);
}

static void APIENTRY InitTexCoord4fVertex4fSUN (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord4fVertex4fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord4fVertex4fSUN = extproc;

	glTexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w);
}

static void APIENTRY InitTexCoord4fVertex4fvSUN (const GLfloat *tc, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord4fVertex4fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord4fVertex4fvSUN = extproc;

	glTexCoord4fVertex4fvSUN(tc, v);
}

static void APIENTRY InitTexCoord2fColor4ubVertex3fSUN (GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor4ubVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor4ubVertex3fSUN = extproc;

	glTexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z);
}

static void APIENTRY InitTexCoord2fColor4ubVertex3fvSUN (const GLfloat *tc, const GLubyte *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor4ubVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor4ubVertex3fvSUN = extproc;

	glTexCoord2fColor4ubVertex3fvSUN(tc, c, v);
}

static void APIENTRY InitTexCoord2fColor3fVertex3fSUN (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor3fVertex3fSUN = extproc;

	glTexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z);
}

static void APIENTRY InitTexCoord2fColor3fVertex3fvSUN (const GLfloat *tc, const GLfloat *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor3fVertex3fvSUN = extproc;

	glTexCoord2fColor3fVertex3fvSUN(tc, c, v);
}

static void APIENTRY InitTexCoord2fNormal3fVertex3fSUN (GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fNormal3fVertex3fSUN = extproc;

	glTexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z);
}

static void APIENTRY InitTexCoord2fNormal3fVertex3fvSUN (const GLfloat *tc, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fNormal3fVertex3fvSUN = extproc;

	glTexCoord2fNormal3fVertex3fvSUN(tc, n, v);
}

static void APIENTRY InitTexCoord2fColor4fNormal3fVertex3fSUN (GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor4fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor4fNormal3fVertex3fSUN = extproc;

	glTexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z);
}

static void APIENTRY InitTexCoord2fColor4fNormal3fVertex3fvSUN (const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord2fColor4fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord2fColor4fNormal3fVertex3fvSUN = extproc;

	glTexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v);
}

static void APIENTRY InitTexCoord4fColor4fNormal3fVertex4fSUN (GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord4fColor4fNormal3fVertex4fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord4fColor4fNormal3fVertex4fSUN = extproc;

	glTexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w);
}

static void APIENTRY InitTexCoord4fColor4fNormal3fVertex4fvSUN (const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoord4fColor4fNormal3fVertex4fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoord4fColor4fNormal3fVertex4fvSUN = extproc;

	glTexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v);
}

static void APIENTRY InitReplacementCodeuiVertex3fSUN (GLenum rc, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiVertex3fSUN = extproc;

	glReplacementCodeuiVertex3fSUN(rc, x, y, z);
}

static void APIENTRY InitReplacementCodeuiVertex3fvSUN (const GLenum *rc, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiVertex3fvSUN = extproc;

	glReplacementCodeuiVertex3fvSUN(rc, v);
}

static void APIENTRY InitReplacementCodeuiColor4ubVertex3fSUN (GLenum rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor4ubVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor4ubVertex3fSUN = extproc;

	glReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z);
}

static void APIENTRY InitReplacementCodeuiColor4ubVertex3fvSUN (const GLenum *rc, const GLubyte *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor4ubVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor4ubVertex3fvSUN = extproc;

	glReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v);
}

static void APIENTRY InitReplacementCodeuiColor3fVertex3fSUN (GLenum rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor3fVertex3fSUN = extproc;

	glReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z);
}

static void APIENTRY InitReplacementCodeuiColor3fVertex3fvSUN (const GLenum *rc, const GLfloat *c, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor3fVertex3fvSUN = extproc;

	glReplacementCodeuiColor3fVertex3fvSUN(rc, c, v);
}

static void APIENTRY InitReplacementCodeuiNormal3fVertex3fSUN (GLenum rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiNormal3fVertex3fSUN = extproc;

	glReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z);
}

static void APIENTRY InitReplacementCodeuiNormal3fVertex3fvSUN (const GLenum *rc, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiNormal3fVertex3fvSUN = extproc;

	glReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v);
}

static void APIENTRY InitReplacementCodeuiColor4fNormal3fVertex3fSUN (GLenum rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor4fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor4fNormal3fVertex3fSUN = extproc;

	glReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z);
}

static void APIENTRY InitReplacementCodeuiColor4fNormal3fVertex3fvSUN (const GLenum *rc, const GLfloat *c, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiColor4fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiColor4fNormal3fVertex3fvSUN = extproc;

	glReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fVertex3fSUN (GLenum rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fVertex3fSUN = extproc;

	glReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fVertex3fvSUN (const GLenum *rc, const GLfloat *tc, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fVertex3fvSUN = extproc;

	glReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fNormal3fVertex3fSUN (GLenum rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN = extproc;

	glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN (const GLenum *rc, const GLfloat *tc, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN = extproc;

	glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN (GLenum rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN = extproc;

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z);
}

static void APIENTRY InitReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN (const GLenum *rc, const GLfloat *tc, const GLfloat *c, const GLfloat *n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN = extproc;

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v);
}

static void APIENTRY InitBlendFuncSeparateEXT (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendFuncSeparateEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendFuncSeparateEXT = extproc;

	glBlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

static void APIENTRY InitBlendFuncSeparateINGR (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBlendFuncSeparateINGR");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBlendFuncSeparateINGR = extproc;

	glBlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

static void APIENTRY InitVertexWeightfEXT (GLfloat weight)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexWeightfEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexWeightfEXT = extproc;

	glVertexWeightfEXT(weight);
}

static void APIENTRY InitVertexWeightfvEXT (const GLfloat *weight)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexWeightfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexWeightfvEXT = extproc;

	glVertexWeightfvEXT(weight);
}

static void APIENTRY InitVertexWeightPointerEXT (GLsizei size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexWeightPointerEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexWeightPointerEXT = extproc;

	glVertexWeightPointerEXT(size, type, stride, pointer);
}

static void APIENTRY InitFlushVertexArrayRangeNV (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFlushVertexArrayRangeNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFlushVertexArrayRangeNV = extproc;

	glFlushVertexArrayRangeNV();
}

static void APIENTRY InitVertexArrayRangeNV (GLsizei length, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexArrayRangeNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexArrayRangeNV = extproc;

	glVertexArrayRangeNV(length, pointer);
}

static void APIENTRY InitCombinerParameterfvNV (GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerParameterfvNV = extproc;

	glCombinerParameterfvNV(pname, params);
}

static void APIENTRY InitCombinerParameterfNV (GLenum pname, GLfloat param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerParameterfNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerParameterfNV = extproc;

	glCombinerParameterfNV(pname, param);
}

static void APIENTRY InitCombinerParameterivNV (GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerParameterivNV = extproc;

	glCombinerParameterivNV(pname, params);
}

static void APIENTRY InitCombinerParameteriNV (GLenum pname, GLint param)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerParameteriNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerParameteriNV = extproc;

	glCombinerParameteriNV(pname, param);
}

static void APIENTRY InitCombinerInputNV (GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerInputNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerInputNV = extproc;

	glCombinerInputNV(stage, portion, variable, input, mapping, componentUsage);
}

static void APIENTRY InitCombinerOutputNV (GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerOutputNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerOutputNV = extproc;

	glCombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum);
}

static void APIENTRY InitFinalCombinerInputNV (GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFinalCombinerInputNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFinalCombinerInputNV = extproc;

	glFinalCombinerInputNV(variable, input, mapping, componentUsage);
}

static void APIENTRY InitGetCombinerInputParameterfvNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCombinerInputParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCombinerInputParameterfvNV = extproc;

	glGetCombinerInputParameterfvNV(stage, portion, variable, pname, params);
}

static void APIENTRY InitGetCombinerInputParameterivNV (GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCombinerInputParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCombinerInputParameterivNV = extproc;

	glGetCombinerInputParameterivNV(stage, portion, variable, pname, params);
}

static void APIENTRY InitGetCombinerOutputParameterfvNV (GLenum stage, GLenum portion, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCombinerOutputParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCombinerOutputParameterfvNV = extproc;

	glGetCombinerOutputParameterfvNV(stage, portion, pname, params);
}

static void APIENTRY InitGetCombinerOutputParameterivNV (GLenum stage, GLenum portion, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCombinerOutputParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCombinerOutputParameterivNV = extproc;

	glGetCombinerOutputParameterivNV(stage, portion, pname, params);
}

static void APIENTRY InitGetFinalCombinerInputParameterfvNV (GLenum variable, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFinalCombinerInputParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFinalCombinerInputParameterfvNV = extproc;

	glGetFinalCombinerInputParameterfvNV(variable, pname, params);
}

static void APIENTRY InitGetFinalCombinerInputParameterivNV (GLenum variable, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFinalCombinerInputParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFinalCombinerInputParameterivNV = extproc;

	glGetFinalCombinerInputParameterivNV(variable, pname, params);
}

static void APIENTRY InitResizeBuffersMESA (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glResizeBuffersMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glResizeBuffersMESA = extproc;

	glResizeBuffersMESA();
}

static void APIENTRY InitWindowPos2dMESA (GLdouble x, GLdouble y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2dMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2dMESA = extproc;

	glWindowPos2dMESA(x, y);
}

static void APIENTRY InitWindowPos2dvMESA (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2dvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2dvMESA = extproc;

	glWindowPos2dvMESA(v);
}

static void APIENTRY InitWindowPos2fMESA (GLfloat x, GLfloat y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2fMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2fMESA = extproc;

	glWindowPos2fMESA(x, y);
}

static void APIENTRY InitWindowPos2fvMESA (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2fvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2fvMESA = extproc;

	glWindowPos2fvMESA(v);
}

static void APIENTRY InitWindowPos2iMESA (GLint x, GLint y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2iMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2iMESA = extproc;

	glWindowPos2iMESA(x, y);
}

static void APIENTRY InitWindowPos2ivMESA (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2ivMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2ivMESA = extproc;

	glWindowPos2ivMESA(v);
}

static void APIENTRY InitWindowPos2sMESA (GLshort x, GLshort y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2sMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2sMESA = extproc;

	glWindowPos2sMESA(x, y);
}

static void APIENTRY InitWindowPos2svMESA (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos2svMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos2svMESA = extproc;

	glWindowPos2svMESA(v);
}

static void APIENTRY InitWindowPos3dMESA (GLdouble x, GLdouble y, GLdouble z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3dMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3dMESA = extproc;

	glWindowPos3dMESA(x, y, z);
}

static void APIENTRY InitWindowPos3dvMESA (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3dvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3dvMESA = extproc;

	glWindowPos3dvMESA(v);
}

static void APIENTRY InitWindowPos3fMESA (GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3fMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3fMESA = extproc;

	glWindowPos3fMESA(x, y, z);
}

static void APIENTRY InitWindowPos3fvMESA (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3fvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3fvMESA = extproc;

	glWindowPos3fvMESA(v);
}

static void APIENTRY InitWindowPos3iMESA (GLint x, GLint y, GLint z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3iMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3iMESA = extproc;

	glWindowPos3iMESA(x, y, z);
}

static void APIENTRY InitWindowPos3ivMESA (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3ivMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3ivMESA = extproc;

	glWindowPos3ivMESA(v);
}

static void APIENTRY InitWindowPos3sMESA (GLshort x, GLshort y, GLshort z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3sMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3sMESA = extproc;

	glWindowPos3sMESA(x, y, z);
}

static void APIENTRY InitWindowPos3svMESA (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos3svMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos3svMESA = extproc;

	glWindowPos3svMESA(v);
}

static void APIENTRY InitWindowPos4dMESA (GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4dMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4dMESA = extproc;

	glWindowPos4dMESA(x, y, z, w);
}

static void APIENTRY InitWindowPos4dvMESA (const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4dvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4dvMESA = extproc;

	glWindowPos4dvMESA(v);
}

static void APIENTRY InitWindowPos4fMESA (GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4fMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4fMESA = extproc;

	glWindowPos4fMESA(x, y, z, w);
}

static void APIENTRY InitWindowPos4fvMESA (const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4fvMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4fvMESA = extproc;

	glWindowPos4fvMESA(v);
}

static void APIENTRY InitWindowPos4iMESA (GLint x, GLint y, GLint z, GLint w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4iMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4iMESA = extproc;

	glWindowPos4iMESA(x, y, z, w);
}

static void APIENTRY InitWindowPos4ivMESA (const GLint *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4ivMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4ivMESA = extproc;

	glWindowPos4ivMESA(v);
}

static void APIENTRY InitWindowPos4sMESA (GLshort x, GLshort y, GLshort z, GLshort w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4sMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4sMESA = extproc;

	glWindowPos4sMESA(x, y, z, w);
}

static void APIENTRY InitWindowPos4svMESA (const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glWindowPos4svMESA");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glWindowPos4svMESA = extproc;

	glWindowPos4svMESA(v);
}

static void APIENTRY InitMultiModeDrawArraysIBM (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount, GLint modestride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiModeDrawArraysIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiModeDrawArraysIBM = extproc;

	glMultiModeDrawArraysIBM(mode, first, count, primcount, modestride);
}

static void APIENTRY InitMultiModeDrawElementsIBM (const GLenum *mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount, GLint modestride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMultiModeDrawElementsIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMultiModeDrawElementsIBM = extproc;

	glMultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride);
}

static void APIENTRY InitColorPointerListIBM (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glColorPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glColorPointerListIBM = extproc;

	glColorPointerListIBM(size, type, stride, pointer, ptrstride);
}

static void APIENTRY InitSecondaryColorPointerListIBM (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSecondaryColorPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSecondaryColorPointerListIBM = extproc;

	glSecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride);
}

static void APIENTRY InitEdgeFlagPointerListIBM (GLint stride, const GLboolean* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glEdgeFlagPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glEdgeFlagPointerListIBM = extproc;

	glEdgeFlagPointerListIBM(stride, pointer, ptrstride);
}

static void APIENTRY InitFogCoordPointerListIBM (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFogCoordPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFogCoordPointerListIBM = extproc;

	glFogCoordPointerListIBM(type, stride, pointer, ptrstride);
}

static void APIENTRY InitIndexPointerListIBM (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIndexPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glIndexPointerListIBM = extproc;

	glIndexPointerListIBM(type, stride, pointer, ptrstride);
}

static void APIENTRY InitNormalPointerListIBM (GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glNormalPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glNormalPointerListIBM = extproc;

	glNormalPointerListIBM(type, stride, pointer, ptrstride);
}

static void APIENTRY InitTexCoordPointerListIBM (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTexCoordPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTexCoordPointerListIBM = extproc;

	glTexCoordPointerListIBM(size, type, stride, pointer, ptrstride);
}

static void APIENTRY InitVertexPointerListIBM (GLint size, GLenum type, GLint stride, const GLvoid* *pointer, GLint ptrstride)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexPointerListIBM");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexPointerListIBM = extproc;

	glVertexPointerListIBM(size, type, stride, pointer, ptrstride);
}

static void APIENTRY InitTbufferMask3DFX (GLuint mask)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTbufferMask3DFX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTbufferMask3DFX = extproc;

	glTbufferMask3DFX(mask);
}

static void APIENTRY InitSampleMaskEXT (GLclampf value, GLboolean invert)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSampleMaskEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSampleMaskEXT = extproc;

	glSampleMaskEXT(value, invert);
}

static void APIENTRY InitSamplePatternEXT (GLenum pattern)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSamplePatternEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSamplePatternEXT = extproc;

	glSamplePatternEXT(pattern);
}

static void APIENTRY InitTextureColorMaskSGIS (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTextureColorMaskSGIS");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTextureColorMaskSGIS = extproc;

	glTextureColorMaskSGIS(red, green, blue, alpha);
}

static void APIENTRY InitIglooInterfaceSGIX (GLenum pname, const GLvoid *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIglooInterfaceSGIX");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glIglooInterfaceSGIX = extproc;

	glIglooInterfaceSGIX(pname, params);
}

static void APIENTRY InitGenFencesNV (GLsizei n, GLuint *fences)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGenFencesNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGenFencesNV = extproc;

	glGenFencesNV(n, fences);
}

static void APIENTRY InitDeleteFencesNV (GLsizei n, const GLuint *fences)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeleteFencesNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeleteFencesNV = extproc;

	glDeleteFencesNV(n, fences);
}

static void APIENTRY InitSetFenceNV (GLuint fence, GLenum condition)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glSetFenceNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glSetFenceNV = extproc;

	glSetFenceNV(fence, condition);
}

static GLboolean APIENTRY InitTestFenceNV (GLuint fence)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTestFenceNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glTestFenceNV = extproc;

	return glTestFenceNV(fence);
}

static void APIENTRY InitFinishFenceNV (GLuint fence)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glFinishFenceNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glFinishFenceNV = extproc;

	glFinishFenceNV(fence);
}

static GLboolean APIENTRY InitIsFenceNV (GLuint fence)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIsFenceNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glIsFenceNV = extproc;

	return glIsFenceNV(fence);
}

static void APIENTRY InitGetFenceivNV (GLuint fence, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetFenceivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetFenceivNV = extproc;

	glGetFenceivNV(fence, pname, params);
}

static void APIENTRY InitMapControlPointsNV (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const GLvoid *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMapControlPointsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMapControlPointsNV = extproc;

	glMapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points);
}

static void APIENTRY InitMapParameterivNV (GLenum target, GLenum pname, const GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMapParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMapParameterivNV = extproc;

	glMapParameterivNV(target, pname, params);
}

static void APIENTRY InitMapParameterfvNV (GLenum target, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glMapParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glMapParameterfvNV = extproc;

	glMapParameterfvNV(target, pname, params);
}

static void APIENTRY InitGetMapControlPointsNV (GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, GLvoid *points)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMapControlPointsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMapControlPointsNV = extproc;

	glGetMapControlPointsNV(target, index, type, ustride, vstride, packed, points);
}

static void APIENTRY InitGetMapParameterivNV (GLenum target, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMapParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMapParameterivNV = extproc;

	glGetMapParameterivNV(target, pname, params);
}

static void APIENTRY InitGetMapParameterfvNV (GLenum target, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMapParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMapParameterfvNV = extproc;

	glGetMapParameterfvNV(target, pname, params);
}

static void APIENTRY InitGetMapAttribParameterivNV (GLenum target, GLuint index, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMapAttribParameterivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMapAttribParameterivNV = extproc;

	glGetMapAttribParameterivNV(target, index, pname, params);
}

static void APIENTRY InitGetMapAttribParameterfvNV (GLenum target, GLuint index, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetMapAttribParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetMapAttribParameterfvNV = extproc;

	glGetMapAttribParameterfvNV(target, index, pname, params);
}

static void APIENTRY InitEvalMapsNV (GLenum target, GLenum mode)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glEvalMapsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glEvalMapsNV = extproc;

	glEvalMapsNV(target, mode);
}

static void APIENTRY InitCombinerStageParameterfvNV (GLenum stage, GLenum pname, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glCombinerStageParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glCombinerStageParameterfvNV = extproc;

	glCombinerStageParameterfvNV(stage, pname, params);
}

static void APIENTRY InitGetCombinerStageParameterfvNV (GLenum stage, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetCombinerStageParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetCombinerStageParameterfvNV = extproc;

	glGetCombinerStageParameterfvNV(stage, pname, params);
}

static void APIENTRY InitBindProgramNV (GLenum target, GLuint id)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glBindProgramNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glBindProgramNV = extproc;

	glBindProgramNV(target, id);
}

static void APIENTRY InitDeleteProgramsNV (GLsizei n, const GLuint *ids)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glDeleteProgramsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glDeleteProgramsNV = extproc;

	glDeleteProgramsNV(n, ids);
}

static void APIENTRY InitExecuteProgramNV (GLenum target, GLuint id, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glExecuteProgramNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glExecuteProgramNV = extproc;

	glExecuteProgramNV(target, id, params);
}

static void APIENTRY InitGenProgramsNV (GLsizei n, GLuint *ids)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGenProgramsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGenProgramsNV = extproc;

	glGenProgramsNV(n, ids);
}

static GLboolean APIENTRY InitAreProgramsResidentNV (GLsizei n, const GLuint *ids, GLboolean *residences)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glAreProgramsResidentNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glAreProgramsResidentNV = extproc;

	return glAreProgramsResidentNV(n, ids, residences);
}

static void APIENTRY InitRequestResidentProgramsNV (GLsizei n, const GLuint *ids)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glRequestResidentProgramsNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glRequestResidentProgramsNV = extproc;

	glRequestResidentProgramsNV(n, ids);
}

static void APIENTRY InitGetProgramParameterfvNV (GLenum target, GLuint index, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetProgramParameterfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetProgramParameterfvNV = extproc;

	glGetProgramParameterfvNV(target, index, pname, params);
}

static void APIENTRY InitGetProgramParameterdvNV (GLenum target, GLuint index, GLenum pname, GLdouble *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetProgramParameterdvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetProgramParameterdvNV = extproc;

	glGetProgramParameterdvNV(target, index, pname, params);
}

static void APIENTRY InitGetProgramivNV (GLuint id, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetProgramivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetProgramivNV = extproc;

	glGetProgramivNV(id, pname, params);
}

static void APIENTRY InitGetProgramStringNV (GLuint id, GLenum pname, GLubyte *program)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetProgramStringNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetProgramStringNV = extproc;

	glGetProgramStringNV(id, pname, program);
}

static void APIENTRY InitGetTrackMatrixivNV (GLenum target, GLuint address, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetTrackMatrixivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetTrackMatrixivNV = extproc;

	glGetTrackMatrixivNV(target, address, pname, params);
}

static void APIENTRY InitGetVertexAttribdvNV (GLuint index, GLenum pname, GLdouble *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetVertexAttribdvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetVertexAttribdvNV = extproc;

	glGetVertexAttribdvNV(index, pname, params);
}

static void APIENTRY InitGetVertexAttribfvNV (GLuint index, GLenum pname, GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetVertexAttribfvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetVertexAttribfvNV = extproc;

	glGetVertexAttribfvNV(index, pname, params);
}

static void APIENTRY InitGetVertexAttribivNV (GLuint index, GLenum pname, GLint *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetVertexAttribivNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetVertexAttribivNV = extproc;

	glGetVertexAttribivNV(index, pname, params);
}

static void APIENTRY InitGetVertexAttribPointervNV (GLuint index, GLenum pname, GLvoid* *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glGetVertexAttribPointervNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glGetVertexAttribPointervNV = extproc;

	glGetVertexAttribPointervNV(index, pname, pointer);
}

static GLboolean APIENTRY InitIsProgramNV (GLuint id)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glIsProgramNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	glIsProgramNV = extproc;

	return glIsProgramNV(id);
}

static void APIENTRY InitLoadProgramNV (GLenum target, GLuint id, GLsizei len, const GLubyte *program)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glLoadProgramNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glLoadProgramNV = extproc;

	glLoadProgramNV(target, id, len, program);
}

static void APIENTRY InitProgramParameter4fNV (GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameter4fNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameter4fNV = extproc;

	glProgramParameter4fNV(target, index, x, y, z, w);
}

static void APIENTRY InitProgramParameter4dNV (GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameter4dNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameter4dNV = extproc;

	glProgramParameter4dNV(target, index, x, y, z, w);
}

static void APIENTRY InitProgramParameter4dvNV (GLenum target, GLuint index, const GLdouble *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameter4dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameter4dvNV = extproc;

	glProgramParameter4dvNV(target, index, params);
}

static void APIENTRY InitProgramParameter4fvNV (GLenum target, GLuint index, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameter4fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameter4fvNV = extproc;

	glProgramParameter4fvNV(target, index, params);
}

static void APIENTRY InitProgramParameters4dvNV (GLenum target, GLuint index, GLuint num, const GLdouble *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameters4dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameters4dvNV = extproc;

	glProgramParameters4dvNV(target, index, num, params);
}

static void APIENTRY InitProgramParameters4fvNV (GLenum target, GLuint index, GLuint num, const GLfloat *params)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glProgramParameters4fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glProgramParameters4fvNV = extproc;

	glProgramParameters4fvNV(target, index, num, params);
}

static void APIENTRY InitTrackMatrixNV (GLenum target, GLuint address, GLenum matrix, GLenum transform)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glTrackMatrixNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glTrackMatrixNV = extproc;

	glTrackMatrixNV(target, address, matrix, transform);
}

static void APIENTRY InitVertexAttribPointerNV (GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribPointerNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribPointerNV = extproc;

	glVertexAttribPointerNV(index, size, type, stride, pointer);
}

static void APIENTRY InitVertexAttrib1sNV (GLuint index, GLshort x)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1sNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1sNV = extproc;

	glVertexAttrib1sNV(index, x);
}

static void APIENTRY InitVertexAttrib1fNV (GLuint index, GLfloat x)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1fNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1fNV = extproc;

	glVertexAttrib1fNV(index, x);
}

static void APIENTRY InitVertexAttrib1dNV (GLuint index, GLdouble x)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1dNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1dNV = extproc;

	glVertexAttrib1dNV(index, x);
}

static void APIENTRY InitVertexAttrib2sNV (GLuint index, GLshort x, GLshort y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2sNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2sNV = extproc;

	glVertexAttrib2sNV(index, x, y);
}

static void APIENTRY InitVertexAttrib2fNV (GLuint index, GLfloat x, GLfloat y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2fNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2fNV = extproc;

	glVertexAttrib2fNV(index, x, y);
}

static void APIENTRY InitVertexAttrib2dNV (GLuint index, GLdouble x, GLdouble y)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2dNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2dNV = extproc;

	glVertexAttrib2dNV(index, x, y);
}

static void APIENTRY InitVertexAttrib3sNV (GLuint index, GLshort x, GLshort y, GLshort z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3sNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3sNV = extproc;

	glVertexAttrib3sNV(index, x, y, z);
}

static void APIENTRY InitVertexAttrib3fNV (GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3fNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3fNV = extproc;

	glVertexAttrib3fNV(index, x, y, z);
}

static void APIENTRY InitVertexAttrib3dNV (GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3dNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3dNV = extproc;

	glVertexAttrib3dNV(index, x, y, z);
}

static void APIENTRY InitVertexAttrib4sNV (GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4sNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4sNV = extproc;

	glVertexAttrib4sNV(index, x, y, z, w);
}

static void APIENTRY InitVertexAttrib4fNV (GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4fNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4fNV = extproc;

	glVertexAttrib4fNV(index, x, y, z, w);
}

static void APIENTRY InitVertexAttrib4dNV (GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4dNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4dNV = extproc;

	glVertexAttrib4dNV(index, x, y, z, w);
}

static void APIENTRY InitVertexAttrib4ubNV (GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4ubNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4ubNV = extproc;

	glVertexAttrib4ubNV(index, x, y, z, w);
}

static void APIENTRY InitVertexAttrib1svNV (GLuint index, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1svNV = extproc;

	glVertexAttrib1svNV(index, v);
}

static void APIENTRY InitVertexAttrib1fvNV (GLuint index, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1fvNV = extproc;

	glVertexAttrib1fvNV(index, v);
}

static void APIENTRY InitVertexAttrib1dvNV (GLuint index, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib1dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib1dvNV = extproc;

	glVertexAttrib1dvNV(index, v);
}

static void APIENTRY InitVertexAttrib2svNV (GLuint index, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2svNV = extproc;

	glVertexAttrib2svNV(index, v);
}

static void APIENTRY InitVertexAttrib2fvNV (GLuint index, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2fvNV = extproc;

	glVertexAttrib2fvNV(index, v);
}

static void APIENTRY InitVertexAttrib2dvNV (GLuint index, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib2dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib2dvNV = extproc;

	glVertexAttrib2dvNV(index, v);
}

static void APIENTRY InitVertexAttrib3svNV (GLuint index, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3svNV = extproc;

	glVertexAttrib3svNV(index, v);
}

static void APIENTRY InitVertexAttrib3fvNV (GLuint index, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3fvNV = extproc;

	glVertexAttrib3fvNV(index, v);
}

static void APIENTRY InitVertexAttrib3dvNV (GLuint index, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib3dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib3dvNV = extproc;

	glVertexAttrib3dvNV(index, v);
}

static void APIENTRY InitVertexAttrib4svNV (GLuint index, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4svNV = extproc;

	glVertexAttrib4svNV(index, v);
}

static void APIENTRY InitVertexAttrib4fvNV (GLuint index, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4fvNV = extproc;

	glVertexAttrib4fvNV(index, v);
}

static void APIENTRY InitVertexAttrib4dvNV (GLuint index, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4dvNV = extproc;

	glVertexAttrib4dvNV(index, v);
}

static void APIENTRY InitVertexAttrib4ubvNV (GLuint index, const GLubyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttrib4ubvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttrib4ubvNV = extproc;

	glVertexAttrib4ubvNV(index, v);
}

static void APIENTRY InitVertexAttribs1svNV (GLuint index, GLsizei n, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs1svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs1svNV = extproc;

	glVertexAttribs1svNV(index, n, v);
}

static void APIENTRY InitVertexAttribs1fvNV (GLuint index, GLsizei n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs1fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs1fvNV = extproc;

	glVertexAttribs1fvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs1dvNV (GLuint index, GLsizei n, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs1dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs1dvNV = extproc;

	glVertexAttribs1dvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs2svNV (GLuint index, GLsizei n, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs2svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs2svNV = extproc;

	glVertexAttribs2svNV(index, n, v);
}

static void APIENTRY InitVertexAttribs2fvNV (GLuint index, GLsizei n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs2fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs2fvNV = extproc;

	glVertexAttribs2fvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs2dvNV (GLuint index, GLsizei n, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs2dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs2dvNV = extproc;

	glVertexAttribs2dvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs3svNV (GLuint index, GLsizei n, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs3svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs3svNV = extproc;

	glVertexAttribs3svNV(index, n, v);
}

static void APIENTRY InitVertexAttribs3fvNV (GLuint index, GLsizei n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs3fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs3fvNV = extproc;

	glVertexAttribs3fvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs3dvNV (GLuint index, GLsizei n, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs3dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs3dvNV = extproc;

	glVertexAttribs3dvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs4svNV (GLuint index, GLsizei n, const GLshort *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs4svNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs4svNV = extproc;

	glVertexAttribs4svNV(index, n, v);
}

static void APIENTRY InitVertexAttribs4fvNV (GLuint index, GLsizei n, const GLfloat *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs4fvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs4fvNV = extproc;

	glVertexAttribs4fvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs4dvNV (GLuint index, GLsizei n, const GLdouble *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs4dvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs4dvNV = extproc;

	glVertexAttribs4dvNV(index, n, v);
}

static void APIENTRY InitVertexAttribs4ubvNV (GLuint index, GLsizei n, const GLubyte *v)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glVertexAttribs4ubvNV");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glVertexAttribs4ubvNV = extproc;

	glVertexAttribs4ubvNV(index, n, v);
}

static void APIENTRY InitAddSwapHintRectWIN (GLint x, GLint y, GLsizei width, GLsizei height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("glAddSwapHintRectWIN");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	glAddSwapHintRectWIN = extproc;

	glAddSwapHintRectWIN(x, y, width, height);
}

static void APIENTRY InitTexBumpParameterivATI (GLenum pname, const GLint *param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glTexBumpParameterivATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glTexBumpParameterivATI = extproc;

    glTexBumpParameterivATI(pname, param);
}

static void APIENTRY InitTexBumpParameterfvATI (GLenum pname, const GLfloat *param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glTexBumpParameterfvATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glTexBumpParameterfvATI = extproc;

    glTexBumpParameterfvATI(pname, param);
}

static void APIENTRY InitGetTexBumpParameterivATI (GLenum pname, GLint *param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetTexBumpParameterivATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetTexBumpParameterivATI = extproc;

    glGetTexBumpParameterivATI(pname, param);
}

static void APIENTRY InitGetTexBumpParameterfvATI (GLenum pname, GLfloat *param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetTexBumpParameterfvATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetTexBumpParameterfvATI = extproc;

    glGetTexBumpParameterfvATI(pname, param);
}

static GLuint APIENTRY InitGenFragmentShadersATI (GLuint range)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGenFragmentShadersATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glGenFragmentShadersATI = extproc;

    return glGenFragmentShadersATI(range);
}

static void APIENTRY InitBindFragmentShaderATI (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindFragmentShaderATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glBindFragmentShaderATI = extproc;

    glBindFragmentShaderATI(id);
}

static void APIENTRY InitDeleteFragmentShaderATI (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDeleteFragmentShaderATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glDeleteFragmentShaderATI = extproc;

    glDeleteFragmentShaderATI(id);
}

static void APIENTRY InitBeginFragmentShaderATI (void)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBeginFragmentShaderATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glBeginFragmentShaderATI = extproc;

    glBeginFragmentShaderATI();
}

static void APIENTRY InitEndFragmentShaderATI (void)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glEndFragmentShaderATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glEndFragmentShaderATI = extproc;

    glEndFragmentShaderATI();
}

static void APIENTRY InitPassTexCoordATI (GLuint dst, GLuint coord, GLenum swizzle)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glPassTexCoordATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glPassTexCoordATI = extproc;

    glPassTexCoordATI(dst, coord, swizzle);
}

static void APIENTRY InitSampleMapATI (GLuint dst, GLuint interp, GLenum swizzle)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glSampleMapATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glSampleMapATI = extproc;

    glSampleMapATI(dst, interp, swizzle);
}

static void APIENTRY InitColorFragmentOp1ATI (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glColorFragmentOp1ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glColorFragmentOp1ATI = extproc;

    glColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod);
}

static void APIENTRY InitColorFragmentOp2ATI (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glColorFragmentOp2ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glColorFragmentOp2ATI = extproc;

    glColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

static void APIENTRY InitColorFragmentOp3ATI (GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glColorFragmentOp3ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glColorFragmentOp3ATI = extproc;

    glColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

static void APIENTRY InitAlphaFragmentOp1ATI (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glAlphaFragmentOp1ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glAlphaFragmentOp1ATI = extproc;

    glAlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod);
}

static void APIENTRY InitAlphaFragmentOp2ATI (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glAlphaFragmentOp2ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glAlphaFragmentOp2ATI = extproc;

    glAlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

static void APIENTRY InitAlphaFragmentOp3ATI (GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glAlphaFragmentOp3ATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glAlphaFragmentOp3ATI = extproc;

    glAlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

static void APIENTRY InitSetFragmentShaderConstantATI (GLuint dst, const GLfloat *value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glSetFragmentShaderConstantATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glSetFragmentShaderConstantATI = extproc;

    glSetFragmentShaderConstantATI(dst, value);
}

static void APIENTRY InitPNTrianglesiATI (GLenum pname, GLint param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glPNTrianglesiATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glPNTrianglesiATI = extproc;

    glPNTrianglesiATI(pname, param);
}

static void APIENTRY InitPNTrianglesfATI (GLenum pname, GLfloat param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glPNTrianglesfATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glPNTrianglesfATI = extproc;

    glPNTrianglesfATI(pname, param);
}

static GLuint APIENTRY InitNewObjectBufferATI (GLsizei size, const GLvoid *pointer, GLenum usage)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNewObjectBufferATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glNewObjectBufferATI = extproc;

    return glNewObjectBufferATI(size, pointer, usage);
}

static GLboolean APIENTRY InitIsObjectBufferATI (GLuint buffer)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glIsObjectBufferATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glIsObjectBufferATI = extproc;

    return glIsObjectBufferATI(buffer);
}

static void APIENTRY InitUpdateObjectBufferATI (GLuint buffer, GLuint offset, GLsizei size, const GLvoid *pointer, GLenum preserve)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glUpdateObjectBufferATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glUpdateObjectBufferATI = extproc;

    glUpdateObjectBufferATI(buffer, offset, size, pointer, preserve);
}

static void APIENTRY InitGetObjectBufferfvATI (GLuint buffer, GLenum pname, GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetObjectBufferfvATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetObjectBufferfvATI = extproc;

    glGetObjectBufferfvATI(buffer, pname, params);
}

static void APIENTRY InitGetObjectBufferivATI (GLuint buffer, GLenum pname, GLint *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetObjectBufferivATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetObjectBufferivATI = extproc;

    glGetObjectBufferivATI(buffer, pname, params);
}

static void APIENTRY InitDeleteObjectBufferATI (GLuint buffer)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDeleteObjectBufferATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glDeleteObjectBufferATI = extproc;

    glDeleteObjectBufferATI(buffer);
}

static void APIENTRY InitArrayObjectATI (GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glArrayObjectATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glArrayObjectATI = extproc;

    glArrayObjectATI(array, size, type, stride, buffer, offset);
}

static void APIENTRY InitGetArrayObjectfvATI (GLenum array, GLenum pname, GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetArrayObjectfvATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetArrayObjectfvATI = extproc;

    glGetArrayObjectfvATI(array, pname, params);
}

static void APIENTRY InitGetArrayObjectivATI (GLenum array, GLenum pname, GLint *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetArrayObjectivATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetArrayObjectivATI = extproc;

    glGetArrayObjectivATI(array, pname, params);
}

static void APIENTRY InitVariantArrayObjectATI (GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantArrayObjectATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantArrayObjectATI = extproc;

    glVariantArrayObjectATI(id, type, stride, buffer, offset);
}

static void APIENTRY InitGetVariantArrayObjectfvATI (GLuint id, GLenum pname, GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantArrayObjectfvATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantArrayObjectfvATI = extproc;

    glGetVariantArrayObjectfvATI(id, pname, params);
}

static void APIENTRY InitGetVariantArrayObjectivATI (GLuint id, GLenum pname, GLint *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantArrayObjectivATI");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantArrayObjectivATI = extproc;

    glGetVariantArrayObjectivATI(id, pname, params);
}

static void APIENTRY InitBeginVertexShaderEXT (void)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBeginVertexShaderEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glBeginVertexShaderEXT = extproc;

    glBeginVertexShaderEXT();
}

static void APIENTRY InitEndVertexShaderEXT (void)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glEndVertexShaderEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glEndVertexShaderEXT = extproc;

    glEndVertexShaderEXT();
}

static void APIENTRY InitBindVertexShaderEXT (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindVertexShaderEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glBindVertexShaderEXT = extproc;

    glBindVertexShaderEXT(id);
}

static GLuint APIENTRY InitGenVertexShadersEXT (GLuint range)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGenVertexShadersEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glGenVertexShadersEXT = extproc;

    return glGenVertexShadersEXT(range);
}

static void APIENTRY InitDeleteVertexShaderEXT (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDeleteVertexShaderEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glDeleteVertexShaderEXT = extproc;

    glDeleteVertexShaderEXT(id);
}

static void APIENTRY InitShaderOp1EXT (GLenum op, GLuint res, GLuint arg1)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glShaderOp1EXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glShaderOp1EXT = extproc;

    glShaderOp1EXT(op, res, arg1);
}

static void APIENTRY InitShaderOp2EXT (GLenum op, GLuint res, GLuint arg1, GLuint arg2)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glShaderOp2EXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glShaderOp2EXT = extproc;

    glShaderOp2EXT(op, res, arg1, arg2);
}

static void APIENTRY InitShaderOp3EXT (GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glShaderOp3EXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glShaderOp3EXT = extproc;

    glShaderOp3EXT(op, res, arg1, arg2, arg3);
}

static void APIENTRY InitSwizzleEXT (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glSwizzleEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glSwizzleEXT = extproc;

    glSwizzleEXT(res, in, outX, outY, outZ, outW);
}

static void APIENTRY InitWriteMaskEXT (GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glWriteMaskEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glWriteMaskEXT = extproc;

    glWriteMaskEXT(res, in, outX, outY, outZ, outW);
}

static void APIENTRY InitInsertComponentEXT (GLuint res, GLuint src, GLuint num)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glInsertComponentEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glInsertComponentEXT = extproc;

    glInsertComponentEXT(res, src, num);
}

static void APIENTRY InitExtractComponentEXT (GLuint res, GLuint src, GLuint num)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glExtractComponentEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glExtractComponentEXT = extproc;

    glExtractComponentEXT(res, src, num);
}

static GLuint APIENTRY InitGenSymbolsEXT (GLenum datatype, GLenum storagetype, GLenum range, GLuint components)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGenSymbolsEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glGenSymbolsEXT = extproc;

    return glGenSymbolsEXT(datatype, storagetype, range, components);
}

static void APIENTRY InitSetInvariantEXT (GLuint id, GLenum type, const void *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glSetInvariantEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glSetInvariantEXT = extproc;

    glSetInvariantEXT(id, type, addr);
}

static void APIENTRY InitSetLocalConstantEXT (GLuint id, GLenum type, const void *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glSetLocalConstantEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glSetLocalConstantEXT = extproc;

    glSetLocalConstantEXT(id, type, addr);
}

static void APIENTRY InitVariantbvEXT (GLuint id, const GLbyte *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantbvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantbvEXT = extproc;

    glVariantbvEXT(id, addr);
}

static void APIENTRY InitVariantsvEXT (GLuint id, const GLshort *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantsvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantsvEXT = extproc;

    glVariantsvEXT(id, addr);
}

static void APIENTRY InitVariantivEXT (GLuint id, const GLint *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantivEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantivEXT = extproc;

    glVariantivEXT(id, addr);
}

static void APIENTRY InitVariantfvEXT (GLuint id, const GLfloat *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantfvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantfvEXT = extproc;

    glVariantfvEXT(id, addr);
}

static void APIENTRY InitVariantdvEXT (GLuint id, const GLdouble *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantdvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantdvEXT = extproc;

    glVariantdvEXT(id, addr);
}

static void APIENTRY InitVariantubvEXT (GLuint id, const GLubyte *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantubvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantubvEXT = extproc;

    glVariantubvEXT(id, addr);
}

static void APIENTRY InitVariantusvEXT (GLuint id, const GLushort *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantusvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantusvEXT = extproc;

    glVariantusvEXT(id, addr);
}

static void APIENTRY InitVariantuivEXT (GLuint id, const GLuint *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantuivEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantuivEXT = extproc;

    glVariantuivEXT(id, addr);
}

static void APIENTRY InitVariantPointerEXT (GLuint id, GLenum type, GLuint stride, const void *addr)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVariantPointerEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVariantPointerEXT = extproc;

    glVariantPointerEXT(id, type, stride, addr);
}

static void APIENTRY InitEnableVariantClientStateEXT (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glEnableVariantClientStateEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glEnableVariantClientStateEXT = extproc;

    glEnableVariantClientStateEXT(id);
}

static void APIENTRY InitDisableVariantClientStateEXT (GLuint id)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDisableVariantClientStateEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glDisableVariantClientStateEXT = extproc;

    glDisableVariantClientStateEXT(id);
}

static GLuint APIENTRY InitBindLightParameterEXT (GLenum light, GLenum value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindLightParameterEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glBindLightParameterEXT = extproc;

    return glBindLightParameterEXT(light, value);
}

static GLuint APIENTRY InitBindMaterialParameterEXT (GLenum face, GLenum value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindMaterialParameterEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glBindMaterialParameterEXT = extproc;

    return glBindMaterialParameterEXT(face, value);
}

static GLuint APIENTRY InitBindTexGenParameterEXT (GLenum unit, GLenum coord, GLenum value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindTexGenParameterEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glBindTexGenParameterEXT = extproc;

    return glBindTexGenParameterEXT(unit, coord, value);
}

static GLuint APIENTRY InitBindTextureUnitParameterEXT (GLenum unit, GLenum value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindTextureUnitParameterEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glBindTextureUnitParameterEXT = extproc;

    return glBindTextureUnitParameterEXT(unit, value);
}

static GLuint APIENTRY InitBindParameterEXT (GLenum value)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindParameterEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glBindParameterEXT = extproc;

    return glBindParameterEXT(value);
}

static GLboolean APIENTRY InitIsVariantEnabledEXT (GLuint id, GLenum cap)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glIsVariantEnabledEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return 0;
    }

    glIsVariantEnabledEXT = extproc;

    return glIsVariantEnabledEXT(id, cap);
}

static void APIENTRY InitGetVariantBooleanvEXT (GLuint id, GLenum value, GLboolean *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantBooleanvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantBooleanvEXT = extproc;

    glGetVariantBooleanvEXT(id, value, data);
}

static void APIENTRY InitGetVariantIntegervEXT (GLuint id, GLenum value, GLint *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantIntegervEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantIntegervEXT = extproc;

    glGetVariantIntegervEXT(id, value, data);
}

static void APIENTRY InitGetVariantFloatvEXT (GLuint id, GLenum value, GLfloat *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantFloatvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantFloatvEXT = extproc;

    glGetVariantFloatvEXT(id, value, data);
}

static void APIENTRY InitGetVariantPointervEXT (GLuint id, GLenum value, GLvoid* *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVariantPointervEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetVariantPointervEXT = extproc;

    glGetVariantPointervEXT(id, value, data);
}

static void APIENTRY InitGetInvariantBooleanvEXT (GLuint id, GLenum value, GLboolean *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetInvariantBooleanvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetInvariantBooleanvEXT = extproc;

    glGetInvariantBooleanvEXT(id, value, data);
}

static void APIENTRY InitGetInvariantIntegervEXT (GLuint id, GLenum value, GLint *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetInvariantIntegervEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetInvariantIntegervEXT = extproc;

    glGetInvariantIntegervEXT(id, value, data);
}

static void APIENTRY InitGetInvariantFloatvEXT (GLuint id, GLenum value, GLfloat *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetInvariantFloatvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetInvariantFloatvEXT = extproc;

    glGetInvariantFloatvEXT(id, value, data);
}

static void APIENTRY InitGetLocalConstantBooleanvEXT (GLuint id, GLenum value, GLboolean *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetLocalConstantBooleanvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetLocalConstantBooleanvEXT = extproc;

    glGetLocalConstantBooleanvEXT(id, value, data);
}

static void APIENTRY InitGetLocalConstantIntegervEXT (GLuint id, GLenum value, GLint *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetLocalConstantIntegervEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetLocalConstantIntegervEXT = extproc;

    glGetLocalConstantIntegervEXT(id, value, data);
}

static void APIENTRY InitGetLocalConstantFloatvEXT (GLuint id, GLenum value, GLfloat *data)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetLocalConstantFloatvEXT");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glGetLocalConstantFloatvEXT = extproc;

    glGetLocalConstantFloatvEXT(id, value, data);
}

static void APIENTRY InitVertexStream1s (GLenum stream, GLshort x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1s");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1s = extproc;

    glVertexStream1s(stream, x);
}

static void APIENTRY InitVertexStream1sv (GLenum stream, const GLshort *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1sv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1sv = extproc;

    glVertexStream1sv(stream, coords);
}

static void APIENTRY InitVertexStream1i (GLenum stream, GLint x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1i");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1i = extproc;

    glVertexStream1i(stream, x);
}

static void APIENTRY InitVertexStream1iv (GLenum stream, const GLint *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1iv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1iv = extproc;

    glVertexStream1iv(stream, coords);
}

static void APIENTRY InitVertexStream1f (GLenum stream, GLfloat x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1f");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1f = extproc;

    glVertexStream1f(stream, x);
}

static void APIENTRY InitVertexStream1fv (GLenum stream, const GLfloat *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1fv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1fv = extproc;

    glVertexStream1fv(stream, coords);
}

static void APIENTRY InitVertexStream1d (GLenum stream, GLdouble x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1d");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1d = extproc;

    glVertexStream1d(stream, x);
}

static void APIENTRY InitVertexStream1dv (GLenum stream, const GLdouble *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream1dv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream1dv = extproc;

    glVertexStream1dv(stream, coords);
}

static void APIENTRY InitVertexStream2s (GLenum stream, GLshort x, GLshort y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2s");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2s = extproc;

    glVertexStream2s(stream, x, y);
}

static void APIENTRY InitVertexStream2sv (GLenum stream, const GLshort *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2sv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2sv = extproc;

    glVertexStream2sv(stream, coords);
}

static void APIENTRY InitVertexStream2i (GLenum stream, GLint x, GLint y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2i");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2i = extproc;

    glVertexStream2i(stream, x, y);
}

static void APIENTRY InitVertexStream2iv (GLenum stream, const GLint *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2iv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2iv = extproc;

    glVertexStream2iv(stream, coords);
}

static void APIENTRY InitVertexStream2f (GLenum stream, GLfloat x, GLfloat y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2f");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2f = extproc;

    glVertexStream2f(stream, x, y);
}

static void APIENTRY InitVertexStream2fv (GLenum stream, const GLfloat *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2fv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2fv = extproc;

    glVertexStream2fv(stream, coords);
}

static void APIENTRY InitVertexStream2d (GLenum stream, GLdouble x, GLdouble y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2d");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2d = extproc;

    glVertexStream2d(stream, x, y);
}

static void APIENTRY InitVertexStream2dv (GLenum stream, const GLdouble *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream2dv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream2dv = extproc;

    glVertexStream2dv(stream, coords);
}

static void APIENTRY InitVertexStream3s (GLenum stream, GLshort x, GLshort y, GLshort z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3s");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3s = extproc;

    glVertexStream3s(stream, x, y, z);
}

static void APIENTRY InitVertexStream3sv (GLenum stream, const GLshort *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3sv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3sv = extproc;

    glVertexStream3sv(stream, coords);
}

static void APIENTRY InitVertexStream3i (GLenum stream, GLint x, GLint y, GLint z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3i");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3i = extproc;

    glVertexStream3i(stream, x, y, z);
}

static void APIENTRY InitVertexStream3iv (GLenum stream, const GLint *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3iv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3iv = extproc;

    glVertexStream3iv(stream, coords);
}

static void APIENTRY InitVertexStream3f (GLenum stream, GLfloat x, GLfloat y, GLfloat z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3f");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3f = extproc;

    glVertexStream3f(stream, x, y, z);
}

static void APIENTRY InitVertexStream3fv (GLenum stream, const GLfloat *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3fv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3fv = extproc;

    glVertexStream3fv(stream, coords);
}

static void APIENTRY InitVertexStream3d (GLenum stream, GLdouble x, GLdouble y, GLdouble z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3d");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3d = extproc;

    glVertexStream3d(stream, x, y, z);
}

static void APIENTRY InitVertexStream3dv (GLenum stream, const GLdouble *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream3dv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream3dv = extproc;

    glVertexStream3dv(stream, coords);
}

static void APIENTRY InitVertexStream4s (GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4s");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4s = extproc;

    glVertexStream4s(stream, x, y, z, w);
}

static void APIENTRY InitVertexStream4sv (GLenum stream, const GLshort *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4sv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4sv = extproc;

    glVertexStream4sv(stream, coords);
}

static void APIENTRY InitVertexStream4i (GLenum stream, GLint x, GLint y, GLint z, GLint w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4i");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4i = extproc;

    glVertexStream4i(stream, x, y, z, w);
}

static void APIENTRY InitVertexStream4iv (GLenum stream, const GLint *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4iv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4iv = extproc;

    glVertexStream4iv(stream, coords);
}

static void APIENTRY InitVertexStream4f (GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4f");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4f = extproc;

    glVertexStream4f(stream, x, y, z, w);
}

static void APIENTRY InitVertexStream4fv (GLenum stream, const GLfloat *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4fv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4fv = extproc;

    glVertexStream4fv(stream, coords);
}

static void APIENTRY InitVertexStream4d (GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4d");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4d = extproc;

    glVertexStream4d(stream, x, y, z, w);
}

static void APIENTRY InitVertexStream4dv (GLenum stream, const GLdouble *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexStream4dv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexStream4dv = extproc;

    glVertexStream4dv(stream, coords);
}

static void APIENTRY InitNormalStream3b (GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3b");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3b = extproc;

    glNormalStream3b(stream, nx, ny, nz);
}

static void APIENTRY InitNormalStream3bv (GLenum stream, const GLbyte *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3bv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3bv = extproc;

    glNormalStream3bv(stream, coords);
}

static void APIENTRY InitNormalStream3s (GLenum stream, GLshort nx, GLshort ny, GLshort nz)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3s");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3s = extproc;

    glNormalStream3s(stream, nx, ny, nz);
}

static void APIENTRY InitNormalStream3sv (GLenum stream, const GLshort *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3sv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3sv = extproc;

    glNormalStream3sv(stream, coords);
}

static void APIENTRY InitNormalStream3i (GLenum stream, GLint nx, GLint ny, GLint nz)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3i");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3i = extproc;

    glNormalStream3i(stream, nx, ny, nz);
}

static void APIENTRY InitNormalStream3iv (GLenum stream, const GLint *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3iv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3iv = extproc;

    glNormalStream3iv(stream, coords);
}

static void APIENTRY InitNormalStream3f (GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3f");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3f = extproc;

    glNormalStream3f(stream, nx, ny, nz);
}

static void APIENTRY InitNormalStream3fv (GLenum stream, const GLfloat *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3fv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3fv = extproc;

    glNormalStream3fv(stream, coords);
}

static void APIENTRY InitNormalStream3d (GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3d");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3d = extproc;

    glNormalStream3d(stream, nx, ny, nz);
}

static void APIENTRY InitNormalStream3dv (GLenum stream, const GLdouble *coords)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glNormalStream3dv");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glNormalStream3dv = extproc;

    glNormalStream3dv(stream, coords);
}

static void APIENTRY InitClientActiveVertexStream (GLenum stream)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glClientActiveVertexStream");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glClientActiveVertexStream = extproc;

    glClientActiveVertexStream(stream);
}

static void APIENTRY InitVertexBlendEnvi (GLenum pname, GLint param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexBlendEnvi");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexBlendEnvi = extproc;

    glVertexBlendEnvi(pname, param);
}

static void APIENTRY InitVertexBlendEnvf (GLenum pname, GLfloat param)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexBlendEnvf");

    if (extproc == NULL) {
        _ASSERT(0);
        return;
    }

    glVertexBlendEnvf = extproc;

    glVertexBlendEnvf(pname, param);
}

static void APIENTRY InitVertexAttrib1sARB(GLuint index, GLshort x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1sARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1sARB = extproc;

    glVertexAttrib1sARB(index, x);    
}

static void APIENTRY InitVertexAttrib1fARB(GLuint index, GLfloat x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1fARB = extproc;

    glVertexAttrib1fARB(index, x);    
}

static void APIENTRY InitVertexAttrib1dARB(GLuint index, GLdouble x)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1dARB = extproc;

    glVertexAttrib1dARB(index, x);    
}

static void APIENTRY InitVertexAttrib2sARB(GLuint index, GLshort x, GLshort y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2sARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2sARB = extproc;

    glVertexAttrib2sARB(index, x, y);    
}

static void APIENTRY InitVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2fARB = extproc;

    glVertexAttrib2fARB(index, x, y);    
}

static void APIENTRY InitVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2dARB = extproc;

    glVertexAttrib2dARB(index, x, y);    
}

static void APIENTRY InitVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3sARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3sARB = extproc;

    glVertexAttrib3sARB(index, x, y, z);    
}

static void APIENTRY InitVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3fARB = extproc;

    glVertexAttrib3fARB(index, x, y, z);    
}

static void APIENTRY InitVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3dARB = extproc;

    glVertexAttrib3dARB(index, x, y, z);    
}

static void APIENTRY InitVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4sARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4sARB = extproc;

    glVertexAttrib4sARB(index, x, y, z, w);    
}

static void APIENTRY InitVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4fARB = extproc;

    glVertexAttrib4fARB(index, x, y, z, w);    
}

static void APIENTRY InitVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4dARB = extproc;

    glVertexAttrib4dARB(index, x, y, z, w);    
}

static void APIENTRY InitVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NubARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NubARB = extproc;

    glVertexAttrib4NubARB(index, x, y, z, w);    
}

static void APIENTRY InitVertexAttrib1svARB(GLuint index, const GLshort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1svARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1svARB = extproc;

    glVertexAttrib1svARB(index, v);    
}

static void APIENTRY InitVertexAttrib1fvARB(GLuint index, const GLfloat *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1fvARB = extproc;

    glVertexAttrib1fvARB(index, v);    
}

static void APIENTRY InitVertexAttrib1dvARB(GLuint index, const GLdouble *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib1dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib1dvARB = extproc;

    glVertexAttrib1dvARB(index, v);    
}

static void APIENTRY InitVertexAttrib2svARB(GLuint index, const GLshort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2svARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2svARB = extproc;

    glVertexAttrib2svARB(index, v);    
}

static void APIENTRY InitVertexAttrib2fvARB(GLuint index, const GLfloat *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2fvARB = extproc;

    glVertexAttrib2fvARB(index, v);    
}

static void APIENTRY InitVertexAttrib2dvARB(GLuint index, const GLdouble *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib2dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib2dvARB = extproc;

    glVertexAttrib2dvARB(index, v);    
}

static void APIENTRY InitVertexAttrib3svARB(GLuint index, const GLshort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3svARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3svARB = extproc;

    glVertexAttrib3svARB(index, v);    
}

static void APIENTRY InitVertexAttrib3fvARB(GLuint index, const GLfloat *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3fvARB = extproc;

    glVertexAttrib3fvARB(index, v);    
}

static void APIENTRY InitVertexAttrib3dvARB(GLuint index, const GLdouble *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib3dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib3dvARB = extproc;

    glVertexAttrib3dvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4bvARB(GLuint index, const GLbyte *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4bvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4bvARB = extproc;

    glVertexAttrib4bvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4svARB(GLuint index, const GLshort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4svARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4svARB = extproc;

    glVertexAttrib4svARB(index, v);    
}

static void APIENTRY InitVertexAttrib4ivARB(GLuint index, const GLint *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4ivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4ivARB = extproc;

    glVertexAttrib4ivARB(index, v);    
}

static void APIENTRY InitVertexAttrib4ubvARB(GLuint index, const GLubyte *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4ubvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4ubvARB = extproc;

    glVertexAttrib4ubvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4usvARB(GLuint index, const GLushort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4usvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4usvARB = extproc;

    glVertexAttrib4usvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4uivARB(GLuint index, const GLuint *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4uivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4uivARB = extproc;

    glVertexAttrib4uivARB(index, v);    
}

static void APIENTRY InitVertexAttrib4fvARB(GLuint index, const GLfloat *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4fvARB = extproc;

    glVertexAttrib4fvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4dvARB(GLuint index, const GLdouble *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4dvARB = extproc;

    glVertexAttrib4dvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NbvARB(GLuint index, const GLbyte *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NbvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NbvARB = extproc;

    glVertexAttrib4NbvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NsvARB(GLuint index, const GLshort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NsvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NsvARB = extproc;

    glVertexAttrib4NsvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NivARB(GLuint index, const GLint *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NivARB = extproc;

    glVertexAttrib4NivARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NubvARB(GLuint index, const GLubyte *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NubvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NubvARB = extproc;

    glVertexAttrib4NubvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NusvARB(GLuint index, const GLushort *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NusvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NusvARB = extproc;

    glVertexAttrib4NusvARB(index, v);    
}

static void APIENTRY InitVertexAttrib4NuivARB(GLuint index, const GLuint *v)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttrib4NuivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttrib4NuivARB = extproc;

    glVertexAttrib4NuivARB(index, v);    
}


static void APIENTRY InitVertexAttribPointerARB(GLuint index, GLint size, GLenum type, 
    GLboolean normalized, GLsizei stride, const void *pointer)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glVertexAttribPointerARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glVertexAttribPointerARB = extproc;

    glVertexAttribPointerARB(index, size, type, normalized, stride, pointer);    
}

static void APIENTRY InitEnableVertexAttribArrayARB(GLuint index)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glEnableVertexAttribArrayARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glEnableVertexAttribArrayARB = extproc;

    glEnableVertexAttribArrayARB(index);    
}

static void APIENTRY InitDisableVertexAttribArrayARB(GLuint index)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDisableVertexAttribArrayARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glDisableVertexAttribArrayARB = extproc;

    glDisableVertexAttribArrayARB(index);    
}

static void APIENTRY InitProgramStringARB(GLenum target, GLenum format, GLsizei len, 
    const void *string)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramStringARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramStringARB = extproc;

    glProgramStringARB(target, format, len, string);    
}

static void APIENTRY InitBindProgramARB(GLenum target, GLuint program)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glBindProgramARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glBindProgramARB = extproc;

    glBindProgramARB(target, program);    
}

static void APIENTRY InitDeleteProgramsARB(GLsizei n, const GLuint *programs)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glDeleteProgramsARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glDeleteProgramsARB = extproc;

    glDeleteProgramsARB(n, programs);    
}

static void APIENTRY InitGenProgramsARB(GLsizei n, GLuint *programs)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGenProgramsARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGenProgramsARB = extproc;

    glGenProgramsARB(n, programs);    
}

static void APIENTRY InitProgramEnvParameter4dARB(GLenum target, GLuint index,
    GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramEnvParameter4dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramEnvParameter4dARB = extproc;

    glProgramEnvParameter4dARB(target, index, x, y, z, w);    
}

static void APIENTRY InitProgramEnvParameter4dvARB(GLenum target, GLuint index,
    const GLdouble *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramEnvParameter4dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramEnvParameter4dvARB = extproc;

    glProgramEnvParameter4dvARB(target, index, params);    
}

static void APIENTRY InitProgramEnvParameter4fARB(GLenum target, GLuint index,
    GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramEnvParameter4fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramEnvParameter4fARB = extproc;

    glProgramEnvParameter4fARB(target, index, x, y, z, w);    
}

static void APIENTRY InitProgramEnvParameter4fvARB(GLenum target, GLuint index,
    const GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramEnvParameter4fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramEnvParameter4fvARB = extproc;

    glProgramEnvParameter4fvARB(target, index, params);    
}

static void APIENTRY InitProgramLocalParameter4dARB(GLenum target, GLuint index,
    GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramLocalParameter4dARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramLocalParameter4dARB = extproc;

    glProgramLocalParameter4dARB(target, index, x, y, z, w);    
}

static void APIENTRY InitProgramLocalParameter4dvARB(GLenum target, GLuint index,
    const GLdouble *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramLocalParameter4dvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramLocalParameter4dvARB = extproc;

    glProgramLocalParameter4dvARB(target, index, params);    
}

static void APIENTRY InitProgramLocalParameter4fARB(GLenum target, GLuint index,
    GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramLocalParameter4fARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramLocalParameter4fARB = extproc;

    glProgramLocalParameter4fARB(target, index, x, y, z, w);    
}

static void APIENTRY InitProgramLocalParameter4fvARB(GLenum target, GLuint index,
    const GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glProgramLocalParameter4fvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glProgramLocalParameter4fvARB = extproc;

    glProgramLocalParameter4fvARB(target, index, params);    
}

static void APIENTRY InitGetProgramEnvParameterdvARB(GLenum target, GLuint index,
    GLdouble *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramEnvParameterdvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramEnvParameterdvARB = extproc;

    glGetProgramEnvParameterdvARB(target, index, params);    
}

static void APIENTRY InitGetProgramEnvParameterfvARB(GLenum target, GLuint index, 
    GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramEnvParameterfvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramEnvParameterfvARB = extproc;

    glGetProgramEnvParameterfvARB(target, index, params);    
}
;
static void APIENTRY InitGetProgramLocalParameterdvARB(GLenum target, GLuint index,
    GLdouble *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramLocalParameterdvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramLocalParameterdvARB = extproc;

    glGetProgramLocalParameterdvARB(target, index, params);    
}

static void APIENTRY InitGetProgramLocalParameterfvARB(GLenum target, GLuint index, 
    GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramLocalParameterfvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramLocalParameterfvARB = extproc;

    glGetProgramLocalParameterfvARB(target, index, params);    
}

static void APIENTRY InitGetProgramivARB(GLenum target, GLenum pname, GLint *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramivARB = extproc;

    glGetProgramivARB(target, pname, params);    
}

static void APIENTRY InitGetProgramStringARB(GLenum target, GLenum pname, void *string)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetProgramStringARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetProgramStringARB = extproc;

    glGetProgramStringARB(target, pname, string);    
}

static void APIENTRY InitGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVertexAttribdvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetVertexAttribdvARB = extproc;

    glGetVertexAttribdvARB(index, pname, params);    
}

static void APIENTRY InitGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVertexAttribfvARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetVertexAttribfvARB = extproc;

    glGetVertexAttribfvARB(index, pname, params);    
}

static void APIENTRY InitGetVertexAttribivARB(GLuint index, GLenum pname, GLint *params)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVertexAttribivARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetVertexAttribivARB = extproc;

    glGetVertexAttribivARB(index, pname, params);    
}

static void APIENTRY InitGetVertexAttribPointervARB(GLuint index, GLenum pname, void **pointer)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glGetVertexAttribPointervARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return;
    }

    glGetVertexAttribPointervARB = extproc;

    glGetVertexAttribPointervARB(index, pname, pointer);    
}

static GLboolean APIENTRY InitIsProgramARB(GLuint program)
{
    void *extproc;

    extproc = (void *) wglGetProcAddress("glIsProgramARB");

    if (extproc == NULL ) {
        _ASSERT(0);
        return 0;
    }

    glIsProgramARB = extproc;

    return glIsProgramARB(program);    
}

#ifdef _WIN32

static HANDLE WINAPI InitCreateBufferRegionARB (HDC hDC, int iLayerPlane, UINT uType)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglCreateBufferRegionARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglCreateBufferRegionARB = extproc;

	return wglCreateBufferRegionARB(hDC, iLayerPlane, uType);
}

static VOID WINAPI InitDeleteBufferRegionARB (HANDLE hRegion)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglDeleteBufferRegionARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	wglDeleteBufferRegionARB = extproc;

	wglDeleteBufferRegionARB(hRegion);
}

static BOOL WINAPI InitSaveBufferRegionARB (HANDLE hRegion, int x, int y, int width, int height)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglSaveBufferRegionARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglSaveBufferRegionARB = extproc;

	return wglSaveBufferRegionARB(hRegion, x, y, width, height);
}

static BOOL WINAPI InitRestoreBufferRegionARB (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglRestoreBufferRegionARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglRestoreBufferRegionARB = extproc;

	return wglRestoreBufferRegionARB(hRegion, x, y, width, height, xSrc, ySrc);
}

static const char * WINAPI InitGetExtensionsStringARB (HDC hdc)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetExtensionsStringARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetExtensionsStringARB = extproc;

	return wglGetExtensionsStringARB(hdc);
}

static BOOL WINAPI InitGetPixelFormatAttribivARB (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, int *piValues)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPixelFormatAttribivARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPixelFormatAttribivARB = extproc;

	return wglGetPixelFormatAttribivARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues);
}

static BOOL WINAPI InitGetPixelFormatAttribfvARB (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int *piAttributes, FLOAT *pfValues)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPixelFormatAttribfvARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPixelFormatAttribfvARB = extproc;

	return wglGetPixelFormatAttribfvARB(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues);
}

static BOOL WINAPI InitChoosePixelFormatARB (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglChoosePixelFormatARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglChoosePixelFormatARB = extproc;

	return wglChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
}

static BOOL WINAPI InitMakeContextCurrentARB (HDC hDrawDC, HDC hReadDC, HGLRC hglrc)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglMakeContextCurrentARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglMakeContextCurrentARB = extproc;

	return wglMakeContextCurrentARB(hDrawDC, hReadDC, hglrc);
}

static HDC WINAPI InitGetCurrentReadDCARB (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetCurrentReadDCARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetCurrentReadDCARB = extproc;

	return wglGetCurrentReadDCARB();
}

static HPBUFFERARB WINAPI InitCreatePbufferARB (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglCreatePbufferARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglCreatePbufferARB = extproc;

	return wglCreatePbufferARB(hDC, iPixelFormat, iWidth, iHeight, piAttribList);
}

static HDC WINAPI InitGetPbufferDCARB (HPBUFFERARB hPbuffer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPbufferDCARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPbufferDCARB = extproc;

	return wglGetPbufferDCARB(hPbuffer);
}

static int WINAPI InitReleasePbufferDCARB (HPBUFFERARB hPbuffer, HDC hDC)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglReleasePbufferDCARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglReleasePbufferDCARB = extproc;

	return wglReleasePbufferDCARB(hPbuffer, hDC);
}

static BOOL WINAPI InitDestroyPbufferARB (HPBUFFERARB hPbuffer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglDestroyPbufferARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglDestroyPbufferARB = extproc;

	return wglDestroyPbufferARB(hPbuffer);
}

static BOOL WINAPI InitQueryPbufferARB (HPBUFFERARB hPbuffer, int iAttribute, int *piValue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglQueryPbufferARB");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglQueryPbufferARB = extproc;

	return wglQueryPbufferARB(hPbuffer, iAttribute, piValue);
}

static GLboolean WINAPI InitCreateDisplayColorTableEXT (GLushort id)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglCreateDisplayColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglCreateDisplayColorTableEXT = extproc;

	return wglCreateDisplayColorTableEXT(id);
}

static GLboolean WINAPI InitLoadDisplayColorTableEXT (const GLushort *table, GLuint length)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglLoadDisplayColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglLoadDisplayColorTableEXT = extproc;

	return wglLoadDisplayColorTableEXT(table, length);
}

static GLboolean WINAPI InitBindDisplayColorTableEXT (GLushort id)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglBindDisplayColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglBindDisplayColorTableEXT = extproc;

	return wglBindDisplayColorTableEXT(id);
}

static VOID WINAPI InitDestroyDisplayColorTableEXT (GLushort id)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglDestroyDisplayColorTableEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return;
	}

	wglDestroyDisplayColorTableEXT = extproc;

	wglDestroyDisplayColorTableEXT(id);
}

static const char * WINAPI InitGetExtensionsStringEXT (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetExtensionsStringEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetExtensionsStringEXT = extproc;

	return wglGetExtensionsStringEXT();
}

static BOOL WINAPI InitMakeContextCurrentEXT (HDC hDrawDC, HDC hReadDC, HGLRC hglrc)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglMakeContextCurrentEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglMakeContextCurrentEXT = extproc;

	return wglMakeContextCurrentEXT(hDrawDC, hReadDC, hglrc);
}

static HDC WINAPI InitGetCurrentReadDCEXT (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetCurrentReadDCEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetCurrentReadDCEXT = extproc;

	return wglGetCurrentReadDCEXT();
}

static HPBUFFEREXT WINAPI InitCreatePbufferEXT (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int *piAttribList)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglCreatePbufferEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglCreatePbufferEXT = extproc;

	return wglCreatePbufferEXT(hDC, iPixelFormat, iWidth, iHeight, piAttribList);
}

static HDC WINAPI InitGetPbufferDCEXT (HPBUFFEREXT hPbuffer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPbufferDCEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPbufferDCEXT = extproc;

	return wglGetPbufferDCEXT(hPbuffer);
}

static int WINAPI InitReleasePbufferDCEXT (HPBUFFEREXT hPbuffer, HDC hDC)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglReleasePbufferDCEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglReleasePbufferDCEXT = extproc;

	return wglReleasePbufferDCEXT(hPbuffer, hDC);
}

static BOOL WINAPI InitDestroyPbufferEXT (HPBUFFEREXT hPbuffer)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglDestroyPbufferEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglDestroyPbufferEXT = extproc;

	return wglDestroyPbufferEXT(hPbuffer);
}

static BOOL WINAPI InitQueryPbufferEXT (HPBUFFEREXT hPbuffer, int iAttribute, int *piValue)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglQueryPbufferEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglQueryPbufferEXT = extproc;

	return wglQueryPbufferEXT(hPbuffer, iAttribute, piValue);
}

static BOOL WINAPI InitGetPixelFormatAttribivEXT (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, int *piValues)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPixelFormatAttribivEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPixelFormatAttribivEXT = extproc;

	return wglGetPixelFormatAttribivEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues);
}

static BOOL WINAPI InitGetPixelFormatAttribfvEXT (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int *piAttributes, FLOAT *pfValues)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetPixelFormatAttribfvEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetPixelFormatAttribfvEXT = extproc;

	return wglGetPixelFormatAttribfvEXT(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues);
}

static BOOL WINAPI InitChoosePixelFormatEXT (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglChoosePixelFormatEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglChoosePixelFormatEXT = extproc;

	return wglChoosePixelFormatEXT(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
}

static BOOL WINAPI InitSwapIntervalEXT (int interval)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglSwapIntervalEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglSwapIntervalEXT = extproc;

	return wglSwapIntervalEXT(interval);
}

static int WINAPI InitGetSwapIntervalEXT (void)
{
	void *extproc;

	extproc = (void *) wglGetProcAddress("wglGetSwapIntervalEXT");

	if (extproc == NULL) {
		_ASSERT(0);
		return 0;
	}

	wglGetSwapIntervalEXT = extproc;

	return wglGetSwapIntervalEXT();
}

#endif /* _WIN32 */

_GLextensionProcs _extensionProcs = {
	InitBlendColor,
	InitBlendEquation,
	InitDrawRangeElements,
	InitColorTable,
	InitColorTableParameterfv,
	InitColorTableParameteriv,
	InitCopyColorTable,
	InitGetColorTable,
	InitGetColorTableParameterfv,
	InitGetColorTableParameteriv,
	InitColorSubTable,
	InitCopyColorSubTable,
	InitConvolutionFilter1D,
	InitConvolutionFilter2D,
	InitConvolutionParameterf,
	InitConvolutionParameterfv,
	InitConvolutionParameteri,
	InitConvolutionParameteriv,
	InitCopyConvolutionFilter1D,
	InitCopyConvolutionFilter2D,
	InitGetConvolutionFilter,
	InitGetConvolutionParameterfv,
	InitGetConvolutionParameteriv,
	InitGetSeparableFilter,
	InitSeparableFilter2D,
	InitGetHistogram,
	InitGetHistogramParameterfv,
	InitGetHistogramParameteriv,
	InitGetMinmax,
	InitGetMinmaxParameterfv,
	InitGetMinmaxParameteriv,
	InitHistogram,
	InitMinmax,
	InitResetHistogram,
	InitResetMinmax,
	InitTexImage3D,
	InitTexSubImage3D,
	InitCopyTexSubImage3D,
	InitActiveTexture,
	InitClientActiveTexture,
	InitMultiTexCoord1d,
	InitMultiTexCoord1dv,
	InitMultiTexCoord1f,
	InitMultiTexCoord1fv,
	InitMultiTexCoord1i,
	InitMultiTexCoord1iv,
	InitMultiTexCoord1s,
	InitMultiTexCoord1sv,
	InitMultiTexCoord2d,
	InitMultiTexCoord2dv,
	InitMultiTexCoord2f,
	InitMultiTexCoord2fv,
	InitMultiTexCoord2i,
	InitMultiTexCoord2iv,
	InitMultiTexCoord2s,
	InitMultiTexCoord2sv,
	InitMultiTexCoord3d,
	InitMultiTexCoord3dv,
	InitMultiTexCoord3f,
	InitMultiTexCoord3fv,
	InitMultiTexCoord3i,
	InitMultiTexCoord3iv,
	InitMultiTexCoord3s,
	InitMultiTexCoord3sv,
	InitMultiTexCoord4d,
	InitMultiTexCoord4dv,
	InitMultiTexCoord4f,
	InitMultiTexCoord4fv,
	InitMultiTexCoord4i,
	InitMultiTexCoord4iv,
	InitMultiTexCoord4s,
	InitMultiTexCoord4sv,
	InitLoadTransposeMatrixf,
	InitLoadTransposeMatrixd,
	InitMultTransposeMatrixf,
	InitMultTransposeMatrixd,
	InitSampleCoverage,
	InitCompressedTexImage3D,
	InitCompressedTexImage2D,
	InitCompressedTexImage1D,
	InitCompressedTexSubImage3D,
	InitCompressedTexSubImage2D,
	InitCompressedTexSubImage1D,
	InitGetCompressedTexImage,
	InitActiveTextureARB,
	InitClientActiveTextureARB,
	InitMultiTexCoord1dARB,
	InitMultiTexCoord1dvARB,
	InitMultiTexCoord1fARB,
	InitMultiTexCoord1fvARB,
	InitMultiTexCoord1iARB,
	InitMultiTexCoord1ivARB,
	InitMultiTexCoord1sARB,
	InitMultiTexCoord1svARB,
	InitMultiTexCoord2dARB,
	InitMultiTexCoord2dvARB,
	InitMultiTexCoord2fARB,
	InitMultiTexCoord2fvARB,
	InitMultiTexCoord2iARB,
	InitMultiTexCoord2ivARB,
	InitMultiTexCoord2sARB,
	InitMultiTexCoord2svARB,
	InitMultiTexCoord3dARB,
	InitMultiTexCoord3dvARB,
	InitMultiTexCoord3fARB,
	InitMultiTexCoord3fvARB,
	InitMultiTexCoord3iARB,
	InitMultiTexCoord3ivARB,
	InitMultiTexCoord3sARB,
	InitMultiTexCoord3svARB,
	InitMultiTexCoord4dARB,
	InitMultiTexCoord4dvARB,
	InitMultiTexCoord4fARB,
	InitMultiTexCoord4fvARB,
	InitMultiTexCoord4iARB,
	InitMultiTexCoord4ivARB,
	InitMultiTexCoord4sARB,
	InitMultiTexCoord4svARB,
	InitLoadTransposeMatrixfARB,
	InitLoadTransposeMatrixdARB,
	InitMultTransposeMatrixfARB,
	InitMultTransposeMatrixdARB,
	InitSampleCoverageARB,
	InitCompressedTexImage3DARB,
	InitCompressedTexImage2DARB,
	InitCompressedTexImage1DARB,
	InitCompressedTexSubImage3DARB,
	InitCompressedTexSubImage2DARB,
	InitCompressedTexSubImage1DARB,
	InitGetCompressedTexImageARB,
	InitWeightbvARB,
	InitWeightsvARB,
	InitWeightivARB,
	InitWeightfvARB,
	InitWeightdvARB,
	InitWeightubvARB,
	InitWeightusvARB,
	InitWeightuivARB,
	InitWeightPointerARB,
	InitVertexBlendARB,
	InitCurrentPaletteMatrixARB,
	InitMatrixIndexubvARB,
	InitMatrixIndexusvARB,
	InitMatrixIndexuivARB,
	InitMatrixIndexPointerARB,
	InitBlendColorEXT,
	InitPolygonOffsetEXT,
	InitTexImage3DEXT,
	InitTexSubImage3DEXT,
	InitGetTexFilterFuncSGIS,
	InitTexFilterFuncSGIS,
	InitTexSubImage1DEXT,
	InitTexSubImage2DEXT,
	InitCopyTexImage1DEXT,
	InitCopyTexImage2DEXT,
	InitCopyTexSubImage1DEXT,
	InitCopyTexSubImage2DEXT,
	InitCopyTexSubImage3DEXT,
	InitGetHistogramEXT,
	InitGetHistogramParameterfvEXT,
	InitGetHistogramParameterivEXT,
	InitGetMinmaxEXT,
	InitGetMinmaxParameterfvEXT,
	InitGetMinmaxParameterivEXT,
	InitHistogramEXT,
	InitMinmaxEXT,
	InitResetHistogramEXT,
	InitResetMinmaxEXT,
	InitConvolutionFilter1DEXT,
	InitConvolutionFilter2DEXT,
	InitConvolutionParameterfEXT,
	InitConvolutionParameterfvEXT,
	InitConvolutionParameteriEXT,
	InitConvolutionParameterivEXT,
	InitCopyConvolutionFilter1DEXT,
	InitCopyConvolutionFilter2DEXT,
	InitGetConvolutionFilterEXT,
	InitGetConvolutionParameterfvEXT,
	InitGetConvolutionParameterivEXT,
	InitGetSeparableFilterEXT,
	InitSeparableFilter2DEXT,
	InitColorTableSGI,
	InitColorTableParameterfvSGI,
	InitColorTableParameterivSGI,
	InitCopyColorTableSGI,
	InitGetColorTableSGI,
	InitGetColorTableParameterfvSGI,
	InitGetColorTableParameterivSGI,
	InitPixelTexGenSGIX,
	InitPixelTexGenParameteriSGIS,
	InitPixelTexGenParameterivSGIS,
	InitPixelTexGenParameterfSGIS,
	InitPixelTexGenParameterfvSGIS,
	InitGetPixelTexGenParameterivSGIS,
	InitGetPixelTexGenParameterfvSGIS,
	InitTexImage4DSGIS,
	InitTexSubImage4DSGIS,
	InitAreTexturesResidentEXT,
	InitBindTextureEXT,
	InitDeleteTexturesEXT,
	InitGenTexturesEXT,
	InitIsTextureEXT,
	InitPrioritizeTexturesEXT,
	InitDetailTexFuncSGIS,
	InitGetDetailTexFuncSGIS,
	InitSharpenTexFuncSGIS,
	InitGetSharpenTexFuncSGIS,
	InitSampleMaskSGIS,
	InitSamplePatternSGIS,
	InitArrayElementEXT,
	InitColorPointerEXT,
	InitDrawArraysEXT,
	InitEdgeFlagPointerEXT,
	InitGetPointervEXT,
	InitIndexPointerEXT,
	InitNormalPointerEXT,
	InitTexCoordPointerEXT,
	InitVertexPointerEXT,
	InitBlendEquationEXT,
	InitSpriteParameterfSGIX,
	InitSpriteParameterfvSGIX,
	InitSpriteParameteriSGIX,
	InitSpriteParameterivSGIX,
	InitPointParameterfARB,
	InitPointParameterfvARB,
	InitPointParameterfEXT,
	InitPointParameterfvEXT,
	InitPointParameterfSGIS,
	InitPointParameterfvSGIS,
	InitGetInstrumentsSGIX,
	InitInstrumentsBufferSGIX,
	InitPollInstrumentsSGIX,
	InitReadInstrumentsSGIX,
	InitStartInstrumentsSGIX,
	InitStopInstrumentsSGIX,
	InitFrameZoomSGIX,
	InitTagSampleBufferSGIX,
	InitDeformationMap3dSGIX,
	InitDeformationMap3fSGIX,
	InitDeformSGIX,
	InitLoadIdentityDeformationMapSGIX,
	InitReferencePlaneSGIX,
	InitFlushRasterSGIX,
	InitFogFuncSGIS,
	InitGetFogFuncSGIS,
	InitImageTransformParameteriHP,
	InitImageTransformParameterfHP,
	InitImageTransformParameterivHP,
	InitImageTransformParameterfvHP,
	InitGetImageTransformParameterivHP,
	InitGetImageTransformParameterfvHP,
	InitColorSubTableEXT,
	InitCopyColorSubTableEXT,
	InitHintPGI,
	InitColorTableEXT,
	InitGetColorTableEXT,
	InitGetColorTableParameterivEXT,
	InitGetColorTableParameterfvEXT,
	InitGetListParameterfvSGIX,
	InitGetListParameterivSGIX,
	InitListParameterfSGIX,
	InitListParameterfvSGIX,
	InitListParameteriSGIX,
	InitListParameterivSGIX,
	InitIndexMaterialEXT,
	InitIndexFuncEXT,
	InitLockArraysEXT,
	InitUnlockArraysEXT,
	InitCullParameterdvEXT,
	InitCullParameterfvEXT,
	InitFragmentColorMaterialSGIX,
	InitFragmentLightfSGIX,
	InitFragmentLightfvSGIX,
	InitFragmentLightiSGIX,
	InitFragmentLightivSGIX,
	InitFragmentLightModelfSGIX,
	InitFragmentLightModelfvSGIX,
	InitFragmentLightModeliSGIX,
	InitFragmentLightModelivSGIX,
	InitFragmentMaterialfSGIX,
	InitFragmentMaterialfvSGIX,
	InitFragmentMaterialiSGIX,
	InitFragmentMaterialivSGIX,
	InitGetFragmentLightfvSGIX,
	InitGetFragmentLightivSGIX,
	InitGetFragmentMaterialfvSGIX,
	InitGetFragmentMaterialivSGIX,
	InitLightEnviSGIX,
	InitDrawRangeElementsEXT,
	InitApplyTextureEXT,
	InitTextureLightEXT,
	InitTextureMaterialEXT,
	InitAsyncMarkerSGIX,
	InitFinishAsyncSGIX,
	InitPollAsyncSGIX,
	InitGenAsyncMarkersSGIX,
	InitDeleteAsyncMarkersSGIX,
	InitIsAsyncMarkerSGIX,
	InitVertexPointervINTEL,
	InitNormalPointervINTEL,
	InitColorPointervINTEL,
	InitTexCoordPointervINTEL,
	InitPixelTransformParameteriEXT,
	InitPixelTransformParameterfEXT,
	InitPixelTransformParameterivEXT,
	InitPixelTransformParameterfvEXT,
	InitSecondaryColor3bEXT,
	InitSecondaryColor3bvEXT,
	InitSecondaryColor3dEXT,
	InitSecondaryColor3dvEXT,
	InitSecondaryColor3fEXT,
	InitSecondaryColor3fvEXT,
	InitSecondaryColor3iEXT,
	InitSecondaryColor3ivEXT,
	InitSecondaryColor3sEXT,
	InitSecondaryColor3svEXT,
	InitSecondaryColor3ubEXT,
	InitSecondaryColor3ubvEXT,
	InitSecondaryColor3uiEXT,
	InitSecondaryColor3uivEXT,
	InitSecondaryColor3usEXT,
	InitSecondaryColor3usvEXT,
	InitSecondaryColorPointerEXT,
	InitTextureNormalEXT,
	InitMultiDrawArraysEXT,
	InitMultiDrawElementsEXT,
	InitFogCoordfEXT,
	InitFogCoordfvEXT,
	InitFogCoorddEXT,
	InitFogCoorddvEXT,
	InitFogCoordPointerEXT,
	InitTangent3bEXT,
	InitTangent3bvEXT,
	InitTangent3dEXT,
	InitTangent3dvEXT,
	InitTangent3fEXT,
	InitTangent3fvEXT,
	InitTangent3iEXT,
	InitTangent3ivEXT,
	InitTangent3sEXT,
	InitTangent3svEXT,
	InitBinormal3bEXT,
	InitBinormal3bvEXT,
	InitBinormal3dEXT,
	InitBinormal3dvEXT,
	InitBinormal3fEXT,
	InitBinormal3fvEXT,
	InitBinormal3iEXT,
	InitBinormal3ivEXT,
	InitBinormal3sEXT,
	InitBinormal3svEXT,
	InitTangentPointerEXT,
	InitBinormalPointerEXT,
	InitFinishTextureSUNX,
	InitGlobalAlphaFactorbSUN,
	InitGlobalAlphaFactorsSUN,
	InitGlobalAlphaFactoriSUN,
	InitGlobalAlphaFactorfSUN,
	InitGlobalAlphaFactordSUN,
	InitGlobalAlphaFactorubSUN,
	InitGlobalAlphaFactorusSUN,
	InitGlobalAlphaFactoruiSUN,
	InitReplacementCodeuiSUN,
	InitReplacementCodeusSUN,
	InitReplacementCodeubSUN,
	InitReplacementCodeuivSUN,
	InitReplacementCodeusvSUN,
	InitReplacementCodeubvSUN,
	InitReplacementCodePointerSUN,
	InitColor4ubVertex2fSUN,
	InitColor4ubVertex2fvSUN,
	InitColor4ubVertex3fSUN,
	InitColor4ubVertex3fvSUN,
	InitColor3fVertex3fSUN,
	InitColor3fVertex3fvSUN,
	InitNormal3fVertex3fSUN,
	InitNormal3fVertex3fvSUN,
	InitColor4fNormal3fVertex3fSUN,
	InitColor4fNormal3fVertex3fvSUN,
	InitTexCoord2fVertex3fSUN,
	InitTexCoord2fVertex3fvSUN,
	InitTexCoord4fVertex4fSUN,
	InitTexCoord4fVertex4fvSUN,
	InitTexCoord2fColor4ubVertex3fSUN,
	InitTexCoord2fColor4ubVertex3fvSUN,
	InitTexCoord2fColor3fVertex3fSUN,
	InitTexCoord2fColor3fVertex3fvSUN,
	InitTexCoord2fNormal3fVertex3fSUN,
	InitTexCoord2fNormal3fVertex3fvSUN,
	InitTexCoord2fColor4fNormal3fVertex3fSUN,
	InitTexCoord2fColor4fNormal3fVertex3fvSUN,
	InitTexCoord4fColor4fNormal3fVertex4fSUN,
	InitTexCoord4fColor4fNormal3fVertex4fvSUN,
	InitReplacementCodeuiVertex3fSUN,
	InitReplacementCodeuiVertex3fvSUN,
	InitReplacementCodeuiColor4ubVertex3fSUN,
	InitReplacementCodeuiColor4ubVertex3fvSUN,
	InitReplacementCodeuiColor3fVertex3fSUN,
	InitReplacementCodeuiColor3fVertex3fvSUN,
	InitReplacementCodeuiNormal3fVertex3fSUN,
	InitReplacementCodeuiNormal3fVertex3fvSUN,
	InitReplacementCodeuiColor4fNormal3fVertex3fSUN,
	InitReplacementCodeuiColor4fNormal3fVertex3fvSUN,
	InitReplacementCodeuiTexCoord2fVertex3fSUN,
	InitReplacementCodeuiTexCoord2fVertex3fvSUN,
	InitReplacementCodeuiTexCoord2fNormal3fVertex3fSUN,
	InitReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN,
	InitReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN,
	InitReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN,
	InitBlendFuncSeparateEXT,
	InitBlendFuncSeparateINGR,
	InitVertexWeightfEXT,
	InitVertexWeightfvEXT,
	InitVertexWeightPointerEXT,
	InitFlushVertexArrayRangeNV,
	InitVertexArrayRangeNV,
	InitCombinerParameterfvNV,
	InitCombinerParameterfNV,
	InitCombinerParameterivNV,
	InitCombinerParameteriNV,
	InitCombinerInputNV,
	InitCombinerOutputNV,
	InitFinalCombinerInputNV,
	InitGetCombinerInputParameterfvNV,
	InitGetCombinerInputParameterivNV,
	InitGetCombinerOutputParameterfvNV,
	InitGetCombinerOutputParameterivNV,
	InitGetFinalCombinerInputParameterfvNV,
	InitGetFinalCombinerInputParameterivNV,
	InitResizeBuffersMESA,
	InitWindowPos2dMESA,
	InitWindowPos2dvMESA,
	InitWindowPos2fMESA,
	InitWindowPos2fvMESA,
	InitWindowPos2iMESA,
	InitWindowPos2ivMESA,
	InitWindowPos2sMESA,
	InitWindowPos2svMESA,
	InitWindowPos3dMESA,
	InitWindowPos3dvMESA,
	InitWindowPos3fMESA,
	InitWindowPos3fvMESA,
	InitWindowPos3iMESA,
	InitWindowPos3ivMESA,
	InitWindowPos3sMESA,
	InitWindowPos3svMESA,
	InitWindowPos4dMESA,
	InitWindowPos4dvMESA,
	InitWindowPos4fMESA,
	InitWindowPos4fvMESA,
	InitWindowPos4iMESA,
	InitWindowPos4ivMESA,
	InitWindowPos4sMESA,
	InitWindowPos4svMESA,
	InitMultiModeDrawArraysIBM,
	InitMultiModeDrawElementsIBM,
	InitColorPointerListIBM,
	InitSecondaryColorPointerListIBM,
	InitEdgeFlagPointerListIBM,
	InitFogCoordPointerListIBM,
	InitIndexPointerListIBM,
	InitNormalPointerListIBM,
	InitTexCoordPointerListIBM,
	InitVertexPointerListIBM,
	InitTbufferMask3DFX,
	InitSampleMaskEXT,
	InitSamplePatternEXT,
	InitTextureColorMaskSGIS,
	InitIglooInterfaceSGIX,
	InitGenFencesNV,
	InitDeleteFencesNV,
	InitSetFenceNV,
	InitTestFenceNV,
	InitFinishFenceNV,
	InitIsFenceNV,
	InitGetFenceivNV,
	InitMapControlPointsNV,
	InitMapParameterivNV,
	InitMapParameterfvNV,
	InitGetMapControlPointsNV,
	InitGetMapParameterivNV,
	InitGetMapParameterfvNV,
	InitGetMapAttribParameterivNV,
	InitGetMapAttribParameterfvNV,
	InitEvalMapsNV,
	InitCombinerStageParameterfvNV,
	InitGetCombinerStageParameterfvNV,
	InitBindProgramNV,
	InitDeleteProgramsNV,
	InitExecuteProgramNV,
	InitGenProgramsNV,
	InitAreProgramsResidentNV,
	InitRequestResidentProgramsNV,
	InitGetProgramParameterfvNV,
	InitGetProgramParameterdvNV,
	InitGetProgramivNV,
	InitGetProgramStringNV,
	InitGetTrackMatrixivNV,
	InitGetVertexAttribdvNV,
	InitGetVertexAttribfvNV,
	InitGetVertexAttribivNV,
	InitGetVertexAttribPointervNV,
	InitIsProgramNV,
	InitLoadProgramNV,
	InitProgramParameter4fNV,
	InitProgramParameter4dNV,
	InitProgramParameter4dvNV,
	InitProgramParameter4fvNV,
	InitProgramParameters4dvNV,
	InitProgramParameters4fvNV,
	InitTrackMatrixNV,
	InitVertexAttribPointerNV,
	InitVertexAttrib1sNV,
	InitVertexAttrib1fNV,
	InitVertexAttrib1dNV,
	InitVertexAttrib2sNV,
	InitVertexAttrib2fNV,
	InitVertexAttrib2dNV,
	InitVertexAttrib3sNV,
	InitVertexAttrib3fNV,
	InitVertexAttrib3dNV,
	InitVertexAttrib4sNV,
	InitVertexAttrib4fNV,
	InitVertexAttrib4dNV,
	InitVertexAttrib4ubNV,
	InitVertexAttrib1svNV,
	InitVertexAttrib1fvNV,
	InitVertexAttrib1dvNV,
	InitVertexAttrib2svNV,
	InitVertexAttrib2fvNV,
	InitVertexAttrib2dvNV,
	InitVertexAttrib3svNV,
	InitVertexAttrib3fvNV,
	InitVertexAttrib3dvNV,
	InitVertexAttrib4svNV,
	InitVertexAttrib4fvNV,
	InitVertexAttrib4dvNV,
	InitVertexAttrib4ubvNV,
	InitVertexAttribs1svNV,
	InitVertexAttribs1fvNV,
	InitVertexAttribs1dvNV,
	InitVertexAttribs2svNV,
	InitVertexAttribs2fvNV,
	InitVertexAttribs2dvNV,
	InitVertexAttribs3svNV,
	InitVertexAttribs3fvNV,
	InitVertexAttribs3dvNV,
	InitVertexAttribs4svNV,
	InitVertexAttribs4fvNV,
	InitVertexAttribs4dvNV,
	InitVertexAttribs4ubvNV,
	InitAddSwapHintRectWIN,
    InitTexBumpParameterivATI,
    InitTexBumpParameterfvATI,
    InitGetTexBumpParameterivATI,
    InitGetTexBumpParameterfvATI,
    InitGenFragmentShadersATI,
    InitBindFragmentShaderATI,
    InitDeleteFragmentShaderATI,
    InitBeginFragmentShaderATI,
    InitEndFragmentShaderATI,
    InitPassTexCoordATI,
    InitSampleMapATI,
    InitColorFragmentOp1ATI,
    InitColorFragmentOp2ATI,
    InitColorFragmentOp3ATI,
    InitAlphaFragmentOp1ATI,
    InitAlphaFragmentOp2ATI,
    InitAlphaFragmentOp3ATI,
    InitSetFragmentShaderConstantATI,
    InitPNTrianglesiATI,
    InitPNTrianglesfATI,
    InitNewObjectBufferATI,
    InitIsObjectBufferATI,
    InitUpdateObjectBufferATI,
    InitGetObjectBufferfvATI,
    InitGetObjectBufferivATI,
    InitDeleteObjectBufferATI,
    InitArrayObjectATI,
    InitGetArrayObjectfvATI,
    InitGetArrayObjectivATI,
    InitVariantArrayObjectATI,
    InitGetVariantArrayObjectfvATI,
    InitGetVariantArrayObjectivATI,
    InitBeginVertexShaderEXT,
    InitEndVertexShaderEXT,
    InitBindVertexShaderEXT,
    InitGenVertexShadersEXT,
    InitDeleteVertexShaderEXT,
    InitShaderOp1EXT,
    InitShaderOp2EXT,
    InitShaderOp3EXT,
    InitSwizzleEXT,
    InitWriteMaskEXT,
    InitInsertComponentEXT,
    InitExtractComponentEXT,
    InitGenSymbolsEXT,
    InitSetInvariantEXT,
    InitSetLocalConstantEXT,
    InitVariantbvEXT,
    InitVariantsvEXT,
    InitVariantivEXT,
    InitVariantfvEXT,
    InitVariantdvEXT,
    InitVariantubvEXT,
    InitVariantusvEXT,
    InitVariantuivEXT,
    InitVariantPointerEXT,
    InitEnableVariantClientStateEXT,
    InitDisableVariantClientStateEXT,
    InitBindLightParameterEXT,
    InitBindMaterialParameterEXT,
    InitBindTexGenParameterEXT,
    InitBindTextureUnitParameterEXT,
    InitBindParameterEXT,
    InitIsVariantEnabledEXT,
    InitGetVariantBooleanvEXT,
    InitGetVariantIntegervEXT,
    InitGetVariantFloatvEXT,
    InitGetVariantPointervEXT,
    InitGetInvariantBooleanvEXT,
    InitGetInvariantIntegervEXT,
    InitGetInvariantFloatvEXT,
    InitGetLocalConstantBooleanvEXT,
    InitGetLocalConstantIntegervEXT,
    InitGetLocalConstantFloatvEXT,
    InitVertexStream1s,
    InitVertexStream1sv,
    InitVertexStream1i,
    InitVertexStream1iv,
    InitVertexStream1f,
    InitVertexStream1fv,
    InitVertexStream1d,
    InitVertexStream1dv,
    InitVertexStream2s,
    InitVertexStream2sv,
    InitVertexStream2i,
    InitVertexStream2iv,
    InitVertexStream2f,
    InitVertexStream2fv,
    InitVertexStream2d,
    InitVertexStream2dv,
    InitVertexStream3s,
    InitVertexStream3sv,
    InitVertexStream3i,
    InitVertexStream3iv,
    InitVertexStream3f,
    InitVertexStream3fv,
    InitVertexStream3d,
    InitVertexStream3dv,
    InitVertexStream4s,
    InitVertexStream4sv,
    InitVertexStream4i,
    InitVertexStream4iv,
    InitVertexStream4f,
    InitVertexStream4fv,
    InitVertexStream4d,
    InitVertexStream4dv,
    InitNormalStream3b,
    InitNormalStream3bv,
    InitNormalStream3s,
    InitNormalStream3sv,
    InitNormalStream3i,
    InitNormalStream3iv,
    InitNormalStream3f,
    InitNormalStream3fv,
    InitNormalStream3d,
    InitNormalStream3dv,
    InitClientActiveVertexStream,
    InitVertexBlendEnvi,
    InitVertexBlendEnvf,
    InitVertexAttrib1sARB,
    InitVertexAttrib1fARB,
    InitVertexAttrib1dARB,
    InitVertexAttrib2sARB,
    InitVertexAttrib2fARB,
    InitVertexAttrib2dARB,
    InitVertexAttrib3sARB,
    InitVertexAttrib3fARB,
    InitVertexAttrib3dARB,
    InitVertexAttrib4sARB,
    InitVertexAttrib4fARB,
    InitVertexAttrib4dARB,
    InitVertexAttrib4NubARB,
    InitVertexAttrib1svARB,
    InitVertexAttrib1fvARB,
    InitVertexAttrib1dvARB,
    InitVertexAttrib2svARB,
    InitVertexAttrib2fvARB,
    InitVertexAttrib2dvARB,
    InitVertexAttrib3svARB,
    InitVertexAttrib3fvARB,
    InitVertexAttrib3dvARB,
    InitVertexAttrib4bvARB,
    InitVertexAttrib4svARB,
    InitVertexAttrib4ivARB,
    InitVertexAttrib4ubvARB,
    InitVertexAttrib4usvARB,
    InitVertexAttrib4uivARB,
    InitVertexAttrib4fvARB,
    InitVertexAttrib4dvARB,
    InitVertexAttrib4NbvARB,
    InitVertexAttrib4NsvARB,
    InitVertexAttrib4NivARB,
    InitVertexAttrib4NubvARB,
    InitVertexAttrib4NusvARB,
    InitVertexAttrib4NuivARB,
    InitVertexAttribPointerARB,
    InitEnableVertexAttribArrayARB,
    InitDisableVertexAttribArrayARB,
    InitProgramStringARB,
    InitBindProgramARB,
    InitDeleteProgramsARB,
    InitGenProgramsARB,
    InitProgramEnvParameter4dARB,
    InitProgramEnvParameter4dvARB,
    InitProgramEnvParameter4fARB,
    InitProgramEnvParameter4fvARB,
    InitProgramLocalParameter4dARB,
    InitProgramLocalParameter4dvARB,
    InitProgramLocalParameter4fARB,
    InitProgramLocalParameter4fvARB,
    InitGetProgramEnvParameterdvARB,
    InitGetProgramEnvParameterfvARB,
    InitGetProgramLocalParameterdvARB,
    InitGetProgramLocalParameterfvARB,
    InitGetProgramivARB,
    InitGetProgramStringARB,
    InitGetVertexAttribdvARB,
    InitGetVertexAttribfvARB,
    InitGetVertexAttribivARB,
    InitGetVertexAttribPointervARB,
    InitIsProgramARB,
#ifdef _WIN32
	InitCreateBufferRegionARB,
	InitDeleteBufferRegionARB,
	InitSaveBufferRegionARB,
	InitRestoreBufferRegionARB,
	InitGetExtensionsStringARB,
	InitGetPixelFormatAttribivARB,
	InitGetPixelFormatAttribfvARB,
	InitChoosePixelFormatARB,
	InitMakeContextCurrentARB,
	InitGetCurrentReadDCARB,
	InitCreatePbufferARB,
	InitGetPbufferDCARB,
	InitReleasePbufferDCARB,
	InitDestroyPbufferARB,
	InitQueryPbufferARB,
	InitCreateDisplayColorTableEXT,
	InitLoadDisplayColorTableEXT,
	InitBindDisplayColorTableEXT,
	InitDestroyDisplayColorTableEXT,
	InitGetExtensionsStringEXT,
	InitMakeContextCurrentEXT,
	InitGetCurrentReadDCEXT,
	InitCreatePbufferEXT,
	InitGetPbufferDCEXT,
	InitReleasePbufferDCEXT,
	InitDestroyPbufferEXT,
	InitQueryPbufferEXT,
	InitGetPixelFormatAttribivEXT,
	InitGetPixelFormatAttribfvEXT,
	InitChoosePixelFormatEXT,
	InitSwapIntervalEXT,
	InitGetSwapIntervalEXT,
#endif /* _WIN32 */
};
