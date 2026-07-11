#include <iostream>

using namespace std;

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n - 1, from, aux, to);
    cout << "Move ring " << n << " from " << from << " to " << to << "\n";
    hanoi(n - 1, aux, to, from);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    bool first = true;
    while (cin >> n) {
        if (!first) {
            cout << "\n";
        }
        first = false;
        hanoi(n, 'A', 'C', 'B');
    }
    
    return 0;
}
