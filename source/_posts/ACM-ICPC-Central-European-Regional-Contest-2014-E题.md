---
title: ACM ICPC Central European Regional Contest 2014 G题
tags:
  - OI
  - codeforces
  - 搜索
  - DP
date: 2020-12-02 11:42:43
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100543)

可以发现，如果操作过程中如果出现序列不是先升再降（升和降的长度可以是0），那么一定不行。

于是考虑记忆化搜索，记 $f_{i,j}$ 表示放了前 $i$ 个，升的部分和为 $j$，是否可行。