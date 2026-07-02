#include <cmath>
#include <iostream>
#include <string>
using namespace std;

class Shape {
  public:
    Shape(const string &);
    double area();
    void display();
    string getName();

  private:
    string name;
};

Shape::Shape(const string &n) : name(n) {
}

double Shape::area() {
    return 0.0;
}

void Shape::display() {
    cout << name << endl;
}

string Shape::getName() {
    return name;
}

class Rectangle : public Shape {
  public:
    Rectangle(const string &, double, double);
    double area();
    void display();

  private:
    double length;
    double width;
};

Rectangle::Rectangle(const string &n, double l, double w)
    : Shape(n), length(l), width(w) {
}

double Rectangle::area() {
    return length * width;
}

void Rectangle::display() {
    cout << "Shape's name: " << getName() << endl;
    cout << "Rectangle's length: " << length << endl;
    cout << "Rectangle's width: " << width << endl;
}

class Circle : public Shape {
  public:
    Circle(const string &n, double);
    double area();
    void display();

  private:
    double radius;
};

Circle::Circle(const string &n, double r)
    : Shape(n), radius(r) {
}

double Circle::area() {
    return radius * radius * acos(-1);
}

void Circle::display() {
    cout << "Shape's name: " << getName() << endl;
    cout << "Circle's radius: " << radius << endl;
}

int main() {
    Rectangle r("Rectangle", 5, 3);
    Circle c("Circle", 10);
    r.display();
    cout << "Area: " << r.area() << endl;
    c.display();
    cout << "Area: " << c.area() << endl;
}