#!/usr/bin/env bash
# 本地試跑 ZeroJudge 範例測資
# 用法：
#   problems/run.sh <題號>            # 自動在 src/ 找對應 .cpp 編譯後跑該題所有範例
#   problems/run.sh <題號> <來源檔>    # 指定要測的原始碼
# 例：problems/run.sh a002
#
# 比對方式與 ZeroJudge 相近：忽略每行尾端空白與檔案尾端多餘換行。
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROB="${1:?請提供題號，例如 a002}"
DIR="$ROOT/problems/$PROB"
[ -d "$DIR" ] || { echo "找不到題目資料夾：$DIR"; exit 1; }

SRC="${2:-}"
if [ -z "$SRC" ]; then
  SRC="$(find "$ROOT/src" -name "$PROB.cpp" | head -1)"
  [ -n "$SRC" ] || { echo "在 src/ 找不到 $PROB.cpp，請以第二個參數指定原始碼"; exit 1; }
fi
echo "原始碼：$SRC"

BIN="$(mktemp)"
g++ -O2 -std=c++17 "$SRC" -o "$BIN"

# 讀 stdin，輸出正規化結果：CRLF→LF、去每行尾端空白、去尾端空行、不含結尾換行
norm() {
  sed 's/\r$//; s/[[:space:]]*$//' \
  | awk '{a[NR]=$0} END{last=NR; while(last>0 && a[last]=="") last--;
          for(i=1;i<=last;i++) printf "%s%s", a[i], (i<last?"\n":"")}'
}

pass=0; fail=0
shopt -s nullglob
for in in "$DIR"/*.in; do
  n="$(basename "${in%.in}")"
  exp="${in%.in}.out"
  got="$("$BIN" < "$in")"
  if diff -q <(printf '%s' "$got" | norm) \
             <(norm < "$exp") >/dev/null; then
    echo "  範例 $n: AC"; pass=$((pass+1))
  else
    echo "  範例 $n: WA"; fail=$((fail+1))
    echo "  --- 期望 ---"; sed 's/^/    /' "$exp"
    echo "  --- 得到 ---"; printf '%s\n' "$got" | sed 's/^/    /'
  fi
done
rm -f "$BIN"
echo "結果：$pass AC / $fail WA"
[ "$fail" -eq 0 ]
