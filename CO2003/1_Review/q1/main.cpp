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

int main()
{
    /*
    Point A(2, 3);
    cout << A.getX() << " " << A.getY() << endl; // 2 3
    */

    Point A(2, 3);
    Point B(1, 1);
    cout << pow(A.distanceToPoint(B), 2); // 5

    return 0;
}