#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

class InvalidDurationException : public runtime_error {
  public:
    explicit InvalidDurationException(const string &msg)
        : runtime_error(msg) {}
};

double fetchTrackDuration(int trackId) {
    if(trackId < 0) {
        throw invalid_argument("Track ID cannot be negative!");
    }

    else if(trackId == 999) {
        throw InvalidDurationException("Corrupted stream: Track duration is negative!");
    } else {
        return 60;
    }
}

int main() {
    vector<int> queue = {-5, 12, 999, 45, 23};
    for(int q : queue) {
        try {
            double dur = fetchTrackDuration(q);
            cout << "Track " << q << " duration: " << dur << " seconds" << endl;
        } catch(const exception &ex) {
            cout << "Exception occurred: " << ex.what() << endl;
        }
    }
}