#define MAX 4
#define MIN 2
#include<iostream>
#include<stdlib.h>
using namespace std;


struct node
{
	int ele[MAX];
	struct node * child[4];
	struct node * parent;
	struct node * next_child;
};
typedef struct node * NODE;

class btree
{
	NODE root;
	public:
		btree()
		{
			root=create_newnode();
		}
		void insert(int);
		int search(int);
		void display();
		int isFull(NODE);
		NODE create_newnode();
		NODE find_leaf(NODE,int);
		void split(NODE,int);
		void sort_node(NODE);
		void update_parent(NODE, int, int);
};

int main()
{
	btree  b;
	int ch, key, flag;

	system("clear");
	while(1)
	{
		cout<<"\n\nMain Menu\n-------------\n1. to insert an element\n2. to Search for an element\n3. to Display the Tree\n4. to Exit\nEnter Choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:	cout<<"Enter the integer to be inserted: ";
				cin>>key;
				b.insert(key);
				break;
			case 2:	cout<<"Enter the integer to be found: ";
				cin>>key;
				flag=b.search(key);
				if(flag)
					cout<<"Element is present\n";
				else
					cout<<"Element not found\n";
				break;
			case 3: b.display();
				break;
			default:exit(0);
		}
	}
}


void btree::insert(int key)
{
	int i,j, t, max;
	NODE temp = find_leaf(root,key);
	if(!temp)
	{
		cout<<"Error!: Cannot insert: This integer is already present in the tree\n";
		return;
	}
	if(!isFull(temp))
	{
		cout<<"Element inserted successfully\n";
		for(i=0;i<MAX;i++)
		{
			if(temp->ele[i]==-1)
			{
				temp->ele[i]=key;
				break;
			}
			max=temp->ele[i];
		}
		sort_node(temp);
		if(key>max && temp->parent!=NULL)
			update_parent(temp->parent,key,max);
		return;
	}
	if(isFull(temp))
	{
		split(temp,key);

	}
}

int btree::isFull(NODE x)
{
	return (x->ele[MAX-1]==-1)?0:1;
}

NODE btree::create_newnode()
{
	int i;
	NODE temp = new (struct node);
	if(!temp)
	{
		cout<<"Fatal ERROR: Out of Memory!\n";
		exit(0);
	}
	for(i=0;i<MAX;i++)
	{
		temp->ele[i]=-1;
		temp->child[i]=NULL;
	}
	temp->parent=NULL;
	temp->next_child=NULL;
	return temp;
}

NODE btree::find_leaf(NODE x, int key)
{
	int i;
	if(x->child[0]==NULL)
	{
		for(i=0;i<MAX;i++)
			if(key==x->ele[i])

				return NULL;
		return x;
	}
	if(key<x->ele[0])
	return(find_leaf(x->child[0],key));
	else
	return(find_leaf(x->child[1],key));
}

void btree::sort_node(NODE x)
{
	int i,j;
	int temp_ele;
	NODE temp_child;
	for(i=0;i<MAX && x->ele[i]!=-1;i++)
	{
		for(j=i+1;j<MAX && x->ele[j]!=-1;j++)
		{
			if(x->ele[i]>x->ele[j])
			{
				temp_ele = x->ele[i];
				temp_child = x->child[i];

				x->ele[i] = x->ele[j];
				x->child[i] = x->child[j];

				x->ele[j] = temp_ele;
				x->child[j]= temp_child;
			}
		}
	}
}

void btree::split(NODE x,int key)
{
	int i;
	NODE temp,temp1,temp2;
       if(x->parent==NULL)
	{
		temp = create_newnode();
		root = create_newnode();

		root->ele[0] = x->ele[MIN];
		root->child[0] = x;

		root->child[1] = temp;

		x->parent = root;
		temp->parent = x->parent;
		temp->ele[0]=x->ele[MIN];
	temp->ele[1]=x->ele[MIN+1];

	x->ele[MIN]=-1;
	x->ele[MIN+1]=-1;
	if(key<root->ele[0])
	x->ele[2]=key;
	else
	temp->ele[2]=key;

	sort_node(x->parent);
	return;
	}
	else
	{

		temp1= create_newnode();
		temp2=create_newnode();
		temp1->parent=x;
		temp2->parent=x;



	temp1->next_child=temp2;
	temp2->next_child=NULL;

	x->child[0]=temp1;
	x->child[1]=temp2;
	x->child[2]=NULL;
	x->child[3]=NULL;
	temp1->ele[0]=x->ele[0];
	x->ele[0]=x->ele[MIN];

	temp1->ele[1]=x->ele[1];
	 x->ele[1]=-1;
	temp2->ele[0]=x->ele[MIN];

	temp2->ele[1]=x->ele[MIN+1];

	if(key<x->ele[0])
	temp1->ele[MIN]=key;
	else
	temp2->ele[MIN]=key;
	x->ele[2]=-1;
	x->ele[3]=-1;

	sort_node(temp1);
	sort_node(temp2);

   }
}

void btree::update_parent(NODE x, int key, int max)
{
	int i, new_max;
	for(i=0;i<MAX&&(x->ele[i]!=-1);i++)
	{
		new_max=x->ele[i];
		if(x->ele[i]==max)
			x->ele[i]=key;
	}
	if(key>new_max && x->parent!=NULL)
		update_parent(x->parent,key,max);
}

int btree::search(int key)
{
	NODE temp = find_leaf(root, key);
	if(temp==NULL)
		return 1;
	return 0;
}
void btree::display()
{
	NODE queue[50];
	int f=0, r=-1, lvl = -1, i;
	queue[++r]=NULL;
	queue[++r]=root;
	while(f<r)
	{
		if(queue[f]==NULL)
		{
			cout<<"\n\nLevel --> "<<++lvl<<endl;
			if(queue[r]!=NULL)
				queue[++r]=NULL;
			f++;
		}
		else
		{
			for(i=0;i<MAX;i++)
			{
				if(queue[f]->ele[i]!=-1)
					cout<<queue[f]->ele[i]<<" ";
				if(queue[f]->child[i]!=NULL)
					queue[++r]=queue[f]->child[i];
			}
			cout<<"       ";
			f++;
		}
	}
}