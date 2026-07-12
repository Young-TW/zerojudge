#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;

const long long MOD = 1000000007;

struct Mat {
    long long a[3][3];
};

static Mat matMul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            C.a[i][j] = 0;
    for (int i = 0; i < 3; ++i)
        for (int k = 0; k < 3; ++k)
            if (A.a[i][k])
                for (int j = 0; j < 3; ++j)
                    C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
    return C;
}

static Mat matIdentity() {
    Mat I;
    memset(I.a, 0, sizeof(I.a));
    for (int i = 0; i < 3; ++i) I.a[i][i] = 1;
    return I;
}

static Mat M_GOOD, M_BAD;

static Mat matPow(Mat base, long long e) {
    Mat r = matIdentity();
    while (e > 0) {
        if (e & 1) r = matMul(r, base);
        base = matMul(base, base);
        e >>= 1;
    }
    return r;
}

// 線段樹：儲存各「壞位置」的轉移區塊，維護「由高位置到低位置」的乘積。
// leaf i 對應第 i 個壞候選位置；未啟用時為單位矩陣。
// 內部節點 = 右子(較高位置) * 左子(較低位置)。
struct SegTree {
    int n;
    vector<Mat> tree;
    void init(int sz) {
        n = sz;
        tree.assign(max(1, 4 * sz), matIdentity());
    }
    void update(int node, int l, int r, int pos, const Mat& val) {
        if (l == r) { tree[node] = val; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(node * 2, l, mid, pos, val);
        else update(node * 2 + 1, mid + 1, r, pos, val);
        tree[node] = matMul(tree[node * 2 + 1], tree[node * 2]);
    }
    // 回傳 [ql,qr] 由高位置到低位置的乘積
    Mat query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return matIdentity();
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) >> 1;
        Mat left = query(node * 2, l, mid, ql, qr);
        Mat right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return matMul(right, left);
    }
    void update(int pos, const Mat& val) { update(1, 0, n - 1, pos, val); }
    Mat query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 狀態向量 (dp[p-1], dp[p-2], dp[p-3])；M_GOOD: dp[p]=dp[p-1]+dp[p-2]+dp[p-3]
    memset(M_GOOD.a, 0, sizeof(M_GOOD.a));
    M_GOOD.a[0][0] = 1; M_GOOD.a[0][1] = 1; M_GOOD.a[0][2] = 1;
    M_GOOD.a[1][0] = 1;
    M_GOOD.a[2][1] = 1;
    // M_BAD: dp[p]=0（此階不可踩）
    memset(M_BAD.a, 0, sizeof(M_BAD.a));
    M_BAD.a[1][0] = 1;
    M_BAD.a[2][1] = 1;

    long long N, M;
    while (cin >> N >> M) {
        vector<int> ex(M);
        vector<long long> ek(M);
        vector<long long> cand;                // 所有可能變壞的位置
        for (long long i = 0; i < M; ++i) {
            cin >> ex[i] >> ek[i];
            if (ex[i] == 1) cand.push_back(ek[i]);
        }
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());
        int C = (int)cand.size();

        SegTree seg;
        seg.init(max(1, C));
        set<int> activeIdx;                    // 已啟用的壞候選索引（遞增）

        for (long long i = 0; i < M; ++i) {
            long long k = ek[i];
            if (ex[i] == 1) {
                int idx = (int)(lower_bound(cand.begin(), cand.end(), k) - cand.begin());
                if (activeIdx.count(idx)) continue;   // 重複標記
                // 前一個已啟用的壞位置
                long long prevPos = 0;
                auto it = activeIdx.lower_bound(idx);
                if (it != activeIdx.begin()) {
                    int pi = *prev(it);
                    prevPos = cand[pi];
                }
                Mat block = matMul(M_BAD, matPow(M_GOOD, k - prevPos - 1));
                seg.update(idx, block);
                activeIdx.insert(idx);
                // 下一個已啟用壞位置的區塊需重算（它的前鄰變成 idx）
                auto nit = activeIdx.upper_bound(idx);
                if (nit != activeIdx.end()) {
                    int ni = *nit;
                    long long nextPos = cand[ni];
                    Mat nb = matMul(M_BAD, matPow(M_GOOD, nextPos - k - 1));
                    seg.update(ni, nb);
                }
            } else {
                // 查詢 dp[k]
                int hiIdx = -1;
                if (C > 0) {
                    hiIdx = (int)(upper_bound(cand.begin(), cand.end(), k) - cand.begin()) - 1;
                }
                long long lastPos = 0;
                if (hiIdx >= 0) {
                    auto it = activeIdx.upper_bound(hiIdx);
                    if (it != activeIdx.begin()) {
                        int bi = *prev(it);
                        lastPos = cand[bi];
                    }
                }
                Mat P = (hiIdx >= 0) ? seg.query(0, hiIdx) : matIdentity();
                Mat full = matMul(matPow(M_GOOD, k - lastPos), P);
                // 乘上初始向量 (dp[0],dp[-1],dp[-2]) = (1,0,0)，取第 0 分量
                cout << full.a[0][0] % MOD << "\n";
            }
        }
    }

    return 0;
}
