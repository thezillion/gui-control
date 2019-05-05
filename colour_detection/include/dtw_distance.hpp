#ifndef TSUTIL_H
#define TSUTIL_H

#include <vector>
#include <cstdint>

typedef std::pair<double, double> PDD;

namespace TimeSeriesUtils {
	
	double CalculateEuclideanDistance(PDD&, PDD&);

	double CalculateDynamicTimeWarpedDistance(std::vector<PDD>& t0, std::vector<PDD>& t1);
	
}

#endif
