#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string.h>
#include <string>
#include "filework.h"

using namespace std;

typedef Doc data;

data shell;

void print_manual();
bool main_func(char);
void search_record_author();
void search_record_type();
void add_record();
void remove_record();
void update_record();
int search_isbn(int,book_record *);


int main()
{
	shell.open_new();
	bool finish = false;
	char input;
	while (1)
	{
		print_manual();
		cin >> input;
		finish = main_func(input);
	}
	shell.close();
	return finish;
}

void print_manual()
{
	cout << endl << endl;
	cout << "Please select the operation to perform and enter the operation code" << endl;
	cout << "(P) Print the whole catalogue," << endl;
	cout << "(A) Search the catalogue by author name," << endl;
	cout << "(T) Search the catalogue by book type," << endl;
	cout << "(I) Insert a new book record," << endl;
	cout << "(U) Update an existing book record," << endl;
	cout << "(R) Remove a book record," << endl;
	cout << "(E) Exit the program." << endl;
	cout << endl;
	cout << "Your selection is: "<<endl;
}

bool main_func(char input)
{
	bool end = false;
	switch (input)
	{
	case 'P': case 'p':
		shell.print_catalogue();
		break;
	case 'A': case 'a':
		shell.search_author();
		break;
	case 'I': case 'i':
		add_record();
		break;
	case 'T': case 't':
		shell.search_type();
		break;
	case 'U': case 'u':
		update_record();
		break;
	case 'R': case 'r':
		remove_record();
		break;
	case 'E': case 'e':
	    exit(1);
		end = true;
		break;

	default:
		cout << "Error: You have made an invalid choice" << endl;
		cout << "Try again {P,A,T,I,U,R,E}";
		cin >> input;
		end = main_func(input);
		break;

	}
	return end;
}

void Doc::search_author()
{
	char arr[20];
	int x=0;
	cout << "Please enter the author name to search: " << endl;
	cin.ignore(20,'\n');
	cin.getline(arr, 20);                                            /*taken author name*/

	book_record lib;

	fseek(library_record, 0, SEEK_SET);                                    /*set file pointer the beginning of file*/
    fread(&lib, sizeof(book_record), 1, library_record);
	while (!feof(library_record))                                           /*reading book_record's from file while not end of file*/
	{
		if (strcmp(lib.authorName, arr) == 0)                                   /*compare the record names and taken name if it is same print it*/
		{
		    cout<<"####################################"<<endl;
			cout <<"Author name: " << lib.authorName << endl;
			cout <<"Author surname: " << lib.authorSurname << endl;
			cout <<"Title: " << lib.title << endl;
			cout <<"Book type: " << lib.bookType << endl;
			cout <<"ISBN: " << lib.ISBN << endl;
			cout <<"Location: " << lib.location << endl;
			cout<<"####################################"<<endl;
			cout<<endl;
			x++;
		}
		fread(&lib, sizeof(book_record), 1, library_record);
	}
	if(feof(library_record) && x==0)
        cout<<"The entered author name is not matching any author name in the catalogue!"<<endl;   /*if there is no match print this*/
}

void Doc::search_type()
{
    char arr[20];
    int x;
	cout << "Please enter the book type to search: " << endl;                        /*it has same logic search_author() function*/
	cin.ignore(20,'\n');
	cin.getline(arr, 20);

	book_record lib;

	fseek(library_record, 0, SEEK_SET);
    fread(&lib, sizeof(book_record), 1, library_record);
	while (!feof(library_record))
	{
		if (strcmp(lib.bookType, arr) == 0)
		{
		    cout<<"####################################"<<endl;
			cout << "Author name: " << lib.authorName << endl;
			cout << "Author surname: " << lib.authorSurname << endl;
			cout << "Title: " << lib.title << endl;
			cout << "Book type: " << lib.bookType << endl;
			cout << "ISBN: " << lib.ISBN << endl;
			cout << "Location: " << lib.location << endl;
			cout<<"####################################"<<endl;
			cout<<endl;
			x++;
		}
		fread(&lib, sizeof(book_record), 1, library_record);
	}
	if(feof(library_record) && x==0)
        cout<<"The entered book type is not matching any book type in the catalogue!"<<endl;
}


void add_record()
{
	book_record new_book;
	cout << "Please enter the new book's info" << endl;
	cout << "ISBN(International Standart Book Number) : ";
	cin >> new_book.ISBN;
    cout << "Author name : ";
	cin.ignore(1000,'\n');
	cin.getline(new_book.authorName,20);
	cout << "Author surname : ";
	cin.getline(new_book.authorSurname,20);
	cout << "Book type : ";
	cin.getline(new_book.bookType,10);
	cout << "Title : ";
	cin.getline(new_book.title,10);
	cout << "Location : ";
	cin >> new_book.location;

	shell.add(&new_book);                                               /*adds new record to file*/
	getchar();
	cout << "************************************************" << endl;
	cout << "***New book has been added on library records***" << endl;
    cout << "************************************************" << endl;


	getchar();
}

void remove_record()
{
	int nbsi;
	cout << "Enter the ISBN of the book to remove from catalogue: " << endl;
	cin >> nbsi;                                                                                /*takes ISBN to use in del() method*/
	shell.del(nbsi);
	cout <<"************************************************"<< endl;
	cout << nbsi << " numbered record has been removed from catalogue." << endl;
	cout <<"************************************************"<< endl;
}

void update_record()
{
    int num,nbsi;
    book_record new_record;
    cout << "Enter the ISBN of the book to update info: " << endl;
	cin >> nbsi;
	num=shell.search_isbn(nbsi);                                /*searches to taken ISBN in catalogue if the return value is 0 prints not found*/
	if(num==0)
    {
        cout<<"The record could not be found please try another isbn!!"<<endl;
    }
    else
    {
        cout<<"Please enter the information to update old one"<<endl;
        cout << "ISBN(International Standart Book Number) : ";
        cin >> new_record.ISBN;
        cout << "\nAuthor name : ";
        cin.ignore(1000,'\n');
        cin.getline(new_record.authorName, 20);
        cout << "Author surname : ";
        cin.getline(new_record.authorSurname, 20);
        cout << "Book type : ";
        cin.getline(new_record.bookType, 10);
        cout << "Title : ";
        cin.getline(new_record.title, 20);
        cout << "Location : ";
        cin >> new_record.location;
        shell.update(num,&new_record);                                                      /*updates the old record*/
        cout << "************************************************" << endl;
        cout << "***Book record has been updated successfully ***" << endl;
        cout << "************************************************" << endl;
    }
}

