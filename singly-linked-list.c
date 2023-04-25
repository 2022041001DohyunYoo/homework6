/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �꾩슂�� �ㅻ뜑�뚯씪 異붽� */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* �⑥닔 由ъ뒪�� */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode媛� NULL�� �꾨땲硫�, freeNode瑜� �몄텧�섏뿬 �좊떦�� 硫붾え由� 紐⑤몢 �댁젣 */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� 硫붾え由щ� �좊떦�섏뿬 由ы꽩 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� �곌껐�� listNode 硫붾え由� �댁젣
	 * headNode�� �댁젣�섏뼱�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;


	node->link = h->first;
	h->first = node;

	return 0;
}


/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
int insertNode(headNode* h, int key) {

    if(h->first == NULL) {
        insertFirst(h, key);
        return 0;
    }

    listNode* cur = h->first;

    listNode* node = (listNode*)malloc(sizeof(listNode));

    node->key = key;

    while(1){

		if(cur->link == NULL ) {
			if(cur->key >= key){
				insertFirst(h, key);
        			return 0;
			}

			else if(cur->key <= key){
				node->link = cur->link;
				cur->link = node;
				return 0;
			}
        			
    			}

		else{

			if(cur->link->key >= key){
			node->link = cur->link;
			cur->link = node;
			return 0;
			}

			
		}


        cur = cur->link;

}
	return 0;
}


/**
 * list�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertLast(headNode* h, int key) {

    if(h->first == NULL) {
        insertFirst(h, key);
        return 0;
    }

    listNode* cur = h->first;

    listNode* node = (listNode*)malloc(sizeof(listNode));

    node->key = key;

    node-> link = NULL;

     while(1){
       
        if(cur->link == NULL) {
            cur->link = node;
            break;
        }
        
        cur = cur->link;
    }



	return 0;
}


/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(headNode* h) {

    listNode* cur = h->first;

    if(cur == NULL) {
        printf("리스트가 비어 있음");
        return 0;
    }

    h->first = cur->link;

    free(cur);


	return 0;
}


/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(headNode* h, int key) {
    

    listNode* cur = h->first;

    if(cur == NULL){
        printf("리스트가 비어있음");
        return 0;
    }

    while(1){
        if(cur->link == NULL){
            if(cur->key != key){
                printf("일치하는 노드 x");
                break;
            }

            else{
                free(cur);
                h->first = NULL;
                break;

            }
        }
        else if(cur->link->key == key){
            cur->link = cur->link->link;
            free(cur->link);
            break;
        }

        else if(cur->link->link = NULL){
            printf("일치하는 노드 x");
            break;
        }

        cur = cur->link;
        
    }

	return 0;

}

/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(headNode* h) {

    listNode* cur = h->first;

    if(cur == NULL){
        printf("리스트가 비어있음");
        return 0;
    }


    while(1){
        if(cur->link == NULL){
            free(cur);
            h->first = NULL;
            break;
        }
        else if (cur->link->link == NULL){
            free(cur->link);
            cur->link = NULL;
            break;
        }
        cur = cur->link;
    }


	return 0;
}


/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(headNode* h) {

    listNode *p,*q,*r;
 
    p = h->first;
    q = NULL;
 
    while (p != NULL)
    {
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }

	h->first = q;
    

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
