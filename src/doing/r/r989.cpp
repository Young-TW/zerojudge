#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N,M;
    long long L;
    while(cin>>N>>M>>L){
        vector<int> K(N);
        for(int i=0;i<N;++i){cin>>K[i];--K[i];}
        vector<long long> ps(M+1,0);
        for(int i=0;i<M;++i){long long s;cin>>s;ps[i+1]=ps[i]+s;}
        sort(K.begin(),K.end());
        long long tot=0;
        for(int i=0;i<N-1;++i)
            tot+=(ps[K[i+1]+1]-ps[K[i]])/L;
        tot+=(ps[K[N-1]+1]-ps[K[0]])/L;
        cout<<tot<<"\n";
    }
    return 0;
}
