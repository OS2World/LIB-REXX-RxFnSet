# Leshek Fiedorowicz Feb-02-92 Make file for 16-bit RXFNSET
# This is in NMAKE syntax!

CLOPT=-DINCL_16 -Alfu -G2s -W4 -MD -Zi -Od -c 

rxfn16.dll:   rxfh16.obj   \
              rxfn16.def   \
              rxkill16.obj \
              rxwcrd16.obj \
              rxqfs16.obj  \
              rxtlst16.obj
   link  /CO  rxfh16\
             +rxkill16\
             +rxwcrd16\
             +rxqfs16\
             +rxtlst16\
             ,rxfn16.dll,,REXX+LLIBCDLL+OS2,rxfn16

rxfh16.obj:  rxsetfh.c
   cl $(CLOPT) /Forxfh16 rxsetfh.c

rxkill16.obj:  rxkill.c
   cl $(CLOPT) /Forxkill16 rxkill.c

rxwcrd16.obj:  rxwcard.c
   cl $(CLOPT) /Forxwcrd16 rxwcard.c

rxqfs16.obj:  rxqfs.c
   cl $(CLOPT) /Forxqfs16 rxqfs.c

rxtlst16.obj:  rxtsklst.c
   cl $(CLOPT) /Forxtlst16 rxtsklst.c

