#include <bits/stdc++.h>

using namespace std;

class Point
{
private:
    double x, y;

public:
    Point()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero x-y coordinate
         */
        x = 0;
        y = 0;
    }

    Point(double x, double y)
    {
        /*
         * STUDENT ANSWER
         */
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        /*
         * STUDENT ANSWER
         */
        this->x = x;
    }

    void setY(double y)
    {
        /*
         * STUDENT ANSWER
         */
        this->y = y;
    }

    double getX() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->x;
    }

    double getY() const
    {
        /*
         * STUDENT ANSWER
         */
        return this->y;
    }

    double distanceToPoint(const Point &pointA)
    {
        /*
         * STUDENT ANSWER
         * TODO: calculate the distance from this point to point A in the coordinate plane
         */
        double dis = pow((pointA.x - this->x), 2) + pow((pointA.y - this->y), 2);
        return sqrt(dis);
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero center's x-y and radius
         */
        center.setX(0);
        center.setY(0);
        radius = 0;
    }

    Circle(Point center, double radius)
    {
        /*
         * STUDENT ANSWER
         */
        this->center.setX(center.getX());
        this->center.setY(center.getY());
        this->radius = radius;
    }

    bool containsPoint(const Point point)
    {
        /*
         * STUDENT ANSWER
         * TODO: check if a given point is entirely within the circle (does not count if the point lies on the circle).  
            If contain, return true.
         */
        return (pow(point.getX() - center.getX(), 2) + pow(point.getY() - center.getY(), 2)) < pow(radius, 2);
    }

    bool containsTriangle(const Point pointA, const Point pointB, const Point pointC)
    {
        /*
         * STUDENT ANSWER
         * TODO: check if a given triangle ABC (A, B, C are not on the same line) is entirely within the circle (does not count if any point of the triangle lies on the circle).  
            If contain, return true.
         */
        return ((pow(pointA.getX() - center.getX(), 2) + pow(pointA.getY() - center.getY(), 2)) < pow(radius, 2)) &&
               ((pow(pointB.getX() - center.getX(), 2) + pow(pointB.getY() - center.getY(), 2)) < pow(radius, 2)) &&
               ((pow(pointC.getX() - center.getX(), 2) + pow(pointC.getY() - center.getY(), 2)) < pow(radius, 2));
    }
};

int main()
{
    Point pointO(0, 2);
    Point point1(1, 2);
    Circle A = Circle(pointO, 2);
    cout << A.containsPoint(point1);

    return 0;
}