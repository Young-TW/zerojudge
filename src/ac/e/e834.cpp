#include <iostream>
using namespace std;

int main() {
    int M;
    while (cin >> M) {
        int T;
        while (cin >> T && T != 0) {
            if (T % M == 0) {
                cout << T / M << endl;
            } else {
                cout << M - (T % M) << endl;
            }
        }
    }
    return 0;
}
