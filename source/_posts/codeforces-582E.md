---
title: codeforces 582E
date: 2020-01-09 16:45:29
tags:
- OI
- codeforces
- 解题报告
- FWT
- DP
- 树形DP
categories: 解题报告
---

## Boolean Function

### 题目大意

给你一个逻辑表达式，包含$A,B,C,D$这4个变量和$\&,|$这2个运算符。现在这个逻辑表达式的一些变量和运算符看不清了。

已知在$n$种不同的$A,B,C,D$取值下，表达式的值，求有多少可能的表达式。


### 数据范围

表达式长度$\le 500$

$n\le 16$

<!--more-->

### 解题思路

考虑到$n\le 16$，将一个表达式每一种情况下当前的答案是0还是1记为一个$g(s)$,$g(s)$是一个$n$位的二进制数，（$0\le g(s) < 2^n$，$s$为一个表达式）。

显然的，$g((s1)|(s2))=g(s1)|g(s2)，g(((s1)\&(s2))=g(s1)\&g(s2)$。

接着考虑题目，一个表达式可以被建为一个二叉树，其节点个数为$\frac{|s|}{6}$级别的。转换为树后开始考虑树形DP，记录$dp[v][x]$，表示所有可以被以$v$为根的子树代表的表达式中（即通过把'?'变为确定符号得到），有多少表达式$s$的$g(s)=x$。该DP的转移为$dp[v][x|y]+=dp[ls][x]\times dp[rs][y]$或$dp[v][x\&y]+=dp[ls][x]\times dp[rs][y]$，其中$ls$为左儿子，$rs$为右儿子。

现在的时间复杂度为$O(|s|*4^n)$，无法通过题目。

观察时间复杂度的瓶颈——DP转移。可以发现该DP转移的形式是一个或卷积或者与卷积的形式，可以使用fwt进行优化。

```cpp
void fwt_and(int*f,int tag){
	for(int mid=1;mid<1<<n;mid<<=1)
		for(int l=0;l<1<<n;l+=mid<<1)
			for(int i=l;i<l+mid;i++){
				f[i]=(f[i]+f[i+mid]*tag)%mod;
			}
}
void fwt_or(int*f,int tag){
	for(int mid=1;mid<1<<n;mid<<=1)
		for(int l=0;l<1<<n;l+=mid<<1)
			for(int i=l;i<l+mid;i++){
				f[i+mid]=(f[i]*tag+f[i+mid])%mod;
			}
}
```

此时，时间复杂度被优化为$O(|s|*2^n*n)$，可以通过题目。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9+7;
int f[500][65536],n,a[20][5],len,tot,g[65536],g1[65536],g2[65536];
char c[510];
void fwt_and(int*f,int tag){
	for(int mid=1;mid<65536;mid<<=1)
		for(int l=0;l<65536;l+=mid<<1)
			for(int i=l;i<l+mid;i++){
				f[i]=(f[i]+f[i+mid]*tag)%mod;
			}
}
void fwt_or(int*f,int tag){
	for(int mid=1;mid<65536;mid<<=1)
		for(int l=0;l<65536;l+=mid<<1)
			for(int i=l;i<l+mid;i++){
				f[i+mid]=(f[i]*tag+f[i+mid])%mod;
			}
}
int dfs(char*c,int l,int r){
	int x=++tot;
	if(l==r){
		if(c[l]=='?'||c[l]=='A'){
			int now=0;
			for(int i=0;i<n;i++) now|=a[i][0]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='B'){
			int now=0;
			for(int i=0;i<n;i++) now|=a[i][1]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='C'){
			int now=0;
			for(int i=0;i<n;i++) now|=a[i][2]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='D'){
			int now=0;
			for(int i=0;i<n;i++) now|=a[i][3]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='a'){
			int now=0;
			for(int i=0;i<n;i++) now|=!a[i][0]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='b'){
			int now=0;
			for(int i=0;i<n;i++) now|=!a[i][1]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='c'){
			int now=0;
			for(int i=0;i<n;i++) now|=!a[i][2]<<i;
			f[x][now]++;
		}
		if(c[l]=='?'||c[l]=='d'){
			int now=0;
			for(int i=0;i<n;i++) now|=!a[i][3]<<i;
			f[x][now]++;
		}
		return x;
	}
	int now=0;
	for(int i=l;i<=r;i++){
		if(c[i]=='(') now++;
		if(c[i]==')') now--;
		if(now==0&&(c[i]=='|'||c[i]=='&'||c[i]=='?')){
			int lc=dfs(c,l+1,i-2),rc=dfs(c,i+2,r-1);
			if(c[i]=='&'||c[i]=='?'){
				memset(g,0,sizeof(g));
				memcpy(g1,f[lc],sizeof(g1));
				memcpy(g2,f[rc],sizeof(g2));
				fwt_and(g1,1);fwt_and(g2,1);
				for(int j=0;j<65536;j++)
					g[j]=1ll*g1[j]*g2[j]%mod;
				fwt_and(g,-1);
				for(int j=0;j<65536;j++)
					f[x][j]=g[j];
			}
			if(c[i]=='|'||c[i]=='?'){
				memset(g,0,sizeof(g));
				memcpy(g1,f[lc],sizeof(g1));
				memcpy(g2,f[rc],sizeof(g2));
				fwt_or(g1,1);fwt_or(g2,1);
				for(int j=0;j<65536;j++)
					g[j]=1ll*g1[j]*g2[j]%mod;
				fwt_or(g,-1);
				for(int j=0;j<65536;j++)
					f[x][j]=(f[x][j]+g[j])%mod;
			}
			return x;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin>>c+1;len=strlen(c+1);
	cin>>n;
	int now=0;
	for(int i=0;i<n;i++){
		cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3]>>a[i][4];
		now|=a[i][4]<<i;
	}
	int x=dfs(c,1,len);
	cout<<(f[x][now]+mod)%mod<<'\n';
	return 0;
}

```

