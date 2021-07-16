---
title: 安装nvidia驱动
tags:
  - 技术
date: 2021-07-16 15:38:42
categories: 教程
top:
---

突然发现没有装NVIDIA的驱动，就尝试装一下。

<!--more-->

## 失败的尝试

一开始我是用`sudo ubuntu-drivers autoinstall`来装的，给我装了460.84的版本。我虽然能在`/usr/src`中找到对应的文件夹，但`nvidia-smi`和`nvidia-settings`都是失败的——它们告诉我我没装NVIDIA驱动。

我在网上翻了翻教程，发现很多教程都说用`dkms`来安装模组，但我的`dkms`里根本就没记录到这个驱动，只有一个`virtualbox`。

研究半天无果，我就先假装看不见`dkms`，看看别人是怎么装的。我发现有人在装完后手动`modprobe nvidia`，也试了试，结果发现我连这个模组都没有。即使我改用`apt`重新装了一遍，也压根没有生成模组。

翻了翻别的教程，发现有人甚至是手动装的驱动，我立刻觉得这安装方法太过陈旧了，不应该是20.04所需要的方法，就改为搜20.04的安装方法。

## 解决方法

Google上[第一篇博客](https://www.myfreax.com/how-to-nvidia-drivers-on-ubuntu-20-04/)就很靠谱，我按这个来搞，一下就搞好了。
