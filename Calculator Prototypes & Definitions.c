#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include <unistd.h>

/* All necessary #defines provided as part of the initial skeleton */

#define INTSIZE	500	/* max number of digits per integer value */
#define LINELEN	999	/* maximum length of any input line */
#define NVARS	26	/* number of different variables */

#define CH_A     'a'    /* character 'a', first variable name */

#define ERROR	(-1)	/* error return value from some functions */
#define PROMPT	"> "	/* the prompt string for interactive input */

#define PRINT	'?'	/* the print operator */
#define ASSIGN	'='	/* the assignment operator */
#define PLUS	'+'	/* the addition operator */
#define MULT	'*'	/* the multiplication operator */
#define POWR	'^'	/* the power-of operator */
#define DIVS	'/'	/* the division operator */
#define ALLOPS  "?=+*^/"

#define CH_ZERO  '0'    /* character zero */
#define CH_ONE   '1'    /* character one */
#define CH_NINE  '9'    /* character nine */

#define CH_COM   ','    /* character ',' */
#define PUT_COMMAS 3    /* interval between commas in output values */

#define INT_ZERO 0	/* integer 0 */
#define INT_ONE 1   /* integer 1 */
#define INT_TEN  10	/* integer 10 */
#define INT_THREE 3 /* integer 3 */
#define INT_TWO 2   /* integer 2 */
#define INT_NEG_ONE -1 /* integer -1 */
#define INT_FOUR 4  /* integer 4 */
#define INT_SIX 6   /* integer 6 */

#define TRUE 1 /* if a statement is true */
#define FALSE 0 /* if a statement is false */

/* Placeholder typedef for skeleton code - longint_t is an array with 501
spaces as 500 spaces are reserved for the digits that make up the integer
and the first space is reserved for the length of the integer.
*/
typedef int longint_t[INTSIZE + INT_ONE];
#define LONG_ZERO 0
#define LONG_ONE  1


/****************************************************************/

/* A "magic" additional function needing explicit declaration */
int fileno(FILE *);

/* Skeleton program function prototypes */

void print_prompt(void);
void print_tadaa();
void print_error(char *message);
int  read_line(char *line, int maxlen);
void process_line(int vars[][INTSIZE + INT_ONE], char *line);
int  get_second_value(int vars[][INTSIZE + INT_ONE], char *rhsarg,
    longint_t second_value);
int  to_varnum(char ident);
void do_print(int varnum, longint_t var);
void do_assign(longint_t var1, longint_t var2);
void do_plus(longint_t var1, longint_t var2);
void zero_vars(int vars[][INTSIZE + INT_ONE]);
void parse_num(char *rhs, longint_t secondval);
void do_multiply(longint_t var1, longint_t var2);
void do_power(longint_t var1, longint_t var2);
int check_if_var2_bigger(longint_t var1, longint_t var2);
void do_minus(longint_t var1, longint_t var2);
void do_division(longint_t var1, longint_t var2);
int count_length(longint_t var);