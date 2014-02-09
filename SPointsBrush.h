//
// SPointsBrush.h
//
// The header file for Scattered Points Brush. 
//

#ifndef SPOINTSBRUSH_H
#define SPOINTSBRUSH_H

#include "ImpBrush.h"

class SPointsBrush : public ImpBrush
{
public:
	SPointsBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif