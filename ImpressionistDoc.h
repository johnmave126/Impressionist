// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

const int X_KERNAL[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
const int Y_KERNAL[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
						 
class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use
	int		loadImage(char *iname, bool mural=false);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int		loadAlphaMapping(char *iname);	// called by the UI to load alpha mapping
	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	int     swapCanvas();                  // called by the UI to swap the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	void	setDirectType(int type);			// called by the UI to set the stroke direct Type
	int		getSize();						// get the UI size
	int		getLineWidth();
	int		getLineAngle();
	int		getSpace();
	double	getAlpha();						// get the UI alpha
	ucolor32	getBlendColor();			// get the UI color
	char*	getImageName();					// get the current image name
	char*	getAlphaMappingName();			// get the current alpha mapping name
	void	genMappingTexture();			// generate the texture in GL
	void 	markMove(const Point p);		// mark the moving of cursor

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;

	//grayscale image for gradient operation
	int**			m_nGrayImg;

	// Dimensions of alpha mapping texture
	int				m_nMappingWidth,
					m_nMappingHeight;
	
	GLubyte*		m_ucMapping;
	unsigned int	m_uMapTextureID;
	bool			m_bMapFlag;

	Point m_lastPoint;
	Point m_curPoint;

	//mark the begin and end point to control direction
	Point m_directBegin;
	Point m_directEnd;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;							
	// The current stroke direct control method
	int m_nCurrentDirect;
	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	int		GetLuminance(int x, int y);
	int		GetLuminance(const Point p);
	Point	GetGradient(const Point p);


private:
	char			m_imageName[256];
	char			m_alphaMappingName[256];

};

extern void MessageBox(char *message);

#endif
