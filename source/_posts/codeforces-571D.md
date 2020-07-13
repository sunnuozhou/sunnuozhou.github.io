---
title: codeforces 571D
tags:
  - OI
  - codeforces
  - 并查集
date: 2020-07-13 10:04:38
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/571/problem/D)

使用两个启发式合并的并查集 $S1,S2$ 维护合并操作。考虑剩下的操作如何维护。

- ’A‘：给 $S1$ 中当前被合并到的并查集打上tag，记录下打tag的时间，并维护增加的值的前缀和。

- ’Z‘：给 $S2$ 中当前被合并到的并查集打上tag，记录下打tag的时间。

- 'U'，'M' ：启发式合并两个并查集，记录下被合并的并查集被合并的时间。

现在来考虑回答询问，先在 $S2$ 上遍历每个祖先节点，求出最后一次清零tag是什么时候打的，注意打tag的时候必须要晚于合并时间才可以统计。

然后到 $S1$ 上来统计答案，遍历每个祖先节点，统计每个节点对答案的贡献。定义一个tag是有效的，当且仅当这个tag是在合并后打上去的。一个tag被统计到，要满足两个要求：时间晚于最后的清零tag，并且是有效的。

可以发现，打tag的时间在一个并查集中是单调的，并且父亲节点的第一个有效的tag的时间也晚于当前节点最后一个tag的时间，所以打tag的时间在整条祖先链上单调。也就是说，在 $O(\log n)$ 级别的祖先中，只有至多一个节点有部分有效tag被统计，其他节点要么有效tag全没被统计，要么有效tag全被统计了。部分被统计的节点可以用二分来求解。

时间复杂度 $O(n+m\log (n+m))$。

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
struct dsu{
	int fa[N],s[N],tim[N];
	vector<int> v[N];
	vector<ll> sum[N];
	void init(int n){
		for(int i=1;i<=n;i++) fa[i]=i,s[i]=1;
	}
	int find(int x){return fa[x]==x?x:find(fa[x]);}
	void merge(int x,int y){
		x=find(x);y=find(y);
		if(s[x]>s[y]) swap(x,y);
		s[y]+=s[x];fa[x]=y;tim[x]=v[y].size();
	}
	void add(int x,int tm,int tag){
		v[x].push_back(tm);
		if(tag){
			sum[x].push_back(sum[x].size()?sum[x].back():0);
			sum[x][sum[x].size()-1]+=s[x];
		}
	}
}h1,h2;
int n,m;
int main(){
	read(n);read(m);
	h1.init(n);
	h2.init(n);
	for(int i=1;i<=m;i++){
		char opt;
		scanf(" %c",&opt);
		if(opt=='U'){
			int x,y;read(x);read(y);
			h1.merge(x,y);
		}
		if(opt=='M'){
			int x,y;read(x);read(y);
			h2.merge(x,y);
		}
		if(opt=='A'){
			int x;read(x);
			h1.add(h1.find(x),i,1);
		}
		if(opt=='Z'){
			int x;read(x);
			h2.add(h2.find(x),i,0);
		}
		if(opt=='Q'){
			int x;read(x);
			int k1=x,k2=x,mx=h2.v[k2].size()?h2.v[k2].back():0;
			while(h2.fa[k2]!=k2){
				int lst=h2.tim[k2];
				k2=h2.fa[k2];
				if(lst!=h2.v[k2].size()) mx=max(mx,h2.v[k2].back());
			}
			ll ans=0;
			if(h1.v[k1].size()){
				if(h1.v[k1][0]>mx) ans+=h1.sum[k1].back();
				else if(h1.v[k1].back()>mx) ans+=h1.sum[k1].back()-h1.sum[k1][lower_bound(h1.v[k1].begin(),h1.v[k1].end(),mx)-h1.v[k1].begin()-1];
			}
			while(h1.fa[k1]!=k1){
				int lst=h1.tim[k1];
				k1=h1.fa[k1];
				if(h1.v[k1].size()!=lst){
					if(h1.v[k1][lst]>mx) ans+=h1.sum[k1].back()-(lst?h1.sum[k1][lst-1]:0);
					else if(h1.v[k1].back()>mx) ans+=h1.sum[k1].back()-h1.sum[k1][lower_bound(h1.v[k1].begin(),h1.v[k1].end(),mx)-h1.v[k1].begin()-1];
				}
			}
			cout<<ans<<'\n';
		}
	}
	return 0;
}
```

