#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "blajac.h"

void create_deck(Card deck[])
{
    int index = 0;

    for (int nipe = HEART; nipe <= SPADE; nipe++)
    {
        for (int i = 1; i <= 13; i++)
        {
            deck[index].value = i;
            deck[index].nipe = (Nipe)nipe;
            index++;
        }
    }
}

void shuffle(Card deck[])
{
    srand(time(NULL));

    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int index = rand() % (i + 1);

        Card temp = deck[i];
        deck[i] = deck[index];
        deck[index] = temp;
    }
}

Card draw(Card deck[], int *top)
{
    if (*top <= 0)
    {
        Card card_null = {0, HEART};
        return card_null;
    }

    Card card = deck[--(*top)];

    char *card_name;
    if (card.value == 1)
    {
        card_name = "As";
    }
    else if (card.value == 11)
    {
        card_name = "Valete";
    }
    else if (card.value == 12)
    {
        card_name = "Dama";
    }
    else if (card.value == 13)
    {
        card_name = "Rei";
    }
    else
    {
        card_name = NULL;
    }

    if (card_name != NULL)
    {
        printf("Carta sacada: %s", card_name);
    }
    else
        printf("Carta sacada: %d", card.value);

    switch (card.nipe)
    {
    case HEART:
        printf(" de Copas.\n\n");
        break;
    case DIAMOND:
        printf(" de Diamantes.\n\n");
        break;
    case CLUB:
        printf(" de Paus.\n\n");
        break;
    case SPADE:
        printf(" de Espadas.\n\n");
        break;
    default:
        printf("Erro inesperado, valor da Enum: %d\n", card.nipe);
        break;
    }

    return card;
}

int score(Card hand[], int size)
{
    int count = 0;
    int value = 0;

    for (int i = 0; i < size; i++)
    {
        value = hand[i].value;

        if(value == 0){
            break;
        }

        if (value >= 10)
        {
            count += 10;
        }
        else if (value == 1)
        {
            count += 1;
        }
        else
            count += value;
    }

    return count > 21 ? -1 : count;
}

void title_game()
{
    printf("\n=================================================================================");
    printf("\n ######    ##       ######  #######  ##  ##      ##     ######  #######  ##  ##\n ##  ##    ##       ##  ##  ##  ###  ##  ##      ##     ##  ##  ##  ###  ##  ##\n ##  ##    ##       ##  ##  ##  ###  ## ##       ##     ##  ##  ##  ###  ## ##\n #######  ###      #######  ##       #######     ###   #######  ##       #######\n ##  ###  ###      ###  ##  ##   ##  ##  ### ##  ###   ###  ##  ##   ##  ##  ###\n ##  ###  ###      ###  ##  ##   ##  ##  ### ##  ###   ###  ##  ##   ##  ##  ###\n #######  ######   ###  ##  #######  ##  ### #######   ###  ##  #######  ##  ###\n");
    printf("=================================================================================\n");
    printf("                           | 1 - JOGAR  | | 0 - SAIR|\n");
}