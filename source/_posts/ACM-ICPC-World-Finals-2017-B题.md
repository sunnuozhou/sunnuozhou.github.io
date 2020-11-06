---
title: ACM ICPC World Finals 2017 B题
tags:
  - OI
  - codeforces
  - 搜索
date: 2020-10-30 10:46:21
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101471)

先求出每个人一定有哪些牌和一定没有哪些牌，然后枚举答案，暴力分配剩下的牌并检查是否合法。

时间复杂度不会分析，但可以通过本题。

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
int n,h[4],nh[4],cnt;
vector<pair<int,int> > ck;
bool dfs(int dep,int ct){
	if(dep==21){
		for(auto pr:ck) if(!(h[pr.first]&pr.second)) return 0;
		return 1;
	}
	if(ct>>dep&1) return dfs(dep+1,ct);
	for(int i=1;i<4;i++)
		if(~nh[i]>>dep&1&&__builtin_popcount(h[i])<4+(i==1)){
			h[i]^=1<<dep;
			int flag=dfs(dep+1,ct);
			h[i]^=1<<dep;
			if(flag) return 1;
		}
	return 0;
}
int main(){
	read(n);
	for(int i=1;i<=5;i++){
		char c;scanf(" %c",&c);
		h[0]|=1<<c-'A';
	}
	int now=0;
	while(n--){
		char c1,c2,c3;scanf(" %c %c %c",&c1,&c2,&c3);
		int tmp=1<<c1-'A'|1<<c2-'A'|1<<c3-'A';
		for(int p=(now+1)%4;p!=now;p=(p+1)%4){
			char t;scanf(" %c",&t);
			if(t=='-') nh[p]|=tmp;
			else{
				if(t=='*') ck.emplace_back(p,tmp);
				else h[p]|=1<<t-'A';
				break;
			}
		}
		now=(now+1)%4;
	}
	int ct=h[0]|h[1]|h[2]|h[3];
	char ans1='-',ans2='-',ans3='-';
	for(int i=0;i<6;i++)
		for(int j=6;j<12;j++)
			for(int k=12;k<21;k++){
				if(ct>>i&1||ct>>j&1||ct>>k&1) continue;
				if(!dfs(0,ct|1<<i|1<<j|1<<k)) continue;
			//	cerr<<i<<' '<<j<<' '<<k<<'\n';
				if(ans1=='-') ans1=i+'A';
				else if(ans1!=i+'A') ans1='?';
				if(ans2=='-') ans2=j+'A';
				else if(ans2!=j+'A') ans2='?';
				if(ans3=='-') ans3=k+'A';
				else if(ans3!=k+'A') ans3='?';
			}
	cout<<ans1<<ans2<<ans3<<'\n';
	return 0;
}
 
```

