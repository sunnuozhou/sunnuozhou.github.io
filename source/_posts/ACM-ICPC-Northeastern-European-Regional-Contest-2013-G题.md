---
title: ACM ICPC Northeastern European Regional Contest 2013 G题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-11-20 10:42:50
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100307)

答案是 整块土地照到的光加最高的塔照到的光 和 所有塔照到的光的和 的最小值。

考虑构造方案，如果是最高的那块就放在整片土地最后可以照到光的地方，否则就紧接着上一个放在自己底部不会被遮挡的地方。

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
int n,m;
double ang,h[N],K;
struct point{
	double x,y;
}p[N];
double operator * (point a,point b){return a.x*b.y-a.y*b.x;}
point operator - (point a,point b){return point{a.x-b.x,a.y-b.y};}
double calc(point pt){return pt.y+pt.x*K;}
int getpos(double H,point a,point b,double&w){
	double k=(b.y-a.y)/(b.x-a.x),B=a.y-a.x*k;
	w=(H-B)/(k+K);
	if(fabs(k+K)<1e-9||w<a.x-1e-9||w>b.x+1e-9) return 0;
	return 1;
}
int main(){
	freopen("green.in","r",stdin);
	freopen("green.out","w",stdout);
	read(n);read(m);read(ang);
	double sum=0,mx=0;
	for(int i=1;i<=n;i++)
		read(h[i]),sum+=h[i],mx=max(mx,h[i]);
	K=tan(ang/180*acos(-1));
	int pos=0;
	for(int i=1;i<=m;i++){
		read(p[i].x),read(p[i].y);
		if(!pos||calc(p[i])>calc(p[pos])) pos=i;
	}
/*	double w;
	cerr<<getpos(calc(p[1]),p[1],p[2],w)<<'\n';
	cerr<<w<<'\n';
	return 0;*/
	printf("%.9lf\n",min(sum,mx+calc(p[pos])-calc(p[1])));
	double S=calc(p[1]);
	for(int i=1,j=1;i<=n;i++){
		if(h[i]==mx){
			mx=1e100;
			printf("%.12lf\n",p[pos].x);
			continue;
		}
		double w=0;
		while(j<pos&&!getpos(S,p[j],p[j+1],w)) j++;
		if(j==pos) w=p[pos].x;
		printf("%.12lf\n",w);
		S+=h[i];
	}
	return 0;
}


```

