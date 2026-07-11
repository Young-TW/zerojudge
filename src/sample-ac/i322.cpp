#include <iostream>

using namespace std;

void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n - 1, from, aux, to);
    cout << "Move disc " << n << " from " << from << " to " << to << "\n";
    hanoi(n - 1, aux, to, from);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        hanoi(n, 'A', 'C', 'B');
    }
    return 0;
}
