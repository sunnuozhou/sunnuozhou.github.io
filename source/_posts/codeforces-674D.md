---
title: codeforces 674D
tags:
  - OI
  - codeforces
date: 2020-01-23 20:16:21
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/674/problem/D)

每一个节点记录$sum_i$表示除了$f_i$的贡献以外的权值和，那么就可以支持$O(1)$的修改和$O(1)$的询问单点。

再在每一个点上记录一个$set$，存下除了$f_i$以外每一个相邻点的权值，然后用一个全局的$set$维护最小值和最大值就可以了。

时间复杂度$O(q\log n+n\log n)$。

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
const int N = 301000;
multiset<ll> p[N],ans;
ll t[N],sum[N],w[N];
int s[N],n,q,fa[N];
void del(int x,ll k){
	ans.erase(ans.find(*p[x].begin()+w[x]));
	ans.erase(ans.find(*p[x].rbegin()+w[x]));
	p[x].erase(p[x].find(k));
	if(p[x].size()) ans.insert(*p[x].begin()+t[x]/s[x]);
	if(p[x].size()) ans.insert(*p[x].rbegin()+t[x]/s[x]);
	w[x]=t[x]/s[x];
}
void ins(int x,ll k){
	if(p[x].size()) ans.erase(ans.find(*p[x].begin()+w[x]));
	if(p[x].size()) ans.erase(ans.find(*p[x].rbegin()+w[x]));
	p[x].insert(k);
	ans.insert(*p[x].begin()+t[x]/s[x]);
	ans.insert(*p[x].rbegin()+t[x]/s[x]);
	w[x]=t[x]/s[x];
}
void change(int x,int y){
	if(fa[x]==y) return;
	del(fa[x],sum[x]);
	del(fa[fa[x]],sum[fa[x]]);
	del(fa[y],sum[y]);
	if(fa[fa[x]]!=y) del(fa[fa[fa[x]]],sum[fa[fa[x]]]);
	if(fa[fa[x]]!=fa[y]&&fa[y]!=fa[x]) del(fa[fa[y]],sum[fa[y]]);
	sum[fa[x]]-=(t[fa[x]]-t[fa[x]]/s[fa[x]]*(s[fa[x]]-1))+t[x]/s[x];
	sum[fa[fa[x]]]-=t[fa[x]]/s[fa[x]];
	s[fa[x]]--;
	sum[fa[x]]+=t[fa[x]]-t[fa[x]]/s[fa[x]]*(s[fa[x]]-1);
	sum[fa[fa[x]]]+=t[fa[x]]/s[fa[x]];
	sum[y]-=(t[y]-t[y]/s[y]*(s[y]-1))-t[x]/s[x];
	sum[fa[y]]-=t[y]/s[y];
	s[y]++;
	sum[y]+=t[y]-t[y]/s[y]*(s[y]-1);
	sum[fa[y]]+=t[y]/s[y];
	ins(fa[x],0);del(fa[x],0);
	ins(y,sum[x]);
	ins(fa[fa[x]],sum[fa[x]]);
	ins(fa[y],sum[y]);
	if(fa[fa[x]]!=y) ins(fa[fa[fa[x]]],sum[fa[fa[x]]]);
	if(fa[y]!=fa[fa[x]]&&fa[y]!=fa[x]) ins(fa[fa[y]],sum[fa[y]]);
	fa[x]=y;
}
int main(){
	read(n);read(q);
	for(int i=1;i<=n;i++)
		read(t[i]),s[i]=2;
	for(int i=1;i<=n;i++)
		read(fa[i]),s[fa[i]]++;
	for(int i=1;i<=n;i++)
		sum[fa[i]]+=t[i]/s[i],sum[i]+=t[i]-t[i]/s[i]*(s[i]-1);
	for(int i=1;i<=n;i++)
		ins(fa[i],sum[i]);
	while(q--){
		int opt,x,y;read(opt);
		if(opt==1){
			read(x);read(y);
			change(x,y);
		}
		if(opt==2){
			read(x);
			cout<<sum[x]+t[fa[x]]/s[fa[x]]<<'\n';
		}
		if(opt==3){
			cout<<*ans.begin()<<' '<<*ans.rbegin()<<'\n';
		}
	}
	return 0;
}
```

