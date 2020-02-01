---
title: codeforces 566C
tags:
  - OI
  - codeforces
  - 分治
date: 2020-01-24 09:54:44
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/566/problem/C)

先假设最终选定的点可以在边上，那么可以得到以下结论：

- 对于一条边$(A,B)$，函数在$(A,B)$上是凹函数。
- 不存在2个函数的极小点。
- 函数的最小点有且只有1个。
- 若最小点在边$(A,B)$上，那么答案点一定是$A,B$中的一个。

定义$g(A,B)$表示函数在$(A,B)$边上时点$A$的右导数，又有以下结论：

- 对于一个顶点$A$，与它相邻的点为$B_1..B_k$，如果$\forall_{1\le i\le k}g(A,B_i)\ge0$，那么点$A$就是最小点。
- 对于一个顶点$A$，与它相邻的点为$B_1..B_k$，如果$\exists_{1\le i\le k}g(A,B_i)<0$，那么将$A$删除后$B_i$和最小点一定在同一连通块。
- 对于一个顶点$A$，与它相邻的点为$B_1..B_k$，不存在两个$B_i$使得$g(A,B_i)<0$。

有了这些结论就可以得到一个做法：

对于一棵树，求出这棵树的重心，如果第5个结论成立，那么重心就是答案，否则删去$A$，对于满足$g(A,B_i)<0$的$B_i$，递归下去求解。

时间复杂度$O(n\log n)$。

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
const int N = 201000;
struct edge{int v,w;};
vector<edge> e[N];
int w[N],W,n,s[N],mx[N],siz,rt,h[N];
lld g[N],ans;
void getroot(int x,int dad){
	s[x]=1;mx[x]=0;
	for(auto v:e[x]) if(v.v!=dad&&!h[v.v]){
		getroot(v.v,x);s[x]+=s[v.v];
		mx[x]=max(mx[x],s[v.v]);
	}
	mx[x]=max(mx[x],siz-s[x]);
	if(!rt||mx[x]<mx[rt]) rt=x;
}
void calc_f(int x,int dad,lld&F,int dis=0){
	F+=dis*sqrtl(dis)*w[x];
	for(auto v:e[x]) if(v.v!=dad) calc_f(v.v,x,F,dis+v.w);
}
void calc_g(int x,int dad,int dis=0){
	g[x]=sqrtl(dis)*1.5*w[x];
	for(auto v:e[x]) if(v.v!=dad){
		calc_g(v.v,x,dis+v.w);
		g[x]+=g[v.v];
	}
}
void solve(int x){
	h[x]=1;getroot(x,0);
	lld F=0;
	calc_f(x,0,F);
	calc_g(x,0);
	if(F<ans) ans=F,W=x;
	for(auto v:e[x]) if(!h[v.v]&&g[x]-g[v.v]<g[v.v]){
		siz=s[v.v];rt=0;
		getroot(v.v,0);
		solve(rt);
		return;
	}
}
int main(){
	read(n);
	for(int i=1;i<=n;i++) read(w[i]);
	for(int i=1;i<n;i++){
		int x,y,z;read(x);read(y);read(z);
		e[x].push_back({y,z});
		e[y].push_back({x,z});
	}
	siz=n;ans=1e24l;
	getroot(1,0);
	solve(rt);
	printf("%d %.10Lf\n",W,ans);
	return 0;
}
```

