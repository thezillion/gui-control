#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <opencv2/opencv.hpp>
#include "../include/dtw_distance.hpp"

double mod(pt& p) {
	return std::pow(p.x, 2) + std::pow(p.y, 2);
}

bool comp(pt& a, pt& b) {
	return mod(a) < mod(b);
}

void normalize(std::deque<pt>& v) {
	auto max_pt = std::max_element(v.begin(), v.end(), comp);
	auto min_pt = std::min_element(v.begin(), v.end(), comp);
	
	double max_x = max_pt->x, max_y = max_pt->y, min_x = min_pt->x, min_y = min_pt->y;

	double divmod = std::sqrt(std::pow(max_x - min_x, 2) + std::pow(max_y - min_y, 2));

	std::for_each(v.begin(), v.end(), [min_x, min_y, divmod](pt& p) {
		p.x -= min_x;
		p.x /= divmod;
		p.y -= min_y;
		p.y /= divmod;
		std::cout << p.x << " " << p.y << "\n";
	});
}

namespace TimeSeriesUtils {

	double CalculateEuclideanDistance(pt& p1, pt& p2) {
		return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
	}	

	double CalculateDynamicTimeWarpedDistance(std::deque<pt>& t0, std::deque<pt>& t1) {
		
        normalize(t0);
		normalize(t1);

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
