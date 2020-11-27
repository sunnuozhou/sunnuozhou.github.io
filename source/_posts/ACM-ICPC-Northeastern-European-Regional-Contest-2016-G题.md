---
title: ACM ICPC Northeastern European Regional Contest 2016 G题
tags:
  - OI
  - codeforces
  - DP
  - dfs
date: 2020-11-11 11:10:51
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

对于没有出边的点，胜负状态已经确定了。

记录每个点当前是必胜还是必败。

如果一个点Gennady的胜负状态确定了，那么与这个点相邻的点Georgiy先手就一定不会和，即要么胜要么负，算出当前的胜负状态。

如果一个点的出边指向的点Georgiy的胜负状态确定了，那么这个点Gennady先手也和不了，算出当前的胜负状态。

把没有出边的点胜负状态确定好后dfs，可以发现Georgiy先手的状态一定不会从赢变输，所以直接dfs复杂度正确。

时间复杂度 $O(n+m)$。

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
struct Graph{
	int n,m,d[N],f[N][2],vis[N];
	vector<int> e[N],E[N];
	void init(){
		read(n);read(m);
		for(int i=1;i<=m;i++){
			int x,y;read(x);read(y);
			e[y].push_back(x);d[x]++;
			E[x].push_back(y);
		}
	}
	void dfs0(int x){
		f[x][0]=-1;
		for(int p:E[x]) if(f[p][1]<0) f[x][0]=1;
		for(int v:e[x]) dfs1(v,-f[x][0]);
	}
	void dfs1(int x,int k){
		if(f[x][1]==1||f[x][1]==-1&&k!=1) return;
		f[x][1]=k;
		int fir=!vis[x];vis[x]=1;
		for(int v:e[x]){
			d[v]-=fir;
			if(!d[v]){
				dfs0(v);
			}
		}
	}
	void solve(){
		for(int i=1;i<=n;i++) 
			if(!E[i].size()) dfs0(i),dfs1(i,-1);
	}
}G;
int main(){
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	G.init();
	G.solve();
	for(int i=1;i<=G.n;i++)
		putchar("LDW"[G.f[i][0]+1]);
	puts("");
	for(int i=1;i<=G.n;i++)
		putchar("LDW"[G.f[i][1]+1]);
	return 0;
}
```

