#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkedList;
typedef enum Status{
    error,
    success
} Status;

//函数的声明
Status InitList(LinkedList *L);
void DestroyList(LinkedList *L);
Status InsertList(LNode *p, ElemType data);
Status DeleteList(LNode *p, ElemType e);
void TraverseList(LinkedList L);
Status SearchList(LinkedList L, ElemType e);
Status ReverseList(LinkedList *L);
Status IsLoopList(LinkedList L);
LNode* FindMidNode(LinkedList L);
void show(void);
int judge_int(void);

Status InitList(LinkedList *L) {
    LinkedList list;

    list = (LinkedList)malloc(sizeof(LNode));
    if(list == NULL)
    {
    	printf("内存分配失败\n");
        return error;
    }
    list->next = NULL;
    *L = list;

    return success;
}

void DestroyList(LinkedList *L) {
    LinkedList temp;

    while(*L != NULL)
    {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

Status InsertList(LNode *p, ElemType data) {
    LinkedList current = p;
    LinkedList newNode = (LinkedList)malloc(sizeof(LNode));

    if(newNode == NULL)
    {
        printf("内存分配失败\n");
        return error;
    }
    newNode->data = data;
    newNode->next = NULL;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    return success;
}

Status DeleteList(LNode *p, ElemType e) {
    LinkedList posNode = p->next;
    LinkedList posNodeFront = p;
    if(posNode == NULL)
    {
        printf("链表为空，无法删除\n");
    }
    else
    {
        while(posNode->data != e)
        {
            posNodeFront = posNode;
            posNode = posNode->next;
            if(posNode == NULL)
            {
                printf("没有该数据\n");
                return error;
            }
        }
        posNodeFront->next = posNode->next;
        free(posNode);
        return success;
    }
}

void TraverseList(LinkedList L) {
    LinkedList temp;

    temp = L->next;
    while(temp != NULL)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Status SearchList(LinkedList L, ElemType e) {
    while(L != NULL)
    {
        if(L->data == e)
        {
            return success;
        }
        L = L->next;
    }
    return error;
}

/*
void ReverseList(LinkedList L) {
    LinkedList current, next, pre;
    current = L->next;
    pre = NULL;
    while(current != NULL)
    {
        next = current->next;
        current->next = pre;
        pre = current;
        current = next;
    }
    L->next = pre;
}
*/

Status ReverseList(LinkedList *L) {
    LNode *newHead;		//储存每次反转后的第一个节点 
    LNode *p1;			//每次都指向前一个节点	
    LNode *p2;			// 储存未反转前的下一个节点 
    p1=(*L)->next;
    p2=p1->next;
    p1->next=NULL;
    newHead=p1;
    while (p2!= NULL) {
        p1=p2;
        p2=p1->next;
        p1->next=newHead;
        newHead=p1;
    }
    (*L)->next=newHead;
}

LNode* FindMidNode(LinkedList L) {
    LinkedList slow = L, fast = L;
    while(fast != NULL && slow != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Status IsLoopList(LinkedList L) {
    LinkedList fast = L, slow = L;
    while(fast->next != NULL && slow->next != NULL)
    {
        slow = slow->next;
        if((fast = fast->next->next) == NULL)
        return error;
        if(fast == slow)
        return success;
    }
    return error;
}

void show(void)
{
    printf("\n\n\n\n单链表ADT\n\n");
    printf("1.创建空链表\n");
    printf("2.销毁链表\n");
    printf("3.插入结点\n");
    printf("4.删除结点\n");
    printf("5.遍历链表\n");
    printf("6.查找数据\n");
    printf("7.反转链表\n");
    printf("8.判断链表是否成环\n");
    printf("9.反转链表中的偶数结点/无此功能\n");
    printf("10.查找中间结点\n");
    printf("11.退出\n");
    printf("\n请输入对应的数字(1-11)：");
}

int judge_int(void)  //防止用户乱输入其他的字符
{
    int len, num = 0, arg = 1;
    char word[10];  
    int m, j= 1, k;
    while(j)
    {
        scanf("%s", word);
        len = strlen(word);
        for(m = 0;m<len;m++)
        {
            if(word[m]<'0' || word[m]>'9')  //检验是否有乱输入其他字符
            {
                printf("请输入整数：");
                break;
            }
            else 
            {
                if(m == len-1)
                    j = 0;
            }
        }
    }
    j = len-1;
    for(m=0;m<len;m++)  // 将字符重新转换为数字
    {
        for(k=0;k<j;k++)
            arg *= 10;
        num += (word[m]-'0')*arg;
        arg = 1;
        j--;
    }
    return num;
} 

int main(void)
{
    int choice, num = 0;
    LinkedList head = NULL;

    do
    {
        show();
        choice = judge_int();
        system("cls");
        switch(choice)
        {
            case 1://创建空链表
            {
                if(InitList(&head))
                {
                    printf("空链表创建成功\n");
                }
                else
                {
                    printf("空链表创建失败\n");
                }
                break;
            }
            case 2://销毁链表
            {
                DestroyList(&head);
                printf("链表销毁完成\n");
                break;
            }
            case 3://插入数据
            {
                if(head == NULL)
                {
                    printf("链表为空， 请先创建链表\n");
                }
                else
                {
                    printf("请输入数据：");
                    scanf("%d", &num);
                    if(InsertList(head, num))
                    {
                        printf("数据插入成功\n");
                    }
                    else
                    {
                        printf("数据插入失败\n");
                    }
                }
                break;
            }
            case 4://删除数据
            {
                printf("你想删除哪个数据：");
                scanf("%d", &num);
                if(DeleteList(head, num))
                {
                    printf("数据删除成功\n");
                }
                else
                {
                	printf("数据删除失败\n");
                }
                break;
            }
            case 5://遍历链表
            {
                if(head == NULL || head->next == NULL)
                {
                    printf("链表不存在或者只存在一个空的头结点\n");
                }
                else
                {
                    TraverseList(head);
                }
                break;
            }
            case 6://查找数据
            {
                printf("请输入你要查找的数据：");
                scanf("%d", &num);
                if(SearchList(head, num))
                {
                    printf("该数存在\n");
                }
                else
                {
                    printf("该数不存在\n");
                }
                break;
            }
            case 7://反转链表
            {
                if(head == NULL || head->next == NULL)
                {
                    printf("链表为空或者链表只含有两个结点\n");
                    printf("链表反转失败\n");
                }
                else
                {
                    if(ReverseList(&head))
                    {
                        printf("链表反转成功\n");
                    }
                    else
                    {
                        printf("链表反转失败\n");
                    }
                    
                }
                break;
            }
            case 8://判断链表是否成环
            {
                if(head == NULL || head->next == NULL)
                {
                    printf("链表为空\n");
                }
                else
                {
                    if(IsLoopList(head))
                    {
                        printf("链表成环\n");
                    }
                    else
                    {
                        printf("链表没有成环\n");
                    }
                }
                break;
            }
            case 9://反转链表中的偶数结点
            {
                break;
            }
            case 10://查找中间结点
            {
                if(head == NULL || head->next == NULL)
                {
                    printf("这是空链表\n");
                }
                else
                {
                    printf("链表中间储存的值为%d\n", (FindMidNode(head))->data);
                }
                break;
            }
            case 11://销毁链表
            {
                DestroyList(&head);
                break;
            }
            default:
            {
                printf("请重新输入数字！(1-11)\n");
                break;
            }
        }
    } while (choice != 11);
    
    return 0;
}
