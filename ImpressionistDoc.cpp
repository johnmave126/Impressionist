// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "SPointsBrush.h"
#include "SLineBrush.h"
#include "SCircleBrush.h"
#include "AlphaMappingBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	
	m_alphaMappingName[0] = '\0';

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_nMappingWidth = -1;
	m_ucMapping = NULL;
	m_nGrayImg	= NULL;

	m_lastPoint = Point(-1, -1);
	m_curPoint = Point(-1, -1);

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new SPointsBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new SLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new SCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_ALPHA_MAPPING]	
		= new AlphaMappingBrush( this, "Alpha Mapping" );

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];
	m_nCurrentDirect = DIRECT_SLIDER;

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Returns the active alpha mapping name
//---------------------------------------------------------
char* ImpressionistDoc::getAlphaMappingName() 
{
	return m_alphaMappingName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Called by the UI when the user changes the stroke direction type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setDirectType(int type)
{
	m_nCurrentDirect= type;
}


//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the line width of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

//---------------------------------------------------------
// Returns the line angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}



//---------------------------------------------------------
// Returns the alpha of the brush.
//---------------------------------------------------------
double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}


//---------------------------------------------------------
// Returns the color of blending.
//---------------------------------------------------------
ucolor32 ImpressionistDoc::getBlendColor()
{
	return m_pUI->getBlendColor();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();

	// generate grayscale image
	GLubyte color[3];
	m_nGrayImg = new int*[m_nWidth];
	for(int i=0; i<m_nWidth; i++) {
		m_nGrayImg[i] = new int[m_nHeight]; 
		for(int j=0; j<m_nHeight; j++) {
			memcpy ( color, GetOriginalPixel(i, j), 3 );
			m_nGrayImg[i][j] =  0.299 * color[0] + 0.587 * color[1] + 0.114 * color[2];
		}
	}

	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//---------------------------------------------------------
// Load the specified alpha mapping
// This is called by the UI when the load alpha mapping button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadAlphaMapping(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				i,
					width, height, all,
					max;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	if(!IS_2_POWER(width) || !IS_2_POWER(height)) {
		fl_alert("The height and width must be power of 2");
		return 0;
	}

	if(width != height) {
		fl_alert("The height must be the same as the width");
		return 0;
	}

	if(width > max) {
		fl_alert("The dimension exceeds the limit of OPENGL of %d px", max);
		return 0;
	}

	// reflect the fact of loading the new image
	m_nMappingWidth	= width;
	m_nMappingHeight = height;
	all = width * height;

	// release old storage
	if ( m_ucMapping ) delete [] m_ucMapping;
	
	m_ucMapping = new GLubyte[all];
	
	for(i = 0; i < all; i++) {
		m_ucMapping[i] = 255 - (data[3 * i] + data[3 * i + 1] + data[3 * i + 1]) / 3;
	}

	m_bMapFlag = true;

	delete [] data;

	return 1;
}

//----------------------------------------------------------------
// Generate the texture of alpha mapping
// This is called by the View when the gl context is reset
//-----------------------------------------------------------------
void ImpressionistDoc::genMappingTexture() {
	int ori_align, ori_row_l;
	if(m_bMapFlag) {
		glDeleteTextures(1, &m_uMapTextureID);
		m_bMapFlag = false;
	}
	if(!m_ucMapping) {
		return;
	}
	
	glGetIntegerv( GL_UNPACK_ALIGNMENT, &ori_align);
	glGetIntegerv( GL_UNPACK_ROW_LENGTH, &ori_row_l);

	glGenTextures( 1, &m_uMapTextureID );
	glBindTexture( GL_TEXTURE_2D, m_uMapTextureID );
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glPixelStorei( GL_UNPACK_ROW_LENGTH, m_nMappingWidth );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, m_nMappingWidth, m_nMappingHeight, 0, GL_ALPHA, GL_UNSIGNED_BYTE, m_ucMapping);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPixelStorei( GL_UNPACK_ALIGNMENT, ori_align );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, ori_row_l );
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::swapCanvas() 
{
	unsigned char *tmp;
	if(!m_ucBitmap) {
		fl_alert("Please load image first");
		return 1;
	}
	tmp = m_ucBitmap;
	m_ucBitmap = m_ucPainting;
	m_ucPainting = tmp;

	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
	return 0;
}

//----------------------------------------------------------------
// Swap the drawing canvas
// This is called by the UI when the swap canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}



//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

int ImpressionistDoc::GetLuminance(int x, int y) {
	if ( x < 0 ) x = 0;
	else if ( x >= m_nWidth ) x = m_nWidth-1;

	if ( y < 0 ) y = 0;
	else if ( y >= m_nHeight ) y = m_nHeight-1;

	return m_nGrayImg[x][y]; 
}

int ImpressionistDoc::GetLuminance(const Point p) {
	return GetLuminance(p.x, p.y);
}

Point ImpressionistDoc::GetGradient(const Point p) {
	Point result(0, 0);
	int lumi;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			lumi = GetLuminance(p.x+i-1, p.y+j-1);
			result.x += X_KERNAL[i*3+j] * lumi;
			result.y += Y_KERNAL[i*3+j] * lumi;
		}
	}
	result.x /= 9;
	result.y /= 9;
	return result;
}

//----------------------------------------------------------------
// Mark the movement of cursor on PaintView
//----------------------------------------------------------------
void ImpressionistDoc::markMove( const Point p )
{
	if(!m_imageName) {
		return;
	}
	if(m_curPoint.x == -1) {
		m_lastPoint = p;
		m_curPoint = p;
	}
	else {
		m_lastPoint = m_curPoint;
		m_curPoint = p;
	}
	m_pUI->m_origView->markTracker();
}