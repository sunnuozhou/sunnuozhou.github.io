---
title: ACM ICPC Northeastern European Regional Contest 2016 C题
tags:
  - OI
  - codeforces
  - 仙人掌
  - 构造
  - dfs
date: 2020-11-10 12:01:20
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101190)

先考虑一棵树的情况，递归解决问题。在每个子树中先把子树中的边建好，并使根节点的颜色为2，其他点的颜色为1。考虑合并，先将根的颜色变为3，依次将子树和根合并，然后在颜色2，3中连边，合并完一个后就把这个子树的根变为1。最后再将根变为2。

现在来做仙人掌的情况，考虑dfs树，可以发现一个子树内最多只有一个连向子树外的返祖边，令返祖边连接的点的颜色为4，每次在返祖边的祖先节点处连颜色3，4的边。由于仙人掌的环可以有重点，注意要先将有返祖边连向当前节点的子树先合并。

<!--more-->

时间复杂度 $O(n)$，但下列代码为了方便用排序。

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
int n,dep[N],f[N],fw[N],col[N],m,cnt;
vector<int> e[N];
char ans[N*10][30];
void Set(int x,int y,int k){
	sprintf(ans[++cnt],"r %d %d %d\n",x,col[y],k);
	col[y]=k;
}
void connect(int x,int y){
	sprintf(ans[++cnt],"c %d %d %d\n",y,col[x],col[y]);
}
void join(int x,int y){
	sprintf(ans[++cnt],"j %d %d\n",x,y);
}
void dfs(int x,int dad){
	dep[x]=dep[dad]+1;
	col[x]=1;
	Set(x,x,3);
	vector<int> p;
	for(int v:e[x]) if(v!=dad){
		if(dep[v]){
			if(dep[v]<dep[x]) fw[x]=v,f[x]=x;
		}
		else{
			dfs(v,x);
			p.push_back(v);
		}
	}
	sort(p.begin(),p.end(),[&](int a,int b){return (fw[f[a]]==x)>(fw[f[b]]==x);});
	for(int v:p){
		join(v,x);
		connect(v,x);
		Set(x,v,f[v]==v?4:1);
		if(f[v]){
			if(fw[f[v]]==x) connect(f[v],x),Set(x,f[v],1);
			else f[x]=f[v];
		}
	}
	Set(x,x,2);
}
int main(){
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int k;read(k);
		int lst=0;
		for(int j=1;j<=k;j++){
			int x;read(x);
			if(lst) e[x].push_back(lst),e[lst].push_back(x);
			lst=x;
		}
	}
	dfs(1,0);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++)
		printf("%s",ans[i]);
	return 0;
}
```

