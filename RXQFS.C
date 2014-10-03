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
#define  DosQueryFSAttach DosQFSAttach
typedef struct _FSQBUFFER2             /* fsqbuf Data structure for         
                                          QFSAttach                         */
{
   USHORT iType;

   USHORT cbName;
   USHORT cbFSDName;
   USHORT cbFSAData;
   UCHAR szName[1];
   UCHAR szFSDName[1];
   UCHAR rgFSAData[1];
   UCHAR Reserved[128];                /* Without that I got 111 buffer     
                                          overflow                          */
} FSQBUFFER2,*PFSQBUFFER2;

#define  RESERVED      ,0 
#define  DATABUFFER    (PBYTE)&DataBuffer

#else
#define  acTYPE        LONG
#define  parTYPE       ULONG
#define  RESERVED      
#define  DATABUFFER    &DataBuffer
#endif

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
RxQueryFileSystem(                     /*                                   */
                  PSZ f,               /* name function called as argument  */
                  acTYPE ac,           /* argument count                    */
                  PRXSTRING av,        /* argument string list              */
                  PSZ q,               /* current queue name                */
                  PRXSTRING s)         /* return string                     */

{                                      /*                                   */
   PUCHAR pDeviceName;                 /* Device name or drive letter string*/
   parTYPE Ordinal;                    /* Ordinal of entry in name list     */
   parTYPE FSAInfoLevel;               /* Type of attached FSD data required*/
   FSQBUFFER2 DataBuffer;              /* Returned data buffer              */
   parTYPE DataBufferLen;              /* Buffer length                     */
   ULONG rc;                           /* Return code                       */
   int avidx;                          /* Parameter index                   */
   BOOL False = FALSE;                 /* Dummy loop control variable       */
   char Disk[3];                       /* Space for sz type disk id         */

   s->strptr[0] = '\0';                /* Initilia return value is set to   
                                          empty string                      */
 
   do                                  /* This is dummy block to exit       
                                          <break>                           */
   {                                   /* in case of any error              */
 
      if (ac != 1)                     /* Only one argument is accepted     */
      {                                /* If not one - error                */
         break;                        /* --> return                        */
      }                                /* endif                             */
      avidx = ac-1;                    /* Tbl. index starts form zero       */
 
      if (av[avidx].strlength != 2)    /* String has to to be of length > 0 */
      {                                /* if it isn't - error               */
         break;                        /* --> return                        */
      }                                /* endif                             */
      memset(Disk,'\0',sizeof(Disk));  /* NULL it                           */ 
      memcpy(Disk,av[avidx].strptr, 2);/* copy disk id                      */

      pDeviceName = Disk;              /* Logical drive of attached         */

      /**********************************************************************/
      /* Indicate that the request is to return information about the drive */
      /* whose name is speficied within the DeviceName variable (also       */
      /* indicate that the Ordinal variable is to be ignored)               */
      /**********************************************************************/

      FSAInfoLevel = FSAIL_QUERYNAME;

      DataBufferLen = sizeof(FSQBUFFER2);/* Length of data buffer           */
      rc = DosQueryFSAttach(pDeviceName, 
                            Ordinal, 
                            FSAInfoLevel, 
                            DATABUFFER, 
                            &DataBufferLen RESERVED);

      /**********************************************************************/
      /* On successful return, the DataBuffer structure contains a set of   */
      /* information describing the specifed attached file system, and the  */
      /* DataBufferLen variable contains the size of information within the */
      /* structure                                                          */
      /**********************************************************************/

      if (rc != NO_ERROR)              /* Any Error ?                       */
      {                                /* if so ...                         */
         break;                        /* --> return empty string           */
      }                                /* endif                             */
      strcpy(s->strptr, DataBuffer.szFSDName);/* Return name of file system */
   } 
 
   while (False);                      /* enddo                             */
   s->strlength = strlen(s->strptr);

   return (APIRET)0;
} 



