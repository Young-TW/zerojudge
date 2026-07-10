#!/usr/bin/env bash
# 對拍（stress test）：主解 vs 暴力參考解，用隨機測資找不一致。
#
# 用法：
#   ./stress.sh a021            # 對拍 1000 輪（預設）
#   ./stress.sh -n 300 a021     # 指定輪數
#
# 每題需要（放在 problems/<id>/）：
#   gen.py       測資產生器：./gen.py <seed> 印一組輸入到 stdout（seed 保證可重現）
#   brute.cpp    暴力參考解（或 brute.py，用 python3 跑）
#
# 主解搜尋順序同 run.sh：src/ac → src/sample-ac → src/doing → src/wa → src/na → src 其餘。
# 比對時忽略每行行尾空白與檔尾多餘空行（與 run.sh 一致）。
# 撞到不一致：存 problems/<id>/counter.in / counter.main / counter.brute 後停止，exit 1。
set -u

ROOT="$(cd "$(dirname "$0")" && pwd)"
PROB="$ROOT/problems"
CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++17 -O2 -I$ROOT}"
TIMEOUT="${TIMEOUT:-5}"
if ! command -v timeout >/dev/null 2>&1; then
  timeout() {
    perl -e 'alarm shift; exec @ARGV' "$@"
  }
fi
for _r in "${TMPDIR:-}" /dev/shm /tmp; do
  [ -n "$_r" ] && [ -d "$_r" ] && [ -w "$_r" ] && { RAMBASE="$_r"; break; }
done
TMP="$(mktemp -d "${RAMBASE:-/tmp}/zjstress.XXXXXX")"
trap 'rm -rf "$TMP"' EXIT

if [ -t 1 ]; then
  G=$'\e[32m'; R=$'\e[31m'; Y=$'\e[33m'; B=$'\e[1m'; N=$'\e[0m'
else
  G=; R=; Y=; B=; N=
fi

ROUNDS=1000
if [ "${1:-}" = "-n" ]; then ROUNDS="$2"; shift 2; fi
if [ "$#" -ne 1 ]; then
  echo "用法: $0 [-n 輪數] <題號>" >&2; exit 2
fi
ID="$1"
DIR="$PROB/$ID"

find_solution() {
  local id="$1" f
  for d in src/ac src/sample-ac src/doing src/wa src/na; do
    f=$(find "$ROOT/$d" -name "$id.cpp" 2>/dev/null | head -1)
    [ -n "$f" ] && { echo "$f"; return; }
  done
  find "$ROOT/src" -name "$id.cpp" 2>/dev/null | head -1
}

SOL=$(find_solution "$ID")
[ -z "$SOL" ] && { echo "${R}找不到主解 $ID.cpp${N}" >&2; exit 2; }
[ -x "$DIR/gen.py" ] || [ -f "$DIR/gen.py" ] || { echo "${R}缺 $DIR/gen.py${N}" >&2; exit 2; }

# 暴力解：brute.cpp 優先，否則 brute.py
BRUTE_RUN=
if [ -f "$DIR/brute.cpp" ]; then
  $CXX $CXXFLAGS "$DIR/brute.cpp" -o "$TMP/brute" 2>"$TMP/brute.cerr" \
    || { echo "${R}brute.cpp 編譯失敗${N}"; sed 's/^/  /' "$TMP/brute.cerr" | head -20; exit 2; }
  BRUTE_RUN="$TMP/brute"
elif [ -f "$DIR/brute.py" ]; then
  BRUTE_RUN="python3 $DIR/brute.py"
else
  echo "${R}缺 $DIR/brute.cpp 或 brute.py${N}" >&2; exit 2
fi

$CXX $CXXFLAGS "$SOL" -o "$TMP/main" 2>"$TMP/main.cerr" \
  || { echo "${R}主解編譯失敗 (${SOL#$ROOT/})${N}"; sed 's/^/  /' "$TMP/main.cerr" | head -20; exit 2; }

echo "${B}對拍 $ID${N}  主解=${SOL#$ROOT/}  暴力=${BRUTE_RUN##*/}  輪數=$ROUNDS"

for seed in $(seq 1 "$ROUNDS"); do
  python3 "$DIR/gen.py" "$seed" > "$TMP/in" \
    || { echo "${R}gen.py 失敗 (seed=$seed)${N}"; exit 2; }

  main_out=$(timeout "$TIMEOUT" "$TMP/main" < "$TMP/in" 2>/dev/null | sed 's/[[:space:]]*$//')
  main_rc=$?
  brute_out=$(timeout "$TIMEOUT" $BRUTE_RUN < "$TMP/in" 2>/dev/null | sed 's/[[:space:]]*$//')
  brute_rc=$?

  if [ "$brute_rc" -ne 0 ]; then
    echo "${Y}暴力解在 seed=$seed 失敗 (rc=$brute_rc$([ $brute_rc -eq 124 ] && echo '，逾時'))，暴力解本身有問題${N}"
    cp "$TMP/in" "$DIR/counter.in"; exit 2
  fi
  if [ "$main_rc" -ne 0 ] || [ "$main_out" != "$brute_out" ]; then
    echo "${R}${B}[MISMATCH]${N} seed=$seed$([ $main_rc -eq 124 ] && echo ' （主解逾時）')"
    cp "$TMP/in" "$DIR/counter.in"
    printf '%s\n' "$main_out"  > "$DIR/counter.main"
    printf '%s\n' "$brute_out" > "$DIR/counter.brute"
    echo "  反例已存: problems/$ID/counter.in / counter.main / counter.brute"
    echo "  ${B}--- 輸入 ---${N}";      sed 's/^/  /' "$TMP/in" | head -20
    echo "  ${B}--- 主解輸出 ---${N}";  printf '%s\n' "$main_out"  | sed 's/^/  /' | head -20
    echo "  ${B}--- 暴力輸出 ---${N}";  printf '%s\n' "$brute_out" | sed 's/^/  /' | head -20
    exit 1
  fi
  if [ $((seed % 100)) -eq 0 ]; then echo "  ...$seed/$ROUNDS OK"; fi
done

echo "${G}[PASS]${N} $ID  $ROUNDS 輪對拍一致"
