//
// GaussianKernel.cpp
//
// The implementation of Gaussian Filter. It is a kind of NumericalKernel.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "GaussianKernel.h"
#include <math.h>

GaussianKernel::GaussianKernel( ImpressionistDoc* pDoc, char* name, int dimension ) :
	NumericalKernel(pDoc,name,dimension)
{
	int i, j;
	double x, y;
	for(i = 0; i < dimension; i++) {
		x = i - dimension / 2.0;
		for(j = 0; j < dimension; j++) {
			y = j - dimension / 2.0;
			kernel[i][j] = exp(-(x * x + y * y));
		}
	}
}
