---
title: ACM ICPC Central European Regional Contest 2017 B题
tags:
  - OI
  - codeforces
  - 扫描线
date: 2020-11-23 12:39:27
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101620)

按 $x$ 从大到小考虑每个栏杆，用扫描线求出每个物品直接属于那个栏杆，以及每个栏杆的上一级栏杆是哪个。

然后按时间从后到先考虑每个栏杆，使用并查集统计栏杆包含栏杆对答案的影响。

时间复杂度 $O((n+m)\log m$。

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
const int N = 301000;
int n,m,ans[N],fa[N],Up[N];
struct node{int x,y,num,typ;};
vector<node> v;
set<pair<int,int> > S;
int find(int x){return fa[x]==x?x:find(fa[x]);}
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		int x,y;read(x);read(y);
		v.push_back({x,y,i,1});
	}
	read(m);
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		v.push_back({x,y,i,0});
		fa[i]=i;
	}
	sort(v.begin(),v.end(),[](node a,node b){
		return a.x>b.x||a.x==b.x&&a.typ<b.typ;
	});
	for(auto&pr:v)
		if(pr.typ){
			auto k=S.lower_bound(make_pair(pr.y,0));
			if(k!=S.end()) ans[k->second]++;
		}
		else{
			auto k=S.lower_bound(make_pair(pr.y,pr.num));
			if(k!=S.end()) Up[pr.num]=k->second;
			while(S.size()&&S.begin()->first<pr.y){
				auto k=--S.upper_bound(make_pair(pr.y,pr.num));
				if(k->second>pr.num) S.erase(k);
				else break;
			}
			S.insert(make_pair(pr.y,pr.num));
		}
	for(int i=m;i;i--){
		if(!Up[i]) continue;
		if(Up[i]<i){
			ans[Up[i]]+=ans[i];
			fa[i]=Up[i];
			continue;
		}
		int nxt=find(Up[i]);
		if(nxt<i) ans[nxt]+=ans[i];
		fa[i]=nxt;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
	return 0;
}


```

