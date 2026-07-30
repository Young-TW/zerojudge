// c631 記憶力試驗 — 自寫解答
// 內容長度可達 5,000 萬字元，注意記憶體限制。
// 不將整段內容存入記憶體，改用 fseek/fread 直接自輸入檔隨機讀取所需片段。
#include <cstdio>

static int Lq[705], Rq[705];
static char buf[1 << 16];

int main() {
    // 加大 stdout 緩衝，減少系統呼叫（總輸出可達 2000 萬字元）
    static char obuf[1 << 20];
    setvbuf(stdout, obuf, _IOFBF, sizeof(obuf));

    long long N;
    if (scanf("%lld", &N) != 1) return 0;

    // 跳過第一行剩餘字元（\n 或 \r\n），contentStart = 內容第一字元位置
    int c;
    while ((c = getchar()) != EOF && c != '\n') { /* skip */ }
    long contentStart = ftell(stdin);

    // 跳過內容 N 個字元，抵達詢問區塊，讀入所有詢問
    if (fseek(stdin, contentStart + N, SEEK_SET) != 0) return 0;
    int q = 0;
    while (q < 705 && scanf("%d %d", &Lq[q], &Rq[q]) == 2) q++;

    // 依序處理每筆詢問：定位到內容中的 L，讀出 [L,R]
    for (int i = 0; i < q; i++) {
        long off = contentStart + (long)Lq[i] - 1;
        long len = (long)Rq[i] - Lq[i] + 1;
        if (fseek(stdin, off, SEEK_SET) != 0) return 0;
        while (len > 0) {
            size_t want = (size_t)(len < (long)sizeof(buf) ? len : (long)sizeof(buf));
            size_t got = fread(buf, 1, want, stdin);
            if (got == 0) break;
            fwrite(buf, 1, got, stdout);
            len -= (long)got;
        }
        putchar('\n');
    }
    return 0;
}
