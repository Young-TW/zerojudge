#include <iostream>
#include <cstring>
#include <cstdint>

using namespace std;

inline uint16_t encrypt(uint16_t M, uint16_t key) {
    uint32_t m = M;
    uint32_t k = key;
    uint32_t n = k & 15;
    uint32_t shifted = (m << n) | (m >> (16 - n));
    return ((shifted + k) ^ k) & 0xFFFF;
}

inline uint16_t decrypt(uint16_t C, uint16_t key) {
    uint32_t c = C;
    uint32_t k = key;
    uint32_t xored = c ^ k;
    uint32_t not_key = (~k) & 0xFFFF;
    uint32_t added = (xored + not_key + 1) & 0xFFFF;
    uint32_t n = k & 15;
    return ((added >> n) | (added << (16 - n))) & 0xFFFF;
}

int cnt[65536];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    uint32_t C_in, M_in;
    while (cin >> C_in >> M_in) {
        uint16_t C = C_in;
        uint16_t M = M_in;
        memset(cnt, 0, sizeof(cnt));
        for (uint32_t key1 = 0; key1 < 65536; ++key1) {
            uint16_t mid = encrypt(M, key1);
            cnt[mid]++;
        }
        long long ans = 0;
        for (uint32_t key2 = 0; key2 < 65536; ++key2) {
            uint16_t mid = decrypt(C, key2);
            ans += cnt[mid];
        }
        cout << ans << '\n';
    }
    return 0;
}
