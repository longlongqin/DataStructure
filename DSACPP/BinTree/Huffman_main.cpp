//Huffman编码的总体框架
#include "Huffman.h"


int main(int argc, char* argv[]) //Huffman编码算法的统一测试
{
	int* freq = statistics(argv[1]); //根据样本文件，统计各字符出现频率
	HuffForest* forest = initForest(freq); release(freq); //创建Huffman森林
	HuffTree* tree = generateTree(forest); release(forest); //生成Huffman编码树
	HuffTable* table = generateTable(tree); //将Huffman编码树转换为编码表
	for (int i = 2; i < argc; i++) //对命令行传入的每一明文串
	{
		Bitmap* codestring = new Bitmap; //二进制编码串
		int n = encode(table, codestring, argv[i]); //将根据编码表生成（长度为n）
		decode(tree, codestring, n); //利用Huffman编码树，对长度为n的二进制编码串解码
		release(codestring);
	}

	release(table);
	release(tree);
	return 0;

}