---
title: codeforces 704B
tags:
  - OI
  - codeforces
  - DP
  - 解题报告
date: 2020-01-16 10:56:08
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/704/problem/B)

令$a_i+=x_i,b_i-=x_i,c_i+=x_i,d_i-=x_i$，那么从$i$走到$j$的代价是：

$c_i+b_j,j<i$

$d_i+a_j,j>i$

记录$f_{i,j}$表示前$i-1$个点，共有$j$个连通块的最小代价。

转移时枚举第$i$个点从前面还是后面到，向前面还是后面走。为了转移方便，我使终点向起点连了一条边，但要注意这条边必须直接连接两个点，中间不能有其他点。

时间复杂度$O(n^2)$。

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
const int N = 5010;
int n,s,t;
ll f[N][N],a[N],b[N],c[N],d[N],x[N];
void upd(ll&a,ll b){a=min(a,b);}
int main(){
	read(n);read(s);read(t);
	for(int i=1;i<=n;i++) read(x[i]);
	for(int i=1;i<=n;i++) read(a[i]),a[i]+=x[i];
	for(int i=1;i<=n;i++) read(b[i]),b[i]-=x[i];
	for(int i=1;i<=n;i++) read(c[i]),c[i]+=x[i];
	for(int i=1;i<=n;i++) read(d[i]),d[i]-=x[i];
	memset(f,63,sizeof(f));
	f[1][0]=0;
	for(int i=1,flag=0;i<=n;i++){
		if(i==max(s,t)&&flag) flag=0;
		for(int j=1-(i==1);j<i;j++){
			if((i!=s||s<t)&&(i!=t||t<s)) upd(f[i+1][j+1],f[i][j]+b[i]+d[i]);
			if((i!=s||s>t)&&(i!=t||t>s)&&(j>1||i==n&&j==1)) upd(f[i+1][j-1],f[i][j]+a[i]+c[i]);
			if((i!=s||s<t)&&(i!=t||t>s)&&j>(flag&&s<t)) upd(f[i+1][j],f[i][j]+b[i]+c[i]);
			if((i!=s||s>t)&&(i!=t||t<s)&&j>(flag&&s>t)) upd(f[i+1][j],f[i][j]+a[i]+d[i]);
		}
		if(i==min(s,t)&&!flag) flag=1;
	}
	cout<<f[n+1][0]-(s<t?c[t]+b[s]:a[s]+d[t])<<'\n';
	return 0;
}


```

