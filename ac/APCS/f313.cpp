#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

// void printVector(vector<vector<int>> v){
//     for(const auto& i : v){
//         for(const auto& j : i){
//             cout << j << " \t";
//         }
//         cout << endl;
//     }
// }

int main(){
    int r,c,k,m;
    cin >> r >> c >> k >> m;
    vector<vector<int>> city(r+2,vector<int>(c+2));
    vector<vector<int>> carry(r+2,vector<int>(c+2));
    // 取得輸入
    for(int i=0;i<r+2;i++){
        for(int j=0;j<c+2;j++){
            if(i==0 || i==r+1 || j==0 || j==c+1){
                city[i][j] = -1;
            }else{
                cin >> city[i][j];
                
            }
        }
    }
    // 計算遷移
    int peopleCount;
    for(int days=0;days<m;days++){
        for(int i=1;i<r+1;i++){
            for(int j=1;j<c+1;j++){
                carry[i][j] = 0;
            }
        }
        for(int i=1;i<r+1;i++){
            for(int j=1;j<c+1;j++){
                peopleCount=0;
                if(city[i-1][j] != -1){
                    carry[i-1][j] += city[i][j]/k;
                    peopleCount += city[i][j]/k;
                }
                if(city[i+1][j] != -1){
                    carry[i+1][j] += city[i][j]/k;
                    peopleCount += city[i][j]/k;
                }
                if(city[i][j-1] != -1){
                    carry[i][j-1] += city[i][j]/k;
                    peopleCount += city[i][j]/k;
                }
                if(city[i][j+1] != -1){
                    carry[i][j+1] += city[i][j]/k;
                    peopleCount += city[i][j]/k;
                }
                city[i][j] -= peopleCount;
            }
        }
        for(int i=1;i<r+1;i++){
            for(int j=1;j<c+1;j++){
                city[i][j] += carry[i][j];
            }
        }
    }
    // printVector(city);
    int max=INT_MIN,min=INT_MAX;
    for(const auto& i : city){
        for(const auto& j : i){
            if(max < j)
                max = j;
            if(j != -1 && min > j)
                min = j;
        }
    }
    cout << min << endl << max;
    return 0;
}