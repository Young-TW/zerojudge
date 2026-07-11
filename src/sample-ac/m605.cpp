#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int N;
    while (cin >> N) {
        if (N < 2) {
            cout << endl;
            continue;
        }
        
        vector<bool> isPrime(N + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= N; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= N; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        map<int, int> expCount;
        for (int p = 2; p <= N; p++) {
            if (isPrime[p]) {
                int exp = 0;
                int temp = N;
                while (temp >= p) {
                    temp /= p;
                    exp += temp;
                }
                expCount[exp]++;
            }
        }
        
        bool first = true;
        for (auto it = expCount.rbegin(); it != expCount.rend(); ++it) {
            if (!first) cout << " ";
            first = false;
            if (it->second >= 2) {
                cout << it->second << "*" << it->first;
            } else {
                cout << it->first;
            }
        }
        cout << endl;
    }
    return 0;
}
