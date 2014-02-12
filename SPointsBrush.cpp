//
// SPointsBrush.cpp
//
// The implementation of Scattered Points Brush. It is a kind of ImpBrush.
//

#include "Impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SPointsBrush.h"
#include <math.h>

extern float frand();
extern int irand(int max);

SPointsBrush::SPointsBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void SPointsBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void SPointsBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int x, y, i, j, size = pDoc->getSize();

	if ( pDoc == NULL ) {
		printf( "SPointsBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	glPointSize( 1.0f );
	glBegin( GL_POINTS );

		for(x = target.x - (size >> 1), i = 0; i <= size; i++, x++) {
			for(y = target.y - (size >> 1), j = 0; j <= size; j++, y++) {
				if(!irand(5)) { // Make it more scattered
					SetColor( Point(x, y) );
					glVertex2d(x, y);
				}
			}
		}


	glEnd();
}

void SPointsBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
