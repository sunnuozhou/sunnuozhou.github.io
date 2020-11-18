---
title: 修复vim插件youcompleteme
tags:
  - 技术
  - vim
date: 2020-11-18 16:33:00
categories: 教程
top:
---

自从我升级到Ubuntu20.04，我的`vim-youcompleteme`就挂了，它显示找不到`.ycm_extra_conf.py`，如果只是报个错还问题不大，但它在我每次编译的时候都会报一个 `value error`，就让我很烦。

当时因为集训队作业突然布置下来，我就没有时间来搞这个事情，就先把`vim-youcompleteme`删了，但在我后续的写题过程中，我发现没有补全还是有一点难受的，于是就准备修一修`vim-youcompleteme`。

<!--more-->

由于我是用`apt`装的插件，而网上别人的安装教程都是用`Plug`或者`bundle`装的，所以我没在网上找到和我一样问题的人。于是我就先找了一个别人的`.ycm_extra_conf.py`先用上，并且把我的`.vimrc`里关于`ycm`的配置都注释了。这时候如果我打开一个`.cpp`文件，它会问我是否要加载这个配置文件，如果我选是，它就会给我的程序报一堆错，比如找不到`bits/stdc++.h`，没有定义`isdigit()`，`getchar()`之类的，而如果选否，这个配置文件就和没加一个，依然是找不到`.ycm_extra_conf.py`。

我在网上搜了半天教程，都没有搜到，这时候我误打误撞把原来注释掉的`let g:ycm_show_diagnostics_ui=0`复原了，然后这些烦人的报错就消失了。我看它在往好的方向发展，就没多管。

还有一个问题是它找不到我的头文件，只会在`~/`里找文件。这个问题倒是很多人有，但也没有给出什么好的解答。后来在我的不断试错下，我把原来的：

```python
flags = [
'-Wall',
'-Wextra',
'-Wno-long-long',
'-Wno-variadic-macros',
'-fexceptions',
'-stdlib=libc++',
'-std=c++11',
'-x',
'c++',
'-I',
'.',
'-isystem',
'/usr/include',
'-isystem',
'/usr/local/include',
'-isystem',
'/Library/Developer/CommandLineTools/usr/include',
'-isystem',
'/Library/Developer/CommandLineTools/usr/bin/../lib/c++/v1',
]
```

改为了

```python
flags = [
'-Wall',
'-Wextra',
'-Wno-long-long',
'-Wno-variadic-macros',
'-fexceptions',
'-stdlib=libc++',
'-std=c++14',
'-x',
'c++',
'.',
'-isystem',
'-I/usr/include',
'-I/usr/local/include',
'-I/usr/include/c++/9',
'-I/usr/include/x86_64-linux-gnu/c++/9',
]
```

然后它就好了。

在把这些弄好后，我才意识到是我去掉注释关掉了报错，我又把报错功能开启了一下，发现它现在已经正常了，而且我也想起来了我就是嫌它的这个功能刷新太慢才把它关掉的。