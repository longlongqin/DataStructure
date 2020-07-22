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


#endif
