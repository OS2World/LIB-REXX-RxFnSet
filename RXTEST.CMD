/* Sample program for demonstrating RXSETFH function */



Arg Device
    Call RxFuncDrop 'RXFNTEST'

    Call RxFuncAdd 'RXFNTEST', 'RXFN32', 'RXFNTEST'

    Call RxFnTest

    say 'Result= 'Result;

    Call RxFuncDrop 'RXFNTEST'
Exit
