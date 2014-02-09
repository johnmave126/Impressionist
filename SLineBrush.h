#ifndef SLINEBRUSH_H
#define SLINEBRUSH_H

#include "LineBrush.h"

class SLineBrush : public LineBrush
{	
public:
	SLineBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );
	void BrushMove( const Point source, const Point target );
};

#endif