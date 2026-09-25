#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define item_cmp(a,b) ((a) - (b))

/********************B+树的代码实现****************************/
typedef int KEY;
typedef int VALUE;
typedef struct  bplus_node_s* bplus_node_pt;
//B+树节点的定义
typedef struct bplus_node_s {
	KEY* keys;//主键 最大max个 最小min个 
	VALUE* data;//真实数据  最大max个 最小min个 对于内部结点 data是NULL
	bplus_node_pt* child;//子节点 最大max+1个 最小min+1个
	bplus_node_pt next;//指向兄弟结点 仅仅是叶子结点的时候才有值 
	int keynum;//当前元素个数
	bplus_node_pt parent;
}bplus_node_t;

typedef struct bplus_tree_s* bplus_tree_pt;

//B+树的定义
typedef struct bplus_tree_s {
	bplus_node_pt root;
	int max;
	int min;
}bplus_tree_t;
/******************************函数声明**************************************/
int bplus_tree_create(bplus_tree_pt* _tree, int m);//B+树的创建
int bplus_tree_insert(bplus_tree_pt tree, KEY key, VALUE value);
int binary_search(KEY* keys, KEY key, int left, int right, int* index);
bplus_node_pt bplus_node_new_leaf(int m);
int _bplus_tree_insert(bplus_tree_pt tree, bplus_node_pt node, KEY key, VALUE value);
bplus_node_pt bplus_node_new_internal(int m);
void bplus_tree_printf(bplus_tree_pt tree);
void bplus_node_show(bplus_node_pt node, int h);
void bplus_node_printfnode(KEY* key, int h);

void bplus_tree_delete(bplus_tree_pt tree, KEY key);


/******************************函数实现**************************************/

int bplus_tree_create(bplus_tree_pt* _tree, int m)
{
	bplus_tree_pt tree = (bplus_tree_pt)malloc(sizeof(bplus_tree_t));
	if (tree == NULL)
	{
		return 0;
	}
	tree->root = NULL;
	tree->max = m;
	tree->min = m / 2;
	*_tree = tree;
	return 1;
}

/*
二分查找 找到数组中指定的key的位置 如果存在返回1 否则返回0
如果找到索引为该值的位置 否则返回右邻的值的位置(child的位置)
*/
int binary_search(KEY* keys, KEY key, int left, int right, int* index)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (item_cmp(keys[mid],key) > 0)
		{
			right = mid - 1;
		}
		else if (item_cmp(keys[mid], key) < 0)
		{
			left = mid + 1;
		}
		else
		{
			*index = mid;
			return 1;
		}
	}
	*index = left;
	return 0;
}

/*
创建新的叶子结点
*/
bplus_node_pt bplus_node_new_leaf(int m)
{
	bplus_node_pt node = (bplus_node_pt)malloc(sizeof(bplus_node_t));
	if (node == NULL)
	{
		return NULL;
	}
	node->parent = NULL;
	node->next = NULL;
	node->keynum = 0;
	node->keys = (KEY*)malloc(sizeof(KEY) * (m + 1));
	node->data = (VALUE*)malloc(sizeof(VALUE) * (m + 1));
	if (node->keys == NULL || node->data == NULL)
	{
		free(node->keys);
		free(node->data);
		free(node);
		return NULL;
	}
	node->child = NULL;
	return node;


}

/*
创建新的内部结点
*/
bplus_node_pt bplus_node_new_internal(int m)
{
	bplus_node_pt node = (bplus_node_pt)malloc(sizeof(bplus_node_t));
	if (node == NULL)
	{
		return NULL;
	}
	node->parent = NULL;
	node->next = NULL;
	node->keynum = 0;
	node->keys = (KEY*)malloc(sizeof(KEY) * (m + 1));
	node->data = NULL;
	node->child = (bplus_node_pt*)malloc(sizeof(bplus_node_pt)*(m + 2));;
	if (node->keys == NULL || node->child == NULL)
	{
		free(node->keys);
		free(node->child);
		free(node);
		return NULL;
	}
	
	return node;

}

/*
元素的插入以及分裂操作
*/
int _bplus_tree_insert(bplus_tree_pt tree, bplus_node_pt node, KEY key, VALUE value)
{
	bplus_node_pt parent ,node2;
	int mid;
	KEY temp;
	int i;
	/*先插入叶子结点*/
	for (i = node->keynum; i > 0 && item_cmp(node->keys[i - 1],key) > 0; i--)
	{
		node->keys[i] = node->keys[i - 1];
		node->data[i] = node->data[i - 1];
	}
	node->keys[i] = key;
	node->data[i] = value;
	node->keynum++;
	while (node->keynum > tree->max)
	{
		/*分裂结点*/
		if (node->child == NULL)
		{
			//叶子结点分裂
			node2 = bplus_node_new_leaf(tree->max);
		}
		else {
			//内部结点分裂
			node2 = bplus_node_new_internal (tree->max);
		}
		if (node2 == NULL)
		{
			return 0;
		}
		//拷贝数据
		mid = node->keynum / 2;
		temp = node->keys[mid];
		if (node->child == NULL)
		{
			node2->keynum = node->keynum - mid;
			memcpy(node2->keys, node->keys + mid, sizeof(KEY) * (node2->keynum));
			memcpy(node2->data, node->data + mid, sizeof(KEY) * (node2->keynum));
			node2->next = node->next;
			node->next = node2;

		}
		else
		{

			node2->keynum = node->keynum - mid - 1;

			memcpy(node2->keys, node->keys + mid + 1, sizeof(KEY) * (node2->keynum));
			memcpy(node2->child, node->child + mid + 1, sizeof(bplus_node_pt) * (node->keynum - mid));

			//重新设置父指针
			for (int i = 0; i <= node2->keynum; i++)
			{
				node2->child[i]->parent = node2;
			}


		}

		node->keynum = mid;

		/*插入父节点*/
		parent = node->parent;
		if (parent == NULL)
		{
			//生成一个新的根节点
			parent = bplus_node_new_internal(tree->max);
			if (parent == NULL)
			{
				return 0;
			}
			parent->child[0] = node;
			node->parent = parent;
			tree->root = parent;
		}
		
		/*增加数据 右子树*/
		for (i = parent->keynum; i > 0 && item_cmp(parent->keys[i - 1], temp) > 0; i--)
		{
			parent->keys[i] = parent->keys[i - 1];
			parent->child[i + 1] = parent->child[i];
		}

		parent->keys[i] = temp;
		parent->child[i + 1] = node2;
		parent->keynum++;

		node2->parent = parent;

		//回溯 向上继续判断
		node = parent;


	}
	return 1;
}


int bplus_tree_insert(bplus_tree_pt tree, KEY key, VALUE value)
{
	bplus_node_pt node;
	int ret,index;
	if (tree->root == NULL)
	{
		node = bplus_node_new_leaf(tree->max);
		if (node == NULL)
		{
			return 0;
		}
		tree->root = node;
	}

	node = tree->root;
	//查找叶子结点
	while (node->child != NULL)
	{
		ret = binary_search(node->keys, key, 0, node->keynum - 1, &index);
		if (ret == 1)
		{
			index++;
		}
		node = node->child[index];
	}

	ret = binary_search(node->keys, key, 0, node->keynum - 1, &index);
	if (ret == 1)
	{
		//这个结点已经存在了
		return 0;
	}
	_bplus_tree_insert(tree, node, key, value);
	return 1;
}



void bplus_node_printfnode(KEY* key, int h)
{
	for (int  i = 0; i < h; i++)
	{
		printf("   ");
	}
	if (key == NULL)
	{
		printf("\n");
	}
	else {
		printf("%d\n", *key);
	}
}

void bplus_node_show(bplus_node_pt node, int h)
{
	if (node == NULL)
	{
		return;
	}
	if (node->child != NULL)
	{
		bplus_node_show(node->child[0], h + 1);
	}
	for (int i = 0; i < node->keynum; i++)
	{
		bplus_node_printfnode(&node->keys[i], h);
		if (node->child != NULL)
		{
			bplus_node_show(node->child[i + 1], h + 1);
		}
	}
}

void bplus_tree_printf(bplus_tree_pt tree)
{
	bplus_node_show(tree->root, 0);
}

/*

叶子结点的左旋转 把右节点的第一个值移到左节点
*/
void _bplus_leaf_left_rotate(bplus_node_pt node,int index)
{
	bplus_node_pt left, right;
	left = node->child[index];
	right = node->child[index + 1];
	left->keys[left->keynum] = right->keys[0];
	left->data[left->keynum] = right->data[0];
	left->keynum++;

	//对右节点进行移位
	for (int  i = 0; i < right->keynum - 1; i++)
	{
		right->keys[i] = right->keys[i + 1];
		right->data[i] = right->data[i + 1];
	}

	right->keynum--;

	node->keys[index] = right->keys[0];
}

/*

内部结点的左旋转 把右节点的第一个值移到父节点 父节点对应的值移到左节点
*/
void _bplus_internal_left_rotate(bplus_node_pt node, int index)
{
	bplus_node_pt left, right;
	left = node->child[index];
	right = node->child[index + 1];

	left->keys[left->keynum] = node->keys[index];
	left->child[left->keynum + 1] = right->child[0];
	left->keynum++;

	node->keys[index] = right->keys[0];


	//对右节点进行移位
	for (int i = 0; i < right->keynum - 1; i++)
	{
		right->keys[i] = right->keys[i + 1];
	}

	for (int i = 0; i < right->keynum; i++)
	{
		right->child[i] = right->child[i + 1];
	}

	right->keynum--;

}

/*
合并结点元素的左右两个子节点
*/
void _bplus_node_merge(bplus_node_pt node, int index)
{
	bplus_node_pt left, right;
	left = node->child[index];
	right = node->child[index + 1];
	if (left->child != NULL)
	{
		/*修改左子节点*/
		left->keys[left->keynum] = node->keys[index];
		memcpy(left->keys + left->keynum + 1, right->keys, sizeof(KEY) * (right->keynum));
		
		for (int i = 0; i <= right->keynum; i++)
		{
			right->child[i]->parent = left;
			left->child[left->keynum + i + 1] = right->child[i];
		}

		left->keynum = left->keynum + right->keynum + 1;
	}
	else
	{
		memcpy(left->keys + left->keynum, right->keys, sizeof(KEY) * (right->keynum));
		memcpy(left->data + left->keynum, right->data, sizeof(VALUE) * (right->keynum));

		left->keynum = left->keynum + right->keynum;;
	}

	/*修改父节点*/
	for (int i = index; i < node->keynum - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
	}

	for (int i = index + 1; i < node->keynum; i++)
	{
		node->child[i] = node->child[i + 1];
	}
	node->keynum--;

	/*释放右节点*/
	free(right->keys);
	free(right->data);
	free(right->child);
	free(right);

}

/*
叶子结点的右旋转
*/
void _bplus_leaf_right_rotate(bplus_node_pt node, int index)
{
	bplus_node_pt left, right;
	left = node->child[index];
	right = node->child[index + 1];

	for (int i = right->keynum; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}
	right->keynum++;
	right->keys[0] = left->keys[left->keynum - 1];
	right->data[0] = left->data[left->keynum - 1];

	left->keynum--;
	node->keys[index] = right->keys[0];

}

/*
内部结点的右旋转 左节点的最后一个值到父节点 父节点对应的值到右节点
*/
void _bplus_internal_right_rotate(bplus_node_pt node, int index)
{
	bplus_node_pt left, right;
	left = node->child[index];
	right = node->child[index + 1];
	for (int  i = right->keynum; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
	}
	right->keys[0] = node->keys[index];
	for (int i = right->keynum + 1; i > 0; i--)
	{
		right->child[i] = right->child[i - 1];
	}
	right->child[0] = left->child[left->keynum];
	right->keynum++;

	node->keys[index] = left->keys[left->keynum - 1];
	left->keynum--;


}


void _bplus_tree_delete(bplus_tree_pt tree, bplus_node_pt node, int index)
{
	bplus_node_pt parent, sibling;
	/*先删除叶子结点的指定的值*/
	for (int i = index; i < node->keynum - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
		node->data[i] = node->data[i + 1];
	}
	node->keynum--;
	parent = node->parent;
	while (node->keynum < tree->min  &&  parent!= NULL)
	{
		/*寻找到当前结点在父节点当中的位置*/
		for ( index = 0; index <= parent->keynum && parent->child[index] != node; index++);
		if (index > parent->keynum)
		{
			//在他的父节点中没找到这个孩子
			return;
		}
		if (index == 0)
		{
			//如果是第一个结点  没有左兄弟 只有右兄弟
			sibling = parent->child[1];
			if (sibling->keynum > tree->min)
			{
				//迁移数据
				if (node->child == NULL)
				{
					//叶子结点的迁移
					_bplus_leaf_left_rotate(parent, 0);
				}
				else {
					_bplus_internal_left_rotate(parent, 0);

				}

			}
			else
			{
				/*合并兄弟*/
				_bplus_node_merge(parent, 0);
			}
		}
		else
		{
			/*
			如果结点是父节中的第index个子节点，兄弟是第index - 1
			中间的分割元素是父节点中的第index - 1个元素
			*/
			sibling = parent->child[index - 1];
			if (sibling->keynum > tree->min)
			{
				//从左兄弟迁移数据
				if (node->child == NULL)
				{
					//叶子结点的右旋转
					_bplus_leaf_right_rotate(parent, index - 1);
				}
				else {
					//内部结点的右旋转
					_bplus_internal_right_rotate(parent, index - 1);
				}

			}
			else
			{
				/*合并兄弟*/
				_bplus_node_merge(parent, index - 1);
			}


		}

		node = parent;
		parent = node->parent;
		
	}

	if (tree->root->keynum == 0 && tree->root->child != NULL)
	{
		node = tree->root;
		tree->root = node->child[0];
		free(node->keys);
		free(node->data);
		free(node->child);
		free(node);
	}



}


void bplus_tree_delete(bplus_tree_pt tree, KEY key)
{
	bplus_node_pt node = tree->root;
	int ret = 0, index;
	/*先查找到叶子*/
	while (node->child != NULL)
	{
		ret = binary_search(node->keys, key, 0, node->keynum - 1, &index);
		if (ret == 1)
		{
			index++;
		}
		node = node->child[index];
	}
	ret = binary_search(node->keys, key, 0, node->keynum - 1, &index);
	if (ret == 0)
	{
		return;
	}

	_bplus_tree_delete(tree,node,index);

	return;

}



int main()
{
	bplus_tree_pt tree;
	int ret;
	ret = bplus_tree_create(&tree, 5);
	for (int i = 0; i < 30; i++)
	{
		bplus_tree_insert(tree, i, 1);
	}
	bplus_tree_printf(tree);

	printf("\n删除元素\n");

	bplus_tree_delete(tree, 1);
	bplus_tree_delete(tree, 2);
	bplus_tree_delete(tree, 3);
	bplus_tree_delete(tree, 4);
	bplus_tree_delete(tree, 5);
	bplus_tree_delete(tree,6);
	bplus_tree_delete(tree, 7);
	bplus_tree_delete(tree, 8);
	bplus_tree_delete(tree, 9);
	bplus_tree_delete(tree, 10);
	bplus_tree_delete(tree, 11);
	bplus_tree_delete(tree, 12);
	bplus_tree_delete(tree, 26);
	bplus_tree_delete(tree, 25);
	bplus_tree_delete(tree, 23);
	bplus_tree_printf(tree);

}

