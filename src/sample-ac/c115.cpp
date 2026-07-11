#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
    int w, l, h;
    Block(int a, int b, int c) {
        w = min(a, b);
        l = max(a, b);
        h = c;
    }
    bool operator<(const Block& other) const {
        if (l != other.l) return l > other.l;
        return w > other.w;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    int case_num = 1;
    
    while (cin >> n && n) {
        vector<Block> blocks;
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            blocks.push_back(Block(x, y, z));
            blocks.push_back(Block(x, z, y));
            blocks.push_back(Block(y, z, x));
        }
        
        sort(blocks.begin(), blocks.end());
        
        int m = blocks.size();
        vector<int> dp(m);
        int max_h = 0;
        
        for (int i = 0; i < m; ++i) {
            dp[i] = blocks[i].h;
            for (int j = 0; j < i; ++j) {
                if (blocks[j].l > blocks[i].l && blocks[j].w > blocks[i].w) {
                    dp[i] = max(dp[i], dp[j] + blocks[i].h);
                }
            }
            max_h = max(max_h, dp[i]);
        }
        
        cout << "Case " << case_num++ << ": maximum height = " << max_h << "\n";
    }
    
    return 0;
}
