#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int main (int argc, char *argv[] )
{
     char *misspelled[1000] ;
     char verb[5] = "were" ;
     FILE *fp ;
     int i,mswords ;

     hashmap_t hashtable[HASH_SIZE] ;


     if ( argc < 3 ) 
     {
          printf("Usage %s <input file> < word list >...\n", argv[0] ) ;
          return (1) ;
     }

     if (( fp = fopen(argv[1], "r")) == NULL )
     {
          printf ( "Error! could not open file \n" ) ;
     }

     load_dictionary( argv[2], hashtable ) ;
     mswords=check_words(fp, hashtable, misspelled) ;

     if ( mswords > 0 ) 
     { 
          if ( mswords == 1 ) { strcpy ( verb, "was" ) ; }
          printf("There %s %i misspelled words found.\n\n", verb, mswords ) ;
     }     

     for ( i=0; i<mswords; i++ )
     {
          printf ("%s\n", misspelled[i] );
     }
}
