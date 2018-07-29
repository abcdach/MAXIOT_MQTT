

	typedef struct node
	{
	    int data;
	    int D0;
	    int D1;
	    int D2;
	    int D3;
	    struct node* next;
	} node;

	typedef void (*callback)(node* data);
//#--------------------------------------------
//#
//#--------------------------------------------
	node* create(int data,int D0,int D1,int D2,int D3,node* next);
	node* prepend(node* head,int data,int D0,int D1,int D2,int D3);
	node* append(node* head, int data,int D0,int D1,int D2,int D3);
	node* insert_after(node *head, int data,int D0,int D1,int D2,int D3, node* prev);
	node* insert_before(node *head, int data,int D0,int D1,int D2,int D3, node* nxt);
	node* remove_front(node* head);
	node* remove_back(node* head);
	node* remove_any(node* head,node* nd);
	node* search(node* head,int data);
	void dispose(node *head);
	int count(node *head);
	node* insertion_sort(node* head);
	node* reverse(node* head);
//#--------------------------------------------
	void traverse(node* head,callback f);
	void display(node* n);
//#--------------------------------------------



//#--------------------------------------------




