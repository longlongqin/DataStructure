#pragma once
//2.5.2 ������

template<typename T>
void permute(Vector<T>& v)  //�������������ʹ��Ԫ�صȸ��ʳ����ڸ�λ��
{
	for (int i = v.size(); i > 0; --i) //�Ժ���ǰ
		swap(v[i - 1], v[rand() % i]);  //V[i - 1]��V[0, i)��ĳһ���Ԫ�ؽ���
}
