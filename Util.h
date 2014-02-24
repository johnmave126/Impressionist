//
// Util.h
//
// header file for utilities
//
//
#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <functional>
#include <math.h>
#include <assert.h>
#define PI 3.14159265

namespace util {
	/*
	 * A base class for vector of any length
	 */
	template<typename T, class Compare = std::less<T>>
	class Vec {
		public:
			/*
			 * default constructor constructs a zero dimension vector
			 */
			Vec(): dimension(0) { }

			/*
			 * construct a vector using dimension specified
			 */
			explicit Vec(int dim): dimension(dim) {
				data.resize(dimension);
			}

			/*
			 * copy constructor
			 */
			Vec(const Vec& v): data(v.data), dimension(v.dimension) { }

			/*
			 * assign operator
			 */
			Vec& operator=(const Vec& v) {
				data = v.data;
				dimension = v.dimension;
			}

			/*
			 * plus operator
			 */
			Vec operator+(const Vec& v) const {
				int i;
				assert(v.dimension == dimension);
				Vec ret(dimension);
				for(i = 0; i < dimension; i++) {
					ret.data[i] = data[i] + v.data[i];
				}
				return ret;
			}

			Vec& operator+=(const Vec& v) {
				int i;
				assert(v.dimension == dimension);
				for(i=0; i < dimension; i++) {
					data[i] += v.data[i];
				}
				return *this;
			}

			/*
			 * minus operator
			 */
			Vec operator-(const Vec& v) const {
				int i;
				assert(v.dimension == dimension);
				Vec ret(dimension);
				for(i = 0; i < dimension; i++) {
					ret.data[i] = data[i] - v.data[i];
				}
				return ret;
			}

			Vec& operator-=(const Vec& v) {
				int i;
				assert(v.dimension == dimension);
				for(i=0; i < dimension; i++) {
					data[i] -= v.data[i];
				}
				return *this;
			}

			/*
			 * unary minus
			 */
			Vec operator-() const {
				int i;
				Vec ret(dimension);
				for(i = 0; i < dimension; i++) {
					ret.data[i] = -data[i];
				}
				return ret;
			}

			/*
			 * dot product as *
			 */
			int operator*(const Vec& v) const {
				int i, ret = 0;
				assert(v.dimension == dimension);
				for(i = 0; i < dimension; i++) {
					ret += data[i] * v.data[i];
				}
				return ret;
			}

			/*
			 * scalar multiplication
			 */
			Vec operator*(const T s) const {
				int i;
				Vec ret(dimension);
				for(i = 0; i < dimension; i++) {
					ret.data[i] = data[i] * s;
				}
				return ret;
			}

			Vec& operator*=(const T s) {
				int i;
				for(i = 0; i < dimension; i++) {
					data[i] *= s;
				}
				return *this;
			}

			/*
			 * relational operators
			 */
			bool operator==(const Vec& v) const {
				return v.dimension == dimension && v.data == data;
			}

			bool operator!=(const Vec& v) const {
				return !(*this == v);
			}

			bool operator<(const Vec& v) const {
				assert(v.dimension == dimension);
				return data < v.data;
			}

			bool operator<=(const Vec& v) const {
				assert(v.dimension == dimension);
				return data <= v.data;
			}

			bool operator>(const Vec& v) const {
				assert(v.dimension == dimension);
				return data > v.data;
			}

			bool operator>=(const Vec& v) const {
				assert(v.dimension == dimension);
				return data >= v.data;
			}

			/*
			 * subscript operator
			 */
			T& operator[](size_t n) {
				assert(n >= 0 && n < dimension);
				return data[n];
			}

			const T& operator[](size_t n) const {
				assert(n >= 0 && n < dimension);
				return data[n];
			}

			/*
			 * Return the dimension of the vector
			 */
			int size() const {
				return dimension;
			}

			/*
			 * Return the modulus of the vector
			 */
			T modulus() const {
				T ret = 0;
				int i;
				for(i = 0; i < dimension; i++) {
					ret += data[i] * data[i];
				}
				return sqrt(ret);
			}

			/*
			 * Return the normalized version of the vector
			 */
			Vec norm() const {
				int i;
				T mod = this->modulus();
				Vec ret(dimension);
				for(i = 0; i < dimension; i++) {
					ret.data[i] = data[i] / mod;
				}
				return ret;
			}

		private:
			std::vector<T> data;
			/* The dimension of the vector */
			int dimension;
	};

	/*
	 * left scalar multiplication of Vec
	 */
	template<typename T, class Compare>
	Vec<T, Compare> operator*(T s, const Vec<T, Compare>& v) {
		return v * s;
	}

	double degree2angle(int degree);
	int angle2degree(double angle);
	int calDegree(int x, int y);
	double calAngle(int x, int y);

	
#define swap(x, y) \
	{t = x; x = y; y = t;}

	template<typename T>
	int partition(T a[], int l, int r, int pivot) {
		int i = l, j = r - 1, t;
		T k = a[pivot];
		swap(a[l], a[pivot]);
		while(i < j) {
			while(i < j && a[j] >= k) j--;
			if(i < j) a[i] = a[j];
			while(i < j && a[i] < k) i++;
			if(i < j) a[j] = a[i];
		}
		a[i] = k;
		return i;
	}

	template<typename T>
	int select5(T a[], int l, int r) {
		int i, j, t;
		for(i = l; i < r; i++) {
			for(j = r - 1; j > i; j--) {
				if(a[j] < a[j-1]) {
					swap(a[j], a[j-1]);
				}
			}
		}
		return l + ((r - l) >> 1);
	}

	template<typename T>
	int medianOfMedian(T a[], int l, int r);

	template<typename T>
	int quickSelect(T a[], int l, int r, int rank) {
		int idx;
		if(r - l == 1) {
			return l;
		}
		idx = medianOfMedian(a, l, r);
		idx = partition(a, l, r, idx);
		if(idx - l + 1 < rank) {
			return quickSelect(a, idx + 1, r, rank - (idx - l + 1));
		}
		else if(idx - l + 1 ==rank) {
			return idx;
		}
		else {
			return quickSelect(a, l, idx, rank);
		}
	}

	template<typename T>
	int medianOfMedian(T a[], int l, int r) {
		int nMedian = (r - l + 4) / 5;
		int i, sl, sr, mid, t;
		for(i = 0; i < nMedian; i++) {
			sl = l + i * 5;
			sr = sl + 5;
			if(sr > r) sr = r;
			mid = select5(a, sl, sr);
			swap(a[l+i], a[mid]);
		}
		return quickSelect(a, l, l + nMedian, nMedian >> 1);
	}
}

#endif