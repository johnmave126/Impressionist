//
// SCircleBrush.h
//
// The header file for Scattered Circles Brush. 
//

#ifndef SCIRCLEBRUSH_H
#define SCIRCLEBRUSH_H

#include "ImpBrush.h"

class SCircleBrush : public ImpBrush
{
public:
	SCircleBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif