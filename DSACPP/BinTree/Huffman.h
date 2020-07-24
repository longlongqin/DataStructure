#ifndef DSACPP_BINTREE_HUFFMAN_H
#define DSACPP_BINTREE_HUFFMAN_H

#include "BinTree.h"
#include "IncludedImplementCpp.h"

//超字符
#define N_CHAR (0x80 - 0x20) //其实就是对应ASCII表中的：32(space)~127(DEL)

class HuffChar //Huffman超字符
{
	char ch_; int weight_; //字符、频率(weight权重)

	HuffChar(char ch ='^', int weight = 0 )
		: ch_(ch), weight_(weight)
	{}

	//比较器、判断器
	bool operator<(const HuffChar& hc)	{ return weight_ > hc.weight_; } //权重比较
	bool operator==(const HuffChar& hc) { return weight_ == hc.weight_; }
};


//Huffman编码树（由BinTree派生，节点类型为HuffChar）
#define HuffTree	BinTree<HuffChar>

//Huffman森林（使用List模板类实现）
#include "../List/List.h"
#include "../List/member_function_implement.h"
typedef List<HuffTree*> HuffForest; //Huffman森林

//Huffman二进制编码
#include "Bitmap.h"
typedef Bitmap Huffman;

//Huffman编码表（留个坑这里使用HashTable实现，待到那时再补全HashTable的实现⭐⭐）
#include "../HashTable/HashTable.h" //用HashTable实现（记得回来补全它）
typedef HashTable<char, char*> HuffTable; //Huffman编码表



/*其他函数*/
//字符出现频率统计
int* statistics(char* sample_text_file);

//初始化Huffman森林
HuffForest* initForest(int* freq); //根据频率统计表，为每一个字符创建为一棵树


//构造Huffman编码树
//1. 找出最小权重的(超)字符
HuffTree* minHChar(HuffForest* forest); //在Huffman森林中找到权重最小的（超）字符（此时每个字符都是一个树）
//2. 生成Huffman编码树
HuffTree* generateTree(HuffForest* forest);


//生成Huffman编码表
//1. 通过遍历获取各字符的编码
static void generateCT(Bitmap* code, int length, HuffTable* table, BinNodePosi<HuffChar> v); //通过遍历获取各字符的编码
// 2. 将各字符编码同一存入以散列表实现的编码表中
HuffTable* generateTable(HuffTree* tree);


//编码
int encode(HuffTable* table, Bitmap* codestring, char* s);

//解码
void decode(HuffTree* tree, Bitmap* code, int n);
#endif
