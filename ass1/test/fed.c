#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <limits.h>

struct Books {
	int book_id;
	char title[50];
	char author[50];
	char subject[100];
};

void printBook( struct Books book ) {
  	printf("Book book_id : %d\n", book.book_id);
   	printf("Book title : %s\n", book.title);
   	printf("Book author : %s\n", book.author);
   	printf("Book subject : %s\n", book.subject);
}

void printBook2( struct Books *book ) {
   	printf("Book book_id : %d\n", book->book_id);
   	printf("Book title : %s\n", book->title);
   	printf("Book author : %s\n", book->author);
   	printf("Book subject : %s\n", book->subject);
}

int main(void)
{
	struct Books book1;

	book1.book_id = 6495407;
	strcpy(book1.title, "C Programming");
	strcpy(book1.author, "Nuha Ali"); 
	strcpy(book1.subject, "C Programming Tutorial");

	printBook(book1);
	printf("\n\n");
	printBook2(&book1);

	strcpy(book1.author, "Federick Kwok"); 

	printf("\n\n");
	printBook2(&book1);

	/* asdfadf */

	return 0;
}
