#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int class_num;
    int seat_num;
    string intro;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<Student> students(n);
        for (int i = 0; i < n; ++i) {
            cin >> students[i].name >> students[i].class_num >> students[i].seat_num >> students[i].intro;
        }
        
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            if (a.class_num != b.class_num) {
                return a.class_num < b.class_num;
            }
            return a.seat_num < b.seat_num;
        });
        
        for (const auto& s : students) {
            cout << s.class_num << " " << s.seat_num << " " << s.name << "\n";
            cout << s.intro << "\n";
        }
    }
    
    return 0;
}
