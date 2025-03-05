#include<iostream>
#include<easyx.h>
#include"Haffman.h"
using namespace std;
int main() {
	char c;
	int n = 37;//�ַ�����
	char str[200], text[1000];
	char* pwd, * Ppwd;
	HuffmanTree* ht;
	hashlist* codetext;//�������Ϣ�����飬��С��̬����
	codetext = (hashlist*)malloc(sizeof(hashlist) * n);//��codetext�������ռ�
	pwd = (char*)malloc(sizeof(char) * 100);
	Ppwd = (char*)malloc(sizeof(char) * 100);
	ht = (HuffmanTree*)malloc(sizeof(HuffmanTree) * (2 * n - 1));//��������������
	cout << "�ı�Ϊ����#��������" << endl;
	scanfstring(text);
	CreatHuffmanTree(ht, n, text);//������������
	PrintcreateTree(ht, n);//ͼ�������ʾ��������
	HuffmanCoding(ht, codetext, n);//����������
	cout << "�����Ӧ�Ĺ�������" << endl;
	PrintHuffmanTreenode(codetext, n);//��ӡ���������ϣ������ݣ�
	cout << "��������Ҫ������ַ�������#��������" << endl;
	scanfstring(str);//�����ַ���
	cout << "���ַ�������Ϊ��" << endl;
	PrintHuffmanCoding(codetext, str, strlen(str));//��ӡ������
	cout << "������Ҫ���ĵı��루��#��������" << endl;
	HuffmanDecoding(ht, n, pwd, Ppwd);//����
	cout << "��������Ϊ��" << endl << pwd;
	PrintHuffmanDecoding(ht, n, Ppwd);//ͼ�������ʾ���������������
	return 0;
}
