#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool is_digit_char(char c) {
    return c >= '0' && c <= '9';
}

char to_upper_char(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
    return c;
}

vector<string> tokenize(const string& s) {
    vector<string> tokens;
    if (s.empty()) return tokens;
    bool is_digit = is_digit_char(s[0]);
    string current;
    current += s[0];
    for (size_t i = 1; i < s.size(); ++i) {
        if (is_digit_char(s[i]) == is_digit) {
            current += s[i];
        } else {
            tokens.push_back(current);
            current = s[i];
            is_digit = is_digit_char(s[i]);
        }
    }
    tokens.push_back(current);
    return tokens;
}

int compare_numeric(const string& a, const string& b) {
    size_t a_start = a.find_first_not_of('0');
    string a_stripped;
    if (a_start == string::npos) a_stripped = "0";
    else a_stripped = a.substr(a_start);
    
    size_t b_start = b.find_first_not_of('0');
    string b_stripped;
    if (b_start == string::npos) b_stripped = "0";
    else b_stripped = b.substr(b_start);
    
    if (a_stripped.length() != b_stripped.length()) {
        return a_stripped.length() < b_stripped.length() ? -1 : 1;
    }
    if (a_stripped != b_stripped) {
        return a_stripped < b_stripped ? -1 : 1;
    }
    if (a != b) {
        return a < b ? -1 : 1;
    }
    return 0;
}

bool compare_strings(const string& s1, const string& s2) {
    string u1 = s1, u2 = s2;
    for (size_t i = 0; i < u1.size(); ++i) u1[i] = to_upper_char(u1[i]);
    for (size_t i = 0; i < u2.size(); ++i) u2[i] = to_upper_char(u2[i]);
    
    vector<string> t1 = tokenize(u1);
    vector<string> t2 = tokenize(u2);
    
    size_t min_len = min(t1.size(), t2.size());
    for (size_t i = 0; i < min_len; ++i) {
        bool d1 = is_digit_char(t1[i][0]);
        bool d2 = is_digit_char(t2[i][0]);
        int cmp = 0;
        if (d1 && d2) {
            cmp = compare_numeric(t1[i], t2[i]);
        } else {
            if (t1[i] != t2[i]) {
                cmp = (t1[i] < t2[i]) ? -1 : 1;
            }
        }
        if (cmp != 0) return cmp < 0;
    }
    return t1.size() < t2.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    while (cin >> n) {
        cin.ignore();
        vector<string> files(n);
        for (int i = 0; i < n; ++i) {
            getline(cin, files[i]);
        }
        sort(files.begin(), files.end(), compare_strings);
        for (int i = 0; i < n; ++i) {
            cout << files[i] << "\n";
        }
    }
    return 0;
}
