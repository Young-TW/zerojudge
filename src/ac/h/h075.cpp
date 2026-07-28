#include <bits/stdc++.h>
using namespace std;

struct Student {
    int id;
    int info;
    int math;
    int eng;
    int sum;            // 5*info + 3*math + 2*eng
};

bool cmp(const Student& a, const Student& b) {
    if (a.sum != b.sum) return a.sum > b.sum;
    if (a.info != b.info) return a.info > b.info;
    if (a.math != b.math) return a.math > b.math;
    if (a.eng != b.eng)   return a.eng > b.eng;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Student> v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) {
            Student s;
            cin >> s.id >> s.info >> s.math >> s.eng;
            s.sum = s.info * 5 + s.math * 3 + s.eng * 2;
            v.push_back(s);
        }
        sort(v.begin(), v.end(), cmp);
        for (const auto& s : v) {
            cout << s.id << ' ';
            if (s.sum % 10 == 0) {
                cout << s.sum / 10;
            } else {
                cout << s.sum / 10 << '.' << s.sum % 10;
            }
            cout << '\n';
        }
    }
    return 0;
}
