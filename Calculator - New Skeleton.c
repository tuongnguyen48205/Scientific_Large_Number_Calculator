/* Program to perform multi-digit integer arithmetic.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2023, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.
   All included code is (c) Copyright University of Melbourne, 2023

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Tuong Bao Nguyen 1463906
   Dated:     07/09/2023

*/

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

/****************************************************************/

/* Main program controls all the action.
*/
int
main(int argc, char *argv[]) {
    char line[LINELEN + 1] = {0};
    int vars[NVARS][INTSIZE + 1];

    zero_vars(vars);
    print_prompt();
    while (read_line(line, LINELEN)) {
        if (strlen(line) > INT_ZERO) {
            /* non empty line, so process it */
            process_line(vars, line);
        }
        print_prompt();
    }
    print_tadaa();
    return 0;
}

/****************************************************************/

/* Prints the prompt indicating ready for input, but only if it
   can be confirmed that the input is coming from a terminal.
   Plus, output might be going to a file, that's why the prompt,
   if required, is written to stderr and not stdout.
*/
void
print_prompt(void) {
    if (isatty(fileno(stdin))) {
        fprintf(stderr, "> ");
        fflush(stderr);
    }
}

void
print_tadaa() {
    /* all done, so pack up bat and ball and head home,
       getting the exact final lines right is a bit tedious,
       because input might be coming from a file and output
       might be going to a file. 
    */
    if (isatty(fileno(stdin)) && isatty(fileno(stdout))) {
        printf("\n");
    }
    printf("ta daa!!!\n");
    if (isatty(fileno(stdin)) && !isatty(fileno(stdout))) {
        fprintf(stderr, "\n");
    }
}

void
print_error(char *message) {
    /* need to write an error message to the right place(s).
    */
    if (isatty(fileno(stdin)) || isatty(fileno(stdout))) {
        fprintf(stderr, "%s\n", message);
        fflush(stderr);
    }
    if (!isatty(fileno(stdout))) {
        printf("%s\n", message);
    }
}

/****************************************************************/

/* Reads a line of input into the array passed as argument,
   returns false if there is no input available.
   All whitespace characters are removed on the way through.
*/
int
read_line(char *line, int maxlen) {
    int i = 0, c;
    while (((c=getchar()) != EOF) && (c != '\n')) {
        if (i < maxlen && !isspace(c)) {
            line[i++] = c;
        }
    }
    line[i] = '\0';
    /* then, if the input is coming from a file or the output
       is going to a file, it is helpful to echo the input line
       and record what the command was. 
    */
    if (!isatty(fileno(stdin)) || !isatty(fileno(stdout))) {
        printf("%s%s\n", PROMPT, line);
    }
    return ((i > 0) || (c != EOF));
}

/****************************************************************/

/* Process a command by parsing the input line into parts.
*/
void
process_line(int vars[][INTSIZE + INT_ONE], char *line) {
    int varnum, optype, status;
    longint_t second_value = {LONG_ZERO};

    /* determine the LHS variable, it
       must be first character in compacted line
    */
    varnum = to_varnum(line[INT_ZERO]);
    if (varnum == ERROR) {
        print_error("invalid LHS variable");
        return;
    }

    /* more testing for validity 
    */
    if (strlen(line) < INT_TWO) {
        print_error("no operator supplied");
        return;
    }

    /* determine the operation to be performed, it
       must be second character of compacted line
    */
    optype = line[INT_ONE];
    if (strchr(ALLOPS, optype) == NULL) {
        print_error("unknown operator\n");
        return;
    }

    /* determine the RHS argument (if one is required),
       it must start in the third character of compacted line
    */
    if (optype != PRINT) {
        if (strlen(line) < INT_THREE) {
            print_error("no RHS supplied");
            return;
        }
        status = get_second_value(vars, line + INT_TWO, second_value);
        if (status == ERROR) {
            print_error("RHS argument is invalid");
            return;
        }
    }

    /* finally, do the actual operation
    */
    if (optype == PRINT) {
        do_print(varnum, vars[varnum]);
    } else if (optype == ASSIGN) {
        do_assign(vars[varnum], second_value);
    } else if (optype == PLUS) {
        do_plus(vars[varnum], second_value);
    // you will need to add further operators here
    } else if (optype == MULT) {
        do_multiply(vars[varnum], second_value);
    } else if (optype == POWR) {
        do_power(vars[varnum], second_value);
    } else if (optype ==DIVS) {
        do_division(vars[varnum], second_value);
    } else {
        print_error("operation not available yet.");
        return;
    }
    return;
}

/****************************************************************/

/* Convert a character variable identifier to a variable number.
*/
int
to_varnum(char ident) {
    int varnum;
    varnum = ident - CH_A;
    if (INT_ZERO <= varnum && varnum < NVARS) {
        return varnum;
    } else {
        return ERROR;
    }
}

/****************************************************************/

/* Process the input line to extract the RHS argument, which
   should start at the pointer that is passed.
*/
int
get_second_value(int vars[][INTSIZE + INT_ONE], char *rhsarg,
    longint_t second_value) {
    char *p;
    int varnum2;
    if (isdigit(*rhsarg)) {
        /* first character is a digit, so RHS is a number
           now check the rest of RHS for validity. 
        */
        for (p = rhsarg + INT_ONE; *p; p++) {
            if (!isdigit(*p)) {
                /* nope, found an illegal character. 
                */
                return ERROR;
            }
        }
        /* nothing wrong, ok to convert 
        */
        parse_num(rhsarg, second_value);
        
        return !ERROR;
    } else {
        /* argument is not a number, so should be a variable 
        */
        varnum2 = to_varnum(*rhsarg);
        if (varnum2 == ERROR || strlen(rhsarg) != INT_ONE) {
            /* nope, not a variable either. 
            */
            return ERROR;
        }
        /* and finally, get that variable's value. 
        */
        do_assign(second_value, vars[varnum2]);
        return !ERROR;
    }
    return ERROR;
}

/****************************************************************/

/* Set the vars array to all zero values
*/
void
zero_vars(int vars[][INTSIZE + INT_ONE]) {
    int i;
    longint_t zero = {LONG_ZERO};
    for (i = 0; i < NVARS; i++) {
        do_assign(vars[i], zero);
    }
    return;
}