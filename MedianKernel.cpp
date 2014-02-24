//
// MedianKernel.cpp
//
// The implementation of Median Kernel. It is a kind of ImpKernel.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "MedianKernel.h"
#include "Util.h"

MedianKernel::MedianKernel( ImpressionistDoc* pDoc, char* name, int dimension ) :
	ImpKernel(pDoc,name,dimension)
{
}

GLubyte MedianKernel::filterFunc( GLubyte* centerblock) {
	int size = m_nDimension * m_nDimension;
	return centerblock[util::quickSelect(centerblock, 0, size, (size + 1) >> 1)];
}
