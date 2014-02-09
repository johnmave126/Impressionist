//
// DrawHelper.cpp
//
// The file for helper functions of drawing. 
//

#include "DrawHelper.h"
#include <math.h>

void DrawCircle(double x, double y, double r, bool filled) {
	int i;
	const int dNumFan = 20;
	GLfloat delta = 2.0f * M_PI / dNumFan;

	if(filled) {
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(x, y);
		for(i = 0; i <= dNumFan; i++) {
			glVertex2d(x + r * cos(i * delta), y + r * sin(i * delta));
		}
		glEnd();
	}
	else {
		glBegin(GL_LINE_LOOP);
		for(i = 0; i <= dNumFan; i++) {
			glVertex2d(x + r * cos(i * delta), y + r * cos(i * delta));
		}
		glEnd();
	}
}

void DrawCircle(const Point p, double r, bool filled) {
	DrawCircle(p.x, p.y, r, filled);
}
