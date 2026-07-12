#include <iostream>
#include <string>

using namespace std;

string formatTerm(int coeff, const string& var, bool isFirst) {
    if (coeff == 0) return "";
    string res = "";
    if (coeff > 0) {
        if (!isFirst) res += "+";
        if (coeff == 1) {
            res += var;
        } else {
            res += to_string(coeff) + var;
        }
    } else {
        if (coeff == -1) {
            res += "-" + var;
        } else {
            res += to_string(coeff) + var;
        }
    }
    return res;
}

string formatConstant(int coeff, bool isFirst) {
    if (coeff == 0) return "";
    string res = "";
    if (coeff > 0) {
        if (!isFirst) res += "+";
        res += to_string(coeff);
    } else {
        res += to_string(coeff);
    }
    return res;
}

string getEquation(int a, int b, int c) {
    string eq = "";
    eq += formatTerm(a, "x^2", true);
    eq += formatTerm(b, "x", eq.empty());
    eq += formatConstant(c, eq.empty());
    eq += "=0";
    return eq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    while (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            cout << "請使用配方法解下列一元二次方程式\n\n";
            for (int i = 1; i <= n; ++i) {
                int a, b, c;
                cin >> a >> b >> c;
                cout << i << ". " << getEquation(a, b, c) << "\n\n";
            }
            cout << "考試要加油口屋\n";
        }
    }
    return 0;
}
