#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string text;
    while (getline(cin, text)) {
        int format;
        if (!(cin >> format)) break;
        cin.ignore();
        
        if (format == 1) {
            bool first = true;
            for (char &c : text) {
                if (isalpha((unsigned char)c)) {
                    if (first) {
                        c = toupper((unsigned char)c);
                        first = false;
                    } else {
                        c = tolower((unsigned char)c);
                    }
                }
            }
        } else if (format == 2) {
            for (char &c : text) {
                if (isalpha((unsigned char)c)) {
                    c = toupper((unsigned char)c);
                }
            }
        } else if (format == 3) {
            bool start = true;
            for (char &c : text) {
                if (isalpha((unsigned char)c)) {
                    if (start) {
                        c = toupper((unsigned char)c);
                        start = false;
                    } else {
                        c = tolower((unsigned char)c);
                    }
                } else {
                    start = true;
                }
            }
        } else if (format == 4) {
            for (char &c : text) {
                if (isalpha((unsigned char)c)) {
                    c = tolower((unsigned char)c);
                }
            }
        }
        
        cout << text << "\n";
    }
    return 0;
}
