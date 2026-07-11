#include <iostream>
using namespace std;

int main() {
    int N, K, W;
    while (cin >> N >> K >> W) {
        int total = N;
        int available = N;
        while (available >= K) {
            int exchanges = available / K;
            int new_phones = exchanges * W;
            total += new_phones;
            available = available % K + new_phones;
        }
        cout << total << endl;
    }
    return 0;
}
