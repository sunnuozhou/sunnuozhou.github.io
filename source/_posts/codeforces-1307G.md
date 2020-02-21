---
title: codeforces 1307G
tags:
  - OI
  - codeforces
  - 费用流
date: 2020-02-21 13:05:13
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/1307/problem/G)

*这题并不算难，可是我比赛的时候手速太慢，根本写不完。*

可以发现以下结论：

- 每次增量一定增在一条当前最短路上。
- 随着$x$的增大，同时增量的边数不断增加。
- 增量边数相同的一段是一段一次函数。

也就是说要求出对于每个不同的增量边数，最短路的长度和当时需要的$x$。

增量的边数等同于流的流量，用费用流解决即可。

时间复杂度$O(nm^2+q\log m)$

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
const int N = 110;
struct edge{int v,nxt,f,w;}e[101000];
int head[N],tot,n,m,d[N],f[N],in[N],fr[N];
ll flow,cost;
vector<pair<ll,ll> > ans;
void add(int x,int y,int f,int w){
	e[++tot]={y,head[x],f,w};
	head[x]=tot;
	e[++tot]={x,head[y],0,-w};
	head[y]=tot;
}
bool spfa(){
	memset(d,63,sizeof(d));d[1]=0;
	memset(f,0,sizeof(f));f[1]=1e9;
	memset(fr,0,sizeof(fr));
	queue<int> q;q.push(1);
	while(!q.empty()){
		int u=q.front();q.pop();in[u]=0;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].f&&d[e[i].v]>d[u]+e[i].w){
				d[e[i].v]=d[u]+e[i].w;
				f[e[i].v]=min(f[u],e[i].f);
				fr[e[i].v]=i;
				if(!in[e[i].v]) in[e[i].v]=1,q.push(e[i].v);
			}
	}
	return f[n];
}
void update(){
	ans.emplace_back(1ll*flow*d[n]-cost,d[n]);
	flow+=f[n];cost+=1ll*f[n]*d[n];
	for(int x=n;fr[x];x=e[fr[x]^1].v)
		e[fr[x]].f-=f[n],e[fr[x]^1].f+=f[n];
}
void Edmonds_karp(){
	cost=flow=0;
	while(spfa())
		update();
	ans.emplace_back(1ll*flow*d[n]-cost,d[n]);
}
int main(){
	read(n);read(m);tot=1;
	for(int i=1;i<=m;i++){
		int x,y,z;read(x);read(y);read(z);
		add(x,y,1,z);
	}
	Edmonds_karp();
	int Q;read(Q);
	while(Q--){
		ll x;read(x);
		auto k=upper_bound(ans.begin(),ans.end(),make_pair(x,(ll)1e18));
		lld Ans=1.l*((k-1)->second*(k->first-x)+k->second*(x-(k-1)->first))/(k->first-(k-1)->first);
		printf("%.10Lf\n",Ans);
	}
	return 0;
}
```

