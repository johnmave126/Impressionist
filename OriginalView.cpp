//
// originalview.cpp
//
// The code maintaining the original view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "originalview.h"

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

OriginalView::OriginalView(int			x, 
						   int			y, 
						   int			w, 
						   int			h, 
						   const char*	l)
							: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}

void OriginalView::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucBitmap ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();

		int drawWidth, drawHeight;
		GLvoid* bitstart;

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
		drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );

		int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + drawHeight);
		if ( startrow < 0 ) 
			startrow = 0;


		bitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);

		// just copy image to GLwindow conceptually
		glRasterPos2i( 0, m_nWindowHeight - drawHeight );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
		glDrawBuffer( GL_BACK );
		glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );

	}
			
	glFlush();
}

void OriginalView::refresh()
{
	redraw();
}

void OriginalView::resizeWindow(int	width, 
								int	height)
{
	resize(x(), y(), width, height);
}

void OriginalView::markTracker() {
	int drawWidth, drawHeight, startrow;;
	Point cur = m_pDoc->m_curPoint, last = m_pDoc->m_lastPoint;
	GLvoid* bitstart;
	const int size = 10;
	make_current();
	
	drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
	drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );
	//restric drawing in the image area
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, m_nWindowHeight - drawHeight, drawWidth, drawHeight);

	//draw last point pixels back
	if(last.x <= drawWidth && last.y >= m_nWindowHeight - drawHeight) {
		last.x -= size >> 1;
		last.y -= size >> 1;
		if(last.x < 0) {
			last.x = 0;
		}
		if(last.x + size > drawWidth) {
			last.x = drawWidth - size;
		}
		if(last.y < m_nWindowHeight - drawHeight) {
			last.y = m_nWindowHeight - drawHeight;
		}
		if(last.y + size > m_nWindowHeight) {
			last.y = m_nWindowHeight - size;
		}

		//Restore content
		startrow = m_pDoc->m_nHeight - m_nWindowHeight + last.y;
		if ( startrow < 0 ) 
			startrow = 0;
		bitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + last.x);

		glRasterPos2i( last.x, last.y );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
		glDrawBuffer( GL_FRONT );
		glDrawPixels( size, size, GL_RGB, GL_UNSIGNED_BYTE, bitstart );
	}

	//put marker on current point	
	if(cur.x <= drawWidth && cur.y >= m_nWindowHeight - drawHeight) {
		glDrawBuffer(GL_FRONT);
		glColor3ub(255, 0, 0);
		glPointSize((float)size);
		glBegin(GL_POINTS);
		glVertex2i(cur.x, cur.y);
		glEnd();
	}
	
	glDisable(GL_SCISSOR_TEST);
	glFlush();
}