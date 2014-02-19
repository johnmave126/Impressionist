//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//-------------------------------------------------------------
// Brings up the colors dialog
// This is called by the UI when the colors menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_colorDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Swaps the paintview/origview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_swap_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->swapCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}



//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for COMP 4411, Spring 2014");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	if(type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES) {
		pUI->m_LineAngleSlider->activate();
		pUI->m_LineWidthSlider->activate();
		pUI->m_StrokeDirectChoice->activate();
	} else {
		pUI->m_LineAngleSlider->deactivate();
		pUI->m_LineWidthSlider->deactivate();
		pUI->m_StrokeDirectChoice->deactivate();
	}

	if(type == BRUSH_ALPHA_MAPPING) {
		pUI->m_LoadAlphaMappingButton->activate();
	}
	else {
		pUI->m_LoadAlphaMappingButton->deactivate();
	}

	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_directChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;
	printf("set type %d\n", type);
	pDoc->setDirectType(type);
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}

void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth=int( ((Fl_Slider *)o)->value() ) ;
}
	

void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle=int( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the brush alpha to use from the value of the alpha
// slider
// Called by the UI when the alpha slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_lfAlpha=double( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Prompt to load alpha mapping texture
// Called by the UI when the load alpha mapping is pressed
//-----------------------------------------------------------
void ImpressionistUI::cb_load_alpha_mapping_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc *pDoc=((ImpressionistUI*)(o->user_data()))->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getAlphaMappingName() );
	if (newfile != NULL) {
		pDoc->loadAlphaMapping(newfile);
	}
}


//-----------------------------------------------------------
// Updates the blending color to use from the value of the color
// chooser
// Called by the UI when the color chooser is used
//-----------------------------------------------------------
void ImpressionistUI::cb_colorChooses(Fl_Widget* o, void* v)
{
	Fl_Color_Chooser* c = (Fl_Color_Chooser*)o;
	((ImpressionistUI*)(o->user_data()))->m_cColor=PACK_COLOR((unsigned)floor(c->r() * 255), (unsigned)floor(c->g() * 255), (unsigned)floor(c->b() * 255));
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40 && size > 0) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the line width
//------------------------------------------------
int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

//-------------------------------------------------
// Set the line width
//-------------------------------------------------
void ImpressionistUI::setLineWidth( int size )
{
	m_nLineWidth=size;

	if (size<=40 && size > 0) 
		m_LineWidthSlider->value(m_nSize);
}

//------------------------------------------------
// Return the line angle
//------------------------------------------------
int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

//-------------------------------------------------
// Set the line Angle
//-------------------------------------------------
void ImpressionistUI::setLineAngle( int size )
{
	m_nLineAngle=size;

	if (size<=359 && size >= 0) 
		m_LineAngleSlider->value(m_nLineAngle);
}

//------------------------------------------------
// Return the brush alpha
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_lfAlpha;
}

//-------------------------------------------------
// Set the brush alpha
//-------------------------------------------------
void ImpressionistUI::setAlpha( double alpha )
{
	m_lfAlpha=alpha;

	if (alpha<=1.00 && alpha >= 0.00) 
		m_BrushAlphaSlider->value(m_lfAlpha);
}

//------------------------------------------------
// Return the color blending
//------------------------------------------------
ucolor32 ImpressionistUI::getBlendColor()
{
	return m_cColor;
}

//-------------------------------------------------
// Set the color blending
//-------------------------------------------------
void ImpressionistUI::setBlendColor(unsigned r, unsigned g, unsigned b)
{
	m_cColor = PACK_COLOR(r, g, b);
	if(r < 256 && g < 256 && b < 256) {
		m_ColorChooser->rgb(r / 255.0, g / 255.0, b / 255.0);
	}
}

//-------------------------------------------------
// Set the color blending
//-------------------------------------------------
void ImpressionistUI::setBlendColor(ucolor32 col)
{
	unsigned r, g, b;
	UNPACK_COLOR(r, g, b, col);
	setBlendColor(r, g, b);
}

// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "S&wap Canvas",	FL_ALT + 'w', (Fl_Callback *)ImpressionistUI::cb_swap_canvas }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },

		{ "&Colors...",	FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colors, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Ink",				FL_ALT+'i', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_INK},
  {"Alpha Mapping",		FL_ALT+'a', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_ALPHA_MAPPING},
  {0}
};

Fl_Menu_Item ImpressionistUI::strokeDirectMenu[NUM_DIRECT+1] = {
	{"Slider/Right Mouse",FL_ALT+'s', (Fl_Callback *)ImpressionistUI::cb_directChoice, (void *)DIRECT_SLIDER},
	{"Gradient",	    FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_directChoice, (void *)DIRECT_GRADIENT},
	{"Brush Direction",	FL_ALT+'b', (Fl_Callback *)ImpressionistUI::cb_directChoice, (void *)DIRECT_BRUSH},
    {0}
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_lfAlpha = 1.0;
	m_nLineAngle = 0;
	m_nLineWidth = 1;
	m_cColor = PACK_COLOR(255, 255, 255);


	m_colorDialog = new Fl_Window(230, 270, "Color Selector");
		// Add the color chooser to the dialog
		m_ColorChooser = new Fl_Color_Chooser(10, 20, 200, 230, "Color Blending");
		m_ColorChooser->user_data((void*)(this));	// record self to be used by static callback functions
		m_ColorChooser->callback(cb_colorChooses);
		m_ColorChooser->rgb(1.0, 1.0, 1.0);
		m_ColorChooser->align(FL_ALIGN_TOP);
		m_ColorChooser->labeltype(FL_NORMAL_LABEL);

	m_colorDialog->end();

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 360, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		// Add a stroke direction type choice to the dialog
		m_StrokeDirectChoice = new Fl_Choice(115,40,150,25,"&Stroke Direction");
		m_StrokeDirectChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectChoice->menu(strokeDirectMenu);
		m_StrokeDirectChoice->callback(cb_directChoice);
		m_StrokeDirectChoice->deactivate();

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line width slider to the dialog 
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
        m_LineWidthSlider->labelfont(FL_COURIER);
        m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_lineWidthSlides);
		m_LineWidthSlider->deactivate();
		

		// Add line angle slider to the dialog 
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_LineAngleSlider->labelfont(FL_COURIER);
        m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_lineAngleSlides);
		m_LineAngleSlider->deactivate();

		// Add brush alpha slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(0.0);
		m_BrushSizeSlider->maximum(1.0);
		m_BrushSizeSlider->step(0.01);
		m_BrushSizeSlider->value(m_lfAlpha);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_alphaSlides);

		// Add alpha mapping loading button to the dialog
		m_LoadAlphaMappingButton = new Fl_Button(10, 315, 150, 25,"&Load Alpha Mapping");
		m_LoadAlphaMappingButton->user_data((void*)(this));
		m_LoadAlphaMappingButton->callback(cb_load_alpha_mapping_button);
		m_LoadAlphaMappingButton->deactivate();

    m_brushDialog->end();	

}
