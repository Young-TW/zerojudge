#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    map<pair<char, string>, string> table;
    table[{'a', "a"}] = "a";
    table[{'a', "e"}] = "a";
    table[{'a', "i"}] = "ai";
    table[{'a', "y"}] = "ay";
    table[{'a', "o"}] = "w";
    table[{'a', "ou"}] = "au";
    table[{'a', "w"}] = "w";

    table[{'e', "a"}] = "e";
    table[{'e', "e"}] = "ei";
    table[{'e', "i"}] = "ei";
    table[{'e', "y"}] = "ey";
    table[{'e', "o"}] = "ou";
    table[{'e', "ou"}] = "eu";
    table[{'e', "w"}] = "eu";

    table[{'o', "a"}] = "o";
    table[{'o', "e"}] = "ou";
    table[{'o', "i"}] = "oi";
    table[{'o', "y"}] = "oy";
    table[{'o', "o"}] = "ou";
    table[{'o', "ou"}] = "ou";
    table[{'o', "w"}] = "ow";

    string s;
    while (cin >> s) {
        if (s == "END") break;
        
        size_t pos = s.find('-');
        string root = s.substr(0, pos);
        string suffix = s.substr(pos + 1);

        char root_end = root.back();
        string suffix_start;
        
        if (suffix.length() >= 2 && suffix[0] == 'o' && suffix[1] == 'u') {
            suffix_start = "ou";
        } else {
            suffix_start = string(1, suffix[0]);
        }

        string replacement = table[{root_end, suffix_start}];
        string result = root.substr(0, root.length() - 1) + replacement + suffix.substr(suffix_start.length());
        
        cout << result << "\n";
    }

    return 0;
}
