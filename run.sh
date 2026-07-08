#!/usr/bin/env bash
# 一鍵編譯並跑 ZeroJudge 範例測資。
#
# 用法：
#   ./run.sh a002            # 跑單一題目的所有範例測資
#   ./run.sh a002 b558 f312  # 跑多個指定題目
#   ./run.sh                 # 跑所有「有解答檔且有範例測資」的題目
#   ./run.sh -v a002         # 失敗時顯示完整 diff（預設只顯示前幾行）
#
# 解答檔搜尋順序：src/ac → src/sample-ac → src/doing → src/wa → src/na → src 其餘。
# 比對時忽略每行行尾空白與檔尾多餘空行（與 ZeroJudge 判定相近）。
set -u

ROOT="$(cd "$(dirname "$0")" && pwd)"
PROB="$ROOT/problems"
CXX="${CXX:-g++}"
CXXFLAGS="${CXXFLAGS:--std=c++17 -O2 -I$ROOT}"
TIMEOUT="${TIMEOUT:-5}"
# 編譯產物與暫存全部丟 RAM（tmpfs），跑完即刪。優先 /dev/shm，否則 $TMPDIR/tmp。
for _r in "${TMPDIR:-}" /dev/shm /tmp; do
  [ -n "$_r" ] && [ -d "$_r" ] && [ -w "$_r" ] && { RAMBASE="$_r"; break; }
done
TMP="$(mktemp -d "${RAMBASE:-/tmp}/zjrun.XXXXXX")"
trap 'rm -rf "$TMP"' EXIT

VERBOSE=0
if [ "${1:-}" = "-v" ]; then VERBOSE=1; shift; fi

if [ -t 1 ]; then
  G=$'\e[32m'; R=$'\e[31m'; Y=$'\e[33m'; B=$'\e[1m'; N=$'\e[0m'
else
  G=; R=; Y=; B=; N=
fi

find_solution() {
  local id="$1" f
  for d in src/ac src/sample-ac src/doing src/wa src/na; do
    f=$(find "$ROOT/$d" -name "$id.cpp" 2>/dev/null | head -1)
    [ -n "$f" ] && { echo "$f"; return; }
  done
  find "$ROOT/src" -name "$id.cpp" 2>/dev/null | head -1
}

# 計數（全域）
TOT_PASS=0 TOT_FAIL=0 TOT_CE=0 TOT_SKIP=0 TOT_PROB=0

run_one() {
  local id="$1"
  local dir="$PROB/$id"
  local sol; sol=$(find_solution "$id")

  if [ -z "$sol" ]; then
    printf "%s[SKIP]%s %-6s 無解答檔\n" "$Y" "$N" "$id"; TOT_SKIP=$((TOT_SKIP+1)); return
  fi
  if [ ! -d "$dir" ] || ! ls "$dir"/*.in >/dev/null 2>&1; then
    printf "%s[SKIP]%s %-6s 無範例測資\n" "$Y" "$N" "$id"; TOT_SKIP=$((TOT_SKIP+1)); return
  fi
  TOT_PROB=$((TOT_PROB+1))

  local bin="$TMP/$id"
  if ! $CXX $CXXFLAGS "$sol" -o "$bin" 2>"$TMP/$id.cerr"; then
    printf "%s[CE]%s   %-6s 編譯失敗 (%s)\n" "$R" "$N" "$id" "${sol#$ROOT/}"
    sed 's/^/      /' "$TMP/$id.cerr" | head -20
    TOT_CE=$((TOT_CE+1)); return
  fi

  local pass=0 fail=0 total=0 inf n exp act
  for inf in "$dir"/*.in; do
    n=$(basename "$inf" .in)
    [ -f "$dir/$n.out" ] || continue
    total=$((total+1))
    exp=$(sed 's/[[:space:]]*$//' "$dir/$n.out")
    act=$(timeout "$TIMEOUT" "$bin" < "$inf" 2>/dev/null | sed 's/[[:space:]]*$//')
    local rc=$?
    if [ "$exp" = "$act" ]; then
      pass=$((pass+1)); TOT_PASS=$((TOT_PASS+1))
    else
      fail=$((fail+1)); TOT_FAIL=$((TOT_FAIL+1))
      if [ "$VERBOSE" = 1 ]; then
        printf "  %s#%s FAIL%s%s\n" "$R" "$n" "$N" "$([ $rc -eq 124 ] && echo ' (逾時)')"
        printf "    --- 期望 ---\n"; printf '%s\n' "$exp" | sed 's/^/    /'
        printf "    --- 實際 ---\n"; printf '%s\n' "$act" | sed 's/^/    /'
      fi
    fi
  done

  if [ "$fail" -eq 0 ]; then
    printf "%s[AC]%s   %-6s %s%d/%d%s\n" "$G" "$N" "$id" "$G" "$pass" "$total" "$N"
  else
    printf "%s[WA]%s   %-6s %s%d/%d%s%s\n" "$R" "$N" "$id" "$R" "$pass" "$total" "$N" \
      "$([ "$VERBOSE" = 0 ] && echo "  （加 -v 看 diff）")"
  fi
}

if [ "$#" -gt 0 ]; then
  ids=("$@")
else
  # 所有有範例測資資料夾的題號
  ids=()
  for d in "$PROB"/*/; do
    id=$(basename "$d"); case "$id" in .*) continue;; esac
    ids+=("$id")
  done
fi

for id in "${ids[@]}"; do run_one "$id"; done

echo "----------------------------------------"
printf "%s題目 %d｜通過測資 %s%d%s｜失敗 %s%d%s｜編譯錯誤 %s%d%s｜略過 %s%d%s%s\n" \
  "$B" "$TOT_PROB" "$G" "$TOT_PASS" "$N" "$R" "$TOT_FAIL" "$N" \
  "$R" "$TOT_CE" "$N" "$Y" "$TOT_SKIP" "$N" "$B$N"

[ "$TOT_FAIL" -eq 0 ] && [ "$TOT_CE" -eq 0 ]
