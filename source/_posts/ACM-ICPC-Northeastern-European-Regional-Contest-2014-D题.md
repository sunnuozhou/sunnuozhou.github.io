---
title: ACM ICPC Northeastern European Regional Contest 2014 D题
tags:
  - OI
  - codeforces
  - 二分答案
date: 2020-11-17 12:13:02
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

二分答案，考虑check，找到以每个位置为最高点时，左边和右边分别是哪两个位置把它拦住的。

在求出这个后，就可以直接计算每个位置作最高点用的格子个数了。

考虑怎么求是谁拦的它，以左边为例，从左到右求出每个位置从哪里开始可以拦人，然后前缀 $\max$ 即可。

时间复杂度 $O(n\log m)$。

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
int n,l[N],r[N],a[N];
ll tag[N];
ll m,s[N];
bool check(ll h){
	for(int i=1;i<=n;i++) tag[i]=0;
	ll mx=0,mn=n+1;
	for(int i=1;i<=n;i++){
		mx=max(mx,tag[i]);
		if(a[i]>=h) return 1;
		if(h-a[i]+i<=n) tag[h-a[i]+i]=i;
		l[i]=mx;
	}
	for(int i=1;i<=n;i++) tag[i]=n+1;
	for(int i=n;i;i--){
		mn=min(mn,tag[i]);
		if(a[i]+i-h>0) tag[a[i]+i-h]=i;
		r[i]=mn;
	}
	for(int i=1;i<=n;i++){
		if(l[i]==0||r[i]>n) continue;
//		cerr<<i<<' '<<l[i]<<' '<<r[i]<<'\n';
		ll k1=i-l[i],k2=r[i]-i-1;
		ll S=(h+h-k1+1)*k1/2+(h-1+h-k2)*k2/2;
//		cerr<<S<<'\n';
		if(S-s[r[i]-1]+s[l[i]]<=m) return 1;
	}
	return 0;
}
int main(){
	freopen("landscape.in","r",stdin);
	freopen("landscape.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++){
		read(a[i]),s[i]=s[i-1]+a[i];
	}
	check(7);
//	return 0;
	ll l=0,r=2e9;
	while(l+1<r){
		ll mid=l+r>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	cout<<l<<'\n';
	return 0;
}


```

