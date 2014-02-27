//
// CustomKernel.cpp
//
// The implementation of Mean Filter. It is a kind of NumericalKernel.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CustomKernel.h"

CustomKernel::CustomKernel( ImpressionistDoc* pDoc, char* name, int dimension ) :
	NumericalKernel(pDoc,name,dimension)
{
	int i, j;
	for(i = 0; i < dimension; i++) {
		for(j = 0; j < dimension; j++) {
			kernel[i][j] = 1;
		}
	}
}

void CustomKernel::set(int x, int y, double value) {
	kernel[x][y] = value;
}