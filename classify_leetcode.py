import json
import re
import shutil
import argparse
import urllib.request
from pathlib import Path


PRACTICE_DIR = Path(__file__).resolve().parent
CPP_DIR = PRACTICE_DIR / "cpp"
MD_DIR = PRACTICE_DIR / "md"
OUTPUT_DIR = PRACTICE_DIR / "tags"

# Common LeetCode tag translations.
ZH_TAG = {
    "Array": "数组",
    "Hash Table": "哈希表",
    "Dynamic Programming": "动态规划",
    "String": "字符串",
    "Math": "数学",
    "Sorting": "排序",
    "Greedy": "贪心",
    "Depth-First Search": "深度优先搜索",
    "Breadth-First Search": "广度优先搜索",
    "Binary Search": "二分查找",
    "Database": "数据库",
    "Matrix": "矩阵",
    "Tree": "树",
    "Binary Tree": "二叉树",
    "Stack": "栈",
    "Queue": "队列",
    "Linked List": "链表",
    "Recursion": "递归",
    "Two Pointers": "双指针",
    "Sliding Window": "滑动窗口",
    "Prefix Sum": "前缀和",
    "Backtracking": "回溯",
    "Bit Manipulation": "位运算",
    "Simulation": "模拟",
    "Graph": "图",
    "Heap (Priority Queue)": "堆_优先队列",
    "Design": "设计",
    "Union Find": "并查集",
    "Trie": "字典树",
    "Monotonic Stack": "单调栈",
    "Monotonic Queue": "单调队列",
    "Segment Tree": "线段树",
    "Ordered Set": "有序集合",
    "Counting": "计数",
    "Brainteaser": "脑筋急转弯",
}


def fetch_all_problems():
    url = "https://leetcode.com/api/problems/all/"
    req = urllib.request.Request(
        url,
        headers={
            "User-Agent": "Mozilla/5.0",
            "Accept": "application/json",
        },
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        return json.load(resp)


def fetch_tags_for_slug(slug: str):
    url = "https://leetcode.com/graphql"
    payload = json.dumps(
        {
            "operationName": "questionData",
            "variables": {"titleSlug": slug},
            "query": "query questionData($titleSlug: String!) { question(titleSlug: $titleSlug) { topicTags { name } } }",
        }
    ).encode("utf-8")
    req = urllib.request.Request(
        url,
        data=payload,
        headers={
            "User-Agent": "Mozilla/5.0",
            "Content-Type": "application/json",
            "Referer": "https://leetcode.com",
        },
        method="POST",
    )
    with urllib.request.urlopen(req, timeout=30) as resp:
        data = json.load(resp)
    tags = data.get("data", {}).get("question", {}).get("topicTags", [])
    return [t["name"] for t in tags]


def sanitize_dir_part(name: str):
    name = name.replace("/", "_").replace("\\", "_")
    name = re.sub(r"[<>:\"|?*]", "_", name)
    return name.strip().replace(" ", "_")


def main():
    parser = argparse.ArgumentParser(description="Classify leetcode solutions into tag folders.")
    parser.add_argument("--ids", default="", help="Comma-separated ids, e.g. 1,2463. Empty means all.")
    parser.add_argument("--include-md", action="store_true", help="Copy leetcodeXXXX.md together with cpp.")
    args = parser.parse_args()
    selected_ids = {x.strip() for x in args.ids.split(",") if x.strip()}

    files = sorted(CPP_DIR.glob("leetcode*.cpp"))
    if not files:
        print(f"No leetcode*.cpp files found under {CPP_DIR}.")
        return

    all_data = fetch_all_problems()
    id_to_slug = {}
    for item in all_data.get("stat_status_pairs", []):
        stat = item.get("stat", {})
        qid = str(stat.get("frontend_question_id", "")).strip()
        slug = stat.get("question__title_slug")
        if qid and slug:
            id_to_slug[qid] = slug

    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    report = []

    for f in files:
        m = re.search(r"leetcode(\d+)\.cpp$", f.name, re.IGNORECASE)
        if not m:
            continue
        qid = m.group(1)
        if selected_ids and qid not in selected_ids:
            continue
        slug = id_to_slug.get(qid)
        if not slug:
            report.append({"file": f.name, "id": qid, "status": "not_found", "tags": []})
            continue
        try:
            tags = fetch_tags_for_slug(slug)
        except Exception as e:
            report.append({"file": f.name, "id": qid, "status": f"tag_fetch_failed: {e}", "tags": []})
            continue

        if not tags:
            folder = OUTPUT_DIR / "未分类_Uncategorized"
            folder.mkdir(parents=True, exist_ok=True)
            shutil.copy2(f, folder / f.name)
            report.append({"file": f.name, "id": qid, "status": "ok_empty_tags", "tags": []})
            continue

        for tag in tags:
            zh = ZH_TAG.get(tag, "其他")
            dirname = f"{sanitize_dir_part(zh)}_{sanitize_dir_part(tag)}"
            folder = OUTPUT_DIR / dirname
            folder.mkdir(parents=True, exist_ok=True)
            shutil.copy2(f, folder / f.name)
            if args.include_md:
                md_path = MD_DIR / f"leetcode{qid}.md"
                if md_path.exists():
                    shutil.copy2(md_path, folder / md_path.name)

        report.append({"file": f.name, "id": qid, "status": "ok", "tags": tags})
        print(f"{f.name} -> {', '.join(tags)}")

    report_path = OUTPUT_DIR / "classification_report.json"
    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding="utf-8")
    print(f"\nDone. Report written to: {report_path}")


if __name__ == "__main__":
    main()
