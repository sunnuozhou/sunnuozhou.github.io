---
title: ACM ICPC Northeastern European Regional Contest 2015 L题
tags:
  - OI
  - codeforces
  - 辛普森积分
date: 2020-11-17 12:12:54
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100553/)

直接辛普森积分即可，注意将两边的半球和中间的圆柱分开了积分，防止hack。

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
const double Pi=acos(-1);
double R,D,T,H,L,K,A;
double calc(double r,double d){
	if(d<-r) return 0;
	if(d>r) return r*r*Pi;
	double ang=acos(d/r);
	return Pi*r*r-ang*r*r+d*sqrt(r*r-d*d);
}
double get_val(double x){
	double r;
	if(0<=x&&x<=L) r=D;
	else if(x<=0) r=sqrt(R*R-(A-x)*(A-x));
	else r=sqrt(R*R-(A+x-L)*(A+x-L));
	if(fabs(L-T)<1e-9) return x<=H?r*r*Pi:0.;
	return calc(r,-x*T/K+H*L/K-D);
}
double get_integral(double l,double r){
	double mid=(l+r)/2;
	double a=get_val(l),b=get_val(mid),c=get_val(r);
	return (a+4*b+c)*(r-l)/6;
}
double simpson(double l,double r){
	if(r<l) return 0;
	double mid=(l+r)/2;
	double now=get_integral(l,r);
	double nxt=get_integral(l,mid)+get_integral(mid,r);
	if(fabs(now-nxt)<1e-8) return nxt;
	return simpson(l,mid)+simpson(mid,r);
}
int main(){
	freopen("damage.in","r",stdin);
	freopen("damage.out","w",stdout);
	read(D);read(L);read(R);read(T);read(H);
	D/=2;A=sqrt(R*R-D*D);K=sqrt(L*L-T*T);
	printf("%.3lf\n",(simpson(-R+A+1e-9,0)+simpson(0,L)+simpson(L,L+R-A-1e-9))/1000000);
	return 0;
}
```

