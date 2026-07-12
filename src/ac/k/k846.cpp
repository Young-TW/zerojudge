#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    while (getline(cin, line)) {
        string s = "";
        for (size_t k = 0; k < line.size(); k++) {
            char c = line[k];
            if (!isspace((unsigned char)c)) s += c;
        }
        if (s.empty()) continue;
        if (s == "0") break;
        
        size_t i = 0;
        if (i < s.size() && s[i] == '-') i++;
        while (i < s.size() && isdigit((unsigned char)s[i])) i++;
        
        long long a = stoll(s.substr(0, i));
        
        char op = s[i];
        size_t opLen = 1;
        if (op == '*' && i + 1 < s.size() && s[i + 1] == '*') {
            opLen = 2;
        }
        
        long long b = stoll(s.substr(i + opLen));
        
        double result = 0;
        string msg;
        if (op == '+') {
            result = (double)(a + b);
            msg = "加起來就是團結，團結就是力量，我們五個是最好的朋友!";
        } else if (op == '-') {
            result = (double)(a - b);
            msg = "減並不負面，減只是加一個負數，失去的，終究會回來。我們之間失去的友誼，也終究會回來。生命是美好的，友誼是寶貴的!";
        } else if (op == '*') {
            if (opLen == 2) {
                result = pow((double)a, (double)b);
                msg = "乘方就是能力翻倍，我們自己能力翻倍的話，我們五個好朋友的能力就會更強!";
            } else {
                result = (double)(a * b);
                msg = "正數乘起來會變大，我們五個好朋友在一起，能量也會翻倍!";
            }
        } else if (op == '/') {
            result = (double)a / (double)b;
            msg = "除法就是分，我們五個是能平分東西，同甘共苦的好朋友!";
        }
        
        long long ans = llround(result);
        cout << ans << "\n" << msg << "\n";
    }
    return 0;
}
