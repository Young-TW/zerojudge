#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Use a multiset for O(log n) insert and min/max queries.
    // Since elements may be duplicated and the problem says
    // "extreme value will be deleted after query", we erase one
    // occurrence of the max/min after each query.
    multiset<long long> s;

    int op;
    while (cin >> op) {
        if (op == 1) {
            long long n;
            cin >> n;
            s.insert(n);
        } else if (op == 2) {
            // Query MAX then delete it
            auto it = prev(s.end());
            cout << *it << '\n';
            s.erase(it);
        } else { // op == 3
            // Query MIN then delete it
            auto it = s.begin();
            cout << *it << '\n';
            s.erase(it);
        }
    }
    return 0;
}
