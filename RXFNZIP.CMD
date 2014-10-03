del rxfnset.exe
Pkzip rxfnset @rxfnset.zfl
zip2exe rxfnset
del rxfnset.zip

del rxfnsrc.exe
Pkzip rxfnsrc -u rx*.c *.mak *.def *.h
zip2exe rxfnsrc
del rxfnsrc.zip
