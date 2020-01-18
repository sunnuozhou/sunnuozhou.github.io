---
title: codeforces 536D
tags:
  - OI
  - codeforces
  - DP
  - 最短路
  - 博弈
date: 2020-01-18 12:05:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/536/problem/D)

先求出从$s$到每一个点的最短路和从t到每一个点的最短路，记为$ds_i,dt_i$。

那么这个游戏就可以变为先手每次选一个$k$,得到一些$ds_i\le k$的点，后手每次选一个$k$,得到一些$dt_i\le k$的点。

记$f_{i,j}$表示先手选的$k$现在是$i$，后手选的$k$现在是$j$的时候先手减后手的差，倒着DP。

DP时记录后缀max，可优化到$O(n^2)$。

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
const int N = 2010;
struct edge{int v,w;};
vector<edge> e[N];
ll dis[N],b[N],f[N][N][2],val[N],s[N][N],mx[N][N][2];
int n,m,S,T,cnt,m1,m2,d1[N],d2[N],h[N][N][2],ss[N][N];
int dij(int s,int*d){
	memset(dis,63,sizeof(dis));
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
	dis[s]=0;q.push(make_pair(0,s));
	while(!q.empty()){
		int u=q.top().second; ll dist=q.top().first; q.pop();
		if(dist!=dis[u]) continue;
		for(edge v:e[u]) 
			if(dis[v.v]>dis[u]+v.w){
				dis[v.v]=dis[u]+v.w;
				q.push(make_pair(dis[v.v],v.v));
			}
	}
	cnt=0;
	for(int i=1;i<=n;i++) b[++cnt]=dis[i];
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++) d[i]=lower_bound(b+1,b+cnt+1,dis[i])-b;
	return cnt;
}
int main(){
	read(n);read(m);
	read(S);read(T);
	for(int i=1;i<=n;i++) read(val[i]);
	for(int i=1;i<=m;i++){
		int x,y,z;read(x);read(y);read(z);
		e[x].push_back({y,z});
		e[y].push_back({x,z});
	}
	m1=dij(S,d1);
	m2=dij(T,d2);
	for(int i=1;i<=n;i++)
		ss[d1[i]][d2[i]]++,s[d1[i]][d2[i]]+=val[i];//cerr<<i<<' '<<d1[i]<<' '<<d2[i]<<'\n';;
	for(int i=0;i<=m1;i++)
		for(int j=0;j<=m2;j++)
			f[i][j][0]=1e18,f[i][j][1]=1e18;
	for(int i=m1;~i;i--)
		for(int j=m2;~j;j--)
			s[i][j]=-s[i+1][j+1]+s[i+1][j]+s[i][j+1]+s[i][j],
			ss[i][j]=-ss[i+1][j+1]+ss[i+1][j]+ss[i][j+1]+ss[i][j];
	for(int i=m1;i;i--)
		for(int j=m2;j;j--){
			h[i][j][0]=ss[i][j]!=ss[i+1][j]?i+1:h[i+1][j][0];
			h[i][j][1]=ss[i][j]!=ss[i][j+1]?j+1:h[i][j+1][1];
			if(h[i][j][0]){
				f[i][j][0]=s[i][j]+mx[h[i][j][0]][j][0];
				mx[i][j][1]=max(mx[i][j][1],-f[i][j][0]-s[i][j]);
			}
			if(h[i][j][1]){
				f[i][j][1]=s[i][j]+mx[i][h[i][j][1]][1];
				mx[i][j][0]=max(mx[i][j][0],-f[i][j][1]-s[i][j]);
			}
			mx[i][j][0]=max(mx[i][j][0],mx[i+1][j][0]);
			mx[i][j][1]=max(mx[i][j][1],mx[i][j+1][1]);
		}
	if(f[1][1][0]==0) puts("Flowers");
	if(f[1][1][0]>0) puts("Break a heart");
	if(f[1][1][0]<0) puts("Cry");
	return 0;
}


```

