#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <utility>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,d;
    while(cin>>n>>m>>d){
        if(n==0&&m==0&&d==0) break;
        int N=n*m;
        vector<bitset<625>> A(N);
        vector<int> b(N,0);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cin>>b[i*n+j];
            }
        }
        for(int a=0;a<m;a++){
            for(int c=0;c<n;c++){
                int var=a*n+c;
                A[a*n+c][var]=1;
                for(int i=0;i<m;i++){
                    for(int j=0;j<n;j++){
                        if(abs(i-a)+abs(j-c)==d){
                            A[i*n+j][var]=1;
                        }
                    }
                }
            }
        }
        int rank=0;
        for(int col=0;col<N;col++){
            int pivot=-1;
            for(int r=rank;r<N;r++){
                if(A[r][col]){pivot=r;break;}
            }
            if(pivot==-1) continue;
            swap(A[rank],A[pivot]);
            swap(b[rank],b[pivot]);
            for(int r=0;r<N;r++){
                if(r!=rank && A[r][col]){
                    A[r]^=A[rank];
                    b[r]^=b[rank];
                }
            }
            rank++;
        }
        bool ok=true;
        for(int r=rank;r<N;r++){
            if(b[r]){ok=false;break;}
        }
        cout<<(ok?1:0)<<"\n";
    }
    return 0;
}
