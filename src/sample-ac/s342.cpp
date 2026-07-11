#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void print_result(const string& title, const vector<string>& v) {
    cout << title << ": ";
    if (v.empty()) {
        cout << "None\n";
    } else {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) cout << ",";
            cout << v[i];
        }
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    vector<string> not_tri, acute, obtuse, right;
    
    while (cin >> s) {
        if (s == "-1") break;
        long long a, b, c;
        cin >> a >> b >> c;
        
        long long arr[3] = {a, b, c};
        sort(arr, arr + 3);
        
        if (arr[0] + arr[1] <= arr[2]) {
            not_tri.push_back(s);
        } else {
            long long sum_sq = arr[0] * arr[0] + arr[1] * arr[1];
            long long max_sq = arr[2] * arr[2];
            if (sum_sq > max_sq) {
                acute.push_back(s);
            } else if (sum_sq < max_sq) {
                obtuse.push_back(s);
            } else {
                right.push_back(s);
            }
        }
    }
    
    sort(not_tri.begin(), not_tri.end());
    sort(acute.begin(), acute.end());
    sort(obtuse.begin(), obtuse.end());
    sort(right.begin(), right.end());
    
    print_result("Not Triangle", not_tri);
    print_result("Acute Angle", acute);
    print_result("Obtuse Angle", obtuse);
    print_result("Right Angle", right);
    
    return 0;
}
