#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int x;
    vector<int> order;
    unordered_map<int, int> cnt;
    
    while (cin >> x) {
        if (cnt.find(x) == cnt.end()) {
            order.push_back(x);
        }
        cnt[x]++;
    }
    
    for (size_t i = 0; i < order.size(); ++i) {
        cout << order[i] << " " << cnt[order[i]] << "\n";
    }
    
    return 0;
}
