/*********************************************************************/
/*                                                                   */
/* Convert Version 1.11                                              */
/*                                                                   */
/* Converts uppercase file names to lower case and visa versa        */
/* Written by :  John Ballment                                       */
/* Written on :  06 June, 1997                                       */
/* Last updated : 21 July, 1997                                      */
/*                                                                   */
/* I wrote this small application to convert files from uppercase    */
/* to lowercase after doing a project with a couple of friends who   */
/* where using Windows 95.                                           */
/*                                                                   */
/* Everytime they saved files onto thier disks, the filenames were   */
/* in uppercase, which made it hard to port onto my OS/2 system and  */
/* the UNIX system which the project was being designed for.         */
/*                                                                   */
/* The program command-line is as follows:                           */
/*                                                                   */
/*      convert -u/l <filename>                                      */
/*                                                                   */
/* -u = convert to uppercase (I wrote it to convert both ways)       */
/* -l = convert to lowercase                                         */
/* <filename> = a filename including wildcards like * and ?          */
/*                                                                   */
/* If you find the program useful please send a post card to:        */
/*                                                                   */
/*     John Ballment                                                 */
/*     98 Kilsay Cres                                                */
/*     Meadowbrook  Q  4131                                          */
/*     Australia, plant Earth, the Milky-Way solar system            */
/*                                                                   */
/* Please send any bug reports to:                                   */
/*                                                                   */
/*     n1237462@droid.fit.qut.edu.au                                 */
/*                                                                   */
/*********************************************************************/

/*********************************************************************/
/*  History -                                                        */
/*                                                                   */
/*  1.11 Made to be UNIX compatible.                                */
/*                                                                   */
/*  1.10 Fix temperary environment bug.  Also simplified the code.   */
/*       Convert does not work on FAT drives only on HPFS.           */
/*                                                                   */
/*  1.00 I thought it was such a simple program, there should not    */
/*       be any bugs.                                                */
/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OK 0
#define FAILED 1
#define FilenameLength 256
#define FILENAME 2
#define CONVERT 1
#define PROGRAM 0
#define TEMPNAME "convert.tmp"


int Rename(const char *oldname, const char *newname);
char *strupr(char *string);
char *strlwr(char *string);

int main (int argc, char *argv[]) {

   char name[FilenameLength], *newname;
   int count;

   newname = name;

   if (argc < 3) {
      printf("\nConvert 1.11\n");
      printf("\nexample usage is: %s <convert> <filename>\n", argv[PROGRAM]);
      printf("Convert must be either -l<ower> or -u<pper>\n");
      return FAILED;
      }
   for (count = FILENAME; count <= argc - 1; count++) {

      if ((strcmp(strlwr(argv[CONVERT]), "-u")) == OK)  {
         strcpy(newname, argv[count]);
         strupr(newname);
         if ((Rename(argv[count], newname)) != OK) {
            return FAILED;
            }
         }
      else if (strcmp(strlwr(argv[CONVERT]), "-l") == OK) {
         strcpy(newname, argv[count]);
         strlwr(newname);
         if ((Rename(argv[count], newname)) != OK) {
            return FAILED;
            }
         }
      else {
         printf("\nConvert must be either -l<ower> or -u<pper>\n");
         return FAILED;
         }
      }
   return OK;
   }

int Rename(const char *oldname, const char *newname) {
   char *tempname;
   tempname = TEMPNAME;

   /* tempname = tmpnam(NULL);    Removed as it did not allow
                                  the program to work across
                                  multipule drives.
                                  The fix uses a standard temp
                                  name for all conversions,
                                  this may be a problem if
                                  multi-tasking.  */
   if ((rename(oldname, tempname)) != OK) {
      printf("\nCould not rename file %s to %s\n", oldname, newname);
      printf("Convert uses a temperary file called convert.tmp in the current directory.\n");
      printf("Please ensure that a file by this name does not already exist.\n");
      return FAILED;
      }
   if ((rename(tempname, newname)) != OK) {
      printf("\nCould not rename file %s to %s\n", oldname, newname);
      return FAILED;
      }
   return OK;
   }

char *strlwr(char *string) {
   char *s;
   s = string;
   while (*s != '\0') {
      *s = tolower(*s);
      s++;
      }
   return string;
   }

char *strupr(char *string) {
   char *s;
   s = string;
   while (*s != '\0') {
      *s = toupper(*s);
      s++;
      }
   return string;
   }
