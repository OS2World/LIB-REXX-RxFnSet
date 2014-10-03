# Leshek Fiedorowicz Feb-02-92 Make file for 32-bit RXSETFH
# This is in NMAKE syntax!
CLOPT=/DINCL_32 /Ge- /c

rxfn32.dll:   rxfh32.obj   \
              rxfn32.def   \
              rxfn32.mak   \
              rxkill32.obj \
              rxwcrd32.obj \
              rxqfs32.obj  \
              rxtlst32.obj \
              rxfntest.obj
   link386 /pmtype:VIO /CO rxfh32    \
                          +rxkill32  \
                          +rxwcrd32  \
                          +rxqfs32   \
                          +rxtlst32  \
                          +rxfntest  \
                          ,rxfn32.dll,,REXX.lib,rxfn32

rxfh32.obj:  rxsetfh.c 
   icc $(CLOPT) /Forxfh32 /Ti+ rxsetfh.c

rxkill32.obj:  rxkill.c
   icc $(CLOPT) /Forxkill32 /Ti+ rxkill.c

rxwcrd32.obj:  rxwcard.c 
   icc $(CLOPT) /Forxwcrd32 /Ti+ rxwcard.c

rxqfs32.obj:  rxqfs.c 
   icc $(CLOPT) /Forxqfs32 /Ti+ rxqfs.c

rxtlst32.obj:  rxtsklst.c 
   icc $(CLOPT) /Forxtlst32 /Ti+ rxtsklst.c

rxfntest.obj:  rxfntest.c 
   icc $(CLOPT) /Forxfntest /Ti+ rxfntest.c

