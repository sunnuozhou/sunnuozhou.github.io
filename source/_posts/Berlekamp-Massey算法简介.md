---
title: Berlekamp-Massey算法简介
tags:
  - OI
  - BM算法
date: 2020-04-22 18:16:41
categories: 教程
top:
---

[模板题链接](https://www.luogu.com.cn/problem/P5487)

## Berlekamp-Massey算法

Berlekamp-Massey算法，简称BM算法，是用来求解一个数列最短线性递推式的算法，时间复杂度为$O(n^2)$。

### 算法流程

记数列为$\{a_1,a_2,..,a_n\}$，只考虑$\{a_1,a_2,..,a_i\}$的最短线性递推为$R_i$，$a_{i+1}$和用$R_i$推算出的下一个数的差为$delta_i$。特别的，$R_0=\{\}$。

现在考虑如果我们已经知道了$R_1,R_2,..R_{i-1}$，如何求$R_i$？

- 如果$delta_{i-1}=0$，那么显然$R_i=R_{i-1}$

- 如果$R_{i-1}$为$\{\}$，那么$R_i=\{0,0,..,0\}$，共$i$个0。

- 否则我们需要对$R_{i-1}$进行调整来得到$R_i$。一个简单的思想是找到一个线性递推式$R'=\{r'_1,r'_2,..,r'_k\}$满足$\sum_{j=1}^kr'_j\times a_{w-j}=0$对所有$k<w<i$成立，并且在$i$处的值为$delta_{i-1}$。那么$R_i$就可以等于$R_{i-1}+R'$。

- 一种可行的构造方案是对于$0\le w<i-1$，可以使$R'=\{0,0,..,0,\frac{delta_{i-1}}{delta_w},-\frac{delta_{i-1}}{delta_w}\times R_w\}$，其中0的个数为$i-w-2$。

- 为了使$R_i$最短，找到一个$w$使得$R'$最短即可。

其中有用的$R_i$只有当前的$R_i$和使$R'$最短的$R_w$，并不需要记录所有$R_i$，空间是$O(n)$的。

用这个方法生成的线性递推正确性是显然的，但我并不会证明一定是最短的。~~但是过了模板题~~

<!--more-->

### 代码

```cpp
void BM(ll *a,int n,vector<ll>&ans){
	ans.clear();
	vector<ll> lst;
	int w=0;ll delta=0;
	for(int i=1;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<ans.size();j++)
			tmp=(tmp+a[i-1-j]*ans[j])%mod;
		if((a[i]-tmp)%mod==0) continue;
		if(!w){
			w=i;delta=a[i]-tmp;
			for(int j=i;j;j--) ans.push_back(0);
			continue;
		}
		vector<ll> now=ans;
		ll mul=(a[i]-tmp)*fp(delta,mod-2)%mod;
		if(ans.size()<lst.size()+i-w) ans.resize(lst.size()+i-w);
		ans[i-w-1]=(ans[i-w-1]+mul)%mod;
		for(int j=0;j<lst.size();j++) ans[i-w+j]=(ans[i-w+j]-mul*lst[j])%mod;
		if((int)now.size()-i<(int)lst.size()-w){
			lst=now;w=i;delta=a[i]-tmp;
		}
	}
}

```

## 特征多项式

### 基本概念

因为模板题要用，就顺带讲一下。

一个$n\times n$矩阵$A$的特征多项式为$f(\lambda)=det(I_n\lambda-A)$，其中$I_n$为$n$阶单位矩阵，$det$为行列式运算。

而一个线性递推矩阵如下：
$$
A=
\left\{
	\begin{matrix}
	a_1 & a_2 & \cdots & a_{n-1} &a_n\\
	1 & 0 & \cdots & 0 & 0 \\
	\vdots & \vdots & \ddots & \vdots& \vdots \\
	0 & 0 & \cdots  & 0 & 0 \\
	0 & 0 & \cdots  & 1 & 0 \\
	\end{matrix} 
\right\}
$$
$$
f(\lambda)=
\left |
	\begin{matrix}
	\lambda-a_1 & -a_2 & \cdots & -a_{n-1} &-a_n\\
	-1 & \lambda & \cdots & 0 & 0 \\
	\vdots & \vdots & \ddots & \vdots& \vdots \\
	0 & 0 & \cdots  & \lambda & 0 \\
	0 & 0 & \cdots  & -1 & \lambda \\
	\end{matrix} 
\right|
$$

展开第一行得:$f(\lambda)=(\lambda-a_1)A_{1,1}+(-a_2)A_{1,2}+\cdots+(-a_n)A_{1,n}$

其中$A_{i,j}$为$A$的代数余子式，显然结果为$f(\lambda)=\lambda^n-\sum_{i=1}^na_i\lambda^{n-i}$

### 实用

现在考虑求递推式的第$m$项，即$A^{m-1}\times\vec H $ 的最后一项。

根据[Cayley-Hamilton定理](https://zh.wikipedia.org/wiki/凱萊–哈密頓定理)可得，$f(A)=0$

于是有$A^{m-1}=g(A)\times f(A)+r(A)$，其中$r(A)$的最高项次数小于$n$。

由于$f(A)=0$，可以得到$A^{m-1}=r(A)$。

这里可以暴力地快速幂算出$r(A)$，也可以使用多项式取模+快速幂的方式~~但我不会~~

现在要求的就是$\sum_{i=0}^{n-1}r_i\times A^i \times \vec H$的最后一项。

其中$A_i\times \vec H$的最后一项为$H_{i+1}$

所以$ans=\sum_{i=0}^{n-1}r_i\times H_{i+1}$

时间复杂度为$O(n^2\log m)$或$O(n\log n\log m)$

### 代码

```cpp
ll calc(int m,vector<ll>&coef,ll*h){
	if(m<=coef.size()) return h[m];
	int k=coef.size();
	static ll f[N],g[N],res[N],p[N];
	p[0]=-1;
	for(int i=1;i<=k;i++) p[i]=coef[i-1];
	for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
	f[0]=1;
	if(k>1) g[1]=1;
	else g[0]=p[0];
	auto mul = [&](ll *a,ll *b,ll *c){
		for(int i=0;i<=2*k;i++) res[i]=0;
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				res[i+j]=(res[i+j]+a[i]*b[j])%mod;
		for(int i=2*k;i>=k;i--)
			if(res[i]%mod)
				for(int j=k;~j;j--)
					res[i-j]=(res[i-j]+res[i]*p[j])%mod;
		for(int i=0;i<2*k;i++) c[i]=res[i];
		return 0;
	};
	for(;m;m>>=1,mul(g,g,g))
		if(m&1) mul(f,g,f);
	ll ans=0;
	for(int i=0;i<k;i++)
		ans=(ans+h[i+1]*f[i])%mod;
	return ans;
}
```

## 模板题代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define lld long ll
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 10010,mod = 998244353;
ll h[N];
int n,m;
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
void BM(ll *a,int n,vector<ll>&ans){
	ans.clear();
	vector<ll> lst;
	int w=0;ll delta=0;
	for(int i=1;i<=n;i++){
		ll tmp=0;
		for(int j=0;j<ans.size();j++)
			tmp=(tmp+a[i-1-j]*ans[j])%mod;
		if((a[i]-tmp)%mod==0) continue;
		if(!w){
			w=i;delta=a[i]-tmp;
			for(int j=i;j;j--) ans.push_back(0);
			continue;
		}
		vector<ll> now=ans;
		ll mul=(a[i]-tmp)*fp(delta,mod-2)%mod;
		if(ans.size()<lst.size()+i-w) ans.resize(lst.size()+i-w);
		ans[i-w-1]=(ans[i-w-1]+mul)%mod;
		for(int j=0;j<lst.size();j++) ans[i-w+j]=(ans[i-w+j]-mul*lst[j])%mod;
		if(now.size()-i<lst.size()-w){
			lst=now;w=i;delta=a[i]-tmp;
		}
	}
}
ll calc(int m,vector<ll>&coef,ll*h){
	if(m<=coef.size()) return h[m];
	int k=coef.size();
	static ll f[N],g[N],res[N],p[N];
	p[0]=-1;
	for(int i=1;i<=k;i++) p[i]=coef[i-1];
	for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
	f[0]=1;
	if(k>1) g[1]=1;
	else g[0]=p[0];
	auto mul = [&](ll *a,ll *b,ll *c){
		for(int i=0;i<=2*k;i++) res[i]=0;
		for(int i=0;i<k;i++)
			for(int j=0;j<k;j++)
				res[i+j]=(res[i+j]+a[i]*b[j])%mod;
		for(int i=2*k;i>=k;i--)
			if(res[i]%mod)
				for(int j=k;~j;j--)
					res[i-j]=(res[i-j]+res[i]*p[j])%mod;
		for(int i=0;i<2*k;i++) c[i]=res[i];
		return 0;
	};
	for(;m;m>>=1,mul(g,g,g))
		if(m&1) mul(f,g,f);
	ll ans=0;
	for(int i=0;i<k;i++)
		ans=(ans+h[i+1]*f[i])%mod;
	return ans;
}
int main(){
	read(n);read(m);
	for(int i=1;i<=n;i++)
		read(h[i]);
	vector<ll> ans;
	BM(h,n,ans);
	for(auto x:ans) cout<<(x+mod)%mod<<' ';
	cout<<'\n';
	cout<<(calc(m,ans,h)+mod)%mod<<'\n';
	return 0;
}
```

