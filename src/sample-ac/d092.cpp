#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    long long c;
    int sign; // 2 for '>', 1 for '=', 0 for '<'
    bool operator<(const Item& other) const {
        if (c != other.c) {
            return c > other.c;
        }
        return sign > other.sign;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    while (cin >> n && n != 0) {
        vector<Item> items(n);
        for (int i = 0; i < n; ++i) {
            long long a, b;
            cin >> a >> b;
            items[i].c = a + b;
            if (a > b) {
                items[i].sign = 2;
            } else if (a == b) {
                items[i].sign = 1;
            } else {
                items[i].sign = 0;
            }
        }
        
        sort(items.begin(), items.end());
        
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                cout << " ";
            }
            if (items[i].sign == 2) {
                cout << ">";
            } else if (items[i].sign == 1) {
                cout << "=";
            } else {
                cout << "<";
            }
            cout << items[i].c;
        }
        cout << "\n";
    }
    
    return 0;
}
