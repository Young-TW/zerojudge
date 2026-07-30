#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

enum Kind { ADD, OUT, GOTO, IFGO, ENDS };

struct Stmt {
    Kind kind;
    int var;
    long long num;
    int target;
};

string strip(const string& s) {
    int a = 0, b = (int)s.size();
    while (a < b && (s[a]==' '||s[a]=='\t'||s[a]=='\r'||s[a]=='\n')) a++;
    while (b > a && (s[b-1]==' '||s[b-1]=='\t'||s[b-1]=='\r'||s[b-1]=='\n')) b--;
    return s.substr(a, b - a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    map<int, Stmt> prog;
    string raw;
    while (getline(cin, raw)) {
        string line = strip(raw);
        if (line.empty()) continue;

        size_t i = 0, n = line.size();
        while (i < n && !isdigit((unsigned char)line[i])) i++;
        if (i >= n) continue;
        long long ln = 0;
        while (i < n && isdigit((unsigned char)line[i])) { ln = ln*10 + (line[i]-'0'); i++; }
        string body = strip(line.substr(i));
        if (body.empty()) continue;

        auto skipsp = [](size_t& p, const string& s){ while (p < s.size() && s[p]==' ') p++; };
        Stmt st{};
        size_t p = 0;
        if (body.rfind("END", 0) == 0) {
            st.kind = ENDS;
        } else if (body.rfind("GO", 0) == 0) {
            p = 2; skipsp(p, body);
            long long t = 0; while (p < body.size() && isdigit((unsigned char)body[p])) { t = t*10 + (body[p]-'0'); p++; }
            st.kind = GOTO; st.target = (int)t;
        } else if (body.rfind("IF", 0) == 0) {
            p = 2; skipsp(p, body);
            st.var = body[p]-'A'; p++; skipsp(p, body);
            if (p < body.size() && body[p]=='=') p++;
            skipsp(p, body);
            long long c = 0; while (p < body.size() && isdigit((unsigned char)body[p])) { c = c*10 + (body[p]-'0'); p++; }
            st.num = c;
            skipsp(p, body);
            if (p+1 < body.size() && body[p]=='G' && body[p+1]=='O') p += 2;
            skipsp(p, body);
            long long t = 0; while (p < body.size() && isdigit((unsigned char)body[p])) { t = t*10 + (body[p]-'0'); p++; }
            st.kind = IFGO; st.target = (int)t;
        } else {
            st.var = body[p]-'A'; p++; skipsp(p, body);
            if (p < body.size() && body[p]=='+') {
                p++; skipsp(p, body);
                long long v = 0; while (p < body.size() && isdigit((unsigned char)body[p])) { v = v*10 + (body[p]-'0'); p++; }
                st.kind = ADD; st.num = v;
            } else {
                st.kind = OUT;
            }
        }
        prog[(int)ln] = st;
    }

    if (prog.empty()) { cout << -1 << "\n"; return 0; }

    vector<int> lns;
    lns.reserve(prog.size());
    for (auto& kv : prog) lns.push_back(kv.first);
    map<int,int> nextLine;
    for (size_t k = 0; k + 1 < lns.size(); ++k) nextLine[lns[k]] = lns[k+1];

    const long long CAP = 10000;
    const long long BOUND = 30000000LL;
    vector<long long> val(26, 0);

    long long count = 0;
    int cur = lns.front();
    bool ended = false;

    while (true) {
        auto it = prog.find(cur);
        if (it == prog.end()) break;
        const Stmt& st = it->second;
        count++;
        if (count > BOUND) break;

        if (st.kind == ENDS) { ended = true; break; }
        else if (st.kind == ADD) {
            val[st.var] = min(val[st.var] + st.num, CAP);
            auto nx = nextLine.find(cur);
            if (nx == nextLine.end()) break;
            cur = nx->second;
        } else if (st.kind == OUT) {
            auto nx = nextLine.find(cur);
            if (nx == nextLine.end()) break;
            cur = nx->second;
        } else if (st.kind == GOTO) {
            cur = st.target;
        } else {
            if (val[st.var] == st.num) cur = st.target;
            else {
                auto nx = nextLine.find(cur);
                if (nx == nextLine.end()) break;
                cur = nx->second;
            }
        }
    }

    cout << (ended ? count : -1) << "\n";
    return 0;
}
