#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, t, w;
    while (cin >> s >> t >> w) {
        string str;
        cin >> str;
        
        vector<int> a(w);
        for (int i = 0; i < w; ++i) {
            a[i] = str[i] - 'a' + 1;
        }

        for (int k = 0; k < 5; ++k) {
            int i = w - 1;
            while (i >= 0 && a[i] == t - w + 1 + i) {
                --i;
            }
            
            if (i < 0) {
                break;
            }
            
            a[i]++;
            for (int j = i + 1; j < w; ++j) {
                a[j] = a[j - 1] + 1;
            }
            
            for (int j = 0; j < w; ++j) {
                cout << (char)('a' + a[j] - 1);
            }
            cout << '\n';
        }
    }
    return 0;
}
