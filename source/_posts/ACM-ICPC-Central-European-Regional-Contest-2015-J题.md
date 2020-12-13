---
title: ACM ICPC Central European Regional Contest 2015 J题
tags:
  - OI
  - codeforces
  - 网络流
date: 2020-12-01 10:50:07
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101480)

可以发现，两点之间的最小割不超过3，于是直接建最小割树即可，复杂度 $O(nm)$。

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
const int N = 3100;
namespace Dinic{
	struct edge{int v,nxt,f;}e[101000];
	int head[N],tot,S,T,cur[N],b[N];
	void add(int x,int y){
		e[++tot]={y,head[x],1};
		head[x]=tot;
		e[++tot]={x,head[y],1};
		head[y]=tot;
	}
	bool bfs(){
		memset(b,0,sizeof(b));b[S]=1;
		queue<int> q;q.push(S);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt)
				if(e[i].f&&!b[e[i].v]){
					b[e[i].v]=b[u]+1;
					q.push(e[i].v);
				}
		}
		return b[T];
	}
	int dfs(int x,int flow){
		if(x==T||!flow) return flow;
		int f=flow,tmp;
		for(int&i=cur[x];i;i=e[i].nxt)
			if(b[e[i].v]==b[x]+1&&(tmp=dfs(e[i].v,min(e[i].f,flow)))){
				e[i].f-=tmp;e[i^1].f+=tmp;f-=tmp;
				if(!f) break;
			}
		return flow-f;
	}
	int Flow(int s,int t){
		S=s;T=t;
		int ans=0;
		while(bfs()){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(s,3);
		}
		return ans;
	}
}
int ans,n,m,p[N],q[N];
vector<pair<int,int> > e[N];
void build(int l,int r){
	if(l>=r) return;
	for(int i=2;i<=Dinic::tot;i++) Dinic::e[i].f=1;
	int f=Dinic::Flow(p[l],p[l+1]);
	e[p[l]].emplace_back(p[l+1],f);
	e[p[l+1]].emplace_back(p[l],f);
	int now=l,mid;
	for(int i=l;i<=r;i++)
		if(Dinic::b[p[i]]) q[now++]=p[i];
	mid=now;
	for(int i=l;i<=r;i++)
		if(!Dinic::b[p[i]]) q[now++]=p[i];
	for(int i=l;i<=r;i++) p[i]=q[i];
	build(l,mid-1);build(mid,r);
}
void dfs(int x,int dad,int tag,int mn=1e9){
	if(x<tag) ans+=mn;
	for(auto&p:e[x]) if(p.first!=dad) dfs(p.first,x,tag,min(mn,p.second));
}
int main(){
	read(n);read(m);
	Dinic::tot=1;
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		Dinic::add(x,y);
	}
	for(int i=1;i<=n;i++) p[i]=i;
	build(1,n);
	for(int i=1;i<=n;i++)
		dfs(i,0,i);
	cout<<ans<<'\n';
	return 0;
}


```

