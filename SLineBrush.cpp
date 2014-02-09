#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SLineBrush.h"

extern float frand();

SLineBrush::SLineBrush( ImpressionistDoc* pDoc, char* name ) :
	LineBrush(pDoc,name)
{
}

void SLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "Scattered LineBrush::BrushMove  document is NULL\n" );
		return;
	}
	double angle = pDoc->getLineAngle() * 2 * PI / 360.0;
	int length = pDoc->getSize();
	int randx = target.x - (frand() - 0.5) * length;
	int randy = target.y - (frand() - 0.5) * pDoc->getLineWidth() / 2;
	int startx = randx - length / 2 * cos(angle);
	int starty = randy - length / 2 * sin(angle); 
	int endx = randx + length / 2 * cos(angle); 
	int endy = randy + length / 2 * sin(angle); 
	glBegin( GL_LINES );
		SetColor( source );
		glVertex2d( startx, starty);
		glVertex2d( endx, endy);
	glEnd();
}