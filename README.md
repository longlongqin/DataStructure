# DataStructure

数据结构的代码的实现

# 参考教程

~~https://www.cnblogs.com/skywang12345/p/3603935.html~~

现在（2020-06-02 10:28:16）看邓俊辉老师的《数据结构》

**未看章节**：

1. 第一章 绪论(下)  —— （xc）动态规划

# 注意

1. 本系列中，所有的区间均为**左闭右开**，即：`[a, b)`
2. 在所`#include "xxx.h"`的时候，如果该模板类中的成员函数的 定义(实现)是分开实现的（在`xxx.cpp`中实现的），则理应加上`#include "xxx.cpp"`（如果已经将该`xxx.cpp`文件包含在 `IncludedImplementCpp.h`之类的文件中，则只需`#include "IncludedImplementCpp.h"`即可。）

# 第二章 向量

## 1.默认(缺省)参数的声明与定义

**在类中，使用带有默认参数值的函数，若声明、定义是分开的，则需要在定义之中，把默认参数注释掉。**

   > 具体解释：https://www.yuque.com/longlongqin/gs7wey/minyp9

## 2.[**函数指针**](http://c.biancheng.net/view/228.html)与[**函数对象**](http://c.biancheng.net/view/354.html)。

## 3.二分查找的平均成功查找长度推导

关于**二分查找（2.6.5）**平均查找成功长度的推导（数据结构 邓俊辉）的详解：

   > https://ask.csdn.net/questions/699067?sort=votes_count
   >
   > https://blog.csdn.net/qq_33499861/article/details/105103708 [推荐]

# 第三章 列表

## 1.模板别名

在ListNode模板类(P68)代码中：

   `#define ListNodePosi(T) ListNode<T>* `中的语法，[参考](https://zhuanlan.zhihu.com/p/40448645)。

   但是，在C++.0X标准之后，出现了“**模板别名(alias template)**”，关于模板别名，[参考官方解释](https://en.cppreference.com/w/cpp/language/type_alias)。

   

   在这里，还有很多需要注意的地方：

   > 我在StackOverflow中，发出了一个关于：“argument list for alias template "ListNodePosi" is missing”的提问（[传送门](https://stackoverflow.com/questions/62327596/c-argument-list-for-alias-template-is-missing)），答者帮我找出了我的很多问题。

   ```c++
   /*这里有很多错误*/
   #ifndef DSACPP_LIST_LISTNODE_H_
   #define DSACPP_LIST_LISTNODE_H_
   
   typedef int Rank;
   
   template<class T>
   class ListNode
   {
   private:
       T data_;
       ListNodePosi pred_; ListNodePosi succ_;
   
   public:
       ListNode() {}; 
       ListNode(T e, ListNodePosi pred = NULL, ListNodePosi succ = NULL)
           : data_{ e }, pred_{ p }, succ_{ succ } {}
   
   
       ListNodePosi insertAspred(T const& e); 
   };
   
   // alias template
   template<typename T>
   using  ListNodePosi = ListNode<T>*;
   
   template<class T>
   ListNodePosi ListNode<T>::insertAspred(T const& e) 
   /*
   -⭐ there will be a error: argument list for alias template "ListNodePosi" is missing
   */
   {
       ...
   }
   
   #endif
   ```

   问题：

   1. 类似于类模板(在非推断的c++ 17上下文中)，在使用别名模板时**需要显式地提供模板参数列表**。

      ```cpp
      ListNodePosi<single-type-template-argument> ...;
      ```

   2. 在ListNode类模板的声明和定义中，名称ListNodePosi还不知道，但是已经大量使用了。

      > 解决：您可以通过**对ListNode的前向声明**来修复上面的第一个要点，**然后再声明别名模板ListNodePosi**(因为它不需要完整的ListNode)，**最后声明使用别名模板的ListNode定义。**

   3. **推荐使用nullptr而不是NULL**(您实际上需要包括一些头文件才可以访问NULL，<u>而nullptr指针字面量是作为关键字来的</u>)。

   修复后的代码：

   ```c++
   template <typename T> class ListNode; //对 ListNode前向声明
   template <typename T> using ListNodePosi = ListNode<T> *;
   
   template <class T> class ListNode {
   private:
     T data_;
     ListNodePosi<T> pred_; //对应问题1
     ListNodePosi<T> succ_;
   
   public:
     ListNode(){};
     ListNode(T e, ListNodePosi<T> pred = nullptr, ListNodePosi<T> succ = nullptr)
         : data_{e}, pred_{pred}, succ_{succ} {}
   
     ListNodePosi<T> insertAspred(T const &e);
   };
   
   template <typename T> ListNodePosi<T> ListNode<T>::insertAspred(T const &e) {
     /* ... */
   }
   ```



## 2.函数声明时可不写形参的标识符

如：

```c++
#include <iostream>

void copy(int, int); //在这里可以只写出形参的类型，而不必写出形参的标识符

int main()
{
	copy(1, 2);
	return 0;
}

void copy(int x, int y) //在函数的定义（实现）处给出形参的标识符即可
{
	x = y;
	std::cout << " x复制y的值,则x现在的值为：" << x << std::endl;
}
```

# 第四章 栈与队列

1.`__int8`, `__int16`, `__int32`, `__int64`的区别

参考：https://docs.microsoft.com/en-us/cpp/cpp/int8-int16-int32-int64?view=vs-2019