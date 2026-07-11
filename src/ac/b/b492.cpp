#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

struct Query {
    int K, L, R, id;
    bool operator<(const Query& other) const {
        return K < other.K;
    }
};

struct Element {
    int val, pos;
    bool operator<(const Element& other) const {
        return val < other.val;
    }
};

int N, Q;
vector<int> count_bit;
vector<long long> prod_bit;

void add_count(int i, int delta) {
    for (; i <= N; i += i & -i)
        count_bit[i] += delta;
}

int query_count(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i)
        res += count_bit[i];
    return res;
}

void add_prod(int i, long long val) {
    for (; i <= N; i += i & -i)
        prod_bit[i] = (prod_bit[i] * val) % MOD;
}

long long query_prod(int i) {
    long long res = 1;
    for (; i > 0; i -= i & -i)
        res = (res * prod_bit[i]) % MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> Q) {
        vector<Element> arr(N);
        for (int i = 0; i < N; ++i) {
            cin >> arr[i].val;
            arr[i].pos = i + 1;
        }
        sort(arr.begin(), arr.end());

        vector<Query> queries(Q);
        for (int i = 0; i < Q; ++i) {
            cin >> queries[i].L >> queries[i].R >> queries[i].K;
            queries[i].id = i;
        }
        sort(queries.begin(), queries.end());

        count_bit.assign(N + 1, 0);
        prod_bit.assign(N + 1, 1);

        vector<int> ans_count(Q);
        vector<long long> ans_prod(Q);

        int ptr = 0;
        for (int i = 0; i < Q; ++i) {
            int K = queries[i].K;
            while (ptr < N && arr[ptr].val <= K) {
                add_count(arr[ptr].pos, 1);
                add_prod(arr[ptr].pos, arr[ptr].val);
                ptr++;
            }
            int L = queries[i].L;
            int R = queries[i].R;
            int cnt = query_count(R) - query_count(L - 1);
            ans_count[queries[i].id] = cnt;
            if (cnt == 0) {
                ans_prod[queries[i].id] = 0;
            } else {
                long long prod = query_prod(R) * modInverse(query_prod(L - 1)) % MOD;
                ans_prod[queries[i].id] = prod;
            }
        }

        for (int i = 0; i < Q; ++i) {
            cout << ans_count[i] << " " << ans_prod[i] << "\n";
        }
    }
    return 0;
}
