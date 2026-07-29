#include <bits/stdc++.h>
using namespace std;

// AST node types
enum { NUM, VAR, CE, ADD, SUB, MUL, DIV, POW, NEG, POS, FUN };
struct N { int t; string s; N *a=nullptr, *b=nullptr; };
static N* mk(int t, const string& s="", N* a=nullptr, N* b=nullptr){ N* n=new N(); n->t=t; n->s=s; n->a=a; n->b=b; return n; }
static N* num(const string& s){ return mk(NUM,s); }
static N* ONE(){ return mk(NUM,"1"); }
static N* TWO(){ return mk(NUM,"2"); }

// ---------- Parser ----------
static string S; static size_t P;
static bool isfun(const string& f){ return f=="sin"||f=="cos"||f=="tan"||f=="cot"||f=="sec"||f=="csc"||f=="ln"; }
static N* pAdd();
static bool starter(char c){ return c=='('||isdigit((unsigned char)c)||c=='.'||(c>='a'&&c<='z'); }
static N* pAtom(){
    char c = P<S.size()? S[P] : 0;
    if(c=='('){ P++; N* e=pAdd(); if(P<S.size()&&S[P]==')') P++; return e; }
    if(isdigit((unsigned char)c)||c=='.'){ string t; while(P<S.size()&&(isdigit((unsigned char)S[P])||S[P]=='.')) t+=S[P++]; return num(t); }
    if(c>='a'&&c<='z'){
        // try function names (len 3 or 2)
        if(P+3<=S.size()){ string f=S.substr(P,3); if(isfun(f)){ P+=3; if(P<S.size()&&S[P]=='(') P++; N* arg=pAdd(); if(P<S.size()&&S[P]==')') P++; return mk(FUN,f,arg); } }
        if(P+2<=S.size()){ string f=S.substr(P,2); if(isfun(f)){ P+=2; if(P<S.size()&&S[P]=='(') P++; N* arg=pAdd(); if(P<S.size()&&S[P]==')') P++; return mk(FUN,f,arg); } }
        if(c=='e'){ P++; return mk(CE); }
        if(c=='x'||c=='y'||c=='z'){ P++; return mk(VAR,string(1,c)); }
        P++; return mk(NUM,"0"); // fallback
    }
    return num("0");
}
static N* pUnary();
static N* pPow(){
    N* base = pAtom();
    if(P<S.size()&&S[P]=='^'){ P++; N* e=pUnary(); return mk(POW,"",base,e); }
    return base;
}
static N* pUnary(){
    if(P<S.size()&&(S[P]=='+'||S[P]=='-')){ char op=S[P++]; N* u=pUnary(); return mk(op=='-'?NEG:POS,"",u); }
    return pPow();
}
static N* pMul(){
    N* l = pUnary();
    for(;;){
        if(P<S.size()&&(S[P]=='*'||S[P]=='/')){ char op=S[P++]; N* r=pUnary(); l=mk(op=='*'?MUL:DIV,"",l,r); }
        else if(P<S.size()&&starter(S[P])){ N* r=pUnary(); l=mk(MUL,"",l,r); }
        else break;
    }
    return l;
}
static N* pAdd(){
    N* l = pMul();
    while(P<S.size()&&(S[P]=='+'||S[P]=='-')){ char op=S[P++]; N* r=pMul(); l=mk(op=='+'?ADD:SUB,"",l,r); }
    return l;
}
static N* parse(const string& in){ S=in; P=0; return pAdd(); }

// ---------- Differentiation (null == zero) ----------
static char VARC;
static N* addN(N* a,N* b){ return a? (b? mk(ADD,"",a,b): a) : b; }
static N* subN(N* a,N* b){ if(!b) return a; if(!a) return mk(NEG,"",b); return mk(SUB,"",a,b); }
static N* mulN(N* a,N* b){ return (a&&b)? mk(MUL,"",a,b): nullptr; }
static N* D(N* n){
    switch(n->t){
        case NUM: case CE: return nullptr;
        case VAR: return n->s[0]==VARC? ONE(): nullptr;
        case NEG: { N* d=D(n->a); return d? mk(NEG,"",d): nullptr; }
        case POS: return D(n->a);
        case ADD: return addN(D(n->a),D(n->b));
        case SUB: return subN(D(n->a),D(n->b));
        case MUL: return addN( mulN(D(n->a),n->b), mulN(n->a,D(n->b)) );
        case DIV: {
            N* num2 = subN( mulN(D(n->a),n->b), mulN(n->a,D(n->b)) );
            if(!num2) return nullptr;
            return mk(DIV,"",num2, mk(POW,"",n->b,TWO()));
        }
        case POW: {
            N *a=n->a,*b=n->b; N *da=D(a),*db=D(b);
            // a^b * ln(a) * b'  +  b * a^(b-1) * a'
            N* t1 = db? mulN( mulN( mk(POW,"",a,b), mk(FUN,"ln",a) ), db ) : nullptr;
            N* t2 = da? mulN( mulN( b, mk(POW,"",a, mk(SUB,"",b,ONE())) ), da ) : nullptr;
            return addN(t1,t2);
        }
        case FUN: {
            N* u=n->a; N* du=D(u); if(!du) return nullptr; const string& f=n->s;
            if(f=="ln")  return mk(DIV,"",du,u);
            if(f=="sin") return mk(MUL,"",mk(FUN,"cos",u),du);
            if(f=="cos") return mk(NEG,"",mk(MUL,"",mk(FUN,"sin",u),du));
            if(f=="tan") return mk(MUL,"",mk(POW,"",mk(FUN,"sec",u),TWO()),du);
            if(f=="cot") return mk(NEG,"",mk(MUL,"",mk(POW,"",mk(FUN,"csc",u),TWO()),du));
            if(f=="sec") return mk(MUL,"",mk(MUL,"",mk(FUN,"sec",u),mk(FUN,"tan",u)),du);
            if(f=="csc") return mk(NEG,"",mk(MUL,"",mk(MUL,"",mk(FUN,"csc",u),mk(FUN,"cot",u)),du));
        }
    }
    return nullptr;
}

// ---------- Output (fully parenthesized) ----------
static void pr(N* n, string& o){
    switch(n->t){
        case NUM: o+=n->s; break;
        case VAR: o+=n->s; break;
        case CE:  o+='e'; break;
        case ADD: o+='('; pr(n->a,o); o+='+'; pr(n->b,o); o+=')'; break;
        case SUB: o+='('; pr(n->a,o); o+='-'; pr(n->b,o); o+=')'; break;
        case MUL: o+='('; pr(n->a,o); o+='*'; pr(n->b,o); o+=')'; break;
        case DIV: o+='('; pr(n->a,o); o+='/'; pr(n->b,o); o+=')'; break;
        case POW: o+='('; pr(n->a,o); o+='^'; pr(n->b,o); o+=')'; break;
        case NEG: o+="(-"; pr(n->a,o); o+=')'; break;
        case POS: o+="(+"; pr(n->a,o); o+=')'; break;
        case FUN: o+=n->s; o+='('; pr(n->a,o); o+=')'; break;
    }
}

static string strip(string s){ while(!s.empty()&&(s.back()=='\r'||s.back()==' '||s.back()=='\t'||s.back()=='\n')) s.pop_back(); size_t i=0; while(i<s.size()&&(s[i]==' '||s[i]=='\t')) i++; return s.substr(i); }

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    vector<string> lines; string ln;
    while(getline(cin,ln)) lines.push_back(strip(ln));
    vector<string> outs;
    for(size_t i=0;i<lines.size();){
        if(lines[i].empty()){ i++; continue; }
        string expr=lines[i++];
        while(i<lines.size()&&lines[i].empty()) i++;
        if(i>=lines.size()) break;
        string var=lines[i++];
        VARC = var.empty()? 'x' : var[0];
        N* f=parse(expr); N* d=D(f);
        string o; if(!d) o="0"; else pr(d,o);
        outs.push_back(o);
    }
    string res;
    for(size_t i=0;i<outs.size();i++){ if(i) res+="\n\n"; res+=outs[i]; }
    res+="\n";
    cout<<res;
    return 0;
}
