#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 20
#define MAX_GUESSES 6

char *wordlist[] = {"hello", "world", "apple", "orange", "banana", "cherry", "grape", "watermelon", "pineapple", "strawberry", NULL};

int random_number(int n)
{
    return rand() % n;
}

void print_word(char *word, int length, char *guessed)
{
    for (int i = 0; i < length; i++)
    {
        if (isalpha(word[i]) && strchr(guessed, word[i]) == NULL)
        {
            printf("_ ");
        }
        else
        {
            printf("%c ", word[i]);
        }
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    char *word = wordlist[random_number(sizeof(wordlist)/sizeof(wordlist[0]))];
    int length = strlen(word);
    char guessed[MAX_WORD_LENGTH] = "";
    int guesses_left = MAX_GUESSES;

    printf("Welcome to Hangman!\n");
    printf("The word to guess is ");
    print_word(word, length, guessed);

    while (guesses_left > 0)
    {
        printf("You have %d guesses left.\n", guesses_left);
        printf("Enter a letter to guess: ");
        char guess;
        scanf(" %c", &guess);
        guess = tolower(guess);
        if (strchr(guessed, guess) != NULL)
        {
            printf("You already guessed %c. Try again.\n", guess);
            continue;
        }
        guessed[strlen(guessed)] = guess;
        if (strchr(word, guess) != NULL)
        {
            printf("Good guess!\n");
            print_word(word, length, guessed);
            if (strchr(guessed, '_') == NULL)
            {
                printf("Congratulations, you won!\n");
                return 0;
            }
        }
        else
        {
            printf("Sorry, %c is not in the word.\n", guess);
            guesses_left--;
            if (guesses_left == 0)
            {
                printf("You lose. The word was %s.\n", word);
            }
        }
    }

    return 0;
}
