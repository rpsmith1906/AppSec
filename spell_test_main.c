#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "testing/wordlist.txt"

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* incorrect_word = "Caoimhín";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_check_word_buffer_overflow)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char incorrect_word[500000];
    for(int i = 0; i < 499999; i++)
        incorrect_word[i] = 'A';
    incorrect_word[499999] = 0;
    ck_assert(!check_word(&incorrect_word[499999], hashtable));
    const char* incorect_word = "pneumonoultramicroscopicsilicovolcanoconiosis";
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_string_buffer_overflow)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Happy";
    const char* incorrect_word = "pneumonoultramicroscopicsilicovolcanoconiosis";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_punctuation)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    FILE *fp ;
    char *misspelled[1000] ;
    char *words[10] ;

    words[0] = "Help?" ;
    words[1] = "H.elp?" ;
    words[2] = "\"Help?\"" ;
    words[3] = "because" ;
    words[4] = "Justic?e" ;
    words[5] = "super-book" ;

    fp = fopen("file.in", "w+") ;

    for ( int i=0 ; i<5 ; i++ )
    {
         fprintf (fp, "%s\n", words[i]) ;
    }
  
    fclose ( fp ) ;

    fp = fopen("file.in", "r") ;
    ck_assert(check_words(fp, hashtable, misspelled)==2);
    fclose(fp) ;
}
END_TEST

START_TEST(test_number)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    FILE *fp ;
    char *misspelled[1000] ;
    char *words[10] ;

    words[0] = "45" ;
    words[1] = "45.0" ;
    words[2] = "45A" ;
    words[3] = "45.A" ;
    words[4] = "67.0A" ;
    words[5] = "6A.5" ;

    fp = fopen("file.in", "w+") ;

    for ( int i=0 ; i<5 ; i++ )
    {
         fprintf (fp, "%s\n", words[i]) ;
    }
  
    fclose ( fp ) ;

    fp = fopen("file.in", "r") ;
    ck_assert(check_words(fp, hashtable, misspelled)==4);
    fclose(fp) ;
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_word_buffer_overflow);
    tcase_add_test(check_word_case, test_string_buffer_overflow);
    tcase_add_test(check_word_case, test_punctuation);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

