#ifndef IMPKERNEL_H
#define IMPKERNEL_H

//
// ImpKernel.h
//
// The header file of virtual kernel filter. All the other kernels inherit from it.
//

#include <stdlib.h>
#include <cmath>
#include "Impressionist.h"

// Each brush type has an associated constant.
enum
{
	KERNEL_MEAN = 0,
	KERNEL_GAUSSIAN,
	KERNEL_MEDIAN,
	KERNEL_CUSTOM,
	NUM_FILTER_TYPE // Make sure this stays at the end!
};
		
class ImpressionistDoc; // Pre-declaring class

class ImpKernel 
{
protected:
	ImpKernel::ImpKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );

public:
	// The implementation of your kernel should realize these virtual functions
	virtual GLubyte filterFunc( GLubyte* centerblock) = 0;

	// Apply the filter to the given image
	// Allow override to boost (Gaussian 1-D convolution)
	virtual void applyFilter( GLubyte* dst, const GLubyte* src, int width, int height);

	// Apply the filter to a point on given image
	// Allow override to boost (Gaussian 1-D convolution)
	virtual void applyFilter( GLubyte* dst, const GLubyte* src, int width, int height, int x, int y);

	// get Doc to communicate with it
	ImpressionistDoc* GetDocument( void );

	// Return the name of the kernel (not used in this version).
	char* KernelName( void );

	// Return the dimension of the kernel
	int KernelDim(void);

	void setNorm(bool norm);
	
	static int			c_nKernelCount;	// How many kernels we have

protected:
	ImpressionistDoc*	m_pDoc;

	// Kernel's name (not used in this version).
	char*				m_pKernelName;

	// Dimension of the filter kernel
	int					m_nDimension;

	// Whether to normalize
	bool				m_bNorm;
};

#endif