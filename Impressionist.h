#ifndef IMPRESSIONIST_H
#define IMPRESSIONIST_H
#define SAMPLE_SOLUTION
#include <stdio.h>

#include <FL/Fl.h>
#include <FL/gl.h>
#include <GL/glu.h>

#include "ImpBrush.h"

#define TRUE	1
#define FALSE	0

#ifdef WIN32
#define M_PI	3.1415926535F
#endif

typedef UINT32 ucolor32;
#define PACK_COLOR(r, g, b)	((r) | ((g) << 8) | ((b) << 16))
#define UNPACK_COLOR(r, g, b, col) \
		(r = col & 0xFF, g = (col >> 8) & 0xFF, b = (col >> 16) & 0xFF, col)

#endif