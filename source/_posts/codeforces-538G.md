---
title: codeforces 538G
tags:
  - OI
  - codeforces
  - 构造
date: 2020-01-21 10:24:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/538/problem/G)

对于一组 $(t,x,y)$ 将坐标转为 $(\frac{x+y+t}{2},\frac{x-y+t}{2})$。那么每一次移动就变成了 $x$ 坐标上 $+0/+1$，$y$ 坐标上 $+0/+1$，可以分开讨论。下面以 $x$ 坐标为例。

令 $S$ 为一个周期内增加的量，$s_i$ 表示一个周期的前$i$个时刻增加的量。可以列出等式 $s_{t_i\ mod\  L}=X_i-S\times\lfloor \frac{t_i}{L}\rfloor$。

把等式按 $t_i\ mod\ L$ 排序，相邻两项相减，可以得到若干不等式，形如 $0\le k_2\times S+k_3\le k_1$，合并后的不等式若有解，随意取一组解即可，求出$S$后即可算出所有$s_i$。

时间复杂度 $O(n\log n)$

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
const int N = 2001000;
struct node{ll w,k,c;}a[N],b[N];
int s1[N],s2[N],n,L;
void fail(){puts("NO");exit(0);}
ll ceil(ll a,ll b){
	if(a<0) a=-a,b=-b;
	if(b<0) return a/b;
	return (a+b-1)/b;
}
ll floor(ll a,ll b){
	if(a<0) a=-a,b=-b;
	if(b<0) return (a+b-1)/b;
	return a/b;
}
void solve(node*a,int*ans){
	sort(a+1,a+n+1,[](node a,node b){return a.w<b.w;});
	a[n+1]={L,-1,0};
	ll l=0,r=L;
	for(int i=0;i<=n;i++){
		ll k1=a[i+1].w-a[i].w,k2=-a[i+1].k+a[i].k,k3=a[i+1].c-a[i].c;
		if(k2>0){
			l=max(l,ceil(-k3,k2));
			r=min(r,floor(k1-k3,k2));
		}
		if(k2<0){
			l=max(l,ceil(k1-k3,k2));
			r=min(r,floor(-k3,k2));
		}
		if(l>r||!k2&&(k3<0||k3>k1)) fail();
	}
	for(int i=0;i<=n;i++){
		ll now=(a[i+1].c-a[i+1].k*l)-(a[i].c-a[i].k*l);
		for(int j=a[i].w+1;j<=a[i].w+now;j++)
			ans[j]=1;
	}
}
int main(){
	read(n);read(L);
	for(int i=1;i<=n;i++){
		ll t,x,y;
		read(t);read(x);read(y);
		if(x+y+t&1) fail();
		a[i]={t%L,t/L,(x+y+t)/2};
		b[i]={t%L,t/L,(x-y+t)/2};
	}
	solve(a,s1);
	solve(b,s2);
	for(int i=1;i<=L;i++)
		putchar("LDUR"[s1[i]<<1|s2[i]]);
	puts("");
	return 0;
}
```

