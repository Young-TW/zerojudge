#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <array>
#include <cstdio>

using uint = uint32_t;
const uint MASK = 0xffffffffu;
const uint K = 0x5a82u;                 // constant k
const std::array<uint,5> V0 = {0xdeadu, 0xcafeu, 0xbeefu, 0x3399u, 0x7788u};

struct Vec5 {
    uint v[5];
    bool operator==(const Vec5& o) const {
        for (int i = 0; i < 5; ++i) if (v[i] != o.v[i]) return false;
        return true;
    }
};

struct VecHash {
    std::size_t operator()(const Vec5& x) const noexcept {
        std::size_t h = 0;
        for (int i = 0; i < 5; ++i) h = h * 31 + x.v[i];
        return h;
    }
};

/* matrix multiplication (5x5) modulo 2^32 */
using Mat = std::array<std::array<uint,5>,5>;

Mat mulMat(const Mat& A, const Mat& B) {
    Mat C{};
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j) {
            uint64_t sum = 0;
            for (int k = 0; k < 5; ++k) sum += (uint64_t)A[i][k] * B[k][j];
            C[i][j] = (uint)(sum & MASK);
        }
    return C;
}

/* matrix * vector */
std::array<uint,5> mulMatVec(const Mat& M, const std::array<uint,5>& vec) {
    std::array<uint,5> res{};
    for (int i = 0; i < 5; ++i) {
        uint64_t sum = 0;
        for (int j = 0; j < 5; ++j) sum += (uint64_t)M[i][j] * vec[j];
        res[i] = (uint)(sum & MASK);
    }
    return res;
}

/* vector addition */
std::array<uint,5> addVec(const std::array<uint,5>& a, const std::array<uint,5>& b) {
    std::array<uint,5> r;
    for (int i = 0; i < 5; ++i) r[i] = a[i] + b[i];
    return r;
}

/* vector subtraction (mod 2^32) */
std::array<uint,5> subVec(const std::array<uint,5>& a, const std::array<uint,5>& b) {
    std::array<uint,5> r;
    for (int i = 0; i < 5; ++i) r[i] = a[i] - b[i];
    return r;
}

/* scalar * vector */
std::array<uint,5> mulScalar(const std::array<uint,5>& v, uint s) {
    std::array<uint,5> r;
    for (int i = 0; i < 5; ++i) r[i] = (uint)(((uint64_t)s * v[i]) & MASK);
    return r;
}

/* vector to Vec5 (for hash map) */
Vec5 toKey(const std::array<uint,5>& a) {
    Vec5 k;
    for (int i = 0; i < 5; ++i) k.v[i] = a[i];
    return k;
}

/* ------------------------------------------------------------------ */

int main() {
    /* ----- build transformation matrices ----- */
    Mat M{};
    // first row: 4*a + b + c + e
    M[0] = {4,1,1,0,1};
    // second row: a
    M[1] = {1,0,0,0,0};
    // third row: 8*b
    M[2] = {0,8,0,0,0};
    // fourth row: c
    M[3] = {0,0,1,0,0};
    // fifth row: d
    M[4] = {0,0,0,1,0};

    // powers of M
    std::array<Mat,6> Mp{};
    // identity
    for (int i = 0; i < 5; ++i) Mp[0][i][i] = 1;
    for (int p = 1; p <= 5; ++p) Mp[p] = mulMat(Mp[p-1], M);

    // constant C = V0 + M^5 * V0
    auto M5V0 = mulMatVec(Mp[5], V0);
    std::array<uint,5> Cvec;
    for (int i = 0; i < 5; ++i) Cvec[i] = V0[i] + M5V0[i];

    // U_i = column 0 of M^{4-i}
    std::array<std::array<uint,5>,5> U{};
    for (int i = 0; i < 5; ++i) {
        const Mat& mat = Mp[4 - i];
        for (int r = 0; r < 5; ++r) U[i][r] = mat[r][0];
    }

    // sum_U = Σ U_i
    std::array<uint,5> sumU = {0,0,0,0,0};
    for (int i = 0; i < 5; ++i)
        for (int r = 0; r < 5; ++r)
            sumU[r] += U[i][r];

    // S_const = k * sumU
    auto S_const = mulScalar(sumU, K);

    /* ----- character set ----- */
    std::vector<char> chars;
    for (char c = '0'; c <= '9'; ++c) chars.push_back(c);
    for (char c = 'A'; c <= 'Z'; ++c) chars.push_back(c);
    for (char c = 'a'; c <= 'z'; ++c) chars.push_back(c);
    const int CNUM = (int)chars.size();   // 62

    // pre‑compute contribution of each position and each character
    // contrib[pos][idx] = wi * U_pos
    std::array<std::vector<std::array<uint,5>>,5> contrib;
    for (int pos = 0; pos < 5; ++pos) {
        contrib[pos].resize(CNUM);
        for (int j = 0; j < CNUM; ++j) {
            uint wi = (uint)(chars[j] - ' ');
            contrib[pos][j] = mulScalar(U[pos], wi);
        }
    }

    /* ----- build prefix (first 2) map ----- */
    std::unordered_map<Vec5, std::string, VecHash> prefMap;
    for (int i0 = 0; i0 < CNUM; ++i0) {
        for (int i1 = 0; i1 < CNUM; ++i1) {
            std::array<uint,5> sum{};
            for (int r = 0; r < 5; ++r)
                sum[r] = contrib[0][i0][r] + contrib[1][i1][r];
            Vec5 key = toKey(sum);
            std::string s;
            s.push_back(chars[i0]);
            s.push_back(chars[i1]);
            prefMap.emplace(key, s);   // if duplicate, first kept (any is fine)
        }
    }

    /* ----- build suffix (last 3) map ----- */
    std::unordered_map<Vec5, std::string, VecHash> suffMap;
    for (int i2 = 0; i2 < CNUM; ++i2) {
        for (int i3 = 0; i3 < CNUM; ++i3) {
            for (int i4 = 0; i4 < CNUM; ++i4) {
                std::array<uint,5> sum{};
                for (int r = 0; r < 5; ++r)
                    sum[r] = contrib[2][i2][r] + contrib[3][i3][r] + contrib[4][i4][r];
                Vec5 key = toKey(sum);
                std::string s;
                s.push_back(chars[i2]);
                s.push_back(chars[i3]);
                s.push_back(chars[i4]);
                suffMap.emplace(key, s);
            }
        }
    }

    /* ----- process test cases ----- */
    int T;
    if (!(std::cin >> T)) return 0;
    for (int tc = 0; tc < T; ++tc) {
        std::array<uint,5> D{};
        for (int i = 0; i < 5; ++i) {
            std::string token; std::cin >> token;
            D[i] = (uint)std::stoul(token, nullptr, 16);
        }

        // D' = D - C
        auto D1 = subVec(D, Cvec);
        // T = D' - S_const
        auto target = subVec(D1, S_const);

        Vec5 targetKey = toKey(target);
        std::string answer;

        // iterate over prefix map and look for complement in suffix map
        for (const auto& p : prefMap) {
            Vec5 need;
            for (int r = 0; r < 5; ++r) need.v[r] = targetKey.v[r] - p.first.v[r];
            auto it = suffMap.find(need);
            if (it != suffMap.end()) {
                answer = p.second + it->second;
                break;
            }
        }

        std::cout << answer << '\n';
    }
    return 0;
}
