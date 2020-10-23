---
title: ACM ICPC World Finals 2015 H题
tags:
  - OI
  - codeforces
  - DP
date: 2020-10-23 10:54:40
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101239)

考虑到这个图形是可以缩放的，记 $f_i$ 表示放了 $i$ 个井的答案，转移时解一个二次方程就好了。

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
double W,H,f[N],w[N];
int n;
int main(){
	read(W);read(H);read(n);
	double k=H/W;
	f[0]=(1+k)*(1+k)/4;
	for(int i=1;i<=n;i++){
		double a=-(1-k)*(1-k)/4-k+0.5+f[i-1];
		double b=(k*k-1)/2;
		double c=(1+k)*(1+k)/4;
		double x=b/(-2*a);
		w[i]=x;
		f[i]=a*x*x+b*x+c;
	}
	printf("%.9lf\n",f[n]*W*W);
	for(int i=n;i>1;i--) w[i-1]*=w[i];
	for(int i=1;i<=n&&i<=10;i++) printf("%.9lf\n",w[i]*W);
	return 0;
}
```

