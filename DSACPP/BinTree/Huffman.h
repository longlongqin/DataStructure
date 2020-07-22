#ifndef DSACPP_BINTREE_HUFFMAN_H
#define DSACPP_BINTREE_HUFFMAN_H

#include "BinTree.h"
#include "IncludedImplementCpp.h"

//���ַ�
#define N_CHAR (0x80 - 0x20) //��ʵ���Ƕ�ӦASCII���еģ�32(space)~127(DEL)

class HuffChar //Huffman���ַ�
{
	char ch_; int weight_; //�ַ���Ƶ��(weightȨ��)

	HuffChar(char ch ='^', int weight = 0 )
		: ch_(ch), weight_(weight)
	{}

	//�Ƚ������ж���
	bool operator<(const HuffChar& hc)	{ return weight_ > hc.weight_; } //Ȩ�رȽ�
	bool operator==(const HuffChar& hc) { return weight_ == hc.weight_; }
};


//Huffman����������BinTree�������ڵ�����ΪHuffChar��
#define HuffTree	BinTree<HuffChar>

//Huffmanɭ�֣�ʹ��Listģ����ʵ�֣�
#include "../List/List.h"
#include "../List/member_function_implement.h"
typedef List<HuffTree*> HuffForest; //Huffmanɭ��


#endif
