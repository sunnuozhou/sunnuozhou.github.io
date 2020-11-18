---
title: ACM ICPC Northeastern European Regional Contest 2014 I题
tags:
  - OI
  - codeforces
  - 树状数组
date: 2020-11-18 11:00:51
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100553)

如果一个位置被移动了，那么它就等于被删除了，不会有任何影响。

令 $p[x[i]]=i$，那么可以发现，答案就是找一个最长的先上升再下降的子序列，直接上树状数组即可。

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
int p[N],n,w[N],s[N];
struct BIT{
	int c[N];
	void modify(int x,int k){
		for(int i=x;i<=n;i+=i&-i) c[i]=max(c[i],k);
	}
	int query(int x){
		int ans=0;
		for(int i=x;i;i-=i&-i) ans=max(ans,c[i]);
		return ans;
	}
}b1,b2;
int main(){
	freopen("improvements.in","r",stdin);
	freopen("improvements.out","w",stdout);
	read(n);
	int ans=0;
	for(int i=1;i<=n;i++)
		read(w[i]),p[w[i]]=i;
	for(int i=1;i<=n;i++){
		s[i]=b1.query(p[i])+1;
		b1.modify(p[i],s[i]);
	}
	for(int i=n;i;i--){
		int sum=b2.query(p[i])+1;
		b2.modify(p[i],sum);
		ans=max(ans,sum+s[i]-1);
	}
	cout<<ans<<'\n';
	return 0;
}


```

