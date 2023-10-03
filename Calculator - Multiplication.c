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
       get the overall multiplication of the two numbers. The following 2D 
       array stores these multiplicands that need to be added together later.
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