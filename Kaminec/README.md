# The Souce Code of Kaminec Launcher

> Welcome to see my pity code.
>
> --Kaniol

## The Source Code Structure of Kaminec Launcher

```lua
.
+--assistance
|  +--files...
+--download
|  +--files...
+--exception
|  +--files...
+--kits
|  +--AssetKit
|  |  +--files...
|  +--AuthKit
|  |  +--files...
|  +--DownloadKit
|  |  +--files...
|  +--JsonKit
|  |  +--files...
|  +--Ruler
|  |  +--files...
+--LAminec
|  +--files...
+--launch
|  +--files...
+--messager
|  +--files...
+--resources
|  +--res
|  |  +--files...
|  +--files...
+--UI
|  +--files...
+--Kaminec.pro
+--main.cpp
+--README.md
```

## The Main Parts

- assistance
- download
- exception
- kits
- LAminec
- launch
- messager
- resources
- UI

*AS YOU SEE IN THIS DIRECTORY*

## Description of These Main Parts

- `assistance/` includes my utilities which helps my work,such as template function `value` used to index `QVariant` object much quicker and more readable.
- `download/` .There is a implementation of universal downloader(with multi-task) to support my download works.Cases to download is downloading game and fixing game file.
- `exception/`includes a entire exception system to manage all the exceptions that my launcher may encounter.
- `kits/` is the most important parts of Kaminec Launcher coz it packages those important works of launcher.These kits are:`Assetkit`, `AuthKit`, `DownloadKit`, `JsonKit`, `Ruler`.
- `LAminec/` is a collection of assorted funtionalities.
- `launch/` does what a launcher should essentially do.
- `messager/` includes the simple message classes.
- `resources/` includes the resource I used in this project.
- `UI/` is the User Interface of Kaminec Launcher.

## Acknowledge

Thanks to my friend [@Lambol](https://github.com/LambolAlee).He always gives me many advice and some knowledge when I am writing this launcher.

Here is his project:[【GitHub】LambolAlee/LAminec](https://github.com/LambolAlee/LAminec)

For this reason that collection parts is named LAminec.