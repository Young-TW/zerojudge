#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Student {
    int id;
    string name;
    int ch, en, ma, so, na;
    int total;
};

bool cmp(const Student& a, const Student& b) {
    if (a.total != b.total) {
        return a.total > b.total;
    }
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<Student> students(N);
        for (int i = 0; i < N; ++i) {
            cin >> students[i].id >> students[i].name 
                >> students[i].ch >> students[i].en >> students[i].ma 
                >> students[i].so >> students[i].na;
            students[i].total = students[i].ch + students[i].en + students[i].ma 
                              + students[i].so + students[i].na;
        }
        
        sort(students.begin(), students.end(), cmp);
        
        int rank = 1;
        for (int i = 0; i < N; ++i) {
            if (i > 0 && students[i].total != students[i - 1].total) {
                rank = i + 1;
            }
            cout << students[i].id << " " << students[i].name << " " 
                 << students[i].ch << " " << students[i].en << " " 
                 << students[i].ma << " " << students[i].so << " " 
                 << students[i].na << " " << students[i].total << " " 
                 << rank << "\n";
        }
    }
    
    return 0;
}
