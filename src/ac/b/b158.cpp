#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int chinese;
    int total;
};

bool cmp(const Student& a, const Student& b) {
    if (a.total != b.total) return a.total > b.total;
    if (a.chinese != b.chinese) return a.chinese > b.chinese;
    return a.id < b.id;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    bool first_case = true;
    while (cin >> n) {
        if (!first_case) {
            cout << "\n";
        }
        first_case = false;
        
        vector<Student> students(n);
        for (int i = 0; i < n; ++i) {
            int c, m, e;
            cin >> c >> m >> e;
            students[i].id = i + 1;
            students[i].chinese = c;
            students[i].total = c + m + e;
        }
        
        sort(students.begin(), students.end(), cmp);
        
        for (int i = 0; i < 5 && i < n; ++i) {
            cout << students[i].id << " " << students[i].total << "\n";
        }
    }
    
    return 0;
}
