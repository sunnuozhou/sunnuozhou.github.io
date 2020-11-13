---
title: ACM ICPC Northeastern European Regional Contest 2017 J题
tags:
  - OI
  - codeforces
  - 最短路
date: 2020-11-09 11:31:40
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101630)

枚举第 $k$ 大的值是多少，假设是 $X$，令每条边的权值减去 $X$（不小于0）。可以发现，只有恰好第 $k$ 大为 $X$ 的路径是以真实值被算到的，其他的路径的值都比真实值大，所以做法正确。

时间复杂度 $O(m(n+m)\log(n+m))$。

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
const int N = 5100;
int n,m,K,u[N],v[N],w[N],Q,b[N],cnt;
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
ll d[N];
vector<pair<int,int> > e[N];
void dij(){
	memset(d,63,sizeof(d));d[1]=0;
	q.emplace(0,1);
	while(!q.empty()){
		int u=q.top().second;ll dis=q.top().first;q.pop();
		if(dis!=d[u]) continue;
		for(auto&p:e[u])
			if(d[p.first]>d[u]+max(0,p.second-Q)){
				d[p.first]=d[u]+max(0,p.second-Q);
				q.emplace(d[p.first],p.first);
			}
	}
}
int main(){
	read(n);read(m);read(K);
	for(int i=1;i<=m;i++){
		read(u[i]);read(v[i]);read(w[i]);
		e[u[i]].emplace_back(v[i],w[i]);
		e[v[i]].emplace_back(u[i],w[i]);
		b[++cnt]=w[i];
	}
	b[++cnt]=0;
	sort(b+1,b+cnt+1);
	ll ans=1e18;
	for(int i=1;i<=cnt;i++){
		Q=b[i];
		dij();
		ans=min(ans,d[n]+1ll*Q*K);
	}
	cout<<ans<<'\n';
	return 0;
}
```

