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