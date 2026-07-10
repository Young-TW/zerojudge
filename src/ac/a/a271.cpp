#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

static bool isBlank(const string &s){
    for(char c : s) if(!isspace((unsigned char)c)) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    if(!getline(cin, line)) return 0;
    {
        istringstream iss(line);
        int T;
        if(!(iss >> T)) return 0;
        while(T--){
            // read params line (skip blank lines)
            string params;
            while(getline(cin, params)){
                if(!isBlank(params)) break;
            }
            istringstream iss(params);
            long long x, y, z, w, n, m;
            iss >> x >> y >> z >> w >> n >> m;

            // read exactly one line as the food sequence (may be empty)
            string foodline;
            getline(cin, foodline);
            vector<int> food;
            {
                istringstream fiss(foodline);
                int f;
                while(fiss >> f) food.push_back(f);
            }

            long long poison = 0;
            bool dead = false;
            for(int f : food){
                // morning: poison effect (poison acquired on previous days)
                m -= poison * n;
                if(m <= 0){ dead = true; break; }
                // evening: eat
                if(f == 1) m += x;          // red
                else if(f == 2) m += y;     // white
                else if(f == 3) m -= z;     // yellow
                else if(f == 4){ m -= w; poison += 1; } // moldy -> poison stacks
                // f == 0 : nothing
                if(m <= 0){ dead = true; break; }
            }

            if(dead) cout << "bye~Rabbit\n";
            else cout << m << "g\n";
        }
    }
    return 0;
}
