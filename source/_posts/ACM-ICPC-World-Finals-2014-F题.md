---
title: ACM ICPC World Finals 2014 F题
tags:
  - OI
  - codeforces
  - 计算几何
  - 二分答案
date: 2020-10-21 10:52:00
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101221/)

首先二分答案，检测对于一个 $T$，存不存在一个答案小于等于 $T$。

接下来，我们改变一下行动顺序，令Nadia先走 $T$ 的时间，然后令送信不需要时间，但是距离不超过 $T$。可以证明，如果有解，那么原问题也有一个 $T$ 以内的解。

考虑把折线拆成若干线段，对每一对Misha和Nadia同时开始，同时结束的线段对进行讨论。可以使用三分的方法求出相距最近的时刻（貌似也可以用计算几何的方法，但我不会），需要注意精度和时间。

时间复杂度 $O(n\log^2 V)$。

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
const double eps=1e-8;
struct point{
	double x,y;
	double len(){
		return sqrt(x*x+y*y);
	}
};
point operator + (point a,point b){return point{a.x+b.x,a.y+b.y};}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
point operator * (point a,double x){return point{a.x*x,a.y*x};}
point move_p(point a,point b,double x){
	return a+(b-a)*(x/(b-a).len());
}
struct Line{
	point p[N],now;
	int n,pos;
	double sum;
	void init(){
		read(n);
		for(int i=1;i<=n;i++)
			read(p[i].x),read(p[i].y);
		sum=0;
		for(int i=1;i<n;i++) sum+=(p[i+1]-p[i]).len();
	}
	void begin(){
		pos=1;now=p[1];
	}
	bool end(){return pos==n;}
	point nxt(){
		return p[pos+1];
	}
	void move_nxt(){
		pos++;now=p[pos];
	}
	void move(double T){
		while(!end()&&T>eps){
			if(T>=(nxt()-now).len()){
				T-=(nxt()-now).len();
				move_nxt();
				continue;
			}
			now=move_p(now,nxt(),T);
			T=0;
		}
	}
}L1,L2;
bool calc(point a1,point a2,point b1,point b2,double T){
	double l=0,r=(a2-a1).len();
	double ans=min((b1-a1).len(),(b2-a2).len());
	if(ans<T+eps) return 1;
	int lim=30;
	for(int i=1;i<lim;i++){
		double k1=(l*2+r)/3,k2=(l+r*2)/3;
		double r1=(move_p(a1,a2,k1)-move_p(b1,b2,k1)).len();
		double r2=(move_p(a1,a2,k2)-move_p(b1,b2,k2)).len();
		if(r1<r2) r=k2,ans=min(ans,r1);
		else l=k1,ans=min(ans,r2);
		if(ans<T+eps) return 1;
		if(i==25&&fabs(ans-T)<1) lim+=15;
		if(i==43&&fabs(ans-T)<1e-3) lim+=15;
	}
	return ans<T+eps;
}
bool check(double T){
	double t1=0,t2=T;
	L1.begin();L2.begin();
	L2.move(T);
	while(1){
		double len1=(L1.nxt()-L1.now).len();
		double len2=(L2.nxt()-L2.now).len();
		if(fabs(len1-len2)<eps){
			if(calc(L1.now,L1.nxt(),L2.now,L2.nxt(),T)) return 1;
			L1.move_nxt();
			L2.move_nxt();
		}
		else if(len1<len2){
			point P=L2.now;L2.move(len1);
			if(calc(L1.now,L1.nxt(),P,L2.now,T)) return 1;
			L1.move_nxt();
		}
		else{
			point P=L1.now;L1.move(len2);
			if(calc(L2.now,L2.nxt(),P,L1.now,T)) return 1;
			L2.move_nxt();
		}
		if(L1.end()||L2.end()) break;
	}
	return 0;
}
int main(){
	L1.init();
	L2.init();
	if((L1.p[1]-L2.p[L2.n]).len()>L2.sum+eps){cout<<"impossible\n";return 0;}
	double l=-1e-10,r=L2.sum+eps;
	check(2.1);
	while(l+1e-7<r){
		double mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%.6lf\n",r);
	return 0;
}
```

