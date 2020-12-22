/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/

#include <stdio.h>
#include <stdlib.h>
#include "adtnum.h"

int main(){
    char s[1000];
    printf("******************************************** Arbitrary Precision Calculator ******************************************** \n ");
    printf("Operations available :- \n");
    printf(" 1. Addition(+) \n");
    printf(" 2. Subtraction(-) \n");
    printf(" 3. Multiplication(*) \n");
    printf(" 4. Division(/) \n");
    printf(" 5. Modulus \n");
    printf(" 6. Factorial(!) \n");
    printf(" 7. Power(^) \n");
    printf("\n");
    printf("************************************************************************************************************************");
    printf("\n");
    printf("Enter expression : \n");
    number *result;
    result = (number*)malloc(sizeof(number));
    init(result);

    gets(s);
    printf("Result = ");
    result = infix(s);
    traverse(result);

}

