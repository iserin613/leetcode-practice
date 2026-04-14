# LeetCode Practice Archive

这个仓库用于管理个人 LeetCode 题解，并自动完成以下工作：

- 根据题号抓取题面并生成中文 `md` 文件
- 根据 LeetCode 官方标签自动分类归档
- 在编辑 `leetcode*.cpp` 后自动同步题面与分类目录

## 目录结构

- `leetcodeXXXX.cpp`：题解代码
- `leetcodeXXXX.md`：对应题目的中文题面（含难度、标签、链接）
- `tags/`：按标签归档后的目录（多标签会复制到多个目录）
- `classify_leetcode.py`：按标签分类脚本
- `fetch_problem_statements.py`：抓取题面脚本（中文优先）
- `.cursor/hooks/leetcode_auto_sync.py`：编辑后自动同步脚本
- `.cursor/hooks.json`：Cursor 项目级 Hook 配置

## 自动化行为

当你在项目里编辑文件名匹配 `leetcode数字.cpp` 的文件时，Hook 会自动执行：

1. 生成或更新根目录 `leetcode数字.md`（中文题面）
2. 按标签复制 `cpp` 到 `tags/标签目录/`
3. 同步复制对应 `md` 到 `tags/标签目录/`

## 手动命令

在 `practice` 目录执行：

```bash
python fetch_problem_statements.py --overwrite
python classify_leetcode.py --include-md
```

可选：只处理指定题号（逗号分隔）：

```bash
python fetch_problem_statements.py --ids 1,11,2463 --overwrite
python classify_leetcode.py --ids 1,11,2463 --include-md
```

## 分类规则

- 使用 LeetCode 官方标签进行分类
- 同一道题支持多标签，文件会被复制到多个标签目录
- 标签目录采用中英混合命名，例如：
  - `数组_Array`
  - `哈希表_Hash_Table`
  - `动态规划_Dynamic_Programming`

## 注意事项

- 题面内容优先来自 `leetcode.cn` 的中文字段（`translatedContent`）
- 若某题无中文字段，则会回退到英文题面字段
- `tags/classification_report.json` 保存最近一次分类报告
