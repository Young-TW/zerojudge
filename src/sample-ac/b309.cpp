#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    static char buf[1 << 16];
    long long cnt[7] = {0, 0, 0, 0, 0, 0, 0};
    const char* names[7] = {"Saber", "Lancer", "Archer", "Rider", "Caster", "Assassin", "Berserker"};
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0) {
        for (size_t i = 0; i < n; ++i) {
            char c = buf[i];
            int idx;
            if (c >= 'A' && c <= 'Z') idx = c - 'A';
            else if (c >= 'a' && c <= 'z') idx = c - 'a';
            else continue;
            cnt[idx % 7]++;
        }
    }
    int best = 0;
    for (int i = 1; i < 7; ++i) {
        if (cnt[i] > cnt[best]) best = i;
    }
    printf("%s\n", names[best]);
    return 0;
}
