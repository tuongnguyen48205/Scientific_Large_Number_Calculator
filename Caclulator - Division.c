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
           everything down' from var1 just like when doing long division 
           before assigning this to var1 so that the loop may continue.
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