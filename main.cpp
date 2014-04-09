//HEADER FILE USED IN PROJECT
//****************************************************************
#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
#include<ctype.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************




class customer
{
	char custno[6];
	char custno1[6];
	char name[20];
	char name1[20];
	char phoneno[10];
	char phoneno1[10];
	char contypecode[10];

public:
	void create_customer()
	{
		clrscr();
		cout<<"\nNEW CUSTOMER ENTRY...\n";
		cout<<"\nEnter The Customer number. (MAX 5 DIGITS) :  ";
		checkcustno();
		cout<<"\n\nEnter The Name of The Customer (MAX 20 CHARACTERS) :  ";
		checkcustname();
		cout<<"\n\nEnter Customer Phone Number (MAX 10 DIGITS) : ";
		checkcustphoneno();
		cout<<"\n\nEnter Connection Type Code : ";
		connectionlist();
		enterconnection();
		cout<<"\n\nCustomer Record Created..";
	}

	void show_customer()
	{
		cout<<"\nCustomer no. : ";puts(custno);
		cout<<"\nCustomer Name : ";
		puts(name);
		cout<<"\nCustomer Phone Number : ";puts(phoneno);
		cout<<"\nconnection type code : ";puts(contypecode);

	}

	void modify_customer()
	{
		cout<<"\nCustomer no. : "<<custno;
		cout<<"\nModify Customer Name (MAX 20 CHARACTERS) : ";
		checkcustname();
		cout<<"\nModify Phone Number (MAX 10 DIGITS) : ";
		checkcustphoneno();
		cout<<"\nModify Connection Type : ";
		connectionlist();
		enterconnection();

	}

	void connectionlist()
	{
		cout<<"\n\n1.CODE - BBULD499 - limited 256kbps upto 4GB - Rent-499 rs"<<endl<<endl;
		cout<<"\n\n2.CODE - BBULD625 - limited 512kbps upto 4GB - Rent-625 rs"<<endl<<endl;
		cout<<"\n\n3.CODE - BBULD750 - limited 1mbps upto 6GB - Rent-750 rs"<<endl<<endl;
		cout<<"\n\n4.CODE - BBULD900 - limited 4mbps upto 8GB - Rent-900 rs"<<endl<<endl;
	}

	void enterconnection()
	{       int option,cflag=0;
		while(cflag!=1)
		{
		cout<<"\n\nchoose your option  :  ";
		cin>>option;
		switch(option)
		{
		case 1:{strcpy(contypecode,"BBULD499");cflag=1;}break;
		case 2:{strcpy(contypecode,"BBULD625");cflag=1;}break;
		case 3:{strcpy(contypecode,"BBULD750");cflag=1;}break;
		case 4:{strcpy(contypecode,"BBULD900");cflag=1;}break;
		default:{ cout<<"wrong choice entered....enter again";
		  cflag=0;}
		  }
		  }
	}


	void checkcustno()
	{       int i,nflag=0,cndigit;
		while(nflag!=1)
		{
		gets(custno1);
		i=strlen(custno1);
		const char *cndigits="0123456789";
		cndigit=strspn(custno1,cndigits);
		if((i<=5)&&(i!=0)&&(cndigit==i))
		{strcpy(custno,custno1);
		nflag=1;
		}
		else
		{
		 nflag=0;
		 cout<<"\n\nPLEASE ENTER A 5 DIGIT NUMBER , ENTER AGAIN : ";
		 }
		}
	}

	void checkcustname()
	{       int i,nameflag=0,cnchar;
		while(nameflag!=1)
		{
		gets(name1);
		i=strlen(name1);
		char *cnchars="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ";
		cnchar=strspn(name1,cnchars);
		if((i<=20)&&(i!=0)&&(i==cnchar))
		{strcpy(name,name1);
		nameflag=1;
		}
		else
		{cout<<"\n\nPLEASE ENTER A PROPER (MAX.20) CHARACTER NAME ,ENTER AGAIN : ";
		 nameflag=0;
		 }
		}
	}

	void checkcustphoneno()
	{       int i,pflag=0,cpdigit;
		while(pflag!=1)
		{
		gets(phoneno1);
		i=strlen(phoneno1);
		char *cpdigits="0123456789";
		cpdigit=strspn(phoneno1,cpdigits);
		if((i<=10)&&(i>6)&&(cpdigit==i))
		{strcpy(phoneno,phoneno1);
		pflag=1;
		}
		else
		{cout<<"\n\nPLEASE ENTER PROPER (7 or 10) DIGIT NUMBER , ENTER AGAIN : ";
		 pflag=0;
		 }
		}
	}


	char* retcustno()
	{
		return custno;
	}

	void report()
	{
	cout<<setw(11)<<custno<<setw(20)<<name<<setw(13)<<phoneno<<setw(12)<<contypecode<<endl;}


};         //class ends here




//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
customer st;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_customer()
{
	char ch;
	fp.open("customer.dat",ios::out|ios::app);
	do
	{
		st.create_customer();
		fp.write((char*)&st,sizeof(customer));
		cout<<"\n\ndo you want to add more record..(y/n?)";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sps(char n[])
{
	cout<<"\nCUSTOMER DETAILS\n";
	int flag=0;
	fp.open("customer.dat",ios::in);
	while(fp.read((char*)&st,sizeof(customer)))
	{
		if((strcmpi(st.retcustno(),n)==0))
		{
			st.show_customer();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nCustomer does not exist";
	getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_customer()
{
	char n[6];
	int found=0;
	clrscr();
	cout<<"\n\n\tMODIFY CUSTOMER RECORD... ";
	cout<<"\n\n\tEnter The customer no. of The customer : ";
	cin>>n;
	fp.open("customer.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(customer)) && found==0)
	{
		if(strcmpi(st.retcustno(),n)==0)
		{
			st.show_customer();
			cout<<"\nEnter The New Details of Customer : "<<endl;
			st.modify_customer();
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(customer));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
	getch();
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_customer()
{
	char n[6];
	int flag=0;
	clrscr();
	cout<<"\n\n\n\tDELETE CUSTOMER...";
	cout<<"\n\nEnter The Customer no. of the Customer You Want To Delete : ";
	cin>>n;
	fp.open("customer.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(customer)))
	{
		if(strcmpi(st.retcustno(),n)!=0)
			fp2.write((char*)&st,sizeof(customer));
		else
			flag=1;
	}

	fp2.close();
	fp.close();
	remove("customer.dat");
	rename("Temp.dat","customer.dat");
	if(flag==1)
		cout<<"\n\n\tRecord Deleted ..";
	else
		cout<<"\n\nRecord not found";
	getch();
}


//***************************************************************
//    	function to display all Customer list
//****************************************************************

void display_alls()
{
	clrscr();
	fp.open("customer.dat",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		getch();
		return;
	}

	cout<<"\n\n\t\tCUSTOMER LIST\n\n";
	cout<<"================================================================================\n";
	cout<<"Customer No.\t"<<"Name\t\t"<<"Phone Number\t"<<"Connection Type\n";
	cout<<"================================================================================\n";

	while(fp.read((char*)&st,sizeof(customer)))
	{
		st.report();
	}

	fp.close();
	getch();
	}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
	clrscr();
	textbackground(2);
	textcolor(1);
	gotoxy(35,11);
	cout<<"BROADBAND";
	gotoxy(35,14);
	cout<<"CUSTOMER DATABASE MANAGEMENT";
	gotoxy(35,17);
	cout<<"SYSTEM";
	cout<<"\n\n\nMADE BY : JAYANT PANWAR & PRABHSIMRAN SINGH";
	cout<<"\n\nSCHOOL : K.V.No.1, JRC";
	getch();
}
//***************************************************************
//EXTRA FUNCTIONS
//***************************************************************
void credits()
{
clrscr();
gotoxy(20,17);
cout<<"CREATORS : Jayant Panwar and Prabhsimran Singh";
getch();
}


//***************************************************************
//    	ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\tADMINISTRATOR MENU";
	cout<<"\n\n\t1.CREATE CUSTOMER RECORD";
	cout<<"\n\n\t2.DISPLAY ALL CUSTOMER RECORD";
	cout<<"\n\n\t3.DISPLAY SPECIFIC CUSTOMER RECORD ";
	cout<<"\n\n\t4.MODIFY CUSTOMER RECORD";
	cout<<"\n\n\t5.DELETE CUSTOMER RECORD";
	cout<<"\n\n\t6.CONNECTION TYPE REFERENCE";
	cout<<"\n\n\t7.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
	cin>>ch2;
	switch(ch2)
	{
		case 1: clrscr();
			write_customer();break;
		case 2: display_alls();break;
		case 3:
			char num[6];
			clrscr();
			cout<<"\n\n\tPlease Enter The Customer No. ";
			cin>>num;
			display_sps(num);
			break;
		case 4: modify_customer();break;
		case 5: delete_customer();break;
		case 6: clrscr();st.connectionlist();getch();break;
		case 7: return;
		default:cout<<"\a";
	}
	admin_menu();
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. ADMINISTRATOR MENU";
		cout<<"\n\n\t02. CREDITS";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		ch=getche();
		switch(ch)
		{
			case '1':clrscr();
				 admin_menu();
				 break;
			case '2':credits();
				 break;
			case '3':exit(0);
				 break;
			default :cout<<"\a";
		}
	}while(ch!='4');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

