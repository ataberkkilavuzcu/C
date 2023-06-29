#include <stdio.h>
#include <stdlib.h>


char toLower(char letter){

    if('A' <= letter && letter <= 'Z'){
        return letter - 'A' + 'a';
    }
    else{
        return -1;
    }
}

int main()
{
    char upperCasedLetter;
    printf("Enter uppercase letter to make it lowercase: \n");
    scanf("%c",&upperCasedLetter);
    char loweredLetter = toLower(upperCasedLetter);
    printf("Result: %c",loweredLetter);
    return 0;
}
