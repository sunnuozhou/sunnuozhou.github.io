---
title: ACM ICPC World Finals 2017 A题
tags:
  - OI
  - codeforces
  - 计算几何
date: 2020-10-29 11:48:55
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242)

结论：答案线段上至少有两个顶点。

枚举这两个顶点，对每条边界检查有没有拦住这条线。

时间复杂度 $O(n^3)$。

本人计算几何水平不行，写的非常冗长。

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
	lld x,y;
	lld len(){return sqrtl(x*x+y*y);}
}p[N];
int n;
lld ans;
point operator + (point a,point b){return {a.x+b.x,a.y+b.y};}
point operator - (point a,point b){return {a.x-b.x,a.y-b.y};}
point operator * (point a,lld b){return {a.x*b,a.y*b};}
lld operator * (point a,point b){return a.x*b.y-a.y*b.x;}
lld operator ^ (point a,point b){return a.x*b.x+a.y*b.y;}
bool operator == (point a,point b){return fabs(a.x-b.x)<1e-9&&fabs(a.y-b.y)<1e-9;}
bool operator != (point a,point b){return !(a==b);}
int get_pt(point a,point b,point c,point d,point&pt){
	lld k1=(a-c)*(d-c),k2=(b-c)*(d-c);
	if(fabs(k1-k2)<1e-9) return 0;
	pt=a+(b-a)*(k1/(k1-k2));
	return 1;
}
bool check_order(point a,point b,point c){
	lld k1=atan2(a.y,a.x),k2=atan2(b.y,b.x),k3=atan2(c.y,c.x);
	if(k1>=k2&&k2>=k3) return 1;
	if(k1<k2&&k2>=k3&&k3>=k1) return 1;
	if(k1>=k2&&k2<k3&&k3>=k1) return 1;
	return 0;
}
void solve(int x,int y){
	if(!check_order(p[x-1]-p[x],p[y]-p[x],p[x+1]-p[x])) return;
	lld lenx=1e9,leny=1e9;
	for(int i=1;i<=n;i++)
		if(fabs((p[i]-p[x])*(p[y]-p[x]))<1e-10){
			int flag=((p[y]-p[x])*(p[i-1]-p[x])>0)==((p[y]-p[x])*(p[i+1]-p[x])>0);
			if(fabs((p[i-1]-p[x])*(p[y]-p[x]))<1e-10){
				if((p[i]-p[x]).len()>(p[i-1]-p[x]).len()) flag=(p[i]-p[x])*(p[i+1]-p[x])<0;
				else flag=(p[i]-p[x])*(p[i+1]-p[x])>0;
			}
			if(fabs((p[i+1]-p[x])*(p[y]-p[x]))<1e-10){
				if((p[i]-p[y]).len()>(p[i+1]-p[y]).len()) flag=(p[i]-p[y])*(p[i-1]-p[y])>0;
				else flag=(p[i]-p[y])*(p[i-1]-p[y])<0;
			}
//			cerr<<i<<' '<<flag<<'\n';
			if(flag) continue;
			if(p[i]!=p[x]&&p[i]!=p[y]&&(p[i]-p[x]).len()+(p[i]-p[y]).len()<(p[x]-p[y]).len()+1e-9) return;
			if((p[i]-p[x]).len()<(p[i]-p[y]).len()) lenx=min(lenx,(p[i]-p[x]).len());
			else leny=min(leny,(p[i]-p[y]).len());
		}
//	cerr<<lenx<<' '<<leny<<'\n';
	for(int i=1;i<=n;i++){
		if(fabs((p[i]-p[x])*(p[y]-p[x]))<1e-10) continue;
		if(fabs((p[i+1]-p[x])*(p[y]-p[x]))<1e-10) continue;
		if(((p[y]-p[x])*(p[i]-p[x])>0)==((p[y]-p[x])*(p[i+1]-p[x])>0)) continue;
		point pt;
		if(!get_pt(p[x],p[y],p[i],p[i+1],pt)) continue;
		if((pt-p[x]).len()+(pt-p[y]).len()<(p[x]-p[y]).len()+1e-9) return;
		if((pt-p[x]).len()<(pt-p[y]).len()) lenx=min(lenx,(pt-p[x]).len());
		else leny=min(leny,(pt-p[y]).len());
	}
	if(lenx>1e8) lenx=0;
	if(leny>1e8) leny=0;
//	cerr<<x<<' '<<y<<' '<<lenx<<' '<<leny<<' '<<(p[x]-p[y]).len()<<'\n';
	ans=max(ans,(p[x]-p[y]).len()+lenx+leny);
}
int main(){
	read(n);
	for(int i=1;i<=n;i++) read(p[i].x),read(p[i].y);
	p[n+1]=p[1];p[0]=p[n];
//	solve(2,3);return 0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			solve(i,j);
	printf("%.8Lf\n",ans);
	return 0;
}
```

