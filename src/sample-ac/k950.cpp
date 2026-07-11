#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

bool check_add(const vector<long long>& v, long long R) {
    __int128 res = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        res += v[i];
        if (res > LLONG_MAX || res < LLONG_MIN) return false;
    }
    return res == R;
}

bool check_sub(const vector<long long>& v, long long R) {
    __int128 res = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        res -= v[i];
        if (res > LLONG_MAX || res < LLONG_MIN) return false;
    }
    return res == R;
}

bool check_mul(const vector<long long>& v, long long R) {
    __int128 res = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        res *= v[i];
        if (res > LLONG_MAX || res < LLONG_MIN) return false;
    }
    return res == R;
}

bool check_div(const vector<long long>& v, long long R) {
    __int128 res = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] == 0) return false;
        if (res % v[i] != 0) return false;
        res /= v[i];
    }
    return res == R;
}

bool check_pow(const vector<long long>& v, long long R) {
    __int128 res = v[0];
    for (size_t i = 1; i < v.size(); ++i) {
        __int128 base = res;
        long long exp = v[i];
        if (base == 0) {
            if (exp <= 0) return false;
            res = 0;
        } else if (base == 1) {
            res = 1;
        } else if (base == -1) {
            long long e = exp < 0 ? -exp : exp;
            res = (e % 2 == 0) ? 1 : -1;
        } else {
            if (exp < 0) return false;
            if (exp == 0) {
                res = 1;
            } else if (exp == 1) {
                res = base;
            } else {
                __int128 temp = 1;
                bool overflow = false;
                for (long long j = 0; j < exp; ++j) {
                    temp *= base;
                    if (temp > LLONG_MAX || temp < LLONG_MIN) {
                        overflow = true;
                        break;
                    }
                }
                if (overflow) return false;
                res = temp;
            }
        }
        if (res > LLONG_MAX || res < LLONG_MIN) return false;
    }
    return res == R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<long long> v;
        long long x;
        while (ss >> x) {
            v.push_back(x);
        }
        if (v.size() >= 3) {
            long long R = v.back();
            v.pop_back();
            vector<string> ans;
            if (check_add(v, R)) ans.push_back("+");
            if (check_sub(v, R)) ans.push_back("-");
            if (check_mul(v, R)) ans.push_back("*");
            if (check_div(v, R)) ans.push_back("/");
            if (check_pow(v, R)) ans.push_back("**");
            for (size_t i = 0; i < ans.size(); ++i) {
                cout << ans[i] << (i + 1 == ans.size() ? "" : "\n");
            }
            cout << "\n";
        }
    }
    return 0;
}
