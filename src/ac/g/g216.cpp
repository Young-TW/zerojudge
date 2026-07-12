#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    if (cin >> s) {
        if (s == "無") {
            cout << "無" << endl;
        } else {
            cout << "2^(10^" << s << ")" << endl;
        }
    } else {
        cout << "無" << endl;
    }
    return 0;
}
