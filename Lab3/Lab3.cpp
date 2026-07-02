#include <iostream>
using namespace std;

class Rectangle {
  public:
    Rectangle();
    void setRectangle(int, int);
    double calPerimeter();
    double calArea();
    double getLength();
    double getWidth();

  private:
    double length = 1;
    double width = 1;
};

Rectangle::Rectangle() {
}

void Rectangle::setRectangle(int l, int w) {
    length = (l > 0) ? l : 1.0;
    width = (w > 0) ? w : 1.0;
}

double Rectangle::calPerimeter() {
    return 2 * (length + width);
}

double Rectangle::calArea() {
    return (length * width);
}

double Rectangle::getLength() {
    return length;
}

double Rectangle::getWidth() {
    return width;
}

int main() {
    Rectangle a;
    Rectangle b;
    a.setRectangle(0, 2);
    b.setRectangle(5, 2);
    cout << "Rectangle a" << endl;
    cout << "width: " << a.getWidth() << endl;
    cout << "length: " << a.getLength() << endl;
    cout << "perimeter: " << a.calPerimeter() << endl;
    cout << "area: " << a.calArea() << endl;
    cout << "Rectangle b" << endl;
    cout << "width: " << b.getWidth() << endl;
    cout << "length: " << b.getLength() << endl;
    cout << "perimeter: " << b.calPerimeter() << endl;
    cout << "area: " << b.calArea() << endl;
}