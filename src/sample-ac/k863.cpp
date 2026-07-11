#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    map<string, int> era_to_year = {
        {"ShunZhi", 1644},
        {"KangXi", 1662},
        {"YongZheng", 1723},
        {"QianLong", 1736},
        {"JiaQing", 1796},
        {"DaoGuang", 1821},
        {"XianFeng", 1851},
        {"TongZhi", 1862},
        {"GuangXu", 1875},
        {"XuanTong", 1909}
    };
    
    string era;
    int year;
    while (cin >> era >> year) {
        if (era_to_year.count(era)) {
            cout << era_to_year[era] + year - 1 << "\n";
        }
    }
    
    return 0;
}
