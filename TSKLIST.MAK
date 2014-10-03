# Make file for 16-bit
# This is in MAKE syntax!

tsklist.exe:   tsklist.obj
   link  /CO /PM:VIO tsklist,tsklist.exe,,LLIBCE+OS2;

tsklist.obj:  tsklist.c
   cl /W4 /DINCL_16 /AL /Zi /Od /G2s /Fotsklist /c tsklist.c


