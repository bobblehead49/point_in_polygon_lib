// Copyright (c) 2023 Kosuke Suzuki
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#include "../include/point_in_polygon/point_in_polygon.hpp"

#include <iostream>


int main(int argc, char **argv)
{
	// Create polygon
	PointInPolygon::Polygon polygon;
	polygon.points.push_back(PointInPolygon::Point(0.0, 0.0));
	polygon.points.push_back(PointInPolygon::Point(1.0, 0.0));
	polygon.points.push_back(PointInPolygon::Point(1.0, 1.0));
	polygon.points.push_back(PointInPolygon::Point(0.0, 1.0));

	// Print polygon
	std::cout << "Polygon:" << std::endl;
	for (const auto& point : polygon.points)
		std::cout << "  (" << point.x << ", " << point.y << ")" << std::endl;

	// Create point in polygon discrimination class
	PointInPolygon point_in_polygon(polygon);

	// Discriminate whether the point is inside the polygon
	double x, y;
	while (true)
	{
		// Input point coordinate
		std::cout << "Input point coordinate." << std::endl;
		std::cout << "\tx: ";
		std::cin >> x;
		std::cout << "\ty: ";
		std::cin >> y;

		// Discriminate
		PointInPolygon::Point point(x, y);
		std::cout << "Point (" << point.x << ", " << point.y << ") is ";
		if (!point_in_polygon.is_inside(point))
			std::cout << "not ";
		std::cout << "inside the polygon." << std::endl;
	}

	return 0;
}