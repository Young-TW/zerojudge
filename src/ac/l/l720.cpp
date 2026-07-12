#include <iostream>
#include <string>
using namespace std;

int main() {
    int l;
    while (cin >> l) {
        string n;
        cin >> n;
        char s;
        int h;
        cin >> s >> h;

        if (s == 'b') {
            for (int i = 0; i < l; ++i) {
                n[i] += h;
            }
        } else if (s == 's') {
            for (int i = 0; i < l; ++i) {
                n[i] -= h;
            }
        }

        cout << n << endl;
    }
    return 0;
}
