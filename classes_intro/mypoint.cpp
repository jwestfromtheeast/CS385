/*
 * mypoint.cpp
 *
 *  Created on: Feb 1, 2019
 *      Author: Brian
 */
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MyPoint {
public:
    // Constructor that uses an initializer list.
    // Brackets declare as a const, which helps with optimization. If can be const, be const
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { }

    // Methods that do not modify member variables should be declared const.
    void print_coords() const {
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
             << setprecision(2) << z_ << ")" << endl;
    }

    // Mutator
    void set_x(int x) {
        x_ = x;
    }

    // Accessor
    int get_x() const {
        return x_;
    }

private:
    // Member variables (fields). Use the trailing _ for these variables.
    int x_, y_;
    float z_;
};

void display_points(const vector<MyPoint> &points) {
    for (auto it = points.cbegin(); it != points.cend(); ++it) {
        it->print_coords();
    }
}

void display_points_v2(const vector<MyPoint> &points) {
    for (size_t i = 0; i < points.size(); i++) {
        points[i].print_coords();
    }
}

int main() {
    int x, y;

    MyPoint point1(5, 7, 1.9823412);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);

    vector<MyPoint> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

    vector<MyPoint> points_above_two;
    for (const auto &point : points) {
        if (point.get_x() > 2) {
            points_above_two.push_back(point);
        }
    }

    display_points(points_above_two);

    // Practice using standard in (STDIN)
    cout << "Input x: ";
    cin >> x;

    cout << "Input y: ";
    cin >> y;

    MyPoint *point4 = new MyPoint(x, y, 7);
    point4->print_coords();
    delete point4;

    return 0;
}
