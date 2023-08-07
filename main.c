#include<stdio.h>
#include"mymalloc.c"

int main(){
    int *a=(int*)Mymalloc(100*sizeof(int));
        printf("Pointer a address is = %d\n\n",&a);

    char *b=(char*)Mymalloc(250*sizeof(char));
        printf("Pointer b address is = %d\n\n",&b);    

    int *c=(int*)Mymalloc(1000*sizeof(int));
        printf("Pointer c address is = %d\n\n",&c);     

    MyFree(a);
    
    MyFree(b);

    char *d=(char*)Mymalloc(700);
        printf("Pointer d address is = %d\n\n",&d);

    MyFree(d);

    int *e=(int*)Mymalloc(500*sizeof(int));
        printf("Pointer e address is = %d\n\n",&e);

    MyFree(e);
}