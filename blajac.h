#ifndef BLAJAC_H
#define BLAJAC_H
#define DECK_SIZE 52

typedef enum{
    HEART,
    DIAMOND,
    CLUB,
    SPADE
}Nipe;

typedef struct{
    int value;
    Nipe nipe;
}Card;

void create_deck(Card deck[]);
void shuffle(Card deck[]);
Card draw(Card deck[], int *top);
int score(Card hand[], int size);
void title_game();

#endif
