/****************************************************************************/
/*                                                                          */
/*  IBM INTERNAL USE ONLY                                                   */
/*  Name: RxQFS.C                                                           */
/*                                                                          */
/*  Author: Leshek Fiedorowicz Feb-01-1992                                  */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RxQueryFIleSystem                                     */
/*                                                                          */
/*  Description:      REXX external function to kill proces by PID          */
/*                                                                          */
/*  Entry Point:      RxQureyFIleSystem                                     */
/*                                                                          */
/*  Parameters accepted: -                                                  */
/*                                                                          */
/*  Return Codes:        - HPFS, FAT ,                                      */
/*                         '' - empty string if any error (ivalid drive...) */
/*                                                                          */
/*  Known problems:      - None                                             */
/*                                                                          */
/****************************************************************************/

#define  INCL_BASE
#define  INCL_REXXSAA
#define  INCL_DOSFILEMGR
#define  INCL_WINSWITCHLIST
#define  INCL_DOSPROCESS     /* Process and thread values */
#include <os2.h>
/* #include <bsetib.h>  */       /* Thread Information Block and
                                   Process Information Block */

#include <rexxsaa.h>   
#include <string.h>    
#include <stdio.h>     
#include <stdlib.h>

PID GetPID(VOID);

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Function Name:      RxQueryFIleSystem                                   */
/*                                                                          */
/*  Description:      REXX external function to obtine File System Type     */
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
/*  Returns:            HPFS, FAT                                           */
/*                      '' - Empty String in case of any error              */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

APIRET APIENTRY                        /*                                   */
RxGetFileName(                         /*                                   */
                  PSZ f,               /* name function called as argument  */
                  ULONG ac,            /* argument count                    */
                  PRXSTRING av,        /* argument string list              */
                  PSZ q,               /* current queue name                */
                  PRXSTRING s)         /* return string                     */

{                                      /*                                   */
   ULONG CurentPID;
   BOOL False = FALSE;                 /* Dummy loop control variable       */


   s->strptr[0] = '\0';                /* Initilia return value is set to   
                                          empty string                      */
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
 
      if (ac != 0)                     /* Only one argument is accepted     */
      {                                /* If not one - error                */
         break;                        /* --> return                        */
      }                                /* endif                             */


   CurentPID = GetPID();


   } while (False); /* Do it only once */

   sprintf(s->strptr,"%li",(ULONG)CurentPID);
   s->strlength = strlen(s->strptr);

   return (APIRET)0;

   }

 
/****************************************************************************

 This example returns the address of the Thread 
 Information Block (TIB) of the current thread.  It 
 also returns the address of the Process 
 Information Block (PIB) of the current process.  
 The calling thread can subsequently browse 
 either control block. 

 HERE: Used to get current process id

 ****************************************************************************/
 

PID GetPID(VOID)

{
 
 PTIB   *pptib;      /* Address of a pointer to the
                        Thread Information Block */
 PPIB   *pppib;      /* Address of a pointer to the
                        Process Information Block */
 ULONG  rc;          /* Return code */

 PIB p;
 
    rc = DosGetInfoBlocks(pptib, pppib);
                    /* On successful return, the variable pptib */
                    /*   contains the address of the TIB, and   */
                    /*   the variable pppib contains the        */
                    /*   address of the PIB                     */
 
    if (rc != 0) /* Theoretically it doesn't return any codes   */
      {
        printf("DosGetInfoBlocks error: return code = %ld", rc);
        return (PID) NULL;
      }


 /* return (*pppib)->pib_s.pib_ulpid; */
 return 0L;
 
}










