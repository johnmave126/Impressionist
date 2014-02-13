#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SLineBrush.h"

extern float frand();
extern int irand(int max);

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
	double angle = getAngle(source);
	int length = pDoc->getSize();
	int randx, randy, startx, starty, endx, endy;
	int x, y;
	int nNumLines = irand(4) + 2;
	glBegin( GL_LINES );
	for(int i=0; i<nNumLines; i++) {
		randx = (frand() - 0.5) * length;
		randy = (frand() - 0.5) * length;
		x = target.x - randx;
		y = target.y - randy;
		SetColor(Point(x, y));
		startx = x - length / 2 * cos(angle);
		starty = y - length / 2 * sin(angle); 
		endx = x + length / 2 * cos(angle); 
		endy = y + length / 2 * sin(angle); 
		glVertex2d( startx, starty);
		glVertex2d( endx, endy);
	}
	glEnd();
}