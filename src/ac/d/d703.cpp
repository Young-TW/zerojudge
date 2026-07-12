#include <iostream>
#include <vector>
#include <string>
using namespace std;

void generate(int n, int m, string current) {
    if (n == 0 && m == 0) {
        cout << current << endl;
        return;
    }
    if (n > 0) {
        generate(n - 1, m, current + 'S');
    }
    if (m > 0) {
        generate(n, m - 1, current + 'L');
    }
}

int main() {
    int n, m;
    bool first = true;
    while (cin >> n >> m) {
        if (!first) {
            cout << endl;
        }
        first = false;
        generate(n, m, "");
    }
    return 0;
}
