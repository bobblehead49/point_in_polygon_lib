// Copyright (c) 2023 Kosuke Suzuki
// Released under the MIT license
// https://opensource.org/licenses/mit-license.php

#ifndef POINT_IN_POLYGON_HPP_
#define POINT_IN_POLYGON_HPP_

#include <vector>


class PointInPolygon
{
public:
    struct Point
    {
        double x;
        double y;
        Point() : x(0.0), y(0.0) {}
        Point(const double x, const double y) : x(x), y(y) {}
    };

    struct Line
    {
        Point p1;
        Point p2;
        Line() : p1(), p2() {}
        Line(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}
    };

    struct Polygon
    {
        std::vector<Point> points;
    };

    /**
     * @brief Point in polygon discrimination class.
    */
    PointInPolygon();

    /**
     * @brief Point in polygon discrimination class.
     * @param[in] polygon A polygon to set.
    */
    PointInPolygon(const PointInPolygon::Polygon& polygon);

    /**
     * @brief Point in polygon discrimination class.
     * @param[in] polygons Polygons to set.
    */
    PointInPolygon(const std::vector<PointInPolygon::Polygon>& polygons);

    /**
     * @brief Remove all polygons and set a new polygon.
     * @param[in] polygon A polygon to set.
    */
    void set_polygon(const PointInPolygon::Polygon& polygon);

    /**
     * @brief Remove all polygons and set new multiple polygons.
     * @param[in] polygons Polygons to set.
    */
    void set_polygons(const std::vector<PointInPolygon::Polygon>& polygons);

    /**
     * @brief Add a single polygon.
     * @param[in] polygon A polygon to add.
    */
    void add_polygon(const PointInPolygon::Polygon& polygon);

    /**
     * @brief Add multiple polygons.
     * @param[in] polygons Polygons to add.
    */
    void add_polygons(const std::vector<PointInPolygon::Polygon>& polygons);

    /**
     * @brief Check if the point is overlapping one of the polygons.
     * @param[in] point A point to check.
     * @return True if the point is overlapping one of the polygons.
    */
    bool is_inside(const PointInPolygon::Point& point) const;

    /**
     * @brief Check if the point is inside one of the polygons.
     * @param[in] x X coordinate of the point.
     * @param[in] y Y coordinate of the point.
     * @return True if the point is inside one of the polygons.
    */
    bool is_inside(const double x, const double y) const;

private:
    /**
     * @brief True if polygons are set.
    */
    bool polygons_initialized_;

    /**
     * @brief Polygons to check if the point is inside.
    */
    std::vector<PointInPolygon::Polygon> polygons_;

    /**
     * @brief Check if lines are overlapping.
     * @param[in] line1 First line.
     * @param[in] line2 Second line.
     * @return True if line1 and line2 are overlapping.
    */
    bool is_overlapping(const PointInPolygon::Line& line1, const PointInPolygon::Line& line2) const;

    /**
     * @brief Check if the point is inside the polygon.
     * @param[in] point A point to check.
     * @param[in] polygon A polygon to check.
     * @return True if the point is inside the polygon.
    */
    bool is_inside_polygon(const PointInPolygon::Point& point, const PointInPolygon::Polygon& polygon) const;
};


#endif // POINT_IN_POLYGON_HPP_
