#ifndef DSACPP_BINTREE_BITMAP_H
#define DSACPP_BINTREE_BITMAP_H
//习题[2-34]
//位图
//参考：https://www.cnblogs.com/yuanyb/p/10620729.html
#include <cstdio>
#include <cstdlib>
#include <memory.h>

//在这里规定一个字节的第x位：是从右到左算起的。

class Bitmap //位图Bitmap类
{
private:
	char* M_; //比特图所存放的空间M[]，容量为N_*sizeof(char)*8（这里容量的单位是：比特）
	int N_;	  ///容量为 N_*sizeof(char)*8，就是N*8，一个字节8位（所以N_表示有多少 字节）

protected:
	void init(int n)
	{
		N_ = (n + 7) / 8; //“+7”是为了如果只有1个bit时，也是会占据一个字节的（也就是说容量最少为一个字节）
		M_ = new char[N_];
		memset(M_, 0, N_);  //将指针M后的N个字节用0代替，初始化位图，位全设置为0
	}

public:
	Bitmap(int n = 8) //按指定或默认规模创建比特图（为测试暂时选用较小的默认值）
	{
		init(n); 
	} 
	Bitmap(char *file, int n=8)    //按指定或默认规模，从指定文件中读取比特图
	{
		init(n);
		FILE* fp = fopen(file, "r");
		fread(M_, sizeof(char), N_, fp);
		fclose(fp);
	}

	~Bitmap() //析构时释放比特图空间
	{
		delete[]  M_;
		M_ = nullptr;
	}

public:
	void set(int k) //将第k位置设置为true（将整数k加入当前集合）
	{
		expand(k); //判断是否需要扩容（如果需要，则扩容）
		//1 byte = 8 bit, 0x80 = 128, 0x07 = 7
		M_[k >> 3] |= (0x80>> (k & 0x07));
		/*
		* 在c++中char占一个字节，也就是8bit。在赋值的时候，由于无法对某个bit进行赋值操作，因此应用了位操作。
		*
		* 因为每个字节包含8个比特，所以通过位运算 k>>3 可以确定对应的比特所属第几个字节。设为第M个字节
		* 通过逻辑位与运算 k & 0x07[0b0111] 可以确定比特位所属字节的第几个比特位。设为x。
		* 通过移位操作 0x80[128:0b1000_0000] >> (k & 0x07) 可以得到该比特位所在字节中对应的数值的掩码。
		* 将(128:0b1000_0000)中最高位的1右移x。即将x位设置为1。然后 |=，将M第k字节的第x为设为1。
		*/
	}

	void clear(int k) //第K个比特位清零
	{
		expand(k);
		M_[k >> 3] &= ~(0x80 >> (k & 0x70));
		/*
		* k >> 3：得到所在第M字节中
		* 0x80 = 128 = 0b1000 0000,
		* (k & 0x70) = 一个字节中的第x比特位。
		* 0x80 >> (k & 0x70)：将0b1000 0000 中最高位的1右移x位。（假设x=3,则结果：0b0001 0000）
		*  ~(0x80 >> (k & 0x70))：将各个位翻转（1→0，0→1）就将上一步得到的结果变为:0b1110 1111
		* &= 操作：将第M字节中的（8-x）位 变为 0。达成目的。
		*/
	}

	bool test(int k) //判断是否存在K
	{
		expand(k);
		return M_[k >> 3] & (0x80 >> (k & 0x70));
		/*
		* k >> 3：得到所在第M字节中
		* 0x80 >> (k & 0x70)：将0b1000 0000 中最高位的1右移x位。（假设x=3,则结果：0b0001 0000）
		* M_[k >> 3] & (0x80 >> (k & 0x70))：在(0x80 >> (k & 0x70))的到的结果中除了要比较的那一位为1，
		* 其他均为0.所以在 与(&)操作时，为0的位的与操作结果还是0；只需要看为1（即需要比较的那各位）的位，
		* 如果M_[k >> 3]中的相对应的这一个位也0，那么 0&1=0。那么此时该字节中的8各位均为0，
		* 所以结果：0b0000 0000=0, return 返回的结果为0，即是不存在k的。反之则存在K
		*/
	}

public:
	void expand(int k) ////若被访问的Bitmap[k]已出界，则需扩容
	{
		if (k < 8 * N_) return; // 仍在界内，无需扩容

		int oldN = N_;
		char* oldM = M_;
		init(2 * k); //与向量类似，加倍策略
		memcpy_s(M_, N_, oldM, oldN); //原数据转移至新空间
		delete[] oldM; //删除原数据所占的内存
	}

	void dump(char* file) //将位图整体导出至指定的文件，以便此后的新位图批量初始化
	{
		FILE* fp = fopen(file, "w");
		fread(M_, sizeof(char), N_, fp);
		fclose(fp);
	}

	char* bits2string(int n) //将当前n位转换为字符串 —— ——
	{
		expand(n - 1); //此时可能被访问的最高位为 bitmap[n-1]
		char* s = new char[n + 1]; s[n] = '\0'; //字符串所占空间，由上层调用者负责释放
		for (int i = 0; i < n; i++)
		{
			s[i] = test(i) ? '1' : '0';
		}
		return s; //返回字符串位置
	}
};
#endif
