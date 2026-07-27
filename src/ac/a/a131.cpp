#include <bits/stdc++.h>
using namespace std;
int code(char c){
    switch(c){
        case 'B':case 'P':case 'F':case 'V': return 1;
        case 'C':case 'S':case 'K':case 'G':case 'J':case 'Q':case 'X':case 'Z': return 2;
        case 'D':case 'T': return 3;
        case 'L': return 4;
        case 'M':case 'N': return 5;
        case 'R': return 6;
        default: return 0; // A E I O U Y W H
    }
}
int main(){
    string name;
    printf("%9s%-25s%s\n","","NAME","SOUNDEX CODE");
    while(getline(cin,name)){
        // 去除可能的尾端空白/回車
        while(!name.empty() && (name.back()=='\r'||name.back()=='\n'||name.back()==' ')) name.pop_back();
        if(name.empty()) continue;
        string sx; sx+=name[0];
        int prev=code(name[0]);
        for(size_t i=1;i<name.size() && sx.size()<4;i++){
            int c=code(name[i]);
            if(c!=0 && c!=prev) sx+=char('0'+c);
            // H,W 不重置 prev(可拆散規則簡化:非0才更新 prev;H/W(code0)不更新→跨H/W同碼只記一次)
            if(name[i]!='H' && name[i]!='W') prev=c;
        }
        while(sx.size()<4) sx+='0';
        // 名字左對齊佔 25 欄(從第10欄起),碼在第35欄
        printf("%9s%-25s%s\n","",name.c_str(),sx.c_str());
    }
    printf("%19s%s\n","","END OF OUTPUT");
    return 0;
}
