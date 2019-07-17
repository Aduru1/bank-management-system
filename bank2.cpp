//--------------------------------------------------------------
//                   Header Files 
//--------------------------------------------------------------
#include<iomanip>
#include<iostream>
#include<cctype>
#include<fstream>
#include<windows.h>
using namespace std;

//---------------------------------------------------------------
//                   Class in  this Project
//---------------------------------------------------------------


class account
{
	int accnum;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	
	void show_account() const;
	void dep(int);	
	int returndeposit() const;	
	void modify();	
	void draw(int);	
	int returnaccnum() const;	
	char rettype() const;
	void report() const;	
};         

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>accnum;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() const
{
	cout<<"\nAccount No. : "<<accnum;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : "<<accnum;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<accnum<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::returnaccnum() const
{
	return accnum;
}

int account::returndeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//--------------------------------------------------------------
//    	           declaration of fuctions
//---------------------------------------------------------------
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void flashscreen();	//introduction screen function

//---------------------------------------------------------------
//    	              Main Function 
//----------------------------------------------------------------


int main()
{
	char ch;
	int num;
	flashscreen();
	system("color b4");
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. NEW ACCOUNT";
		cout<<"\n\n\t2. DEPOSIT AMOUNT";
		cout<<"\n\n\t3. WITHDRAW AMOUNT";
		cout<<"\n\n\t4. BALANCE ENQUIRY";
		cout<<"\n\n\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t6. CLOSE AN ACCOUNT";
		cout<<"\n\n\t7. MODIFY AN ACCOUNT";
		cout<<"\n\n\t8. EXIT";
		cout<<"\n\n\tSelect Your choice (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter  account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter  account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter  account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter  account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using Aduru bank management system ";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//---------------------------------------------------------------
//    	          function to write in file
//---------------------------------------------------------------

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//---------------------------------------------------------------
//    	function to read specific record from file
//---------------------------------------------------------------

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open  or file not found !! \nPress any Key...";
		return;
	}
	cout<<"\nBalence Details\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.returnaccnum()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}


//--------------------------------------------------------------
//    	function for modify record in file
//---------------------------------------------------------------

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open  or file not found !! \n Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.returnaccnum()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//---------------------------------------------------------------
//    	function for deletion of record in file
//---------------------------------------------------------------


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open  or file not found !! \n Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.returnaccnum()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//---------------------------------------------------------------
//    	function for show all accounts deposit list
//---------------------------------------------------------------

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open  or file not found !! \n Press any Key...";
		return;
	}
	cout<<"\n\n\t\tAccount Holder List\n\n";
	cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	cout<<"Acc num      Name        Type  Balance\n";
	cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//---------------------------------------------------------------
//    	function for deposit , withdraw amounts
//---------------------------------------------------------------

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.returnaccnum()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.returndeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}
     

//---------------------------------------------------------------
//             screen name's for this project      	
//---------------------------------------------------------------


void flashscreen()
{
	system("color e0");
	cout<<"\n\n\n\t\t\t\t*****************WELCOME******************* ";

	cout<<"\n\n\t\t\t\t\t***BANK MANAGEMENT SYSTEM***";
	cout<<"\n\n\t\t\t\t\t\tL P U";
	cout<<"\n\n\n\n\n\n\n\t\t\t\tpress ENTER for main menu ";
	
		
	cin.get();
}

//---------------------------------------------------------------
//                     End of project   	
//---------------------------------------------------------------
		   
