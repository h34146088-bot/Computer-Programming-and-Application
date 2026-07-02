#include <iostream>
using namespace std;

class Love {
  public:
    Love(int j = 9, int i = 0);

    void hehehe() {
        cout << love;
    }

  private:
    int japan;
    const int love;
};

Love::Love(int j, int i)
    : japan(j),
      love(i) {
}

int main() {
    Love a;
    a.hehehe();
}