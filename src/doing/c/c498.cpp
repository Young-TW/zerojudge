#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    string A, B;
    int T;
    while (cin >> A >> B >> T) {
        int lenA = A.size();
        int lenB = B.size();
        int total = 0;

        for (int t = 0; t < T; ++t) {
            char a = A[t % lenA];
            char b = B[t % lenB];
            int diff = abs((a - 'a') - (b - 'a'));
            total += 26 - diff;
        }

        cout << total << endl;
    }
    return 0;
}
