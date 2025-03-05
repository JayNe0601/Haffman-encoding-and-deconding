#pragma once
#ifndef _Haffman_H_
#define _Haffman_H_
#include<iostream>
typedef struct {
	double weight;//�ڵ���Ȩֵ
	char s;//�ڵ�����
	int parent, lchild, rchild;//�ڵ�ĸ��׽ڵ㣬���ӽڵ㣬�Һ��ӽڵ�
}HuffmanTree;//Ĭ�Ϲ������������ո�a--z��0--9��37���ڵ�
typedef struct {
	char s;//����Ľڵ�����
	char code[38];//��������ַ���
	int cnt;
}hashlist;//�������Ϣ�����飨һ����������
void CreatHuffmanTree(HuffmanTree* ht, int n, char* text);//������������
void PrintcreateTree(HuffmanTree* ht, int n);//�������������Ĺ���
void Treemap(HuffmanTree* ht, int startx, int endx, int d, int r, int i, int j);//�ݹ��������������ͬʱ���ڵ����֦,iΪ��������ht�Ľڵ��ַ��dΪͼ��ڵ����µľ��룬rΪ�ڵ�İ뾶��jΪ����
void PrintHuffmanTree(HuffmanTree* ht, int n);//ͼ����ӡ��������
void HuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//����������
void RHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//�������������
void FHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n);//�������������
void PrintHuffmanTreenode(hashlist* codetext, int n);//��ӡ���������������ϣ������ݣ�
void scanfstring(char* str);//������Ҫ������ַ���
void PrintHuffmanCoding(hashlist* codetext, char* str, int lens);//��ӡ������
void HuffmanDecoding(HuffmanTree* ht, int n, char* pwd, char* Ppwd);//���������벢���ı��봫��Ppwd;
void PrintHuffmanDecoding(HuffmanTree* ht, int n, char* pwd);//ͼ�������ʾ���������������
void lineArrow(int x1, int y1, int x2, int y2);//easyX����ͷ
#endif // !_Haffman_H_