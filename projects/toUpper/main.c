#include <stdio.h>
#include <stdlib.h>


char toUpper(char letter){

    if(letter >= 'a' && letter <= 'z'){
        return letter - 'a' + 'A';
    }
    else{
        return -1;
    }
}

int main()
{
    char inputLetter;
    printf("Enter a letter to make it uppercase: \n");
    scanf("%c", &inputLetter);
    char upperedLetter = toUpper(inputLetter);
    printf("Result: %c",upperedLetter);
    return 0;
}
