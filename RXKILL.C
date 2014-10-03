/****************************************************************************/
/*                                                                          */
/*  IBM INTERNAL USE ONLY                                                   */
/*  Name: RXKILL.C                                                         */
/*                                                                          */
/*  Author: Leshek Fiedorowicz Feb-01-1992                                  */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RXKILLPROCESS                                         */
/*                                                                          */
/*  Description:      REXX external function to kill proces by PID          */
/*                                                                          */
/*  Entry Point:      RXKILLPROCESS                                         */
/*                                                                          */
/*  Parameters accepted: - Process ID - decimal number                      */
/*                                                                          */
/*  Return Codes:        - 0  - operation succesfully completed             */
/*                         13 - ERROR_INVALID_DATA                          */
/*                         303- ERROR_INVALID_PROCID                        */
/*                         305- ERROR_NOT_DESCENDANT                        */
/*                                                                          */
/*  Known problems:      - None                                             */
/*                                                                          */
/****************************************************************************/

#define  INCL_BASE
#define  INCL_REXXSAA
#define  INCL_DOSFILEMGR
#include <os2.h>
#include <rexxsaa.h>   
#include <string.h>    
#include <stdio.h>     
#include <stdlib.h>

#ifdef   INCL_16
#include <dos.h>
#define  APIRET        USHORT
#define  acTYPE        SHORT
#define  parTYPE       USHORT

#else
#define  acTYPE        LONG
#define  parTYPE       ULONG
#pragma  linkage       (REXXDUMP, system)
#endif

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Function Name:      RXKILLPROCESS                                       */
/*                                                                          */
/*  Description:      REXX external function to kill proces by PID          */
/*                                                                          */
/*  Notes:              exported function                                   */
/*                                                                          */
/*  Entry Point:        RXSETFH(f,ac,av,q,s)                                */
/*                                                                          */
/*  Parameters:         f  - name of function called (ignored)              */
/*                      ac - argument count                                 */
/*                      av - list of argument strings                       */
/*                      q  - name of current active queue (ignored)         */
/*                      s  - pointer for return of RXSTRING                 */
/*                                                                          */
/*  Returns:            last rc from DosKillProcess                         */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

APIRET APIENTRY RXKILLPROCESS(PSZ f,acTYPE ac,PRXSTRING av,PSZ q,PRXSTRING s)/*   
                                          name function called as argument  
                                          count argument string list current
                                          queue name return string          */

{                                      /*                                   */
   ULONG rc;
   PID Pid;                            /* Requested Number of Handles       */
   BOOL False = FALSE;                 /* Dummy loop control variable       */
   int  avidx;                         /* Index for parameter list element  */ 
 
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
 

      if (ac != 1)                     /* Only one argument is accepted     */
      {                                /* If not one - error                */
         rc = ERROR_INVALID_DATA;
         break;                        /* --> return                        */
      }                                /* endif                             */
 
      avidx = ac - 1;                  /* Tbl. index starts form zero */

      if (av[avidx].strlength < 1)        /* String has to to be of length > 0 */
      {                                /* if it isn't - error               */
         rc = ERROR_INVALID_DATA;
         break;                        /* --> return                        */
      }                                /* endif                             */

      Pid = (PID)atoi(av[avidx].strptr);
 
      rc = (LONG)DosKillProcess(1, Pid);/* Kill Process (that one only) */

   } while (False);                    /* enddo                             */

   sprintf(s->strptr, "%lu", rc);      /* Set return value                  */
   s->strlength = strlen(s->strptr);

   return (APIRET)0;
} 


