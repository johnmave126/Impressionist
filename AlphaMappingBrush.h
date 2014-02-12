//
// AlphaMappingBrush.h
//
// The header file for Alpha Mapping Brush. 
//

#ifndef ALPHAMAPPINGBRUSH_H
#define ALPHAMAPPINGBRUSH_H

#include "ImpBrush.h"

class AlphaMappingBrush : public ImpBrush
{
public:
	AlphaMappingBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );

	GLuint tex;
};

#endif