---
title: ACM ICPC Northeastern European Regional Contest 2015 J题
tags:
  - OI
  - codeforces
  - 交互
date: 2020-11-16 11:30:35
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/100851)

每次随机一个序列，看是否返回 $n/2$，如果不是就再随一个。

在有一个返回 $n/2$ 的序列后，枚举二元组 $(1,2),(1,3),(1,4)\cdots$，看每个二元组取反后是不是 $n/2$，并把每个是 $n/2$ 的位置取反。

现在得到的序列就要么是全对，要么是全错了，试两次就行。

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
const int N = 1010;
int tag[N],n;
char c[N];
int query(char*c){
	cout<<c<<endl;
	int k;cin>>k;
	if(k==n) exit(0);
	return k;
}
int main(){
	srand(38428934);
	cin>>n;
	for(int i=0;i<n;i++)
		c[i]='0'^(rand()&1);
	while(query(c)!=n/2)
		for(int i=0;i<n;i++)
			c[i]='0'^(rand()&1);
	for(int i=1;i<n;i++){
		c[0]^=1;c[i]^=1;
		tag[i]=query(c)==n/2;
		c[0]^=1;c[i]^=1;
	}
	for(int i=1;i<n;i++) c[i]^=tag[i];
	if(!query(c)) for(int i=0;i<n;i++) c[i]^=1;
	query(c);
	return 0;
}
```

