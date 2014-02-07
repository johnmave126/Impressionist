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
}

#endif