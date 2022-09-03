#include <iostream>
#include <vector>
using namespace std;

int main(){
    int s,t,n,m,r,a=0;
    cin >> s >> t >> n >> m >> r;
    int A[10][10], B[10][10];
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

    int count=0;
    int nearby;
    for(int x=0;x<n-s;x++){
        for(int y=0;y<m-t;y++){
            int b=0;
            for(int i=x;i<s;i++){
                for(int j=y;j<t;j++){
                    b += B[i][j];
                    cout << B[i][j] << " ";
                }
            }
            cout << endl;
            if(b>a-r || b<a+r)
                count++;
                nearby = b;
        }
        cout << endl << endl;
    }

    if(count==0)
        nearby = -1;

    cout << count << endl << nearby;
    
    return 0;
}