# 2110. 股票平滑下跌阶段的数目

- 难度: `Medium`
- 标签: 数组(Array), 数学(Math), 双指针(Two Pointers), 动态规划(Dynamic Programming), 滑动窗口(Sliding Window)
- 力扣(中文): https://leetcode.cn/problems/number-of-smooth-descent-periods-of-a-stock/
- LeetCode(英文): https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/

## 题目描述

给你一个整数数组 `prices` ，表示一支股票的历史每日股价，其中 `prices[i]` 是这支股票第 `i` 天的价格。

一个 **平滑下降的阶段** 定义为：对于 **连续一天或者多天** ，每日股价都比 **前一日股价恰好少 **`1` ，这个阶段第一天的股价没有限制。

请你返回 **平滑下降阶段** 的数目。

 

**示例 1：**

输入：prices = [3,2,1,4]
输出：7
解释：总共有 7 个平滑下降阶段：
[3], [2], [1], [4], [3,2], [2,1] 和 [3,2,1]
注意，仅一天按照定义也是平滑下降阶段。

```

**示例 2：**

输入：prices = [8,6,7,7]
输出：4
解释：总共有 4 个连续平滑下降阶段：[8], [6], [7] 和 [7]
由于 8 - 6 ≠ 1 ，所以 [8,6] 不是平滑下降阶段。

```

**示例 3：**

输入：prices = [1]
输出：1
解释：总共有 1 个平滑下降阶段：[1]

```

 

**提示：**

	- `1 <= prices.length <= 105`

	- `1 <= prices[i] <= 105`
