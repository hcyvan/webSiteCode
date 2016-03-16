/* 反转单链表的实现及测试 */

#include <stdio.h>
#include <stdlib.h>
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - ((size_t) &((type *)0)->member) );})

typedef struct node {
	struct node *next;
} Node;
/** 将与节点关联的数据域放在节点的外部。有利于对于数据结构的统一管理。
    参考linux内核源代码。
**/
typedef struct data {
	Node node;
	int num;
} Data;

Node *add_from_head(Node *Head, Node *node)
{
	if (node != NULL) {
		node->next = Head;
		Head = node;
	}
	return Head;
}
// num 表示生成一个节点数为 num 的单链表
Node *generate_singly_linkedlist(int num)
{
	int i;
	Data *tmp;
	Node *head = NULL;
		
	for (i = 0; i < num; i++) {
		tmp = (Data *)malloc(sizeof(Data));
		tmp->num = num - i;
		tmp->node.next = NULL;
		head = add_from_head(head, &tmp->node);
	}

	return head;
}
// 利用节点关联的数据，检测单链表的顺序
void show_singly_linkedlist(Node *head)
{
	Node *p = head;

	while(p != NULL) {
		printf("%d ",container_of(p, Data, node)->num);
		p = p->next;
	}
	printf("\n");
}

// 以下是反转单链表的三个实现
Node *reverse(Node *Head)
{
	Node *p1, *p2, *p3;

	if (Head == NULL || Head->next == NULL)
		return Head;

	p1 = Head;
	p2 = p1->next;

	p1->next = NULL;
	while (p2 != NULL) {
		p3 = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}

	return p1;
}

Node *reverse_recur(Node *Head)
{
	Node *new_head;
	if (Head == NULL || Head->next == NULL)
		return Head;

	new_head = reverse_recur(Head->next);

	Head->next->next = Head;
	Head->next = NULL;

	return new_head;
}

Node *reverse_array(Node *Head)
{
	Node **array;
	Node *p, *new_head;
	int num = 0;
	int i = 0;

	if (Head == NULL)
		return Head;
	
	for (p = Head; p != NULL; p = p->next)
		num++;

	array = (Node **)malloc(sizeof(Node *)*num);
	if (array == NULL) {
		printf("Out of memory!\n");
		exit(0);
	}

	for (p = Head; p != NULL; p = p->next) {
		array[i] = p;
		i++;
	}
	for (i=num-1; i > 0; i--)
		array[i]->next = array[i-1];

	array[0]->next = NULL;
	new_head = array[num-1];
	free(array);

	return new_head;
}

int main()
{
	// 生成一个单链表，可以利用节点关联的数据检测
	// 单链表节点数据为：1 2 3 4 5 6 7 8 9 10
	Node *head = generate_singly_linkedlist(10);
	show_singly_linkedlist(head);
	// 反转一次
	printf("reverse the linkedlist: \n");
	head = reverse(head);
	show_singly_linkedlist(head);
	// 再次反转
	printf("Use reverse_recur() to reverse the linkedlist: \n");
	head = reverse_recur(head);
	show_singly_linkedlist(head);
	// 再次反转
	printf("Use reverse_array() to reverse the linkedlist: \n");
	head = reverse_array(head);
	show_singly_linkedlist(head);
	return 0;
}
