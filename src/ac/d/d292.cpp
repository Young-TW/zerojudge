#include <bits/stdc++.h>
using namespace std;
int main(){
    // UVa 386 Perfect Cubes: a^3 = b^3 + c^3 + d^3, all > 1, 1<b<=c<=d<a<=200
    for(long long a=2;a<=200;a++){
        long long a3=a*a*a;
        for(long long b=2;b<a;b++){
            long long b3=b*b*b;
            if(b3*3>=a3) break; // b<=c<=d => b3*3 <= a3
            for(long long c=b;c<a;c++){
                long long c3=c*c*c;
                long long rem=a3-b3-c3;
                if(rem< c3) break; // d>=c => rem = d^3 >= c^3
                // find d with d^3 == rem, d>=c, d<a
                long long d=llround(cbrt((double)rem));
                for(long long dd=d-2; dd<=d+2; dd++){
                    if(dd>=c && dd<a && dd*dd*dd==rem){
                        printf("Cube = %lld, Triple = (%lld,%lld,%lld)\n",a,b,c,dd);
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
