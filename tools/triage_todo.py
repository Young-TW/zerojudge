#!/usr/bin/env python3
"""把還沒有解答檔的題目分類，供派工用。

分類（互斥，依此優先序）：
  placeholder  佔位題（標題 Unfinished!）
  stub         敘述幾乎沒有文字（題本在外部 PDF 等），但有範例，題意需從範例推斷
  image        題目文字含圖片，subagent 看不到圖，需人工確認
  normal       純文字題，可直接進自動解題產線

輸出 problems/.todo_placeholder.txt / .todo_image.txt / .todo_normal.txt
並在 stdout 印統計。
"""
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent  # repo 根目錄（本檔在 tools/）
PROB = ROOT / "problems"

IMG_RE = re.compile(r"!\[[^\]]*\]\([^)]*\)")


def solved_ids():
    out = set()
    for f in (ROOT / "src").rglob("*.cpp"):
        if re.fullmatch(r"[a-z]\d+", f.stem):
            out.add(f.stem)
    return out


def classify(pid):
    md = (PROB / pid / "problem.md").read_text(encoding="utf-8")
    lines = md.splitlines()
    title = lines[0].lstrip("# ").strip() if lines else pid
    # 題目文字 = 範例之前的敘述，去掉標題行與圖片連結後的實際字數
    body = md.split("## 範例輸入")[0]
    body = "\n".join(body.splitlines()[1:])
    text = IMG_RE.sub("", body)
    text = re.sub(r"^##\s.*$", "", text, flags=re.M)  # 段落標題不算
    text = re.sub(r"\s+", "", text)
    if "Unfinished!" in title:
        return "placeholder"
    if len(text) < 40:
        return "stub"
    if IMG_RE.search(md):
        return "image"
    return "normal"


def main():
    solved = solved_ids()
    todo = sorted(
        d.name for d in PROB.iterdir()
        if d.is_dir() and re.fullmatch(r"[a-z]\d+", d.name) and d.name not in solved
    )
    buckets = {"placeholder": [], "stub": [], "image": [], "normal": []}
    for pid in todo:
        buckets[classify(pid)].append(pid)

    for name, ids in buckets.items():
        (PROB / f".todo_{name}.txt").write_text("\n".join(ids) + "\n", encoding="utf-8")
        print(f"{name:12s} {len(ids):5d} 題  -> problems/.todo_{name}.txt")
    print(f"{'total':12s} {len(todo):5d} 題")


if __name__ == "__main__":
    main()
