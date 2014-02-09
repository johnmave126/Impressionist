//
// DrawHelper.h
//
// The header file for helper functions of drawing. 
//

#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include "Impressionist.h"
#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"

/*
 * DrawCircle
 *
 * Draw a circle
 *
 * param x, The x-coord of center
 * param y, The y-coord of center
 * param r, The radius of the circle
 * param filled, True if the circle to be filled
 */
void DrawCircle(double x, double y, double r, bool filled);

#endif