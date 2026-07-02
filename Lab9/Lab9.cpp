#include <iostream>
using namespace std;

template <typename T>
class Calculator {
  public:
    explicit Calculator(T a, T b) : x(a), y(b) {}
    T add() {
        return x + y;
    }
    T subtract() {
        return x - y;
    }
    T getX() const {
        return x;
    }
    T getY() const {
        return y;
    }

  private:
    T x;
    T y;
};

int main() {
    Calculator<int> Int(10, 20);
    Calculator<double> Double(5.2, 2.8);
    cout << Int.getX() << " + " << Int.getY() << " = " << Int.add() << endl;
    cout << Int.getX() << " - " << Int.getY() << " = " << Int.subtract() << endl;
    cout << Double.getX() << " + " << Double.getY() << " = " << Double.add() << endl;
    cout << Double.getX() << " - " << Double.getY() << " = " << Double.subtract() << endl;
    return 0;
}