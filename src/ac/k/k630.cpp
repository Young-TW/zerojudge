// k630. 產生隨機亂數1 — 無輸入,輸出一個隨機數(special judge)。
// 每次執行用 random_device+時間種子產生不同的正整數,避免「跨執行需相異」的判定。
#include <cstdio>
#include <random>
#include <chrono>
int main(){
    unsigned long long seed =
        (unsigned long long)std::chrono::high_resolution_clock::now().time_since_epoch().count();
    seed ^= std::random_device{}();
    std::mt19937_64 rng(seed);
    unsigned int x = 1u + (unsigned int)(rng() % 1000000ull);  // [1,1000000]
    printf("%u\n", x);
    return 0;
}
