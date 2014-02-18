#include "Util.h"

namespace util {
	double degree2angle(int degree) {
		return degree * 2 * PI / 360.0;
	}

	int angle2degree(double angle) {
		return angle * 360 / (2 * PI);
	}

	int calDegree(int x, int y) {
		if(x == 0) return 90;
		double angle = abs(tanh((double)y / x)); 
		int degree = angle2degree(angle);
		if(x < 0 && y > 0) degree = 180 - degree;
		else if(x < 0 && y < 0) degree += 180;
		else if(x > 0 && y < 0) degree = 360 - degree;
		return degree;
	}

	double calAngle(int x, int y) {
		return degree2angle(calDegree(x, y));
	}
}