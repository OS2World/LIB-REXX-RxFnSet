/****************************************************************************/
/*                                                                          */
/*  File Name:          SW.C                                                */
/*                                                                          */
/*  Author:             Marc Fiammante (France) FIAMMANT at LGEPROFS        */
/*                      Changes for RXFNSET package and 32 bit environment  */
/*                      by Leshek Fiedorowicz CONT06 at LEXVM2              */
/*                                                                          */
/*  Description:        Provides sample TASKLIST  to list tasklist          */
/*                      From REXX                                           */
/*                                                                          */
/*  Entry Points:       RxTaskList    - Lists into rexx stems PID. ENTRY.   */
/*                                                                          */
/*  It work in both Non-PM or in PM sessions.                               */
/*                                                                          */
/****************************************************************************/

#define  INCL_DOS                      /* include macrospace info           */
#define  INCL_WINSWITCHLIST
#include <os2.h>
#define  INCL_RXSHV
#include <rexxsaa.h>                   /* REXXSAA header information        */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef   INCL_16
#define  APIRET        USHORT
#define  acTYPE        SHORT
#define  parTYPE       USHORT
#define  RexxVariablePool RxVar

#else
#define  acTYPE        LONG
#define  parTYPE       ULONG
#endif



INT SetRexxVar(SHVBLOCK RexxVar,PSZ Name,PSZ Value)

{
   INT rc;

   RexxVar.shvcode = RXSHV_SYSET;
   RexxVar.shvret = (UCHAR) 0;
   RexxVar.shvnext = (PSHVBLOCK)0;

   MAKERXSTRING(RexxVar.shvname, Name, strlen(Name));

   MAKERXSTRING(RexxVar.shvvalue, Value, strlen(Value));

   RexxVar.shvvaluelen = strlen(Value);

   rc = RexxVariablePool(&RexxVar);

   return(rc); 
} 


/* tobuf (static) internal function                                         */

static VOID tobuf(                     /* copy RXSTRING to buffer           */
                  PCH b,               /* address of destination buf        */
                  RXSTRING s,          /* string to be copied               */
                  USHORT l)

  /**************************************************************************/
  /* length of destination buf                                              */
  /**************************************************************************/

{                                      /*                                   */
   memset(b, '\0', l);                 /* clear destination buffer          */
 
   if (s.strlength < l)
   {                                   /* if length < buffer size           */
      memcpy(                          /* copy string to buffer             */
        b,                             /*                                   */
        s.strptr,                      /*                                   */
        (unsigned)s.strlength);        /*                                   */
   }                                   /*                                   */
   return ;                            /*                                   */
}                                      /*                                   */

/* List Tasklist                                                            */

APIRET APIENTRY RxTaskList(PSZ func,   /*                                   */
                           USHORT ac,  /*                                   */
                           PRXSTRING av,/*                                  */
                           PSZ que,    /*                                   */
                           PRXSTRING s)/*                                   */
{
   parTYPE Count;
   PSWBLOCK List;
   CHAR VarName[10];
   CHAR Buffer[10];

   Count = WinQuerySwitchList((HAB)NULL, 
                              (PSWBLOCK)NULL, 
                              0);
 
   if (Count > 0)
   {
      parTYPE DataLength;
      SHVBLOCK RexxVar;
      parTYPE i;
      SWENTRY SwEntry;

      DataLength = sizeof(SWBLOCK)+Count *sizeof(SWENTRY);
      List = (PSWBLOCK)malloc((unsigned)DataLength);
      Count = WinQuerySwitchList((HAB)NULL, 
                                 List, 
                                 DataLength);

      /*--------------------------------------------------------------------*/
      /* Now put the number of entries read in entry.0                      */
      /**********************************************************************/

      strcpy(VarName, "ENTRY.0");
      sprintf(Buffer, "%li", (LONG)Count);

      /**********************************************************************/
      /* itoa(Count, Buffer, 10);                                           */
      /**********************************************************************/

      SetRexxVar(RexxVar, VarName, Buffer);
 
      for (i = 0; i < Count; i++)
      {

         SwEntry = List->aswentry[i];   /* This to see entry for the test purposes */

         /*******************************************************************/
         /* store the program title in REXX var ENTRY.i                     */
         /*******************************************************************/

         strcpy(VarName, "ENTRY.");
         sprintf(VarName+strlen(VarName), "%li", (LONG)i+1);
         SetRexxVar(RexxVar, VarName, List->aswentry[i].swctl.szSwtitle);

         /*******************************************************************/
         /* Now store the corresponding PID in rexx var PID.i               */
         /*******************************************************************/

         strcpy(VarName, "PID.");
         sprintf(VarName+strlen(VarName), "%li", (LONG)i+1);
         sprintf(Buffer, "%li", (LONG)List->aswentry[i].swctl.idProcess);
         SetRexxVar(RexxVar, VarName, Buffer);
      }                                /* endfor                            */
      free(List);

      sprintf(Buffer, "%li", (LONG)Count);/* Convert number of entries to   */
      strcpy(VarName, "ENTRY.0");      /* Store it in ENTRY. string         */
      SetRexxVar(RexxVar, VarName, Buffer);     /* element zero and in PID. stem     */
      strcpy(VarName, "PID.0");        /* element zero                      */
      SetRexxVar(RexxVar, VarName, Buffer);     /*                                   */
   } 
 
   else
   {
      fprintf(stderr, "Error in getting switchlist\n");

   }                                   /* endif                             */

   sprintf(s->strptr, "%li", (LONG) Count);
   s->strlength = strlen(s->strptr);   /*                                   */

   return (APIRET)0;

} 



