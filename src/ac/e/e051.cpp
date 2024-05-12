#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    cin >> str;
    cout << str.front();
    for (int i = 0; i < str.length() - 2; i++) {
        cout << '_';
    }
    cout << str.back();
    return 0;
}
