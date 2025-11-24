#ifndef CARDHANDLING_H
#define CARDHANDLING_H

#include <stdbool.h>
#include <time.h>

typedef struct {
    int card_number;  // card number
    bool access;            // Access (True,False)
    char date[20];         // date (YYYY-MM-DD)
} Card;

typedef struct {
    Card *cards;  // card details
    int count;    // number of cards
} AccessList;

//get current date
void get_current_date(char *buf, size_t sz);


//card functions
void add_card(AccessList *list, int card_number);

int find_card(AccessList *list, const int *card_number);

bool check_access(AccessList *list, const int *card_number);

void give_access(AccessList *list, const int *card_number);

void remove_access(AccessList *list, const int *card_number);


//file functions
void save_to_file(const AccessList *list, const char *filename);

void load_from_file(AccessList *list, const char *filename);


#endif