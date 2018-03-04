#include"ilist.cpp"


int main()
{
	ilist<char> mylist;
	ilist_item<char> *adr;
	char i ='A';
	int value = 20;
	cout<<"*****************insert_front******************"<<endl;
	while( mylist.insert_front( i )){
		i += 1;
		if( i == 'E' ){
			mylist.display();
			cout<<"the size of the list is: "<<mylist.size()<<endl;
			break;
		}
	}
	cout<<"*****************insert_end********************"<<endl;
	while( mylist.insert_end( i ) ){
		i += 1;
		if( i == 'K' ){
			mylist.display();
			cout<<"the size of the list is: "<<mylist.size()<<endl;
			break;
		}
	}
	cout<<"********************insert*********************"<<endl;
	cout<<"insert 20: ";
	if( mylist.insert( 20, 'O' ) )
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"insert 11: ";
	if( mylist.insert( 11, 'O') )
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"insert 5: ";
	if( mylist.insert( 5, 'O' ) )
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"insert 1: ";
	if( mylist.insert( 1, 'O' ) )
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"insert -1: ";
	if( mylist.insert( -1, 'O' ) )
		mylist.display();
	else
		cout<<"wrong position"<<endl;

	cout<<"*********************find**********************"<<endl;
	if( adr = mylist.find(value) )
		cout<<"the address of "<< value <<" is: "<< adr<<endl;
	else
		cout<<"the " <<value <<" is not in this list"<<endl;

	cout<<"*************remove_front*********************"<<endl;
	if( mylist.remove_front(  ) )
		mylist.display();
	else{
		cout<<"the list is empty"<<endl;
	}
	cout<<"*************remove_end***********************"<<endl;
	if( mylist.remove_end(  ) )
		mylist.display();
	else{
		cout<<"the list is empty"<<endl;
	}
	cout<<"***************remove_value******************"<<endl;
	cout<<"remove O: ";
	if( mylist.remove_value( 'O' ) )
		mylist.display();
	else
		cout<<"the value is not in the list"<<endl;
	cout<<"***************remove_index******************"<<endl;
	cout<<"remove 20: ";
	if( mylist.remove_index( 20 ))
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"remove -1: ";
	if( mylist.remove_index( -1 ))
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"remove 10: ";
	if( mylist.remove_index( 10 ))
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"remove 5: ";
	if( mylist.remove_index( 5 ))
		mylist.display();
	else
		cout<<"wrong position"<<endl;
	cout<<"remove1: ";
	if( mylist.remove_index( 1 ))
		mylist.display();
	else
		cout<<"wrong position"<<endl;

	ilist<char> mylist2;
	for( i = 'U'; i <= 'Z'; i += 1 ){
		mylist2.insert_end( i );
	}

	cout<<"*****************contact*********************"<<endl;
	if( mylist.contact( mylist2)){
		mylist.display();
		mylist2.display();
	}
	else
		cout<<"contact error"<<endl;

	cout<<"*****************reserve*********************"<<endl;
	if( mylist.reserve( )){
		mylist.display();
	}
	else
		cout<<"reserve error"<<endl;

	cout<<"*****************remove_all******************"<<endl;
	if( mylist.remove_all( ))
		mylist.display();
	else
		cout<<"the list is wmpty"<<endl;


	return 1;
}