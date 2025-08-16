#include <stdio.h>

struct Book
{
    char title[50];
    char author[30];
    float price;
};

void printGreaterPrice(struct Book books[],int size){
  int maxIndex=0;
  for(int i=0;i<size;i++){
    if(books[i].price>books[maxIndex].price){
        maxIndex=i;
    }
     
  }
   printf("\n--- Book with the Highest Price ---\n");
    printf("Title: %s\n", books[maxIndex].title);
    printf("Author: %s\n", books[maxIndex].author);
    printf("Price: %.2f\n", books[maxIndex].price);

}
int main()
{
     char ch;
    struct Book e[3];
    for (int i = 0; i < 3; i++)
    {
        printf("enter the title of the book of %d\n", i + 1);
        scanf(" %49[^\n]", e[i].title);
        printf("enter the author of the book of %d\n", i + 1);
        scanf(" %29[^\n]", e[i].author);
        printf("enter the price of the book of %d\n", i + 1);
        scanf("%f", &e[i].price);

        

    }

    printf("the details are\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Title of Book %d: %s\nAuthor of Book %d: %s\nPrice of Book %d: %f\n",
       i + 1, e[i].title, i + 1, e[i].author, i + 1, e[i].price);
    }


    printGreaterPrice(e,3);
    return 0;
}