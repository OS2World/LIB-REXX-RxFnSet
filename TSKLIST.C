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



/* List Tasklist                                                            */

int main()

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

 
      for (i = 0; i < Count; i++)
      {

         SwEntry = List->aswentry[i];   /* This to see entry for the test purposes */

         /*******************************************************************/
         /* store the program title in REXX var ENTRY.i                     */
         /*******************************************************************/

         printf("%5.5li %s \n", (LONG)List->aswentry[i].swctl.idProcess,List->aswentry[i].swctl.szSwtitle);

      }                                /* endfor                            */
      free(List);

   } 
 
   else
   {
      printf("%s", "Error in getting switchlist\n");

   }                                   /* endif                             */


   return 0;

} 



