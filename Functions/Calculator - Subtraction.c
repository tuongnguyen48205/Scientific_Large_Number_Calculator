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
