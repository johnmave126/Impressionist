//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush.
//

#include "Impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <math.h>

extern float frand();

CircleBrush::CircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void CircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void CircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int i, size = pDoc->getSize() >> 1;
	const int dNumFan = 20;
	GLfloat delta = 2.0f * M_PI / dNumFan;

	if ( pDoc == NULL ) {
		printf( "CircleBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	glBegin( GL_TRIANGLE_FAN );
		SetColor( source );

		glVertex2d( target.x, target.y );
		for(i = 0; i <= dNumFan; i++) {
			glVertex2d(target.x + size * cos(i * delta), target.y + size * sin(i * delta));
		}

	glEnd();
}

void CircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

