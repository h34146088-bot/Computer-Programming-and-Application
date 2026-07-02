#include <iostream>
using namespace std;

class Vector2D {
    friend Vector2D operator*(const int, const Vector2D &);
    friend double operator*(const Vector2D &, const Vector2D &);
    friend ostream &operator<<(ostream &, const Vector2D &);

  public:
    Vector2D(double = 0, double = 0);
    Vector2D operator*(const int);

  private:
    double x;
    double y;
};

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator*(const int scalar) {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D operator*(const int scalar, const Vector2D &v) {
    return Vector2D(v.x * scalar, v.y * scalar);
}

double operator*(const Vector2D &v1, const Vector2D &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

ostream &operator<<(ostream &os, const Vector2D &v) {
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}

int main() {
    Vector2D v1(2, 5);
    Vector2D v2(6, 8);
    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 * 3 = " << v1 * 3 << endl;
    cout << "4 * v2 = " << 4 * v2 << endl;
    cout << "v1 * v2 = " << v1 * v2 << endl;
    return 0;
}