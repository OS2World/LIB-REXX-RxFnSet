/*------------------------------------------------------------------*/
/* run a rexx macro from a C program.  why? to codeview function    */
/* package dll's                                                    */
/*------------------------------------------------------------------*/
/* 90/08/22 - Patrick Mueller                                       */
/* 91/12/26 - Upped to date (16 & 32 bit env.) Leshek Fiedorowicz   */
/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/* For 16 bit environment (MSC 6.00A)   use RUNM16.mak              */
/* For 32 bit environment (IBM C Set/2 )use runm32.mak              */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsearg.h"

#define INCL_DOSMODULEMGR
#include <os2.h>
#define INCL_REXXSAA

#ifdef INCL_16
   #define RexxStart REXXSAA
#endif
#include <rexxsaa.h>

/*------------------------------------------------------------------*/
/*                                                                  */
/*------------------------------------------------------------------*/
void usage(
   char *program_name
   )
   {
   printf("usage:\n");
   printf("   %s <macro name> <arg1> ... <argn> /L<dlls>\n",program_name);
   printf("is used to run a rexx macro for debugging rexx function package\n");
   printf("DLLs.\n\n");
   printf("where:\n");
   printf("   <macro name> - is the rexx program to run\n");
   printf("   <argx>       - are arguments to the macro\n");
   printf("   <dlls>       - are comma delimited dll names to load\n");
   printf("                  (the L is case sensitive)\n");

   exit(0);
   }

/*------------------------------------------------------------------*/
/* append arguments together                                        */
/*------------------------------------------------------------------*/
char *append(
   char *org,
   char *new
   )
   {
   if (NULL == org)
      {
      org = malloc(1+strlen(new));
      if (NULL == org)
         {
         printf("Out of memory!!!\n");
         exit(1);
         }

      strcpy(org,new);

      return(org);
      }

   org = realloc(org,2+strlen(org)+strlen(new));
   if (NULL == org)
      {
      printf("Out of memory!!!\n");
      exit(1);
      }

   strcat(org," ");
   strcat(org,new);

   return(org);
   }

/*------------------------------------------------------------------*/
/* main routine                                                     */
/*------------------------------------------------------------------*/
void main(
   int   argc,
   char *argv[]
   )

   {
   RXSTRING  rxargv;
   char     *arg_string;
   char     *macro;
   RXSTRING  result;
   short     ret_code;
   int       rc;
   char     *dlls;
   char     *dll;
   char     *me;
   char     *p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8,*p9,*p10;

   parsearg(&argc,argv,1,NULL,"-/",
            "-Ldlls  me  macro  p1  p2  p3  p4  p5  p6  p7  p8  p9  p10",
              &dlls,&me,&macro,&p1,&p2,&p3,&p4,&p5,&p6,&p7,&p8,&p9,&p10);

   /*---------------------------------------------------------------*/
   /* make sure a macro name is entered                             */
   /*---------------------------------------------------------------*/
   if (NULL == macro)
      usage(me);

   if (0 == strcmp(macro,"?"))
      usage(me);

   /*---------------------------------------------------------------*/
   /* set up arguments to macro                                     */
   /*---------------------------------------------------------------*/
   arg_string = NULL;

   if (NULL != p1)  arg_string = append(arg_string,p1);
   if (NULL != p2)  arg_string = append(arg_string,p2);
   if (NULL != p3)  arg_string = append(arg_string,p3);
   if (NULL != p4)  arg_string = append(arg_string,p4);
   if (NULL != p5)  arg_string = append(arg_string,p5);
   if (NULL != p6)  arg_string = append(arg_string,p6);
   if (NULL != p7)  arg_string = append(arg_string,p7);
   if (NULL != p8)  arg_string = append(arg_string,p8);
   if (NULL != p9)  arg_string = append(arg_string,p9);
   if (NULL != p10) arg_string = append(arg_string,p10);

   rxargv.strptr    = arg_string;
   rxargv.strlength = (NULL == arg_string ? 0 : strlen(arg_string));

   /*---------------------------------------------------------------*/
   /* get dlls and load them                                        */
   /*---------------------------------------------------------------*/
   dll = strtok(dlls,",");
   while (NULL != dll)
      {
      char    DLM_msg[100];
      HMODULE mod_handle;
      USHORT  rc;

      rc = DosLoadModule(DLM_msg,sizeof(DLM_msg)-1,dll,&mod_handle);
      if (0 != rc)
         printf("error %hd loading DLL '%s' (%s)\n",rc,dll,DLM_msg);

      dll = strtok(NULL,",");
      }

   /*---------------------------------------------------------------*/
   /* run rexx program                                              */
   /*---------------------------------------------------------------*/
   rc = RexxStart (1,
                &rxargv,
                macro,
                NULL,
                NULL,
                RXCOMMAND,
                NULL,
                &ret_code,
                &result);

   }

