#ifndef NUMERICALKERNEL_H
#define NUMERICALKERNEL_H

//
// NumericalKernel.h
//
// The header file of numerical kernel using convolution
//

#include "ImpKernel.h"

class NumericalKernel: public ImpKernel {
	public:
		NumericalKernel( ImpressionistDoc* pDoc = NULL, char* name = NULL, int dimension = 3 );
		~NumericalKernel();
		GLubyte filterFunc( GLubyte* centerblock);
		char* KernelName( void );

		const double* const * getKernel();

	protected:
		double** kernel;
};

#endif