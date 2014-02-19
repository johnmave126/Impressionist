#ifndef INKBRUSH_H
#define INKBRUSH_H

#include "ImpBrush.h"

class InkBrush : public ImpBrush
{	
public:
	InkBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );
	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	static const int MAX_WIDTH = 20;
private:
	Point m_cur, m_prev;
	//four point of a polygon
	Point m_a, m_b, m_c, m_d; 
	int m_width;
};

#endif