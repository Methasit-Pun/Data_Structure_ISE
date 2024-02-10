#include<stdio.h>
#include<stdlib.h>

struct btree_node
{
	//data to store
	int data;

	//downward pointers
	struct btree_node *right;
	struct btree_node *left;
};


//creates new binary tree from two previous binary trees, with new root node storing new data
struct btree_node *create_btree(int data, struct btree_node *left, struct btree_node *right)
{
	struct btree_node *new_node = (struct btree_node *)malloc(sizeof(struct btree_node));

	new_node->data = data;
	new_node->right = right;
	new_node->left = left;

	return new_node;
}

//prints a binary tree, starting from a root
//uses tabs to separate level
void print_btree(struct btree_node *root, int tabs)
{
	int current_tabs = 0;

	if(root == NULL)
		return;

	while(current_tabs < tabs)
	{
		printf("\t");
		current_tabs++;
	}
	printf("%d\n",root->data);

	current_tabs = 0;
	while(current_tabs <= tabs)
	{
		printf("\t");
		current_tabs++;
	}
	printf("Right:\n");
	print_btree(root->right, tabs+1);

	current_tabs = 0;
	while(current_tabs <= tabs)
	{
		printf("\t");
		current_tabs++;
	}
	printf("Left:\n");
	print_btree(root->left, tabs+1);
}


//returns the sum of all nodes in a binary tree
int sum_btree(struct btree_node *root)
{
	if(root == NULL)
		return 0;

	return root->data + sum_btree(root->left) + sum_btree(root->right);
}

/****************************************************
 *
 * 	Depth first search: easy recursive function
 *
 * **************************************************/
struct btree_node *dfs(struct btree_node *root, int data)
{
	if(root == NULL)
		return NULL;

	if(root->data == data)
		return root;

	struct btree_node *found = dfs(root->left, data);

	if(found != NULL)
		return found;

	return dfs(root->right, data);
}

/****************************************************
 *
 * 	Breadth first search: requires linked list to use as queue
 *
 * **************************************************/
//linked list points to binary tree nodes
//treated as a FIFO (first in, first out) queueu
struct ll_node
{
	struct btree_node *btree_entry;
	struct ll_node *next;
};

struct ll_node *head = NULL;

//creates a new node, adds to head of queue
void add_to_queue(struct btree_node *btree_entry)
{
	struct ll_node *new_queue_entry = (struct ll_node *)malloc(sizeof(struct ll_node));

	new_queue_entry->btree_entry = btree_entry;
	new_queue_entry->next = head;

	head = new_queue_entry;
}

void delete_whole_queue()
{
	struct ll_node *to_free;

	if(head == NULL)
	{
		return;
	}
	while(head != NULL)
	{
		to_free = head;
		head = head->next;
		free(to_free);
	}
}

//returns element from tail of queue; also removes it from queue (without freeing it)
struct btree_node *get_from_queue()
{
	struct ll_node *p = head;
	struct btree_node *found = NULL;

	if(head == NULL)
	{
		return NULL;
	}

	//special case: if we just have one element (head == tail)
	if(head->next == NULL)
	{
		found = head->btree_entry;
		free(head);
		head = NULL;
		return found;
	}


	while((p->next)->next != NULL)
	{
		p = p->next;
	}
	//at this point, p points to second to last element
	found = (p->next)->btree_entry;
	free(p->next);
	p->next = NULL;
	return found;
}

struct btree_node *bfs(struct btree_node *root, int data)
{
	//add root to queue
	add_to_queue(root);

	struct btree_node *current = root;

	//until queue is empty
	while(head != NULL)
	{
		//add left and right children to queue
		if(current->left != NULL)
			add_to_queue(current->left);
		if(current->right != NULL)
			add_to_queue(current->right);

		//check if queue tail matches
		current = get_from_queue();

		if(current->data == data)
		{
			delete_whole_queue();
			return current;
		}
	}

	//not found
	delete_whole_queue();
	return NULL;
}



int main()
{
	//create test binary tree from the ground up
	struct btree_node *root;
	struct btree_node *tmp1;
	struct btree_node *tmp2;

	tmp1 = create_btree(10, NULL, NULL);
	tmp2 = create_btree(11, NULL, NULL);

	tmp1 = create_btree(9, tmp1, NULL);

	tmp2 = create_btree(8, NULL, tmp2);

	root =  create_btree(6, tmp1, tmp2);

	tmp1 = create_btree(4, NULL, NULL);
	tmp2 = create_btree(3, NULL, NULL);

	tmp1 = create_btree(2, NULL, tmp1);
	tmp2 = create_btree(3, root, tmp2);

	root =  create_btree(1, tmp1, tmp2);

	print_btree(root, 0);

	printf("Current sum is %d\n",sum_btree(root));
	root =  create_btree(2, NULL, root);
	printf("Now should be previous sum + 2 = %d\n",sum_btree(root));


	tmp1 = dfs(root, 11);
	printf("Found node with data 11 (%d) through DFS\n",tmp1->data);

	tmp1 = bfs(root, 11);
	printf("Found node with data 11 (%d) through BFS\n",tmp1->data);

	return 0;
}
