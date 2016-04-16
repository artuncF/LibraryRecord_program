/**
 *Furkan Artunç
 */
#ifndef DOSYAISLEMLERI_H
#define DOSYAISLEMLERI_H

#include <stdio.h>
#include "book_record.h"
#include <string.h>

struct Doc
{
	FILE* library_record;
	void open_new();
	void close();
	void print_catalogue();
	void add(book_record *);
	void search_author();
	void search_type();
	int search_isbn(int);
    void del(int);
	void update(int,book_record*);
};
#endif
