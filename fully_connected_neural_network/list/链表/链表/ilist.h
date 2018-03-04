
template < class elemType >
class ilist_item{
public:
	ilist_item():_value(0),_next(0) {}

	virtual elemType & get_value();
	virtual ilist_item<elemType> * &next_item();
private:
	elemType _value;
	ilist_item<elemType> * _next;
};

template < class elemType >
class ilist{
public:
	ilist():_at_front( 0 ), _at_end( 0 ), _size( 0 ) {}

	~ilist(){ remove_all();}
	virtual bool insert( int index, elemType value );
	virtual bool insert_front( elemType value );
	virtual bool insert_end( elemType value );
	virtual ilist_item<elemType> * find( elemType value );

	virtual ilist_item<elemType> * new_item( void );

	virtual bool remove_value( elemType value );
	virtual bool remove_index( int index);
	virtual bool remove_front( void );
	virtual bool remove_end( void );
	virtual bool remove_all( void );

	int size( void );

	virtual void display( void );
	virtual bool reserve( void );

	virtual bool contact( ilist catlist );

private: 
	ilist_item<elemType> *_at_front; 
	ilist_item<elemType> *_at_end; 
	int _size;
};