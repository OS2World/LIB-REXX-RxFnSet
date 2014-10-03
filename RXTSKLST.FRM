----- REXXOS2 FORUM appended at 17:42:59 on 92/02/04 GMT (by FIAMMANT at LGEVM2)
Subject: Stopping a process - how to identify rexx program ?
    Ref: Append at 15:49:59 on 92/02/04 GMT (by CONT06 at LEXVM2)
Warning : Long append

Here is a sample C rexx callable function which returns the task list
contents in Rexx variables. ENTRY.0 contains the number of entries
Entry.i contains the task list title for entry i where i goes from 1
to entry.0 , pid.i contains the pid of that entry.

This function must be compiled in a DLL and RxFuncAdd must have been
called to add it to known REXX functions.

It work in both Non-PM or in PM sessions.

/*********************************************************************/
/*                                                                   */
/*  File Name:          SW.C                                         */
/*                                                                   */
/*  Description:        Provides sample LISTTASKS to list tasklist   */
/*                      From REXX                                    */
/*                                                                   */
/*  Entry Points:       LISTTASKS     - Lists into rexx vars         */
/*********************************************************************/

#define INCL_DOS                       /* include macrospace info    */
#define INCL_WINSWITCHLIST
#include <os2.h>
#define INCL_RXSHV
#include <rexxsaa.h>                   /* REXXSAA header information */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETREXXVAR(Name,Value) \
        RexxVar.shvnext           =(struct shvnode far *)NULL; \
        RexxVar.shvname.strptr    =(PCH)VarName; \
        RexxVar.shvname.strlength =strlen((PSZ)(Name)); \
        RexxVar.shvnamelen        =RexxVar.shvname.strlength; \
        RexxVar.shvvalue.strlength=strlen((Value)); \
        RexxVar.shvvalue.strptr   =(Value); \
        RexxVar.shvvaluelen       =RexxVar.shvvalue.strlength;  \
        RexxVar.shvcode=RXSHV_SET; \
        RxVar((PSHVBLOCK)&RexxVar);
/*tobuf (static) internal function */
static VOID tobuf(b,s,l)               /* copy RXSTRING to buffer    */
PUCHAR b;                              /* address of destination buf */
RXSTRING s;                            /* string to be copied        */
USHORT l;                              /* length of destination buf  */
  {                                    /*                            */
  memset(b,'\0',l);                    /* clear destination buffer   */
  if (s.strlength < l) {               /* if length < buffer size    */
    memcpy(                            /* copy string to buffer      */
        b,                             /*                            */
        s.strptr,                      /*                            */
        s.strlength);                  /*                            */
    }                                  /*                            */
  return;                              /*                            */
  }                                    /*                            */
/* List Tasklist         */
SHORT APIENTRY ListTasks(PSZ func, USHORT ac, PRXSTRING av, PSZ que, PRXSTRING s
  {
   int rc;
   USHORT Count;
   PSWBLOCK List;
   CHAR     VarName[10];
   CHAR     Buffer[10];
   Count = WinQuerySwitchList((HAB)NULL,(PSWBLOCK)NULL,0);
   if (Count>0) {
        USHORT DataLength;
        SHVBLOCK RexxVar;
        int i;
        DataLength=sizeof(SWBLOCK)+Count*sizeof(SWENTRY);
        List=(PSWBLOCK)malloc(DataLength);
        Count = WinQuerySwitchList((HAB)NULL,List,DataLength);
        /*--------------------------------------------------------*/
        /* Now put the number of entries read in entry.0        */
        strcpy(VarName,"ENTRY.0");
        itoa(Count,Buffer,10);
        SETREXXVAR(VarName,Buffer);
        for (i=0;i<Count ;i++ ) {
            /* store the program title in REXX var ENTRY.i */
            strcpy(VarName,"ENTRY.");
            itoa(i+1,VarName+strlen(VarName),10);
            SETREXXVAR(VarName,List->aswentry[i].swctl.szSwtitle);
            /* Now store the corresponding PID in rexx var PID.i */
            strcpy(VarName,"PID.");
            itoa(i+1,VarName+strlen(VarName),10);
            itoa(List->aswentry[i].swctl.idProcess,Buffer,16);
            SETREXXVAR(VarName,Buffer);
        } /* endfor */
   } else {
      fprintf(stderr,"Error in getting switchlist\n");
   } /* endif */
   rc = 0;                            /* no errors in call           */
   itoa(rc,sel->strptr,10);         /*                               */
   sel->strlength=strlen(sel->strptr);/*                             */
   return rc;

}
Hope this helps
Marc Fiammante

