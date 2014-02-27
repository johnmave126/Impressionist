#ifndef GAUSSIANKERNEL_H
#define GAUSSIANKERNEL_H

//
// GaussianKernel.h
//
// The header file of gaussian filter kernel
//

#include "NumericalKernel.h"

class GaussianKernel: public NumericalKernel {
	public:
		GaussianKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );
		char* KernelName( void );
};

#endif