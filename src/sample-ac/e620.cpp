#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char keyboard[37] = {
        '1','q','a','z','2','w','s','x','e','d','c','r','f','v','5','t','g','b','y','h','n',
        'u','j','m',
        '8','i','k',',','9','o','l','.','0','p',';','/','-'};
    string Bopomofo[37] = {
        "ㄅ","ㄆ","ㄇ","ㄈ","ㄉ","ㄊ","ㄋ","ㄌ","ㄍ","ㄎ","ㄏ","ㄐ","ㄑ","ㄒ","ㄓ","ㄔ","ㄕ","ㄖ","ㄗ","ㄘ","ㄙ",
        "ㄧ","ㄨ","ㄩ",
        "ㄚ","ㄛ","ㄜ","ㄝ","ㄞ","ㄟ","ㄠ","ㄡ","ㄢ","ㄣ","ㄤ","ㄥ","ㄦ"};

    char tone_key[5] = {' ', '6', '3', '4', '7'};
    string tone_val[5] = {" ", "ˊ", "ˇ", "ˋ", "˙"};

    map<char, int> char_to_idx;
    for (int i = 0; i < 37; ++i) {
        char_to_idx[keyboard[i]] = i;
    }

    map<char, string> tone_map;
    for (int i = 0; i < 5; ++i) {
        tone_map[tone_key[i]] = tone_val[i];
    }

    string line;
    while (getline(cin, line)) {
        string initial = "", medial = "", final_char = "";
        for (char c : line) {
            if (c == '\r') continue;
            if (char_to_idx.count(c)) {
                int idx = char_to_idx[c];
                if (idx <= 20) {
                    initial = Bopomofo[idx];
                } else if (idx <= 23) {
                    medial = Bopomofo[idx];
                } else {
                    final_char = Bopomofo[idx];
                }
            } else if (tone_map.count(c)) {
                cout << initial << medial << final_char << tone_map[c];
                initial = medial = final_char = "";
            } else {
                if (!initial.empty() || !medial.empty() || !final_char.empty()) {
                    cout << initial << medial << final_char;
                    initial = medial = final_char = "";
                }
                cout << c;
            }
        }
        if (!initial.empty() || !medial.empty() || !final_char.empty()) {
            cout << initial << medial << final_char;
        }
        cout << "\n";
    }

    return 0;
}
