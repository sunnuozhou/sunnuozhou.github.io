---
title: ACM ICPC World Finals 2016 B题
tags:
  - OI
  - codeforces
  - DP
  - 贪心
date: 2020-10-27 13:00:49
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242/)

以 $b+1$ 为源点跑两遍最短路，一次正向一次负向。记一个点两次最短路的距离和为 $w_i$，那么对于一个做同一个项目的集合 $S$，代价为 $(|S|-1)\sum w_i$，这也说明了一个集合中的元素在大小上应该是连续的，排序后DP即可。

记录 $f_{i,j}$ 表示前 $i$ 个元素，组成了 $j$ 组的最小代价，转移时枚举当前集合的大小，注意到大小不超过 $\frac ij$，所以时间复杂度 $O(n^2\log n)$，可以用单调队列优化到 $O(n^2)$，但没必要。

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
const int N = 101000;
ll d[N],val[N];
int n,S,B,m;
ll f[5010][5010];
vector<pair<int,int> > e[N],ve[N];
void dij(vector<pair<int,int> > *e){
	memset(d,63,sizeof(d));
	d[B+1]=0;
	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
	q.emplace(0,B+1);
	while(!q.empty()){
		int u=q.top().second;
		int dis=q.top().first;
		q.pop();
		if(dis>d[u]) continue;
		for(auto v:e[u]) if(d[v.first]>d[u]+v.second){
			d[v.first]=d[u]+v.second;
			q.emplace(d[v.first],v.first);
		}
	}
	for(int i=1;i<=B;i++) val[i]+=d[i];
}
int main(){
	read(n);read(B);read(S);read(m);
	for(int i=1;i<=m;i++){
		int x,y,z;read(x);read(y);read(z);
		e[x].emplace_back(y,z);
		ve[y].emplace_back(x,z);
	}
	dij(e);
	dij(ve);
	memset(f,63,sizeof(f));
	f[0][0]=0;
	sort(val+1,val+B+1);
	for(int i=1;i<=B;i++) val[i]+=val[i-1];
	for(int i=1;i<=B;i++)
		for(int j=1;j<=i&&j<=S;j++)
			for(int k=0;k<=i/j;k++)
				f[i][j]=min(f[i][j],f[i-k][j-1]+(k-1)*(val[i]-val[i-k]));
	cout<<f[B][S]<<'\n';
	return 0;
}
```

