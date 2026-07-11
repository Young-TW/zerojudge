#include <iostream>
#include <cstring>
using namespace std;

int cnt[30005];

int main(){
    int n;
    while(cin >> n){
        memset(cnt, 0, sizeof(cnt));
        for(int i=0;i<n;i++){
            int x; cin >> x;
            cnt[x]++;
        }
        int mx = 0;
        for(int i=1;i<=30000;i++) if(cnt[i] > mx) mx = cnt[i];
        for(int i=1;i<=30000;i++){
            if(cnt[i] == mx){
                cout << i << "   " << mx << "\n";
            }
        }
    }
    return 0;
}
