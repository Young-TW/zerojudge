#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        vector<tuple<char, char, int, string>> students;
        students.reserve(N);
        
        for (int i = 0; i < N; ++i) {
            string id, name;
            cin >> id >> name;
            char college = id[8];
            char degree = id[0];
            students.emplace_back(college, degree, i, name);
        }
        
        sort(students.begin(), students.end());
        
        for (const auto& s : students) {
            cout << get<0>(s) << ": " << get<3>(s) << "\n";
        }
    }
    
    return 0;
}
