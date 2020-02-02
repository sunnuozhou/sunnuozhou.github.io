---
title: lemon spj
tags:
  - 技术
date: 2020-02-02 21:11:39
categories: 教程
top: 1
---

因为老是忘记$lemon$的$spj$怎么写，又懒得用$testlib$，就在博客里记录一下。

$argv[1]$是输入文件；

$argv[2]$是选手输出文件；

$argv[3]$是标准输出文件；

$argv[4]$是满分分数**（注意，$argv[4]$不是文件）**；

$argv[5]$是选手得分（必须创建）；

$argv[6]$是报告文件（可以不创建）；

<!--more-->

[lemon-lime](https://github.com/iotang/Project_LemonLime)是真的好用。



附我的$spj$模板：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
const int N = 101000;
FILE *fin,*fout,*fans,*res,*rep;
int score;
void quit(int s){
	fprintf(res,"%d",s);
	exit(0);
}
int main(int argc,char* argv[]){
	fin=fopen(argv[1],"r");
	fout=fopen(argv[2],"r");
	fans=fopen(argv[3],"r");
	score=atoi(argv[4]);
	res=fopen(argv[5],"w");
	rep=fopen(argv[6],"w");

	return 0;
}
```

