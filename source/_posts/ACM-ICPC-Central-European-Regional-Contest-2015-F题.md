---
title: ACM ICPC Central European Regional Contest 2015 F题
tags:
  - OI
  - codeforces
  - 计数
date: 2020-11-27 10:22:53
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101480)

将第一行，第一列，和 $C$ 的贡献分开来算。

第一行第一列的贡献可以枚举位置用组合数算。

$C$ 的贡献为：$$C\sum_{i=0}^{n-2}\sum_{j=0}^{n-2}A^iB^j\binom{i+j}{i}$$。

可以用MTT快速计算。

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
const int N = 401000,mod = 1e6+3;
namespace MTT{
	const double Pi=acos(-1);
	int r[N*4],maxn,len;
	struct comp{double x,y;}g[4][N*4];
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
	template<typename tn> void mult(tn *a,tn *b,tn *c,int n,int m){
		build(n+m);
		for(int i=0;i<maxn;i++) for(int j=0;j<4;j++) g[j][i]={0,0};
		for(int i=0;i<=n;i++) g[0][i]={a[i]%40000*1.,0},g[1][i]={a[i]/40000*1.,0};
		for(int i=0;i<=m;i++) g[2][i]={b[i]%40000*1.,0},g[3][i]={b[i]/40000*1.,0};
		fft(g[0],1);fft(g[1],1);fft(g[2],1);fft(g[3],1);
		for(int i=0;i<maxn;i++){
			comp x=g[0][i]*g[2][i],y=g[1][i]*g[2][i]+g[0][i]*g[3][i],z=g[1][i]*g[3][i];
			g[0][i]=x;g[1][i]=y;g[2][i]=z;
		}
		fft(g[0],-1);fft(g[1],-1);fft(g[2],-1);
		for(int i=0;i<maxn;i++)
			c[i]=((ll)(g[0][i].x/maxn+0.5)+(ll)(g[1][i].x/maxn+0.5)%mod*40000+(ll)(g[2][i].x/maxn+0.5)%mod*(1600000000ll%mod))%mod;
	}
}
int n,A,B,C;
ll fac[N],ifac[N],f0[N],f1[N],ans;
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
int main(){
	read(n);read(A);read(B);read(C);
	fac[0]=1;
	for(int i=1;i<=n*2;i++) fac[i]=fac[i-1]*i%mod;
	ifac[n*2]=fp(fac[n*2],mod-2);
	for(int i=n*2;i;i--) ifac[i-1]=ifac[i]*i%mod;
	for(int i=1;i<=n;i++){
		int x;read(x);
		if(i>1) ans=(ans+fp(A,n-1)*fp(B,n-i)%mod*x%mod*fac[n-2+n-i]%mod*ifac[n-2]%mod*ifac[n-i])%mod;
	}
	for(int i=1;i<=n;i++){
		int x;read(x);
		if(i>1) ans=(ans+fp(A,n-i)*fp(B,n-1)%mod*x%mod*fac[n-2+n-i]%mod*ifac[n-2]%mod*ifac[n-i])%mod;
	}
	for(int i=0;i<n-1;i++) f0[i]=fp(A,i)*ifac[i]%mod;
	for(int i=0;i<n-1;i++) f1[i]=fp(B,i)*ifac[i]%mod;
	MTT::mult(f0,f1,f0,n-2,n-2);
	for(int i=0;i<=2*n;i++) ans=(ans+fac[i]*f0[i]%mod*C)%mod;
	cout<<(ans+mod)%mod<<'\n';
	return 0;
}


```

