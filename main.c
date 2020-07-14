#include<stdio.h>
#include<stdarg.h> 
#include<stdlib.h> 
#include<string.h> 
#include<ctype.h>
#include<math.h>
#include<locale.h>
#define pi 3.14159265358979323846
#define e 2.71828182845904523536
#define EPSILON 0.0000000001
#pragma warning( disable:4996)

typedef enum error
{
	ERRORTYPE_WITHOUT_ERROR,
	ERRORTYPE_LACK_OF_MEMORY,
	ERRORTYPE_PROBLEM_WITH_BRACKETS,
	ERRORTYPE_ERROR_WITHIN_OPERATIONS,
	ERRORTYPE_DIVISION_BY_ZERO, 
	ERRORTYPE_ERROR_IN_NUMBER, 
	ERRORTYPE_PROBLEM_WITH_ARGUMENT,
	ERRORTYPE_UNACCEPTABLE_SYMBOLS, 
	ERRORTYPE_ERROR_WITH_SIGNS,
	ERRORTYPE_ERROR_WITH_PI_OR_E,
	ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION,
	ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES, 
	ERRORTYPE_EMPTY_EXPRESSION
}
error_type;

void error_print(error_type error, char *str)
{
	switch (error)
	{
		case ERRORTYPE_WITHOUT_ERROR:
			break;
		case ERRORTYPE_PROBLEM_WITH_BRACKETS:
			printf ("%s == ERROR: problem with brackets\n", str);
			break;
		case ERRORTYPE_ERROR_WITHIN_OPERATIONS:
			printf ("%s == ERROR: error inside expression\n", str);
			break;
		case ERRORTYPE_DIVISION_BY_ZERO:
			printf ("%s == ERROR: division by zero is unacceptable\n", str);
			break;
		case ERRORTYPE_ERROR_IN_NUMBER:
			printf ("%s == ERROR: problem with numbers\n", str);
			break;
		case ERRORTYPE_PROBLEM_WITH_ARGUMENT:
			printf ("%s == ERROR: problem with arguments\n", str);
			break;
		case ERRORTYPE_UNACCEPTABLE_SYMBOLS:
			printf ("%s == ERROR: unresolved characters\n", str);
			break;
		case ERRORTYPE_ERROR_WITH_SIGNS:
			printf ("%s == ERROR: invalib number of characters\n", str);
			break;
		case ERRORTYPE_ERROR_WITH_PI_OR_E:
			printf ("%s == ERROR: problem with e or pi\n", str);
			break;
		case ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION:
			printf ("%s == ERROR: invalid exponential notation\n", str);
			break;
		case ERRORTYPE_LACK_OF_MEMORY:
			printf ("ERROR: lack of memory\n");
			break;
		case ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES:
			printf ("%s == ERROR: check the valid range\n", str);
			break;
		case ERRORTYPE_EMPTY_EXPRESSION:
			printf ("%s == ERROR: empty expression\n", str);
			break;
	}
}
int PRIOR(char a) 
{ 
	switch(a) 
	{ 
		case 'l':
		case 'f':
		case 'i':
		case 'n':
		case 'o':
		case 'a':
		case 'q':
		case 'g':   
		case 't':
		case 'c':
		case 's':
			return 5;
				
		case '^':
			return 4;

		case '*': 
		case '/':
			return 3; 

		case '-': 
		case '+': 
			return 2; 

		case '(': 
			return 1; 
		} 
	return 0; 
}
int isSign(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' )
		return 1;
	return 0;
}
char symbol(char* string, int k)
{
	if ( string[k] == 'c' && string[k + 1] == 't' && string[k + 2] == 'g' )
		return 'g';
	if ( string[k] == 't' && string[k + 1] == 'g' )
		return 't';
	if ( string[k] == 'c' && string[k + 1] == 'o' && string[k + 2] == 's' )
		return 'c';
	if ( string[k] == 's' && string[k + 1] == 'i' && string[k + 2] == 'n' )
		return 's';
	if ( string[k] == 's' && string[k + 1] == 'q' && string[k + 2] == 'r' && string[k + 3] == 't' )
		return 'q';
	if ( string[k] == 'l' && string[k + 1] == 'n' )
		return 'l';
	if ( string[k] == 'f' && string[k + 1] == 'l' && string[k + 2] == 'o' && string[k + 3] == 'o' && string[k + 4] == 'r' )
		return 'f';
	if ( string[k] == 'c' && string[k + 1] == 'e' && string[k + 2] == 'i' && string[k + 3] == 'l' )
		return 'i';
	if ( string[k] == 'a' && string[k + 1] == 'r' && string[k + 2] == 'c' && string[k + 3] == 's' && string[k + 4] == 'i' && string[k + 5] == 'n' )
		return 'n';
	if ( string[k] == 'a' && string[k + 1] == 'r' && string[k + 2] == 'c' && string[k + 3] == 'c' && string[k + 4] == 'o' && string[k + 5] == 's' )
		return 'o';
	if ( string[k] == 'a' && string[k + 1] == 'r' && string[k + 2] == 'c' && string[k + 3] == 't' && string[k + 4] == 'g')
		return 'a';
	if ( string [k] == 'e' && k != 0 )
	{
		if ( isdigit(string[k - 1]) != 0 && string[k + 1] != '\0' )
		{
			return 'E';
		}
	}
	if (string[k] == 'E')
		return 'E';
	return 'x';
}
char check_for_unary_minus(char* string, int k)
{
	if ( string[k - 1] == ')' || isdigit(string[k - 1]) != 0 || ( k == 1 && (isdigit(string[k - 1]) != 0 || string[k - 1]=='e' ) )\
		|| ( string[k - 1] == 'e' && isdigit(string[k - 2]) == 0 ) || string[k - 1] == 'i' )
			return '0';
	return 'y';
}

char *translation_into_reverse_Polish_notation (char *string, error_type* error_code)
{
	char s;
	int k = 0, point = 0, length = strlen(string), z = 0, j = 0;
	char min;
	char *outstring = NULL, *OPERS = NULL;
	outstring = (char *)malloc(1 * sizeof(char));
	if(outstring == NULL) 
	{
		*error_code = ERRORTYPE_LACK_OF_MEMORY;
		return NULL;
	}
	while (string[k]!='\0') 
	{  
		if ( isdigit(string[k]) != 0 || string[k] == '.' || ( string[k] == 'e' && string[k+1] != 'i' ) || ( string[k] == 'p' && string[k+1] == 'i' )\
			|| string[k] == 'E' ) 
		{
			outstring[point] = string[k];
			outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
			if(outstring == NULL)
			{
				if (OPERS != NULL)
				{
					free(OPERS);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			point++;
			if ( ( string[k] == 'e' || string[k] == 'E' ) && ( string[k+1] == '-' || string[k+1] == '+' ) && symbol(string, k) == 'E' )
			{
				k++;
				outstring[point] = string[k];
				outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
				if(outstring == NULL)
				{
					if (OPERS != NULL)
					{
						free(OPERS);
					}
					*error_code = ERRORTYPE_LACK_OF_MEMORY;
					return NULL;
				}
				point++;
			}
		}
		if ( string[k] == '-' && ( k == 0 || check_for_unary_minus(string, k) == 'y' ) && string[k-1] != 'e' && string[k-1] != 'E' )
		{
			outstring[point] = ' ';
			outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
			if(outstring == NULL)
			{
				if (OPERS != NULL)
				{
					free(OPERS);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			point++;			
			outstring[point] = '0';
			outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
			if(outstring == NULL)
			{
				if (OPERS != NULL)
				{
					free(OPERS);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			point++;			
			outstring[point] = ' ';
			outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
			if(outstring == NULL)
			{
				if (OPERS != NULL)
				{
					free(OPERS);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			point++;
			if (OPERS == NULL)
			{
				OPERS = (char *)malloc(length * sizeof(char));
			}
			if (OPERS == NULL)
			{
				if ( outstring != NULL)
				{
					free(outstring);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			OPERS[z] = '-';
			z++;
		}
		if ( ( string[k] == '+' && symbol(string, (k-1)) != 'E' ) || ( string[k] == '-' && k != 0 && check_for_unary_minus(string, k) != 'y'\
		&& symbol(string, (k-1)) != 'E' ) || (PRIOR(string[k])) == 3 || string[k] == '^' || ( string[k] == 'c' && ( ( string[k+1] == 'o'\
		&& string[k-1] != 'c' ) || string[k+1] == 'e' || (string[k-1] != 'r' && string[k+1] == 't' ) ) ) || ( string[k] == 's'\
		&& ( (string[k-1] != 'c' && string[k+1] == 'i' ) || string[k+1] == 'q' ) ) || (string[k] == 't' && string[k+1] == 'g' && string[k-1] != 'c')\
		|| string[k] == 'a' || ( string[k] == 'l' && string[k+1] == 'n') || string[k] == 'f' ) 
		{ 
			outstring[point] = ' ';
			outstring = (char *)realloc(outstring,(2 + point) * sizeof(char));
			if(outstring == NULL)
			{
				if (OPERS != NULL)
				{
					free(OPERS);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			point++;
			if(OPERS == NULL) 
			{
				OPERS=(char *)malloc(length * sizeof(char));
				if (OPERS == NULL)
				{
					if (outstring != NULL)
					{
						free(outstring);
					}
					*error_code = ERRORTYPE_LACK_OF_MEMORY;
					return NULL;
				}
				if ( string[k] >= 'a' && string[k] <= 'z' )
				{
					s = symbol(string, k);
					if (s == 'x')
					{
						if (OPERS != NULL)
						{
							free(OPERS);
						}
						if ( outstring != NULL)
						{
							free(outstring);
						}
						*error_code = ERRORTYPE_ERROR_WITHIN_OPERATIONS;
						return NULL;
					}
					OPERS[z] = s;
				}
				else
				{
					OPERS[z] = string[k];
				}
				z++; 
			} 
			else 
			{ 
				if( (PRIOR(OPERS[z-1]) < PRIOR(string[k]) ) || ( (PRIOR(string[k]) == 4) && (PRIOR(OPERS[z-1]) == 4) ) )
				{
					if (string[k] >= 'a' && string[k] <= 'z')
					{
						s = symbol(string, k);
						if (s =='x')
						{
							if (OPERS != NULL)
							{
								free(OPERS);
							}
							if ( outstring != NULL)
							{
								free(outstring);
							}
							*error_code = ERRORTYPE_ERROR_WITHIN_OPERATIONS;
							return NULL;
						}
						OPERS[z] = s;
					} 
					else
					{
						OPERS[z]=string[k];
					}
					z++;
				}
				else 
				{ 
					while( PRIOR(OPERS[z-1]) >= PRIOR(string[k]) )  
					{ 
						outstring[point] = OPERS[z-1]; 
						point++;
						outstring = (char *)realloc(outstring,(1 + point) * sizeof(char));
						if(outstring == NULL)
						{
							if (OPERS != NULL)
							{
								free(OPERS);
							}
							*error_code = ERRORTYPE_LACK_OF_MEMORY;
							return NULL;
						}
						z--; 
						OPERS[z] = 0; 
					}
					if (string[k] >= 'a' && string[k] <= 'z')
					{
						s = symbol(string, k);
						if (s == 'x')
						{
							if (OPERS != NULL)
							{
								free(OPERS);
							}
							if (outstring != NULL)
							{
								free(outstring);
							}
							*error_code = ERRORTYPE_ERROR_WITHIN_OPERATIONS;
							return NULL;
						}
						OPERS[z] = s;
					} 
					else 
					{
						OPERS[z]=string[k];
					}
					z++;
				}
			}
		}
		if (string[k] == '(')   
		{
			if (OPERS == NULL)
			{
				OPERS = (char *)malloc(length * sizeof(char));
			}
			if (OPERS == NULL)
			{	
				if (outstring != NULL)
				{
					free(outstring);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return NULL;
			}
			OPERS[z] = '(';
			z++;
		}
		if(string[k] == ')')             
		{   
			while((OPERS[z-1]) != '(') 
			{
				outstring[point] = OPERS[z-1]; 
				point++;
				outstring = (char *)realloc(outstring,(1 + point) * sizeof(char));
				if(outstring == NULL)
				{
					if (OPERS != NULL)
					{
						free(OPERS);
					}
					*error_code = ERRORTYPE_LACK_OF_MEMORY;
					return NULL;
				}
				z--; 
				OPERS[z] = 0; 
			}
			OPERS[z-1] = 0; 
			z--;  
		}
		if (string[k] == 'a' && string[k+3] != 't')
		{
			k = k+5;
		}
		k++; 
		min = 0;
	}
	for (j = (z-1); j >= 0; j--) 
	{
		outstring[point] = OPERS[j]; 
		point++;
		outstring = (char *)realloc(outstring,(1 + point) * sizeof(char));
		if(outstring == NULL)
		{
			if ( OPERS != NULL)
			{
				free(OPERS);
			}
			*error_code = ERRORTYPE_LACK_OF_MEMORY;
			return NULL;
		}
	}	
	outstring[point] = '\0';
	free(OPERS);
	*error_code = ERRORTYPE_WITHOUT_ERROR;
	return outstring;
}

double operations(double *str, int k, char c)
{
	double rez = 1;
	switch(c)
    {
		case 'y':
			return ((-1) * str[k - 1]);
		case 'a':
			return (atan(str[k - 1]));
		case 'o':
			return (acos(str[k - 1]));
		case 'n':
			return (asin(str[k - 1]));
		case 'i':
			return (ceil(str[k - 1]));
		case 'f':
			return (floor(str[k - 1]));
		case 'l':
			return (log(str[k - 1]));
		case 'q':
			return (sqrt(str[k - 1]));
		case 'g':
			return (1 / tan(str[k - 1]));
		case 't':
			return (tan(str[k - 1]));
		case 's':
			return (sin(str[k - 1]));
		case 'c':
			return (cos(str[k - 1]));
        case '+':
            return ( str[k - 2] + str[k - 1] );
        case '-':
		    return ( str[k - 2] - str[k - 1] );
        case '*':
			return ( str[k - 2] * str[k - 1] );
        case '/':
            return ( str[k - 2] / str[k - 1] );
		case '^':
			rez = pow(str[k - 2], str[k - 1]);
			return rez;
	}
	return 0;
}
error_type check_for_odz(double* str, int i, double c)
{
	if ( ( c == '^' && str[i-2] < 0 && fmod(str[i-1], 1) != 0 ) || ( c == 'q' && str[i-1] < 0 ) || ( c == 'l' && str [i-1] <= 0 )\
		|| ( ( c == 'n' || c == 'o' ) && ( str[i-1] < -1 || str[i-1] > 1 ) ) || ( c == 't' && fabs(cos(str[i-1])) < EPSILON)\
		|| ( c == 'g' && fabs(sin(str[i-1])) < EPSILON ) )
	{
		return ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES;
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
int check_for_cos_sin_tg_ctg(double* str,int i, double c)
{
	if (c == 's')
	{
		if (fabs(sin(str[i-1])) < EPSILON)
			return 1;
	}
	if (c == 'c')
	{
		if (fabs(cos(str[i-1])) < EPSILON) 
			return 1;
	}
	if (c == 't')
	{
		if (fabs(tan(str[i-1])) < EPSILON)
			return 1;
	}
	if (c == 'g')
	{
		if (fabs(1 / tan(str[i-1])) < EPSILON)
			return 1;
	}
	return 0;
}
double Calculate(char *outstring, error_type* error_code)
{
	int i = 0, p = 0, n = 0, length = strlen(outstring), j = 0, null = 0, w = 0, d = 0;
	error_type odz = ERRORTYPE_WITHOUT_ERROR;
	double c1;
	double rezult = 0;
	char ch;
	double *stek = NULL;
	char *ch1 = (char *)malloc((length + 1) * sizeof(char));
	if ( ch1 == NULL )
	{
		*error_code = ERRORTYPE_LACK_OF_MEMORY;
		return 0;
	}
	stek = (double *)malloc(sizeof(double));
	if ( stek == NULL )
	{
		free(ch1);
		*error_code = ERRORTYPE_LACK_OF_MEMORY;
		return 0;
	}
	while (outstring[i] != '\0')
	{		
		if ( isdigit(outstring[i]) != 0 )
		{
			ch1[p] = outstring[i]; 
			if (isdigit(outstring[i+1]) == 0 && outstring[i+1] != '.' && outstring[i+1] != 'e' && outstring[i+1] != 'E')
			{
				stek = (double *)realloc(stek,(2 + n)*sizeof(double));
				if (stek == NULL)
				{
					if (ch1 != NULL)
					{
						free(ch1); 
					}
					*error_code = ERRORTYPE_LACK_OF_MEMORY;
					return 0;
				}
				stek[n] = (ch1[p] - 48);
				n++;
				ch1[p] = 0;
			}
			else 
			{
				i++;
				while ( isdigit(outstring[i]) != 0 || outstring[i] == '.' || outstring[i] == 'e' || outstring[i] == 'E' || ( outstring[i] == '+'\
						&& symbol(outstring, (i-1)) == 'E' ) || ( outstring[i] == '-' && symbol(outstring, (i-1)) == 'E' ) ) 
				{
					p++;
					ch1[p] = outstring[i];
					i++;
				}
				ch1[p+1] = '\0';
				for (w = 0; w <= p; w++)
				{
					if (ch1[w] == 'e' || ch1[w] == 'E')
					d = 1;
					if (ch1[w] == '.' && d == 1)
					{
						if (stek != NULL)
						{
							free(stek);
						}
						if (ch1 != NULL)
						{
							free(ch1);
						}
						*error_code = ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION;
						return 0;
					}
				}
				c1 = atof(ch1);
				stek = (double *)realloc(stek,(2 + n)*sizeof(double));
				if (stek == NULL)
				{
					if (ch1 != NULL)
					{
						free(ch1);
					}
					*error_code = ERRORTYPE_LACK_OF_MEMORY;
					return 0;
				}
				stek[n] = c1;
				n++;
				c1 = 0;
				for (j = 0; j <= p; j++)
				{
					ch1[j] = 0;
				}
				p = 0;
				d = 0;
				w = 0;
				i--;
			}
		}
		if (outstring[i] == 'e')
		{
			stek = (double *)realloc(stek,(2 + n) * sizeof(double));
			if (stek == NULL)
			{
				if (ch1 != NULL)
				{
					free(ch1);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return 0;
			}
			stek[n] = e;
			n++;
		}
		if (outstring[i] == 'p')
		{
			stek = (double *)realloc(stek,(2 + n) * sizeof(double));
			if (stek == NULL)
			{
				if (ch1 != NULL)
				{
					free(ch1);
				}
				*error_code = ERRORTYPE_LACK_OF_MEMORY;
				return 0;
			}
			stek[n] = pi;
			n++;	
		}
		if (isSign(outstring[i]) == 1)
		{
			ch = outstring[i];
			if (ch == '/')
			{
				if (stek[n-1] == 0)
				{
					if (stek != NULL)
					{
						free(stek);
					}
					if (ch1 != NULL)
					{
						free(ch1);
					}
					*error_code = ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES;
					return 0;
				}
			}
			if (ch == '^')
			{
				odz = check_for_odz(stek, n, ch);
				if (odz == ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES)
				{
					if (stek != NULL)
					{
						free(stek);
					}
					if (ch1 != NULL)
					{
						free(ch1);
					}
					*error_code = ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES;
					return 0;
				}
			}
			stek[n-2] = operations(stek, n, ch);
			stek[n-1] = 0;
			n--;
		}
		if (PRIOR(outstring[i]) == 5)
		{
			ch = outstring[i];
			if (ch == 'q' || ch == 'l' || ch == 'n' || ch == 'o' || ch == 't' || ch == 'g')
			{
				odz = check_for_odz(stek, n, ch);
			}
			if (odz == ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES)
			{
				if (stek != NULL)
				{
					free(stek);
				}
				if (ch1 != NULL)
				{
					free(ch1);
				}
				*error_code = ERRORTYPE_ERROR_IN_THE_RANGE_OF_ALLOWED_VALUES;
				return 0;
			}
			if (ch == 's' || ch == 'c' || ch == 't' || ch == 'g')
				null = check_for_cos_sin_tg_ctg(stek, n, ch);
			if (null == 1)
			{
				stek[n-1] = 0;
			}
			else
			{
				stek[n-1] = operations(stek, n, ch);
			}
			stek[n]=0;
		}
		odz = ERRORTYPE_WITHOUT_ERROR;
		null = 0;
		i++;
	}
stek[n]='\0';
free(ch1);
rezult = stek[0];
free(stek);
*error_code = ERRORTYPE_WITHOUT_ERROR;
return rezult;
}

int checking_for_comments(char *str, int i)
{ 
	int r = 0, j;
	for (j = 0; j < i; j++)
	{
		if (isspace(str[j]) == 0)
			r++;
	}
	if (r > 0)
		return 0;
	return 1;
}
error_type check_for_invalid_character(char c)
{
	if ( ( c >= '0' && c <= '9') || c == '.' || c == '\n' || c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\b' || c == '\f'\
		|| isSign(c) == 1 || c == '(' || c == ')' || c == 'c' || c == 'o' || c == 's' || c == 'i' || c == 'n' || c == 'a' || c == 'r'\
		|| c == 't' || c == 'g' || c == 'q' || c == 'l' || c == 'f' || c == 'e' || c == 'E' || c == 'p') 
	{
		return ERRORTYPE_WITHOUT_ERROR;
	}
	return ERRORTYPE_UNACCEPTABLE_SYMBOLS;
}
char *removing_spaces(char* string, error_type *error_code)
{
	int length = strlen(string), i = 0, x = 0;
	char* str = (char *)malloc((length + 1) * sizeof(char));
	if (str == NULL)
	{
		*error_code = ERRORTYPE_LACK_OF_MEMORY;
		return NULL;
	}
	for (i = 0; i < length; i++)
	{
		if (check_for_invalid_character(string[i]) == ERRORTYPE_UNACCEPTABLE_SYMBOLS)
		{
			str[x] = string[i];
			x++;
		}
		else
		{
			if (isspace(string[i]) == 0)
			{
				str[x] = string[i];
				x++;
			}
		}
	}
	str[x] = '\0';
	*error_code = ERRORTYPE_WITHOUT_ERROR;
	return str;
}

error_type checking_for_brackets(char *str)
{
	int i = 0, p = 0, length = strlen (str);
	for (i = 0; i < length; i++)
	{
		if (str[i] == '(')
			p++;
		if (p == 0 && str[i] == ')')
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;
		if (str[i] == ')')
			p--;
		if ( str[i] == '(' && i != 0 && str[i-1] != '(' && isSign(str[i-1]) == 0 && str[i-1] != 's' && str[i-1] != 'n'\
			&& str[i-1] != 'g' && str[i-1] != 'r' && str[i-1] != 'l' && str[i-1] != 't' )
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;
		if ( str[i] == '(' && str[i+1] != '(' && str[i+1] != '-' && isdigit(str[i+1]) == 0 && str[i+1] != 'a'\
			&& str[i+1] != 't' && str[i+1] != 'e' && str[i+1] != 'p' && str[i+1] != 's' && str[i+1] != 'l'\
			&& str[i+1] != 'f' && str[i+1] != 'c' )
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;
		if ( str[i] == ')' && str[i-1] != ')' && isdigit(str[i-1]) == 0 && str[i-1] != 'e' && str[i-1] != 'i' )
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;
		if ( str[i]==')' && isSign(str[i+1]) == 0 && str[i+1] != ')' && str[i+1] != '\0' )
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;
	}
		if (p != 0)
			return ERRORTYPE_PROBLEM_WITH_BRACKETS;;
		return ERRORTYPE_WITHOUT_ERROR;
}
error_type check_for_invalid_characters(char *str)
{
	int i, count = 0, length = strlen(str);
	for (i = 0; i < length; i++)
	{
		if ( (isdigit(str[i])!=0) || ( str[i-1]>='0' && str[i-1]<='9' && str[i]=='.' && str[i+1]>='0' && str[i+1]<='9') || str[i]=='+' || str[i]=='-' || str[i]=='/' || str[i]=='*' || str[i]=='^' || str[i]=='(' || str[i]==')' || str[i]=='c' || str[i]=='o' || str[i]=='s' || str[i]=='i' || str[i]=='n' || str[i]=='a' || str[i]=='r' || str[i]=='t' || str[i]=='g' || str[i]=='q' || str[i]=='l' || str[i]=='f' || str[i]=='e' || str[i]=='E' || str[i]=='p') 
		
			count++;

	}
	if (count == length)
		return ERRORTYPE_WITHOUT_ERROR;
	return ERRORTYPE_UNACCEPTABLE_SYMBOLS;
}
error_type checking_operations(char *string)
{
	int k = 0, length = strlen(string);
	for (k = 0; k < length; k++)
	{
	if ( string[k] == 'a' && string[k+1] == 'r' && string[k+2] == 'c' && ( (string[k+3] == 'c' && string[k+4] == 'o' && string[k+5] == 's')\
		|| (string[k+3] == 't' && string[k+4] == 'g') || (string[k+3] == 's' && string[k+4] == 'i' && string[k+5] == 'n') ) )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 'a') 
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS;
	if ( string[k] == 'c' && ( (string[k+1] == 't' && string[k+2] == 'g') || (string[k+1] == 'o' && string[k+2] == 's')\
		|| (string[k+1] == 'e' && string[k+2] == 'i' && string[k+3] == 'l') ) )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 'c') 
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS;
	if ( string[k] == 'f' && string[k+1] == 'l' && string[k+2] == 'o' && string[k+3] == 'o' && string[k+4] == 'r' )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 'f')
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS;
	if ( string[k] == 't' && string[k+1] == 'g' )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 't')
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS; 
	if ( string[k] == 's'  && ( (string[k+1] == 'i' && string[k+2] == 'n') || (string[k+1] == 'q' && string[k+2] == 'r' && string[k+3] == 't') ) )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 's')
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS; 
	if ( string[k] == 'l' && string[k+1] == 'n' )
		return ERRORTYPE_WITHOUT_ERROR;
	else if (string[k] == 'l')
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS; 
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
error_type check_for_divide_by_zero(char *str)
{
	int i, length = strlen(str);
	for (i = 0; i < length; i++)
	{
		if ( str[i] == '/' && str[i+1] == '0' )
		return ERRORTYPE_DIVISION_BY_ZERO;
	}
	return ERRORTYPE_WITHOUT_ERROR;
}

error_type checking_for_signs(char *str, int i)
{
	if (str[i] != '-')
	{
		if (i == 0)
			return ERRORTYPE_ERROR_WITH_SIGNS;
		if ( ( isdigit(str[i+1]) != 0 || str[i+1] == '(' || str[i+1] == 'a' || str[i+1] == 'c' || str[i+1] == 't'\
			|| str[i+1] == 'e' || str[i+1] == 'p' || str[i+1] == 's' || str[i+1] == 'l' || str[i+1] == 'f'\
			|| str[i+1] == '-' ) && ( (str[i] == '+' && (str[i-1] == 'e' || str[i-1] == 'E') )\
			|| isdigit(str[i-1]) != 0 || str[i-1] == ')' || str[i-1] == 'e' || str[i-1] == 'i' ) )
				return ERRORTYPE_WITHOUT_ERROR;
	}
	if ( i != 0 && str[i] == '-' && (isdigit(str[i+1]) != 0 || str[i+1] == '(' || str[i+1] == 'a' || str[i+1] == 'c'\
		|| str[i+1] == 't' || str[i+1] == 'e' || str[i+1] == 'p' || str[i+1] == 's' || str[i+1] == 'l'\
		|| str[i+1] == 'f' || str[i+1] == '-' ) &&  ( str[i-1] == ')' || str[i-1] == '(' || str[i-1] == 's'\
		|| str[i-1] == 'n' || str[i-1] == 'g' || str[i-1] == 'i' || str[i-1] == 'r' || str[i-1] == 'l'\
		|| str[i-1] == 't' || isdigit(str[i-1]) != 0 || isSign(str[i-1]) == 1 || str[i-1] == 'e'  || str[i-1] == 'E' ) ) 
			return ERRORTYPE_WITHOUT_ERROR;
	if ( i == 0  && str[i] == '-' && (str[i+1] == '(' || str[i+1] == 'a' || str[i+1] == 'c' || str[i+1] == 't'\
		|| str[i+1] == 'e' || str[i+1] == 'p' || str[i+1] == 's' || str[i+1] == 'l' || str[i+1] == 'f'\
		|| isdigit(str[i+1]) != 0 || str[i+1] == '-' ) )
			return ERRORTYPE_WITHOUT_ERROR;
	return ERRORTYPE_ERROR_WITH_SIGNS;
}
error_type checking_for_pi_and_e(char *string, char* string1)
{
	int i = 0, j = 0, length = strlen(string), length1 = strlen(string1);
	for (i = 0; i < length; i++)
	{
		if ( i != 0 && string[i] == 'p' && string[i+1] == 'i' && ( isalpha(string[i+2]) != 0 || isdigit(string[i+2]) != 0 || string[i+2] == '('\
			|| string[i+2] == '.' || isdigit(string[i-1]) != 0 || string[i-1] == '.' || string[i-1] == ')' || ( isalpha(string[i-1]) != 0\
			&& string[i-1] != 'n' && string[i-1] != 's' && string[i-1] != 'g' && string[i-1] != 'r' && string[i-1] != 'l' && string[i-1] != 't' ) ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i != 0 && string[i] == 'e' && string[i+1] != 'i' && symbol(string, i) != 'E' && ( isdigit(string[i+1]) != 0 || string[i+1] == '(' \
			|| string[i+1] == '.' || isalpha(string[i+1]) != 0 || isdigit(string[i-1]) != 0 || string[i-1] == ')' || ( isalpha(string[i-1]) != 0\
			&& string[i-1] != 'n' && string[i-1] != 's' && string[i-1] != 'g' && string[i-1] != 'r' && string[i-1] != 'l' && string[i-1] != 't' ) ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i != 0 && ( ( string[i] == 'e' && string[i+1] != 'i' ) || string[i] == 'E' ) && ( string[i-1] == ')' || string[i-1] == '.'\
			|| string[i+1] == '.' || string[i+1] == '(' ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i != 0 && string[i] == 'e' && string[i+1] != 'i' && isalpha(string[i-1]) != 0 && string[i-1] != 'n' && string[i-1] != 's'\
			&& string[i-1] != 'g' && string[i-1] != 'r' && string[i-1] != 'l' && string[i-1] != 't' )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i != 0 && string[i] == 'E' && isdigit(string[i-1]) == 0 )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( string[i] == 'E' && string[i+1] != '-' && string[i+1] != '+' && isdigit(string[i+1]) == 0 )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i == 0 && string[i] == 'e' && (isdigit(string[i+1]) != 0 || string[i+1] == '(' || isalpha(string[i+1]) != 0 || string[i+1] == ')'\
			|| string[i+1] == '.' ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( string[i] == 'e' && string[i+1] == 'e' )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if (  i != 0 && ( ( string[i] == 'e' && string[i+1] != 'i' ) || string[i] == 'E') && isdigit(string[i-1]) != 0 && ( string[i+2] == '('\
			|| string[i+1] == '(' || string[i+1] == ')' ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( string[i] == 'p' && string[i+1] == 'i' && ( isalpha(string[i+2]) != 0 || isdigit(string[i+2]) != 0 || string[i+2] == '.' || string[i+2] == '(' ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
		if ( i == 0 && string[i] == 'p' && string[i+1] == 'i' && ( isdigit(string[i+2]) != 0 || string[i+2] == '(' || string[i+2] == '.'\
			|| string[i+2] == ')' || isalpha(string[i+2]) != 0 ) )
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
	}
	for (j=0; j<length1; j++)
	{
		if (string1[j]=='p' && isspace(string1[j+1])!=0)
			return ERRORTYPE_ERROR_WITH_PI_OR_E;
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
error_type check_for_numbers(char* string, char* string1)
{
	int i = 0, length = strlen(string), length1 = strlen(string1);
	for (i = 0; i < length; i++)
	{
		if (string[i] == '.')
		{
			i++;
			if(isdigit(string[i]) == 0)
				return ERRORTYPE_ERROR_IN_NUMBER;
			while (isdigit(string[i]) != 0)
			{
				i++;
				if ( string[i] == '.' || ( isalpha(string[i]) != 0 && string[i] != 'e' && string[i] != 'E' ) || string[i] == '(' )
				return ERRORTYPE_ERROR_IN_NUMBER;
			}
		}
		if ( isdigit(string[i]) != 0 && string[i+1] != 'e' && string[i+1] != 'E' && isalpha(string[i+1]) != 0)
			return ERRORTYPE_ERROR_IN_NUMBER;
		if ( i != 0 && isdigit(string[i]) != 0 && isdigit(string[i-1]) == 0 && string[i-1] != '(' && string[i-1] != '.' && isSign(string[i-1]) == 0\
			&& string[i-1] != 'n' && string[i-1] != 's' && string[i-1] != 'g' && string[i-1] != 't' && string[i-1] != 'r' && string[i-1] != 'l'\
			&& string[i-1] != 'e' && string[i-1] != 'E' )
			return ERRORTYPE_ERROR_IN_NUMBER;
		if ( i == 0 && isalpha(string[i]) != 0 && string[i] != 'c' && string[i] != 's' && string[i] != 't' && string[i] != 'f' && string[i] != 'l'\
			&& string[i] != 'a' && string[i] != 'p' && string[i] != 'e' )
			return ERRORTYPE_ERROR_IN_NUMBER;
	}
	for (i = 0; i < length1; i++)
	{
		if ( isdigit(string1[i]) != 0 && isspace(string1[i+1]) != 0 )
		{
			i++;
			while (isspace(string1[i]) != 0)
				i++; 
			if (isdigit(string1[i]) != 0 || string1[i] == '.' || string1[i] == '(' || (isalpha(string1[i]) != 0 && string1[i] != 'e' && string1[i] != 'E' ) )
				return ERRORTYPE_ERROR_IN_NUMBER; 
		}
		if (string1[i]=='.' && isdigit(string1[i+1])==0 )
		{
			return ERRORTYPE_ERROR_IN_NUMBER;
		}
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
error_type operations_without_arg(char* string)
{
	int k = 0, length = strlen(string);
	for (k = 0; k < length; k++)
	{
	if ( string[k] == 'c' && string[k+1] == 't' && string[k+2] == 'g' && string[k+3] != '(' && string[k+3] != '-' && string[k+3] != 'e'\
		&& string[k+3] != 'p' && isdigit(string[k+3]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 't' && string[k+1] == 'g' && string[k+2] != '(' && string[k+2] != '-' && string[k+2] != 'e' && string[k+2] != 'p'\
		&& isdigit(string[k+2]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'c' && string[k+1] == 'o' && string[k+2] == 's' && string[k+3] != '(' && string[k+3] != '-' && string[k+3] != 'e'\
		&& string[k+3] != 'p' && isdigit(string[k+3]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 's' && string[k+1] == 'i' && string[k+2] == 'n' && string[k+3] != '(' && string[k+3] != '-' && string[k+3] != 'e'\
		&& string[k+3] != 'p' && isdigit(string[k+3]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 's' && string[k+1] == 'q' && string[k+2] == 'r' && string[k+3] == 't' && string[k+4] != '(' && string[k+4] != '-'\
		&& string[k+4] != 'e' && string[k+4] != 'p' && isdigit(string[k+4]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'l' && string[k+1] == 'n' && string[k+2] != '(' && string[k+2] != '-' && string[k+2] != 'e' && string[k+2] != 'p'\
		&& isdigit(string[k+2]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'f' && string[k+1] == 'l' && string[k+2] == 'o' && string[k+3] == 'o' && string[k+4] == 'r' && string[k+5] != '('\
		&& string[k+5] != '-' && string[k+5] != 'e' && string[k+5] != 'p' && isdigit(string[k+5]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'c' && string[k+1] == 'e' && string[k+2] == 'i' && string[k+3] == 'l' && string[k+4] != '(' && string[k+4] != '-'\
		&& string[k+4] != 'e' && string[k+4] != 'p' && isdigit(string[k+4]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'a' && string[k+1] == 'r' && string[k+2] == 'c' && string[k+3] == 's' && string[k+4] == 'i' && string[k+5] == 'n'\
		&& string[k+6] != '(' && string[k+6] != '-' && string[k+6] != 'e' && string[k+6] != 'p' && isdigit(string[k+6]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'a' && string[k+1] == 'r' && string[k+2] == 'c' && string[k+3] == 'c' && string[k+4] == 'o' && string[k+5] == 's'\
		&& string[k+6] != '(' && string[k+6] != '-' && string[k+6] != 'e' && string[k+6] != 'p' && isdigit(string[k+6]) == 0 ) 
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	if ( string[k] == 'a' && string[k+1] == 'r' && string[k+2] == 'c' && string[k+3] == 't' && string[k+4] == 'g' && string[k+5] != '('\
		&& string[k+5] != '-' && string[k+5] != 'e' && string[k+5] != 'p' && isdigit(string[k+5]) == 0 )
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
error_type verification_of_scientific_record(char *string, char *string1)
{
	int i, length= strlen(string), length1 = strlen(string1), k;
	for (i = 0; i < length1; i++)
		{
			if (string1[i] == 'E')
			{
				if (isspace(string1[i-1]) != 0 || isspace(string1[i+1]) != 0 || isspace(string1[i+1]) != 0 || string1[i+1] == '(' || string1[i+1] == ')'\
					|| string1[i+1] == '*' || string1[i+1] == '/' || string1[i+1] == '^' || isalpha(string1[i+1]) != 0 || string1[i-1] == '*'\
					|| string1[i-1] == '/' || string1[i-1] == '^' || isalpha(string1[i-1]) != 0 || ( isdigit(string1[i+1]) == 0 && isdigit(string1[i+2]) == 0 ) )
				{
					return ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION;
				}
			}
			if (string1[i] == 'e' && i != 0)
			{
				k = i - 1;
				while (isspace(string1[k]) != 0)
					k--;
				if (isdigit(string1[k]) != 0)
				{
					if ( isspace(string1[i-1]) != 0 || isspace(string1[i+1]) != 0 || string1[i+1] == '(' || string1[i+1] == ')' || string1[i+1]=='*'\
						|| string1[i+1] == '/' || string1[i+1] == '^' || isalpha(string1[i+1]) != 0 || string1[i-1] == '*' || string1[i-1] == '/'\
						|| string1[i-1] == '^' || isalpha(string1[i-1]) != 0 || ( isdigit(string1[i+1]) == 0 && isdigit(string1[i+2]) == 0 ) )
					{
						return ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION;
					}
				}
				k = 0;
			}
		}
		for (i= 0; i < length; i++)
		{
			if ( ( i != 0 && string[i] == 'e' && isdigit(string[i-1]) != 0 ) || string[i] == 'E' )
			{
				i++;
				while ( isdigit(string[i]) != 0 || ( string[i] == '-' && ( string[i-1] == 'e' || string[i-1] == 'E' ) ) || (string[i] == '+'\
					&& (string[i-1] == 'e' || string[i-1] == 'E' ) ) )
					i++;
				if (string[i] == 'e' || string[i] == 'E')
				{
					return ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION;
				}				
			}
		}
return ERRORTYPE_WITHOUT_ERROR;
}


error_type checking_for_a_fool (char* string, char* string1)
{
	int i = 0, length = strlen(string);
	error_type brackets, operations, number, zero, argument, letter, sign, pi_and_e,scientific_record;
	brackets = checking_for_brackets(string);
	if (brackets != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_PROBLEM_WITH_BRACKETS;
	} 
	operations = checking_operations(string1);
	if (operations != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_ERROR_WITHIN_OPERATIONS;
	}
	zero = check_for_divide_by_zero(string);
	if (zero != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_DIVISION_BY_ZERO;
	}
	number = check_for_numbers(string, string1);
	if (number != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_ERROR_IN_NUMBER;
	}
	argument = operations_without_arg(string);
	if (argument != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_PROBLEM_WITH_ARGUMENT;
	}
	letter = check_for_invalid_characters(string);
	if (letter != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_UNACCEPTABLE_SYMBOLS;
	}
	for (i = 0; i < length; i++)
	{
		if (isSign(string[i]) == 1)
		{
			sign = checking_for_signs(string, i);
			if (sign != ERRORTYPE_WITHOUT_ERROR)
			{
				return ERRORTYPE_ERROR_WITH_SIGNS;
			}
		}
	}
	pi_and_e = checking_for_pi_and_e(string, string1);
	if (pi_and_e != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_ERROR_WITH_PI_OR_E;
	}
	scientific_record = verification_of_scientific_record(string, string1);
	if (scientific_record != ERRORTYPE_WITHOUT_ERROR)
	{
		return ERRORTYPE_ERROR_IN_EXPONENTIAL_NOTATION;
	}
	return ERRORTYPE_WITHOUT_ERROR;
}
void read_out_when_there_is_a_shortage_of_memory ()
{
	int i = 0, c = 0;
	while ( (c = getchar()) != EOF && c != '\n' )
		i++;
}
int main (int argc, char const *argv[])
{
	int w = 0, i, u = 0, n = 0, space = 0, count = 0, r = 0;
	int simvol = 0, p = 0;
	error_type error_code = ERRORTYPE_WITHOUT_ERROR;
	error_type* error_code_for_functions = NULL;
	char *string1 = NULL;
	char *string = NULL;
	char *newstring = NULL; 
	double rezult = 0;
	if (argc > 2)
	{
		printf("ERROR: a lot of arguments. Enter 1 or 2 arguments");
		return 0;
	}
	if (argc == 2)
	{
		FILE *arr;
		arr = freopen (argv[1], "r", stdin);
		if (arr == NULL)
		{
			printf ("ERROR: unable to open file");
			return 0;
		}
	}
	do
	{
		error_code = ERRORTYPE_WITHOUT_ERROR;
		while( ( (simvol = getchar()) != EOF) && (simvol != '\n') ) 
		{
			if (r == 0)
			{
				string1 = (char *)malloc(1 * sizeof(char));
				if (string1 == NULL)
				{
					read_out_when_there_is_a_shortage_of_memory();
					error_code = ERRORTYPE_LACK_OF_MEMORY;
					break;
				}
				r = 1;
			}
			string1[count] = (char)simvol; 
			string1 = (char *)realloc(string1,(2 + count)*sizeof(char));
			if(string1 == NULL)
			{
				read_out_when_there_is_a_shortage_of_memory();
				error_code = ERRORTYPE_LACK_OF_MEMORY;
				break;
			}
			count++;
		}
		if (string1 != NULL)
		string1[count] = '\0';
		if (error_code != ERRORTYPE_WITHOUT_ERROR)
		{
			error_print (error_code, string1);
		}
		else
		{
			if ( string1 == NULL && (simvol == EOF || simvol == '\n') )
			{
				if ( simvol == '\n' )
				{
					printf ("\n");
					p = 1;
				}
				else
				{
					return 0;
				}
			}
			if (p == 0)
			{
				error_code_for_functions = (error_type *)malloc(1 * sizeof(error_type));
				if (error_code_for_functions == NULL)
				{
					error_code = ERRORTYPE_LACK_OF_MEMORY;
					error_print (error_code, string1);
					free(string1);
				}
				else 
				{
					string = removing_spaces(string1, error_code_for_functions);
					error_code = *error_code_for_functions;
					if (error_code != ERRORTYPE_WITHOUT_ERROR)
					{
						error_print (error_code, string1);
						free(string1);
						free(error_code_for_functions);
					}
					else 
					{
						for (i = 0; i < count; i++)
						{
							if ( (string1[i] == '/') && (string1[i + 1] == '/') )
							{
								u = i;
								n = 1;
								break;
							}
						}
						if (n == 1)
						{
							w = checking_for_comments(string1, u);
						}
						if ( w == 1 || string[0] == '\0' )
						{
							space = 1;
							printf ("%s\n", string1);
							free(string1);
							free(error_code_for_functions);
							free(string);
						}
						else
						{
							error_code = checking_for_a_fool(string, string1);
							if (error_code != ERRORTYPE_WITHOUT_ERROR)
							{
								error_print (error_code, string1);
								free(string1);
								free(error_code_for_functions);
								free(string);
							}
							if ( error_code == ERRORTYPE_WITHOUT_ERROR && w == 0 )
							{  
								newstring = translation_into_reverse_Polish_notation(string, error_code_for_functions);
								error_code = *error_code_for_functions;
								if (error_code != ERRORTYPE_WITHOUT_ERROR)
								{
									error_print (error_code, string1);
									free(string1);
									free(error_code_for_functions);
									free(string);
								}
								else
								{
									rezult = Calculate(newstring, error_code_for_functions);
									error_code = *error_code_for_functions;
									if ( error_code == ERRORTYPE_WITHOUT_ERROR )
									{
										if (rezult == -0)
										{
											rezult = 0;
										}
										printf("%s == %g\n", string1, rezult);
									}
									else 
									{
										error_print (error_code, string1);	
									}
										free(string1);
										free(error_code_for_functions);
										free(string);
										free(newstring);
								}
							}
						}
					}
				}
			}
		}
		w = 0;
		u = 0;
		n = 0;
		space = 0;
		p = 0;
		count = 0;
		r = 0;
		string1 = NULL;
} while (simvol!=EOF);
	return 0;
}