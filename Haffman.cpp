#include<easyx.h>
#include<iostream>
#include"Haffman.h"
using namespace std;
int R[7] = { 235,240,255,117,80,0,115 };
int G[7] = { 51,135,253,249,127,35,43 };
int B[7] = { 36,89,85,77.128,245,245 };
void CreatHuffmanTree(HuffmanTree* ht, int n, char* text) {
	int i, j, firstmin, secondmin, first, second;
	ht[0].s = ' ';//�ո�Ϊ0�ŵ�Ԫֱ�Ӵ�
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
			cout << "�����ı�����" << endl;
			break;
		}
	}
	cout << "��ӡ�ı����ָ����ַ���Ƶ�ȣ�" << endl;
	for (int i = 0; i < n; i++) cout << ht[i].s << '\t' << ht[i].weight << endl;
	for (i = n; i < 2 * n - 1; i++) {
		firstmin = 99999;//��Сֵ
		secondmin = 99999;//����Сֵ
		first = 0;
		second = 0;//��¼��Сֵ�ʹ���Сֵ���±�
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
		ht[i].s = ' ';//�½ڵ㷽��������������ַ��ո�
		ht[i].lchild = first;
		ht[i].rchild = second;
		ht[first].parent = i;
		ht[second].parent = i;
		ht[i].parent = -1;//�½ڵ�û��˫��
	}//�����������Ĺ���ע�� �ҵ�����Сֵ��Ϊ�¸������ӣ���Сֵ��Ϊ�Һ���
}//������������
void PrintcreateTree(HuffmanTree* ht, int n) {
	PrintHuffmanTree(ht, n);
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			closegraph();
			break;
		}
	}//����ESC��ʱ�˳�ѭ��,����ͼ��
	closegraph();
}
void HuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int f;
	cout << "ѡ�����˳������1��������0����";
	cin >> f;
	if (f == 0) RHuffmanCoding(ht, codetext, n);
	else if (f == 1) FHuffmanCoding(ht, codetext, n);
}//����������
void RHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int p, c;
	hashlist s;
	for (int i = 0; i < n; i++) {
		c = i;//�����еĵ�һ���ַ����±��c�ݴ�
		p = ht[c].parent;//�ҵ�c�±��ַ���˫�׸�p�ݴ�
		s.cnt = n; //��cnt��ֵ��ʼ��Ϊn����������������ַ��ı���ʱ, ���Ŵ�
		s.code[n] = '\0';
		while (p != -1) {
			if (ht[p].lchild == c) s.code[--s.cnt] = '0';
			else s.code[--s.cnt] = '1';
			c = p;
			p = ht[c].parent;
		}//����i���ַ����������ҵ�����˫��Ϊֹ
		codetext[i] = s;//��i���ַ��ı������codetext
		codetext[i].s = ht[i].s;
	}
}//�������������
void FHuffmanCoding(HuffmanTree* ht, hashlist* codetext, int n) {
	int c, p;
	hashlist s;
	for (int i = 0; i < n; i++) {
		c = i;//�����еĵ�һ���ַ����±��c�ݴ�
		p = ht[c].parent;//�ҵ�c�±��ַ���˫�׸�p�ݴ�
		s.cnt = 0;// ��cnt��ֵ��ʼ��Ϊ0����������������ַ��ı���ʱ, ���Ŵ�
		while (p != -1) {
			if (ht[p].lchild == c) s.code[s.cnt++] = '0';
			else s.code[s.cnt++] = '1';
			c = p;
			p = ht[p].parent;
		}// ����i���ַ����������ҵ����ڵ�Ϊֹ
		s.code[s.cnt] = '\0';
		int start = 0;
		int end = s.cnt - 1;
		while (start < end) {
			int temp = s.code[start];
			s.code[start] = s.code[end];
			s.code[end] = temp;
			start++;
			end--;
		}//����������
		s.cnt = 0;//��cnt��ֵ��תΪ��ȷ��˳��
		codetext[i] = s;
		codetext[i].s = ht[i].s;
	}
}//�������������
void PrintHuffmanTreenode(hashlist* codetext, int n) {
	for (int i = 0; i < n; i++) {
		cout << i + 1 << '\t';
		cout << codetext[i].s << "��";
		int index = codetext[i].cnt;
		while (codetext[i].code[index] != '\0') cout << codetext[i].code[index++];
		cout << endl;
	}
}//��ӡ���������������ϣ������ݣ�
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
}//������Ҫ������ַ���
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
}//��ӡ������
void HuffmanDecoding(HuffmanTree* ht, int n, char* pwd, char* Ppwd) {
	int ct = 0, Ppwdlen = 0;
	char s;
	cin >> s;
	Ppwd[Ppwdlen++] = s;
	int i = 2 * n - 2; //�������±꣨��ַ��Ϊ2* N - 2
	while (s != '#') {
		if (s == '0') i = ht[i].lchild;//��0���ж�����
		else if (s == '1') i = ht[i].rchild;//��1���ж�����
		if (ht[i].lchild == -1 || ht[i].rchild == -1) {
			pwd[ct++] = ht[i].s;
			i = 2 * n - 2;//����һ�α������Ϊͷ����������
		}//�Ӹ����һֱ�ҵ�Ҷ��
		cin >> s;
		Ppwd[Ppwdlen++] = s;
	}//#�������ٷ���
	if ((ht[i].lchild != -1 || ht[i].rchild != -1) && i != 2 * n - 2) cout << "��������";
	pwd[ct] = '\0';
	Ppwd[Ppwdlen] = '\0';
}//����������
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
}//�ݹ��������������ͬʱ���ڵ����֦
void PrintHuffmanTree(HuffmanTree* ht, int n) {
	initgraph(1800, 600);//����������ʾ������
	int i = 2 * n - 2; //�������±꣨��ַ��Ϊ2* N - 2
	int j = 1;//����
	int r = 5;//�뾶
	int d = 30;//���
	int startx = 0;//x����С����
	int endx = 1700;//x���������
	Treemap(ht, startx, endx, d, r, i, j);//�ݹ黭ͼ
}//��ӡ��������
void PrintHuffmanDecoding(HuffmanTree* ht, int n, char* Ppwd) {
	PrintHuffmanTree(ht, n);
	int j = 1;//����
	int r = 5;//�뾶
	int d = 30;//���
	int startx = 0;//x����С����
	int endx = 1700;//x���������
	int i = 2 * n - 2; //�������±꣨��ַ��Ϊ2* N - 2
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
		}//��0���ж�����
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
		}//��1���ж�����
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
			//����
			j = 1;//����
			r = 5;//�뾶
			d = 30;//���
			startx = 0;//x����С����
			endx = 1700;//x���������
			i = 2 * n - 2;
		}//�Ӹ����һֱ�ҵ�һ��Ҷ�ӽڵ�
		Ppwdlen++;
	}
	while (true) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			closegraph();
			break;
		}
	}//����ESC��ʱ�˳�ѭ��,����ͼ��
	closegraph();
}//ͼ�������ʾ���������������
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
}//easyX����ͷ