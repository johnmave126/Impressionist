//
// BlurBrush.h
//
// The header file for Blur Brush. 
//

#ifndef BLURBRUSH_H
#define BLURBRUSH_H

#include "ImpBrush.h"

class BlurBrush : public ImpBrush
{
public:
	BlurBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
};

#endif