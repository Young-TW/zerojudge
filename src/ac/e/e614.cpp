#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        while (N--) {
            long long a, b, c;
            cin >> a >> b >> c;
            if (a + b > c && a + c > b && b + c > a) {
                cout << "OK\n";
            } else {
                cout << "Wrong!!\n";
            }
        }
    }
    
    return 0;
}
