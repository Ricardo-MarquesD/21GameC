#include <stdio.h>
#include <stdlib.h>
#include "blajac.h"

#define MAX_CARD_HAND 15
#define MAX_PLAYERS 4

int main(int argc, char const *argv[])
{
    int players = 1, flag = 0, flag2 = 1;

    title_game();
    scanf("%d", &flag);

    switch (flag)
    {
    case 1:
        system("cls");
        flag = 1;
        break;
    default:
        system("cls");
        printf("Programa encerrado");
        return 0;
    }

    while (flag)
    {
        flag = 0;
        flag2 = 1;

        printf("Quantos Jogadores: ");
        scanf("%d", &players);
        if(players > 4){
            printf("Quantidade maxima de jogadores é 4, repita o codigo");
            continue;
        }
        system("cls");

        while (flag2)
        {
            int top = DECK_SIZE;
            Card deck[DECK_SIZE];
            Card hands[MAX_PLAYERS][MAX_CARD_HAND];
            for (int i = 0; i < MAX_PLAYERS; i++) {
            for (int j = 0; j < MAX_CARD_HAND; j++) {
                hands[i][j].value = 0;
                hands[i][j].nipe = HEART;
                }
            }
            int online[MAX_PLAYERS] = {0};

            for (int i = 0; i < players; i++) online[i] = 1;

            create_deck(deck);
            shuffle(deck);

            for (int i = 0; i < MAX_CARD_HAND; i++)
            {
                printf("\n\n|RODADA %d|\n\n", i);
                for (int j = 0; j < players; j++)
                {
                    if (online[j] && score(hands[j], MAX_CARD_HAND) != -1)
                    {
                        printf("Vez do Jogador %d:\n1 - Sacar | 0 - Passar\n", j + 1);
                        int choose;
                        scanf("%d", &choose);
                        if (choose == 1)
                        {
                            hands[j][i] = draw(deck, &top);
                            int points = score(hands[j], MAX_CARD_HAND);

                            #ifdef DEBUG
                                int debugPoints = score(hands[j], MAX_CARD_HAND);
                                printf("Pontuacao atual do Jogador %d, %d\n", j + 1, debugPoints);
                            #endif
                            if (points == 21)
                            {
                                printf("Jogador %d ganhou a partida!\n", j + 1);
                                flag2 = 0;
                                break;
                            }
                            else if (points == -1)
                            {
                                printf("Jogador %d estourou!\n\n", j + 1);
                                online[j] = 0;
                            }
                        }
                        else
                        {
                            printf("Jogador %d passou a vez\n\n", j + 1);
                            online[j] = 0;
                        }
                    }
                }

                int winnable = 0;
                for (int j = 0; j < players; j++)
                {
                    if (online[j] && score(hands[j], MAX_CARD_HAND) != -1)
                    {
                        winnable = 1;
                        break;
                    }
                }

                if (!winnable)
                {
                    flag2 = 0;
                    break;
                }
            }

            int highest_score = 0;
            int winner = -1;
            for (int i = 0; i < players; i++)
            {
                int current_score = score(hands[i], MAX_CARD_HAND);
                if (current_score > highest_score && current_score <= 21)
                {
                    highest_score = current_score;
                    winner = i;
                }
            }

            if (winner != -1)
            {
                printf("Jogador %d venceu a rodada com %d pontos!\n", winner + 1, highest_score);
            }
            else
            {
                printf("Todos os jogadores estouraram! Ninguem ganhou.\n");
            }

            flag2 = 0;
        }

        printf("Deseja repetir a partida(0 - Nao | 1 - Sim)?");
        scanf("%d", &flag);
    }

    return 0;
}
