#ifndef MEANKERNEL_H
#define MEANKERNEL_H

//
// MeanKernel.h
//
// The header file of mean filter kernel
//

#include "NumericalKernel.h"

class MeanKernel: public NumericalKernel {
	public:
		MeanKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );
		char* KernelName( void );
};

#endif