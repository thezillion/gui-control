#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include "../include/TimeSeriesUtils.hpp"

double mod(PDD& p) {
	return std::pow(p.first, 2) + std::pow(p.second, 2);
}

bool comp(PDD& a, PDD& b) {
	return mod(a) < mod(b);
}

void normalize(std::vector<PDD>& v) {
	auto max_pt = std::max_element(v.begin(), v.end(), comp);
	auto min_pt = std::min_element(v.begin(), v.end(), comp);
	
	double max_x = max_pt->first, max_y = max_pt->second, min_x = min_pt->first, min_y = min_pt->second;

	double divmod = std::sqrt(std::pow(max_x - min_x, 2) + std::pow(max_y - min_y, 2));

	std::for_each(v.begin(), v.end(), [min_x, min_y, divmod](PDD& p) {
		p.first -= min_x;
		p.first /= divmod;
		p.second -= min_y;
		p.second /= divmod;
		std::cout << p.first << " " << p.second << "\n";
	});
}

namespace TimeSeriesUtils {

	double CalculateEuclideanDistance(PDD& p1, PDD& p2) {
		return std::sqrt(std::pow((p1.first - p2.first), 2) + std::pow((p1.second - p2.second), 2));
	}	

	double CalculateDynamicTimeWarpedDistance(std::vector<PDD>& t0, std::vector<PDD>& t1) {
		
        normalize(timeSeries0);
		normalize(timeSeries1);

		size_t m = t0.size();
		size_t n = t1.size();

		// Allocate the Matrix to work on:
		std::vector<std::vector<double>> cost(m, std::vector<double>(n));

		cost[0][0] = CalculateEuclideanDistance(t0[0], t1[0]);

		// Calculate the first row:
		for (int i = 1; i < m; i++) {
			cost[i][0] = cost[i - 1][0] + CalculateEuclideanDistance(t0[i], t1[0]);
		}

		// Calculate the first column:
		for (int j = 1; j < n; j++) {
			cost[0][j] = cost[0][j - 1] + CalculateEuclideanDistance(t0[0], t1[j]);
		}

		// Fill the matrix:
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				cost[i][j] = std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1])) 
					+ CalculateEuclideanDistance(t0[i], t1[j]);
			}
		}
	
		return cost[m-1][n-1];
	}

}
