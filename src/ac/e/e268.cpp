#include <iostream>
#include <string>
#include <map>

using namespace std;

bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int L, N;
    while (cin >> L >> N) {
        map<string, string> irregular;
        for (int i = 0; i < L; ++i) {
            string singular, plural;
            cin >> singular >> plural;
            irregular[singular] = plural;
        }
        
        for (int i = 0; i < N; ++i) {
            string w;
            cin >> w;
            
            if (irregular.find(w) != irregular.end()) {
                cout << irregular[w] << "\n";
            } else {
                int len = w.length();
                if (len >= 2 && w[len - 1] == 'y' && !isVowel(w[len - 2])) {
                    cout << w.substr(0, len - 1) << "ies\n";
                } else if (len >= 1 && (w[len - 1] == 'o' || w[len - 1] == 's' || w[len - 1] == 'x')) {
                    cout << w << "es\n";
                } else if (len >= 2 && ((w[len - 2] == 'c' && w[len - 1] == 'h') || (w[len - 2] == 's' && w[len - 1] == 'h'))) {
                    cout << w << "es\n";
                } else {
                    cout << w << "s\n";
                }
            }
        }
    }
    
    return 0;
}
