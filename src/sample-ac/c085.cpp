#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Z, I, M, L;
    int case_num = 1;
    
    while (cin >> Z >> I >> M >> L && (Z || I || M || L)) {
        int vis[10005];
        memset(vis, 0, sizeof(vis));
        int step = 1;
        
        while (vis[L] == 0) {
            vis[L] = step;
            L = (Z * L + I) % M;
            step++;
        }
        
        cout << "Case " << case_num << ": " << step - vis[L] << "\n";
        case_num++;
    }
    
    return 0;
}
