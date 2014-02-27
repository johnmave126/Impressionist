//
// MedianKernel.cpp
//
// The implementation of Median Kernel. It is a kind of ImpKernel.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "MedianKernel.h"
#include "Util.h"

GLubyte select256(GLubyte* arr, int length) {
	GLubyte b[256];
	int i, idx = 255, s = 0, t = (length + 1) >> 1;
	memset(b, 0, sizeof(b));
	for(i = 0; i < length; i++) {
		b[arr[i]]++;
		if(arr[i] < idx) idx = arr[i];
	}
	for(i = idx; i < 256; i++) {
		s += b[i];
		if(s >= t) {
			return i;
		}
	}
	return 0;
}

MedianKernel::MedianKernel( ImpressionistDoc* pDoc, char* name, int dimension ) :
	ImpKernel(pDoc,name,dimension)
{
}

GLubyte MedianKernel::filterFunc( GLubyte* centerblock) {
	int size = m_nDimension * m_nDimension;
	return select256(centerblock, size);
	//return centerblock[util::quickSelect(centerblock, 0, size, (size + 1) >> 1)];
}
