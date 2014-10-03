/* Sample program for demonstrating RXSETFH function */



Arg Device
    Call RxFuncDrop 'RXGETFILENAME'

    Call RxFuncAdd 'RXGETFILENAME', 'RXFN32', 'RXGETFILENAME'

    Call RxGetFileName 

    say 'PID = 'Result;

    Call RxFuncDrop 'RXGETFILENAME'
Exit
