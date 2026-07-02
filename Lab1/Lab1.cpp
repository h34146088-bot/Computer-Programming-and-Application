#include <iostream>
#include <vector>
using namespace std;

int main(){
    int numberOfStudents;
    int totalScore = 0;
    int max, min;
    cout << "Enter the number of students: ";
    cin >> numberOfStudents;
    vector <int> score (numberOfStudents);
    for(int i = 0; i < numberOfStudents; i++){
        cout << "Enter the score of " << i + 1 << "th student: ";
        cin >> score.at(i);
    }
    max = score.at(0);
    min = score.at(0);
    for(int score :score){
        totalScore += score;
        if(score > max){
            max = score;
        }
        if(score < min){
            min = score;
        }
    }
    cout << "The average score is: " << (double)totalScore / numberOfStudents << endl;
    cout << "The highest score is: " << max << endl;
    cout << "The lowest score is: " << min << endl;
    return 0;
}
