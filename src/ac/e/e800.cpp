#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Video {
    string name;
    long long num;
    long long den;
    int idx;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    while (cin >> N) {
        vector<Video> videos(N);
        for (int i = 0; i < N; ++i) {
            string S;
            long long P;
            long long L, W, R;
            cin >> S >> P >> L >> W >> R;
            videos[i].name = S;
            videos[i].num = P * W * R;
            videos[i].den = L * 100;
            videos[i].idx = i;
        }
        
        stable_sort(videos.begin(), videos.end(), [](const Video& a, const Video& b) {
            return a.num * b.den > b.num * a.den;
        });
        
        for (int i = 0; i < N; ++i) {
            cout << videos[i].name << "\n";
        }
    }
    
    return 0;
}
