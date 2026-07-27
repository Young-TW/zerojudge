#include <cstdio>
#include <cstdint>

static const std::size_t BUFSIZE = 1 << 20;
static char buf[BUFSIZE];
static std::size_t buf_len = 0, buf_pos = 0;

inline int getChar() {
    if (buf_pos >= buf_len) {
        buf_len = std::fread(buf, 1, BUFSIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return buf[buf_pos++];
}

inline bool readInt(int &out) {
    int c = getChar();
    if (c == EOF) return false;
    // skip non‑numeric characters
    while (c != '-' && (c < '0' || c > '9')) {
        c = getChar();
        if (c == EOF) return false;
    }
    int sign = 1;
    if (c == '-') {
        sign = -1;
        c = getChar();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getChar();
    }
    out = x * sign;
    return true;
}

int main() {
    int N;
    if (!readInt(N)) return 0;

    std::uint32_t ones = 0, twos = 0;   // bit masks

    for (int i = 0; i < N; ++i) {
        int v;
        readInt(v);
        std::uint32_t x = static_cast<std::uint32_t>(v);

        std::uint32_t new_twos = twos | (ones & x);
        std::uint32_t new_ones = ones ^ x;
        std::uint32_t threes   = new_ones & new_twos;

        ones = new_ones & ~threes;
        twos = new_twos & ~threes;
    }

    int answer = static_cast<int>(ones);
    std::printf("%d\n", answer);
    return 0;
}
