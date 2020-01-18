---
title: codeforces 605E
tags:
  - OI
  - codeforces
  - 概率
  - DP
date: 2020-01-17 09:37:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/605/problem/E)

考虑倒着DP，记$f_i$表示$i$到$n$的期望最短路，进行一个类似于$dijkstra$的算法，就可以求出答案。

具体式子如下：

记$g_i$表示如果最短路方案下没路可走的时候贡献算零的最短路的值，$p_i$表示有多少概率没路走。

从$u$到$v$转移时

$f_v\to(g_v+p_v\times P_{边的出现概率}\times (f_u+1)+p_i\times(1-P))/(1-p_i\times(1-P))$

$g_v\to(g_v+p_v\times P_{边的出现概率}\times (f_u+1))$

$p_v\to p_v\times(1-P)$

<!--more-->

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
const int N = 1010;
int n,vis[N];
double mp[N][N],f[N],g[N],p[N];
int main(){
	read(n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int p;read(p);
			mp[i][j]=p/100.;
		}
	for(int i=1;i<n;i++) f[i]=1e9,p[i]=1;
	for(int t=1;t<=n;t++){
		int x=0;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(!x||f[i]<f[x])) x=i;
		vis[x]=1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(g[i]+p[i]*mp[i][x]*(f[x]+1)+(p[i]*(1-mp[i][x])))/(1-p[i]*(1-mp[i][x]))<f[i]){
				f[i]=(g[i]+p[i]*mp[i][x]*(f[x]+1)+(p[i]*(1-mp[i][x])))/(1-p[i]*(1-mp[i][x]));
				g[i]=(g[i]+p[i]*mp[i][x]*(f[x]+1));
				p[i]=p[i]*(1-mp[i][x]);
			}
	}
	cout<<fixed<<setprecision(10)<<f[1]<<'\n';
	return 0;
}

```

