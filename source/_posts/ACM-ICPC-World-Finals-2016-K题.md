---
title: ACM ICPC World Finals 2016 K题
tags:
  - OI
  - codeforces
  - 字符串
  - 贪心
date: 2020-10-29 11:48:48
categories: 解题报告
top:
---

[题目链接](https://codeforces.com/gym/101242)

首先引号个数必须是偶数。

从大到小枚举答案，考虑检查是否可行。

直接贪心的在两边取需要的引号就可以了，因为多余的引号都可以变成`1-quotation`。

注意特判答案为1的情况。

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
int a[110],b[110],n;
bool check(int lim){
	for(int i=1;i<=n;i++) b[i]=a[i];
	int l=1,r=n;
	for(int j=lim;j;j--){
		if(b[l]<j) return 0;
		b[l]-=j;
		if(b[r]<j) return 0;
		b[r]-=j;
		if(!b[l]) l++;
		if(!b[r]) r--;
	}
	return 1;
}
int main(){
	read(n);
	int sum=0;
	for(int i=1;i<=n;i++){
		read(a[i]);
		sum+=a[i];
	}
	if(sum&1){puts("no quotation");return 0;}
	for(int i=100;i;i--)
		if(check(i)){
			if(i==1&&sum>2) break;
			cout<<i<<'\n';
			return 0;
		}
	puts("no quotation");
	return 0;
}
```

