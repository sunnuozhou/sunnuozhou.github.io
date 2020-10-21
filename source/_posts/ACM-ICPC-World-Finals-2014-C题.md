---
title: ACM ICPC World Finals 2014 C题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-10-19 12:15:23
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221/attachments)

以多边形的左支点和右支点为转轴，求一次力矩，然后分类讨论即可。

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
struct point{
	int x,y;
}p[N];
int n;
ll operator * (point a,point b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
int main(){
	read(n);
	int L=1e9,R=-1e9,pl=0,pr=0;
	for(int i=1;i<=n;i++){
		int x,y;read(x);read(y);p[i]={x,y};
		if(p[i].y==0){
			if(p[i].x<L) L=p[i].x,pl=i;
			if(p[i].x>R) R=p[i].x,pr=i;
		}
	}
	p[n+1]=p[1];
	ll ans1=0,ans2=0;
	for(int i=1;i<=n;i++){
		ll s1=(p[i]-p[pl])*(p[i+1]-p[pl]);
		ll s2=(p[i]-p[pr])*(p[i+1]-p[pr]);
		ans1+=s1*(p[i].x+p[i+1].x-2*L);
		ans2+=s2*(p[i].x+p[i+1].x-2*R);
	}
	int flag=0;
	for(int i=1;i<=n;i++)
		flag+=p[i]*p[i+1];
	if(flag<0) ans1*=-1,ans2*=-1;
	if(L<=p[1].x&&p[1].x<=R){
		if(ans1<0&&L==p[1].x||ans2>0&&R==p[1].x){puts("unstable");return 0;}
		if(ans1>=0&&ans2<=0){puts("0 .. inf");return 0;}
		if(ans1<0){
			printf("%d .. inf\n",(int)floor(1.*ans1/(L-p[1].x)/6));
			return 0;
		}
		else{
			printf("%d .. inf\n",(int)floor(1.*ans2/(R-p[1].x)/6));
			return 0;
		}
	}
	if(p[1].x<L){
		if(ans1<0){puts("unstable");return 0;}
		printf("%d .. %d\n",max(0,(int)floor(1.*ans2/(R-p[1].x)/6)),(int)ceil(1.*ans1/(L-p[1].x)/6));
		return 0;
	}
	else{
		if(ans2>0){puts("unstable");return 0;}
		printf("%d .. %d\n",max(0,(int)floor(1.*ans1/(L-p[1].x)/6)),(int)ceil(1.*ans2/(R-p[1].x)/6));
	}
	return 0;
}
```

