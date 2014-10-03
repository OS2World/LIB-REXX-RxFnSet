/****************************************************************************/
/*                                                                          */
/*  IBM INTERNAL USE ONLY                                                   */
/*  Name: RXSETFH.C                                                         */
/*                                                                          */
/*  Author: Leshek Fiedorowicz Feb-01-1992                                  */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RXSETFH                                               */
/*                                                                          */
/*  Description:      REXX external function to change number of File       */
/*                    Handles assigned to the REXX process for OS/2 1.x 2.x */
/*                                                                          */
/*  Entry Point:      RXSETFH(n)                                            */
/*                                                                          */
/*  Parameters accepted: - Number of Requested File Handles                 */
/*                                                                          */
/*  Return Codes:        - 0  - operation succesfully completed             */
/*                         8  - Not Enought memory                          */
/*                         87 - Invalid parameter                           */
/*                                                                          */
/*  Known problems:      - None                                             */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RXADDFH                                               */
/*                                                                          */
/*  Description:      REXX external function to add number of File       */
/*                    Handles assigned to already allocated for process for */
/*                    OS/2 2.x environment                                  */
/*                                                                          */
/*  Entry Point:      RXADDFH(n)                                            */
/*                                                                          */
/*  Parameters accepted: - Number of File Handles to add                 */
/*                                                                          */
/*  Return Codes:        - Number of Allocated File Handles                 */
/*                         0  - if unsuccesfull operation or */
/*                              parameter error */
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
#endif

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Function Name:      RXSETFH                                             */
/*                                                                          */
/*  Description:      REXX external function to change number of File       */
/*                    Handles assigned to the REXX process for 32 bit       */
/*                    OS/2 2.x environment                                  */
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
/*  Returns:            last rc from DosSetMaxFH                       */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

APIRET APIENTRY RXSETFH(PSZ f,acTYPE ac,PRXSTRING av,PSZ q,PRXSTRING s)/*   
                                          name function called as argument  
                                          count argument string list current
                                          queue name return string          */

{                                      /*                                   */
   ULONG rc;
   parTYPE NumberHandles;              /* Requested Number of Handles       */
   BOOL False = FALSE;                 /* Dummy loop control variable       */
   int  avidx;                         /* Index for parameter list element  */ 
 
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
      char tx[255];

      if (ac != 1)                     /* Only one argument is accepted     */
      {                                /* If not one - error                */
         rc = ERROR_INVALID_PARAMETER;
         break;                        /* --> return                        */
      }                                /* endif                             */
 
      avidx = ac - 1;                  /* Tbl. index starts form zero */

      if (av[avidx].strlength < 1)        /* String has to to be of length > 0 */
      {                                /* if it isn't - error               */
         rc = ERROR_INVALID_PARAMETER;
         break;                        /* --> return                        */
      }                                /* endif                             */
      memset(tx,'\0',sizeof(tx));
      memcpy(tx,av[avidx].strptr,(int) av[avidx].strlength);
      NumberHandles = (parTYPE)atoi(tx);
 
      if (NumberHandles < 2)           /* Number of requested handles has   */
      {                                /* to be at least 1                   */
         rc = ERROR_INVALID_PARAMETER; /* if it isn't - error               */
         break;                        /* --> return                        */
      }                                /* endif                             */
      rc = (LONG)DosSetMaxFH(NumberHandles);/* Set Requested Number of      
                                          handles                           */
   } while (False);                    /* enddo                             */

   sprintf(s->strptr, "%lu", rc);      /* Set return value                  */
   s->strlength = strlen(s->strptr);

   return (APIRET)0;
} 


#ifndef  INCL_16

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RXADDFH                                               */
/*                                                                          */
/*  Description:      REXX external function to add number of File       */
/*                    Handles assigned to already allocated for process for */
/*                    OS/2 2.x environment                                  */
/*                                                                          */
/*  Notes:              exported function                                   */
/*                      ONLY FOR OS/2 2.x                          */
/*                                                                          */
/*  Entry Point:        RXSETFH(f,ac,av,q,s)                                */
/*                                                                          */
/*  Parameters:         f  - name of function called (ignored)              */
/*                      ac - argument count                                 */
/*                      av - list of argument strings                       */
/*                      q  - name of current active queue (ignored)         */
/*                      s  - pointer for return of RXSTRING                 */
/*                                                                          */
/*  Returns:            Number of Allocated File Handles                  */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

APIRET APIENTRY RXADDFH(PSZ f,acTYPE ac,PRXSTRING av,PSZ q,PRXSTRING s)/*   
                                          name function called as argument  
                                          count argument string list current
                                          queue name return string          */

{                                      /*                                   */
   ULONG rc;
   LONG  NumberHandles;              /* Requested Number of Handles       */
   ULONG NumberHandlesAllocated;     /* Allocated Number of Handles       */
   BOOL False = FALSE;                 /* Dummy loop control variable       */
   int  avidx;                         /* Index for parameter list element  */ 
 
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
 

      if (ac != 1)                     /* Only one argument is accepted     */
      {                                /* If not one - error                */
         rc = 0;
         break;                        /* --> return                        */
      }                                /* endif                             */
 
      avidx = ac - 1;                  /* Tbl. index starts form zero */

      if (av[avidx].strlength < 1)        /* String has to to be of length > 0 */
      {                                /* if it isn't - error               */
         rc = 0;
         break;                        /* --> return                        */
      }                                /* endif                             */
      NumberHandles = (parTYPE)atoi(av[avidx].strptr);
 
      if (NumberHandles < 0)           /* Number of requested handles has   */
      {                                /* to be at least 0                   */
         rc = 0;                       /* if it isn't - error               */
         break;                        /* --> return                        */
      }                                /* endif                             */

      DosSetRelMaxFH(&NumberHandles, &NumberHandlesAllocated);/* Add FH */
      rc = NumberHandlesAllocated;

   } while (False);                    /* enddo                             */

   sprintf(s->strptr, "%lu", rc);      /* Set return value                  */
   s->strlength = strlen(s->strptr);

   return (APIRET)0;
} 


#endif
