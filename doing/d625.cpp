#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n,x,y;
    char index;
    cin >> n;
    x=n;
    y=n;
    vector<vector<char>> v;

    while(y>0){
        x=n;
        while(x>0){
            cin >> index;
            v[y][x] = index;
            x--;
        }
        y--;
    }
    return 0;
}

// 踩地雷真好玩