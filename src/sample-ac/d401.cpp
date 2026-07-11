#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        vector<int> sponge;
        vector<int> patrick;

        for (int i = 0; i < N; ++i) {
            int a, b;
            cin >> a >> b;
            if (a == 1) {
                sponge.push_back(b);
            } else {
                patrick.push_back(b);
            }
        }

        sort(sponge.begin(), sponge.end(), greater<int>());
        sort(patrick.begin(), patrick.end(), greater<int>());

        int K;
        cin >> K;

        int sponge_val = (K <= sponge.size()) ? sponge[K-1] : 0;
        int patrick_val = (K <= patrick.size()) ? patrick[K-1] : 0;

        if (sponge_val > patrick_val) {
            cout << "1 " << sponge_val - patrick_val << '\n';
        } else if (patrick_val > sponge_val) {
            cout << "2 " << patrick_val - sponge_val << '\n';
        } else {
            cout << "1 0\n";
        }
    }

    return 0;
}
