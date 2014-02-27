//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Output.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"
#include "ImpKernel.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirectChoice;
	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_BrushAlphaSlider;
	Fl_Slider*			m_SpaceSlider;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Check_Button*	m_RandSizeButton;
	Fl_Button*			m_PaintButton;
	Fl_Button*			m_LoadAlphaMappingButton;

	// for color picking
	Fl_Window*			m_colorDialog;
	Fl_Color_Chooser*	m_ColorChooser;

	// for image filtering
	Fl_Window*			m_filterDialog;
	Fl_Choice*			m_filterDimSlider;
	Fl_Choice*			m_filterTypeChoice;
	Fl_Check_Button*	m_normalizeCheck;
	Fl_Button*			m_FilterImageButton;
	Fl_Float_Input*		m_aFilterInput[9][9];

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();
	void				show();
	void				resize_windows(int w, int h);
	PaintView*			getPaintView();

	// Interface to get attribute
	int					getSize();
	void				setSize(int size);

	int					getSpace();
	void				setSpace(int size);

	bool				getRandSize();
	void				setRandSize(bool);

	int					getLineWidth();
	void				setLineWidth(int size);

	int					getLineAngle();
	void				setLineAngle(int angle);
	
	double				getAlpha();
	void				setAlpha(double alpha);

	ucolor32			getBlendColor();
	void				setBlendColor(ucolor32 col);
	void				setBlendColor(unsigned r, unsigned g, unsigned b);

	int					getFilterDim();
	void				setFilterDim(int dim);

	int					getFilterNorm();
	void				setFilterNorm(int norm);

	void				getFilter(double **a);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	double 	m_lfAlpha;
	int		m_nLineWidth;
	int		m_nLineAngle;
	int		m_nSpace;
	bool	m_bRandSize;
	ucolor32	m_cColor;
	int		m_nFilterDim;
	int		m_bNorm;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		filterTypeMenu[NUM_FILTER_TYPE+1];
	static Fl_Menu_Item		filterDimMenu[4+1];
	static Fl_Menu_Item		strokeDirectMenu[NUM_DIRECT+1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_load_mural(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_colors(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_swap_canvas(Fl_Menu_* o, void* v);
	static void cb_filter_image(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_directChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_alphaSlides(Fl_Widget* o, void* v);
	static void	cb_lineWidthSlides(Fl_Widget* o, void* v);
	static void	cb_lineAngleSlides(Fl_Widget* o, void* v);
	static void	cb_spaceSlides(Fl_Widget* o, void* v);
	static void	cb_colorChooses(Fl_Widget* o, void* v);
	static void	cb_paint_button(Fl_Widget* o, void* v);
	static void	cb_rand_size_button(Fl_Widget* o, void* v);
	static void	cb_load_alpha_mapping_button(Fl_Widget* o, void* v);
	static void	cb_filterChoice(Fl_Widget* o, void* v);
	static void cb_filterDimChoice(Fl_Widget* o, void* v);
	static void cb_filterNormalizeCheck(Fl_Widget* o, void* v);
	static void cb_filter_image_button(Fl_Widget* o, void* v);

};

#endif
