#include <cstdio>
#include <cstring>

int main() {
    long long t;
    while (scanf("%lld", &t) == 1) {
        const int chunk_size = 100000;
        char buf[chunk_size * 7 + 1];
        for (int i = 0; i < chunk_size; ++i) {
            memcpy(buf + i * 7, "=_=|||\n", 7);
        }
        
        long long chunks = t / chunk_size;
        long long rem = t % chunk_size;
        
        for (long long i = 0; i < chunks; ++i) {
            fwrite(buf, 1, chunk_size * 7, stdout);
        }
        if (rem > 0) {
            fwrite(buf, 1, rem * 7, stdout);
        }
    }
    return 0;
}
