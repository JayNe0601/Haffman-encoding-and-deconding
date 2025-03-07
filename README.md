# 哈夫曼编码与译码
## 简介
> 该项目是一个实现哈夫曼编码和解码的程序。哈夫曼编码是一种无损数据压缩算法，通过使用变长编码表来表示输入字符，常用于文件压缩和数据传输。编码实现正向与逆向两种方式，并实现了图形化界面展示。
## 项目框架
> 项目主要包括以下几个部分：
> 1. 编码部分：将输入的字符转换为哈夫曼编码。
> 2. 解码部分：将哈夫曼编码转换回原始字符。
## 主要特性
> 1. 实现哈夫曼编码和解码算法。
> 2. 支持文件读写操作。
> 3. 提供简单的图形化界面。
## 技术栈
> 1. 编程语言：C++
> 2. 标准库：C++标准库
> 3. 图形库：esayX库
## 功能说明
> 1. encode：读取输入文件，生成哈夫曼编码，并将编码结果写入输出文件。
> 2. decode：读取编码文件，解码为原始字符，并将结果写入输出文件。
## 目录结构
```
├── 头文件
│   └── Haffman.c
├── 源文件
│   └── Haffman.cpp
│   └── main.cpp
├── 解析ppt
    └── Haffman.pptx
```
