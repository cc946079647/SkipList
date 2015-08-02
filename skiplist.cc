#include "skiplist.h"
#include <iostream>
template<class Value>
void print(Value value)
{
	if(value==NULL)
	{
		std::cout<<"NULL"<<std::endl;
		return;
	}
	std::cout<<value<<std::endl;
}
bool less(int k1,int k2)
{
	return k1<k2;
}
bool equal(int k1,int k2)
{
	return k1==k2;
}
int main()
{
	SkipList<int,const char*>list(99);
	list.less=less;
	list.equal=equal;

	list.insert(1,"one");
	list.insert(3,"three");

	list.insert(5,"five");
	print(list.search(1));
	print(list.search(2));
	print(list.search(3));
	print(list.search(5));

	list.remove(3);
	list.remove(4);
	print(list.search(1));
	print(list.search(2));
	print(list.search(3));
	print(list.search(5));

	list.insert(1,"modified one");

	print(list.search(1));
	print(list.search(2));
	print(list.search(3));
	print(list.search(5));
	return 0;
}