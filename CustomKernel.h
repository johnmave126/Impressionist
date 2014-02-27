#ifndef CUSTOMKERNEL_H
#define CUSTOMKERNEL_H

//
// CustomKernel.h
//
// The header file of custom filter kernel
//

#include "NumericalKernel.h"

class CustomKernel: public NumericalKernel {
	public:
		CustomKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );
		char* KernelName( void );

		void set(int x, int y, double value);
};

#endif