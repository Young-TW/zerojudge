#include <cstdio>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int main() {
    int D;
    while (scanf("%d", &D) == 1) {
        long long base = 0;
        long long sum = 0;
        long long count = 0;
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        
        for (int i = 0; i < D; ++i) {
            long long v, d;
            if (scanf("%lld %lld", &v, &d) != 2) break;
            base += d;
            sum -= d * count;
            while (!pq.empty() && pq.top() <= base) {
                long long val = pq.top();
                pq.pop();
                sum -= (val - base);
                count--;
            }
            count++;
            sum += v;
            pq.push(v + base);
            printf("%lld\n", sum);
        }
    }
    return 0;
}
