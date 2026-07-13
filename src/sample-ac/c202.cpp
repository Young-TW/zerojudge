#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string token;
    while (cin >> token) {
        if (!token.empty() && isdigit((unsigned char)token[0])) {
            int n = stoi(token);
            int g = 0;
            for (int i = 0; i < n; ++i) {
                int x;
                cin >> x;
                if (i == 0) g = x;
                else g = gcd(g, x);
            }
            cout << g << "\n";
        } else {
            size_t pos = token.find("輸入");
            if (pos != string::npos) {
                token.replace(pos, 6, "輸出");
            }
            cout << token << "\n";
        }
    }
    return 0;
}
