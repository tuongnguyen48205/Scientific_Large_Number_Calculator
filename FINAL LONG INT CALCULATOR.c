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

/*****************************************************************
******************************************************************

Your answer to the assignment should start here, using your new
typedef defined at the top of the program. The next few functions
will require modifications because of the change of structure
used for a long_int, and then you'll need to start adding whole
new functions after you get these first ones working properly.
Try and make the new functions fit the style and naming pattern
of the existing ones, ok?

******************************************************************
*****************************************************************/

/* Create an internal-format number out of a string by placing
   placing the number of digits of the number in index 0 and
   each digit of the number in the subsequent indexes in the
   reverse order. For example, for number 1234, in the array, it
   should appear as 4 4 3 2 1.
*/
void
parse_num(char *rhs, longint_t rhsval) {
    int length = strlen(rhs); 
    char digit[INT_ONE];
    
    /* If the length of the string is over INTSIZE, return an error
       and exit. 
    */
    if (length > INTSIZE) {
        print_error("RHS argument is too large.");
        exit(EXIT_FAILURE);
    }
    
    /* Time to place the rest of the digits in the number into the register
       in reverse order.
    */
    for(int i = 1; i <= length; i++) {
        digit[INT_ZERO] = rhs[length - i];
        rhsval[i] = atoi(digit);
    }    
    
    /* Now remove leading zeroes and store the (current) number of digits
       in the register's first slot.
    */
    rhsval[INT_ZERO] = count_length(rhsval);
}

/****************************************************************/

/* Print out a longint value
*/
void
do_print(int varnum, longint_t var) {   

    printf("register %c: ", varnum+CH_A);
    
    /* If the variable has no register, the default value is 0. 
    */
    if (var[INT_ZERO] == INT_ZERO) {
        printf("%d", INT_ZERO);
    }
        
    /* The following is responsible for actually printing the variable
       number as well as placing commas in the appropriate locations.
    */      
    for (int i = var[INT_ZERO]; i > INT_ZERO; i--) {
        if (i % INT_THREE == INT_ZERO && i != var[INT_ZERO]) {
            printf(",%d", var[i]);
        }
        else {
            printf("%d", var[i]);
        }
    }
    
    /* Now print new line character for next function call. 
    */
    printf("\n");
}

/****************************************************************/

/* Assign a longint value, could do this with just an assignment
   statement, because structs can be assigned, but this is more
   elegant, and only copies over the array elements (digits) that
   are currently in use: var1 = var2.
*/
void
do_assign(longint_t var1, longint_t var2) {
    for (int i = 0; i <= INTSIZE; i++) {
        var1[i] = var2[i];
    }
}

/****************************************************************/

/* Update the indicated variable var1 by doing an addition
   using var2 to compute var1 = var1 + var2
*/
void
do_plus(longint_t var1, longint_t var2) {
    /* check which of the two variables is larger. 
    */
    int larger_num = var1[INT_ZERO];
    if (check_if_var2_bigger(var1, var2) == TRUE) {
        larger_num = var2[INT_ZERO];
    }
    
    /* Time to actually do the addition and deal with integer overflow.
       To save time, this only needs to be looped through 'the number of
       digits of the larger number' times, else it'll keep adding 0 to the 
       following digit which is redundant.
    */
    for (int j = 1; j <= larger_num + INT_ONE; j++) {
        var1[j] += var2[j];
        /* Each array index can only contain one digit so if it goes over
           ten, add one to the next number to be added and reduce it so that
           it only contains one digit instead of two. Also, the resultant
           number after addition can be at most only one digit larger than
           the larger number between var1 and var2 so if this happens and
           either var1 or var2 happen to be INTSIZE digits long, this would
           lead to integer overflow.
        */
        if (var1[j] >= INT_TEN) {
            if (j == INTSIZE) {
                print_error("This operation leads to integer overflow.");
                exit(EXIT_FAILURE);
            }
            var1[j] -= INT_TEN;
            var2[j + INT_ONE] += INT_ONE;
        }
    } 
    
    /* Now find out how long the resultant number is.
    */
    var1[INT_ZERO] = count_length(var1); 
}

/*****************************************************************
******************************************************************

Put your new functions below this line. Make sure you add suitable
prototypes at the top of the program.

******************************************************************
*****************************************************************/

/* Update the indicated variable var1 by doing a multiplication
   using var2 to compute var1 = var1 * var2
*/
void 
do_multiply(longint_t var1, longint_t var2) {
    int i, j, digit, length;
    int carry = 0;
    int *larger_var, *smaller_var;

    /* anything multiplied by zero is zero.
    */
    if (var2[INT_ZERO] == INT_ONE && var2[INT_ONE] == INT_ZERO) {
        var1[INT_ZERO] = INT_ONE;
        var1[INT_ONE] = INT_ZERO;
        return;
    }

    /* find the number that has the smaller number of digits and get
       its length. This will make the multiplication more efficient.
    */
    if (check_if_var2_bigger(var1, var2) == TRUE) {
        smaller_var = var1;
        larger_var = var2;
    }
    else {
        smaller_var = var2;
        larger_var = var1;
    }
    int smaller_length = smaller_var[INT_ZERO];
    
    /* When doing long multiplication, you multiply each digit of one number
       by each digit of the other number and then add up the multiplicands to
       get the overall multiplication of the two numbers. The following 2D array
       stores these multiplicands that need to be added together later.
    */
    int multiplicand[smaller_length + INT_ONE][INTSIZE + INT_ONE];
    
    /* set everything to zero in the multiplicand array.
    */
    longint_t zero = {LONG_ZERO};  
    for (int k = 0; k <= smaller_length; k++) {
        do_assign(multiplicand[k], zero);
    }
    
    /* When doing long multiplication, you shift each multiplicand one to 
       the left for each digit of the multiplier. The following is used 
       to do that.
    */
    int increase_by_one = -1; 
    
    /* Do the long multiplication. In long multiplication if a result  
       contains more than one digit, we carry over the leading digit and
       add it to the next result of the multiplication of the following 
       digit.   
    */
    for (i = 1; i <= smaller_length; i++) {
        increase_by_one++;
        for (j = 1; j <= larger_var[INT_ZERO] + INT_ONE; j++) {
            digit = smaller_var[i] * larger_var[j];
            digit += carry;
            carry = 0;          
            carry = digit / INT_TEN;
            digit %= INT_TEN;
            multiplicand[i - INT_ONE][j + increase_by_one] = digit;
        }

        /* deal with integer overflow and find the length of each
           multiplicand. If the length of any of the multiplicands
           is greater than INT_SIZE, when you add them together, 
           they will also be greater than INT_SIZE leading to integer
           overflow.
        */
        length = count_length(multiplicand[i - INT_ONE]);
        if (length < INT_ZERO || length > INTSIZE) {
            print_error("This operation leads to integer overflow.");
            exit(EXIT_FAILURE);
        }
        else {
            multiplicand[i - INT_ONE][INT_ZERO] = length;
        }
    } 
    
    /* Set var1 to be zero so that the result can be placed there. 
    */
    do_assign(var1, zero);
    var1[INT_ZERO] = INT_ONE;
     
    /* Now add up everything in multiplicand to get the final result of
       the multiplication and set it to var1.
    */
    for (j = 0; j < smaller_length; j++) {
        do_plus(var1, multiplicand[j]);
    }
} 

/****************************************************************/

/* Checks if the var2 variable is larger than the var1 variable. Returns
   True if var2 is larger and returns False if var1 is larger using a flag.
*/
int 
check_if_var2_bigger(longint_t var1, longint_t var2) {
    int var_2_is_bigger = FALSE;
    
    /* If var2 has more digits than var1, it is larger than var1. 
    */
    if (var2[INT_ZERO] > var1[INT_ZERO]) {
        var_2_is_bigger = TRUE;
        return var_2_is_bigger;
    }
    /* If they have the same number of digits, loop through each digit to
       determine which one is larger. 
    */
    else if (var2[INT_ZERO] == var1[INT_ZERO]) {
        for (int i = var2[0]; i > INT_ZERO; i--) {
            if (var2[i] > var1[i]) {
                var_2_is_bigger = TRUE;
                return var_2_is_bigger;
            }
            else if (var2[i] == var1[i]) {
                 continue;
            }
            else {
                return var_2_is_bigger;
            }
        }
        return var_2_is_bigger;
    }
    /* If var2 does not have more than or equal number of digits
       to var1, then var1 has more digits so var1 is larger. 
    */
    else {
        return var_2_is_bigger;       
    }
}

/****************************************************************/

/* Update the indicated variable var1 by doing a exponentiation
   using var2 to compute var1 = var1 ^ var2.
*/
void 
do_power(longint_t var1, longint_t var2) {
    /* anything to the power of zero is one.
    */
    if ((var2[INT_ZERO] == INT_ONE || var2[INT_ZERO] == INT_ZERO)
        && var2[INT_ONE] == INT_ZERO) {
        var1[INT_ZERO] = INT_ONE;
        var1[INT_ONE] = INT_ONE;
        return;
    }
    
    /* zero to the power of anything other than zero is zero and one to the
       power of anything is one.
    */
    if ((var1[INT_ZERO] == INT_ONE || var1[INT_ZERO] == INT_ZERO)
        && var1[INT_ONE] == INT_ZERO) {
        return;
    }
    else if (var1[INT_ZERO] == INT_ONE && var1[INT_ONE] == INT_ONE) {
        return;
    }
    
    /* It isn't possible to have a power greater than 1660 so deal with 
       this now for efficiency.
    */
    longint_t max_power = {LONG_ZERO};
    max_power[INT_ZERO] = INT_FOUR;
    max_power[INT_ONE] = INT_ZERO;
    max_power[INT_TWO] = INT_SIX;
    max_power[INT_THREE] = INT_SIX;
    max_power[INT_FOUR] = INT_ONE;
    
    if (check_if_var2_bigger(max_power, var2) == TRUE) {
        print_error("This operation leads to integer overflow.");
        exit(EXIT_FAILURE);
    }
    
    /* Exponentiation can be done through repeated multiplication. For
       example, var1^3 is var1 multiplied by var1 3 times. However, as the
       multiplications happen, var1 is altered and so temp is used to store
       the original var1.
    */
    longint_t temp;
    do_assign(temp, var1);
    
    /* Do the repeated multiplication var2 number of times. var2 is 
       reduced by one each time in the cycle until it is one.
    */
    while (TRUE) {
        longint_t one = {LONG_ZERO};
        one[INT_ZERO] = INT_ONE;
        one[INT_ONE] = INT_ONE;
        if (var2[INT_ZERO] == INT_ONE && var2[INT_ONE] == INT_ONE) {
            break;
        }
        else {
            do_minus(var2, one);
            /* No need to place length of the resultant number in index
               zero since the do_multiplication function already does this.
            */
            do_multiply(var1, temp);
        }
    }

    /* Now to deal with integer overflow.
    */
    if ((var1[INT_ZERO] == INT_ONE || var1[INT_ZERO] == INT_ZERO)
        && var1[INT_ONE] == INT_ZERO) {
        print_error("This operation leads to integer overflow.");
        exit(EXIT_FAILURE);
    }
}


/****************************************************************/

/* Update the indicated variable var1 by doing a subtraction
   using var2 to compute var1 = var1 - var2. THis function will be used
   for the exponentiation and division functions.
*/
void 
do_minus(longint_t var1, longint_t var2) {
    /* no need to deal with possible integer overflow since subtraction can
       only decrease the size of the number. But deal with case where 
       subtraction leads to a negative number. This happens if var2 is larger
       than var1.
    */
    if (check_if_var2_bigger(var1, var2) == TRUE) {
        return;
    }
    else {
        /* Do the actual subtraction using long subtraction.
        */       
        for (int i = 1; i <= var1[INT_ZERO]; i++) {
            if (i == INTSIZE) {
                break;
            }
            var1[i] -= var2[i];
            if (var1[i] < INT_ZERO) {
                var1[i] += INT_TEN;
                var2[i + INT_ONE] += INT_ONE;
            }
        }

        /* Now to find the length of the new number.
        */
        var1[INT_ZERO] = count_length(var1);
    }
} 


/****************************************************************/

/* Update the indicated variable var1 by doing a division
   using var2 to compute var1 = var1 / var2.
*/
void 
do_division(longint_t var1, longint_t var2) {
    /* no need to deal with possible integer overflow since division can
       only decrease size of number. But deal with division by zero case.
    */
    if ((var2[INT_ZERO] == INT_ONE || var2[INT_ZERO] == INT_ZERO) 
        && var2[INT_ONE] == INT_ZERO) {
        print_error("Cannot divide by zero.");
        exit(EXIT_FAILURE);
    }
    
    /* If the numerator is smaller than the denominator, the result 
       would be 0 in integer division.
    */
    if (check_if_var2_bigger(var1, var2) == TRUE) {
        for (int i = 1; i <= var1[INT_ZERO]; i++) {
            var1[i] = INT_ZERO;
        }
        var1[INT_ZERO] = INT_ONE;
        return;
    }
    
    /* Any number divided by one would not have its value changed.
    */
    if (var2[INT_ZERO] == INT_ONE && var2[INT_ONE] == INT_ONE) {
        return;
    }    
    
    /* Store the answer to the division seperately since we need to 
       work with var1 which will altered in the process.
    */
    longint_t answer = {LONG_ZERO};
    /* Keep track of how long the answer is using answer_index. In
       long division, if the division has no remainder, it is considered
       to be 'perfect' so perfect zero keepts track of this.
    */
    int answer_index = 0; 
    int perfect_zero = 0;
    int shift = FALSE;
    
    /* In long division, as the division happens, var1 will slowly get
       smaller so while var1 is larger than var2, the division can occur.
       Eventually when var1 becomes smaller than var2, this would lead to
       a decimal which is ignored in integer division.
    */
    while (check_if_var2_bigger(var1, var2) == FALSE) {
        /* Now to do the actual division. Start by getting the first few
           digits of the numerator or var1 in this case. In long division,
           you begin the division by dividing using the front numbers.
        */
        longint_t numerator = {LONG_ZERO};
        numerator[INT_ZERO] = var2[INT_ZERO];
        int tracker = 0, j;
        for (j = 1; j <= numerator[INT_ZERO] ; j++) {
            numerator[numerator[INT_ZERO] - j + INT_ONE] = 
            var1[var1[INT_ZERO] - tracker];
            tracker += INT_ONE;
        }

        /* If numerator is still smaller than the denominator after 
           grabbing the front few numbers of var1, one more number needs
           to be grabbed to ensure that the numerator is larger than the
           denominator.
        */
        if (check_if_var2_bigger(numerator, var2) == TRUE) {
            shift = TRUE;
            numerator[INT_ZERO] += INT_ONE;
            for (int k = numerator[INT_ZERO]; k > INT_ONE; k--) {
                numerator[k] = numerator[k - INT_ONE];
            }
            numerator[INT_ONE] = var1[var1[INT_ZERO] - tracker];         
        }
        
        /* Now use subtraction to see how many times the denominator fits
           inside the first couple digits of the numerator.
        */   
        int counter = 0;
        longint_t denominator = {LONG_ZERO};
        int numerator_length = numerator[INT_ZERO];
        while (check_if_var2_bigger(numerator, var2) == FALSE) {
            do_assign(denominator, var2);
            do_minus(numerator, denominator);
            counter++;
        }
        
        /* Place this answer into the answer array and change the length
           of the answer accordingly.
        */
        int answer_len = 0;
        int temp_counter = counter;       
        while (temp_counter > INT_ZERO) {
            temp_counter /= INT_TEN;
            answer_len++;
        }      
        for (int l = answer_len; l > INT_ZERO; l--) {
            answer[answer_index + l] = counter % INT_TEN;
            counter /= INT_TEN;
        }
        answer_index += answer_len;
        
        /* In long division, if the numerator perfectly divides like 
           afforementioned, everything needs to be shifted one to the right
           (opposite of long multiplication).
        */
        if ((numerator[INT_ZERO] == INT_ZERO || 
        numerator[INT_ZERO] == INT_ONE) && numerator[INT_ONE] == INT_ZERO) {
            if (perfect_zero % INT_TWO == INT_ZERO) {
                answer_index--;
            }
            else {
                answer_index++;
            }
            perfect_zero++;
        }
        
        /* Because numerator was used in the do_minus function before, it
           had its length altered but we want it to keep its original length
           before the minuses happened.
        */
        numerator[INT_ZERO] = numerator_length;
 
        /* This final part uses the remainder after the division and 'brings
           everything down' from var1 just like you would when doing long 
           division before assigning this to var1 so that the loop may continue.
        */
        int difference = var1[INT_ZERO] - numerator[INT_ZERO];
        for (int o = numerator[INT_ZERO]; o > INT_ZERO; o--) {
            numerator[o + difference] = numerator[o];
            numerator[o] = INT_ZERO;
        }                      
        for (int p = difference; p > INT_ZERO; p--) {
            numerator[p] = var1[p];
        }
        numerator[INT_ZERO] = var1[INT_ZERO];
        do_assign(var1, numerator);
        var1[INT_ZERO] = count_length(var1);
    }
    
    /* Now to reorder the answer since it was put in non reverse order and now
       we want it in reverse order so that it becomes a longint. If the answer
       was not shifted, we need to add one more to answer_index.
    */
    if (shift == FALSE) {
        answer_index += 1;
    }
    longint_t final_answer = {LONG_ZERO};
    final_answer[INT_ZERO] = answer_index;
    int q = 1;
    for (int n = answer_index; n > INT_ZERO; n--) {
        final_answer[q] = answer[n];
        q++;
    }
    
    /* Now put everything back to var1. 
    */
    do_assign(var1, final_answer);
} 

/****************************************************************/

/* This function counts how many digits are present in the longint
   and returns this number.
*/
int count_length(longint_t var) {
    int counter = 0;
    /* Start counting from the right hand side at INT_ZERO. Since
       everything was set to zero at the beginning, everything on the
       right hand side of the array should be zero, each time it notices
       a zero, the counter will increase. However, if it runs into a 
       non zero number, it means that the actual longint number begins
       here. To get the length of the longint number, just minus the 
       largest number of digits possible, INTSIZE, by the number of 
       zeros encountered.
    */
    for (int j = INTSIZE; j > 0; j--) {
        if (var[j] != INT_ZERO) {
            return INTSIZE - counter;
        }
        else {
            counter++;
        }
    }

    /* If the function does not return by this point, it means that
       variable is 0.
    */
    return INTSIZE - counter;
}

/*algorithms is fun! 
*/