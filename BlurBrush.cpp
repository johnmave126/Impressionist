//
// BlurBrush.cpp
//
// The implementation of Blur Brush. It is a kind of ImpBrush.
//

#include "Impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "BlurBrush.h"
#include "MedianKernel.h"

BlurBrush::BlurBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void BlurBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void BlurBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	ImpKernel* ker = new MedianKernel(pDoc, "Median Kernel", 5);
	int x, y, i, j, size = pDoc->getSize(), hSize = size >> 1;
	GLubyte col[4];

	if ( pDoc == NULL ) {
		printf( "BlurBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	glPointSize( 1.0f );
	glBegin( GL_POINTS );
	for(i = max(0, target.x - hSize); i < target.x + hSize && i < pDoc->m_nWidth; i++) {
		for(j = max(0, target.y - hSize); j < target.y + hSize && j < pDoc->m_nHeight; j++) {
			ker->applyFilter(col, pDoc->m_ucBitmap, pDoc->m_nWidth, pDoc->m_nHeight, i, j);
			col[3] = (int)(pDoc->getAlpha() * 255);
			glColor4ubv(col);
			glVertex2f(i, j);
		}
	}

	glEnd();
}

void BlurBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
