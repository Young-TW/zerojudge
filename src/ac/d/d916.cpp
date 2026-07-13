#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    string line;
    while (getline(cin, line)) {
        for (char &c : line) {
            if (c == 'l' || c == 'I') c = '1';
            if (c == 'O' || c == 'o') c = '0';
        }
        stringstream ss(line);
        int N, M;
        while (ss >> N >> M) {
            if (N <= 0) continue;
            vector<int> f(N + 1);
            f[0] = 1;
            for (int i = 1; i <= N; i++) {
                int prev = (i - M - 1 < 0) ? 1 : f[i - M - 1];
                f[i] = (f[i - 1] + prev) % 10000;
            }
            cout << f[N] << endl;
        }
    }
    return 0;
}
