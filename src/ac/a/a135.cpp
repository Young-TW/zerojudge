#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, string> lang = {
        {"HELLO", "ENGLISH"},
        {"HOLA", "SPANISH"},
        {"HALLO", "GERMAN"},
        {"BONJOUR", "FRENCH"},
        {"CIAO", "ITALIAN"},
        {"ZDRAVSTVUJTE", "RUSSIAN"}
    };

    string s;
    int case_num = 1;
    while (cin >> s && s != "#") {
        cout << "Case " << case_num << ": ";
        auto it = lang.find(s);
        if (it != lang.end()) {
            cout << it->second << "\n";
        } else {
            cout << "UNKNOWN\n";
        }
        case_num++;
    }

    return 0;
}
