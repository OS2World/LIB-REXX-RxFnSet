/* Sample program for demonstrating RXSETFH function */
Arg Number
    Call RxFuncDrop 'RXSETFH'

    Call RxFuncAdd 'RXSETFH', 'RXFN16', 'RXSETFH'

    Call RXSETFH Number

    select;
      when result = 0 then 
         say Number' of File Handles succesfully allocated.'
      when result = 8 then 
         say 'ERROR - Not enough memory.'
      when result = 87 then do
            say 'ERROR - Invalid parameter ('Number').'
            say '        Specified parameter was not valid number or is less'
            say '        then Number of File Handles already available.'
         end
      Otherwise 
         say 'ERROR - DosSetMaxFH function returned 'result'.'
         say '        Check your Control Program Programming Reference'
         say '        for details.'
    end;

    Call RxFuncDrop 'RXSETFH'
Exit
