#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int minPrice = 1000000000;
    int maxProfit = 0;
    int x;
    while (cin >> x) {
        if (x < minPrice) minPrice = x;
        int profit = x - minPrice;
        if (profit > maxProfit) maxProfit = profit;
    }
    
    cout << maxProfit << "\n";
    return 0;
}
