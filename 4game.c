#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


#define SHOOT 1
#define JUMP 2

struct btree_node
{
	//data
	int points;
	int highest;

	//pointers
	struct btree_node *right; //jump
	struct btree_node *left; //shoot
};
// func right left




//returns the reward for specific action at this point in time
//returns 0, 1, or -infinity points

int reward(int action, int steps)
{
	//static unsigned int steps = 0;
	unsigned int p = 0x18352037;
	unsigned int d = 0x11111111;

	int reward;

	//death if you shoot at wrong time
	if(((d >> steps)&1) && (action == SHOOT))
	{
		reward = INT_MIN;
	}
	else
	{
		if(action == SHOOT)
		{
			if((p >> steps)&1)
				reward = 1;
			else
				reward = 0;
		}
		else
		{
			reward = 0;
		}
	}
	//steps++;
	return reward;
}

struct btree_node *root = NULL;

//Builds a decision binary tree for up to x steps: max 64
void train(unsigned int steps, struct btree_node *current)
{





}

int calculate_score(struct btree_node *current)
{

}


void print_best_strategy(struct btree_node *current)
{
	if(current == NULL)
		return;
	//in case they're both null
	if((current->left == NULL) && (current->right == NULL))
	{
		return;
	}
	//if left is NULL
	if((current->left == NULL))
	{
		printf("J ");
		print_best_strategy(current->right);
		return;
	}
	//if right is NULL
	if((current->right == NULL))
	{
		printf("S ");
		print_best_strategy(current->left);
		return;
	}

	if((current->left)->highest > (current->right)->highest)
	{
		printf("S ");
		print_best_strategy(current->left);
	}
	else
	{
		printf("J ");
		print_best_strategy(current->right);
	}
}








int main()
{
	//creates root, representing beginning position of game
	root = (struct btree_node *)malloc(sizeof(struct btree_node));

	root->highest = 0;
	root->points = 0;

	root->left = NULL;
	root->right = NULL;

	train(5,root);

	printf("Trained\n");

	//What's the highest score we achieved?
	calculate_score(root);

	printf("High score: %d\n",root->highest);

	printf("Best strategy:\n");
	print_best_strategy(root);
	printf("\n");

	return 0;
}
