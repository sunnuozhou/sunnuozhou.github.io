---
title: 让goolge收录hexo博客
tags:
  - 技术
date: 2020-01-28 17:48:18
categories: 教程
top: 
---

我发现在google上搜不到自己的博客，就研究了一下。

### 生成站点地图

先在自己的网站中生成站点地图，在博客目录下`npm install hexo-generator-sitemap --save`安装插件。

然后再配置文件中插入以下内容：

```yml
# 自动生成sitemap
sitemap: 
  path: sitemap.xml
```

现在`hexo g`之后就可以在`/public`中发现`sitemap.xml`。



### 验证网站所有权

我选的是$google$推荐的验证方式——上传html。先在[Google Search Console](https://search.google.com/search-console/welcome)输入你的网址，选择继续，把$google$的html放到博客文件夹的`public`目录下，然后`hexo d`上传。

等上传完后开始验证就好了。



### 上传站点地图

在左侧选择站点地图一项，输入站点地图的位置，然后上传就好了。