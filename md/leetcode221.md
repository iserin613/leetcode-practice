# 221. 最大正方形

- 难度: `Medium`
- 标签: 数组(Array), 动态规划(Dynamic Programming), 矩阵(Matrix)
- 力扣(中文): https://leetcode.cn/problems/maximal-square/
- LeetCode(英文): https://leetcode.com/problems/maximal-square/

## 题目描述

在一个由 `'0'` 和 `'1'` 组成的二维矩阵内，找到只包含 `'1'` 的最大正方形，并返回其面积。

 

**示例 1：**

**输入：**matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
**输出：**4

```

**示例 2：**

**输入：**matrix = [["0","1"],["1","0"]]
**输出：**1

```

**示例 3：**

**输入：**matrix = [["0"]]
**输出：**0

```

 

**提示：**

	- `m == matrix.length`

	- `n == matrix[i].length`

	- `1 <= m, n <= 300`

	- `matrix[i][j]` 为 `'0'` 或 `'1'`
