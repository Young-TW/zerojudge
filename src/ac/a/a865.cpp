#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<char, int> val;
    val['A'] = 1;
    val['B'] = 2;
    val['G'] = 3;
    val['D'] = 4;
    val['E'] = 5;
    val['#'] = 6;
    val['Z'] = 7;
    val['Y'] = 8;
    val['H'] = 9;
    val['I'] = 10;
    val['K'] = 20;
    val['L'] = 30;
    val['M'] = 40;
    val['N'] = 50;
    val['X'] = 60;
    val['O'] = 70;
    val['P'] = 80;
    val['Q'] = 90;
    val['R'] = 100;
    val['S'] = 200;
    val['T'] = 300;
    val['U'] = 400;
    val['F'] = 500;
    val['C'] = 600;
    val['$'] = 700;
    val['W'] = 800;
    val['3'] = 900;

    string s;
    while (cin >> s) {
        if (s == ".") break;
        int sum = 0;
        for (char c : s) {
            sum += val[c];
        }
        cout << sum << "\n";
    }
    
    return 0;
}
