#include <iostream>
#include <string>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        if (line == "e/o/i") {
            break;
        }
        
        int syllables[3] = {0, 0, 0};
        int part = 0;
        bool prevVowel = false;
        
        for (char c : line) {
            if (c == '/') {
                part++;
                prevVowel = false;
                continue;
            }
            
            bool currVowel = isVowel(c);
            if (currVowel && !prevVowel) {
                syllables[part]++;
            }
            prevVowel = currVowel;
        }
        
        if (syllables[0] != 5) {
            cout << "1\n";
        } else if (syllables[1] != 7) {
            cout << "2\n";
        } else if (syllables[2] != 5) {
            cout << "3\n";
        } else {
            cout << "Y\n";
        }
    }
    
    return 0;
}
