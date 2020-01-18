---
title: codeforces 685C
tags:
  - OI
  - codeforces
  - 二分答案
date: 2020-01-16 08:03:24
categories: 解题报告
top:
---

[题目描述](https://codeforces.com/contest/685/problem/C)

先二分答案，考虑对于一个答案如何检验。

二分答案后，一个点的限制就是在八个方向各有一个限制。而多个点的限制就是每个方向的限制取最大值。整理限制可以得到一下式子：

$l_0\le x+y+z \le r_0$

$l_1\le -x+y+z \le r_1$

$l_2\le x-y+z \le r_2$

$l_3\le x+y-z \le r_3$

设$a=-x+y+z,b=x-y+z,c=x+y-z$，那么限制变为

$l_0\le a+b+c \le r_0$

$l_1\le a \le r_1$

$l_2\le b \le r_2$

$l_3\le c \le r_3$

因为$x=\frac{b+c}{2},y=\frac{a+c}{2},z=\frac{a+b}{2}$，所以$a,b,c$必须同奇或同偶，分类讨论即可。

时间复杂度$O(T(n+\log V))$，其中$V$为值域。

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
ll lim[8],lm[8];
int n;
struct point{
	ll x,y,z;
	ll getval(int k){
		return x*(k&1?-1:1)+y*(k>>1&1?-1:1)+z*(k>>2&1?-1:1);
	}
}p[N],ans;
bool chk(int tag,ll*lim){
	ll l[4]={(-lim[7]+1-3*tag)>>1,(-lim[6]+1-tag)>>1,(-lim[5]+1-tag)>>1,(-lim[3]+1-tag)>>1};
	ll r[4]={(lim[0]-3*tag)>>1,(lim[1]-tag)>>1,(lim[2]-tag)>>1,(lim[4]-tag)>>1};
	ll a=l[1],b=l[2],c=l[3];
	for(int i=0;i<4;i++) if(r[i]<l[i]) return 0;
	if(a+b+c>r[0]) return 0;
	if(a+b+c<l[0]){
		a=min(r[1],l[0]-b-c);
		b=min(r[2],l[0]-a-c);
		c=min(r[3],l[0]-a-b);
	}
	if(a+b+c<l[0]) return 0;
	ans={b+c+tag,a+c+tag,a+b+tag};
	return 1;
}
bool check(ll len){
	memcpy(lm,lim,sizeof(lm));
	for(int i=0;i<8;i++) lm[i]+=len;
	if(chk(0,lm)) return 1;
	if(chk(1,lm)) return 1;
	return 0;
}
int main(){
	int T;read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++)
			read(p[i].x),read(p[i].y),read(p[i].z);
		memset(lim,63,sizeof(lim));
		for(int i=1;i<=n;i++)
			for(int j=0;j<8;j++)
				lim[j]=min(lim[j],p[i].getval(j));
		ll l=-1,r=4e18l+1;
		while(l+1<r){
			ll mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid;
		}
		check(r);
		cout<<ans.x<<' '<<ans.y<<' '<<ans.z<<'\n';
	}
	return 0;
}
```

