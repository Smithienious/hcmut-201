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

    Circle(const Circle &circle)
    {
        /*
         * STUDENT ANSWER
         */
        center.setX(circle.center.getX());
        center.setY(circle.center.getY());
        radius = circle.getRadius();
    }

    void setCenter(Point point)
    {
        /*
         * STUDENT ANSWER
         */
        center.setX(point.getX());
        center.setY(point.getY());
    }

    void setRadius(double radius)
    {
        /*
         * STUDENT ANSWER
         */
        this->radius = radius;
    }

    Point getCenter() const
    {
        /*
         * STUDENT ANSWER
         */
        return center;
    }

    double getRadius() const
    {
        /*
         * STUDENT ANSWER
         */
        return radius;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main()
{
    Circle A;
    A.printCircle();

    return 0;
}