import json
import re
import html
import argparse
import urllib.request
import urllib.error
from pathlib import Path


PRACTICE_DIR = Path(__file__).resolve().parent
CPP_DIR = PRACTICE_DIR / "cpp"
MD_DIR = PRACTICE_DIR / "md"


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


def _fetch_question_data_from_endpoint(slug: str, url: str, referer: str, retries: int = 3):
    payload = json.dumps(
        {
            "operationName": "questionData",
            "variables": {"titleSlug": slug},
            "query": """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionId
    questionFrontendId
    title
    translatedTitle
    titleSlug
    difficulty
    translatedContent
    content
    topicTags {
      name
      translatedName
    }
  }
}
""",
        }
    ).encode("utf-8")

    req = urllib.request.Request(
        url,
        data=payload,
        headers={
            "User-Agent": "Mozilla/5.0",
            "Accept": "application/json",
            "Content-Type": "application/json",
            "Origin": referer.rstrip("/"),
            "Referer": referer,
        },
        method="POST",
    )
    last_exc = None
    for _ in range(retries):
        try:
            with urllib.request.urlopen(req, timeout=30) as resp:
                data = json.load(resp)
            return data.get("data", {}).get("question")
        except Exception as exc:
            last_exc = exc
    raise last_exc


def fetch_question_data(slug: str, retries: int = 3):
    # Some regions/networks intermittently get 403 from leetcode.cn/graphql.
    # Try CN first for translated content, then fallback to leetcode.com/graphql.
    endpoints = [
        ("https://leetcode.cn/graphql", "https://leetcode.cn/"),
        ("https://leetcode.com/graphql", "https://leetcode.com/"),
    ]
    last_exc = None
    for url, referer in endpoints:
        try:
            return _fetch_question_data_from_endpoint(slug, url, referer, retries=retries)
        except urllib.error.HTTPError as exc:
            last_exc = exc
            # 403 is usually policy/session related; fallback to next endpoint.
            if exc.code != 403:
                continue
        except Exception as exc:
            last_exc = exc
    raise last_exc


def html_to_markdown(raw_html: str) -> str:
    text = raw_html or ""

    # Convert some common block tags before stripping remaining tags.
    replacements = [
        (r"<\s*br\s*/?\s*>", "\n"),
        (r"</\s*p\s*>", "\n\n"),
        (r"<\s*p[^>]*>", ""),
        (r"</\s*li\s*>", "\n"),
        (r"<\s*li[^>]*>", "- "),
        (r"</\s*ul\s*>", "\n"),
        (r"<\s*ul[^>]*>", ""),
        (r"</\s*ol\s*>", "\n"),
        (r"<\s*ol[^>]*>", ""),
        (r"<\s*h1[^>]*>", "# "),
        (r"<\s*h2[^>]*>", "## "),
        (r"<\s*h3[^>]*>", "### "),
        (r"</\s*h[1-6]\s*>", "\n\n"),
        (r"<\s*pre[^>]*>", "\n```text\n"),
        (r"</\s*pre\s*>", "\n```\n"),
        (r"<\s*code[^>]*>", "`"),
        (r"</\s*code\s*>", "`"),
        (r"<\s*strong[^>]*>", "**"),
        (r"</\s*strong\s*>", "**"),
        (r"<\s*em[^>]*>", "*"),
        (r"</\s*em\s*>", "*"),
    ]
    for pattern, repl in replacements:
        text = re.sub(pattern, repl, text, flags=re.IGNORECASE)

    # Drop all other HTML tags.
    text = re.sub(r"<[^>]+>", "", text)

    # Decode HTML entities.
    text = html.unescape(text)

    # Normalize excessive blank lines.
    text = re.sub(r"\n{3,}", "\n\n", text).strip()
    return text


def parse_args():
    parser = argparse.ArgumentParser(description="Generate Chinese markdown statements for leetcode*.cpp.")
    parser.add_argument(
        "--ids",
        default="",
        help="Comma-separated question ids, e.g. 1,11,2463. Empty means all.",
    )
    parser.add_argument(
        "--overwrite",
        action="store_true",
        help="Overwrite existing leetcodeXXXX.md files.",
    )
    return parser.parse_args()


def main():
    args = parse_args()
    selected_ids = {x.strip() for x in args.ids.split(",") if x.strip()}
    CPP_DIR.mkdir(parents=True, exist_ok=True)
    MD_DIR.mkdir(parents=True, exist_ok=True)
    code_files = sorted(CPP_DIR.glob("leetcode*.cpp"))
    if not code_files:
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

    generated = 0
    skipped = 0
    failed = 0

    for code_file in code_files:
        m = re.search(r"leetcode(\d+)\.cpp$", code_file.name, re.IGNORECASE)
        if not m:
            continue

        qid = m.group(1)
        if selected_ids and qid not in selected_ids:
            continue
        md_file = MD_DIR / f"leetcode{qid}.md"
        if md_file.exists() and not args.overwrite:
            skipped += 1
            print(f"[SKIP] {md_file.name} already exists.")
            continue

        slug = id_to_slug.get(qid)
        if not slug:
            failed += 1
            print(f"[FAIL] leetcode{qid}.cpp: question id not found in API.")
            continue

        try:
            question = fetch_question_data(slug)
        except Exception as exc:
            failed += 1
            print(f"[FAIL] leetcode{qid}.cpp: request failed: {exc}")
            continue

        if not question:
            failed += 1
            print(f"[FAIL] leetcode{qid}.cpp: empty question response.")
            continue

        title = question.get("translatedTitle") or question.get("title", "")
        difficulty = question.get("difficulty", "Unknown")
        tags = []
        for item in question.get("topicTags", []):
            zh_tag = (item.get("translatedName") or "").strip()
            en_tag = (item.get("name") or "").strip()
            if zh_tag and en_tag:
                tags.append(f"{zh_tag}({en_tag})")
            elif zh_tag or en_tag:
                tags.append(zh_tag or en_tag)
        content_md = html_to_markdown(question.get("translatedContent") or question.get("content", ""))

        out = []
        out.append(f"# {question.get('questionFrontendId', qid)}. {title}")
        out.append("")
        out.append(f"- 难度: `{difficulty}`")
        out.append(f"- 标签: {', '.join(tags) if tags else 'N/A'}")
        out.append(f"- 力扣(中文): https://leetcode.cn/problems/{slug}/")
        out.append(f"- LeetCode(英文): https://leetcode.com/problems/{slug}/")
        out.append("")
        out.append("## 题目描述")
        out.append("")
        out.append(content_md if content_md else "_未获取到题面内容。_")
        out.append("")

        md_file.write_text("\n".join(out), encoding="utf-8")
        generated += 1
        print(f"[OK] generated {md_file.name}")

    print("\nDone.")
    print(f"Generated: {generated}")
    print(f"Skipped:   {skipped}")
    print(f"Failed:    {failed}")


if __name__ == "__main__":
    main()
