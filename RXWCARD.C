/****************************************************************************/
/*                                                                          */
/*  IBM INTERNAL USE ONLY                                                   */
/*  Name: RXWCARD.C                                                         */
/*                                                                          */
/*  Author: Leshek Fiedorowicz Feb-01-1992                                  */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*  Function Name:    RXWILDCARD                                            */
/*                                                                          */
/*  Description:      REXX external function to edit name with wildcard     */
/*                                                                          */
/*  Entry Point:      RxWildCard(Source, WildCard)                          */
/*                                                                          */
/*  Parameters accepted: - Source to be edited                              */
/*                       - Wild card specification                          */
/*                                                                          */
/*  Returns:             - Name Edited with wildcard or empty string if any */
/*                         error (invalid name or wildcard)                 */
/*                                                                          */
/*  Known problems:      - None                                             */
/*                                                                          */
/****************************************************************************/

#define  INCL_BASE
#define  INCL_REXXSAA
#include <os2.h>
#include <rexxsaa.h>   
#include <string.h>    

/* #include <stdio.h>                                                       */
/* #include <stdlib.h>                                                      */

#ifdef   INCL_16
#include <dos.h>
#define  APIRET        USHORT
#define  acTYPE        SHORT
#define  parTYPE       USHORT

#else
#define  acTYPE        LONG
#define  parTYPE       ULONG

#endif
#define  MAXNAMELENGTH 256             /* Maximum Length of the name        */

/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*  Function Name:      RXWILDCARD                                          */
/*                                                                          */
/*  Description:        REXX external function to edit name with wildcard   */
/*                                                                          */
/*  Notes:              exported function                                   */
/*                      uses DosEditName CP call                            */
/*                                                                          */
/*  Entry Point:        RXWILDCARD(f,ac,av,q,s)                             */
/*                                                                          */
/*  Parameters:         f  - name of function called (ignored)              */
/*                      ac - argument count                                 */
/*                      av - list of argument strings                       */
/*                      q  - name of current active queue (ignored)         */
/*                      s  - pointer for return of RXSTRING                 */
/*                                                                          */
/*  Returns:            editd name or empty string if any error (invalid    */
/*                         name or wildcard)                                */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/

#define  SOURCE        0               /* Index of source - first parameter */
#define  WILDCARD      1               /* Index of WildCard - second          
                                        parameter                          */
#define  EDITLEVEL     1               /* Edit Level for maco is 1.2        */
APIRET APIENTRY RXWILDCARD(PSZ f,acTYPE ac,PRXSTRING av,PSZ q,PRXSTRING s)/*
                                          name function called as argument  
                                          count argument string list current
                                          queue name return string          */

{                                      /*                                   */
   BOOL False = FALSE;                 /* Dummy loop control variable       */
   char WorkString[MAXNAMELENGTH];     /* Room for Source edited by         */
   LONG rc;                            /* Work variable for the return      */
 
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
 

      if (ac != 2)                     /* Only two arguments are accepted   */
      {                                /* If not one - error                */
         s->strptr[0] = '\0';          /* Return empty string               */
         break;                        /* --> return                        */
      }                                /* endif                             */
      rc = (LONG) DosEditName(EDITLEVEL, 
                             av[SOURCE].strptr, 
                             av[WILDCARD].strptr, 
                             (PBYTE)WorkString, 
                             MAXNAMELENGTH);
 
      if (rc != NO_ERROR)              /* If any error ocurred ( possible:  */
                                       /* 87 -ERROR_INVALID_PARAMETER       */
      {                                /* 123-ERROR_INVALID_NAME            */
         s->strptr[0] = '\0';          /* Return empty string               */
         break;                        /* --> return                        */
      }                                /* endif                             */
      strcpy(s->strptr, WorkString);   /* Fine - copy return string.        */
   } 
 
   while (False);                      /* enddo                             */
   s->strlength = strlen(s->strptr);

   return (APIRET)0;
} 



