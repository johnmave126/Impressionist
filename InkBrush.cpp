#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Util.h"
#include "InkBrush.h"

extern float frand();
extern int irand(int max);

InkBrush::InkBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void InkBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	m_width = 0;
	m_cur = target;
	m_prev = target;
	BrushMove( source, target );
}


void InkBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "Scattered ImpBrush::BrushMove  document is NULL\n" );
		return;
	}
	m_prev = m_cur;
	m_cur = target;
	double angle = util::calAngle(m_cur.x - m_prev.x, m_cur.y - m_prev.y) + PI/2;
	if(m_width < MAX_WIDTH) m_width ++;

	SetColor(source);
	if(m_width == 1) {
		m_c = target;
		m_d = target;
	}
	m_a = m_d;
	m_b = m_c;
	m_c = Point(target.x + m_width / 2 * cos(angle),
		target.y + m_width / 2 * sin(angle)); 
	m_d = Point(target.x - m_width / 2 * cos(angle),
		target.y - m_width / 2 * sin(angle));
	glBegin( GL_POLYGON );
		glVertex2d(m_a.x, m_a.y);
		glVertex2d(m_b.x, m_b.y);
		glVertex2d(m_c.x, m_c.y);
		glVertex2d(m_d.x, m_d.y);
	glEnd();
}
	

void InkBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "Scattered ImpBrush::BrushMove  document is NULL\n" );
		return;
	}
	m_prev = m_cur;
	m_cur = target;
	int deltax = m_cur.x - m_prev.x;
	int deltay = m_cur.y - m_prev.y;
	double angle = util::calAngle(deltax, deltay) + PI/2;
	Point temp = target;
	while(m_width > 1) {
		m_width -= 2;
		SetColor(source);
		m_a = m_d;
		m_b = m_c;
		m_c = Point(temp.x + m_width / 2 * cos(angle),
			temp.y + m_width / 2 * sin(angle)); 
		m_d = Point(temp.x - m_width / 2 * cos(angle),
			temp.y - m_width / 2 * sin(angle));
		glBegin( GL_POLYGON );
			glVertex2d(m_a.x, m_a.y);
			glVertex2d(m_b.x, m_b.y);
			glVertex2d(m_c.x, m_c.y);
			glVertex2d(m_d.x, m_d.y);
		glEnd();
		temp.x += deltax;
		temp.y += deltay;
	}
}
