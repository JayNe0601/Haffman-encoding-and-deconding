#include<easyx.h>
#include<iostream>
#include"Haffman.h"
using namespace std;
int R[7] = { 235,240,255,117,80,0,115 };
int G[7] = { 51,135,253,249,127,35,43 };
int B[7] = { 36,89,85,77.128,245,245 };
void CreatHuffmanTree(HuffmanTree* ht, int n, char* text) {
	int i, j, firstmin, secondmin, first, second;
	ht[0].s = ' ';//空格为0号单元直接存
	ht[0].parent = ht[0].lchild = ht[0].rchild = -1;
	ht[0].weight = 0;
	for (i = 1; i < 27; i++) {
		ht[i].s = 'a' + i - 1;
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
		ht[i].weight = 0;
	}
	for (i = 1; i < 11; i++) {
		ht[i + 26].s = '0' + i - 1;
		ht[i + 26].parent = ht[i + 26].lchild = ht[i + 26].rchild = -1;
		ht[i + 26].weight = 0;
	}
	for (i = 0; i < strlen(text); i++) {
		if (text[i] == ' ') ht[0].weight++;
		else if (text[i] >= 'a' && text[i] <= 'z') {
			int j = text[i] - 'a' + 1;
			ht[j].weight++;
		}
		else if (text[i] >= '0' && text[i] <= '9') {
			int j = text[i] - '0' + 27;
			ht[j].weight++;
		}
		else {
			cout << "输入文本有误" << endl;
			break;
		}
	}
	cout << "打印文本出现各个字符的频度：" << endl;
	for (int i = 0; i < n; i++) cout << ht[i].s << '\t' << ht[i].weight << endl;
	for (i = n; i < 2 * n - 1; i++) {
		firstmin = 99999;//最小值
		secondmin = 99999;//次最小值
		first = 0;
		second = 0;//记录最小值和次最小值的下标
		for (int j = 0; j < i; j++) {
			if (ht[j].parent == -1) {
				if (ht[j].weight < firstmin) {
					second = first;
					secondmin = firstmin;
					firstmin = ht[j].weight;
					first = j;
				}
				else if (ht[j].weight < secondmin) {
					secondmin = ht[j].weight;
					second = j;
				}
			}
		}
		ht[i].weight = ht[first].weight + ht[second].weight;
		ht[i].s = ' ';//新节点方便整体输出加入字符空格
		ht[i].lchild = first;
		ht[i].rchild = second;
		ht[first].parent = i;
		ht[second].parent = i;
		ht[i].parent = -1;//新节点没有双亲
	}//构建哈夫曼的过程注意 找到的最小值作为新根的左孩子，次小值作为右孩子
}//创建哈夫曼树
void PrintcreateTree(HuffmanTree* ht, int n) {
	PrintHuffmanTree(ht, n);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			closegraph();
			break;
		}
	}//按下ESC键时退出循环,结束图画
	closegraph();
}
void HuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int f;
	cout << "选择编码顺序，正向（1），逆序（0）：";
	cin >> f;
	if (f == 0) RHuffmanCoding(ht, codetext, n);
	else if (f == 1) FHuffmanCoding(ht, codetext, n);
}//哈夫曼编码
void RHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int p, c;
	hashlist s;
	for (int i = 0; i < n; i++) {
		c = i;//将树中的第一个字符的下标给c暂存
		p = ht[c].parent;//找到c下标字符的双亲给p暂存
		s.cnt = n; //把cnt的值初始化为n，后续再用数组存字符的编码时, 倒着存
		s.code[n] = '\0';
		while (p != -1) {
			if (ht[p].lchild == c) s.code[--s.cnt] = '0';
			else s.code[--s.cnt] = '1';
			c = p;
			p = ht[c].parent;
		}//将第i个字符从它自身找到它的双亲为止
		codetext[i] = s;//第i个字符的编码存入codetext
		codetext[i].s = ht[i].s;
	}
}//逆向哈夫曼编码
void FHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int c, p;
	hashlist s;
	for (int i = 0; i < n; i++) {
		c = i;//将树中的第一个字符的下标给c暂存
		p = ht[c].parent;//找到c下标字符的双亲给p暂存
		s.cnt = 0;// 将cnt的值初始化为0，后续再用数组存字符的编码时, 正着存
		while (p != -1) {
			if (ht[p].lchild == c) s.code[s.cnt++] = '0';
			else s.code[s.cnt++] = '1';
			c = p;
			p = ht[p].parent;
		}// 将第i个字符从它自身找到根节点为止
		s.code[s.cnt] = '\0';
		int start = 0;
		int end = s.cnt - 1;
		while (start < end) {
			int temp = s.code[start];
			s.code[start] = s.code[end];
			s.code[end] = temp;
			start++;
			end--;
		}//将编码逆序
		s.cnt = 0;//将cnt的值反转为正确的顺序
		codetext[i] = s;
		codetext[i].s = ht[i].s;
	}
}//正向哈夫曼编码
void PrintHuffmanTreenode(hashlist* codetext, int n) {
	for (int i = 0; i < n; i++) {
		cout << i + 1 << '\t';
		cout << codetext[i].s << "：";
		int index = codetext[i].cnt;
		while (codetext[i].code[index] != '\0') cout << codetext[i].code[index++];
		cout << endl;
	}
}//打印哈夫曼编译表（即哈希表的数据）
void scanfstring(char* str) {
	int lens = 0;
	while (1) {
		cin.get(str[lens]);
		if (str[lens] == '#') {
			str[lens] = '\0';
			break;
		}
		lens++;
	}
}//输入需要编码的字符串
void PrintHuffmanCoding(hashlist* codetext, char* str, int lens) {
	for (int i = 0; i < lens; i++) {
		int index;
		if (str[i] == ' ') {
			index = 0;
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') cout << codetext[index].code[len++];
		}
		else if (str[i] <= 'z' && str[i] >= 'a') {
			index = (int)(str[i] - 'a' + 1);
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') cout << codetext[index].code[len++];
		}
		else if (str[i] <= '9' && str[i] >= '0') {
			index = (int)(str[i] - '0' + 27);
			int len = codetext[index].cnt;
			while (codetext[index].code[len] != '\0') cout << codetext[index].code[len++];
		}
	}
	cout << endl;
}//打印编码结果
void HuffmanDecoding(HuffmanTree* ht, int n, char* pwd, char* Ppwd) {
	int ct = 0, Ppwdlen = 0;
	char s;
	cin >> s;
	Ppwd[Ppwdlen++] = s;
	int i = 2 * n - 2; //根结点的下标（地址）为2* N - 2
	while (s != '#') {
		if (s == '0') i = ht[i].lchild;//‘0’判断左走
		else if (s == '1') i = ht[i].rchild;//‘1’判断右走
		if (ht[i].lchild == -1 || ht[i].rchild == -1) {
			pwd[ct++] = ht[i].s;
			i = 2 * n - 2;//译完一段编码后置为头结点继续翻译
		}//从根结点一直找到叶子
		cin >> s;
		Ppwd[Ppwdlen++] = s;
	}//#结束后不再翻译
	if ((ht[i].lchild != -1 || ht[i].rchild != -1) && i != 2 * n - 2) cout << "编码有误！";
	pwd[ct] = '\0';
	Ppwd[Ppwdlen] = '\0';
}//哈夫曼译码
void Treemap(HuffmanTree* ht, int startx, int endx, int d, int r, int i, int j) {
	circle((startx + endx) / 2, j * 20 + (j - 1) * (d + r), r);
	if (ht[i].lchild == -1 || ht[i].rchild == -1) outtextxy((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + 2 * r, ht[i].s);
	if (ht[i].lchild != -1) {
		line((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + r, (startx + (startx + endx) / 2) / 2, (j + 1) * 20 + j * (d + r));
		outtextxy(((startx + endx) / 2 + (startx + (startx + endx) / 2) / 2) / 2 - 5, (j * 20 + (j - 1) * (d + r) + r + (j + 1) * 20 + j * (d + r)) / 2 - 5, '0');
		Treemap(ht, startx, (startx + endx) / 2, d, r, ht[i].lchild, j + 1);
	}
	if (ht[i].rchild != -1) {
		line((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + r, (endx + (startx + endx) / 2) / 2, (j + 1) * 20 + j * (d + r));
		outtextxy(((startx + endx) / 2 + (endx + (startx + endx) / 2) / 2) / 2 + 5, (j * 20 + (j - 1) * (d + r) + r + (j + 1) * 20 + j * (d + r)) / 2 - 5, '1');
		Treemap(ht, (startx + endx) / 2, endx, d, r, ht[i].rchild, j + 1);
	}
}//递归遍历哈夫曼树，同时画节点和树枝
void PrintHuffmanTree(HuffmanTree* ht, int n) {
	initgraph(1800, 600);//创建窗口显示二叉树
	int i = 2 * n - 2; //根结点的下标（地址）为2* N - 2
	int j = 1;//层数
	int r = 5;//半径
	int d = 30;//间隔
	int startx = 0;//x轴最小坐标
	int endx = 1700;//x轴最大坐标
	Treemap(ht, startx, endx, d, r, i, j);//递归画图
}//打印哈夫曼树
void PrintHuffmanDecoding(HuffmanTree* ht, int n, char* Ppwd) {
	PrintHuffmanTree(ht, n);
	int j = 1;//层数
	int r = 5;//半径
	int d = 30;//间隔
	int startx = 0;//x轴最小坐标
	int endx = 1700;//x轴最大坐标
	int i = 2 * n - 2; //根结点的下标（地址）为2* N - 2
	int Ppwdlen = 0;
	int rgb = 0;
	while (Ppwd[Ppwdlen] != '\0') {
		setlinecolor(RGB(R[(rgb) % 7], G[(rgb) % 7], B[(rgb) % 7]));
		rgb++;
		circle((startx + endx) / 2, j * 20 + (j - 1) * (d + r), r);
		Sleep(500);
		if (Ppwd[Ppwdlen] == '0') {
			setlinecolor(RGB(R[(rgb) % 7], G[(rgb) % 7], B[(rgb) % 7]));
			rgb++;
			lineArrow((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + r, (startx + (startx + endx) / 2) / 2, (j + 1) * 20 + j * (d + r));
			Sleep(500);
			settextcolor(LIGHTRED);
			outtextxy(((startx + endx) / 2 + (startx + (startx + endx) / 2) / 2) / 2 - 5, (j * 20 + (j - 1) * (d + r) + r + (j + 1) * 20 + j * (d + r)) / 2 - 5, Ppwd[Ppwdlen]);
			Sleep(500);
			endx = (startx + endx) / 2;
			i = ht[i].lchild;
			j++;
		}//‘0’判断左走
		else if (Ppwd[Ppwdlen] == '1') {
			setlinecolor(RGB(R[(rgb) % 7], G[(rgb) % 7], B[(rgb) % 7]));
			rgb++;
			lineArrow((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + r, (endx + (startx + endx) / 2) / 2, (j + 1) * 20 + j * (d + r));
			Sleep(500);
			settextcolor(LIGHTRED);
			outtextxy(((startx + endx) / 2 + (endx + (startx + endx) / 2) / 2) / 2 + 5, (j * 20 + (j - 1) * (d + r) + r + (j + 1) * 20 + j * (d + r)) / 2 - 5, Ppwd[Ppwdlen]);
			Sleep(500);
			startx = (startx + endx) / 2;
			i = ht[i].rchild;
			j++;
		}//‘1’判断右走
		if (ht[i].lchild == -1 || ht[i].rchild == -1) {
			setlinecolor(RGB(R[(rgb) % 7], G[(rgb) % 7], B[(rgb) % 7]));
			rgb++;
			circle((startx + endx) / 2, j * 20 + (j - 1) * (d + r), r);
			Sleep(500);
			settextcolor(LIGHTRED);
			outtextxy((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + 2 * r, ht[i].s);
			Sleep(500);
			setlinecolor(RGB(R[(rgb) % 7], G[(rgb) % 7], B[(rgb) % 7]));
			rgb++;
			lineArrow((startx + endx) / 2, j * 20 + (j - 1) * (d + r) + r, (0 + 1700) / 2, 1 * 20 + (1 - 1) * (30 + 2) + 2);
			Sleep(500);
			//重置
			j = 1;//层数
			r = 5;//半径
			d = 30;//间隔
			startx = 0;//x轴最小坐标
			endx = 1700;//x轴最大坐标
			i = 2 * n - 2;
		}//从根结点一直找到一个叶子节点
		Ppwdlen++;
	}
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			closegraph();
			break;
		}
	}//按下ESC键时退出循环,结束图画
	closegraph();
}//图像界面显示哈夫曼树译码过程
void lineArrow(int x1, int y1, int x2, int y2) {
	line(x1, y1, x2, y2);
	double distance = sqrt((y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2));
	double tmpx = double(x1 + (x2 - x1) * (1 - (12 * sqrt(3) / 2) / distance));
	double tmpy = double(y1 + (y2 - y1) * (1 - (12 * sqrt(3) / 2) / distance));
	if (y1 == y2) {
		line(x2, y2, int(tmpx), int(tmpy + 6));
		line(x2, y2, int(tmpx), int(tmpy - 6));
	}
	else {
		double k = (double(x2) - double(x1)) / (double(y1) - double(y2));
		double increX = 6 / sqrt(k * k + 1);
		double increY = 6 * k / sqrt(k * k + 1);
		line(x2, y2, int(tmpx + increX), int(tmpy + increY));
		line(x2, y2, int(tmpx - increX), int(tmpy - increY));
	}
}//easyX画箭头