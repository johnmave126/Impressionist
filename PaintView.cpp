//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "Util.h"
#include "paintview.h"
#include "ImpBrush.h"


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	m_bPaintAuto	= false;

}

void PaintView::paintAutomatic() {
	m_bPaintAuto = true;
	refresh();
}

void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);
		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );
		ortho();
		glClear( GL_COLOR_BUFFER_BIT );
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_SCISSOR_TEST);
	}
	if(!valid() || m_pDoc->m_bMapFlag) 
		m_pDoc->genMappingTexture();

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;
	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	glScissor(0, m_nWindowHeight - m_nDrawHeight, m_nDrawWidth, m_nDrawHeight);
	if(m_bPaintAuto) {
		int space = m_pDoc->getSpace();
		int width = m_pDoc->m_nWidth;
		int height = m_pDoc->m_nHeight;
		printf("%d %d", width, height);
		if(m_pDoc->getRandSize()) {
			m_pDoc->setRand(true);
		} else {
			m_pDoc->setRand(false);
		}
		
		m_pDoc->m_pCurrentBrush->BrushBegin(Point(0, 0), Point(0, 0));
		for(int i=0; i<width; i += space) {
			for(int j=0; j<height; j += space) {
				m_pDoc->m_pCurrentBrush->BrushMove(Point(i, j), Point(i, j));
			}
		}
		m_pDoc->m_pCurrentBrush->BrushEnd(Point(width-1, height-1), Point(width-1, height-1));
		SaveCurrentContent();
		RestoreContent();
		m_bPaintAuto = false;
	}

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();
	}
	
	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{
	
		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			printf("(%d, %d), (%d, %d) \n", source.x, source.y, target.x, target.y);
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			if(m_pDoc->m_nCurrentDirect == DIRECT_SLIDER) {
				m_directStartPoint = target;
				SaveCurrentContent();
			}
			break;
		case RIGHT_MOUSE_DRAG:
			if(m_pDoc->m_nCurrentDirect == DIRECT_SLIDER) {
				markDirectControl(target);
			}
			break;
		case RIGHT_MOUSE_UP:
			if(m_pDoc->m_nCurrentDirect == DIRECT_SLIDER) {
				int deltax = target.x - m_directStartPoint.x;
				int deltay = target.y - m_directStartPoint.y;
				int degree = util::calDegree(deltax, deltay);
				printf("x %d, y %d,  set degree %d\n", deltax, deltay, degree);
				if(deltax != 0) m_pDoc->m_pUI->setLineAngle(degree);
				RestoreContent();
			}
			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}

	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		m_pDoc->markMove( Point(coord.x, m_nWindowHeight - coord.y) ); // Tell Doc the position of cursor
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		m_pDoc->markMove( Point(coord.x, m_nWindowHeight - coord.y) ); // Tell Doc the position of cursor
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	int ori_align, ori_row_l;
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glGetIntegerv( GL_PACK_ALIGNMENT, &ori_align);
	glGetIntegerv( GL_PACK_ROW_LENGTH, &ori_row_l);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );

	glPixelStorei( GL_PACK_ALIGNMENT, ori_align );
	glPixelStorei( GL_PACK_ROW_LENGTH, ori_row_l );
}


void PaintView::RestoreContent()
{
	int ori_align, ori_row_l;
	//glDrawBuffer(GL_BACK);

	glGetIntegerv( GL_UNPACK_ALIGNMENT, &ori_align);
	glGetIntegerv( GL_UNPACK_ROW_LENGTH, &ori_row_l);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);
	
	glPixelStorei( GL_UNPACK_ALIGNMENT, ori_align );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, ori_row_l );
//	glDrawBuffer(GL_FRONT);
}

void PaintView::markDirectControl(Point target)
{
    RestoreContent();
	if(target.x <= m_nWindowWidth && target.y <= m_nWindowHeight) {
		glColor3ub(255, 0, 0);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2i(m_directStartPoint.x, m_directStartPoint.y);
		glVertex2i(target.x, target.y);
		glEnd();
	}
	glFlush();
}
