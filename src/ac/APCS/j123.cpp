#include <iostream>
#include <vector>
using namespace std;

int main(){
    char t;
    int r,c,n,y,pack=0,high,blocks=0;
    cin >> r >> c >> n;
    vector<int> box(r);
    for(int i=0;i<n;i++){
        cin >> t >> y;
        switch(t){
            case 'A':
                high = max(max(box[y],box[y+1]),max(box[y+2],box[y+3]))+1;
                if(high <= c){
                    for(int j=0;j<4;j++){
                        box[y+j] = high;
                    }
                    blocks += 4;
                    pack++;
                }
                break;
            case 'B':
                if(box[y]+3 <= c){
                    box[y] += 3;
                    blocks += 3;
                    pack++;
                }
                break;
            case 'C':
                high = max(box[y],box[y+1])+2;
                if(high <= c){
                    blocks += 4;
                    box[y] = high;
                    box[y+1] = high;
                    pack++;
                }
                break;
            case 'D':
                high = max(box[y]-2,box[y+1])+3;
                if(high <= c){
                    blocks += 4;
                    box[y] = high;
                    box[y+1] = high;
                    pack++;
                }
                break;
            case 'E':
                high = max(max(box[y]-1,box[y+1]),box[y+2])+2;
                if(high <= c){
                    blocks += 5;
                    box[y] = high;
                    box[y+1] = high;
                    box[y+2] = high;
                    pack++;
                }
                break;
        }
    }
    cout << (r*c)-blocks << " " << n-pack << endl;
    return 0;
}