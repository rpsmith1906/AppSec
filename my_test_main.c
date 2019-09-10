#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int main ()
{

     char dictonary[80] = "wordlist.txt" ;
     char *misspelled[90] ;
     FILE *fp ;
//     int* head ;
  //   node* new_node ;
     int i,j ;
     hashmap_t hashtable[HASH_SIZE] ;

     if (( fp = fopen("sentence.txt", "r")) == NULL )
     {
          printf ( "Error! could not open file \n" ) ;
     }

     load_dictionary( dictonary, hashtable ) ;
     j=check_words(fp, hashtable, misspelled) ;

     for ( i=0; i<j; i++ )
     {
          printf ("Array %i %s\n", i, misspelled[i] );
     }

//    printf ( "Here %s\n", hashtable[425]->word ) ;
//     for ( i=1; i<10; i++ )
//     {
//          new_node = (node*)malloc(sizeof(node)) ;
//          new_node->next = head ;

//          if ( new_node == NULL )
//          {
//               printf("Error creating a new node.\n") ;
//               exit(0) ;
//          }
     
//          sprintf ( new_node->word, "Test %i", i ) ;
//          head = new_node ;
//     }
//     printf ("%s\n", new_node->word ) ;
//     new_node->next = head ;

//     node* cursor = head ;

//     while ( cursor != NULL )
//     {
//          printf ("%s\n", cursor->word );
//          cursor = cursor->next ;
//     }
//
//     for ( i=0; i< HASH_SIZE; i++ )
//     {
//          if ( hashtable[i] == NULL ) { continue; }

//          printf ("%s %i \n", hashtable[i]->word, i) ;
//          new_node = hashtable[i] ;
//          while ( new_node->next != NULL ) 
//          {
//               new_node = new_node->next ;
//               printf ("%s %i \n", new_node->word, i) ;
//          }
//     }
}
