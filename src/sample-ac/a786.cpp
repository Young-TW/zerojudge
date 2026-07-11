#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        
        if (line == "[L3X1K0N]") {
            std::unordered_map<std::string, std::string> dict;
            while (std::getline(std::cin, line)) {
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }
                if (line == "[1337]") break;
                if (line.empty()) continue;
                
                size_t pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string key = line.substr(0, pos);
                    std::string val = line.substr(pos + 1);
                    dict[key] = val;
                }
            }
            
            while (std::getline(std::cin, line)) {
                if (!line.empty() && line.back() == '\r') {
                    line.pop_back();
                }
                if (line == "[3ND]") break;
                
                std::istringstream iss(line);
                std::string word;
                bool first = true;
                while (iss >> word) {
                    if (!first) {
                        std::cout << " ";
                    }
                    first = false;
                    
                    auto it = dict.find(word);
                    if (it != dict.end()) {
                        std::cout << it->second;
                    } else {
                        std::cout << word;
                    }
                }
                std::cout << "\n";
            }
        }
    }
    
    return 0;
}
