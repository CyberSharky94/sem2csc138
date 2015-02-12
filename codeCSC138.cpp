//Created by:													|
//-Muhammad Shakirin Bin Samin (2012603436)						|
//-Faizal Bin Ismail (2011826722)								|
//																| 
//This program is about Online Book Store Buy & Sell            |
//---------------------------------------------------------------

//all library used in this program
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//********************************************************************************************
//This struct store Books record
//********************************************************************************************
struct BookStore
{
	char title[50];
	char synopsis[2000];
	double price;
};

//********************************************************************************************
//This struct store books added to cart record
//********************************************************************************************
struct addCartData
{
	int rowNumber[10];
	int columnNumber[10];
	int column;
	int row;
};

//********************************************************************************************
//This struct store payment calculation record
//********************************************************************************************
struct paymentCalc
{
	double totalPrice;
};
paymentCalc pay;

//********************************************************************************************
//This struct store user information record
//********************************************************************************************
struct userData
{
	char name[100];
	char email[100];
	char address[300];
	char phone[12];
	int method;
};
userData acc;


void outputSynopsis(string s); //prototype
int GetBufferWidth(); //prototype
void readData(BookStore book[][5]); //prototype
void viewList (BookStore book[][5], addCartData& cart, int& cartFlag); //prototype
void displayBook (BookStore book[][5], int row, int column); //prototype
void addCart(BookStore book[][5], addCartData& cart, int row, int column, int cartFlag); //prototype
void confirm(BookStore book[][5], addCartData& cart); //prototype
void payment(BookStore book[][5], addCartData& cart); //prototype
void printReceipt(BookStore book[][5], addCartData& cart); //prototype

//********************************************************************************************
//This is main of the program
//********************************************************************************************
void main()
{
	BookStore book[2][5]; //declare struct variable for BookStore
	addCartData cart; //declare struct variable for addCartData
	cart.column=0;
	cart.row=0;
	int cartFlag=0; //as flag if cart is used or not, 1-Use, 0-Not in use

	//reading data from booklist.txt
	cout << "Loading Book Record... ";
	readData(book);
	cout << "Load Completed.\n\n";

	//Menu will be shown and user will be given choices.
	int choice=0;
	while(choice!=2)
	{
		system("cls");
		cout << "--------------------------------------------------------------------------------\n";
		cout << "\t         " << "Welcome to Islamic Resources Online Bookstore\n";
		cout << "--------------------------------------------------------------------------------\n";
		cout << " Created by: Muhammad Shakirin Samin & Faizal Ismail\n\n";


		cout << " Please Choose Menu:\n";
		cout << " 1. View List of Books\n";
		cout << " 2. Exit Application\n\n";


		cout << " Enter Your Choice Code (1/2): ";
		cin >> choice;

		if(choice==1)
			viewList (book, cart, cartFlag);
	}
	system("cls"); //clear screen
	cout << " Exiting from application...\n\n";
	exit(1);
}

//This function read data from booklist.txt
//then, store it in Struct BookStore book.
void readData(BookStore book[][5])
{
	int i=0, j=0;
	ifstream infile;
	infile.open("booklist.txt", ifstream::in);
	if(infile.is_open() && i==0 && j==0)
	{
		while(infile.good())
		{
			infile.getline(book[i][j].title,50, '*');
			infile.getline(book[i][j].synopsis,2000,'*');
			infile.ignore(1, '\n');
			infile >> book[i][j].price;
			infile.ignore(2, '\n\n');
			j++;
			if(j==5 && i==0)
			{
				j=0;
				i=1;
			}
			
		}
	}
	else
	{
		cout << "error opening file\n";
		exit(-1);
	}
	infile.close();
}

//This function will view list of books available in record.
void viewList (BookStore book[][5], addCartData& cart, int& cartFlag)
{
	system("cls");

	int aCart;
	
	int choice; 
	int i=0;
	int row=0, column=0;
	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t         " << "Welcome to Islamic Resources Online Bookstore\n";
	cout << "--------------------------------------------------------------------------------\n\n";

	cout << " List of Books Available in Our Bookstore:\n";
	cout << " 1. Learning Without Stress\n";
	cout << " 2. Imam Hanafi\n";
	cout << " 3. Imam Maliki\n";
	cout << " 4. Imam Syafie\n";
	cout << " 5. Imam Hanbali\n";
	cout << " 6. Life is Beautiful with Syariah\n";
	cout << " 7. Can I Have Couple?\n";
	cout << " 8. End Times People Compass\n";
	cout << " 9. I'm A Muslim\n";
	cout << " 10. 60 Tips on Travelling\n\n";
	cout << " 0. Return to Main Menu\n";
	cout << endl;

	if(cartFlag!=1)
	{
		cout << " Enter Your Choice Code (0-10): ";
	}

	else if(cartFlag==1)
	{
		cout << " 11. Make Payment!\n\n";
		cout << " Enter Your Choice Code (0-11): ";
	}

	cin >> choice;

	system("cls");

	if(choice!=0 && choice != 11)
	{
		if(choice<=5 && choice!=0)
		{
			column=choice-1;
			row=0;
			displayBook(book, row, column);
		}
	
		else if(choice>=6 && choice<=10)
		{
			column=choice-6;
			row=1;
			displayBook(book, row, column);
		}

		cout << endl;
		
		cout << " Next Option:\n";
		cout << " 1. Buy Now!\n";
		cout << " 2. Return to List of Books\n";
		cout << " 3. Exit from Application\n\n";
		cout << " Enter Choice Code (1-3): ";
		cin >> aCart;

		if(aCart==1)
		{
			cartFlag=1;
			addCart(book, cart, row, column, cartFlag);
		}

		else if(aCart==2)
		{
			viewList(book,cart,cartFlag);
		}

		else if(aCart==3)
		{
			cout << " Exit from Application...\n\n";
			exit(1);
		}
	}

	else if(choice==11)
	{
		confirm(book, cart);
	}

}

//This function will display detail about books chosen by user.
void displayBook (BookStore book[][5], int row, int column)
{
	system("cls");
	cin.ignore();

	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t         " << "Welcome to Islamic Resources Online Bookstore\n";
	cout << "--------------------------------------------------------------------------------\n\n";
	
	cout << fixed << setprecision(2);
	cout << "Title: " << book[row][column].title << endl;
	cout << "Price: RM" << book[row][column].price << endl;
	cout << "Synopsis: \n"; 
	outputSynopsis(book[row][column].synopsis);
	cout << endl;
}

//This function will add book data to cart if user agree to buy it.
void addCart(BookStore book[][5], addCartData& cart, int row, int column, int cartFlag)
{
	cin.ignore();

	if (row==0 && cart.column<5)
	{
		cart.rowNumber[cart.row]=row;
		cart.columnNumber[cart.column]=column;
	}
	else if(row==1 && cart.column<10)
	{
		cart.rowNumber[cart.row]=row;
		cart.columnNumber[cart.column]=column;
	}
	cart.row++;
	cart.column++;


	cout << " Book Added to Cart!\n\n";

	cin.ignore();

	viewList (book, cart, cartFlag);
}

//This function will request for user confirmation in buying books.
void confirm(BookStore book[][5], addCartData& cart)
{
	system("cls");
	cin.ignore();

	int takeColumn=0;
	int takeRow=0;
	int countCol=0;
	int countRow=0;
	int choice;

	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t         " << "Welcome to Islamic Resources Online Bookstore\n";
	cout << "--------------------------------------------------------------------------------\n\n";

	cout << "List of Books in Cart:\n";
	
	for(int i=0; i<2; i++)
	{
		for(int line=0; line<4 && countRow<cart.row && countCol<cart.column; line++)
		{
			takeColumn = cart.columnNumber[countCol];
			takeRow = cart.rowNumber[countRow];
			cout << countCol+1 << ". " << book[takeRow][takeColumn].title << " (RM" << book[takeRow][takeColumn].price << ")" << endl;
			
			pay.totalPrice = pay.totalPrice + book[takeRow][takeColumn].price;

			countRow++;
			countCol++;
		}
	}
	cout << endl;
	cout << "Total Amount: RM" << pay.totalPrice << endl << endl;

	cout << "Next Option:\n";
	cout << "1. Proceed with Payment\n";
	cout << "2. Cancel Purchase and Exit Application\n\n";

	cout << "Enter Your Choice Code (1/2): ";
	cin >> choice;

	if(choice==1)
		payment(book, cart);

	else if(choice==2)
	{
		cout << "Your Purchase Has Been Canceled...\n";
		cout << "Exiting from Appliaction...\n\n";
		exit(1);
	}
}

//This function will request user to enter details required for payment purpose.
void payment(BookStore book[][5], addCartData& cart)
{
	system("cls");
	cin.ignore();

	cout << "--------------------------------------------------------------------------------\n";
	cout << "\t         " << "Welcome to Islamic Resources Online Bookstore\n";
	cout << "--------------------------------------------------------------------------------\n\n";

	cout << "Please Enter Your Information:\n";

	cout << "Name: ";
	cin.getline(acc.name, 100);

	cout << "E-Mail: ";
	cin.getline(acc.email, 100);

	cout << "Phone Number: ";
	cin.getline(acc.phone, 12);
	cout << endl;

	cout << "Choose Delivery Method:\n";
	cout << "1. Self Collect\n";
	cout << "2. Post (+RM10.00)\n\n";

	cout << "Enter Your Choice Code (1/2):";
	cin >> acc.method;
	cin.ignore();
	cout << endl;

	if(acc.method==2)
	{
		pay.totalPrice = pay.totalPrice+10;
		cout << "Please Enter Your Address:\n";
		cin.getline(acc.address, 300);
	}
	cout << endl;

	printReceipt(book, cart);
}

//This function will store receipt data into a file named OrderReceipt.txt
void printReceipt(BookStore book[][5], addCartData& cart)
{
	system("cls");

	int takeColumn=0;
	int takeRow=0;
	int countCol=0;
	int countRow=0;

	ofstream outfile;
	outfile.open("OrderReceipt.txt", ofstream::out);
	outfile << fixed << setprecision(2);

	
	
	outfile << "============================================================\n";
	outfile << "	                  Purchase Receipt\n";
	outfile << "              Islamic Resources Online Bookstore\n";
	outfile << "============================================================\n";
	outfile << "Buyer: " << acc.name << endl;
	outfile << "Phone Number: " << acc.phone << endl;
	outfile << "E-Maill: " << acc.email << endl;
	outfile << "Address: " << acc.address << endl << endl;

	if(acc.method==1)
		outfile << "Delivery Method: Self Collect\n\n";
	else if(acc.method==2)
		outfile << "Delivery Method: Post (+RM10.00)\n\n";

	outfile << "Purchased Item:\n";

	for(int i=0; i<2; i++)
	{	
		for(int line=0; line<4 && countRow<cart.row && countCol<cart.column; line++)
		{
			takeColumn = cart.columnNumber[countCol];
			takeRow = cart.rowNumber[countRow];
			outfile << book[takeRow][takeColumn].title << " (RM" << book[takeRow][takeColumn].price << ")" << endl;
		
			countRow++;
			countCol++;
		}
	}
	outfile << endl;
	outfile << "Total Amount: RM" << pay.totalPrice << endl << endl;

	outfile << "------------------------------------------------------------\n";
	outfile << "	  Please Complete Your Payment Within 1 Week.\n";
	outfile << " Send Proof of Payment at: 'mail@islamicresource.com.my'\n";
	outfile << "  We'll Contact You Soon Once Payment Has Been Verified.\n";
	outfile << "------------------------------------------------------------\n";
	outfile << "                       THANK YOU!\n";


	outfile.close();

	cout << "Your Receipt Saved. Ready To Be Printed!\n";
	cout << "Program Exiting...!\n";
	exit(1);
}

//********************************************************************************************
//This is for Word Warp Output Purpose...
//********************************************************************************************
int GetBufferWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	int bufferWidth, result;

	result = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&bufferInfo);

	if(result)
	{
		bufferWidth = bufferInfo.dwSize.X;
	}

	return bufferWidth;
}

void outputSynopsis(string s)
{
	int bufferWidth = GetBufferWidth();

	for (unsigned int i = 1; i <= s.length() ; i++)
	{
		char c = s[i-1];

		int spaceCount = 0;

		// Add whitespace if newline detected.
		if (c == '\n')
		{
			int charNumOnLine = ((i) % bufferWidth);
			spaceCount = bufferWidth - charNumOnLine;
			s.insert((i-1), (spaceCount), ' ');			//insert space before newline break
			i+=(spaceCount);							//jump forward in string to character at beginning of next line
			continue;
		}

		if ((i % bufferWidth) == 0)
		{
			if (c != ' ')
			{
				for (int j = (i-1); j > -1 ; j--)
				{
					if (s[j] == ' ')
					{
							s.insert(j, spaceCount, ' ');
							break;						
					}
					else spaceCount++;
				}
			}
		}
	}

	cout << s << endl;
	// Output string to console
}
//********************************************************************************************
