#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct House {
    long long d1, d2;
};

struct Query {
    long long r1, r2;
    int id;
};

struct BIT {
    vector<int> tree;
    int n;
    void init(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }
    void add(int i, int delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int caseNum = 1;
    int N;
    while (cin >> N && N) {
        vector<House> houses(N);
        for (int i = 0; i < N; ++i) {
            long long x, y;
            cin >> x >> y;
            houses[i].d1 = x;
            houses[i].d2 = y;
        }
        long long ax, ay, bx, by;
        int Q;
        cin >> ax >> ay >> bx >> by >> Q;
        vector<Query> queries(Q);
        for (int i = 0; i < N; ++i) {
            long long x = houses[i].d1;
            long long y = houses[i].d2;
            houses[i].d1 = (x - ax) * (x - ax) + (y - ay) * (y - ay);
            houses[i].d2 = (x - bx) * (x - bx) + (y - by) * (y - by);
        }
        for (int i = 0; i < Q; ++i) {
            long long r1, r2;
            cin >> r1 >> r2;
            queries[i].r1 = r1 * r1;
            queries[i].r2 = r2 * r2;
            queries[i].id = i;
        }

        sort(houses.begin(), houses.end(), [](const House& a, const House& b) {
            return a.d1 < b.d1;
        });
        sort(queries.begin(), queries.end(), [](const Query& a, const Query& b) {
            return a.r1 < b.r1;
        });

        vector<long long> d2_vals;
        for (int i = 0; i < N; ++i) {
            d2_vals.push_back(houses[i].d2);
        }
        sort(d2_vals.begin(), d2_vals.end());
        d2_vals.erase(unique(d2_vals.begin(), d2_vals.end()), d2_vals.end());

        BIT bit;
        bit.init(d2_vals.size());

        int house_ptr = 0;
        vector<long long> ans(Q);
        for (int i = 0; i < Q; ++i) {
            while (house_ptr < N && houses[house_ptr].d1 <= queries[i].r1) {
                int idx = lower_bound(d2_vals.begin(), d2_vals.end(), houses[house_ptr].d2) - d2_vals.begin();
                bit.add(idx + 1, 1);
                house_ptr++;
            }
            int idx = upper_bound(d2_vals.begin(), d2_vals.end(), queries[i].r2) - d2_vals.begin();
            ans[queries[i].id] = bit.query(idx);
        }

        cout << "Case " << caseNum++ << ":\n";
        for (int i = 0; i < Q; ++i) {
            cout << ans[i] << "\n";
        }
        cout << "\n";
    }
    return 0;
}
