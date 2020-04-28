#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<fstream>
using namespace std;
typedef class WhatIsStudent {
public:
	char stunum[30] ;
	char stuname[30];
	char stuschool[25];
	char stutype[25];
	int stuscore1;
	int stuscore2;
	int stuscore3;
	int stuscoretest;
	int stuscorefinally;
}Student;	//小吴这么写只是想训练一下typedef的用法0.0

typedef class MyNode {
public:
	Student stu;			//数据 
	class MyNode* pNext;	//模仿链表用上一结点链接下一个值 
}Node;		//小吴觉得这样写看起来比较厉害

void InputStudent();//录入学生信息1
void PrintfStudent();//打印2
void ChangeDeleteSearchStudent(int a, char stdnum[]);//删除8
void LittleChange(Node* pnow);
void ReadTXT(char* file);
void SaveTXT(char* file);

Node* p_head = nullptr;
int counts = 0;
char stdnum[30];
char* file = (char*)"student.txt";
void menu(int thetimenow) {
	printf("========武汉大学大作业--学生成绩管理系统========\n");
	printf("\t========请选择功能========\n");
	printf("\t\t1.录入学生信息\n");
	printf("\t\t2.打印学生信息\n");
	printf("\t\t3.保存学生信息\n");
	printf("\t\t4.读取学生信息\n");
	printf("\t\t5.统计学生人数\n");
	printf("\t\t6.查找学生信息\n");
	printf("\t\t7.修改学生信息\n");
	printf("\t\t8.删除学生信息\n");
	printf("\t\t0.====退出====\n");
	printf("==================================================\n");
}
void contolmenu(int thetimenow, char stdnum[]) {
	switch (thetimenow) {
	case 1:
		InputStudent();
		break;
	case 2:
		PrintfStudent();
		break;
	case 3:
		SaveTXT(file);
		break;
	case 4:
		ReadTXT(file);
		break;
	case 5:
		printf("一共%d名学生\n",counts);
		break;
	case 6:
		printf("请输入查找学生的学号\n");
		scanf("%s", stdnum);
		ChangeDeleteSearchStudent(thetimenow, stdnum);
		break;
	case 7:
		printf("请输入修改学生的学号\n");
		scanf("%s", stdnum);
		ChangeDeleteSearchStudent(thetimenow, stdnum);
		break;
	case 8:
		printf("请输入删除学生的学号\n");
		scanf("%s", stdnum);
		ChangeDeleteSearchStudent(thetimenow, stdnum);
		break;
	default:
		printf("输入错误，请重新输入\n");
	}
}
int main()
{
	ReadTXT(file);
	int thetimenow = 99;
	menu(thetimenow);
	cin >> thetimenow;
	while (thetimenow != 0) {
		contolmenu(thetimenow,stdnum);
		printf("请重新输入数字1~8或0\n");
		if (cin>>thetimenow);
		{		
		system("cls"); 
		menu(thetimenow); 
		}
	}
	printf("已退出");
	return 0;
}

void InputStudent() {
	counts++;
	printf("\n请输入学生信息:学号: 姓名：所在院系： 学习类型： 成绩1： 成绩2： 成绩3： 期末成绩： 总评成绩：\n");
	Node* p;//当前结点
	p = p_head;
	while (p_head != nullptr && p->pNext != nullptr) {//当前结点的地址不是null 下一个结点地址也不是null的话
		p = p->pNext;//然后把现结点的地址变成下一个结点的地址 直到现在的节点为Null
	}
	//再弄一个新节点
	Node* pNew = (Node*)malloc(sizeof(Node));//开辟一个内存
	pNew->pNext = nullptr;
	if (p_head == nullptr) {
		p_head = pNew;
		p = p_head;
	}
	else {
		p->pNext = pNew;
	}
	scanf("%s %s %s %s %d %d %d %d %d", pNew->stu.stunum,
		pNew->stu.stuname,pNew->stu.stuschool, pNew->stu.stutype,
		&pNew->stu.stuscore1, &pNew->stu.stuscore2, &pNew->stu.stuscore3, 
		&pNew->stu.stuscoretest, &pNew->stu.stuscorefinally);
	int i = counts;
	p = p_head;
	while (p!= nullptr&&i>=2) {
		if (p == nullptr) { return; }
		if (0 == strcmp(pNew->stu.stunum, p->stu.stunum)) {
			printf("学号重复，将删除原数据\n");
			ChangeDeleteSearchStudent(8, pNew->stu.stunum);
			return;
		}
		p = p->pNext; i--;
	}
	SaveTXT(file);
	printf("添加成功\n");
}

void PrintfStudent() {
	printf("打印所有学生信息\n");
	Node* p;
	p = p_head;
	if (p == nullptr) {
		printf("\t没学生了\n");
	}
	while (p != nullptr) {
		if (p->stu.stuscore1 == 0 & p->stu.stuscore2 == 0 & p->stu.stuscore3 == 0 & p->stu.stuscoretest == 0 & p->stu.stuscorefinally == 0) {
			printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t",
				p->stu.stunum, p->stu.stuname,
				p->stu.stuschool, p->stu.stutype);
			printf(" 还没出成绩\n");
		}
		else {
			printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t 成绩1：%d\t 成绩2：%d\t 成绩3：%d\t 期末成绩：%d\t 总评成绩：%d\n",
				p->stu.stunum, p->stu.stuname,
				p->stu.stuschool, p->stu.stutype,
				p->stu.stuscore1, p->stu.stuscore2, p->stu.stuscore3,
				p->stu.stuscoretest, p->stu.stuscorefinally
			);
		}
		p = p->pNext;
	}
}
void ChangeDeleteSearchStudent(int a, char stdnum[]) {//data是类似位置的意思？
	Node* p;
	Node* p1;
	p = p_head;
	if (p == nullptr) {//如下 防止越界= =
		printf("\t数据数量为0，会报错");
		return;
	}
	p1 = p->pNext;
	if (a == 8) {
		if (p1 == nullptr && 0 == strcmp(p->stu.stunum, stdnum)) {//当只有一个元素的时候 直接把头节点等于当前节点的指向的(下一个)节点(就是Null)
			p_head = p->pNext;
			free(p_head);//释放内存
			printf("\t已删除\n"); counts--;
			SaveTXT(file);
			return;
		}
		else if (0 == strcmp(stdnum, p->stu.stunum)) {//当删除的是第一个元素的时候
			p_head = p_head->pNext;//让头节点指向下一个节点
			printf("\t已删除\n"); counts--;
			free(p);
			SaveTXT(file);
			return;
		}//事实上 以上两个if和else if的删除是一样的 但是我为了凸显当前节点的特点 所以在if中使用的是p->pNext
		while (p1 != nullptr) {
			if (0 == strcmp(p1->stu.stunum, stdnum)) {
				p->pNext = p1->pNext;//让当前节点指向的节点改为 下一个节点指向的节点，其中下一个节点就是所寻节点
				printf("\t已删除\n"); counts--;
				free(p1);
				SaveTXT(file);
				return;
			}
			p = p->pNext;
			p1 = p->pNext;
		}
	}
	else if (a == 7) {
		if (p1 == nullptr && 0 == strcmp(p->stu.stunum, stdnum)) {//当只有一个元素的时候 直接把头节点等于当前节点的指向的(下一个)节点(就是Null)
			LittleChange(p_head);
			return;
		}
		else if (0 == strcmp(stdnum, p->stu.stunum)) {//当修改的是第一个元素的时候
			LittleChange(p);
			return;
		}
		while (p1 != nullptr) {
			if (0 == strcmp(p1->stu.stunum, stdnum)) {//正常的情况下
				LittleChange(p1);
				return;
			}
			p = p->pNext;
			p1 = p->pNext;
		}
	}
	else if (a == 6) {
		if (p1 == nullptr && 0 == strcmp(p->stu.stunum, stdnum)) {//当只有一个元素的时候 直接把头节点等于当前节点的指向的(下一个)节点(就是Null)
			if (p_head->stu.stuscore1 == 0 & p_head->stu.stuscore2 == 0 & p_head->stu.stuscore3 == 0 & p_head->stu.stuscoretest == 0 & p_head->stu.stuscorefinally == 0) {
				printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t",
					p_head->stu.stunum, p_head->stu.stuname,
					p_head->stu.stuschool, p_head->stu.stutype);
				printf(" 还没出成绩\n");
			}
			else {
				printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t 成绩1：%d\t 成绩2：%d\t 成绩3：%d\t 期末成绩：%d\t 总评成绩：%d\n",
					p_head->stu.stunum, p_head->stu.stuname,
					p_head->stu.stuschool, p_head->stu.stutype,
					p_head->stu.stuscore1, p_head->stu.stuscore2, p_head->stu.stuscore3,
					p_head->stu.stuscoretest, p_head->stu.stuscorefinally
				);
			}
			return;
		}
		else if (0 == strcmp(stdnum, p->stu.stunum)) {//当修改的是第一个元素的时候
			if (p->stu.stuscore1 == 0 & p->stu.stuscore2 == 0 & p->stu.stuscore3 == 0 & p->stu.stuscoretest == 0 & p->stu.stuscorefinally == 0) {
				printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t",
					p->stu.stunum, p->stu.stuname,
					p->stu.stuschool, p->stu.stutype);
				printf(" 还没出成绩\n");
			}
			else {
				printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t 成绩1：%d\t 成绩2：%d\t 成绩3：%d\t 期末成绩：%d\t 总评成绩：%d\n",
					p->stu.stunum, p->stu.stuname,
					p->stu.stuschool, p->stu.stutype,
					p->stu.stuscore1, p->stu.stuscore2, p->stu.stuscore3,
					p->stu.stuscoretest, p->stu.stuscorefinally
				);
			}
			return;
		}
		while (p1 != nullptr) {
			if (0 == strcmp(p1->stu.stunum, stdnum)) {//正常的情况下
				if (p1->stu.stuscore1 == 0 & p1->stu.stuscore2 == 0 & p1->stu.stuscore3 == 0 & p1->stu.stuscoretest == 0 & p1->stu.stuscorefinally == 0) {
					printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t",
						p1->stu.stunum, p1->stu.stuname,
						p1->stu.stuschool, p1->stu.stutype);
					printf(" 还没出成绩\n");
				}
				else {
					printf("学号:%s\t 姓名：%s\t 所在院系：%s\t 学习类型：%s\t 成绩1：%d\t 成绩2：%d\t 成绩3：%d\t 期末成绩：%d\t 总评成绩：%d\n",
						p1->stu.stunum, p1->stu.stuname,
						p1->stu.stuschool, p1->stu.stutype,
						p1->stu.stuscore1, p1->stu.stuscore2, p1->stu.stuscore3,
						p1->stu.stuscoretest, p1->stu.stuscorefinally
					);
				}
				return;
			}
			p = p->pNext;
			p1 = p->pNext;
		}
	}
		printf("\t学号输入有误\n");
		return;
}

void LittleChange(Node* pnow) {
	int times = 99;
	printf("\t已找到学生，请输入要修改的选项\n");
	while (times != 0) {
		printf("\t\t修改名字请输入“1”\n");
		printf("\t\t修改学号请输入“2”\n");
		printf("\t\t修改成绩请输入“3”\n");
		printf("\t\t退出修改请输入“0”\n");
		cin >> times;
		if (times == 1) {
			printf("\t请输入名字\n");
			cin >> pnow->stu.stuname;
			printf("\t已修改\n");
			SaveTXT(file);
		}
		else if (times == 2) {
			printf("\t请输入学号\n");
			cin >> pnow->stu.stunum;
			printf("\t已修改\n");
			SaveTXT(file);
		}
		else if (times == 3) {
			printf("\t请输入想要修改的成绩\n 修改成绩1 2 3 期末请对应输入1 2 3 4\n");
			cin >> times;
			if (times == 1)scanf("%d", &pnow->stu.stuscore1);
			else if (times == 2)scanf("%d", &pnow->stu.stuscore2);
			else if (times == 3)scanf("%d", &pnow->stu.stuscore3);
			else if (times == 4)scanf("%d", &pnow->stu.stuscoretest);
			else printf("输错了！");
			printf("\t已修改”\n");
			SaveTXT(file);
		}
		else if (times == 0) {
			break;
		}
		else {
			printf("\t输错了，请重新输入");
			printf("\t\t修改名字请输入“1”\n");
			printf("\t\t修改学号请输入“2”\n");
			printf("\t\t修改成绩请输入“3”\n");
			printf("\t\t退出修改请输入“0”\n");
		}
	}
	printf("\t已退出");
	return;
}
void ReadTXT(char* file) {
	FILE* pFile = fopen(file, "r");
	if (pFile == nullptr) {
		pFile = fopen(file, "w");
		return;
		}
	Node* p;
	p = p_head;
	while (p_head != nullptr && p->pNext != nullptr) {
		p = p->pNext;
	}
	Node* pNew = (Node*)malloc(sizeof(Node));//开辟一个内存
	pNew->pNext = nullptr;
	ifstream in;
	in.open(file);
	if (p_head == nullptr&&(in>>stdnum) ) {
		p_head = pNew;
		p = p_head;
	}
	else if((in >> stdnum)){
		p->pNext = pNew;
	}
	char a[40];
	fscanf(pFile, "%s\t %s\t %s\t %s\n", a, a, a,a);
	fscanf(pFile, "%s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\t %s\n", a, a, a, a,a, a, a, a,a);
	while ((fscanf
		(pFile, "%s %s %s %s %d %d %d %d %d", pNew->stu.stunum,
		pNew->stu.stuname, pNew->stu.stuschool, pNew->stu.stutype,
		&pNew->stu.stuscore1, &pNew->stu.stuscore2, &pNew->stu.stuscore3,
		&pNew->stu.stuscoretest, &pNew->stu.stuscorefinally)
		)!=EOF) {
		counts++;
		while (p_head != nullptr && p->pNext != nullptr) {
			p = p->pNext;
		}
		pNew = (Node*)malloc(sizeof(Node));//开辟一个内存
		pNew->pNext = nullptr;
		if (p_head == nullptr) {
			p_head = pNew;
			p = p_head;
		}
		else {
			p->pNext = pNew;
		}
	}
	if ((in >> stdnum)) { p->pNext = nullptr; }
	if (p != nullptr) {
		p->pNext = pNew->pNext;
		free(pNew);
	}
	fclose(pFile);
	}

void SaveTXT(char* file) {
	FILE* pFile = fopen(file, "w");
	Node* p;
	p = p_head;
	if (p == nullptr) {
		return;
	}
	fprintf(pFile, "课头号：\t\t 20192021044\t 课程名称\t 高级语言程序设计\n");
	fprintf(pFile, "学号\t姓名\t\t所在院系\t学习类型\t成绩1\t成绩2\t成绩3\t期末成绩\t总评成绩\n");
	while (p != nullptr) {
		fprintf(pFile, "%s\t %s\t %s\t %s\t",
			p->stu.stunum, p->stu.stuname,
			p->stu.stuschool, p->stu.stutype);
		fprintf(pFile, "%d\t %d\t %d\t %d\t %d\n" ,p->stu.stuscore1, p->stu.stuscore2, p->stu.stuscore3,
				p->stu.stuscoretest, p->stu.stuscorefinally);
		p = p->pNext;
	}
	fclose(pFile);
}
