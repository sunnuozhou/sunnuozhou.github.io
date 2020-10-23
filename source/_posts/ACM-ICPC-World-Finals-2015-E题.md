---
title: ACM ICPC World Finals 2015 E题
tags:
  - OI
  - codeforces
  - 字符串
date: 2020-10-23 10:54:37
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101239)

将字符串按长度排序，考虑将每个字符串放入A组还是B组。

如果一个字符串在A，B组后面都可以加，就先保留，直到有一个字符串只能加在一边，就把前面保留的加到另一边即可。

时间复杂度 $O(n\times L)$，不知道为什么我常数很大，卡了一波常才过。

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
int n;
string s[5010],T;
vector<int> ansA,ansB;
bool chk(string&a,string&b){
	int k=0,len1=a.length(),len2=b.length();
	for(int i=0;k<len1&&i<len2;i++)
		if(b[i]==a[k]) k++;
	return k==a.length();
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	cin>>T;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		if(!chk(s[i],T)){cout<<"impossible\n";return 0;}
	}
	sort(s+1,s+n+1,[](const string&a,const string&b){
		return a.size()<b.size();
	});
	int A=0,B=0;
	vector<int> tmp;
	for(int i=1;i<=n;i++){
		int k1=chk(s[A],s[i]),k2=chk(s[B],s[i]);
		if(!k1&&!k2){cout<<"impossible\n";return 0;}
		if(k1&&k2&&chk(s[i-1],s[i])){tmp.push_back(i);continue;}
		if(k1){
			ansA.push_back(i);
			for(int x:tmp) ansB.push_back(x),B=x;
			tmp.clear();
			A=i;
		}
		else{
			ansB.push_back(i);
			for(int x:tmp) ansA.push_back(x),A=x;
			tmp.clear();
			B=i;
		}
	}
	for(int x:tmp) ansA.push_back(x);
	cout<<ansA.size()<<' '<<ansB.size()<<'\n';
	for(int x:ansA) cout<<s[x]<<'\n';
	for(int x:ansB) cout<<s[x]<<'\n';
	return 0;
}
```

