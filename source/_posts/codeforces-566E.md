---
title: codeforces 566E
tags:
  - OI
  - codeforces
  - 构造
  - bitset
date: 2020-01-25 17:18:30
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/566/problem/E)

先排除$n=2$的情况，下面讨论$n\ge 3$的情况。

对于一对点$x,y$，如果它们距离$>$4，那么就没有交集。

如果距离$=4$，那么有恰好一个点在两边都出现。

如果距离$=3$，那么恰好有两个点$u,v$都出现，并且$u,v$之间有连边（$u,v$均不是叶子）。

如果距离$\le2$，那么至少有$3$个点都出现。

我们可以枚举两个点，如果它们交集为2，就可以得到一条边。

全部枚举完后，我们可以得到所有连接两个非叶子节点的边，假设一个有$cnt$条。

如果$cnt=0$ ，输出一棵菊花即可。

如果$cnt=1$，假设边为$(x,y)$，那么除了$x,y$以外的所有点，集合应该只有至多两种，分别连在$x,y$上就好了。

如果$cnt>2$，在只考虑非叶子点的情况下，求出每个非叶子点的距离$\le1$集合，如果一个叶子的距离$\le2$集合在只考虑非叶子的时候等于某个非叶子点的距离$\le1$集合，那么就说明他们之间有连边。一个叶子对应的集合一定是包含自己并且在只考虑非叶子的时候最小的集合。

可以用$bitset$优化，时间复杂度$O(\frac{n^3}{w})$

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
int n,cnt,u[N],v[N],d[N];
bitset<N> b[N],E[N],vis[N];
void add(int x,int y){
	if(x>y) swap(x,y);
	for(int i=1;i<=cnt;i++)
		if(u[i]==x&&v[i]==y) return;
	++cnt;
	u[cnt]=x;v[cnt]=y;
	d[x]++;d[y]++;
	E[x][y]=E[y][x]=1;
}
int main(){
	read(n);
	if(n==2){
		cout<<1<<' '<<2<<'\n';
		return 0;
	}
	for(int i=1;i<=n;i++){
		int k;read(k);
		for(int j=1;j<=k;j++){
			int x;read(x);
			b[i][x]=1;
			vis[i][x]=1;
		}
		E[i][i]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if((b[i]&b[j]).count()==2){
				int x=n,y=1;
				auto now=b[i]&b[j];
				while(!now[x]) x--;
				while(!now[y]) y++;
				add(x,y);
			}
	if(cnt==0){
		for(int i=2;i<=n;i++)
			cout<<1<<' '<<i<<'\n';
		return 0;
	}
	if(cnt==1){
		int p[2]={u[1],v[1]};
		for(int i=1;i<=n;i++)
			if(b[i].count()==n) swap(b[i],b[p[b[p[0]].count()==n]]);
		cout<<p[0]<<' '<<p[1]<<'\n';
		auto now=b[p[0]==1?p[1]==2?3:2:1];
		for(int i=1;i<=n;i++)
			if(i!=p[0]&&i!=p[1])
				cout<<i<<' '<<p[now[i]]<<'\n';
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(d[j]==0) b[i][j]=0;
	for(int i=1;i<=cnt;i++)
		cout<<u[i]<<' '<<v[i]<<'\n';
	for(int i=1;i<=n;i++)
		if(!d[i]){
			int now=n,w=0;
			for(int j=1;j<=n;j++)
				if(vis[j][i]&&b[j].count()<now){
					now=b[j].count();
					w=j;
				}
			for(int j=1;j<=n;j++)
				if(d[j]&&E[j]==b[w]){cout<<j<<' '<<i<<'\n';break;}
			b[w].set();
		}
	return 0;
}
```

