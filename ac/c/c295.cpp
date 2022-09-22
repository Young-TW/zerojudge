#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n,m,tt=0,temp;
    cin >> n >> m;
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> temp;
            ans[i] = max(ans[i],temp);
        }
        tt += ans[i];
    }
    cout << tt << endl;
    bool judge=1;
    for(int i=0;i<n;i++){
        if (tt % ans[i] == 0) {
            if (!judge) cout << ' ';
            cout << ans[i];
            judge = 0;
        }
    }
    if(judge){
        cout << "-1";
    }
    return 0;
}