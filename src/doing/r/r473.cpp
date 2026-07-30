#include <iostream>
#include <string>
#include <set>
#include <queue>

using namespace std;

string rotY(const string& s) {
    string t = s;
    t[0] = s[0];
    t[1] = s[4];
    t[2] = s[1];
    t[3] = s[2];
    t[4] = s[3];
    t[5] = s[5];
    return t;
}

string rotX(const string& s) {
    string t = s;
    t[0] = s[3];
    t[1] = s[0];
    t[2] = s[2];
    t[3] = s[5];
    t[4] = s[4];
    t[5] = s[1];
    return t;
}

string rotZ(const string& s) {
    string t = s;
    t[0] = s[4];
    t[1] = s[1];
    t[2] = s[0];
    t[3] = s[3];
    t[4] = s[5];
    t[5] = s[2];
    return t;
}

bool check(const string& s1, const string& s2) {
    set<string> vis;
    queue<string> q;
    q.push(s1);
    vis.insert(s1);
    while(!q.empty()) {
        string u = q.front(); 
        q.pop();
        if(u == s2) return true;
        
        string v1 = rotY(u);
        string v2 = rotX(u);
        string v3 = rotZ(u);
        
        if(vis.find(v1) == vis.end()) { 
            vis.insert(v1); 
            q.push(v1); 
        }
        if(vis.find(v2) == vis.end()) { 
            vis.insert(v2); 
            q.push(v2); 
        }
        if(vis.find(v3) == vis.end()) { 
            vis.insert(v3); 
            q.push(v3); 
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    while(cin >> s) {
        if(s.length() < 12) continue;
        string s1 = s.substr(0, 6);
        string s2 = s.substr(6, 6);
        if(check(s1, s2)) {
            cout << "TRUE\n";
        } else {
            cout << "FALSE\n";
        }
    }
    return 0;
}
