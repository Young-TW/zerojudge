#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

string base64_encode(const string &in) {
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) {
        out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }
    while (out.size() % 4) {
        out.push_back('=');
    }
    return out;
}

string base64_decode(const string &in) {
    string out;
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) {
        T[base64_chars[i]] = i;
    }

    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    char op;
    string s;
    while (cin >> op) {
        cin.ignore();
        getline(cin, s);
        if (op == 'e') {
            cout << base64_encode(s) << '\n';
        } else if (op == 'd') {
            cout << base64_decode(s) << '\n';
        }
    }
    return 0;
}
