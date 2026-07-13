#include <cstdio>
#include <iostream>
using namespace std;

int main(){
    int n;
    if(!(cin>>n)) return 0;
    double sumY = 0.0;
    int total = n*n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int r,g,b;
            cin>>r>>g>>b;
            double X = 0.5149*r + 0.3244*g + 0.1607*b;
            double Y = 0.2654*r + 0.6704*g + 0.0642*b;
            double Z = 0.0248*r + 0.1248*g + 0.8504*b;
            printf("%.4f %.4f %.4f\n", X, Y, Z);
            sumY += Y;
        }
    }
    printf("The average of Y is %.4f\n", sumY/total);
    return 0;
}
