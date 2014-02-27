//
// NumericalKernel.cpp
//
// The implementation of Numerical Kernel. It is a kind of ImpKernel.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "NumericalKernel.h"

NumericalKernel::NumericalKernel( ImpressionistDoc* pDoc, char* name, int dimension ) :
	ImpKernel(pDoc,name,dimension)
{
	int i;
	kernel = new double*[dimension];
	for(i = 0; i < dimension; i++) {
		kernel[i] = new double[dimension];
	}
}

NumericalKernel::~NumericalKernel()
{
	int i;
	for(i = 0; i < m_nDimension; i++) {
		delete kernel[i];
	}
	delete kernel;
}

GLubyte NumericalKernel::filterFunc( GLubyte* centerblock) {
	double ans = 0, sum = 0;
	int i, j;
	for(i = 0; i < m_nDimension; i++) {
		for(j = 0; j < m_nDimension; j++, centerblock++) {
			sum += kernel[i][j];
			ans += kernel[i][j] * (*centerblock);
		}
	}
	if(m_bNorm) {
		ans /= abs(sum);
	}
	if(ans > 255 - 1E-6) {
		ans = 255;
	}
	if(ans < 1E-6) {
		ans = 0;
	}
	return (GLubyte)ans;
}

const double* const * NumericalKernel::getKernel() {
	return kernel;
}