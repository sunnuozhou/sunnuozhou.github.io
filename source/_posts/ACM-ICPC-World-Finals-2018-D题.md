---
title: ACM ICPC World Finals 2018 D题
tags:
  - OI
  - codeforces
  - DP
date: 2020-10-15 12:27:37
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/gym/102482/problem/D)

观察分裂宝石随机的方式，可以发现对于固定的 $n,d$，所有可能的宝石分布方式的出现概率是一样的。

考虑动态规划，记 $f_{n,d}$ 表示有 $n$ 个人，过了 $d$ 天，宝石前 $r$ 多的人的宝石总数的期望。

可以发现， $f_{n,d}$ 就是答案。

枚举只有一个宝石的人数，可以得到转移：

$$f_{n,d}=r+\sum\limits_{k=0}^nf_{n-k,d-n+k}\frac{\binom{d-1}{d-n+k}}{\binom{n+d-1}{d}}\binom{n}{k}$$

<!--more-->

边界条件为如果 $n\le r$，$f_{n,d}=n+d[n>0]$。

精度貌似不需要考虑。

时间复杂度 $O(n^3)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 101000;
double C[1010][1010],f[510][510];
int n,d,r;
int main(){
	read(n);read(d);read(r);
	C[0][0]=1;
	for(int i=1;i<=n+d;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=d;j++){
			if(i==0&&j>0){f[i][j]=0;continue;}
			if(i<=r){f[i][j]=j+i;continue;}
			f[i][j]=r;
			for(int k=0;k<=i;k++)
				if(j-i+k>=0){
					f[i][j]+=f[i-k][j-i+k]*C[j-1][j-i+k]/C[i+j-1][j]*C[i][k];
				}
		}
	printf("%.8lf\n",f[n][d]);
	return 0;
}
```

