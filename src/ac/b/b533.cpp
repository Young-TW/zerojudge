#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

set<int> parse_set(const string& str) {
    set<int> s;
    int num = 0;
    bool in_num = false;
    bool is_neg = false;
    for (char c : str) {
        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
            in_num = true;
        } else if (c == '-' && !in_num) {
            is_neg = true;
        } else {
            if (in_num) {
                s.insert(is_neg ? -num : num);
                num = 0;
                in_num = false;
                is_neg = false;
            }
        }
    }
    if (in_num) {
        s.insert(is_neg ? -num : num);
    }
    return s;
}

string format_vec(const vector<int>& v) {
    if (v.empty()) return "N";
    string res = "{";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) res += ", ";
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    while (cin >> N) {
        cin.ignore();
        while (N--) {
            string line;
            getline(cin, line);
            size_t pos1 = line.find('}');
            size_t pos2 = line.find('{', pos1 + 1);
            if (pos1 == string::npos || pos2 == string::npos) continue;
            string partA = line.substr(0, pos1 + 1);
            string partB = line.substr(pos2);
            set<int> A = parse_set(partA);
            set<int> B = parse_set(partB);
            
            vector<int> u, i, d, sd;
            set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(u));
            set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(i));
            set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(d));
            set_symmetric_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(sd));
            
            cout << format_vec(u) << ", " << format_vec(i) << ", " << format_vec(d) << ", " << format_vec(sd) << "\n";
        }
    }
    return 0;
}
