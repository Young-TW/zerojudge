// ZeroJudge a198 - NOI2005 智慧珠游戏
// 三角形盤 (第 i 列有 i 格, i=1..10, 共 55 格)，12 個零件 A..L 珠數合計恰 55。
// 盤上已預放若干零件，需放入其餘零件 (可旋轉 0/90/180/270 + 翻轉)，填滿全盤。
// 保證最多一組解；無解輸出 "No solution"。
//
// 演算法：exact-cover 回溯 + MRV(最少候選)剪枝 + 位元遮罩。
//   每一步挑「候選擺法最少的空格」分支，若某空格 0 候選立即回溯。
//   如此不論「有解」或「無解」皆能快速判定 (避免無解稀疏盤的組合爆炸)。

#include <bits/stdc++.h>
using namespace std;

// 12 個零件的基準形狀，(row,col) 偏移；row 向下為正、col 向右為正。
static const vector<vector<pair<int,int>>> BASE = {
    {{0,0},{0,1},{1,0}},                 // A
    {{0,0},{0,1},{0,2},{0,3}},           // B
    {{0,0},{0,1},{0,2},{1,0}},           // C
    {{0,0},{0,1},{1,0},{1,1}},           // D
    {{0,0},{1,0},{2,0},{2,1},{2,2}},     // E
    {{0,0},{0,1},{0,2},{0,3},{1,1}},     // F
    {{0,0},{0,1},{0,2},{1,0},{1,2}},     // G
    {{0,0},{0,1},{0,2},{1,0},{1,1}},     // H
    {{0,0},{0,1},{0,2},{1,2},{1,3}},     // I
    {{0,1},{1,0},{1,1},{1,2},{2,1}},     // J
    {{0,0},{1,0},{1,1},{2,1},{2,2}},     // K
    {{0,0},{0,1},{0,2},{0,3},{1,0}},     // L
};

// 每個零件的所有相異朝向 (正規化後的偏移集合)。
static vector<vector<vector<pair<int,int>>>> orient(12);

static vector<pair<int,int>> normalize(vector<pair<int,int>> v){
    int mr=INT_MAX, mc=INT_MAX;
    for(auto&p:v){ mr=min(mr,p.first); mc=min(mc,p.second); }
    for(auto&p:v){ p.first-=mr; p.second-=mc; }
    sort(v.begin(), v.end());
    return v;
}

static void buildOrients(){
    for(int pi=0; pi<12; ++pi){
        set<vector<pair<int,int>>> seen;
        for(int flip=0; flip<2; ++flip){
            vector<pair<int,int>> f = BASE[pi];
            if(flip) for(auto&p:f) p.second = -p.second;      // 水平翻轉
            for(int rot=0; rot<4; ++rot){
                vector<pair<int,int>> g = f;
                for(int k=0;k<rot;++k)                        // 旋轉 90°: (r,c)->(c,-r)
                    for(auto&p:g){ int nr=p.second, nc=-p.first; p.first=nr; p.second=nc; }
                auto n = normalize(g);
                if(seen.insert(n).second) orient[pi].push_back(n);
            }
        }
    }
}

// 三角形格子編號 idx(r,c)=r*(r+1)/2+c , r=0..9, c=0..r , 共 55。
static inline int cellIdx(int r,int c){ return r*(r+1)/2 + c; }
static const uint64_t FULL = ((uint64_t)1<<55) - 1;

static int idxR[55], idxC[55];          // idx -> (r,c)

struct Cand { int pid; uint64_t mask; }; // 一種擺法：使用零件 pid、覆蓋的格子遮罩
static vector<Cand> cellCand[55];        // cellCand[cell] = 覆蓋該格的所有擺法

static int board[10][10];                 // 輸出用；-1=空
static uint64_t occ;                      // 已佔用遮罩
static int usedMask;                      // 已使用零件 (12 bit)

static void applyMask(uint64_t m,int pid){
    while(m){ int b=__builtin_ctzll(m); m&=m-1; board[idxR[b]][idxC[b]]=pid; }
}

static bool solve(){
    if(occ == FULL) return true;
    // MRV：挑候選數最少的空格
    int best=-1, bestCnt=INT_MAX;
    for(int cell=0; cell<55; ++cell){
        if((occ>>cell)&1) continue;
        int cnt=0;
        for(const Cand &cd : cellCand[cell]){
            if((usedMask>>cd.pid)&1) continue;
            if(cd.mask & occ) continue;
            if(++cnt >= bestCnt) break;      // 已不可能更小
        }
        if(cnt==0) return false;             // 死格 -> 剪枝
        if(cnt < bestCnt){ bestCnt=cnt; best=cell; if(cnt==1) break; }
    }
    for(const Cand &cd : cellCand[best]){
        if((usedMask>>cd.pid)&1) continue;
        if(cd.mask & occ) continue;
        occ |= cd.mask; usedMask |= (1<<cd.pid);
        applyMask(cd.mask, cd.pid);
        if(solve()) return true;
        occ &= ~cd.mask; usedMask &= ~(1<<cd.pid);
        applyMask(cd.mask, -1);              // 還原為空 (-1)
    }
    return false;
}

int main(){
    buildOrients();
    for(int r=0;r<10;++r) for(int c=0;c<=r;++c){ int id=cellIdx(r,c); idxR[id]=r; idxC[id]=c; }

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 讀入所有行 (去尾 CR/LF)；以每 10 行為一個盤面，讀到 EOF (可含多筆測資)。
    vector<string> lines;
    string ln;
    while(getline(cin, ln)){
        while(!ln.empty() && (ln.back()=='\r' || ln.back()=='\n')) ln.pop_back();
        lines.push_back(ln);
    }

    size_t idx=0;
    while(idx < lines.size()){
        while(idx < lines.size() && lines[idx].empty()) ++idx; // 跳過盤面間空行
        if(idx + 10 > lines.size()) break;

        // 讀盤面
        int pre[10][10];
        int preUsed=0;
        for(int r=0;r<10;++r) for(int c=0;c<10;++c) pre[r][c]=-1;
        occ=0;
        for(int r=0;r<10;++r){
            const string &t = lines[idx+r];
            for(int c=0;c<=r;++c){
                char ch = (c < (int)t.size()) ? t[c] : '.';
                if(ch>='A' && ch<='L'){
                    pre[r][c]=ch-'A';
                    preUsed |= (1<<(ch-'A'));
                    occ |= (uint64_t)1 << cellIdx(r,c);
                }
            }
        }
        idx += 10;

        // 建立剩餘零件的所有擺法 (只放到空格上)
        for(int i=0;i<55;++i) cellCand[i].clear();
        uint64_t emptyMask = FULL & ~occ;
        for(int pid=0; pid<12; ++pid){
            if((preUsed>>pid)&1) continue;                 // 已預放
            for(const auto &shp : orient[pid]){
                int maxr=0;
                for(auto&p:shp) maxr=max(maxr,p.first);
                for(int r0=0; r0+maxr<10; ++r0){
                    for(int c0=0; c0<10; ++c0){
                        uint64_t m=0; bool ok=true;
                        for(auto&p:shp){
                            int rr=r0+p.first, cc=c0+p.second;
                            if(rr<0||rr>=10||cc<0||cc>rr){ ok=false; break; }
                            m |= (uint64_t)1 << cellIdx(rr,cc);
                        }
                        if(!ok) continue;
                        if(m & ~emptyMask) continue;        // 不能蓋到非空格
                        Cand cd{pid,m};
                        uint64_t t=m;
                        while(t){ int b=__builtin_ctzll(t); t&=t-1; cellCand[b].push_back(cd); }
                    }
                }
            }
        }

        // 初始化輸出盤 + 求解
        for(int r=0;r<10;++r) for(int c=0;c<=r;++c) board[r][c]=pre[r][c];
        usedMask = preUsed;

        if(solve()){
            for(int r=0;r<10;++r){
                string s;
                for(int c=0;c<=r;++c) s += char('A'+board[r][c]);
                cout << s << "\n";
            }
        } else {
            cout << "No solution\n";
        }
    }
    return 0;
}
