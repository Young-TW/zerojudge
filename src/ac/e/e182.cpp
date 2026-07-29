#include <bits/stdc++.h>
using namespace std;

static char* buf;
static size_t bufsz, bufpos;
static inline bool readInt(long long &out){
    while(bufpos<bufsz){
        char c=buf[bufpos];
        if((c>='0'&&c<='9')||c=='-') break;
        bufpos++;
    }
    if(bufpos>=bufsz) return false;
    bool neg=false;
    if(buf[bufpos]=='-'){neg=true;bufpos++;}
    long long v=0; bool any=false;
    while(bufpos<bufsz && buf[bufpos]>='0'&&buf[bufpos]<='9'){
        v=v*10+(buf[bufpos]-'0'); bufpos++; any=true;
    }
    if(!any) return false;
    out=neg?-v:v;
    return true;
}

// generic count: group positions (1-indexed) by key, count pairs (i<j) in same group
// with pos[i] > prevA[pos[j]]  and  nextA[pos[i]] > pos[j]
long long countPairs(int n, vector<int>&key, vector<int>&prevA, vector<int>&nextA,
                     int keyMin, int keyMax){
    int range = keyMax-keyMin+1;
    vector<int> cnt(range+1,0);
    for(int i=1;i<=n;i++) cnt[key[i]-keyMin]++;
    vector<int> start(range+1,0);
    for(int k=1;k<range;k++) start[k]=start[k-1]+cnt[k-1];
    vector<int> flat(n);
    vector<int> fill=start;
    for(int i=1;i<=n;i++){ int k=key[i]-keyMin; flat[fill[k]++]=i; }
    long long ans=0;
    vector<int> fenw; // local per group, size m+1
    for(int k=0;k<range;k++){
        int gs=start[k]; int m=cnt[k];
        if(m<2) continue;
        int *g=&flat[gs];
        fenw.assign(m+1,0);
        auto fupd=[&](int i,int d){ for(;i<=m;i+=i&(-i)) fenw[i]+=d; };
        auto fq=[&](int i){ int s=0; for(;i>0;i-=i&(-i)) s+=fenw[i]; return s; };
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        for(int j=0;j<m;j++){
            int r=g[j];
            while(!pq.empty() && pq.top().first <= r){
                int idx=pq.top().second; pq.pop();
                fupd(idx+1,-1);
            }
            int pg=prevA[r];
            int lo=0,hi=m;
            while(lo<hi){int mid=(lo+hi)>>1; if(g[mid]>pg) hi=mid; else lo=mid+1;}
            int t=lo;
            ans += fq(m) - fq(t);
            fupd(j+1,+1);
            pq.push({nextA[g[j]], j});
        }
    }
    return ans;
}

int main(){
    {
        std::string data;
        FILE*f=stdin;
        if(fseek(f,0,SEEK_END)==0){
            long sz=ftell(f);
            if(sz>0){ fseek(f,0,SEEK_SET); data.resize(sz); size_t rd=fread(&data[0],1,sz,f); data.resize(rd);}
        }
        if(data.empty()){ char tmp[1<<16]; size_t r; while((r=fread(tmp,1,sizeof(tmp),stdin))>0) data.append(tmp,r);}
        static string hold; hold=std::move(data);
        buf=&hold[0]; bufsz=hold.size(); bufpos=0;
    }
    long long T;
    if(!readInt(T)) return 0;
    string out;
    for(long long tc=0;tc<T;tc++){
        long long nn; if(!readInt(nn)) break;
        int n=(int)nn;
        vector<int> S(n+2);
        for(int i=1;i<=n;i++){ long long x; readInt(x); S[i]=(int)x; }
        vector<int> PG(n+2),NS(n+2),PS(n+2),NG(n+2);
        vector<int> st; st.reserve(n+1);
        st.clear();
        for(int i=1;i<=n;i++){ while(!st.empty()&&S[st.back()]<=S[i]) st.pop_back(); PG[i]=st.empty()?0:st.back(); st.push_back(i);}
        st.clear();
        for(int i=1;i<=n;i++){ while(!st.empty()&&S[st.back()]>=S[i]) st.pop_back(); PS[i]=st.empty()?0:st.back(); st.push_back(i);}
        st.clear();
        for(int i=n;i>=1;i--){ while(!st.empty()&&S[st.back()]>=S[i]) st.pop_back(); NS[i]=st.empty()?(n+1):st.back(); st.push_back(i);}
        st.clear();
        for(int i=n;i>=1;i--){ while(!st.empty()&&S[st.back()]<=S[i]) st.pop_back(); NG[i]=st.empty()?(n+1):st.back(); st.push_back(i);}
        vector<int> key1(n+2),key2(n+2);
        int k1min=INT_MAX,k1max=INT_MIN,k2min=INT_MAX,k2max=INT_MIN;
        for(int i=1;i<=n;i++){ key1[i]=S[i]-i; key2[i]=S[i]+i;
            k1min=min(k1min,key1[i]);k1max=max(k1max,key1[i]);
            k2min=min(k2min,key2[i]);k2max=max(k2max,key2[i]); }
        long long ans=0;
        if(n>=2){
            ans += countPairs(n,key1,PG,NS,k1min,k1max);
            ans += countPairs(n,key2,PS,NG,k2min,k2max);
        }
        out += to_string(ans); out += '\n';
    }
    fputs(out.c_str(),stdout);
    return 0;
}
