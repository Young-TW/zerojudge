#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct River {
    double u, v;
    int id;
};

struct RiverCmp {
    bool operator()(const River& a, const River& b) const {
        if (a.u != b.u) return a.u < b.u;
        return a.id < b.id;
    }
};

typedef tree<River, null_type, RiverCmp, rb_tree_tag,
             tree_order_statistics_node_update> OrderedSet;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double EPS = 1e-9;

    int N;
    if (!(cin >> N)) return 0;
    OrderedSet os;
    int curId = 0;

    for (int i = 0; i < N; ++i) {
        char op;
        cin >> op;
        if (op == 'A') {
            double u, v;
            cin >> u >> v;
            ++curId;
            os.insert({u, v, curId});
        } else if (op == 'Q') {
            double x, y;
            cin >> x >> y;
            int sz = (int)os.size();

            // binary search on rank
            int low = 0, high = sz;
            while (low < high) {
                int mid = (low + high) >> 1;
                const River& r = *os.find_by_order(mid);
                double xi = r.v + (r.u - r.v) * y;
                if (xi < x - EPS)   // strictly less
                    low = mid + 1;
                else
                    high = mid;
            }
            int pos = low; // first river with xi >= x

            bool onRiver = false;
            if (pos < sz) {
                const River& r = *os.find_by_order(pos);
                double xi = r.v + (r.u - r.v) * y;
                if (fabs(xi - x) <= EPS) onRiver = true;
            }

            if (onRiver) {
                cout << "[?, ?]\n";
                continue;
            }

            string left, right;
            if (pos == 0) left = "S";
            else {
                const River& r = *os.find_by_order(pos - 1);
                left = to_string(r.id);
            }

            if (pos == sz) right = "M";
            else {
                const River& r = *os.find_by_order(pos);
                right = to_string(r.id);
            }

            cout << "[" << left << ", " << right << "]\n";
        }
    }
    return 0;
}
