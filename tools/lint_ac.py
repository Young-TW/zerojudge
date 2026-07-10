#!/usr/bin/env python3
"""掃 src/ac/*.cpp，找出 subagent 不該碰的題目。

只做兩個檢查（誤報率低）：
1. 圖片題：problem.md 含有 <img 或 markdown ![...](...)，subagent 看不到圖
2. 沒讀輸入：程式碼沒有 cin/getline/scanf 等 I/O，純 print 風格

不會自動 reject，只是輸出清單給人 review。
"""
import os, re, sys, json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent  # repo 根目錄（本檔在 tools/）
SRC_AC = ROOT / "src" / "ac"
PROBLEMS = ROOT / "problems"

HAS_INPUT_RE = re.compile(r"\b(cin|getline|scanf|fread|getchar|read\()")
IMG_RE = re.compile(r"<img|\!\[[^]]*\]\(")


def has_image(pid: str) -> bool:
    md = PROBLEMS / pid / "problem.md"
    if not md.exists():
        return False
    return bool(IMG_RE.search(md.read_text(encoding="utf-8")))


def no_input(path: Path) -> bool:
    return not HAS_INPUT_RE.search(path.read_text(encoding="utf-8"))


def main():
    if "--pre-commit" in sys.argv:
        run_pre_commit()
        return

    files = sorted(SRC_AC.rglob("*.cpp"))
    img_ids, no_in_ids = [], []
    for f in files:
        pid = f.stem
        if has_image(pid):
            img_ids.append((pid, str(f.relative_to(ROOT))))
        if no_input(f):
            no_in_ids.append((pid, str(f.relative_to(ROOT))))

    print(f"掃 {len(files)} 個檔\n")
    print(f"=== 圖片題 ({len(img_ids)} 個)，subagent 應跳過 ===")
    for pid, p in img_ids:
        print(f"  {pid:8s}  {p}")
    print(f"\n=== 沒讀輸入 ({len(no_in_ids)} 個)，可疑 ===")
    for pid, p in no_in_ids:
        print(f"  {pid:8s}  {p}")


def run_pre_commit():
    """Hook mode：檢查 staged 的 src/ac/*.cpp，圖片題 exit 1 擋下 commit。

    只擋「新增」(A) 跟「修改」(M)：
    - A (新增)：圖片題 subagent 看不到，不該從無到有生出來
    - M (修改)：圖片題 OJ AC 解不該被 subagent 改

    不擋 D (刪除) / R (改名)：搬走是對的（例如回 src/doing/）
    """
    import subprocess
    try:
        staged = subprocess.run(
            ["git", "diff", "--cached", "--name-status"],
            capture_output=True, text=True, check=True, cwd=ROOT,
        ).stdout.splitlines()
    except subprocess.CalledProcessError:
        sys.exit(1)

    blocked = []
    warned = []
    for line in staged:
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        status, path = parts[0], parts[-1]
        if status in ("D",):
            continue
        m = re.match(r"src/ac/[^/]+/([a-z]\d+)\.cpp$", path)
        if not m:
            continue
        pid = m.group(1)
        cpp = ROOT / path
        if has_image(pid):
            blocked.append((pid, path, f"圖片題 {status}（problem.md 有 <img / ![]()），subagent 看不到圖，不應自動碰"))
        if no_input(cpp):
            warned.append((pid, path, "沒讀輸入"))

    if blocked:
        print("=" * 50, file=sys.stderr)
        print("lint_ac.py 擋下這次 commit：", file=sys.stderr)
        print("=" * 50, file=sys.stderr)
        for pid, path, reason in blocked:
            print(f"  {pid}  ({path})", file=sys.stderr)
            print(f"    原因：{reason}", file=sys.stderr)
            print(f"    解法：git reset HEAD {path}，然後手動處理或跳過這題", file=sys.stderr)
            print(f"          或 git commit --no-verify 強制跳過 hook", file=sys.stderr)
        print("=" * 50, file=sys.stderr)
        sys.exit(1)

    if warned:
        print("lint_ac.py 警告（不擋 commit）：", file=sys.stderr)
        for pid, path, reason in warned:
            print(f"  {pid}  ({path}): {reason}", file=sys.stderr)

    sys.exit(0)


if __name__ == "__main__":
    main()
