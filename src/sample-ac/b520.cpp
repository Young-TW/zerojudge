#include <iostream>
#include <set>

using namespace std;

set<int> read5() {
    set<int> s;
    int cnt = 0;
    int num = -1;
    char c;
    while (cnt < 5 && cin.get(c)) {
        if (c >= '0' && c <= '9') {
            if (num == -1) num = 0;
            num = num * 10 + (c - '0');
        } else {
            if (num != -1) {
                s.insert(num);
                cnt++;
                num = -1;
            }
        }
    }
    if (num != -1 && cnt < 5) {
        s.insert(num);
        cnt++;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n) {
        while (n--) {
            set<int> s1 = read5();
            set<int> s2 = read5();
            
            int count = 0;
            for (int x : s1) {
                if (s2.count(x)) {
                    count++;
                }
            }
            cout << count << "\n";
        }
    }
    return 0;
}
