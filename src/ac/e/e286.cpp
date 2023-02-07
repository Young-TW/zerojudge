#include <iostream>
using namespace std;

int main(){
    int sum1, sum2, point1 = 0, point2 = 0;
    int input;
    for(int k=0;k<2;k++){
        sum1 = 0;
        sum2 = 0;
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                cin >> input;
                if(i == 0){
                    sum1 += input;
                }else{
                    sum2 += input;
                }
            }
        }
        cout << sum1 << ":" << sum2 << endl;
        if(sum1 > sum2){
            point1++;
        }else{
            point2++;
        }
    }
    if(point1 > point2){
        cout << "Win";
    }else if(point1 == point2){
        cout << "Tie";
    }else{
        cout << "Lose";
    }
    return 0;
}