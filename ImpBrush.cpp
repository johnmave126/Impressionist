//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();
	int r, g, b, m;
	ucolor32 col = pDoc->getBlendColor();


	GLubyte color[4];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );

	// Blend the color
	UNPACK_COLOR(r, g, b, col);
	m = (r + g + b) / 3;
	if(m != 0) {
		r = (int)color[0] * r / m;
		g = (int)color[1] * g / m;
		b = (int)color[2] * b / m;
	}
	color[0] = (r > 255) ? 255 : (unsigned)r;
	color[1] = (g > 255) ? 255 : (unsigned)g;
	color[2] = (b > 255) ? 255 : (unsigned)b;

	//Alpha
	color[3] = (int)(pDoc->getAlpha() * 255);
 
	glColor4ubv( color );

}