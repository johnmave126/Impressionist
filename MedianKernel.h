#ifndef MEDIANKERNEL_H
#define MEDIANKERNEL_H

//
// MedianFilter.h
//
// The header file of median filter kernel
//

#include "ImpKernel.h"

class MedianKernel: public ImpKernel {
	public:
		MedianKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );
		char* KernelName( void );

		GLubyte filterFunc(GLubyte* centerblock);
};

#endif