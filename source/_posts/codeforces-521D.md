---
title: codeforces 521D
tags:
  - OI
  - codeforces
  - 贪心
date: 2020-01-27 16:57:51
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/521/problem/D)

假设只有乘，就是排个序取最大的$m$个。

假设只有乘和加，对一个位置$i$单独考虑，如果$i$从加操作中选了一些，那一定选了最大的若干个。于是我们对于每个$i$，将对这个$i$的加操作从大到小排序，令排完序的序列为$b_1..b_s$，那第$j$个操作的相当于乘上$\frac{a_i+\sum_{1\le l\le j}b_l}{a_i+\sum_{1\le l< j}b_l}$，于是我们可以把所有加操作当成乘操作来做。

再考虑赋值操作，对于一个位置一定可以不赋值超过1次。所以只考虑赋值操作中值最大的那一个，并把它当成是加操作，然后和上面一样做。

时间复杂度$O(n\log n)$。

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
struct frac{
	ll p,q;
	frac(ll a,ll b){
		p=a;q=b;
	}
};
bool operator < (frac a,frac b){
	return 1.l*a.p/a.q<1.l*b.p/b.q;
}
int k,n,m,a[N],opt[N];
vector<pair<int,int> > q[N][2];
vector<pair<frac,int> > Q;
int main(){
	read(k);read(n);read(m);
	for(int i=1;i<=k;i++)
		read(a[i]);
	for(int i=1;i<=n;i++){
		int x,y;read(opt[i]);read(x);read(y);
		if(opt[i]<3) q[x][opt[i]-1].emplace_back(y,i);
		else Q.emplace_back(frac(y,1),i);
	}
	for(int i=1;i<=k;i++){
		pair<int,int> mx=make_pair(-1,0);
		for(auto x:q[i][0]) if(x.first>mx.first) mx=x;
		mx.first-=a[i];
		if(mx.first>0) q[i][1].push_back(mx);
		sort(q[i][1].begin(),q[i][1].end(),greater<pair<int,int> >());
		ll s=a[i];
		for(auto x:q[i][1]){
			Q.emplace_back(frac(s+x.first,s),x.second);
			s+=x.first;
		}
	}
	sort(Q.begin(),Q.end(),greater<pair<frac,int> >());
	vector<int> ans;
	for(auto x:Q){
		if(m--==0) break;
		ans.push_back(x.second);
	}
	sort(ans.begin(),ans.end(),[&](int a,int b){
		return opt[a]<opt[b];
	});
	cout<<ans.size()<<'\n';
	for(int x:ans) cout<<x<<' ';
	cout<<'\n';
	return 0;
}
```

