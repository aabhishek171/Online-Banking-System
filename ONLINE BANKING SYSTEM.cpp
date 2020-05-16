#include<fstream>
#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;

class account
{
  public:
	char fir[50],name[50],address[100];
	long long int phone_number;
	int ifsc;
	int accno, acctno;
	float amount, deposit,rate;
	account()
	{
		amount=0.00;
		deposit=0.00;
		rate = 0.0;
		ifsc=18571010;
		ifstream file;
		file.open("acctno.dat",ios::in);
		file>>acctno;
		file.close();
	}

	void addnewrecord();
	void viewrecord();
	void updaterecord();
	void read();
	int get_acctno();
	void display();
	
};


void account::addnewrecord()						//to create a new account
{		
	ofstream outfile;
	outfile.open("accountdets.dat",ios::out|ios::binary|ios::app);
	account person;
	gets(person.fir);
	cout<<endl<<"Enter name : ";
	gets(person.name);
	cout<<endl<<"Enter address : ";
	gets(person.address);
	cout<<endl<<"Enter phone number : ";
	cin>>person.phone_number;
	cout<<endl<<"Your PERMANENT ACCOUNT NO: is : "<<(acctno++);
	cout<<endl<<endl<<"Your IFSC : "<<ifsc;
	cout<<endl<<endl<<"Enter deposit (min Rs.350) : ";
	cin>>person.deposit;
	ofstream fout;
      fout.open("acctno.dat",ios::out);
      fout<<acctno;
      fout.close();

	outfile.write((char*) &person, sizeof(person));
	outfile.close();
}

void account::read()
{
	cout<<endl<<"Enter the account number : ";
	cin>>accno;
}


int account::get_acctno()
{
	return accno;
}


void account::viewrecord()		//to view records of account
{
	ifstream f2;
	account t2,t02;
	t02.read();
	f2.open("accountdets.dat",ios::binary|ios::in);
	f2.seekg(0,ios::beg);
	int j=0;
	while(!f2.eof())
	{
		f2.read((char*) &t2,sizeof(t2));

		if(t2.acctno==t02.get_acctno())
		{
			j=1;
			t2.display();
			break;
		}
	}
	if(j!=1)
		cout<<endl<<"Record not found...";
	f2.close();
	cout<<endl<<endl<<"\t\t\t(Press any key to return to MAIN MENU..)";
	getch();
}


void account::display()			//to display records
{
	cout<<endl
	<<"Name         : "<<name<<endl
	<<"Address      : "<<address<<endl
	<<"IFSC         : "<<ifsc<<endl
	<<"Phone Number : "<<phone_number<<endl
	<<"Balance      : "<<deposit<<endl;

}


void account::updaterecord()
{
	int ch2,debit,credit;
	 do{
		system("cls");
		cout<<endl<<endl<<"Please";
		cout<<endl<<"\tEnter 1 to debit(withdraw) "<<endl
		   <<"\tEnter 2 to credit(deposit) "<<endl
		   <<"\tEnter 3 to view account balance "<<endl
		   <<"\tEnter 4 to calculate interest and view balance after the calculations "<<endl
		   <<"\tEnter 5 to close transactions "<<endl;
		cout<<endl<<"Enter choice : ";
		cin>>ch2;
		system("cls");
		switch(ch2)
		{
			case 1:							//to debit(withdraw)
			{
				fstream f3;
				account t3,t03;
				int j=0, count=0, debit;
				t03.read();
				cout<<endl<<"Please enter the amount to be debited : ";
				cin>>debit;
				f3.open("accountdets.dat",ios::binary|ios::in|ios::out);
				f3.seekg(0,ios::beg);
				while(!f3.eof())
				{
					f3.read((char*) &t3,sizeof(t3));

					if(t3.acctno==t03.get_acctno())
					{
						j++;
						break;
					}
					count++;
				 }
				 if(j!=0)
				 {
					if(debit<=t3.deposit)
					{
						t3.deposit-=debit;
						f3.seekp(count*sizeof(t3),ios::beg);
						f3.write((char*) &t3 ,sizeof(t3));
					}
					if(t3.deposit>=250)
						cout<<"Your account balance is Rs"<<t3.deposit<<endl;
					else
						cout<<"Your Balance is not sufficient to debit this amount"<<endl;
				 }
				 else
				 {
					cout<<endl<<"Record NOT found"<<endl;
				 }
				f3.close();
				cout<<endl<<endl<<endl<<endl<<"\t\t(Press any key to return to previous menu..)";
				getch();
				break;

			}

			case 2:				//to credit (deposit)
			{
				fstream f4;
				account t4,t04;
				int j=0, count=0,credit;
				t04.read();
				cout<<endl<<"Please enter the amount to be credited  ";
				cin>>credit;
				f4.open("accountdets.dat",ios::binary|ios::in|ios::out);
				f4.seekg(0,ios::beg);

				while(!f4.eof())
				{
					f4.read((char*) &t4,sizeof(t4));
					if(t4.acctno==t04.get_acctno())
					{
						j++;
						break;
					}
					count++;
				}
				if(j!=0)
				{
					t4.deposit+=credit;
					f4.seekp(count*sizeof(t4),ios::beg);
					f4.write((char*) &t4 ,sizeof(t4));
				}
				else
				{
					cout<<endl<<"Record NOT found";
				}

				cout<<"Your account balance is Rs "<<t4.deposit;
				f4.close();
				cout<<endl<<endl<<endl<<endl<<"\t\t(Press any key to return to previous menu..)";
				getch();
				break;

			}

			case 3:				//to view account balance
			{
				fstream f5;
				account t5,t05;
				int j=0;
				t05.read();
				f5.open("accountdets.dat",ios::binary|ios::in|ios::out);
				f5.seekg(0,ios::beg);
				while(!f5.eof())
				{
					f5.read((char*) &t5,sizeof(t5));
					if(t5.acctno==t05.get_acctno())
					{
						j++;
						break;
					}
				 }
				 if(j!=0)
				 {
					cout<<endl<<endl<<"The ACCOUNT BALANCE is  Rs "<<t5.deposit;
				 }
				 else
				 {
					cout<<endl<<"Record NOT found";
				 }
				f5.close();
				cout<<endl<<endl<<endl<<endl<<"\t\t(Press any key to return to previous menu..)";
				getch();
				break;
			}

			case 4:					//to calculate interest
			{
				fstream f6;
				account t6,t06;
				int timeperiod, j=0;
				float interest;
				t06.read();
				f6.open("accountdets.dat",ios::binary|ios::in|ios::out);
				f6.seekg(0,ios::beg);
				while(!f6.eof())
				{
					f6.read((char*) &t6,sizeof(t6));
					if(t6.acctno==t06.get_acctno())
					{
						cout<<endl<<"Please enter the time period : ";
						cin>>timeperiod;
						rate=1.5*timeperiod;

						interest=t6.deposit*timeperiod*(rate/100.0);
						cout<<endl<<"Interest is Rs "<<interest;
						amount=t6.deposit + interest;
						cout<<endl<<"Amount is Rs "<<amount;

						if(amount==0)
							cout<<"Sorry!The interest rate for the time period you have entered is not specified";
						j=1;
						break;
					}
				}
				if(j==0)
					cout<<endl<<"Record not found";
				cout<<endl<<endl<<endl<<endl<<"\t\t(Press any key to return to previous menu..)";
				getch();
				break;
			}

			case 5:
				   cout<<endl<<endl<<endl<<endl<<endl<<"\t\tModifications are SAVED to your account..... ";
			       cout<<endl<<endl<<"\t\t\t(Press any key..)";
			       getch();
			       ch2=6;
			       break;
			default:cout<<endl<<endl<<"\t\t\tinvalid entry!!!!";
				cout<<endl<<endl<<endl<<endl<<"\t\t(Press any key to return to previous menu..)";
				getch();
				break;
		}

	}while(ch2<6);

}


int main()
{
	account obj;
	int ch;
	do
	{
		system("cls");
		cout<<endl<<"\t\t\t ==========================";
		cout<<endl<<"\t\t\t\t MAIN MENU";
		cout<<endl<<"\t\t\t ==========================\n";
		cout<<"\t1. Add record\n";
		cout<<"\t2. View record\n";
		cout<<"\t3. Update record / Transactions\n";
		cout<<"\t4. Exit\n";
		cout<<"\tEnter your choice: ";
		cin>>ch;
		system("cls");

		int in=0;

		switch(ch)
		{
			case 1:
				obj.addnewrecord();
				break;
			case 2:
				obj.viewrecord();
				break;
			case 3:
				obj.updaterecord();
				break;
			case 4:
				system("cls");
				cout<<endl<<endl<<endl<<endl<<endl<<"\t\t\t....Terminating....";
				exit(0);
			default:
				cout<<endl<<"\t\t\tinvalid entry!!!!";
				cout<<endl<<endl<<"\t\t\t(Press any key..)";
				getch();
				break;
			}
	}while(ch<10);
	return 0;
}
