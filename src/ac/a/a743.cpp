#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    map<string, int> cnt;
    string country, rest;
    for (int i = 0; i < n; i++) {
        cin >> country;
        cnt[country]++;
        getline(cin, rest);
    }
    for (auto &p : cnt) {
        cout << p.first << " " << p.second << "\n";
    }
    return 0;
}
