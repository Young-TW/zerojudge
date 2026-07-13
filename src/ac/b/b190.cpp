#include <iostream>

using namespace std;

int steps = 0;

void move(int ring, char from, char to) {
    cout << "ring " << ring << " : " << from << " -> " << to << "\n";
    steps++;
}

char get_other(char x, char y) {
    if (x != 'a' && y != 'a') return 'a';
    if (x != 'b' && y != 'b') return 'b';
    return 'c';
}

void hanoi_normal(int m, char from, char to, char other) {
    if (m == 0) return;
    hanoi_normal(m - 1, from, other, to);
    move(m, from, to);
    hanoi_normal(m - 1, other, to, from);
}

void hanoi_special(int m, char from, char target_odd, char target_even) {
    if (m == 0) return;
    char target_m = (m % 2 == 1) ? target_odd : target_even;
    if (from == target_m) {
        hanoi_special(m - 1, from, target_odd, target_even);
    } else {
        char other = get_other(from, target_m);
        hanoi_normal(m - 1, from, other, target_m);
        move(m, from, target_m);
        hanoi_special(m - 1, other, target_odd, target_even);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while (cin >> n) {
        steps = 0;
        hanoi_special(n, 'a', 'b', 'c');
        cout << "共移動了 " << steps << " 步\n";
    }
    return 0;
}
