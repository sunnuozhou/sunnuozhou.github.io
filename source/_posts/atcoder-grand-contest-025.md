---
title: atcoder grand contest 025
date: 2020-01-09 16:37:20
tags:
- OI
- atcoder
- 解题报告
categories: 解题报告
---
## F.Addition and Andition

### 题目大意

给你两个正整数$X,Y$，进行$K$次以下操作：

- 令Z=X and Y，and为位运算与。

- X+=Z,Y+=Z

输出最终的$X,Y$。



### 数据范围

$X,Y$二进制表示下长度不超过$10^6$。

$1\le K\le 10^6$

<!--more-->



### 解题过程

定义$S_i$表示$X$二进制表示下从低到高第$i$位的值，$T_i$表示$Y$二进制表示下从低到高第$i$位的值。

定义一次对$i$进行的**进位**为：

```
S[i]=T[i]=2
while S[i]==2||T[i]==2 {
	if S[i]==2
    then
    	S[i]=0,S[i+1]+=1
    endif
	if T[i]==2
    then
    	T[i]=0,T[i+1]+=1
    endif
	i+=1
}
```

定义一次**加法**为

```
for(i=max(|S|,|T|);i>=0;i-=1){
	if S[i]==1&&T[i]==1
	then
		对i进行进位操作
	endif
}
```

现在要做的就是进行$K$次加法操作。

现在我们考虑交换循环顺序：从大到小枚举每一个$S_i=T_i=1$的$i$，然后重复$K$次以下操作：

找到最小的$j\ge i$ ，使得$S_j=T_j=1$，对$j$进行进位操作，若不存在这样的$j$ ，则停止操作。

由于在第$i$个位置一次进位的增量大于所有$j<i$的$j$进位产生的增量之和，所以交换循环顺序后的结果不变。

用$x$表示进位的情况，$now$表示当前还能操作几次。初始是先令$S_i=T_i=0,x=11,now=K$

对于$j=i,i+1,..$进行以下操作：

如果$(S_j,T_j,x)=(0,0,10)$，那么使$(S_j,T_j)=(1,0)$，结束操作。
如果$(S_j,T_j,x)=(0,0,01)$，那么使$(S_j,T_j)=(0,1)$，结束操作。
如果$(S_j,T_j,x)=(0,0,11)$，那么使$(S_j,T_j,x)=(0,0,11)，now \to now-1$，如果$now < 0$，结束操作。
如果$(S_j,T_j,x)=(1,0,11)$，那么使$(S_j,T_j,x)=(0,1,10)$。
如果$(S_j,T_j,x)=(1,0,10)$，那么使$(S_j,T_j,x)=(0,0,10)$。
如果$(S_j,T_j,x)=(1,0,01)$，那么使$(S_j,T_j,x)=(0,0,11)，now \to now-1$，如果$now < 0$，结束操作。

$(S_j,T_j)=(0,1)$和$(S_j,T_j)=(1,0)$的情况类似。

因为可以交换循环顺序，所以并不会遇到$(S_j,T_j)=(1,1)$。

可以发现，如果有连续一段$(S_j,T_j)=(0,0)$，可以快速处理。所以考虑使用一个栈记录所有$(S_j,T_j)\ne (0,0)$的位置，$j$在栈中从顶到底递增。当我们找到一个$(S_i,T_i)=(1,1)$时，弹出栈顶，快速处理当前位置到栈顶所在位置间的$(0,0)$，如果能处理到栈顶的位置，就把他暴力处理掉，并把中途新增的$(S_j,T_j)\ne (0,0)$的位置记录在一个临时数组中，重复执行上述操作。执行完后把临时数组中$(S_j,T_j)\ne (0,0)$的位置加进栈中。

撇开$(0,0)$,$x=11$时,$X,Y$中1的数量不增，$x\ne 11$时,$X,Y$中1的数量减少，并且如果$x=11$，那么一次操作后$x$一定不等于11,而当$(S_j,T_j)=(0,0)$时，可以快速处理。所以时间复杂度为$O(N+M+K)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3001000;
int a[N],b[N],n,m,K;
char s1[N],s2[N];
stack<pair<int,int> > st;
void init(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	while(!st.empty()){
		int w=st.top().first,A=st.top().second>>1&1,B=st.top().second&1;
		//cout<<w<<' '<<A<<' '<<B<<'\n';
		a[w]=A;b[w]=B;st.pop();
	}
}
void print(int*a){
	int len=N;
	while(!a[--len]);
	while(~len) cout<<a[len--];
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>K;
	cin>>s1>>s2;
	for(int i=0;i<n;i++) a[n-i-1]=s1[i]-'0';
	for(int i=0;i<m;i++) b[m-i-1]=s2[i]-'0';
	for(int i=max(n,m)-1;~i;i--){
		if(a[i]+b[i]==1) st.emplace(i,a[i]<<1|b[i]);
		if(a[i]+b[i]<2) continue;
		int now=K,pos=i,x=3;
		stack<pair<int,int> > res;
		while(!st.empty()){
			auto tmp=st.top();
			if(pos==tmp.first){
				st.pop();
				if((x^tmp.second)==3){if((x=3)&&--now<0) break;}
				else{
					if(x^3){pos++;continue;}
					res.emplace(pos,x^tmp.second);
					x&=tmp.second;
				}
				pos++;
			}
			else{
				if(x==3&&(now-=tmp.first-pos)<0||x!=3){
					if(now<0) pos=tmp.first+now;
					break;
				}
				pos=tmp.first;
			}
		}
		if(x==3&&now>0) pos+=now;
		res.emplace(pos,x);
		while(!res.empty()){
			st.push(res.top());res.pop();
		}
	}
	init();
	print(a);
	print(b);
	return 0;
}

```

