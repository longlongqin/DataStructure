#pragma once
//2.5.2 置乱器

template<typename T>
void permute(Vector<T>& v)  //随机置乱向量，使各元素等概率出现于各位置
{
	for (int i = v.size(); i > 0; --i) //自后向前
		swap(v[i - 1], v[rand() % i]);  //V[i - 1]与V[0, i)中某一随机元素交换
}
