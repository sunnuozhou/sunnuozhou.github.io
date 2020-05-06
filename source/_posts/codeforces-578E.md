---
title: codeforces 578E
tags:
  - OI
  - 构造
  - 贪心
date: 2020-04-28 13:53:19
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/contest/578/problem/E)

一开始我的想法是直接贪心取最左可取的，写完发现有问题，结尾的地方和开头的地方LR不匹配可能导致结果不是最优。

但这锅显然是可以修的，考虑每一次正着走都记为LL,LR,RL,RR中的一种，我们可以将贪心的取改为构造一个合法的顺序。

显然LR可以拼成一个大LR，RL也是。并且LL和RR的个数差不超过1。

把LR和RL中一个的尾部放到另一个上，得到一个LL和一个RR。

现在就只有LL和RR了，间隔排开即可。

时间复杂度 $O(|S|)$。

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
set<int> s1,s2;
int n;
char c[N];
pair<vector<int>,int> solve(char*c){
	int sum=0;
	vector<int> ans;
	vector<vector<int> > p,q[4];
	stack<int> s[2];
	for(int i=0;i<n;i++)
		if(s[c[i]=='L'].empty()){
			p.push_back({i});
			s[c[i]=='R'].push(p.size()-1);
		}
		else{
			int k=s[c[i]=='L'].top();
			p[k].push_back(i);
			s[c[i]=='L'].pop();
			s[c[i]=='R'].push(k);
		}
	sum=p.size()-1;
	for(auto x:p){
		if(c[x[0]]=='L'){
			if(c[x.back()]=='L') q[0].push_back(x);
			else q[1].push_back(x);
		}
		else{
			if(c[x.back()]=='L') q[2].push_back(x);
			else q[3].push_back(x);
		}
	}
	if(q[0].empty()&&q[3].empty()){
		if(q[1].empty()||q[2].empty()){
			for(auto x:p) for(auto v:x) ans.push_back(v);
			return make_pair(ans,sum);
		}
		else{
			if(q[1].back().back()<q[2].back().back()){
				q[0].push_back(q[1].back()),q[1].pop_back();
				q[0][0].push_back(q[2].back().back());
				q[2].back().pop_back();
			}
			else{
				q[3].push_back(q[2].back()),q[2].pop_back();
				q[3][0].push_back(q[1].back().back());
				q[1].back().pop_back();
			}
		}
	}
	if(q[0].size()<q[3].size()) swap(q[0],q[3]),swap(q[1],q[2]);
	for(auto x:q[1]) for(auto v:x) ans.push_back(v);
	for(auto v:q[0].back()) ans.push_back(v);
	q[0].pop_back();
	for(auto x:q[2]) for(auto v:x) ans.push_back(v);
	int now=3;
	while(q[now].size()){
		for(auto v:q[now].back()) ans.push_back(v);
		q[now].pop_back();
		now^=3;
	}
	return make_pair(ans,sum);
}
int main(){
	cin>>c;
	n=strlen(c);
	auto ans=solve(c);
	cout<<ans.second<<'\n';
	for(int x:ans.first)
		cout<<x+1<<' ';
	cout<<'\n';
	return 0;
}


```

