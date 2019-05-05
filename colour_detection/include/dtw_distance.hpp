#ifndef TSUTIL_H
#define TSUTIL_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>
#include "fingertip.hpp"

typedef Hand pt;

namespace TimeSeriesUtils {
	
	double CalculateEuclideanDistance(pt&, pt&);

	double CalculateDynamicTimeWarpedDistance(std::deque<pt>& t0, std::deque<pt>& t1);
	
}

#endif
