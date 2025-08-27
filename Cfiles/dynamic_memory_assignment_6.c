#include <stdio.h>
#include <stdlib.h>
int main()
{

   int n, r;
   int *ptr;
   printf("enter the n");
   scanf("%d", &n);
   ptr = (int *)malloc(n * sizeof(int));
   if (ptr == NULL)
   {
      printf("memory allocation failed");
      return 1;
   }

   for (int i = 0; i < n; i++)
   {
      printf("enter the element%d\n", i);
      scanf("%d", ptr + i);
   }

   char choice;
   int more;
   printf("\nDo you want to add more elements? (y/n): ");
   scanf(" %c", &choice); // Note the space before %c to consume newline

   if (choice == 'y' || choice == 'Y')
   {
      printf("How many more elements? ");
      scanf("%d", &more);

      // 🔹 Reallocate memory
      int *temp = realloc(ptr, (n + more) * sizeof(int));
      if (temp == NULL)
      {
         printf("Reallocation failed\n");
         free(ptr); // Free original memory
         return 1;
      }
      ptr = temp;

      // 🔹 Input new elements
      for (int i = n; i < n + more; i++)
      {
         printf("Enter element %d: ", i);
         scanf("%d", ptr + i);
      }

      n += more; // Update total count
   }

   for (int i = 0; i < n; i++)
   {
      printf("elements of index %d is %d\n", i, *(ptr + i));
   }

   free(ptr);
   //  printf("%f",*ptr);

   // calloc
   int *ctr;
   printf("enter the element for calloc");
   scanf("%d,", &r);
   ctr = calloc(r, sizeof(int));

   if (ctr == NULL)
   {
      printf("memory allocation failed");
      return 1;
   }

   for (int i = 0; i < r; i++)
   {
      printf("enter the element%d\n", i);
      scanf("%d", ctr + i);
   }

   for (int i = 0; i < r; i++)
   {
      printf("elements of index %d is %d\n", i, *(ctr + i));
   }

   free(ctr);

   return 0;
}