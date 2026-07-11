#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>

using namespace std;

struct Medicine {
    long long t;
    int idx;
    int f;
    string m;
    
    bool operator>(const Medicine& other) const {
        if (t != other.t) {
            return t > other.t;
        }
        return idx > other.idx;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    while (cin >> T) {
        while (T--) {
            int n, k;
            cin >> n >> k;
            priority_queue<Medicine, vector<Medicine>, greater<Medicine>> pq;
            for (int i = 0; i < n; ++i) {
                string m;
                int f;
                cin >> m >> f;
                pq.push({f, i, f, m});
            }
            for (int i = 0; i < k; ++i) {
                Medicine med = pq.top();
                pq.pop();
                cout << med.t << " " << med.m << "\n";
                med.t += med.f;
                pq.push(med);
            }
        }
    }
    return 0;
}
