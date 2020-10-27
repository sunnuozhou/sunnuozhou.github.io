---
title: ACM ICPC World Finals 2016 A题
tags:
  - OI
  - codeforces
  - 贪心
date: 2020-10-27 13:00:46
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242/)

考虑贪心，每次吃最早会到达下限限制的食物，由于上下限的界限足够大，可以不管上限，用堆维护可以做到 $O(n\log n)$。

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
int n,m,S,p[N],h[N];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
ll calc(int x,ll s){
	return (s*S+S-1)/p[x]+1;
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++) read(p[i]),S+=p[i];
	for(int i=1;i<=m;i++){
		int x;read(x);
		h[x]++;
	}
	for(int i=1;i<=n;i++) q.emplace(calc(i,h[i]),i);//,cerr<<i<<' '<<h[i]<<' '<<calc(i,h[i])<<'\n';
	int tim=m;
	while(!q.empty()){
		int x=q.top().second;
		ll nxt=q.top().first;
		q.pop();
		tim++;
		if(nxt<tim){cout<<nxt-m-1<<'\n';return 0;}
		if(tim>m+S){cout<<"forever\n";return 0;}
		h[x]++;
		q.emplace(calc(x,h[x]),x);
	}
	cerr<<"error\n";
	return 0;
}
 
```

