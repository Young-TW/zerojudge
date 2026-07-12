#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Product {
    int profit;
    int deadline;
};

bool compareDeadline(const Product &a, const Product &b) {
    return a.deadline < b.deadline;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<Product> products(n);
        for (int i = 0; i < n; ++i) {
            cin >> products[i].profit >> products[i].deadline;
        }

        sort(products.begin(), products.end(), compareDeadline);

        priority_queue<int, vector<int>, greater<int>> pq;
        int totalProfit = 0;

        for (const auto &product : products) {
            if (pq.size() < product.deadline) {
                pq.push(product.profit);
                totalProfit += product.profit;
            } else if (!pq.empty() && pq.top() < product.profit) {
                totalProfit -= pq.top();
                pq.pop();
                pq.push(product.profit);
                totalProfit += product.profit;
            }
        }

        cout << totalProfit << '\n';
    }

    return 0;
}
