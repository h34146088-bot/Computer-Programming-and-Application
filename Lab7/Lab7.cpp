#include <iostream>
#include <vector>
using namespace std;

class Media {
  public:
    Media(const string &t) : title(t) {};
    virtual void showType() const = 0;
    virtual ~Media() {};

  private:
    string title;
};

class Book : public Media {
  public:
    Book(const string &t) : Media(t) {};
    virtual void showType() const override {
        cout << "This is a physical text." << endl;
    };
};

class DVD : public Media {
  public:
    DVD(const string &t) : Media(t) {};
    virtual void showType() const override {
        cout << "This is a digital media." << endl;
    };
};

int main() {
    Book book("Harry Potter");
    DVD dvd("Titanic");
    vector<Media *> medias(2);
    medias[0] = &book;
    medias[1] = &dvd;
    for(Media *m : medias) {
        m->showType();
    }
    return 0;
}