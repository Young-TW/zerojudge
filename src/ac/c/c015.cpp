#include <iostream>

using namespace std;

unsigned long long reverse_num(unsigned long long n) {
    unsigned long long r = 0;
    while (n > 0) {
        r = r * 10 + n % 10;
        n /= 10;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        while (N--) {
            unsigned long long P;
            cin >> P;
            int cnt = 0;
            do {
                P += reverse_num(P);
                cnt++;
            } while (P != reverse_num(P));
            cout << cnt << " " << P << "\n";
        }
    }
    return 0;
}
