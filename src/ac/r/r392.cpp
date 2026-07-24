#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    map<int, int> cnt;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    long long ans = 0;
    for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        int x = it->first;
        int c = it->second;
        int group_size = x + 1;
        int groups = (c + group_size - 1) / group_size;
        ans += (long long)groups * group_size;
    }

    cout << ans << "\n";

    return 0;
}
