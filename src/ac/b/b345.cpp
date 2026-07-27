#include <bits/stdc++.h>
using namespace std;

const long long MOD = 99999997;

// Fenwick for inversion counting
struct BIT {
    int n;
    vector<int> t;
    BIT(int n=0):n(n),t(n+1,0){}
    void add(int i){ for(; i<=n; i+=i&-i) t[i]++; }
    int sum(int i){ int s=0; for(; i>0; i-=i&-i) s+=t[i]; return s; }
};

// compute min adjacent swaps (mod MOD) to align a to b
long long solve(const vector<long long>& a, const vector<long long>& b){
    int n = a.size();
    // ranks of a and b
    vector<long long> sa=a, sb=b;
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    // rankA[i] = index (0..n-1) of a[i] in sorted a
    auto rankOf = [](const vector<long long>& v, const vector<long long>& sorted){
        vector<int> r(v.size());
        for(size_t i=0;i<v.size();++i)
            r[i] = int(lower_bound(sorted.begin(), sorted.end(), v[i]) - sorted.begin());
        return r;
    };
    vector<int> rankA = rankOf(a, sa);
    vector<int> rankB = rankOf(b, sb);
    // posA[r] = position in a whose rank is r
    vector<int> posA(n);
    for(int i=0;i<n;++i) posA[rankA[i]] = i;
    // c[i] = posA[rankB[i]] ; count inversions of c
    vector<int> c(n);
    for(int i=0;i<n;++i) c[i] = posA[rankB[i]];
    // inversion count with BIT (c values are 0..n-1, a permutation)
    BIT bit(n);
    long long inv = 0;
    for(int i=n-1;i>=0;--i){
        inv += bit.sum(c[i]);        // count already-added values < c[i]
        inv %= MOD;
        bit.add(c[i]+1);
    }
    return inv % MOD;
}

static bool isHeaderLine(const string& s){
    for(char ch : s){
        if(ch==' '||ch=='\t'||ch=='\r'||ch=='\n') continue;
        // first meaningful char: data if digit or sign
        if(isdigit((unsigned char)ch) || ch=='-' || ch=='+') return false;
        return true; // non-numeric leading char -> header
    }
    return false; // blank line: not a header
}

static string rtrim(string s){
    while(!s.empty() && (s.back()=='\r'||s.back()=='\n'||s.back()==' '||s.back()=='\t'))
        s.pop_back();
    return s;
}

static bool isBlank(const string& s){
    for(char c : s) if(c!=' '&&c!='\t'&&c!='\r'&&c!='\n') return false;
    return true;
}

int main(){
    // read all lines
    vector<string> lines;
    string line;
    while(getline(cin, line)) lines.push_back(line);

    int i=0, N=lines.size();
    bool firstBlock=true;
    string out;

    auto readIntsFromLine = [](const string& s){
        vector<long long> v; long long x;
        stringstream ss(s);
        while(ss>>x) v.push_back(x);
        return v;
    };

    while(i<N){
        // skip blanks
        while(i<N && isBlank(lines[i])) i++;
        if(i>=N) break;

        string header="";
        if(isHeaderLine(lines[i])){
            header = rtrim(lines[i]);
            i++;
            while(i<N && isBlank(lines[i])) i++;
        }
        if(i>=N) break;

        // n line: first int
        vector<long long> nv = readIntsFromLine(lines[i]);
        if(nv.empty()){ i++; continue; }
        int n = (int)nv[0];
        i++;
        if(n<=0){
            // still emit block with answer 0 if header present
            if(!firstBlock) out += "\n\n";
            if(!header.empty()) out += header + "\n";
            out += "0";
            firstBlock=false;
            continue;
        }

        // read array a: gather n ints starting from current line (line-aware)
        auto readArray = [&](int cnt)->vector<long long>{
            vector<long long> arr;
            while((int)arr.size()<cnt && i<N){
                while(i<N && isBlank(lines[i])) i++;
                if(i>=N) break;
                vector<long long> t = readIntsFromLine(lines[i]);
                i++;
                for(long long x : t){
                    if((int)arr.size()<cnt) arr.push_back(x);
                }
            }
            return arr;
        };

        vector<long long> a = readArray(n);
        vector<long long> b = readArray(n);
        if((int)a.size()<n || (int)b.size()<n) break; // malformed / EOF

        long long ans = solve(a,b);

        if(!firstBlock) out += "\n\n";
        if(!header.empty()) out += header + "\n";
        out += to_string(ans);
        firstBlock=false;
    }

    cout << out << "\n";
    return 0;
}
