#include <bits/stdc++.h>
using namespace std;

int idx(char c){ return c - 'A'; }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const string orderStr = "DABCEFGHIJKLMNOPQRSTUVWXY Z";
    // build priority: D=0, A=1, B=2, C=3, E=4, F=5, ...
    vector<int> priority(26, 1000);
    vector<char> order = {'D','A','B','C','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    for(int i=0;i<(int)order.size();++i) priority[idx(order[i])] = i;

    int N,M;
    while ( (cin>>N>>M) ){
        // initialise
        vector<int> gender(26,-1); // -1 unknown, 0 male, 1 female
        vector<int> gen(26, INT_MAX);
        vector<vector<pair<int,int>>> genAdj(26); // (to, weight)  gen[u]-gen[v]=weight
        vector<vector<int>> ageAdj(26);
        vector<int> ageIndeg(26,0);
        bool bad = false;

        auto addGender = [&](int p,int g){
            if(gender[p]==-1) gender[p]=g;
            else if(gender[p]!=g) bad=true;
        };

        auto addGenEdge = [&](int u,int v,int w){
            genAdj[u].push_back({v,w});
            genAdj[v].push_back({u,-w});
        };

        auto trim = [&](string &s){
            while(!s.empty() && isspace(s.back())) s.pop_back();
            while(!s.empty() && isspace(s.front())) s.erase(s.begin());
        };

        for(int i=0;i<M && !bad;i++){
            char c1,c2;
            cin>>c1>>c2;
            string rel;
            getline(cin,rel);
            trim(rel);
            // lower case for easier comparison
            string low;
            for(char ch:rel) low+=tolower(ch);
            int a = idx(c1), b = idx(c2);
            int delta = 0; // gen[a]-gen[b]
            bool sameGen = false;
            bool olderAB = false; // a older than b
            bool youngerAB = false; // a younger than b
            // map relation
            if(low=="father"){ delta=1; addGender(a,0); }
            else if(low=="mother"){ delta=1; addGender(a,1); }
            else if(low=="parent"){ delta=1; }
            else if(low=="son"){ delta=-1; addGender(a,0); }
            else if(low=="daughter"){ delta=-1; addGender(a,1); }
            else if(low=="child"){ delta=-1; }
            else if(low=="grandpa"){ delta=2; addGender(a,0); }
            else if(low=="grandma"){ delta=2; addGender(a,1); }
            else if(low=="grandparent"){ delta=2; }
            else if(low=="grandson"){ delta=-2; addGender(a,0); }
            else if(low=="granddaughter"){ delta=-2; addGender(a,1); }
            else if(low=="grandchild"){ delta=-2; }
            else if(low=="older brother"){ delta=0; sameGen=true; addGender(a,0); olderAB=true; }
            else if(low=="older sister"){ delta=0; sameGen=true; addGender(a,1); olderAB=true; }
            else if(low=="younger brother"){ delta=0; sameGen=true; addGender(a,0); youngerAB=true; }
            else if(low=="younger sister"){ delta=0; sameGen=true; addGender(a,1); youngerAB=true; }
            else if(low=="brother"){ delta=0; sameGen=true; addGender(a,0); }
            else if(low=="sister"){ delta=0; sameGen=true; addGender(a,1); }
            else if(low=="cousin"){ delta=0; sameGen=true; }
            else if(low=="uncle"){ delta=1; sameGen=true; addGender(a,0); }
            else if(low=="aunt"){ delta=1; sameGen=true; addGender(a,1); }
            else if(low=="nephew"){ delta=-1; sameGen=true; addGender(a,0); }
            else if(low=="niece"){ delta=-1; sameGen=true; addGender(a,1); }
            else if(low=="husband"){ delta=0; sameGen=true; addGender(a,0); }
            else if(low=="wife"){ delta=0; sameGen=true; addGender(a,1); }
            // synonym handling
            else if(low=="big brother"){ delta=0; sameGen=true; addGender(a,0); olderAB=true; }
            else if(low=="big sister"){ delta=0; sameGen=true; addGender(a,1); olderAB=true; }
            else { // unknown relation -> treat as error
                bad = true;
            }

            // add generation constraint
            addGenEdge(a,b,delta);
            // age constraint
            if(olderAB) ageAdj[a].push_back(b), ++ageIndeg[b];
            if(youngerAB) ageAdj[b].push_back(a), ++ageIndeg[a];
        }

        // gender conflict already flagged

        // ---------- propagate generations ----------
        for(int i=0;i<N && !bad;i++){
            if(gen[i]==INT_MAX){
                gen[i]=0;
                queue<int> q;
                q.push(i);
                while(!q.empty() && !bad){
                    int u=q.front(); q.pop();
                    for(auto [v,w]: genAdj[u]){
                        int expect = gen[u]-w;
                        if(gen[v]==INT_MAX){
                            gen[v]=expect;
                            q.push(v);
                        }else if(gen[v]!=expect){
                            bad=true; break;
                        }
                    }
                }
            }
        }

        // ---------- check age edges same generation ----------
        if(!bad){
            for(int u=0;u<N;u++){
                for(int v: ageAdj[u]){
                    if(gen[u]!=gen[v]){ bad=true; break; }
                }
                if(bad) break;
            }
        }

        // ---------- topological sort per generation ----------
        vector<string> outputLines;
        if(!bad){
            // group by generation value
            map<int, vector<int>, greater<int>> groups; // descending gen
            for(int i=0;i<N;i++) groups[gen[i]].push_back(i);

            for(auto &kv: groups){
                vector<int> nodes = kv.second;
                // build indegree copy for this group
                unordered_map<int,int> indeg;
                for(int u: nodes) indeg[u]=0;
                for(int u: nodes){
                    for(int v: ageAdj[u]){
                        if(indeg.find(v)!=indeg.end()){
                            indeg[v]++;
                        }
                    }
                }
                // adjacency within group
                unordered_map<int, vector<int>> adj;
                for(int u: nodes){
                    for(int v: ageAdj[u]){
                        if(indeg.find(v)!=indeg.end()){
                            adj[u].push_back(v);
                        }
                    }
                }

                vector<int> order; order.reserve(nodes.size());
                while(!indeg.empty()){
                    // collect zero indegree nodes
                    vector<int> zero;
                    for(auto &p: indeg) if(p.second==0) zero.push_back(p.first);
                    if(zero.empty()){ bad=true; break; }

                    // among zero, prefer those having outgoing edges
                    vector<int> candidates;
                    for(int x: zero){
                        if(!adj[x].empty()) candidates.push_back(x);
                    }
                    int chosen = -1;
                    if(!candidates.empty()){
                        // pick with smallest priority (older)
                        chosen = *min_element(candidates.begin(), candidates.end(),
                                              [&](int a,int b){ return priority[a] < priority[b]; });
                    }else{
                        chosen = *min_element(zero.begin(), zero.end(),
                                              [&](int a,int b){ return priority[a] < priority[b]; });
                    }
                    order.push_back(chosen);
                    // remove chosen
                    for(int nb: adj[chosen]){
                        indeg[nb]--;
                    }
                    indeg.erase(chosen);
                }
                if(bad) break;
                // build line string
                string line;
                for(size_t i=0;i<order.size();++i){
                    if(i) line.push_back(' ');
                    line.push_back(char('A'+order[i]));
                }
                outputLines.push_back(line);
            }
        }

        if(bad){
            cout<<"DD被整了!\n";
        }else{
            for(string &ln: outputLines) cout<<ln<<"\n";
        }
    }
    return 0;
}
