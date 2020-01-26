---
title: codeforces 528C
tags:
  - OI
  - codeforces
  - 构造
  - 欧拉回路
date: 2020-01-26 15:48:58
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/528/problem/C)

先考虑加边，一张图有解，那么每一个点的度数都必须是偶数，假设现在有$k$个度数是奇数的点，那么就先加入$\frac k2$条边使得每一个点的度数都是偶数。其次，总边数必须是偶数条，所有如果当前总边数为奇数，就加一个自环。

由于图连通且每一个点的度数都是偶数，一定存在一个欧拉回路。求出一个欧拉回路，对于每一个形如$a\to b\to c$的结构，给边定向使得$a\to b,c\to b$或者$b\to a,b\to c$。

时间复杂度$O(n+m)$。

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
const int N = 1001000;
struct edge{int v,nxt;}e[N];
int d[N],head[N],cur[N],tot,n,m,ban[N];
vector<int> P;
map<pair<int,int>,stack<int> > mp;
void add(int x,int y){
	d[x]++;d[y]++;
	e[++tot]={y,head[x]};
	head[x]=tot;
	e[++tot]={x,head[y]};
	head[y]=tot;
}
void dfs(int x){
	for(int&i=cur[x];i;i=e[i].nxt)
		if(!ban[i]&&!ban[i^1])
			ban[i]=1,dfs(e[i].v);
	P.push_back(x);
}
int main(){
	read(n);read(m);tot=1;
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		add(x,y);
	}
	int lst=0;
	for(int i=1;i<=n;i++)
		if(d[i]&1){
			if(lst) add(i,lst),lst=0,m++;
			else lst=i;
		}
	if(m&1) add(1,1),m++;
	memcpy(cur,head,sizeof(cur));
	dfs(1);
	cout<<m<<'\n';
	for(int i=1;i<P.size();i++)
		if(i&1) cout<<P[i-1]<<' '<<P[i]<<'\n';
		else cout<<P[i]<<' '<<P[i-1]<<'\n';
	return 0;
}
```

