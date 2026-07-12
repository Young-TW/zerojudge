#include <iostream>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int finger_mask[128] = {0};
    finger_mask['c'] = (1<<1)|(1<<2)|(1<<3)|(1<<6)|(1<<7)|(1<<8)|(1<<9);
    finger_mask['d'] = (1<<1)|(1<<2)|(1<<3)|(1<<6)|(1<<7)|(1<<8);
    finger_mask['e'] = (1<<1)|(1<<2)|(1<<3)|(1<<6)|(1<<7);
    finger_mask['f'] = (1<<1)|(1<<2)|(1<<3)|(1<<6);
    finger_mask['g'] = (1<<1)|(1<<2)|(1<<3);
    finger_mask['a'] = (1<<1)|(1<<2);
    finger_mask['b'] = (1<<1);
    finger_mask['C'] = (1<<2);
    finger_mask['D'] = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<6)|(1<<7)|(1<<8);
    finger_mask['E'] = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<6)|(1<<7);
    finger_mask['F'] = (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<6);
    finger_mask['G'] = (1<<0)|(1<<1)|(1<<2)|(1<<3);
    finger_mask['A'] = (1<<0)|(1<<1)|(1<<2);
    finger_mask['B'] = (1<<0)|(1<<1);

    int t;
    while (cin >> t) {
        cin.ignore();
        while (t--) {
            string s;
            getline(cin, s);
            if (!s.empty() && s.back() == '\r') {
                s.pop_back();
            }
            int count[10] = {0};
            int current_mask = 0;
            for (char ch : s) {
                int next_mask = finger_mask[(unsigned char)ch];
                int pressed = next_mask & ~current_mask;
                for (int i = 0; i < 10; ++i) {
                    if (pressed & (1 << i)) {
                        count[i]++;
                    }
                }
                current_mask = next_mask;
            }
            for (int i = 0; i < 10; ++i) {
                cout << count[i] << (i == 9 ? "" : " ");
            }
            cout << "\n";
        }
    }
    return 0;
}
