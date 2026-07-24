#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
struct Node {
    int h, c;
};
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        vector<Node> stk;
        stk.reserve(n);
        ll ans = 0;
        for (int i = 0; i < n; ++i) {
            int h;
            scanf("%d", &h);
            int cnt = 1;
            while (!stk.empty() && stk.back().h <= h) {
                ans += stk.back().c;
                if (stk.back().h == h) cnt += stk.back().c;
                stk.pop_back();
            }
            if (!stk.empty()) ans += 1;
            stk.push_back({h, cnt});
        }
        printf("%lld\n", ans * 2);
    }
    return 0;
}
