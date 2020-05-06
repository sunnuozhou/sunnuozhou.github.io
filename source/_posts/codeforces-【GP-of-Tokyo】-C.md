---
title: codeforces 【GP of Tokyo】 C
tags:
  - OI
  - codeforces
  - 多项式
  - BM算法
  - 矩阵乘法
  - DP
  - 概率
date: 2020-05-06 15:16:10
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/102586/problem/C)

如果 $m\le 500$，可以直接高斯消元，$O(m^3)$ 得到答案。

考虑 $[k,k+n-1]$ 这个区间，由于走一步的步长不超过 $n$，每一圈至少有一步在这个区间内。

设 $F_{i,j，0/1},i,j \in [k,k+n-1]$ 表示由 $i$ 出发，在下一次离开这个区间后再进来，第一个到达的数是 $j$ 的概率以及期望的步数。

如果求出了所有 $F_{i,j}$，那么就可以解出 $x\in [k,k+n-1]$ 到 $k$ 的期望步数。只要再知道从0到达 $x\in[k,k+n-1]$ 的期望步数和概率，就可以算出答案。

考虑如何求出所有 $F_{i,j}$：

对于一对 $i,j$，枚举走到 $j$ 的上一步在哪，显然可行的位置不超过 $n$ 个，令从 $i$ 到该位置的距离为 $D$，如果我们知道恰好走 $D$ 步的概率和期望步数，就可以算出 $F_{i,j}$。

由于 $i,j\in [k,k+n-1]$，$D$ 必然在 $[m-2\times n,m]$中，一个显然的想法是使用矩阵乘法优化转移，求出所有 $D\in [m-2\times n,m]$ 时的概率和期望。 

但由于既要算期望，又要算概率，$1000\times1000$ 的矩阵快速幂在这题中是不能接受的，要考虑优化矩阵快速幂。

如果我们知道了这个矩阵的特征多项式，我们就可以在 $O(n\log n\log m+n^2)$ 的时间内算出所有 $D\in [m-2\times n,m]$ 时的概率和期望（不用多项式取模会T），具体方法参见[这篇文章](https://sunnuozhou.github.io/2020/04/22/Berlekamp-Massey算法简介/)。

<!--more-->

现在考虑如何求解一个矩阵的特征多项式，该方法在 *IOI2019论文集* 中zzq的论文里有提到。大概方法是考虑求一个矩阵列 $I,A,A^2,A^3,\cdots$ 的最小线性递推。随机生成一个行向量，一个列向量，使得矩阵列中的每一个矩阵都左乘行向量，右乘列向量，变为一个数列。这个数列的最短线性递推有 $1-\frac{n+m}p$ 的概率是矩阵列的最短递推，其中 $n,m$ 为矩阵的行数和列数，$p$ 为模数。这个做法对于有 $e$ 的元素的稀疏矩阵的复杂度为 $O(n(e+n))$。

在实际实现时，我使用的数列长度为矩阵大小的2倍，如果数列太短，可能会求出一个错误的递推。

在本题中，矩阵为一个元素在 $O(n)$ 级别的稀疏矩阵。

从0到达 $x\in[k,k+n-1]$ 的期望步数和概率也可以用同样方法算出。

总时间复杂度为 $O(n^3+n\log n\log m)$。

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
const int N = 2010,mod = 998244353;
namespace FFT{
	int len,maxn,r[N*8];
	ll g1[N*8],g2[N*8];
	ll fp(ll a,ll k){
		ll ans=1;
		for(;k;k>>=1,a=(a*a)%mod)
			if(k&1) ans=(a*ans)%mod;
		return ans;
	}
	void build(int n){
		maxn=1;len=0;while(maxn<=n) maxn<<=1,len++;
		for(int i=0;i<maxn;i++) r[i]=r[i>>1]>>1|(i&1)<<len-1;
	}
	void NTT(ll *a,int tag){
		for(int i=0;i<maxn;i++)
			if(i<r[i]) swap(a[i],a[r[i]]);
		for(int mid=1;mid<maxn;mid<<=1){
			ll wn=fp(3,(mod-1)/mid/2);
			if(tag<0) wn=fp(wn,mod-2);
			for(int l=0;l<maxn;l+=mid<<1)
				for(int i=l,w=1;i<l+mid;i++,w=wn*w%mod){
					ll x=a[i],y=a[i+mid]*w;
					a[i]=(x+y)%mod; a[i+mid]=(x-y)%mod;
				}
		}
	}
	void mul(ll *a,ll *b){for(int i=0;i<maxn;i++) a[i]=a[i]*b[i]%mod;}
	void clear(ll *a,int bg=0){for(int i=bg;i<maxn;i++) a[i]=0;}
	void turn(ll *a,ll *b,int ed=maxn){memcpy(b,a,8*ed);}
	void iturn(ll *a,ll *b){ll inv=fp(maxn,mod-2);for(int i=0;i<maxn;i++) b[i]=a[i]*inv%mod;}
	void mult(ll *a,ll *b,ll *c,int n,int m){
		build(n+m);
		clear(g1);clear(g2);
		turn(a,g1,n+1);turn(b,g2,m+1);
		NTT(g1,1);NTT(g2,1);
		mul(g1,g2);NTT(g1,-1);iturn(g1,c);
	}
	void inv(ll *a,ll *b,int n){
		clear(b);
		b[0]=fp(a[0],mod-2);
		for(int now=1;now<n;now<<=1){
			build(now*2);
			clear(g1);clear(g2);
			turn(b,g1);NTT(g1,1);
			turn(a,g2,now*2);NTT(g2,1);
			mul(g1,g1);mul(g1,g2);NTT(g1,-1);
			iturn(g1,g1);
			for(int i=0;i<maxn;i++) b[i]=(b[i]*2-g1[i])%mod;
			clear(b,2*now);
		}
	}
	void div(ll *a,ll *b,ll *c,int n,int m){
		for(int i=0;i<=n;i++) if(i<n-i) swap(a[i],a[n-i]);
		for(int i=0;i<=m;i++) if(i<m-i) swap(b[i],b[m-i]);
		inv(b,c,n-m+1);
		mult(c,a,c,n-m,n-m);
		clear(c,n-m+1);
		for(int i=0;i<=n-m;i++) if(i<n-m-i) swap(c[i],c[n-m-i]);
		for(int i=0;i<=n;i++) if(i<n-i) swap(a[i],a[n-i]);
		for(int i=0;i<=m;i++) if(i<m-i) swap(b[i],b[m-i]);
	}
}
int n;
ll m,K,f[1010],g[1010],ans[1010],a[1010];
ll fp(ll a,ll k){
	ll ans=1;
	for(;k;k>>=1,a=a*a%mod)
		if(k&1) ans=a*ans%mod;
	return ans;
}
void solve(ll *f,ll *g){
	static ll b[510][510];
	for(int i=1;i<n;i++){
		b[i][i]=1;
		for(int j=1;j<n;j++){
			for(int k=j+1;k<=n;k++)
				b[i][j]=(b[i][j]-f[i-(j-k)]*a[k])%mod,b[i][n]=(b[i][n]+(g[i-(j-k)]+f[i-(j-k)])*a[k])%mod;
		}
		for(int k=1;k<=n;k++)
			b[i][n]=(b[i][n]+(g[i+k]+f[i+k])*a[k])%mod;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<n;j++)
			if(b[i][i]%mod==0&&b[j][i]%mod) swap(b[i],b[j]);
		if(b[i][i]%mod==0) continue;
		for(int j=i+1;j<n;j++){
			ll res=b[j][i]*fp(b[i][i],mod-2)%mod;
			for(int k=1;k<=n;k++)
				b[j][k]=(b[j][k]-b[i][k]*res)%mod;
		}
	}
	for(int i=n-1;i;i--){
		for(int j=i+1;j<n;j++)
			b[i][n]=(b[i][n]-b[i][j]*ans[j])%mod;
		ans[i]=b[i][n]*fp(b[i][i],mod-2)%mod;
	}
}
namespace BM{
	const int mod = 998244353;
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
	void calc(ll m,vector<ll>&coef,ll*ans){
		int k=coef.size();
		static ll f[N*8],g[N*8],res[N*8],p[N*8];
		p[0]=-1;
		for(int i=1;i<=k;i++) p[i]=coef[i-1];
		reverse(p,p+k+1);
		for(int i=0;i<=2*k;i++) f[i]=g[i]=0;
		f[0]=1;
		if(k>1) g[1]=1;
		else g[0]=p[0];
	/*	auto mul = [&](ll *a,ll *b,ll *c){
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
			if(m&1) mul(f,g,f);*/
		while(m){
			if(m&1){
				FFT::mult(f,g,f,k-1,k-1);
				FFT::div(f,p,res,2*k-2,k);
				FFT::mult(res,p,res,k-2,k);
				for(int i=0;i<2*k;i++) f[i]=(f[i]-res[i])%mod;
			}
			m>>=1;
			FFT::mult(g,g,g,k-1,k-1);
			FFT::div(g,p,res,2*k-2,k);
			FFT::mult(res,p,res,k-2,k);
			for(int i=0;i<2*k;i++) g[i]=(g[i]-res[i])%mod;
		}
		for(int i=0;i<k;i++) ans[i]=f[i];
	}
}
vector<ll> coef;
void calc(ll l,ll r){
	int now=0;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	while(l<0) f[now]=0,g[now]=0,l++,now++; 
	static ll p1[1510],p2[1510],p[1010];
	p1[0]=1;p2[0]=0;
	for(int i=1;i<=3*n;i++){
		p1[i]=p2[i]=0;
		for(int j=1;j<=n;j++)
			if(j<=i)
				p1[i]=(p1[i]+p1[i-j]*a[j])%mod,p2[i]=(p2[i]+(p2[i-j]+p1[i-j])*a[j])%mod;
	}
	BM::calc(l,coef,p);
	for(int i=0;i<n&&i<=r-l;i++){
		for(int j=0;j<coef.size();j++)
			f[now]=(f[now]+p[j]*p1[i+j])%mod,g[now]=(g[now]+p[j]*p2[i+j])%mod;
		now++;
	}
	for(ll i=l+n;i<=r;i++){
		f[now]=g[now]=0;
		for(int j=1;j<=n;j++)
			f[now]=(f[now]+f[now-j]*a[j])%mod,g[now]=(g[now]+(g[now-j]+f[now-j])*a[j])%mod;
		now++;
	}
	reverse(f,f+now);
	reverse(g,g+now);
}
ll C[2010];
void get_coef(){
	static int M[1010][1010],now[1010],q[1010],res[1010];
	vector<pair<int,int> > V;
	for(int i=0;i<n;i++){
		M[0][i]=a[i+1],M[n][i]=M[n][i+n]=a[i+1];
		V.emplace_back(0,i);
		V.emplace_back(n,i);
		V.emplace_back(n,i+n);
	}
	for(int i=1;i<n;i++){
		M[i][i-1]=1,M[i+n][i+n-1]=1;
		V.emplace_back(i,i-1);
		V.emplace_back(i+n,i+n-1);
	}
	srand(19428);
	for(int i=0;i<2*n;i++) now[i]=rand()%mod,q[i]=rand()%mod;
	for(int i=1;i<=4*n+1;i++){
		for(int j=0;j<2*n;j++) C[i]=(C[i]+1ll*now[j]*q[j])%mod;
		memset(res,0,sizeof(res));
		for(auto pr:V)
			res[pr.second]=(res[pr.second]+1ll*now[pr.first]*M[pr.first][pr.second])%mod;
		memcpy(now,res,sizeof(res));
	}
	BM::BM(C,4*n+1,coef);
}
int main(){
	read(n);read(m);read(K);
	int sum=0;
	for(int i=1;i<=n;i++)
		read(a[i]),sum+=a[i];
	for(int i=1;i<=n;i++)
		a[i]=a[i]*fp(sum,mod-2)%mod;
	get_coef();
	calc(m-2*n,m);
	solve(f,g);
	calc(K-n,K);
	ll S=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<n;j++)
			S=(S+a[i+j]*f[i]%mod*ans[j]+a[i+j]*(g[i]+f[i]))%mod;
		S=(S+a[i]*(g[i]+f[i]))%mod;
	}
	cout<<(S+mod)%mod<<'\n';
	return 0;
}


```

