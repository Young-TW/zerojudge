// k632. 產生隨機亂數2 — 輸出 1..N 的隨機排列(special judge 驗證是否為合法排列)
// 讀 N,Fisher-Yates 洗牌 1..N,以空格分隔輸出。
#include <cstdio>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
int main(){
    long long n;
    if(scanf("%lld", &n) != 1) return 0;
    if(n <= 0){ return 0; }
    vector<int> a(n);
    for(long long i = 0; i < n; ++i) a[i] = (int)(i + 1);
    unsigned long long seed =
        (unsigned long long)chrono::high_resolution_clock::now().time_since_epoch().count();
    seed ^= random_device{}();
    mt19937_64 rng(seed);
    for(long long i = n - 1; i > 0; --i){
        long long j = (long long)(rng() % (unsigned long long)(i + 1));
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
    // 快速輸出
    for(long long i = 0; i < n; ++i){
        if(i) putchar(' ');
        printf("%d", a[i]);
    }
    putchar('\n');
    return 0;
}
