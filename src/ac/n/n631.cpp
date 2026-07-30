#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    while(cin>>n){
        vector<int> cnt(53,0);
        int p;
        for(int i=0;i<n;i++){
            cin>>p;
            if(p>=1 && p<=52) cnt[p]++;
        }
        int maxct=0, minct=n;
        for(int i=1;i<=52;i++){
            if(cnt[i]>maxct) maxct=cnt[i];
            if(cnt[i]<minct) minct=cnt[i];
        }
        cout<<minct<<" "<<maxct*52-n<<"\n";
    }
    return 0;
}
