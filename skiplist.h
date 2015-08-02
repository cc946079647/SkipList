#ifndef SKIPLIST
#define SKIPLIST
#include <stdlib.h>
#include <time.h>
#define MAXLEVEL 12

template<typename Key,typename Value>
class Node{
public:
	Node<Key,Value>(int level){_level=level;}
	Node<Key,Value>*forward[MAXLEVEL];
	Key _key;
	Value _value;
	int _level;
};
template<typename Key,typename Value>
class SkipList{
public:
	SkipList(Key maxkey)
	{
		level=MAXLEVEL/2;
		
		head=new Node<Key,Value>(level);
		tail=new Node<Key,Value>(level);

		tail->_key=maxkey;

		for(int i=0;i<this->level;++i)
		{
			head->forward[i]=tail;
		}
	}

	Value search(Key key)
	{
		Node<Key,Value>*ptr=head;
		for(int i=level-1;i>=0;--i)
		{
			while(less(ptr->forward[i]->_key,key))
				ptr=ptr->forward[i];
		}
		ptr=ptr->forward[0];
		if(equal(ptr->_key,key))
			return ptr->_value;
		return NULL;
	}

	void insert(Key key,Value value)
	{
		int iLevel=random();
		if(iLevel>this->level)
		{
			for(int i=this->level;i<iLevel;++i)
			{
				head->forward[i]=tail;
			}
			this->level=iLevel;
		}
		
		Node<Key,Value>*iNode=new Node<Key,Value>(iLevel);
		Node<Key,Value>*update[MAXLEVEL];
		
		Node<Key,Value>*ptr=head;
		for(int i=iLevel-1;i>=0;--i)
		{
			while(less(ptr->forward[i]->_key,key))
				ptr=ptr->forward[i];
			update[i]=ptr;
		}
		if(equal(update[0]->forward[0]->_key,key))
		{
			update[0]->forward[0]->_value=value;
			return;
		}
		iNode->_key=key;
		iNode->_value=value;
		for(int i=0;i<iLevel;++i)
		{
			iNode->forward[i]=update[i]->forward[i];
			update[i]->forward[i]=iNode;
		}
	}

	void remove(Key key)
	{
		Node<Key,Value>*update[MAXLEVEL];
		Node<Key,Value>*ptr=head;
		for(int i=this->level-1;i>=0;--i)
		{
			while(less(ptr->forward[i]->_key,key))
				ptr=ptr->forward[i];
			update[i]=ptr;
		}
		if(!equal(ptr->forward[0]->_key,key))
			return;
		Node<Key,Value>*dNode=update[0]->forward[0];
		int dNodeLevel=dNode->_level;
		for(int i=0;i<dNodeLevel;++i)
		{
			update[i]->forward[i]=dNode->forward[i];
		}
		delete dNode;
	}
	int level;
	Node<Key,Value>*head;
	Node<Key,Value>*tail;

	bool (*less)(Key k1,Key k2);
	bool (*equal)(Key k1,Key k2);

private:
	int random()
	{
		srand((unsigned)time(NULL));
		return rand()%MAXLEVEL+1;
	}
};



#endif