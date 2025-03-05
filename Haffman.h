#pragma once
#ifndef _Haffman_H_
#define _Haffman_H_
#include<iostream>
typedef struct {
	double weight;//节点所权值
	char s;//节点数据
	int parent, lchild, rchild;//节点的父亲节点，左孩子节点，右孩子节点
}HuffmanTree;//默认哈夫曼树包括空格，a--z，0--9共37个节点
typedef struct {
	char s;//存入的节点数据
	char code[38];//存入编码字符串
	int cnt;
}hashlist;//存编码信息的数组（一个哈夫曼表）
void CreatHuffmanTree(HuffmanTree* ht, int n, char* text);//创建哈夫曼树
void PrintcreateTree(HuffmanTree* ht, int n);//画创建二叉树的过程
void Treemap(HuffmanTree* ht, int startx, int endx, int d, int r, int i, int j);//递归遍历哈夫曼树，同时画节点和树枝,i为哈夫曼树ht的节点地址，d为图像节点上下的距离，r为节点的半径，j为层数
void PrintHuffmanTree(HuffmanTree* ht, int n);//图化打印哈夫曼树
void HuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//哈夫曼编码
void RHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//逆向哈夫曼编码
void FHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//正向哈夫曼编码
void PrintHuffmanTreenode(hashlist* codetext, int n);//打印哈夫曼编译表（即哈希表的数据）
void scanfstring(char* str);//输入需要编码的字符串
void PrintHuffmanCoding(hashlist* codetext, char* str, int lens);//打印编码结果
void HuffmanDecoding(HuffmanTree* ht, int n, char* pwd, char* Ppwd);//哈夫曼译码并将改编码传给Ppwd;
void PrintHuffmanDecoding(HuffmanTree* ht, int n, char* pwd);//图像界面显示哈夫曼树译码过程
void lineArrow(int x1, int y1, int x2, int y2);//easyX画箭头
#endif // !_Haffman_H_