#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int toNum(const string& s) {
    if (s == "TWO") return 2;
    if (s == "THREE") return 3;
    if (s == "FOUR") return 4;
    if (s == "FIVE") return 5;
    if (s == "SIX") return 6;
    if (s == "SEVEN") return 7;
    if (s == "EIGHT") return 8;
    if (s == "NINE") return 9;
    if (s == "TEN") return 10;
    if (s == "ELEVEN") return 11;
    if (s == "TWELVE") return 12;
    if (s == "THIRTEEN") return 13;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string w1, w2, w3, w4, w5;
    while (cin >> w1 >> w2 >> w3 >> w4 >> w5) {
        int num1 = toNum(w4);
        string companions_plural = w5;
        
        cin >> w1 >> w2 >> w3 >> w4 >> w5;
        int num2 = toNum(w4);
        string containers_plural = w5;
        
        cin >> w1 >> w2 >> w3 >> w4 >> w5;
        int num3 = toNum(w4);
        string objects_plural = w5;
        
        cin >> w1 >> w2 >> w3 >> w4 >> w5;
        int num4 = toNum(w4);
        string items_plural = w5;
        
        cin >> w1 >> w2 >> w3;
        if (!w3.empty() && w3.back() == '?') {
            w3.pop_back();
        }
        string somethings_plural = w3;
        
        char c;
        while (cin.get(c)) {
            if (c == '?') continue;
            if (isspace(c)) continue;
            cin.putback(c);
            break;
        }
        
        long long count1 = num1;
        long long count2 = count1 * num2;
        long long count3 = count2 * num3;
        long long count4 = count3 * num4;
        
        if (somethings_plural == companions_plural) {
            cout << count1 << " " << somethings_plural << "\n";
        } else if (somethings_plural == containers_plural) {
            cout << count2 << " " << somethings_plural << "\n";
        } else if (somethings_plural == objects_plural) {
            cout << count3 << " " << somethings_plural << "\n";
        } else if (somethings_plural == items_plural) {
            cout << count4 << " " << somethings_plural << "\n";
        }
    }
    
    return 0;
}
