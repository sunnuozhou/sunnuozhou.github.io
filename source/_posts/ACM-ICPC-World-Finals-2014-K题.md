---
title: ACM ICPC World Finals 2014 K题
tags:
  - OI
  - codeforces
  - 倍增
  - 贪心
date: 2020-10-22 11:43:06
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/gym/101221)

先破环成链，将被包含的区间都去掉。

可以注意到，在选了一个区间后，它的后继区间是可以确定的，将其求出来，是一棵树。

在树上倍增求出答案，时间复杂度 $O(k\log k)$。

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
const int N = 1001000;
pair<int,int> p[N];
int n,m,cnt,ans,fa[21][N],dep[N];
int main(){
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int l,r;read(l);read(r);
		if(l>r) r+=n;
		p[i]=make_pair(l,r);
		if(r-l+1>=n){puts("1");return 0;}
	}
	sort(p+1,p+m+1);
	int mx=0;
	for(int i=1;i<=m;i++){
		if(mx>p[i].second) continue;
		mx=max(mx,p[i].second);
		p[++cnt]=make_pair(p[i].first,p[i].second);
	}
	int pos=1;
	for(int i=2;i<=cnt;i++){
		while(pos<i&&p[i].first>p[pos].second+1) pos++;
		if(pos<i) fa[0][i]=pos,dep[i]=dep[pos]+1;
	}
	for(int i=1;i<=20;i++)
		for(int j=1;j<=cnt;j++)
			fa[i][j]=fa[i-1][fa[i-1][j]];
	int ans=m+1;
	for(int i=1;i<=cnt;i++){
		int x=i;
		for(int j=20;~j;j--)
			if(p[i].second-p[fa[j][x]].first+1<n) x=fa[j][x];
		x=fa[0][x];
		if(x) ans=min(ans,dep[i]-dep[x]+1);
	}
	if(ans>m) puts("impossible");
	else printf("%d\n",ans);
	return 0;
}
```

