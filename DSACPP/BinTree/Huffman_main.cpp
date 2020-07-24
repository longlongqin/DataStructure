//Huffman�����������
#include "Huffman.h"


int main(int argc, char* argv[]) //Huffman�����㷨��ͳһ����
{
	int* freq = statistics(argv[1]); //���������ļ���ͳ�Ƹ��ַ�����Ƶ��
	HuffForest* forest = initForest(freq); release(freq); //����Huffmanɭ��
	HuffTree* tree = generateTree(forest); release(forest); //����Huffman������
	HuffTable* table = generateTable(tree); //��Huffman������ת��Ϊ�����
	for (int i = 2; i < argc; i++) //�������д����ÿһ���Ĵ�
	{
		Bitmap* codestring = new Bitmap; //�����Ʊ��봮
		int n = encode(table, codestring, argv[i]); //�����ݱ�������ɣ�����Ϊn��
		decode(tree, codestring, n); //����Huffman���������Գ���Ϊn�Ķ����Ʊ��봮����
		release(codestring);
	}

	release(table);
	release(tree);
	return 0;

}