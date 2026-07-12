#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string n_str;
        ss >> n_str;
        vector<string> tokens;
        string tok;
        while (ss >> tok) {
            tokens.push_back(tok);
        }
        
        // Split numerator and denominator at '/'
        vector<string> num_tokens, den_tokens;
        auto it = find(tokens.begin(), tokens.end(), "/");
        if (it != tokens.end()) {
            num_tokens.assign(tokens.begin(), it);
            den_tokens.assign(it + 1, tokens.end());
        } else {
            num_tokens = tokens;
        }
        
        // Parse a polynomial from tokens: coefficient followed by optional "x" or "x^2"
        auto parse_poly = [](const vector<string>& t) -> array<long long, 3> {
            array<long long, 3> poly = {0, 0, 0};
            size_t i = 0;
            while (i < t.size()) {
                long long coeff = stoll(t[i]);
                i++;
                int exp = 0;
                if (i < t.size()) {
                    const string& next = t[i];
                    if (next == "x") {
                        exp = 1;
                        i++;
                    } else if (next == "x^2") {
                        exp = 2;
                        i++;
                    }
                }
                poly[exp] += coeff;
            }
            return poly;
        };
        
        array<long long, 3> P = parse_poly(num_tokens);
        array<long long, 3> Q = parse_poly(den_tokens);
        if (den_tokens.empty()) {
            Q = {1, 0, 0};  // denominator is 1 for polynomials
        }
        
        if (n_str == "inf" || n_str == "-inf") {
            // Limit at infinity
            int dp = -1;
            for (int i = 2; i >= 0; --i) {
                if (P[i] != 0) { dp = i; break; }
            }
            int dq = -1;
            for (int i = 2; i >= 0; --i) {
                if (Q[i] != 0) { dq = i; break; }
            }
            
            if (dp == -1) {
                cout << 0 << '\n';
            } else if (dp < dq) {
                cout << 0 << '\n';
            } else if (dp > dq) {
                cout << "limit doesn't exist\n";
            } else {
                // dp == dq, ratio of leading coefficients (guaranteed integer)
                long long limit = P[dp] / Q[dq];
                cout << limit << '\n';
            }
        } else {
            // Finite limit point
            long long n_val = stoll(n_str);
            auto eval = [](const array<long long, 3>& poly, long long x) -> long long {
                return poly[0] + poly[1] * x + poly[2] * x * x;
            };
            
            long long Pn = eval(P, n_val);
            long long Qn = eval(Q, n_val);
            
            if (Qn != 0) {
                // Direct substitution (guaranteed integer)
                long long limit = Pn / Qn;
                cout << limit << '\n';
            } else {
                if (Pn != 0) {
                    cout << "limit doesn't exist\n";
                } else {
                    // 0/0 indeterminate form: use derivatives (L'Hopital)
                    long long P_prime = P[1] + 2 * P[2] * n_val;
                    long long Q_prime = Q[1] + 2 * Q[2] * n_val;
                    
                    if (Q_prime != 0) {
                        long long limit = P_prime / Q_prime; // guaranteed integer
                        cout << limit << '\n';
                    } else {
                        if (P_prime != 0) {
                            cout << "limit doesn't exist\n";
                        } else {
                            // Double root at n_val: limit = leading coefficient ratio
                            long long limit = P[2] / Q[2]; // guaranteed integer
                            cout << limit << '\n';
                        }
                    }
                }
            }
        }
    }
    return 0;
}
