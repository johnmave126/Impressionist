//
// ImpKernel.cpp
//
// The implementation of virtual kernel. All the other kernels inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpKernel.h"

// Static class member initializations
int			ImpKernel::c_nKernelCount	= 0;

ImpKernel::ImpKernel(ImpressionistDoc*	pDoc, 
				   char*				name,
				   int					dimension) :
					m_pDoc(pDoc), 
					m_pKernelName(name),
					m_nDimension(dimension),
					m_bNorm(true)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpKernel::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpKernel::KernelName(void)
{
	return m_pKernelName;
}

//---------------------------------------------------
// Return the dimension of the current brush
//---------------------------------------------------
int ImpKernel::KernelDim(void)
{
	return m_nDimension;
}

//----------------------------------------------------
// Apply the filter on a given image
//----------------------------------------------------
void ImpKernel::applyFilter(GLubyte* dst, const GLubyte* src, int width, int height)
{
	int i, j;
	for(i = 0; i < height; i++) {
		for(j = 0; j < width; j++, dst += 3) {
			applyFilter(dst, src, width, height, j, i);
		}
	}
}

//----------------------------------------------------
// Apply the filter on a given point
//----------------------------------------------------
void ImpKernel::applyFilter(GLubyte* dst, const GLubyte* src, int width, int height, int x, int y)
{
	GLubyte** mat = new GLubyte*[3];
	GLubyte col[3];
	int i, j, c, t;
	int r = 0, h = m_nDimension >> 1;
	const GLubyte* c_src;

	for(i = 0; i < 3; i++) {
		mat[i] = new GLubyte[m_nDimension * m_nDimension];
	}

	//Construct matrix
	// Bottom reflect
	for(c_src = src + (h - y) * 3 * width, i = y - h, t = r * m_nDimension; i < 0; i++, c_src -= 3 * width, r++, t += m_nDimension) {
		// Left reflect
		c = 0;
		for(j = x - h; j < 0; j++, c++) {
			mat[0][t + c] = c_src[-3 * j];
			mat[1][t + c] = c_src[-3 * j + 1];
			mat[2][t + c] = c_src[-3 * j + 2];
		}
		for(; j <= x + h && j < width; j++, c++) {
			mat[0][t + c] = c_src[3 * j];
			mat[1][t + c] = c_src[3 * j + 1];
			mat[2][t + c] = c_src[3 * j + 2];
		}
		// Right Reflect
		for(; j <= x + h; j++, c++) {
			mat[0][t + c] = c_src[3 * (2 * width - j - 2)];
			mat[1][t + c] = c_src[3 * (2 * width - j - 2) + 1];
			mat[2][t + c] = c_src[3 * (2 * width - j - 2) + 2];
		}
	}
	for(c_src = src + i * 3 * width, t = r * m_nDimension; i <= y + h && i < height; i++, c_src += 3 * width, r++, t += m_nDimension) {
		// Left reflect
		c = 0;
		for(j = x - h; j < 0; j++, c++) {
			mat[0][t + c] = c_src[-3 * j];
			mat[1][t + c] = c_src[-3 * j + 1];
			mat[2][t + c] = c_src[-3 * j + 2];
		}
		for(; j <= x + h && j < width; j++, c++) {
			mat[0][t + c] = c_src[3 * j];
			mat[1][t + c] = c_src[3 * j + 1];
			mat[2][t + c] = c_src[3 * j + 2];
		}
		// Right Reflect
		for(; j <= x + h; j++, c++) {
			mat[0][t + c] = c_src[3 * (2 * width - j - 2)];
			mat[1][t + c] = c_src[3 * (2 * width - j - 2) + 1];
			mat[2][t + c] = c_src[3 * (2 * width - j - 2) + 2];
		}
	}
	// Top reflect
	for(c_src = src + (height - 2) * 3 * width, t = r * m_nDimension; i <= y + h; i++, c_src -= 3 * width, r++, t += m_nDimension) {
		// Left reflect
		c = 0;
		for(j = x - h; j < 0; j++, c++) {
			mat[0][t + c] = c_src[-3 * j];
			mat[1][t + c] = c_src[-3 * j + 1];
			mat[2][t + c] = c_src[-3 * j + 2];
		}
		for(; j <= x + h && j < width; j++, c++) {
			mat[0][t + c] = c_src[3 * j];
			mat[1][t + c] = c_src[3 * j + 1];
			mat[2][t + c] = c_src[3 * j + 2];
		}
		// Right Reflect
		for(; j <= x + h; j++, c++) {
			mat[0][t + c] = c_src[3 * (2 * width - j - 2)];
			mat[1][t + c] = c_src[3 * (2 * width - j - 2) + 1];
			mat[2][t + c] = c_src[3 * (2 * width - j - 2) + 2];
		}
	}
	//Recycle
	for(i = 0; i < 3; i++) {
		col[i] = filterFunc(mat[i]);
		delete [] mat[i];
	}
	memcpy(dst, col, 3 * sizeof(GLubyte));
	delete [] mat;
}


void ImpKernel::setNorm(bool norm) {
	m_bNorm = norm;
}