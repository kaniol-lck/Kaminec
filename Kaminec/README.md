# The Souce Code of Kaminec Launcher

> Welcome to see my pity code.
>
> --Kaniol

## The Source Code Structure of Kaminec Launcher

```lua
.
+--assistance
|  +--files...
+--core
|  +--auth
|  |  +--files...
|  +--json
|  |  +--files...
|  +--files...
+--downloader
|  +--files...
+--LAminec
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
- core
- downloader
- LAminec
- messager
- resources
- UI

*AS YOU SEE IN THIS DIRECTORY*

## Description of These Main Parts

- `assistance/` includes my utilities which helps my work,such as template function `value` used to index `QVariant` object much quicker and more readable.
- `core/` is the core of Kamine Launcher.All the things like Launching game or generating start code or authenticate account are in it.
- `downloader/` .There is a implementation of universal downloader(with multi-task) to support my download works.Cases to download is downloading game and fixing game file.
- `LAminec/` is a collection of assorted funtionalities.
- `messager/` includes the simple message classes.
- `resources/` includes the resource I used in this project.
- `UI/` is the User Interface of Kaminec Launcher.

## Acknowledge

Thanks to my friend [@Lambol](https://github.com/LambolAlee).He always gives me many advice and some knowledge when I am writing this launcher.

Here is his project:[【GitHub】LambolAlee/LAminec](https://github.com/LambolAlee/LAminec)

For this reason that collection parts is named LAminec.