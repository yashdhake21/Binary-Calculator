/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4

*/


#include<stdio.h>
#include "numfunc.h"
#include<stdlib.h>
#include<limits.h>

number *addition(number *l1, number *l2) {  /*adds(+) 2 numbers */
	number *result;
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	result = (number *)malloc(sizeof(number));
	init(result);

	if(l1->sign != l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			result = subtraction(l2, l1);
		}
		else if(l2->sign == -1) {
			l2->sign = 1;
			result = subtraction(l1, l2);
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1)
			result->sign = -1;
		else
			result->sign = 1;
		int num = 0, i, j;
		i = l1->len;
		j = l2->len;
		int carry = 0;
		while(i != 0 || j != 0) {
			if(i == 0) {
				num = show(l2, j - 1) + carry;
				j--;
				carry = num / 10;
				num = num % 10;
				insert_beg(result, num);
			}
			else if(j == 0) {
				num = show(l1, i -1) + carry;
				i--;
				carry = num / 10;
				num = num % 10;
				insert_beg(result, num);
			}
			else {
				num = show(l1, i - 1) + show(l2, j - 1) + carry;
				i--;
				j--;
				carry = num / 10;
				num = num % 10;
				insert_beg(result, num);
			}
		}
		if(carry != 0)
			insert_beg(result, carry);
	}
	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	if (result->head == NULL)
        append(result,0);
	return result;
}



void lengthEqual(number *a, number *b) {    /*equalises the length for certain operations*/
	int gap;
	gap = a->len - b->len;
	if(gap > 0) {
		int i = 0;
		while(i < gap) {
			insert_beg(b, 0);
			i++;
		}
	}
	else if(gap < 0) {
		int i = 0;
		gap = -gap;
		while(i < gap) {
			insert_beg(a, 0);
			i++;
		}
	}
}

number *subtraction(number *l1, number *l2) {   /*Performs subtraction operation on adt number*/
	int sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;

	int num;
	int flag = 0;
	number *result;
	result = (number *)malloc(sizeof(number));
	init(result);
	if(l1->sign != l2->sign) {
		if(l2->sign == -1) {
			l2->sign = 1;
			result = addition(l1, l2);
			result->sign = 1;
		}
		if(l1->sign == -1) {
			l1->sign = 1;
			result = addition(l1, l2);
			result->sign = -1;
		}
	}
	else if(l1->sign == l2->sign) {
		if(l1->sign == -1) {
			l1->sign = 1;
			l2->sign = 1;
			result = subtraction(l2, l1);

		}
		else if(l1->sign == 1) {
			if(compare(l1, l2) >= 0) {
				if(flag != 1)
					result->sign = 1;
				else
					result->sign = -1;
				int b = 0;
				int m,n;
				m = l1->len - 1;
				n = l2->len - 1;
				while(m != -1 || n != -1) {
						if(n == -1) {
						num = show(l1, m);
						m--;
						insert_beg(result, num);
					}
					else {
						int a = show(l1, m);
						m--;
						int c = show(l2, n);
						n--;
						if(a >= c) {
							num = a - c;
							insert_beg(result, num);
						}
						else {
							int d = 0;
							while(!(b = remov(l1, m))) {
								m--;
								d++;
							}
							m--;
							m++;
							insert_at(l1, m, b - 1);
							int i;
							for(i = 0; i < d; i++) {
								m++;
								insert_at(l1, m, 9);
							}
							num = 10 + a - c;
							insert_beg(result, num);
						}
					}
				}
			}
			else if(compare(l1, l2) < 0) {
				flag = 1;
				result = subtraction(l2, l1);
				result->sign = -1;
			}
		}
	}
	flag = 0;
	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	if (result->head == NULL)
        append(result,0);
	return result;
}



void make_empty_list(number *newn,int size) {
    int i=0;
    while (i<size){
        insert_beg(newn,0);
        i++;
    }
}



void zeroRemov(number *n){  /*checks and removes extra zero/zeroes in an adt number*/

    node *p = n->head;
    while (p){
        if (p->data == 0){
            p = p->next;
            remov(n,0);
        }
        else{
            break;
        }
    }
}


number* multiplication(number *n1,number *n2){  /*multiplies(*) 2 adt numbers*/
    number *multi;
    multi = (number*)malloc(sizeof(number));
    init(multi);

    int m = n1->len;
    int n = n2->len;

    make_empty_list(multi,m + n+1);

    node *second_ptr = n2->tail,*result_ptr1 = multi->tail, *result_ptr2, *first_ptr;
    while (second_ptr) {

        int carry = 0;

        result_ptr2 = result_ptr1;

        first_ptr = n1->tail;

        while (first_ptr) {

            int mul = first_ptr->data * second_ptr->data + carry;

            result_ptr2->data += mul % 10;

            carry = mul / 10 + result_ptr2->data / 10;
            result_ptr2->data = result_ptr2->data % 10;

            first_ptr = first_ptr->prev;
            result_ptr2 = result_ptr2->prev;
        }

        if (carry > 0) {
            result_ptr2->data += carry;
        }

        result_ptr1 = result_ptr1->prev;
        second_ptr = second_ptr->prev;
    }
    if ((n1->sign == -1 && n2->sign == 1) || (n2->sign == -1 && n1->sign == 1))
        multi->sign = -1;

    zeroRemov(multi);
    if (multi->head == NULL)
        append(m,0);
    return multi;

}


int checkzero(number *l) {  /*checks for zeroes in an adt number*/
	int e, flag = 0;
	node *p = l->head;

	while (p){
        if (p->data != 0)
            flag = 1;
        p = p->next;
	}
	return flag;
}


number *division(number *l1, number *l2) {  /* Performs division operation on 2 adt numbers */
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:dividing by zero");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}

    int num;

	for(int i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l2) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subtraction(temp, l2);
				d++;
				if(compare(temp, l2) < 0)
					break;

			}
			append(result, d);
		}
	}


	l1->sign = sign1;
	l2->sign = sign2;
	zeroRemov(result);
	if (result->head == NULL)
        append(result,0);
	return result;
}


number *modulus(number *l1, number *l2) {   /*Calculates a % b (Remainder)*/
	if(checkzero(l2) == 0) {
		printf("INVALID INPUT:modulo by zero");
		return NULL;
	}
	number *result;
	result = (number *)malloc(sizeof(number));
	number *temp;
	temp = (number *)malloc(sizeof(number));
	init(temp);
	init(result);
	number *l3;
	l3 = (number *)malloc(sizeof(number));
	init(l3);
	copy(l3, l2);
	int m, sign1, sign2;
	sign1 = l1->sign;
	sign2 = l2->sign;
	if(l1->sign == l2->sign) {
		result->sign = 1;
		l1->sign = l2->sign = 1;
	}
	else {
		result->sign = -1;
		l1->sign = l2->sign = 1;
	}

	int a, b;
	m = l1->len;
	int i, j, num;


	for(i = 0; i < l1->len; i++) {
		num = show(l1, i);
		append(temp, num);
		if(compare(temp, l3) < 0) {
			append(result, 0);
		}
		else {
			int d = 0;
			while(1) {
				temp = subtraction(temp, l3);
				d++;
				if(compare(temp, l3) < 0)
					break;

			}
			append(result, d);
		}
	}
	l1->len = m;
	l1->sign = sign1;
	l2->sign = sign2;
	if (temp->head == NULL)
        append(temp,0);
	return temp;
}

number *factorial(number *a) {  /*finds factorial(!) of adt number(represented by linked list)*/

	number *ans = (number *)malloc(sizeof(number));
	init(ans);
	append(ans, 1);
	number *b = (number *)malloc(sizeof(number));
	init(b);
	append(b, 1);
	while(compare(a, b) > 0) {
		ans = multiplication(a, ans);
		a = subtraction(a, b);
	}
	return ans;
}

number *power(number *a, number *b) { /*calculates a ^ b(a to the power b)*/
	number *ans = (number *)malloc(sizeof(number));
	init(ans);
	append(ans, 1);
	number *n1 = (number *)malloc(sizeof(number));
	init(n1);
	append(n1, 1);
	number *n2 = (number *)malloc(sizeof(number));
	init(n2);
	append(n2, 2);
	number *n0 = (number *)malloc(sizeof(number));
	init(n0);
	append(n0, 0);
	number *c = (number *)malloc(sizeof(number));
	init(c);
	copy(c,b);
	int sign = a->sign;
	if(b->sign == 1) {
		while(checkzero(c) != 0) {
			ans = multiplication(ans, a);
			c = subtraction(c, n1);
		}
	}
	else if(b->sign == -1) {
		while(checkzero(c) != 0) {
			ans = division(ans, a);
			c = addition(c, n1);
		}
	}
	a->sign = sign;
	if(a->sign == 1) {
		number *temp;
		temp = modulus(b, n2);
	}
	return ans;
}

void copy(number *n1,number *n2){

    destroy(n1);
    node *p = n2->head;

    while (p){
        append(n1,p->data);
        p = p->next;
    }

    n1->sign = n2->sign;
    return ;

}


int compare(number *a,number *b) {

    if (a->head == NULL)
        return -1;
    if (b->head == NULL)
        return 1;

    zeroRemov(a);
    zeroRemov(b);

    if (a->head == NULL)
        append(a,0);
    if (b->head == NULL)
        append(b, 0);


    int lenA = a->len;
    int lenB = b->len;

    if (lenA > lenB) {

        return 1;
    }
    else if (lenB > lenA) {
        return -1;
    }


    node *p = a->head;
    node *q = b->head;
    while (p != NULL && q != NULL) {
        if (p->data > q->data)
            return 1;
        else if (p->data < q->data)
            return -1;


        p = p->next;
        q = q->next;
    }


    return 0;
}



