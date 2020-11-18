---
title: ACM ICPC Northeastern European Regional Contest 2015 K题
tags:
  - OI
  - codeforces
  - 状压DP
date: 2020-11-17 12:12:52
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

由于额外的边数只有20条，所以后继节点不确定的点最多也只有20个，将这些点拎出来跑状压DP就可以了，注意在无解的情况下可能出现死循环，要判掉。

时间复杂度 $O(m+n+2^{m-n}\times(m-n)^2)$。

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
int f[1<<20][20],g[1<<20][20],n,m,nxt[N],pre[N],tag[N],p[N];
vector<int> V,P,a[50],e[N];
void solve(int n){
	for(int x=0;x<n;x++){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[1<<x][x]=1;
		for(int i=0;i<1<<n;i++){
			for(int j=0;j<n;j++){
				if(!f[i][j]) continue;
				for(int&v:a[j])
					if(~i>>v&1) f[i|1<<v][v]=1,g[i|1<<v][v]=j;
			}
		}
		for(int i=0;i<n;i++)
			if(f[(1<<n)-1][i]){
				int flag=0;
				for(int v:a[i]) if(v==x) flag=1;
				if(!flag) continue;
				int x=i,now=(1<<n)-1;
				while(now){
					int y=g[now][x];
					P.push_back(V[x]);
					now=now^(1<<x);
					x=y;
				}
				return;
			}
	}
	puts("There is no route, Karl!");
	exit(0);
}
int main(){
	freopen("king.in","r",stdin);
	freopen("king.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		if(!pre[y]) pre[y]=x;
		else tag[y]=1;
		e[x].push_back(y);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]){puts("There is no route, Karl!");return 0;}
	for(int i=1;i<=n;i++)
		if(!tag[i]) nxt[pre[i]]=i;
	for(int i=1;i<=n;i++)
		if(e[i].size()==1) pre[e[i][0]]=i,tag[e[i][0]]=0,nxt[i]=e[i][0];
	for(int i=1;i<=n;i++)
		if(!nxt[i]) p[i]=1+V.size(),V.push_back(i);
	if(V.size()==0){
		int cnt=0;
		for(int x=1,flag=1;(flag||x!=1)&&cnt<=n;flag=0,x=nxt[x])
			cnt++;
		if(cnt!=n){puts("There is no route, Karl!");return 0;}
		for(int x=1,flag=1;flag||x!=1;flag=0,x=nxt[x])
			printf("%d ",x);
		printf("1\n");
		return 0;
	}
	if(V.size()>20){
		puts("There is no route, Karl!");
		return 0;
	}
	for(int i=0;i<V.size();i++)
		for(auto&v:e[V[i]]){
			int x=v;
			if(!tag[x]) continue;
			int cnt=0;
			while(nxt[x]){
				x=nxt[x];
				if(++cnt>n){
					puts("There is no route, Karl!");
					return 0;
				}
			}
			a[i].push_back(p[x]-1);
		}
	solve(V.size());
	queue<int> ans;
	vector<int> A;
	for(int x:P){
		int y=x;A.push_back(x);
		while(!tag[y]&&pre[y]){
			A.push_back(pre[y]),y=pre[y];
			if(A.size()>n) break;
		}
	}
	reverse(A.begin(),A.end());
	for(int x:A) ans.push(x);
	if(ans.size()!=n){puts("There is no route, Karl!");return 0;}
	while(ans.front()!=1){
		int x=ans.front();ans.pop();
		ans.push(x);
	}
	while(!ans.empty()){
		printf("%d ",ans.front());
		ans.pop();
	}
	printf("1\n");
	return 0;
}


```

