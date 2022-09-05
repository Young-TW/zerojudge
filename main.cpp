#include <iostream>
#include <vector>
using namespace std;

bool pressure(int left,int right,vector<int> trePlace,vector<int> treHigh){
    for(int i=left;i<right;i++){
        for(int j=0;j<trePlace.size();j++){
            if(trePlace[j]==i && treHigh[j]!=0){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int n,l;
    cin >> n >> l;
    vector<int> trePlace(n);
    vector<int> treHigh(n);
    for(int i=0;i<n;i++){
        cin >> trePlace[i];
    }
    for(int i=0;i<n;i++){
        cin >> treHigh[i];
    }
    int highest=0,count=0,lastCount=-1;

    while(1){
        if(lastCount == count)
            break;
        lastCount = count;
        cout << "round" << endl;

        for(int i=0;i<trePlace.size();i++)
            cout << trePlace[i] << " " << treHigh[i] << endl;

        for(int i=0;i<n;i++){
            if((treHigh[i]!=0) && !(pressure(trePlace[i]-treHigh[i],treHigh[i],trePlace,treHigh) || pressure(trePlace[i]+treHigh[i],treHigh[i],trePlace,treHigh))){
                highest = max(treHigh[i], highest);
                treHigh[i]=0;
                count++;
            }
        }
    }

    cout << count << endl << highest;
    return 0;
}