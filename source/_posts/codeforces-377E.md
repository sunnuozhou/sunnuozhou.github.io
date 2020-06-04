---
title: codeforces 377E
tags:
  - OI
  - codeforces
  - 决策单调性
  - 斜率优化
  - DP
  - 贪心
date: 2020-06-03 13:56:01
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/377/problem/E)

首先，将数组按 $c_i$ 从小到大排序，如果存在 $c_i<c_j,v_i>v_j$，那么显然 $j$ 没有用，所以 $v_i$ 单调。

考虑暴力DP，记 $f_i$ 表示最少几秒可以得到 $i$，$g_i$ 表示在最少时间得到 $i$ 的情况下，最多可以剩多少钱，转移时枚举上一个得到的工厂是谁。

这个DP可以斜率优化或者决策单调性优化。

时间复杂度 $O(n\log n)$。

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
ll S;
int n;
struct node{
	ll c,v;
}a[N];
struct tran{
	int l,r;
	int num;
}q[N];
ll f[N],lft[N];
bool check(int k1,int k2,int pos){
	ll tim1=(a[pos].c-lft[k1]+a[k1].v-1)/a[k1].v+f[k1];
	ll tim2=(a[pos].c-lft[k2]+a[k2].v-1)/a[k2].v+f[k2];
	if(tim1>tim2) return 1;
	if(tim1<tim2) return 0;
	ll Lft1=(tim1-f[k1])*a[k1].v+lft[k1]-a[pos].c;
	ll Lft2=(tim2-f[k2])*a[k2].v+lft[k2]-a[pos].c;
	if(Lft1<Lft2) return 1;
	return 0;
}
int main(){
	read(n);read(S);
	for(int i=1;i<=n;i++)
		read(a[i].v),read(a[i].c);
	sort(a+1,a+n+1,[](node a,node b){
		return a.c<b.c||a.c==b.c&&a.v>b.v;
	});
	vector<node> V;
	int mx=0;
	for(int i=1;i<=n;i++){
		if(mx<a[i].v){
			V.push_back(a[i]);
			mx=a[i].v;
		}
	}
	while(V.size()&&V.back().c>=S) V.pop_back();
	n=V.size();
	for(int i=1;i<=n;i++) a[i]=V[i-1];
	a[++n]={S,0};
	/*for(int i=2;i<=n;i++){
		f[i]=1e18;
		for(int j=1;j<i;j++){
			if(lft[j]>=a[i].c) continue;
			ll tim=(a[i].c-lft[j]+a[j].v-1)/a[j].v+f[j];
			ll Lft=(tim-f[j])*a[j].v+lft[j]-a[i].c;
			if(tim<f[i]||tim==f[i]&&Lft>lft[i]){
				f[i]=tim;lft[i]=Lft;
			}
		}
	}*/
	int L=1,R=1;q[L]={1,n,1};
	for(int i=2;i<=n;i++){
		while(L<=R&&q[L].r<i) L++;
		if(L>R){cerr<<"!!\n";return 0;}
		if(q[L].l<i) q[L].l=i;
		int pos=q[L].num;
		f[i]=(a[i].c-lft[pos]+a[pos].v-1)/a[pos].v+f[pos];
		lft[i]=(f[i]-f[pos])*a[pos].v+lft[pos]-a[i].c;
		if(i==n) break;
		while(L<=R&&check(q[R].num,i,q[R].l)) R--;
		if(L>R){
			q[++R]={i,n,i};
			continue;
		}
		int l=q[R].l,r=q[R].r+1;
		while(l+1<r){
			int mid=l+r>>1;
			if(check(q[R].num,i,mid)) r=mid;
			else l=mid;
		}
		q[R].r=l;
		if(r<=n) q[++R]={r,n,i};
	}
	cout<<f[n]<<'\n';
	return 0;
}

```

