/**
  *Furkan Artunç
  */
#include "filework.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

void Doc::add(book_record *ptr)                               /*pointer goes to end of file then new record will be added there*/
{
	fseek(library_record, 0, SEEK_END);
	fwrite(ptr, sizeof(book_record), 1, library_record);
}

void Doc::open_new()                                            /*opens a file for both reading and writing*/
{
        if(!(library_record = fopen("library.txt", "w+")))
        {
                cerr << "File can not be opened" << endl;
                exit(1);
        }
}

void Doc::close()
{
	fclose(library_record);                           /*close the file*/
}



int Doc::search_isbn(int x)
{
    int counter=0;
    book_record lib;
	fseek(library_record, 0, SEEK_SET);
	while (!feof(library_record))
	{
		fread(&lib, sizeof(book_record), 1, library_record);        /*while not end of file take records and compare the isbn and parameter x(ISBN) if they are equal iterate the counter*/
		if (lib.ISBN == x)
		{
			counter++;
		}
	}
	return counter;
}

void Doc::update(int num,book_record* ptr)                              /*manipulate the pointer to go num's record*/
{
    if (fseek(library_record, sizeof(book_record)*(num-1), SEEK_SET) == 0)
	{
		fwrite(ptr, sizeof(book_record), 1, library_record);          /*write the parameter book_record to the file*/
	}
}

void Doc::del(int num)
{
    book_record dummy;
    FILE* dum;
    dum=fopen("tempfile.txt","w+");                                         /*open a temp file to write contents of first file*/
    if(dum==NULL)
    {
        cerr<<"File could not be opened!!"<<endl;
        exit(1);
    }
    fseek(library_record,0,SEEK_SET);
    fseek(dum,0,SEEK_SET);                                          /*set the pointers beginning of the files*/
    fread(&dummy,sizeof(book_record),1,library_record);
    while(!feof(library_record))
    {
        if(dummy.ISBN!=num)
        {
        fwrite(&dummy,sizeof(book_record),1,dum);                   /*write the not matching ISBN contents from first file to temp file*/
        }
        fread(&dummy,sizeof(book_record),1,library_record);
    }

    fclose(library_record);               /*close the first file to make it empty*/
    open_new();                             /*open the first file */

    fseek(library_record,0,SEEK_SET);
    fseek(dum,0,SEEK_SET);

    fread(&dummy,sizeof(book_record),1,dum);

    while(!feof(dum))                                               /*while not end of temp file write records the first file*/
        {
        fwrite(&dummy,sizeof(book_record),1,library_record);
        fread(&dummy,sizeof(book_record),1,dum);
        }

    fclose(dum);                                             /*close the temp file*/
}

void Doc::print_catalogue()
{
    book_record newbee;

    fseek(library_record,0,SEEK_END);                    /*set the pointer end of file to use in ftell()*/
    if(ftell(library_record)==0)
        {                                                  /*this block enable me to understand whether file is empty or not*/

            cout<<"********************************************"<<endl;
            cout<<"***      There is no record found !      ***"<<endl;
            cout<<"********************************************"<<endl;
        }

    else
    {
    fseek(library_record,0,SEEK_SET);
    fread(&newbee,sizeof(book_record),1,library_record);
    while(!feof(library_record))
    {
        cout<<"####################################"<<endl;
        cout <<"Author name: " << newbee.authorName << endl;
        cout <<"Author surname: " << newbee.authorSurname << endl;          /*print whole records in the file*/
        cout <<"Title: " << newbee.title << endl;
        cout <<"Book type: " << newbee.bookType << endl;
        cout <<"ISBN: " << newbee.ISBN << endl;
        cout <<"Location: " << newbee.location << endl;
        cout<<"####################################"<<endl;
        cout<<endl;
        fread(&newbee,sizeof(book_record),1,library_record);
    }
    cout<<"*************************************************"<<endl;
    cout<<"*** The whole catalogue has just shown above! ***"<<endl;
    cout<<"*************************************************"<<endl;
    }
}














