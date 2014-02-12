//
// AlphaMappingBrush.cpp
//
// The implementation of Scattered Circles Brush. It is a kind of ImpBrush.
//

#include "Impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "AlphaMappingBrush.h"

#include <FL/fl_ask.H>

extern float frand();
extern int irand(int max);

AlphaMappingBrush::AlphaMappingBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void AlphaMappingBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void AlphaMappingBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int size = pDoc->getSize() >> 1;

	if(pDoc->m_ucMapping == NULL) {
		fl_alert("Please load alpha mapping brush first");
		return;
	}

	if ( pDoc == NULL ) {
		printf( "AlphaMappingBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pDoc->m_uMapTextureID);
	SetColor(source); 
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(target.x - size, target.y - size);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(target.x - size, target.y + size);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(target.x + size, target.y + size);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(target.x + size, target.y - size);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void AlphaMappingBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}
