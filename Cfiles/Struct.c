
#include <stdio.h>

struct Employee
{
    char name[32];
    int id;
    float salary;
};


void increment(struct Employee e,float percentage){
  
   float percent =( e.salary*percentage)/100;
    e.salary = e.salary+ percent;
    printf("the salary is %f\n",e.salary);

}
int main()
{
   int i,ch;


   

    struct Employee p = {"Nivya", 102, 5000000};
    // struct Employee g;
    // printf("enter the name\n");
    //  scanf("%31[^\n]", g.name); // ✔️ Correct  to avoid the space
    // printf("enter the id \n");
    // scanf("%d", &g.id);

    // printf("enter the salary \n");
    // scanf("%f", &g.salary);



   struct Employee  e[5];
    
   for (int i=0;i<5;i++){
    printf("enter the name %d\n",i+1);
     scanf(" %31[^\n]", e[i].name);// ✔️ Correct  to avoid the space
    printf("enter the id %d\n",i+1);
    scanf("%d", &e[i].id);

    printf("enter the salary %d\n",i+1);
    scanf("%f", &e[i].salary);

//     while(ch==getchar()!='\n'&&ch!=EOF){
    
//    }

   }

   

   for (int i = 0; i < 5; i++) {
    printf("Name = %s\n Id:%d\n Salary=%.2f\n", e[i].name, e[i].id, e[i].salary);
   }

   printf("the function is ");
    increment(p,10.0);
  
    //printf("Name %d= %s\n Id %d:%d\n Salary %d=%.2f\n", i+1,i+1,i+1 g.name, g.id, g.salary);
    return 0;
}