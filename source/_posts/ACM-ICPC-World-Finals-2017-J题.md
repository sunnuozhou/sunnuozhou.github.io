---
title: ACM ICPC World Finals 2017 J题
tags:
  - OI
  - codeforces
  - 网络流
date: 2020-11-02 12:25:19
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101471)

显然答案是一个最大流，记 $maxF$ 表示1到3的最大流，$maxW$ 表示2到3的最大流，$S$ 表示最大流。

首先如果对于 $0\le F\le S$，都有最大流满足 $W+F=S$，那么最优解一定是取到 $F=aS$，可以使用求导证明。

由于函数是单峰的，即使不满足上述条件，也只要取 $F$ 为 $[S-maxW,maxF]$ 中离 $aS$  最近的就可以了。

考虑构造答案，记 $\vec{f1}$  表示 $F=maxF$ 的最大流，$\vec{f2}$ 表示 $W=maxW$ 的最大流，先求出比率 $p$ 满足 $\vec{f1}\times p+\vec{f2}\times(1-p)$ 的 $F$ 最优。

为了满足题目中流向相同的限制，需要再跑一遍网络流：将边的流量设为  $\vec{f1}\times p+\vec{f2}\times(1-p)$  的流量，跑一遍网络流使得 $F$ 达到最优，此时空下来的流量就是流 $W$ 的。

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
const int N = 1010, M = 1001000;
struct edge{int v,nxt; double f;};
struct Dinic{
	edge e[M];
	int head[N],cur[N],tot,b[N];
	void add(int x,int y,double f1,double f2){
		e[++tot]={y,head[x],f1};
		head[x]=tot;
		e[++tot]={x,head[y],f2};
		head[y]=tot;
	}
	bool bfs(int S,int T){
		memset(b,0,sizeof(b));b[S]=1;
		queue<int> q;q.push(S);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];i;i=e[i].nxt)
				if(fabs(e[i].f)>1e-9&&!b[e[i].v]){
					b[e[i].v]=b[u]+1;
					q.push(e[i].v);
				}
		}
		return b[T];
	}
	double dfs(int x,int T,double flow){
		if(x==T||flow<1e-10) return flow;
		double tmp,f=flow;
		for(int&i=cur[x];i;i=e[i].nxt)
			if(b[e[i].v]==b[x]+1&&(tmp=dfs(e[i].v,T,min(e[i].f,f)))>1e-10){
				f-=tmp;e[i].f-=tmp;e[i^1].f+=tmp;
				if(f<1e-10) break;
			}
		return flow-f;
	}
	double solve(int S,int T,double FF=1e9){
		double ans=0;
		while(bfs(S,T)&&FF>ans){
			memcpy(cur,head,sizeof(head));
			ans+=dfs(S,T,FF-ans);
		}
		return ans;
	}
}gW,gF,gA;
int n,m;
double V,A,tag[M];
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>V>>A;
	gF.tot=1;
	for(int i=1;i<=m;i++){
		int x,y,z;cin>>x>>y>>z;
		gF.add(x,y,z,z);
	}
	gW=gF;
	double maxF=gF.solve(1,3);
	double maxW=gW.solve(2,3);
	double maxA=maxF+gF.solve(2,3);
	gW.solve(1,3);
	double F,W;
	if(A*maxA<maxA-maxW) F=maxA-maxW;
	else if(A*maxA>maxF) F=maxF;
	else F=A*maxA;
	W=maxA-F;
//	cerr<<F<<' '<<W<<' '<<maxF<<' '<<maxW<<' '<<maxA<<'\n';
	double p=fabs(maxF-maxA+maxW)<1e-9?0.:(F-maxA+maxW)/(maxF-maxA+maxW);
	gA.tot=1;
	for(int i=1;i<=m;i++){
		double c1=p*gF.e[i*2+1].f+(1-p)*gW.e[i*2+1].f;
		double c2=p*gF.e[i*2].f+(1-p)*gW.e[i*2].f;
		double c=(c1+c2)/2;
//		cerr<<gF.e[i*2+1].v<<' '<<gF.e[i*2].v<<' '<<c1<<' '<<c2<<' '<<c<<'\n';
		gA.add(gF.e[i*2+1].v,gF.e[i*2].v,max(0.,c1-c),max(0.,c2-c));
		tag[i]=max(0.,c2-c);
	}
	gA.solve(1,3,F);
	cout<<fixed<<setprecision(10);
	for(int i=1;i<=m;i++){
		cout<<(gA.e[i*2+1].f-tag[i])/V<<' '<<(gA.e[i*2].f-tag[i])<<'\n';
	}
	cout<<pow(F/V,A)*pow(W,1-A)<<'\n';
	return 0;
}
```

