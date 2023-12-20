// Copyright (c) 2023 Kosuke Suzuki
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#include <point_in_polygon/point_in_polygon.hpp>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


PointInPolygon::PointInPolygon() : polygons_initialized_(false) {}

PointInPolygon::PointInPolygon(const PointInPolygon::Polygon& polygon) : polygons_initialized_(false)
{
	set_polygon(polygon);
}

PointInPolygon::PointInPolygon(const std::vector<PointInPolygon::Polygon>& polygons) : polygons_initialized_(false)
{
	set_polygons(polygons);
}

void PointInPolygon::set_polygon(const PointInPolygon::Polygon& polygon)
{
	polygons_.clear();
	polygons_.push_back(polygon);
	polygons_initialized_ = true;
}

void PointInPolygon::set_polygons(const std::vector<PointInPolygon::Polygon>& polygons)
{
	polygons_ = polygons;
	polygons_initialized_ = true;
}

void PointInPolygon::add_polygon(const PointInPolygon::Polygon& polygon)
{
	polygons_.push_back(polygon);
	polygons_initialized_ = true;
}

void PointInPolygon::add_polygons(const std::vector<PointInPolygon::Polygon>& polygons)
{
	polygons_.insert(polygons_.end(), polygons.begin(), polygons.end());
	polygons_initialized_ = true;
}

bool PointInPolygon::is_inside(const PointInPolygon::Point& point) const
{
	if (!polygons_initialized_)
	{
		std::cerr << "Polygons are not initialized." << std::endl;
		return false;
	}

	for (const auto& polygon : polygons_)
		if (is_inside_polygon(point, polygon))
			return true;

	return false;
}

bool PointInPolygon::is_inside(const double x, const double y) const
{
	return is_inside(Point(x, y));
}

bool PointInPolygon::is_overlapping(const PointInPolygon::Line& line1, const PointInPolygon::Line& line2) const
{
	double s, t;
	s = (line2.p1.x - line2.p2.x) * (line1.p1.y - line2.p1.y) + (line2.p1.y - line2.p2.y) * (line2.p1.x - line1.p1.x);
	t = (line2.p1.x - line2.p2.x) * (line1.p2.y - line2.p1.y) + (line2.p1.y - line2.p2.y) * (line2.p1.x - line1.p2.x);
	if (s * t >= 0)
		return false;

	s = (line1.p1.x - line1.p2.x) * (line2.p1.y - line1.p1.y) + (line1.p1.y - line1.p2.y) * (line1.p1.x - line2.p1.x);
	t = (line1.p1.x - line1.p2.x) * (line2.p2.y - line1.p1.y) + (line1.p1.y - line1.p2.y) * (line1.p1.x - line2.p2.x);
	if (s * t >= 0)
		return false;

	return true;
}

bool PointInPolygon::is_inside_polygon(const PointInPolygon::Point& point, const PointInPolygon::Polygon& polygon) const
{
	// Get furthest distance and angles to each point of the polygon
	double max_distance = 0;
	std::vector<double> angles;
	for (const auto& point_p : polygon.points)
	{
		double distance = std::sqrt(
			(point_p.x - point.x) * (point_p.x - point.x)
			+ (point_p.y - point.y) * (point_p.y - point.y)
		);
		if (distance > max_distance)
			max_distance = distance;
		
		angles.push_back(std::atan2(point_p.y - point.y, point_p.x - point.x));
	}

	// Sort angles
	std::sort(angles.begin(), angles.end());

	// Get angle to check for overlaps
	double search_angle = 0;
	for (size_t i = 0; i < angles.size() - 1; i++)
	{
		if (angles[i] != angles[i+1])
		{
			search_angle = (angles[i] + angles[i+1]) / 2.0;
			break;
		}
	}

	// Get target point to check for overlaps
	PointInPolygon::Point target_point;
	target_point.x = point.x + 2 * max_distance * std::cos(search_angle);
	target_point.y = point.y + 2 * max_distance * std::sin(search_angle);

	// Count overlaps
	uint overlap_count = 0;
	for (size_t i = 0; i < polygon.points.size(); i++)
	{
		size_t j = (i + 1) % polygon.points.size();
		if (is_overlapping(Line(point, target_point), Line(polygon.points[i], polygon.points[j])))
			overlap_count++;
	}

	// If overlaps are odd, the point is inside the polygon
	if (overlap_count % 2 == 1)
		return true;
	else
		return false;
}
