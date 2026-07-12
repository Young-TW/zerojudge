#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unsigned int N, M;
    while (cin >> N >> M) {
        cout << ((N >> (M - 1)) & 1) << '\n';
    }
    
    return 0;
}
