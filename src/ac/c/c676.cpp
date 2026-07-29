// c676. 大家來出題1 簡易加法 — output-only,產生100組 n1 n2 (n1+n2),ans不重複
#include <cstdio>
int main(){
    for(int i=1;i<=100;i++) printf("%d %d %d\n", i, 100000+i, 100000+2*i); // sum=100002..100200 皆相異
    return 0;
}
