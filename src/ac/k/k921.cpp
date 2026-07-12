#include <iostream>
#include <map>
#include <functional>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    map<long long, long long, greater<long long>> money;
    long long a, b;
    
    while (cin >> a >> b) {
        money[a] += b;
    }
    
    long long total = 0;
    for (const auto& p : money) {
        cout << p.first << "元鈔票共有" << p.second << "張\n";
        total += p.first * p.second;
    }
    
    cout << "總共有" << total << "元\n";
    
    return 0;
}
