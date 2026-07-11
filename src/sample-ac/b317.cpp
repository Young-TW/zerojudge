#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Magic {
    int r, h;
    bool operator<(const Magic& other) const {
        if (h != other.h) return h < other.h;
        return r < other.r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, K;
    while (cin >> N >> K) {
        vector<Magic> magics(N);
        for (int i = 0; i < N; ++i) {
            cin >> magics[i].r >> magics[i].h;
        }
        
        sort(magics.begin(), magics.end());
        
        priority_queue<int> pq;
        long long min_volume = -1;
        
        for (int i = 0; i < N; ++i) {
            pq.push(magics[i].r);
            if ((int)pq.size() > K) {
                pq.pop();
            }
            if ((int)pq.size() == K) {
                long long R = pq.top();
                long long H = magics[i].h;
                long long volume = 4 * R * R * H;
                if (min_volume == -1 || volume < min_volume) {
                    min_volume = volume;
                }
            }
        }
        
        cout << min_volume << "\n";
    }
    
    return 0;
}
