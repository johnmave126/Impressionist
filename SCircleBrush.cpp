//
// SCircleBrush.cpp
//
// The implementation of Scattered Circles Brush. It is a kind of ImpBrush.
//

#include "Impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SCircleBrush.h"
#include "DrawHelper.h"

extern float frand();
extern int irand(int max);

SCircleBrush::SCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void SCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	glPointSize( 1.0f );

	BrushMove( source, target );
}

void SCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int i, x, y,
		size = pDoc->getSize(),
		halfSize = size >> 1,
		nNumCir = irand(4) + 1;

	if ( pDoc == NULL ) {
		printf( "SCircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	for(i = 1; i <= nNumCir; i++) {
		x = target.x - halfSize + irand(size);
		y = target.y - halfSize + irand(size);
		SetColor(Point(x, y));
		DrawCircle(x, y, halfSize, true);
	}

}

void SCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
