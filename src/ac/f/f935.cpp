#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        int price;
        vector<int> prices;
        
        while (ss >> price) {
            prices.push_back(price);
        }
        
        if (prices.empty()) continue;
        
        int min_price = prices[0];
        int max_profit = 0;
        int buy_price = -1;
        int sell_price = -1;
        
        for (size_t i = 1; i < prices.size(); ++i) {
            int p = prices[i];
            if (p < min_price) {
                min_price = p;
            } else if (p - min_price > max_profit) {
                max_profit = p - min_price;
                buy_price = min_price;
                sell_price = p;
            }
        }
        
        if (max_profit == 0) {
            cout << "0 -1 -1\n";
        } else {
            cout << max_profit << " " << buy_price << " " << sell_price << "\n";
        }
    }
    
    return 0;
}
