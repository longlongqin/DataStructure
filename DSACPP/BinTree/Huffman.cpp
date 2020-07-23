#include "Huffman.h"

#include <string.h>

//构建Huffman编码、解码时，所使用的的函数

//字符出现频率统计
int* statistics(char* sample_text_file)
{
	int* freq = new int[N_CHAR];
	memset(freq, 0, sizeof(int) * N_CHAR); //清零（初始时 每个字符出现都为0次）
	FILE* fp = fopen(sample_text_file, "r"); //打开文件（assert：文件存在且能正确打开）
	for (char ch; 0 < fscanf(fp, "%c", &ch);) //逐个扫描样本文件中的每个字符
	{
		if (ch >= 0x20) //0x20 = 32（对照ASCII表可知道它代表的字符）
			freq[ch - 0x20]++;
	}
	fclose(fp);
	return freq;
	/*
	* freq表示样本文件中字符串中每个字符出现的频率，
	* 数组的下标是由 “对应字符所对应的十进制码 - 32”得到的。（因为下标需要从0开始）
	*/
}


//初始化Huffman森林
HuffForest* initForest(int* freq) //根据频率统计表，为每一个字符创建为一棵树
{
	HuffForest* forest = new HuffForest;
	for (int i=0; i<N_CHAR; i++) //为每一个字符
	{
		if (freq[i] != 0)  //频率为0的字符，说明在这个字符串中就没出现过，所以不用管它（自己家的判断）
		{
			forest->insertAsLast(new HuffTree); //生成一棵树
			forest->last()->data_->insertAsRoot(HuffChar(0x20 + i, freq[i]));
			/*
			* 在这里链表的节点是 BinTree<HuffChar>类型，该类有一个成员函数“insertAsRoot”表示将
			* forest是HuffForest类的一个对象；HuffForest = List<HuffTree*>
			* HuffTree = BinTree<HuffChar>
			* HuffChar 是Huffman超字符 类，它的成员变量为：char ch_; int weight_; //字符、频率(weight权重)
			*
			* forest->last() 相当于 List<HuffTree*>->last() ~ ListNode<HuffTree*>（最后一个节点）
			* forest->last()->data_ 相当于  ListNode<HuffTree*>->data_ ~ HuffTree* data_; ~ BinTree<HuffChar>* data_;
			* forest->last()->data_->insertAsRoot() 相当于 [类型:BinTree<HuffChar>*]data_->insertAsRoot() ~ BinNode<HuffChar>（成为根节点）
			* insertAsRoot(HuffChar(0x20 + i, freq[i])) 带入。
			*/
		}
	}

	return forest;
}



//构造Huffman编码树

//1. 找出最小权重的(超)字符
HuffTree* minHChar(HuffForest* forest) //在Huffman森林中找到权重最小的（超）字符（此时每个字符都是一个树）
{
	ListNodePosi<HuffTree*> p = forest->first(); //从森林的首节点出发
	ListNodePosi<HuffTree*> minchar = p; //最小Huffman树所在的节点位置
	int minWeight = p->data_->root()->data_.weight_; //目前的最小权重
	while (forest->valid(p = p->succ_)) //遍历所有节点
	{
		if (minWeight > p->data_->root_->data_.weight_) //若当前节点所含树更小，则更新记录
		{
			minchar = p;
			minWeight = p->data_->root_->data_.weight_;
		}
			
	}
	return forest->remove(minchar);
}

//2. 生成Huffman编码树
HuffTree* generateTree(HuffForest* forest)
{
	while (forest->size() > 1) //因为最后剩下那一个树就是最后的Huffman编码树
	{
		HuffTree* T1 = minHChar(forest);
		HuffTree* T2 = minHChar(forest);
		HuffTree* S = new HuffTree();

		S->insertAsRoot(HuffChar('^', T1->root()->data_.weight_ + T2->root()->data_.weight_));
		S->attachAsLC(S->root(), T1);
		S->attachAsRC(S->root(), T2);

		forest->insertAsLast(S);  //将当前新生成的子树合并到森林中，同时删除那两个子树
	}
	return forest->first().data_; //循环结束时，森林中唯一（列表首节点中）的那棵树即是 Huffman树
}


//生成Huffman编码表

//1. 通过遍历获取各字符的编码
static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi<HuffChar> v) //通过遍历获取各字符的编码
{
	if (IsLeaf(*v)) //如果是叶子节点
	{
		table->put(v->data_.ch_, code->bits2string(length));
		return;
	}

	if (HasLChild(*v)) //left = 0 , 向左走向为0
	{
		code->clear(length);
		generateCT(code, length + 1, table, v->lc_);
	}

	if (HasRChild(*v)) //right = 1 , 向右走向为1
	{
		code->set(length);
		generateCT(code, length + 1, table, v->rc_);
	}
}

// 2. 将各字符编码同一存入以散列表实现的编码表中
HuffTable* generateTable(HuffTree* tree)
{
	HuffTable* table = new HuffTable;
	Bitmap* code = new Bitmap;

	generateCT(code, 0, table, tree->root());
	release(table);
	return table;
}


//编码、解码这两部分 暂时看不懂，先不写（✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖✖）

//编码
//int encode(HuffTable* table, Bitmap* codestring, char* s) //按照编码表对Bitmap串编码
//{
//	int n = 0; //待返回的编码串总长n
//	for (size_t m = strlen(s), i = 0; i < m; i++) //对于明文中的每个字符
//	{
//		char** pCharCode = table->get(s[i]); //取出其对应的编码串
//
//	}
//}