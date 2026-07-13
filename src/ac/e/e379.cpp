#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string digitLower[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
    string digitUpper[] = {"零", "壹", "貳", "參", "肆", "伍", "陸", "柒", "捌", "玖"};
    string unitLower[] = {"", "十", "百", "千"};
    string unitUpper[] = {"", "拾", "佰", "仟"};
    string bigUnits[] = {"", "萬", "億", "兆", "京", "垓", "秭", "穰", "溝", "澗", "正", "載"};
    
    int T;
    while (cin >> T) {
        string N;
        if (!(cin >> N)) break;
        
        string* digits = (T == 0) ? digitLower : digitUpper;
        string* units = (T == 0) ? unitLower : unitUpper;
        
        int start = 0;
        while (start < (int)N.size() - 1 && N[start] == '0') start++;
        string num = N.substr(start);
        
        if (num == "0") {
            cout << "零" << "\n";
            continue;
        }
        
        vector<string> groups;
        int len = num.size();
        for (int i = len; i > 0; i -= 4) {
            int s = max(0, i - 4);
            groups.push_back(num.substr(s, i - s));
        }
        
        string result = "";
        bool needZero = false;
        
        for (int g = (int)groups.size() - 1; g >= 0; g--) {
            string grp = groups[g];
            while (grp.size() < 4) grp = "0" + grp;
            
            bool allZero = true;
            for (int i = 0; i < 4; i++) {
                if (grp[i] != '0') { allZero = false; break; }
            }
            
            if (allZero) {
                needZero = true;
                continue;
            }
            
            string groupStr = "";
            bool lastWasZero = false;
            bool started = false;
            for (int i = 0; i < 4; i++) {
                int d = grp[i] - '0';
                if (d == 0) {
                    if (started) lastWasZero = true;
                } else {
                    if (lastWasZero) {
                        groupStr += "零";
                        lastWasZero = false;
                    }
                    groupStr += digits[d] + units[3 - i];
                    started = true;
                }
            }
            
            if (!result.empty()) {
                bool leadingZero = (grp[0] == '0');
                if (leadingZero || needZero) {
                    result += "零";
                }
            }
            
            result += groupStr;
            if (g > 0) result += bigUnits[g];
            needZero = false;
        }
        
        cout << result << "\n";
    }
    return 0;
}
