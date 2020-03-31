#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �洢ѧ���ɼ������ݽṹ
typedef struct student{
	char name[20];
	char stuId[14];
	int math;
	int English;
	int politics;
	int specCourse;
	int totalScore;
}Student;

typedef Student ElemType;
// ������
typedef struct node{
	ElemType data;
	struct node *next;
}ListNode;

// ��������
ListNode *creatList()
{
	ListNode *head = (ListNode*)calloc(1, sizeof(ListNode));
	return head;
}
// �������
ListNode *creatNode(ElemType data)
{
	ListNode *newNode = (ListNode*)calloc(1, sizeof(ListNode));
	strcpy(newNode->data.name, data.name);
	strcpy(newNode->data.stuId, data.stuId);
	newNode->data.English = data.English;
	newNode->data.math = data.math;
	newNode->data.politics = data.politics;
	newNode->data.specCourse = data.specCourse;
	newNode->data.totalScore = data.totalScore;
	newNode->next = NULL;
	return newNode;
}

// ������
void insertNode(ListNode *head, ElemType data)
{
	ListNode *p = creatNode(data);
	p->next = head->next;
	head->next = p;
	++(head->data.totalScore); // �洢������
}

// ɾ�����
void deleteNode(ListNode *head, char *name)
{
	ListNode *pre = head, *p = head->next;
	if(p == NULL)
	{
		printf("��δ¼��ѧ����Ϣ��ɾ��ʧ�ܣ�");
		return;
	}
	while(p && strcmp(p->data.name, name) != 0)
	{
		pre = p;
		p = p->next;
	}
	if(p == NULL)
	{
		printf("δ�ҵ���ѧ����Ϣ��ɾ��ʧ�ܣ�");
		return;
	}
	pre->next = p->next;
	--(head->data.totalScore);
	free(p);
}

// ���ҽ��
ListNode *searchNode(ListNode *head, char *name)
{
	ListNode *p = head->next;
	while(p && strcmp(p->data.name, name))
	{
		p = p->next;
	}
	if(p == NULL)
	{
		printf("δ�ҵ���ѧ����Ϣ��");
	}
	return p;
}

// ��������-->��ѧ��
void sortListById(ListNode *head)
{
	ListNode *q, *tmp, *pre, *p = head->next;
	head->next = NULL;
	while(p)
	{
		q = p->next;
		pre = head;
		tmp = head->next;
		while(tmp && strcmp(tmp->data.stuId, p->data.stuId) < 0)
		{
			pre = tmp;
			tmp = tmp->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

// ��������-->���ܷ�
void sortListBySore(ListNode *head)
{
	ListNode *q, *tmp, *pre, *p = head->next;
	head->next = NULL;
	while(p)
	{
		q = p->next;
		pre = head;
		tmp = head->next;
		while(tmp && tmp->data.totalScore < p->data.totalScore)
		{
			pre = tmp;
			tmp = tmp->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
}

// ��ӡ����
void printList(ListNode *head)
{
	ListNode *p = head->next;
	if(p == NULL) 
	{
		printf("��δ¼��ѧ���ɼ�\n");
		return;
	}
	printf("ѧ��\t����\tӢ��\t����\t��ѧ\tרҵ��\t�ܷ�\n");
	while(p)
	{
		printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse, p->data.totalScore);
		p = p->next;
	}
	printf("----------------------------------------------------------\n");
	printf("���� %d ��\n", head->data.totalScore);
}

// �ļ�������
void readInfoFromFile(ListNode *head, char *fileName)
{
	FILE *fp;
	ElemType data;
	fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	while(fscanf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", data.stuId, data.name, &data.English, &data.politics, &data.math, &data.specCourse) != EOF)
	{
		insertNode(head, data);
	}
	fclose(fp);
}

// �ļ�д����
void writeInfoToFile(ListNode *head, char *fileName)
{
	FILE *fp;
	ListNode *p = head->next;
	fp = fopen(fileName, "w");
	while(p)
	{
		fprintf(fp, "%s\t%s\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse);
		p = p->next;
	}
	fclose(fp);
}
// ��ʼ����
void menu()
{
	printf("*********************ѧ���ɼ�����ϵͳ*********************\n\n");
	printf("\t\t\t0.�˳�ϵͳ\n\n");
	printf("\t\t\t1.��ʾȫ��\n\n");
	printf("\t\t\t2.��ӳɼ�\n\n");
	printf("\t\t\t3.ɾ���ɼ�\n\n");
	printf("\t\t\t4.�޸ĳɼ�\n\n");
	printf("\t\t\t5.���ҳɼ�\n\n");
	printf("**********************************************************\n");
}

// �������� 0 - 5
void keyDown(ListNode *head)
{
	int flag = 1, op, sortOp;
	char name[20] = {0};
	ElemType stu;
	ListNode *p;
	printf("������Ҫִ�еĲ�����0 - 5����");
	scanf("%d", &op);
	switch (op)
	{
	case 0:
		exit(0);
		break;
	case 1:
		printf("*************************��ʾȫ��*************************\n");
		while(flag)
		{
			printf("�����루1.��ѧ������ 2.���ܷ����� 3.��������");
			scanf("%d", &sortOp);
			printf("**********************************************************\n");
			if(sortOp == 1)
				sortListById(head);
			if(sortOp == 2)
				sortListBySore(head);
			printList(head);
			printf("----------------------------------------------------------\n");
			printf("�����루0.�ص������� 1.�����鿴����");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("���벻�Ϸ������������룺");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		break;
	case 2:
		printf("*************************��ӳɼ�*************************\n");
		while(flag)
		{
			printf("������ѧ��ѧ�ţ�");
			fflush(stdin);
			scanf("%s", stu.stuId);
			printf("������ѧ��������");
			fflush(stdin);
			scanf("%s", stu.name);
			printf("������Ӣ��ɼ���");
			scanf("%d", &(stu.English));
			printf("���������γɼ���");
			scanf("%d", &(stu.politics));
			printf("��������ѧ�ɼ���");
			scanf("%d", &(stu.math));
			printf("������רҵ�ɼ���");
			scanf("%d", &(stu.specCourse));
			stu.totalScore = stu.English + stu.math + stu.politics + stu.specCourse;
			insertNode(head, stu);
			printf("----------------------------------------------------------\n");
			printf("�����루0.��ӽ��� 1.������ӣ���");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("���벻�Ϸ������������룺");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("��ӳɹ�!\n");
		printf("----------------------------------------------------------\n");
		break;
	case 3:
		printf("*************************ɾ���ɼ�*************************\n");
		while(flag)
		{
			printf("������Ҫɾ����ѧ��������");
			scanf("%s", &name);
			deleteNode(head, name);
			printf("----------------------------------------------------------\n");
			printf("�����루0.ɾ������ 1.����ɾ������");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("���벻�Ϸ������������룺");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("ɾ���ɹ�!\n");
		printf("----------------------------------------------------------\n");
		break;
	case 4:
		printf("*************************�޸ĳɼ�*************************\n");
		while(flag)
		{
			printf("������Ҫ�޸ĵ�ѧ��������");
			fflush(stdin);
			scanf("%s", &name);
			p = searchNode(head, name);
			if(p)
			{
				printf("�������޸ĺ��Ӣ��ɼ������޸�������-1����");
				scanf("%d", &(stu.English));
				p->data.English = stu.English != -1 ? stu.English : p->data.English;
				printf("�������޸ĺ�����γɼ������޸�������-1����");
				scanf("%d", &(stu.politics));
				p->data.politics = stu.politics != -1 ? stu.politics : p->data.politics;
				printf("�������޸ĺ����ѧ�ɼ������޸�������-1����");
				scanf("%d", &(stu.math));
				p->data.math = stu.math != -1 ? stu.math : p->data.math;
				printf("�������޸ĺ��רҵ�ɼ������޸�������-1����");
				scanf("%d", &(stu.specCourse));
				p->data.specCourse = stu.specCourse != -1 ? stu.specCourse : p->data.specCourse;
				p->data.totalScore = p->data.English + p->data.math + p->data.politics + p->data.specCourse;
			}
			printf("----------------------------------------------------------\n");
			printf("�����루0.�޸Ľ��� 1.�����޸ģ���");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("���벻�Ϸ������������룺");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		printf("�޸ĳɹ���\n");
		printf("----------------------------------------------------------\n");
		break;
	case 5:
		printf("*************************���ҳɼ�*************************\n");
		while(flag)
		{
			printf("������Ҫ���ҵ�ѧ��������");
			fflush(stdin);
			scanf("%s", name);
			p = searchNode(head, name);
			if(p)
			{
				printf("ѧ��\t����\tӢ��\t����\t��ѧ\tרҵ��\t�ܷ�\n");
				printf("\n%s\t%s\t%d\t%d\t%d\t%d\t%d\n", p->data.stuId, p->data.name, p->data.English, p->data.politics, p->data.math, p->data.specCourse, p->data.totalScore);
			}
			printf("----------------------------------------------------------\n");
			printf("�����루0.���ҽ��� 1.�������ң���");
			scanf("%d", &flag);
			while(flag != 1 && flag != 0)
			{
				printf("���벻�Ϸ������������룺");
				scanf("%d", &flag);
			}
			printf("----------------------------------------------------------\n");
		}
		break;
	default:
		printf("----------------------------------------------------------\n");
		printf("����������������룡\n");
		printf("----------------------------------------------------------\n");
		system("pause");
		break;
	}
	writeInfoToFile(head, "student.text");
}

void main()
{
	// �����հ�ѧ����
	ListNode *head = creatList();
	readInfoFromFile(head, "student.text");
	while(1)
	{
		// ��ӡ������
		menu();
		// �û�����
		keyDown(head);
		system("pause");
		system("cls");
	}
	system("pause");
}
