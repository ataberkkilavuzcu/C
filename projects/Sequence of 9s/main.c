#include <stdio.h>
#include <stdlib.h>


int nineNumber(int length){
    int i;
    int num = 0;

    for(i = 0; i < length; i++){
        num = num * 10 + 9;
    }
    return num;
}

int main()
{
    int lengthSeq;
    printf("Enter length for nth sequence of 9s: \n");
    scanf("%d",&lengthSeq);
    int number = nineNumber(lengthSeq);
    printf("Your number: %d",number);
    return 0;
}
