import os
import re

CODEFORCES_HANDLE = "Lucky_0704"
CODEFORCES_PROFILE = "https://codeforces.com/profile/Lucky_0704"

README_TEMPLATE = """# ⚔️ Codeforces Solutions

Archive of competitive programming solutions from Codeforces contests and problem sets.

## 👤 Profile
- **Codeforces:** [{handle}]({cf_link})

## 📊 Progress Dashboard
- **Total Problems Solved:** {total}
- **Categories Covered:** {topics_count}

## 📚 Problem Catalog

| # | Problem | Contest / ID | Rating | Topic | Solution | Date |
|---|---------|:------------:|:------:|-------|:--------:|------|
{rows}

---
*Auto-updated via [GitHub Actions](.github/workflows/update_readme.yml).*
"""

problems = []

for root, dirs, files in os.walk("."):
    if "/.git" in root or root.startswith("./.git") or "scripts" in root:
        continue

    for file in sorted(files):
        if file.endswith((".cpp", ".py", ".java")):
            filepath = os.path.join(root, file).replace("\\", "/")
            with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
                content = f.read()

            name = re.search(r"Problem Name\s*:\s*(.*)", content)
            cf_id = re.search(r"Problem ID\s*:\s*(.*)", content)
            rating = re.search(r"Rating\s*:\s*(.*)", content)
            topic = re.search(r"Topic\s*:\s*(.*)", content)
            date = re.search(r"Date Solved\s*:\s*(.*)", content)

            p_name = name.group(1).strip() if name else file
            p_id = cf_id.group(1).strip() if cf_id else "-"
            p_rating = rating.group(1).strip() if rating else "-"
            p_topic = topic.group(1).strip() if topic else "General"
            p_date = date.group(1).strip() if date else "-"

            # Automatically generates link to Codeforces problem if ID is formatted like 71A
            cf_cell = "-"
            if p_id != "-":
                match = re.match(r"^(\d+)([A-Z]\d*)$", p_id)
                if match:
                    contest_id, index = match.groups()
                    cf_cell = f"[{p_id}](https://codeforces.com/problemset/problem/{contest_id}/{index})"
                else:
                    cf_cell = p_id

            problems.append({
                "name": p_name,
                "cf_cell": cf_cell,
                "rating": p_rating,
                "topic": p_topic,
                "link": f"[{file}]({filepath})",
                "date": p_date
            })

table_rows = []
unique_topics = {p["topic"] for p in problems}

for idx, p in enumerate(problems, 1):
    table_rows.append(
        f"| {idx} | {p['name']} | {p['cf_cell']} | `{p['rating']}` | `{p['topic']}` | {p['link']} | {p['date']} |"
    )

with open("README.md", "w", encoding="utf-8") as f:
    f.write(README_TEMPLATE.format(
        handle=CODEFORCES_HANDLE,
        cf_link=CODEFORCES_PROFILE,
        total=len(problems),
        topics_count=len(unique_topics),
        rows="\n".join(table_rows) if table_rows else "| - | No problems added yet | - | - | - | - | - |"
    ))