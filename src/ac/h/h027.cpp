#include <iostream>
#include <vector>
using namespace std;

int main(){
    int s,t,n,m,r,a=0;
    cin >> s >> t >> n >> m >> r;
    int A[10][100], B[10][100];
    for(int i=0;i<s;i++){
        for(int j=0;j<t;j++){
            cin >> A[i][j];
            a += A[i][j];
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> B[i][j];
        }
    }
    int count = 0;
    int mn = 1e6;
    for(int x=0;x<=n-s;x++){
        for(int y=0;y<=m-t;y++){
            int dist = 0;
            int b=0;
            for(int i=0;i<s;i++){
                for(int j=0;j<t;j++){
                    dist += (A[i][j] != B[i+x][j+y]);
                    b += B[i+x][j+y];
                }
            }
            if(dist<=r){
                count++;
                mn = min(mn, abs(a-b));
            }
        }
    }

    if(count>0)
        cout << count << endl << mn << endl;
    else
        cout << "0" << endl << "-1" << endl;
    return 0;
}