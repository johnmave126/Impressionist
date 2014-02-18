#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Util.h"
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
	m_cur = target;
	m_prev = target;
	BrushMove( source, target );
}

double LineBrush::getAngle(Point source) {
	ImpressionistDoc* pDoc = GetDocument();
	double angle = pDoc->getLineAngle()*2*PI/360.0;
	if(pDoc->m_nCurrentDirect == DIRECT_GRADIENT) {
		//caluate degree using gradient and perpendicular to it
		Point gradient = pDoc->GetGradient(source);
		int degree = util::calDegree(gradient.x, gradient.y);
		printf("gradient %d, %d, degree %d\n", gradient.x, gradient.y, degree);
		angle = util::degree2angle(degree + 90);
	} else if (pDoc->m_nCurrentDirect == DIRECT_BRUSH) {
		angle = util::calAngle(m_cur.x - m_prev.x, m_cur.y - m_prev.y);
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
	m_prev = m_cur;
	m_cur = target;
	double angle = getAngle(source);
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

