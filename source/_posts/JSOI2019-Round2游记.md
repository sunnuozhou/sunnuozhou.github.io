---
title: JSOI2019-Round2游记
date: 2020-01-08 21:44:32
tags:
- OI
- 游记
categories: 实事记录
---

JSOI2019-ROUND2-游记

## Day0

中午就到了南京，愉快地颓废了一下午之后就去试机了。南航的机房通风不是很好，在机房里很闷，而且试机的时候有好多电脑开不起来，我用的那台电脑Linux有点卡，我写了一个FFT，跑1000000的数据要0.7s，比在Luogu上都慢，整体感觉不是很好。



## Day1

到了以后一直等到8:11才进场，JSOI又咕咕了。

<!-- more -->

T1看完没什么思路，数据范围又大得很，T2感觉像是充满JSOI风格的树形dp，仔细想一想感觉好像会做了，T3看完觉得不太可做，脑补了一个后缀数组的30分做法就去想T1了。

我想了一会儿T1，发现这好像是一个2-sat问题，然后我就脑补了一个假算法开始写，写了一半发现这是假算法，心态有一点小崩，再想了想，会了一个用bitset优化的做法，但只有60分了，为了调整心态，我决定先放弃T1，去做T2，这时候已经9:17了。

我先行云流水地码完了T2，一测样例发现WA了，仔细一想，发现我的做法又是假的。心态崩了，我两题满分做法全是假的，我当时感觉我可能三位数都上不了了（T2几乎没有暴力分）。我花了5-10分钟调整了心态，重新开始想T2。经过了将近30分钟的思考，我终于会做T2了，一遍就过了样例，内心有点激动。我在差不多10:30的时候写完了对拍，结果一拍就出错。我错的是m=1的数据，但我完全不知道为什么错（我当时已经几乎思考不动了）。我就不断换容斥系数，好不容易m=1的数据对了，样例却WA了。我当时真心觉得自己没什么问题，就先不管m=1的情况，去对拍m!=1的数据，然后发现m!=1的数据我没问题。我仔细想了一想，发现m=1的时候好像是特殊情况，和m!=1不一样，不是我算法的问题，于是我就把m=1的数据特判掉，然后不管T2了。

写完T2已经11:00了，我又开始回去写T1，但这时候我心态已经好多了，很快就把T1写完了，经过很长时间的调试，我终于过了第一个样例，但第二个样例一直不对，当时已经12:00过了，而我T3还动都没动。时间一分一秒地过去，我心里很急，但也没有什么好办法，只能努力保持头脑清晰，全力调试。运气不错，我终于在12:40的时候调出来了错，原来是因为我是在我以前的假算法上做的修改，给一个数组换名字的时候有一个地方没换到。

已经12:40了，我想着我也写不出T3的30分了，还不如检查一下我的T1和T2。我花了10分钟检查了我的代码，并把它们放到了提交目录下面。在12:50的时候，监考的老师说因为开考的时间推迟了，所以到13:11才收题。我当时已经检查了一遍了，就想尝试写写T3的暴力，没想到我15分钟不到就写完调完了一个后缀数组。我把3题全都放到提交目录已经13:08了，我再检查了一遍发现我T1数组大小不太对，就赶紧改了过了（事实上这根本不影响结果）。

我在的那个考场一次只能有一个人去上厕所，我每次去上厕所都有1-2分钟的延迟。为了节约比赛时间，我就只喝了3瓶水（一般情况下我一场考试会喝4-5瓶）。

考完之后一交流发现大家都不是很高，本来我以为会被全场切的T2也没几个人写对。而且今天我也没有像ROUND1一样FST，居然考了第二。成绩折算下来一看，发现我居然翻到了省队第六（不算南外的初二神仙djq）。

ROUND1考完后我本来都有点抱着打酱油的心态了，结果这次意外的考得不错，看来我暂时可以不用AFO了。