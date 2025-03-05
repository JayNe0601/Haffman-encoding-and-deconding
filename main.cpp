#include<iostream>
#include<easyx.h>
#include"Haffman.h"
using namespace std;
int main() {
	char c;
	int n = 37;//字符个数
	char str[200], text[1000];
	char* pwd, * Ppwd;
	HuffmanTree* ht;
	hashlist* codetext;//存编码信息的数组，大小动态分配
	codetext = (hashlist*)malloc(sizeof(hashlist) * n);//给codetext数组分配空间
	pwd = (char*)malloc(sizeof(char) * 100);
	Ppwd = (char*)malloc(sizeof(char) * 100);
	ht = (HuffmanTree*)malloc(sizeof(HuffmanTree) * (2 * n - 1));//哈夫曼树结点个数
	cout << "文本为（以#结束）：" << endl;
	scanfstring(text);
	CreatHuffmanTree(ht, n, text);//创建哈夫曼树
	PrintcreateTree(ht, n);//图像界面显示哈夫曼树
	HuffmanCoding(ht, codetext, n);//哈夫曼编码
	cout << "编码对应的哈夫曼表" << endl;
	PrintHuffmanTreenode(codetext, n);//打印编码表（即哈希表的数据）
	cout << "请输入需要编码的字符串（以#结束）：" << endl;
	scanfstring(str);//输入字符串
	cout << "该字符串编码为：" << endl;
	PrintHuffmanCoding(codetext, str, strlen(str));//打印编码结果
	cout << "输入需要译文的编码（以#结束）：" << endl;
	HuffmanDecoding(ht, n, pwd, Ppwd);//解码
	cout << "编码译文为：" << endl << pwd;
	PrintHuffmanDecoding(ht, n, Ppwd);//图像界面显示哈夫曼树译码过程
	return 0;
}
