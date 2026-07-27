#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long q;
    while (cin >> q) {
        vector<long long> need;
        need.reserve(q);
        multiset<long long> unsat;
        size_t front = 0;
        long long total = 0;          // total buns given so far

        for (long long i = 0; i < q; ++i) {
            int type;
            long long x;
            cin >> type >> x;
            if (type == 1) {          // new customer
                long long th = x + total;   // (1)
                need.push_back(th);
                unsat.insert(th);
            } else {                  // batch
                total += x;            // give k buns to everyone in queue

                // 1) remove newly satisfied customers from unsatisfied set
                while (!unsat.empty() && *unsat.begin() <= total) {
                    unsat.erase(unsat.begin());
                }

                // 2) front customers that can now leave
                while (front < need.size() && need[front] <= total) {
                    ++front;
                }

                // 3) answer
                long long still_waiting = (need.size() - front) - unsat.size();
                cout << still_waiting << '\n';
            }
        }
    }
    return 0;
}
