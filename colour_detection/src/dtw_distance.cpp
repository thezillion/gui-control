#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <opencv2/opencv.hpp>
#include "../include/dtw_distance.hpp"

typedef std::pair<double, double> PDD;

double mod(pt& p) {
	return std::pow(p.x, 2) + std::pow(p.y, 2);
}

bool comp(pt& a, pt& b) {
	return mod(a) < mod(b);
}

void normalize(std::deque<pt>& v, std::vector<PDD>& norm) {
	auto max_pt = std::max_element(v.begin(), v.end(), comp);
	auto min_pt = std::min_element(v.begin(), v.end(), comp);
	
	double max_x = max_pt->x, max_y = max_pt->y, min_x = min_pt->x, min_y = min_pt->y, norm_x, norm_y;

	double divmod = std::sqrt(std::pow(max_x - min_x, 2) + std::pow(max_y - min_y, 2));

	std::cout << "\n\nStarting normalization\n\n";

	std::for_each(v.begin(), v.end(), [min_x, min_y, divmod, &norm, &norm_x, &norm_y](pt& p) {
		std::cout << "gesture.push_back(Hand(" << p.x << ", " << p.y << "));\n";
		p.x -= min_x;
		p.x /= divmod;
		p.y -= min_y;
		p.y /= divmod;
		norm_x = (double)(p.x - min_x) / divmod;
		norm_y = (double)(p.y - min_y) / divmod;
		norm.push_back(std::make_pair(norm_x, norm_y));
	});
}

namespace TimeSeriesUtils {

	double CalculateEuclideanDistance(PDD& p1, PDD& p2) {
		return std::sqrt(std::pow((p1.first - p2.first), 2) + std::pow((p1.second - p2.second), 2));
	}	

	double CalculateDynamicTimeWarpedDistance(std::deque<pt>& t0, std::deque<pt>& t1) {
		
        std::vector<PDD> norm0;
		normalize(t0, norm0);
		std::vector<PDD> norm1;
		normalize(t1, norm1);

		size_t m = norm0.size();
		size_t n = norm1.size();

		// Allocate the Matrix to work on:
		std::vector<std::vector<double>> cost(m, std::vector<double>(n));

		cost[0][0] = CalculateEuclideanDistance(norm0[0], norm1[0]);

		// Calculate the first row:
		for (int i = 1; i < m; i++) {
			cost[i][0] = cost[i - 1][0] + CalculateEuclideanDistance(norm0[i], norm1[0]);
		}

		// Calculate the first column:
		for (int j = 1; j < n; j++) {
			cost[0][j] = cost[0][j - 1] + CalculateEuclideanDistance(norm0[0], norm1[j]);
		}

		// Fill the matrix:
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				cost[i][j] = std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1])) 
					+ CalculateEuclideanDistance(norm0[i], norm1[j]);
			}
		}
	
		return cost[m-1][n-1];
	}

}
