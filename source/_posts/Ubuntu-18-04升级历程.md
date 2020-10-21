---
title: Ubuntu 18.04升级历程
tags:
  - 技术
date: 2020-10-12 13:47:16
categories: 教程
top:
---

早在今年6月份的时候，我就已经尝试过一次升级Ubuntu 18.04，但当时不知道什么原因，我的`ubuntu-desktop`居然和别的一些东西有依赖冲突，由于我完全不会处理，就暂且不管了。

<!--more-->

今天`update-manager`提醒我可以更新到Ubuntu 20.04，我才想起来还有这回事，就开始升级了，这次升级基本上没遇到什么问题就好了。

### 刚升级好时和原来区别

- 开机界面和动画变了，启动动画和锁屏好看了很多。
- 主题变成了`Adwaita`，很丑。
- 搜狗输入法没了。
- 不能往桌面拖图标。
- 在18.04里我去掉的桌面主文件夹和回收站又来了。

### 主题

虽然wyj升级的时候改主题好像出了一点问题，但我是直接在`gnome-tweaks`里把主题改成`Yaru`就好了。

### 输入法

我先尝试了一下google 输入法：

```zsh
sudo apt install fcitx-googlepinyin
```

然后先在`im-config`里启用`Fctix`，重启一下，`fcitx-config-gtk3`里就有google 输入法了。

但它的缺点挺多的：

- 输入一个单词只能按`Enter`不能按`Space`。
- 输入u会直接打出来，看着不爽。

我就还是到[wyj的博客](https://2o181o28.github.io)里找了[搜狗输入法](https://github.com/laomocode/fcitx-sogouimebs/releases/download/v2.0.0.38-debian/sogouimebs.deb)。

这次我一不小心把搜狗输入法的状态栏关了，然后我就不知道怎么加回来了，不过问题不大。

### 桌面图标

我还是跟随wyj的步伐，使用了他博客里的[插件](https://extensions.gnome.org/extension/2087/desktop-icons-ng-ding/)，先

```zsh
sudo apt install chrome-gnome-shell
```

然后在Chrome应用商店里下载“[GNOME Shell integration](https://chrome.google.com/webstore/detail/gnome-shell-integration/gphhapmejobijbbhgpjhcjognlahblep)”扩展，下好后插件页面的右上角就有了一个`OFF`，点一下改成`ON`就开始安装了。

然后需要在`Extensions`里面把原来的桌面图标去掉，不然桌面就会像被JERA了一样，每个文件都有两个。

现在也就可以去掉桌面上的主文件夹和回收站了：在桌面上右击中的`settings`里面改。

虽然这个插件的效果比18.04自带的还是差了一点，但也已经挺好用了。

### 后续问题

搜狗输入法已经奔溃两次了，目前除了重起以外完全不会解决。

在他崩溃第3次后我学会了如何重启`fcitx`。

`vim-youcompleteme`挂了，暂时没去管，就先卸了。