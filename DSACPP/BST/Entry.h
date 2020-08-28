#ifndef DSACPP_BST_ENTRY_H_
#define DSACPP_BST_ENTRY_H_
/*词条*/

template<class K, class V>
class Entry
{
public:
	K key_; V value_; //关键码、数值

	Entry(K k = k(),V v = v()) //k()：表示默认值为0，就相当于k = k() ==》k=0（https://stackoverflow.com/questions/46330646/what-does-const-k-k-k-mean-in-this-constructor-function）
		:key_(k), value_(v)
	{}
	Entry(const Entry<K, V>& e) //拷贝构造函数
		: key_(e.key_), value_(e.value_)
	{}
	
	// 比较器、判断器
	bool operator< (const Entry<K, V>& e)
	{
		return key_ < e.key_;
	}

	bool operator> (const Entry<K, V>& e)
	{
		return key_ > e.key_;
	}

	bool operator== (const Entry<K, V>& e)
	{
		return key_ == e.key_;
	}

	bool operator!= (const Entry<K, V>& e)
	{
		return key_ != e.key_;
	}
};

#endif
