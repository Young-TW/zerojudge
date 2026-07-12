#include <cstdio>

int main() {
    const int BUF = 1 << 16;
    char inbuf[BUF];
    char outbuf[BUF];
    int outpos = 0;
    
    int spaceCount = 0;
    bool done = false;
    
    while (!done) {
        size_t n = fread(inbuf, 1, BUF, stdin);
        if (n == 0) break;
        
        for (size_t i = 0; i < n; i++) {
            char c = inbuf[i];
            if (c == ' ') {
                spaceCount++;
            } else if (c == '\n' || c == '\r') {
                done = true;
                break;
            } else {
                if (spaceCount % 2 == 1) {
                    outbuf[outpos++] = ' ';
                    if (outpos == BUF) { fwrite(outbuf, 1, outpos, stdout); outpos = 0; }
                }
                spaceCount = 0;
                outbuf[outpos++] = c;
                if (outpos == BUF) { fwrite(outbuf, 1, outpos, stdout); outpos = 0; }
            }
        }
    }
    
    if (spaceCount % 2 == 1) {
        outbuf[outpos++] = ' ';
        if (outpos == BUF) { fwrite(outbuf, 1, outpos, stdout); outpos = 0; }
    }
    
    outbuf[outpos++] = '\n';
    fwrite(outbuf, 1, outpos, stdout);
    
    return 0;
}
