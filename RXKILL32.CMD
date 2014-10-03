/* Sample program for */
Arg Number
    Call RxFuncDrop 'RXKILLPROCESS'

    Call RxFuncAdd 'RXKILLPROCESS', 'RXFN32', 'RXKILLPROCESS'

    Call RxKillProcess Number

    say 'Return code from kill:'result'.'
    if result \=  0 then say ' See your CP Program Ref. (DosKillProcess) for deteils.';

    Call RxFuncDrop 'RXKILLPROCESS'
Exit
