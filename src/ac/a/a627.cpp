#include <iostream>
using namespace std;

int main() {
    int cap, raid;
    bool first = true;
    while (cin >> cap >> raid) {
        int dc[4] = {250, 400, 500, 750};
        int dp[4] = {75, 110, 140, 250};

        int bestCost = -1, bestQty = 0, bestDiskCap = 0, bestDiskPrice = 0, bestArrCap = 0;

        for (int d = 0; d < 4; d++) {
            int lo, hi;
            if (raid == 0) { lo = 2; hi = 8; }
            else if (raid == 1) { lo = 2; hi = 8; }
            else { lo = 3; hi = 8; }

            for (int q = lo; q <= hi; q++) {
                if (raid == 1 && (q % 2) != 0) continue;
                int arrCap;
                if (raid == 0) arrCap = q * dc[d];
                else if (raid == 1) arrCap = (q / 2) * dc[d];
                else arrCap = (q - 1) * dc[d];

                if (arrCap >= cap) {
                    int cost = q * dp[d];
                    if (bestCost == -1 || cost < bestCost) {
                        bestCost = cost;
                        bestQty = q;
                        bestDiskCap = dc[d];
                        bestDiskPrice = dp[d];
                        bestArrCap = arrCap;
                    }
                }
            }
        }

        if (!first) cout << "\n";
        first = false;
        cout << "Qty: " << bestQty << " Disk: " << bestDiskCap << "GB Price: $" << bestDiskPrice << "\n";
        cout << "Total price of this " << bestArrCap << "GB array: $" << bestCost << "\n";
    }
    return 0;
}
