#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Fort {
    int a;
    int b;
};

bool cmp(const Fort& f1, const Fort& f2) {
    return f1.a * f2.b < f2.a * f1.b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        vector<Fort> forts(N);
        for (int i = 0; i < N; ++i) {
            cin >> forts[i].a >> forts[i].b;
        }
        sort(forts.begin(), forts.end(), cmp);
        
        long long M = 100000007;
        long long T = 0;
        for (int i = 0; i < N; ++i) {
            T = (forts[i].a + (1LL + forts[i].b) * T) % M;
        }
        cout << T << "\n";
    }
    return 0;
}
