#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string delimiter, names;
    getline(cin, delimiter);
    getline(cin, names);

    size_t pos = 0;
    string token;
    bool first = true;

    while ((pos = names.find(delimiter)) != string::npos) {
        token = names.substr(0, pos);
        if (!first || !token.empty()) {
            cout << token << '\n';
        }
        names.erase(0, pos + delimiter.length());
        first = false;
    }
    if (!names.empty()) {
        cout << names << '\n';
    }

    return 0;
}
