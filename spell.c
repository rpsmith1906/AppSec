#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int hash_function(const char* word);
int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]);
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]);
bool check_word(const char* word, hashmap_t hashtable[]);

bool check_word(const char* word, hashmap_t hashtable[])
{
     int hash,i ;
     node* node ;
     char lword[LENGTH + 1] ;

     i=0 ;
     while ( word[i] != '\0' )
     {
          lword[i] = tolower( word[i] ) ;
          i++ ;
     }
     lword[i] = '\0' ;

     hash = hash_function(lword) ;

     node = hashtable[hash] ;
     while ( node != NULL )
     {
          if ( strcmp(lword, node->word ) == 0 )
          {
               return ( true ) ;
          }

          node = node->next ;
     }
     return ( false ) ;
}

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[])
{
     char word[LENGTH + 1] ;
     char c ;
     int i ;
     int mswords=0 ;

     while ( ! feof( fp ))
     {
          c = fgetc(fp) ;
          i = 0 ;
          strcpy(word, "") ;

          while (( ! isspace(c) ) && ( ! ispunct(c)) )
          {
               if ( feof(fp) ) { break ; }
               if ( i < LENGTH)
               {
                    word[i++] = c ;
                    word[i] = '\0' ;
               }
               c = fgetc(fp) ;

          }

          if ( strlen(word) != 0 ) 
          { 
               if ( check_word(word, hashtable) == false ) 
               { 
                    misspelled[mswords] = (char* )malloc(sizeof(char)*(LENGTH + 1)) ;
                    strcpy ( misspelled[mswords++], word ) ;
               }
          }
     }

     return ( mswords ) ;
}

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
     char word[LENGTH + 1] ;
     int hash,i,len ;
     node* head ;
     FILE *fptr;

     for ( i=0 ; i<HASH_SIZE-1; i++ ) { hashtable[i] = NULL ; }

     if (( fptr = fopen(dictionary_file, "r")) == NULL )
     {
          printf ( "Error! could not open file %s\n", dictionary_file ) ;
          return ( false ) ;
     }

     while ( fgets ( word, sizeof word, fptr ) != NULL )
     {
          len = strlen(word) ;
          if ( len > 0 )
          {
               if (( word[len-1] == '\n' ) || ( word[len-1] == '\r' )) { word[--len] = '\0' ; }
               if (( word[len-1] == '\n' ) || ( word[len-1] == '\r' )) { word[--len] = '\0' ; }
          }

          i=0 ;
          while ( word[i] != '\0' )
          {
               word[i] = tolower(word[i]) ;
               i++ ;
          }

          hash = hash_function(word) ;
          head = hashtable[hash] ;

          hashtable[hash] = (node*)malloc(sizeof(node)) ;

          if ( hashtable[hash] == NULL )
          {
               printf( "Error creating a new node.\n" ) ;
               return ( false ) ;
          }
          hashtable[hash]->next = head ;
          strcpy ( hashtable[hash]->word, word ) ;
     }

     fclose(fptr) ;
     return ( true ) ;
}


int main ()
{

     char dictonary[80] = "wordlist.txt" ;
   //  char word[46] = "becauser" ;
     char *misspelled[90] ;
     FILE *fp ;
//     int* head ;
//     node* new_node ;
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

//     for ( i=0; i< HASH_SIZE; i++ )
//{
//if ( hashtable[i] == NULL ) { continue; }

 //         printf ("%s %i \n", hashtable[i]->word, i) ;
  //        new_node = hashtable[i] ;
   //       while ( new_node->next != NULL ) 
    //      {
     //          new_node = new_node->next ;
      //         printf ("%s %i \n", new_node->word, i) ;
       //   }
   //  }
}
