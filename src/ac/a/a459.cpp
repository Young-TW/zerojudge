#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <stack>

int main() {
    // Read entire input
    std::string src;
    {
        char buf[1 << 16];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), stdin)) > 0) {
            src.append(buf, n);
        }
    }

    // Tokenize. Tokens may be separated by whitespace but some tokens contain
    // internal spaces ("CHAOS CHAOS!", "I WANNA CHAOS!"). Use exact matching.
    // Known tokens:
    //   (>OwO)>u~!!!(/OwO)/nya~!!!   Brain[Ptr]--
    //   (>OwO)>u~!!(/OwO)/nya~!!     Ptr--
    //   (>OwO)>u~!(/OwO)/nya~!       Brain[Ptr]++
    //   (>OwO)>u~(/OwO)/nya~         Ptr++
    //   CHAOS CHAOS!                 while{
    //   I WANNA CHAOS!               }
    //   Let's\(OwO)/nya~             putchar
    //
    // Strategy: scan char by char. Skip whitespace. Then try to match each
    // known token by its first character for speed.

    static const char* T_DEC_VAL = "(>OwO)>u~!!!(/OwO)/nya~!!!";
    static const char* T_DEC_PTR = "(>OwO)>u~!!(/OwO)/nya~!!";
    static const char* T_INC_VAL = "(>OwO)>u~!(/OwO)/nya~!";
    static const char* T_INC_PTR = "(>OwO)>u~(/OwO)/nya~";
    static const char* T_LOOP    = "CHAOS CHAOS!";
    static const char* T_ENDLP   = "I WANNA CHAOS!";
    static const char* T_PUT     = "Let's\\(OwO)/nya~";

    std::vector<char> prog;   // opcodes
    enum { OP_INC_PTR, OP_DEC_PTR, OP_INC_VAL, OP_DEC_VAL, OP_OUT, OP_JMPZ, OP_JMPNZ };

    size_t i = 0;
    size_t len = src.size();

    auto startsWith = [&](const char* tok, size_t pos) -> bool {
        size_t k = 0;
        while (tok[k] != '\0') {
            if (pos + k >= len || src[pos + k] != tok[k]) return false;
            k++;
        }
        return true;
    };

    while (i < len) {
        char c = src[i];
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' || c == '\v') {
            i++;
            continue;
        }
        // Dispatch by first char
        if (c == '(') {
            if (startsWith(T_DEC_VAL, i)) {
                prog.push_back(OP_DEC_VAL);
                i += strlen(T_DEC_VAL);
            } else if (startsWith(T_DEC_PTR, i)) {
                prog.push_back(OP_DEC_PTR);
                i += strlen(T_DEC_PTR);
            } else if (startsWith(T_INC_VAL, i)) {
                prog.push_back(OP_INC_VAL);
                i += strlen(T_INC_VAL);
            } else if (startsWith(T_INC_PTR, i)) {
                prog.push_back(OP_INC_PTR);
                i += strlen(T_INC_PTR);
            } else {
                // unknown, skip one char to avoid infinite loop
                i++;
            }
        } else if (c == 'C') {
            if (startsWith(T_LOOP, i)) {
                prog.push_back(OP_JMPZ);
                i += strlen(T_LOOP);
            } else {
                i++;
            }
        } else if (c == 'I') {
            if (startsWith(T_ENDLP, i)) {
                prog.push_back(OP_JMPNZ);
                i += strlen(T_ENDLP);
            } else {
                i++;
            }
        } else if (c == 'L') {
            if (startsWith(T_PUT, i)) {
                prog.push_back(OP_OUT);
                i += strlen(T_PUT);
            } else {
                i++;
            }
        } else {
            // Unknown character, skip
            i++;
        }
    }

    // Precompute bracket jumps
    size_t m = prog.size();
    std::vector<size_t> jump(m, 0);
    {
        std::stack<size_t> st;
        for (size_t k = 0; k < m; k++) {
            if (prog[k] == OP_JMPZ) {
                st.push(k);
            } else if (prog[k] == OP_JMPNZ) {
                if (!st.empty()) {
                    size_t open = st.top();
                    st.pop();
                    jump[open] = k;
                    jump[k] = open;
                }
            }
        }
    }

    // Execute
    static unsigned char brain[240];
    memset(brain, 0, sizeof(brain));
    int ptr = 0;
    size_t pc = 0;

    // Use a large output buffer
    std::string out;
    out.reserve(1 << 20);

    while (pc < m) {
        switch (prog[pc]) {
            case OP_INC_PTR: ptr++; if (ptr >= 240) ptr = 239; pc++; break;
            case OP_DEC_PTR: ptr--; if (ptr < 0) ptr = 0; pc++; break;
            case OP_INC_VAL: brain[ptr]++; pc++; break;
            case OP_DEC_VAL: brain[ptr]--; pc++; break;
            case OP_OUT:    out.push_back((char)brain[ptr]); pc++; break;
            case OP_JMPZ:
                if (brain[ptr] == 0) pc = jump[pc] + 1;
                else pc++;
                break;
            case OP_JMPNZ:
                if (brain[ptr] != 0) pc = jump[pc] + 1;
                else pc++;
                break;
        }
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
