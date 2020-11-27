---
title: ACM ICPC Northeastern European Regional Contest 2016 D题
tags:
  - OI
  - codeforces
  - 费用流
date: 2020-11-11 11:10:48
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

这题和NOI的志愿者招募是一个费用流模型，考虑把限制改写为连续 $k$ 的睡觉的天数在一个区间内，然后对 $n-k+1$ 个限制建点并顺序连边，考虑如果一天从睡变成吃，会使连续 $k$ 个限制中睡的天数减1，就连一条跨越 $k$ 个限制的边即可。

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
const int N = 10100;
struct edge{int v,nxt,f,w;}e[N*50];
int head[N],in[N],tot,flow,n,t,fr[N],p[N],lim1,lim2,S[N],E[N],K;
ll d[N],cost,h[N];
void add(int x,int y,int f,int w){
	e[++tot]={y,head[x],f,w};
	head[x]=tot;
	e[++tot]={x,head[y],0,-w};
	head[y]=tot;
}
void spfa(){
	memset(d,192,sizeof(d));
	d[0]=0;
	queue<int> q;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();in[u]=0;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].f&&d[e[i].v]<d[u]+e[i].w){
				d[e[i].v]=d[u]+e[i].w;
				if(!in[e[i].v]) q.push(e[i].v),in[e[i].v]=1;
			}
	}
	for(int i=0;i<=t;i++)
		h[i]=d[i];
}
bool dij(){
	memset(d,192,sizeof(d));
	memset(fr,0,sizeof(fr));
	d[0]=0;
	priority_queue<pair<ll,int> > q;
	q.push(make_pair(0,0));
	while(!q.empty()){
		ll dis=q.top().first,u=q.top().second;q.pop();
		if(dis>d[u]) continue;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].f&&d[e[i].v]<d[u]-h[e[i].v]+h[u]+e[i].w){
				d[e[i].v]=d[u]-h[e[i].v]+h[u]+e[i].w;
				fr[e[i].v]=i;
				q.emplace(d[e[i].v],e[i].v);
			}
	}
	return fr[t];
}
void update(){
	int tmp=1e9;
	for(int i=t;fr[i];i=e[fr[i]^1].v) tmp=min(tmp,e[fr[i]].f);
	int x=t;cost+=1ll*(h[t]-h[0]+d[t])*tmp;flow+=tmp;
	for(int i=t;fr[i];i=e[fr[i]^1].v) e[fr[i]].f-=tmp,e[fr[i]^1].f+=tmp;
}
void Flow(){
	spfa();
	while(dij()){
		update();
		for(int i=0;i<=t;i++)
			h[i]+=d[i];
	}
}
int main(){
	freopen("delight.in","r",stdin);
	freopen("delight.out","w",stdout);
	read(n);read(K);read(lim1);read(lim2);
	for(int i=1;i<=n;i++) read(S[i]),cost+=S[i];
	for(int i=1;i<=n;i++) read(E[i]);
	tot=1;t=n+1;
	for(int i=1;i<=n-K+1;i++)
		add(i,i+1,K-lim2-lim1,0);
	add(0,1,K-lim1,0);add(n-K+2,t,K-lim1,0);
	for(int i=1;i<=n;i++){
		int l=max(1,i-K+1),r=min(i,n-K+1);
		add(l,r+1,1,E[i]-S[i]);
		p[i]=tot-1;
	}
	Flow();
	cout<<cost<<'\n';
	for(int i=1;i<=n;i++)
		putchar("ES"[e[p[i]].f]);
	return 0;
}
 
```

