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
	double angle = pDoc->getLineAngle() * 2 * PI / 360.0;
	int length = pDoc->getSize();
	int randx, randy, startx, starty, endx, endy;
	int nNumLines = irand(4) + 1;
	for(int i=0; i<nNumLines; i++) {
		randx = target.x - (frand() - 0.5) * length;
		randy = target.y - (frand() - 0.5) * pDoc->getLineWidth() / 2;
		startx = randx - length / 2 * cos(angle);
		starty = randy - length / 2 * sin(angle); 
		endx = randx + length / 2 * cos(angle); 
		endy = randy + length / 2 * sin(angle); 
		glBegin( GL_LINES );
			SetColor( source );
			glVertex2d( startx, starty);
			glVertex2d( endx, endy);
		glEnd();
	}
}