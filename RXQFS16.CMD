/* Sample program for demonstrating */
Arg Device
    Call RxFuncDrop 'RXQUERYFILESYSTEM'

    Call RxFuncAdd 'RXQUERYFILESYSTEM', 'RXFN16', 'RXQUERYFILESYSTEM'

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