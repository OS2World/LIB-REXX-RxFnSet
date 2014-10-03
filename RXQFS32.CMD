/* Sample program for demonstrating */

say 
say 'I am sorry but, because of DosQueryFSAttach CP function does not'
say '  work properly in full 32 bit environment, RxQueryFileSystem '
say '  function will always return empty string - error, just like'
say '  Kernel function returns me an error.  Hope it will work with '
say '  the next release of ... Toolkit ?  System ? .... '.
say '  Sorry for any inconvenience.'
say 'Leshek'
exit








Arg Device
    Call RxFuncDrop 'RXQUERYFILESYSTEM'

    Call RxFuncAdd 'RXQUERYFILESYSTEM', 'RXFN32', 'RXQUERYFILESYSTEM'

    Call RxQueryFileSystem Device

    if (Length(Result) = 0) then do
            say 'ERROR - Check your parameter ('Device').'
            say '        D: is expected, where D - device (disk) letter followed by colon.'
         end
    else
       say 'File System for 'Device' is 'Result'.'


    Call RxFuncDrop 'RXQUERYFILESYSTEM'
Exit
