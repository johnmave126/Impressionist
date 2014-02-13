#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int width = pDoc->getLineWidth();
	glLineWidth( (float)width );

	BrushMove( source, target );
}

double LineBrush::getAngle() {
	ImpressionistDoc* pDoc = GetDocument();
	double angle;
	if(pDoc->m_nCurrentDirect == DIRECT_GRADIENT) {
		//to do....
		angle = pDoc->getLineAngle()*2*PI/360.0;
	} else if (pDoc->m_nCurrentDirect == DIRECT_SLIDER) {
		angle = pDoc->getLineAngle()*2*PI/360.0;
	}
	return angle;
}
		
void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	double angle = getAngle();
	
	int length = pDoc->getSize();
	int startx = target.x - length/2 * cos(angle);
	int starty = target.y - length/2 * sin(angle); 
	int endx = target.x + length/2 * cos(angle); 
	int endy = target.y + length/2 * sin(angle); 
	glBegin( GL_LINES );
		SetColor( source );
		glVertex2d( startx, starty);
		glVertex2d( endx, endy);
	glEnd();
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

