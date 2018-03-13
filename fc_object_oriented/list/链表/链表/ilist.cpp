#include"ilist.h"
#include<iostream>
using namespace std;


/**************************ilist_item**************************/
//此处返回值为引用类型，使得使用该函数可以对_value进行修改
template < class elemType > 
inline elemType & ilist_item< elemType >:: get_value()
{
	return _value;
}
//此处返回值为引用类型，使得使用该函数可以对_next进行修改
template < class elemType > 
inline ilist_item<elemType> * &ilist_item< elemType >::next_item()
{
	return _next;
}


/***************************ilist******************************/


//为新的链表项分配内存空间
template< class elemType >
inline ilist_item<elemType> * ilist<elemType>:: new_item( void )
{
	return new ilist_item<elemType>; 
}

//在链表项索引为index的位置插入一个值为value的链表项,索引从1开始
template< class elemType >
inline bool ilist<elemType>::insert( int index, elemType value )
{

	ilist_item<elemType> * index_adr = _at_front;
	//插入位置超过链表项数
	if( index <=0 || index >_size + 1 )
		return false;
	
	if( index == 1 ){  //插入位置为链表的第一项，则相当于插入链表头
		return insert_front( value );
	}
	else if( index == _size +1 ){   //插入位置为链表的最后一项+1，则相当于插入链表尾
		return insert_end( value );
	}
	else{    //在链表的中间位置插入元素
		ilist_item<elemType> * new_adr = new_item( );
		if( ! new_adr )
			return false;
		new_adr->get_value( ) = value;
		for( int i = 2; i < index; i++ ){    //获得链表的第index -1个链表项的地址
			index_adr = index_adr->next_item();
		}
		new_adr->next_item() = index_adr->next_item();//将新建的链表项插入第index位置，建立链表关系
		index_adr->next_item() = new_adr;
		
		_size += 1;
		return true;
	}
}


//插入链表头
template< class elemType >
inline	bool ilist<elemType>::insert_front( elemType value )
{
	ilist_item<elemType> * front_adr = new_item( );
	if( front_adr ){
		front_adr->get_value() = value;
		if( _at_front ){  //如果链表不为空
			front_adr->next_item() = _at_front;
			_at_front = front_adr;
		}
		else{//链表为空
			_at_front = front_adr;
			_at_end = front_adr;
		}
		_size += 1;
		return true;
	}
	else 
		return false;

}


//插入链表尾

template< class elemType >
inline bool ilist<elemType>::insert_end( elemType value )
{
	ilist_item<elemType> * end_adr = new_item( );
	if( end_adr ){
		end_adr->get_value() = value;
		if( _at_end ){ //如果链表不为空
			_at_end->next_item() = end_adr;
			end_adr->next_item() = 0;
			_at_end = end_adr;
		}
		else{  //如果链表为空
			_at_front = end_adr;
			_at_end = end_adr;
		}
		_size += 1;
		return true;
	}
	else 
		return false;
}

//找到第一个值为value的链表项的地址
template< class elemType >
inline ilist_item<elemType> * ilist<elemType>:: find( elemType value )
{
	ilist_item<elemType> *adr = _at_front;
	while( adr ){
		if( adr->get_value() == value )
			return adr;
		adr = adr->next_item();
	}
	return 0;
}

//删除第一个值为value的链表项
template< class elemType >
inline	bool ilist<elemType>::remove_value( elemType value )
{
	ilist_item<elemType> *adr = _at_front;
	ilist_item<elemType> *pre = _at_front;
	while( adr ){ //链表项不为空
		if( adr->get_value() == value ){  //链表项的值与value相同
			if( adr == _at_front ){//如果链表项为第一项
				return remove_front();
			}
			else if( adr == _at_end ){//如果链表项为最后一项
				return remove_end();
			}
			else{//链表项为中间项
				pre->next_item() = adr->next_item ();
				_size -= 1;
				delete adr;
				return true;
			}
		}
		else{//链表项的值与value不想等，继续判断下一个链表项
			pre = adr;
			adr = adr->next_item();
		}
	}
	return false;
}

template< class elemType >
inline bool ilist<elemType>::remove_index( int index)
{
	int i;
	ilist_item<elemType> *adr = _at_front;
	ilist_item<elemType> *pre = _at_front;
	if( index <=0 || index > _size )
		return false;
	if( index ==1 )
		return remove_front();
	else if( index == _size )
		return remove_end();
	else{
		for( i =2; i <= index; i++ ){
			pre = adr;
			adr = adr->next_item();
		}
		pre->next_item() = adr->next_item();
		delete adr;
		_size -=1;
		return true;
	}
}
//删除链表头
template< class elemType >
inline	bool ilist<elemType>::remove_front( void )
{
	ilist_item<elemType> *adr = _at_front;
	if( !_at_front )
		return false;
	_at_front = _at_front->next_item();
	if( _at_front ==0 )
		_at_end =0;
	_size -= 1;
	delete adr;
	return true;
}


//删除链表尾
template< class elemType >
inline bool ilist<elemType>::remove_end( void )
{
	ilist_item<elemType> *adr = _at_front;
	//链表为空时，返回错误
	if( !_at_end )
		return false;

	if( adr == _at_end ){  	//链表只包含一项时
		delete adr;
		_at_end = 0;
		_at_front = 0;
	}
	else{   //连表包含的项数多于1个
		while( adr->next_item() != _at_end ){
			adr =adr->next_item();
		}
		adr->next_item() = 0;
		delete _at_end;
		_at_end = adr;
	}
	_size -= 1;
	return true;	
}

//删除整个链表
template< class elemType >
inline bool ilist<elemType>::remove_all( void )
{
	ilist_item<elemType> *adr = _at_front;
	if( !_at_front )
		return false;
	while( adr ){
		remove_front( );
		adr = _at_front;
	}
	return true;

}

template< class elemType >
inline int ilist<elemType>::size( void )
{
	return _size;
}

//显示链表项
template< class elemType >
inline void ilist< elemType >::display( void )
{
	ilist_item<elemType> *adr = _at_front;
	cout<<"( "<< _size <<" )";
	cout<<"(front  ";
	while( adr ){
		cout<< adr->get_value()<<"  ";
		adr = adr->next_item();
	}
	cout<<"end）"<<endl;
}

template< class elemType >
inline bool ilist< elemType >::reserve( void )
{
	ilist_item<elemType> *end = _at_end;
	int i = 1;
	while( i <= _size ){
		if( insert( i,end->get_value() ) ){
			remove_end();
			end = _at_end;
			i += 1;
		}
		else
			return false;
	}
	return true;
}

template< class elemType >
inline bool ilist< elemType >::contact( ilist catlist )
{
	ilist_item<elemType> *adr = catlist._at_front;
	while( adr ){
		if( insert_end( adr->get_value() ))
			adr = adr->next_item();
		else
			return false;
	}
	return true;
}




