#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    int info;
    int math;
    int eng;
    int total;
};

bool cmp(const Student& a, const Student& b) {
    if (a.total != b.total) return a.total > b.total;
    if (a.info != b.info) return a.info > b.info;
    if (a.math != b.math) return a.math > b.math;
    if (a.eng != b.eng) return a.eng > b.eng;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        vector<Student> students(n);
        for (int i = 0; i < n; ++i) {
            cin >> students[i].id >> students[i].info >> students[i].math >> students[i].eng;
            students[i].total = students[i].info * 5 + students[i].math * 3 + students[i].eng * 2;
        }
        sort(students.begin(), students.end(), cmp);
        for (int i = 0; i < n; ++i) {
            cout << students[i].id << " " << students[i].total / 10 << "\n";
        }
    }
    return 0;
}
