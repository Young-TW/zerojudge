#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<string, char> morseToChar = {
        {".-", 'A'},
        {"-...", 'B'},
        {"-.-.", 'C'},
        {"-..", 'D'},
        {".", 'E'},
        {"..-.", 'F'},
        {"--.", 'G'},
        {"....", 'H'},
        {"..", 'I'},
        {".---", 'J'},
        {"-.-", 'K'},
        {".-..", 'L'},
        {"--", 'M'},
        {"-.", 'N'},
        {"---", 'O'},
        {".--.", 'P'},
        {"--.-", 'Q'},
        {".-.", 'R'},
        {"...", 'S'},
        {"-", 'T'},
        {"..-", 'U'},
        {"...-", 'V'},
        {".--", 'W'},
        {"-..-", 'X'},
        {"-.--", 'Y'},
        {"--..", 'Z'},
        {"-----", '0'},
        {".----", '1'},
        {"..---", '2'},
        {"...--", '3'},
        {"....-", '4'},
        {".....", '5'},
        {"-....", '6'},
        {"--...", '7'},
        {"---..", '8'},
        {"----.", '9'},
        {".-.-.-", '.'},
        {"--..--", ','},
        {"..--..", '?'},
        {".----.", '\''},
        {"-.-.--", '!'},
        {"-..-.", '/'},
        {"-.--.", '('},
        {"-.--.-", ')'},
        {".-...", '&'},
        {"---...", ':'},
        {"-.-.-.", ';'},
        {"-...-", '='},
        {".-.-.", '+'},
        {"-....-", '-'},
        {"..--.-", '_'},
        {".-..-.", '"'},
        {".--.-.", '@'}
    };

    int T;
    if (cin >> T) {
        cin.ignore();
        for (int t = 1; t <= T; ++t) {
            string line;
            getline(cin, line);
            string decoded;
            int i = 0;
            while (i < line.length()) {
                string code;
                while (i < line.length() && line[i] != ' ') {
                    code += line[i];
                    i++;
                }
                
                int spaceCount = 0;
                while (i < line.length() && line[i] == ' ') {
                    spaceCount++;
                    i++;
                }
                
                if (!code.empty()) {
                    if (morseToChar.find(code) != morseToChar.end()) {
                        decoded += morseToChar[code];
                    }
                    if (spaceCount >= 2) {
                        decoded += ' ';
                    }
                }
            }
            cout << "Message #" << t << "\n";
            cout << decoded << "\n";
            if (t < T) {
                cout << "\n";
            }
        }
    }

    return 0;
}
