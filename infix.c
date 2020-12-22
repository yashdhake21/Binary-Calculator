/*
Name : Yash Pradeep Dhake
MIS : 111903160
Division : 2
Batch : S-4
*/

#include <stdio.h>
#include "numstack.h"
#include "opstack.h"
int precedance(char o) {
	switch(o) {

		case ')' :
			return 0;
			break;
		case '+' :
        case '-' :
			return 1;
			break;
		case '*' :
		case '/' :
			return 2;
			break;
		case '%' :
			return 3;
			break;
		case '(' :
			return 4;
			break;
		default :
			return 5;
			break;
	}
	return 5;
}

#define OPERAND	50
#define OPERATOR 100
#define END	200
#define ERR 300

typedef struct token{
	int type;
	number *num;
	char op;
}token;
enum state { NUMBER, DOT, OP, FINISH, ERROR, SPC };


token gettoken(char *expr, int *reset) {
    static int i=0;
	number *a = (number *)malloc(sizeof(number));
	init(a);
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;
	if(*reset == 1) {
		currstate = SPC;
		*reset = 0;
		i = 0;

	}
	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						append(a, (int)currchar-'0');
						i++;
						break;
					case '+': case '-': case '*': case '/': case '^': case '%': case '!': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						i++;
						return t;
						break;


					default:
						nextstate = ERROR;
						t.type = OPERAND;
						t.num = a;
						currstate = nextstate;
						return t;
						break;
				}
				break;



			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						t.type = OPERAND;

						nextstate = NUMBER;
						currstate = nextstate;
						if (expr[i-1] == '-')
                            a->sign = -1;
                        append(a,(int)currchar - '0');
						i++;

						break;
                    case '+': case '-': case '*': case '/': case '^': case '%': case '!': case '(' : case ')' :
						nextstate = OP;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					default:
						nextstate = ERROR;
						t.type = OPERATOR;
						t.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						append(a, (int) currchar-'0');
						nextstate = NUMBER;
						i++;
						break;
                    case '+': case '-': case '*': case '/': case '^': case '%': case '!': case '(' : case ')' :
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;

					default:
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}


number *infix(char *exp) {
	token t;
	char curr_op, prev_op, ch;
	int setpow = 0,
	cnt_ob = 0, cnt_cb = 0, reset  = 1, curr, prev;
	number *a, *b, *z;
	a = (number *)malloc(sizeof(number));
	b = (number *)malloc(sizeof(number));
	z = (number *)malloc(sizeof(number));
	init(a);
	init(b);
	init(z);
	istack is;
	cstack cs;
	iinit(&is);
	cinit(&cs);
	prev = ERR;
	while(1) {
		t = gettoken(exp, &reset);
		curr = t.type;
		if(curr == prev && prev == OPERAND) {
			return NULL;
		}
		if(t.type == OPERAND){
			ipush(&is, t.num);
		}
		else if(t.type == OPERATOR){
			curr_op = t.op;
			if(curr_op == '(')
				cnt_ob++;
			if(curr_op == ')')
				cnt_cb++;
			if(cnt_cb > cnt_ob)
				return NULL;
			if(!cisempty(&cs)) {
				prev_op = ctop(&cs);

				while(precedance(prev_op) >= precedance(curr_op)) {
					prev_op = cpop(&cs);
					if(!iisempty(&is)) {
						a = ipop(&is);
					}
					else{
						cpush(&cs, prev_op);
						break;
					}
					if(!iisempty(&is)) {
						b = ipop(&is);
					}
					else {
						cpush(&cs, prev_op);
						ipush(&is, a);
						break;
					}
					if((prev_op == '/' || prev_op == '%') && a == 0) {
                        printf("Mathematical error\n");
                        return NULL;
                    }
					switch (prev_op) {
						case '+' :
							z = addition(a, b);
							ipush(&is, z);
							break;
						case '-' :
							z = subtraction(b, a);
							ipush(&is, z);
							break;
						case '*' :
							z = multiplication(b, a);
							ipush(&is, z);
							break;
						case '/' :
							z = division(b, a);
							ipush(&is, z);
							break;
                        case '%' :
							z = modulus(b, a);
							ipush(&is, z);
							break;
                        case '^':
							setpow = 1;
							break;
						case '!':
							a = ipop(&is);
							if(a->sign == -1)
								return NULL;
							else {
                                z = factorial(a);
								ipush(&is, z);

							}
							break;
						case '(' :
							cpush(&cs, prev_op);
							ipush(&is, b);
							ipush(&is, a);
							break;
						default :
							return NULL;
					}
					if (prev_op == '(')
						break;
					if(!cisempty(&cs))
						prev_op = ctop(&cs);
					else
						break;
				}
			}
			cpush(&cs, t.op);
			if(curr_op == ')') {
				ch = cpop(&cs);
				cnt_cb--;
				ch = cpop(&cs);
				cnt_ob--;
			}
		}
		else if(t.type == END) {
			if(cnt_ob == cnt_cb) {
				while(!cisempty(&cs)) {
					if(!iisempty(&is)) {
						a = ipop(&is);
					}
					else {
						printf("Less operands\n");
                        return NULL;
					}
					if(!iisempty(&is)) {
						b = ipop(&is);
					}
					else {
                        z = factorial(a);
                        return z;
						printf("Less operands\n");
                        return NULL;
					}
					ch = cpop(&cs);
					if((ch == '/' || ch == '%') && a == 0) {
						printf("Mathematical error\n");
						return NULL;
					}
					switch(ch) {
						case '+' :
							z = addition(b, a);
							ipush(&is, z);
							break;
						case '-' :
							z = subtraction(b, a);
							ipush(&is, z);
							break;
						case '*' :
							z = multiplication(b, a);
							ipush(&is, z);
							break;
						case '/' :
							z = division(b, a);
							ipush(&is, z);
							break;
						case '%' :
							z = modulus(b, a);
							ipush(&is, z);
							break;
                        case '^' :
                            z = power(b, a);
                            ipush(&is, z);
                            break;

						default :
							return NULL;
					}
				}
			}
			else {
				printf("Expression error\n");
				return NULL;
			}
			if(!iisempty(&is)){
				z = ipop(&is);
				if(iisempty(&is))
					return z;
				else {
                                	printf("Less Operators\n");
                                	return NULL;
                        	}
			}
			else {
				printf("Less Operands\n");
				return NULL;
			}
		}
		else if(t.type == ERR) {
            printf("Wrong input , please try again !");
			return NULL;
		}
		prev = curr;
	}
}

