#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

string stripLead(const string &s){
    int i = 0;
    int n = (int)s.size();
    while (i < n-1 && s[i]=='0') i++;
    return s.substr(i);
}

int cmp(const string &A, const string &B){
    string a = stripLead(A), b = stripLead(B);
    if (a.size()!=b.size()) return a.size()<b.size()?-1:1;
    if (a==b) return 0;
    return a<b?-1:1;
}

string sub(const string &A, const string &B){
    string a = stripLead(A), b = stripLead(B);
    string res;
    int i = (int)a.size()-1, j = (int)b.size()-1, borrow=0;
    while(i>=0){
        int da = a[i]-'0' - borrow;
        int db = j>=0 ? b[j]-'0' : 0;
        if(da < db){ da+=10; borrow=1; } else borrow=0;
        res += char('0'+(da-db));
        i--; j--;
    }
    reverse(res.begin(), res.end());
    return stripLead(res);
}

string mulDigit(const string &B, int x){
    if(x==0) return "0";
    string b = stripLead(B);
    string res;
    int carry=0;
    for(int i=(int)b.size()-1;i>=0;i--){
        int p = (b[i]-'0')*x + carry;
        res += char('0'+ p%10);
        carry = p/10;
    }
    if(carry) res += char('0'+carry);
    reverse(res.begin(), res.end());
    return stripLead(res);
}

pair<string,string> divmod(const string &A, const string &B){
    string a = stripLead(A), b = stripLead(B);
    string prod[10];
    prod[0]="0";
    for(int x=1;x<=9;x++) prod[x]=mulDigit(b,x);
    string rem="0";
    string quo;
    for(int i=0;i<(int)a.size();i++){
        string t = rem + a[i];
        rem = stripLead(t);
        if(rem.empty()) rem="0";
        int q=0;
        for(int x=9;x>=1;x--){
            if(cmp(prod[x],rem)<=0){ q=x; break; }
        }
        quo += char('0'+q);
        rem = sub(rem, prod[q]);
        if(rem.empty()) rem="0";
    }
    quo = stripLead(quo);
    return make_pair(quo, rem);
}

int main(){
    string a,b;
    while(cin>>a>>b){
        pair<string,string> r = divmod(a,b);
        cout<<r.first<<"    "<<r.second<<"\n";
    }
    return 0;
}
