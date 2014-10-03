/* Sample program for demonstrating RXSETFH function */

    Call RxFuncDrop 'RXTASKLIST'

    Call RxFuncAdd 'RXTASKLIST', 'RXFN16', 'RXTASKLIST'

    Call RxTaskList

       say
       say result' Tasks found.' 
       say
       say '  #   PID     NAME '
       say '---  ----  ----------------';
       do i = 1 to PID.0
         say right(i,3)||right(PID.i,6)'  'ENTRY.i;
       end;

    Call RxFuncDrop 'RXTASKLIST'
Exit
