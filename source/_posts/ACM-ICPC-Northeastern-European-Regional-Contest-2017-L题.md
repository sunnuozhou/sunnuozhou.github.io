---
title: ACM ICPC Northeastern European Regional Contest 2017 L题
tags:
  - OI
  - codeforces
  - dfs
date: 2020-11-10 12:01:13
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101630)

对于一个路径 $(a,b)$，在 $a$ 处和 $b$ 处各加入一个点。然后考虑点的匹配。

递归的考虑，首先当前的根如果有超过两个子树有点要匹配，那么一定不行。

先考虑有两个子树的情况，枚举尝试匹配两个子树最浅的点，可以匹配就匹配，不可以就不行。

在只剩一个子树后，先尝试用当前的根上的点和最浅的点匹配，可以就匹配，不可以就加入待匹配点。

判断是否可以匹配可以用哈希表或`map`，由于路径的端点可以相同，在匹配时有诸多细节，如在两个子树不能匹配时尝试用根上的点匹配。

时间复杂度 $O(n)$ 或 $O(n\log n)$。

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
vector<int> e[N];
stack<int> h[N];
int n,m,q[N],dep[N];
map<pair<int,int>,int> mp;
void dfs(int x,int dad){
	vector<int> s;dep[x]=dep[dad]+1;
	int fg1=0,fg2=0;
	for(int v:e[x]) if(v!=dad){
		dfs(v,x);
		if(h[v].size()) s.push_back(v);
	}
	if(s.size()>2){puts("No");cerr<<"!!\n";exit(0);}
	if(s.size()==2){
		int p0=0,p1=0;
		while(h[s[0]].size()&&h[s[1]].size()){
			int k1=h[s[0]].top(),k2=h[s[1]].top();
			if(k1>k2) swap(k1,k2);
			if(mp[make_pair(k1,k2)]){
				if(!fg1) fg1=h[s[0]].size()>h[s[1]].size()?dep[h[s[0]].top()]:dep[h[s[1]].top()];
				mp[make_pair(k1,k2)]--;
				h[s[0]].pop();
				h[s[1]].pop();
			}
			else{
				int k3=0;
				if(mp[make_pair(x,k1)]||mp[make_pair(k1,x)]) k3=k1;
				if(mp[make_pair(x,k2)]||mp[make_pair(k2,x)]) k3=k2;
				if(!k3){puts("No");exit(0);}
				if(fg1&&fg1<dep[k3]){puts("No");cerr<<"##\n";exit(0);}
				if(h[s[0]].top()==k3) h[s[0]].pop(),p0=dep[k3];
				else h[s[1]].pop(),p1=dep[k3];
				q[x]--;
				mp[make_pair(min(x,k3),max(x,k3))]--;
			}
			if(p0&&p1){puts("No");exit(0);}
		}
		if(h[s[0]].size()){
			if(fg1) fg1=min(fg1,p1);
			else fg1=p1;
			swap(h[s[0]],h[x]);
		}
		else{
			if(fg1) fg1=min(fg1,p0);
			else fg1=p0;
			swap(h[s[1]],h[x]);
		}
	}
	else if(s.size()) swap(h[s[0]],h[x]);
	while(q[x]&&h[x].size()){
		int k1=h[x].top(),k2=x;
		if(k1>k2) swap(k1,k2);
		if(mp[make_pair(k1,k2)]){
			if(fg1&&fg1<dep[h[x].top()]){puts("No");cerr<<"##\n";exit(0);}
			fg2=1;
			mp[make_pair(k1,k2)]--;
			h[x].pop();q[x]--;
		}
		else break;
	}
	if(fg2&&q[x]){puts("No");cerr<<"$$\n";exit(0);}
	while(q[x]--) h[x].push(x);
	if(fg1&&h[x].size()){puts("No");exit(0);}
}
int main(){
	read(n);read(m);
	for(int i=1;i<n;i++){
		int x,y;read(x);read(y);
		e[x].push_back(y);
		e[y].push_back(x);
	}
	for(int i=1;i<=m;i++){
		int x,y;read(x);read(y);
		if(x==y) continue;
		q[x]++;
		q[y]++;
		if(x>y) swap(x,y);
		mp[make_pair(x,y)]++;
	}
	dfs(1,0);
	if(h[1].size()) puts("No");
	else puts("Yes");
	return 0;
}
```

