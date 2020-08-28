#ifndef DSACPP_BST_ENTRY_H_
#define DSACPP_BST_ENTRY_H_
/*����*/

template<class K, class V>
class Entry
{
public:
	K key_; V value_; //�ؼ��롢��ֵ

	Entry(K k = k(),V v = v()) //k()����ʾĬ��ֵΪ0�����൱��k = k() ==��k=0��https://stackoverflow.com/questions/46330646/what-does-const-k-k-k-mean-in-this-constructor-function��
		:key_(k), value_(v)
	{}
	Entry(const Entry<K, V>& e) //�������캯��
		: key_(e.key_), value_(e.value_)
	{}
	
	// �Ƚ������ж���
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
