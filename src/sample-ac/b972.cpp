#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, t;
    while (cin >> n >> t) {
        vector<int> times(t, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < t; ++j) {
                int m, s;
                char colon;
                cin >> m >> colon >> s;
                times[j] += m * 60 + s;
            }
        }
        sort(times.begin(), times.end());
        for (int i = 0; i < t; ++i) {
            cout << times[i] << "\n";
        }
    }
    return 0;
}
