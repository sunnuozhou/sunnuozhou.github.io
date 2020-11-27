---
title: ACM ICPC World Finals 2015 J题
tags:
  - OI
  - codeforces
  - 多项式乘法
date: 2020-10-23 10:54:43
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101239)

考虑在 $X\times Y$ 的矩形中，剪出一个 $(a,0),(b,Y),(0,c),(X,d)$ 的平行四边形，其中 $a+b=x,c+d=Y$，其面积为 $ab+cd$。

记 $f_n$ 表示 $ab=n$ 的个数，$f\times f$ 就是答案。

不知道CF编译器怎么回事，我本地0.2s的FFT在CF上要10s，很恐怖。

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
const int N = 501000;
namespace FFT{
	const double Pi=acos(-1);
	int r[N*4],maxn,len;
	struct comp{double x,y;}g1[N*4],g2[N*4];
	vector<comp> wn[25];
	comp operator * (comp a,comp b){return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
	comp operator + (comp a,comp b){return {a.x+b.x,a.y+b.y};}
	comp operator - (comp a,comp b){return {a.x-b.x,a.y-b.y};}
	void build(int n){
		maxn=1;len=0;while(maxn<=n) maxn<<=1,len++;
		for(int i=0;i<maxn;i++) r[i]=r[i>>1]>>1|(i&1)<<len-1;
		for(int mid=1,p=0;mid<maxn;mid<<=1,p++){
			wn[p].resize(mid);
			for(int j=0;j<mid;j++) wn[p][j]={cos(j*Pi/mid),sin(j*Pi/mid)};
		}
	}
	void fft(comp *a,int tag){
		for(int i=0;i<maxn;i++) if(r[i]>i) swap(a[i],a[r[i]]);
		for(int mid=1,p=0;mid<maxn;mid<<=1,p++){
			for(int j=0;j<mid;j++) wn[p][j].y=tag*wn[p][j].y;
			for(int l=0;l<maxn;l+=mid<<1)
				for(int i=l;i<l+mid;i++){
					comp x=a[i],y=a[i+mid]*wn[p][i-l];
					a[i]=x+y;a[i+mid]=x-y;
				}
			for(int j=0;j<mid;j++) wn[p][j].y=tag*wn[p][j].y;
		}
	}
	template<typename tn> void turn(tn *a,comp *c,int ed=maxn-1){
		for(int i=ed+1;i<maxn;i++) c[i]={0,0};
		for(int i=0;i<=ed;i++) c[i]={1.*a[i],0};
		fft(c,1);
	}
	void mul(comp *a,comp *b){
		for(int i=0;i<maxn;i++) a[i]=a[i]*b[i];
	}
	template<typename tn> void iturn(tn *a,comp *c){
		fft(c,-1);
		for(int i=0;i<maxn;i++) a[i]=(c[i].x)/maxn+0.5;
	}
	template<typename tn> void mult(tn *a,tn *b,tn *c,int n,int m){
		build(n+m);
		turn(a,g1,n);turn(b,g2,m);
		mul(g1,g2);iturn(c,g1);
	}
}
int n,f[N],ans[N*4];
int main(){
	read(n);
	int maxn=500000;
	for(int i=1;i<=maxn;i++)
		for(int j=i;j<=maxn;j+=i)
			f[j]++;
	FFT::mult(f,f,ans,maxn,maxn);
	while(n--){
		int l,r;read(l);read(r);
		int k=0;
		for(int i=l;i<=r;i++)
			if(ans[i]>ans[k]) k=i;
		cout<<k<<' '<<ans[k]<<'\n';
	}
	return 0;
}

```

