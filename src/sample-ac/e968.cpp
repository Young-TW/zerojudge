#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    while (cin >> N) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int i = N; i >= 1; i--) {
            if (i != a && i != b && i != c) {
                cout << "No. " << i << "\n";
            }
        }
    }
    return 0;
}
