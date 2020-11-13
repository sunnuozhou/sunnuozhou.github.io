---
title: ACM ICPC Northeastern European Regional Contest G题
tags:
  - OI
  - codeforces
  - 二分答案
  - 线段树
  - 平衡树
date: 2020-11-06 11:41:37
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101630)

先二分答案，求出有多少方法的结果比二分的值要小。

从左到右枚举 $x$，令只选了一个区间 $x$ 的答案为 $now$，维护选每个 $y$ 强度会增加多少。当 $x$ 右移时，先维护好 $now$ 的变化，然后 修改 $y\in(x,x+R)$ 的权值，因为这个区间是右移的，所以可以将当前区间内的 $y$ 维护在集合中，然后整体加就可以了。

使用平衡树或权值线段树来维护有多少方法的结果比二分的值要小，时间复杂度 $O(n\log^2n)$。

<!--more-->

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
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
using namespace __gnu_pbds;
tree<pair<ll,int>,null_type,less<pair<ll,int> >,rb_tree_tag,tree_order_statistics_node_update> t1,t2;
int n,R,K,a[N],b[N],c[N];
ll val[N],in[N];
ll check(ll lim){
	ll now=0,S=0,tag=0;
	for(int i=1;i<R;i++) now+=b[i];
	for(int i=R;i<=n;i++) now+=a[i];
	for(int i=1;i<=n;i++) val[i]=val[i-1]+(i<R?c[i]-b[i]:b[i]-a[i]);
	t1.clear();t2.clear();
	for(int i=1;i<R&&i+R-1<=n;i++){
		in[i]=val[i+R-1]-val[i-1];
		t1.insert(make_pair(in[i],i));
	}
	for(int i=R;i+R-1<=n;i++)
		t2.insert(make_pair(val[i+R-1]-val[i-1],i));
	for(int i=1;i+R-1<=n;i++){
		now+=b[i+R-1]-a[i+R-1]-b[i-1]+a[i-1];
		if(i+R-1+R-1<=n){
			in[i+R-1]=val[i+R+R-2]-val[i+R-2];
			t2.erase(make_pair(in[i+R-1],i+R-1));
			in[i+R-1]-=tag;
			t1.insert(make_pair(in[i+R-1],i+R-1));
		}
		t1.erase(make_pair(in[i],i));
		tag+=(c[i+R-1]-b[i+R-1])-(b[i+R-1]-a[i+R-1]);
		S+=t1.order_of_key(make_pair(lim-now-tag,n+1))+t2.order_of_key(make_pair(lim-now,n+1));
	}
	return S;
}
int main(){
	read(n);read(R);read(K);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1;i<=n;i++) read(b[i]);
	for(int i=1;i<=n;i++) read(c[i]);
	ll l=0,r=1e11;
	while(l+1<r){
		ll mid=l+r>>1;
		if(check(mid)>=K) r=mid;
		else l=mid;
	}
	cout<<r<<'\n';
	return 0;
}
```

