/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


//글자가 깨진 각주들은 전부 삭제 후 임의로 작성 하였음

#include<stdio.h>
#include<stdlib.h>

//연결 리스트 노드 타입 관련 정의

typedef struct Node {
	int key;
	struct Node* link;
} listNode;


typedef struct Head {
	struct Node* first;
} headNode;


// 관련 함수들 정의
headNode* initialize(headNode* h); //리스트를 초기화
int freeList(headNode* h); //리스트 전체를 할당해제

int insertFirst(headNode* h, int key);//리스트의 맨 처음에 노드 삽입
int insertNode(headNode* h, int key);//리스트의 알맞은 위치에 노드 삽입(오름차순)
int insertLast(headNode* h, int key);//리스트의 마지막 위치에 노드 삽입

int deleteFirst(headNode* h);//리스트의 맨 처음 노드 삭제
int deleteNode(headNode* h, int key);//특정한 key값을 가진 노드를 리스트에서 찾아 삭제
int deleteLast(headNode* h);//리스트의 마지막 위치에 있는 노드 삭제
int invertList(headNode* h);//리스트의 순서를 반전

void printList(headNode* h);//리스트의 요소들을 보여줌

int main()
{
	char command; //명령 변수
	int key; //노드에 집어 넣을 값
	headNode* headnode=NULL; //리스트의 헤드 노드를 가리킬 포인터


	printf("[-----[유도현][2022041001]-----]\n");

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
		//양식

		printf("Command = ");
		scanf(" %c", &command);//명령을 입력받음

		switch(command) {//입력받은 명령을 판단해서 양식에 따라 실행
		case 'z': case 'Z':
			headnode = initialize(headnode); 
			//리스트의 헤드노드(실질적인 리스트를 가리키는 빈 노드)를 만들어서 포인터 headnode가 가리키게 만듬
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트의 요소 보여줌
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //노드에 집어넣을 값 입력 받음
			insertNode(headnode, key);//입력 받은 값을 집어넣은 노드를 적절한 위치에 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); //검색할 값 입력
			deleteNode(headnode, key); //검색한 값을 가지고 있는 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);//노드에 집어넣을 값 입력 받음
			insertLast(headnode, key);//입력 받은 값을 집어넣은 노드를 리스트의 마지막 위치에 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);//노드에 집어넣을 값 입력 받음
			insertFirst(headnode, key);//입력 받은 값을 집어넣은 노드를 리스트의 처음 위치에 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);//리스트의 처음 위치에 있는 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);//리스트의 마지막 위치에 있는 노드 삭제
			break;
		case 'q': case 'Q':
			freeList(headnode); //리스트의 모든 요소와 헤드 노드까지 전부 할당 해제 하고
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; //부적절한 입력 방지
		}

	}while(command != 'q' && command != 'Q'); //반복 종료

	return 1;
}


//리스트를 초기화

headNode* initialize(headNode* h) {

	
	if(h != NULL)
		freeList(h); //만약 이미 리스트가 있다면 전부 할당 해제

	
	headNode* temp = (headNode*)malloc(sizeof(headNode)); //헤드노드 할당
	temp->first = NULL; //헤드노드의 링크는 NULL로
	return temp;//할당한 헤드노드의 주소 반환
}



int freeList(headNode* h){
	
	
	listNode* p = h->first; //노드를 가리키는 임시 포인터에 헤드노드에 연결된 값 집어넣기

	listNode* prev = NULL; //목표 노드의 이전 노드를 가리킬 포인터

	while(p != NULL) {// 임시 포인터가 NULL 을 가리키지 않을때 까지 반복
	//=링크의 마지막까지 차례대로 할당해제 한다는 뜻
		prev = p;//임시포인터가 가리키는 주소를 prev에 넘기고
		p = p->link;//임시포인터는 다음 노드를 가리킴
		free(prev);//prev가 가리키는 노드 할당해제
	}
	free(h); //헤드노드 할당 해제
	return 0;
}




int insertFirst(headNode* h, int key) {//리스트의 처음 위치에 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 할당
	node->key = key;//노드에 값 집어넣기


	node->link = h->first; //기존에 헤드노드가 가리키던 곳을 노드가 가리키게 하기
	h->first = node; //헤드노드가 노드를 가리키게 하기

	return 0;
}



int insertNode(headNode* h, int key) {

    if(h->first == NULL) { //만약 리스트가 비어있으면
        insertFirst(h, key);//리스트의 처음 위치에 노드를 삽입
        return 0; //함수 강제 종료
    }

    listNode* cur = h->first; //커서(현재노드)가 헤드노드를 가리키게 함

    listNode* node = (listNode*)malloc(sizeof(listNode)); //노드 할당

    node->key = key; //노드에 값 집어넣기

    while(1){ //무한 반복

		if(cur->link == NULL ) {//만약 현재 노드뒤에 아무것도 없으면
			if(cur->key >= key){//만약 현재 노드의 값이 입력받은 값보다 크면
				insertFirst(h, key); //리스트의 처음 위치에 노드 삽입
        			return 0; //함수 강제 종료
			}

			else if(cur->key <= key){//현재 노드의 값이 입력받은 값보다 작으면
				node->link = cur->link; //새로운 노드 뒤에 현재노드 뒤에 있는 노드를 연결 
				cur->link = node; //현재노드 뒤에 새로운 노드 연결
				return 0; // 함수 강제 종료
			}
        			
    			}

		else{

			if(cur->link->key >= key){ //만약 현재 노드의 값이 입력받은 값보다 크면
			node->link = cur->link;//새로운 노드 뒤에 현재노드 뒤에 있는 노드를 연결 
			cur->link = node;//현재노드 뒤에 새로운 노드 연결
			return 0;// 함수 강제 종료
			}

			
		}


        cur = cur->link; //현재노드(커서)를 다음 노드로 넘김

}
	return 0;
}



 
int insertLast(headNode* h, int key) {//리스트의 마지막 위치에 노드 삽입

    if(h->first == NULL) { //만약 리스트가 비어있으면
        insertFirst(h, key); //리스트의 처음 위치에 노드 삽입
        return 0;//함수 강제종료
    }

    listNode* cur = h->first;//커서(현재노드)가 헤드노드를 가리키게 함

    listNode* node = (listNode*)malloc(sizeof(listNode));//새로운 노드 할당

    node->key = key;//새로운 노드에 값 집어넣기

    node-> link = NULL;//새로운 노드뒤에 NULL 연결 (=연결된게 아무것도 없게 하기)

     while(1){//무한반복
       
        if(cur->link == NULL) {//만약 현재노드가 마지막 노드라면
            cur->link = node; //새로운노드를 현재노드 뒤에 붙이기
            break;//반복 종료
        }
        
        cur = cur->link; //현재노드 (커서)가 다음 노드를 가리키게 함
    }



	return 0;
}


int deleteFirst(headNode* h) { //리스트의 처음 위치의 노드 삭제

    listNode* cur = h->first;//커서(현재노드)가 헤드노드를 가리키게 함

    if(cur == NULL) {//리스트 비어있으면
        printf("리스트가 비어 있음\n");
        return 0;//강제종료
    }

    h->first = cur->link; //헤드노드와 현재노드 다음노드를 연결

    free(cur); //현재노드 할당해제


	return 0;
}



int deleteNode(headNode* h, int key) {
    

if (h->first == NULL) //리스트가 비어있으면면
	{
		printf("리스트가 비어 있음\n");//출력
		return 0;//함수 강제종료
	}

	listNode* cur = h->first;//현재 노드 가리키는 포인터
	listNode* prev = NULL;//이전 노드 가리키는 포인터

	
	while(cur != NULL) {//현재 노드(커서)가 NULL을 가리킬때까지
		if(cur->key == key) { //현재 노드의 값이 입력받은 값과 일치한다면
			
			if(cur == h->first) {//만약 이게 처음에 위치한 노드면
				h->first = cur->link;// 현재노드 뒤 노드를 헤드노드와 연결
			} else { //아니면
				prev->link = cur->link; //뒷 노드와 앞노드를 연결
			}
			free(cur); //현재 노드 할당해제
			return 0;//함수 강제종료
		}

		prev = cur; 
		cur = cur->link;

		//현재와 이전 노드(커서)를 한칸씩 뒤로
	}

	//만약 일치하는 값이 없다면
	printf("cannot find the node for key = %d\n", key);
	return 0;


}


int deleteLast(headNode* h) {//마지막 노드 삭제

    	if (h->first == NULL)//리스트 비어있으면
	{
		printf("리스트가 비어 있음\n");
		return 0;//강제종료
	}

	listNode* cur = h->first; //현재 노드 가리키는 포인터
	listNode* prev = NULL; //이전 노드 가리키는 포인터

	
	if(cur->link == NULL) { //만약 현재노드가 마지막이면
		h->first = NULL;//헤드포인터 뒤에 NULL 연결
		free(cur); //현재 노드 할당해제
		return 0;//함수 강제종료
	}

	while(cur->link != NULL) { //마지막 노드일때 까지 반복
		prev = cur;
		cur = cur->link;
		//cur와 prev를 각각 리스트의 한칸씩 뒤를 가리키게 함
	}

	prev->link = NULL; //이전 노드는 NULL 가리키게
	free(cur);//현재노드는 할당해제

	return 0;
}



int invertList(headNode* h) {//리스트 순서 거꾸로

    listNode *tail, *body,*head ; //임시 포인터 3개
 
    head = h->first;//head가 리스트의 첫 노드 가리키게
    body = NULL;//body는 NULL 가리키게
	tail = NULL;//tail이 NULL 가리키게

	//3량 짜리 열차가 리스트 한칸씩 뒤로 움직이는 이미지
 
    while (head != NULL) // head가 NULL을 가리킬때 까지 반복
    {
        tail = body;
        body = head;
        head = head->link;
		//여기까지 하면 head ~ tail까지 전부 한칸씩 뒤로 가는 것
        body->link = tail;//body과 tail를 기존에 연결되어 있던것과 반대로 연결
	
    }
	//노드의 주소를 하나하나 역방향으로 연결하다가 body이 NULL을 가리킨다
	// = 리스트의 모든 요소를 역방향으로 연결하면 종료


	h->first = body;//모든 노드를 역방향으로 연결했으니 기존의 마지막 노드를 헤드노드에 연결
    

	return 0;
}


void printList(headNode* h) { //리스트 요소 출력
	int i = 0; //현재 노드의 위치 저장용
	listNode* p; //커서 (현재 노드)

	printf("\n---PRINT\n");

	if(h == NULL) { //리스트가 비어있으면
		printf("Nothing to print....\n");//출력
		return;//함수 강제종료
	}

	p = h->first;//커서가 첫번째 노드 가리키게 함

	while(p != NULL) {//마지막 노드까지 반복
		printf("[ [%d]=%d ] ", i, p->key);//현재 위치와 노드의 값 출력
		p = p->link;//현재위치 (커서)를 다음 노드로 넘김
		i++;//현재 위치 하나 증가
	}

	printf("  items = %d\n", i);//총 노드 개수 출력
}
