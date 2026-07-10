#include <cstdio>
using namespace std;

int main(){
    long long a,b,c,d,e,f;
    if(scanf("%lld %lld %lld %lld %lld %lld",&a,&b,&c,&d,&e,&f)!=6) return 0;
    long long det = a*e - b*d;
    if(det != 0){
        __int128 nx = (__int128)c*e - (__int128)b*f;
        __int128 ny = (__int128)a*f - (__int128)c*d;
        __int128 den = det;
        auto cents = [&](__int128 num, __int128 dd) -> long long {
            if(dd < 0){ num = -num; dd = -dd; }
            __int128 q = num*100 / dd;
            __int128 r = num*100 % dd;
            __int128 ar = r < 0 ? -r : r;
            if(2*ar >= dd) q += (num >= 0 ? 1 : -1);
            return (long long)q;
        };
        long long cx = cents(nx, den);
        long long cy = cents(ny, den);
        printf("x=%.2f\ny=%.2f\n", (double)cx/100.0, (double)cy/100.0);
    } else {
        bool consistent;
        if(a==0 && b==0 && d==0 && e==0){
            consistent = (c==0 && f==0);
        } else {
            __int128 m13 = (__int128)a*f - (__int128)c*d;
            __int128 m23 = (__int128)b*f - (__int128)c*e;
            consistent = (m13==0 && m23==0);
        }
        printf(consistent ? "Too many\n" : "No answer\n");
    }
    return 0;
}
