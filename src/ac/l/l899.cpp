#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (cin >> s) {
        cout << "<不告訴你！>\n";
    } else {
        cout << "18446744073709551615\n";
    }

    return 0;
}
