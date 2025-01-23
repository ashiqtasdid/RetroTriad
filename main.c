#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

struct Player
{
    char username[50];
    int quizGame_score;
    int ticTacToe_score;
    int storyGame;
};

void saveScore(struct Player player)
{
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s %d %d %d\n",
                player.username,
                player.quizGame_score,
                player.ticTacToe_score,
                player.storyGame);
        fclose(file);
    }
}

void displayScore(char username[])
{
    FILE *file = fopen("scores.txt", "r");
    int gameNumber = 1;
    int totalSum = 0;

    if (file != NULL)
    {
        char stored_username[50];
        int score1, score2, score3;

        while (fscanf(file, "%s %d %d %d",
                      stored_username, &score1, &score2, &score3) == 4)
        {
            if (strcmp(stored_username, username) == 0)
            {
                int lineSum = score1 + score2 + score3;
                printf("Game %d: %d Points\n", gameNumber, lineSum);
                totalSum += lineSum;
                gameNumber++;
            }
        }
        fclose(file);
    }

    printf("\nTotal score across all games: %d Points\n", totalSum);
}
// Story Game by Md. Ashiquzzaman Khan - C243005

#define MAX_HEALTH 100
int s_score = 0;
int health = MAX_HEALTH;
char name[40];
int relation_house_owner = 1;

void getInput(int *x)
{
    scanf("%d", x);
}

int intro();
void house();
void checkHealth();
void insideHouse();
void inCar();
int playTicTacToe();
void finalScene();

// Quiz Game by Md Raahim Anowar-C243009

struct Question
{
    char question[200];
    char options[4][50];
    char correct_answer;
};

int playQuizGame()
{
    // Questions and answers
    struct Question questions[] = {
        {"Who won the battle of 1st Panipat?",
         {"Babur", "Ibrahim", "Sher Shah Suri", "Humayun"},
         'A'},
        {"Who was the first muslim to led conquest in India?",
         {"Muhammad Ghori", "Muhammad Bin Qasim", "Babur", "Emir Timur"},
         'B'},
        {"What is the first capital of Bengal Sultanate?",
         {"Sonargaon", "Lakhnauti", "Pandua", "Gaur"},
         'C'},
        {"Who almost destroyed Ottoman Empire?",
         {"Emir Timur", "Vlad The Impaler", "King of Hungary", "Eskander Beg"},
         'A'},
        {"Who conqured Spain and establish muslim rule?",
         {"Tariq Bin Ziyad", "Abdul Rahman Al Ghafiqi", "Muhammad Bin Qasim", "Sultan Alauddin"},
         'A'}};

    int num_questions = sizeof(questions) / sizeof(questions[0]);
    int score = 0;
    char answer;

    printf("\n===== WELCOME TO THE QUIZ GAME =====\n");
    printf("Answer these multiple-choice questions!\n");
    printf("Enter A, B, C, or D for your answer.\n\n");

    for (int i = 0; i < num_questions; i++)
    {
        printf("\nQuestion %d: %s\n", i + 1, questions[i].question);
        printf("A) %s\n", questions[i].options[0]);
        printf("B) %s\n", questions[i].options[1]);
        printf("C) %s\n", questions[i].options[2]);
        printf("D) %s\n", questions[i].options[3]);

        printf("Your answer: ");
        scanf(" %c", &answer);
        answer = toupper(answer);

        if (answer == questions[i].correct_answer)
        {
            printf("Correct! Well done!\n");
            score += 1;
        }
        else
        {
            printf("Sorry, that's incorrect. The correct answer was %c.\n",
                   questions[i].correct_answer);
        }
    }

    printf("\n===== QUIZ COMPLETE =====\n");
    printf("Your final score: %d\n", score);

    return score;
}

// TIC TAC TOE by Md. Tansen Uddin Tansu - C243012

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int t_score = 0;

int playTicTacToe()
{
    t_score = 0;
    char winner = ' ';
    char response = ' ';

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        while (winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0)
            {
                break;
            }
        }

        printBoard();
        printWinner(winner);
        printf("\nWould you like to play again? (Y/N): ");
        while ((getchar()) != '\n')
            ;
        response = getchar();
        response = toupper(response);

    } while (response == 'Y');

    printf("Thanks for playing!\n");

    return t_score;
}

void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
int checkFreeSpaces()
{
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void playerMove()
{
    int x;
    int y;

    do
    {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (board[x][y] != ' ');
}
void computerMove()
{

    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        printWinner(' ');
    }
}
char checkWinner()
{
    // check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    // check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    // check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}
void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        t_score++;
        printf("YOU WIN!");
    }
    else if (winner == COMPUTER)
    {
        printf("YOU LOSE!");
    }
    else
    {
        printf("IT'S A TIE!");
    }
}

// MENU BY AFIF - C243017

void launchGame(char username[], int gameChoice)
{
    printf("\n***** %s is playing Game %d *****\n", username, gameChoice);

    struct Player player = {0};
    strcpy(player.username, username);

    // This space is reserved for actual game code
    switch (gameChoice)
    {
    case 1:
        player.quizGame_score = playQuizGame();
        saveScore(player);
        break;
    case 2:
        player.ticTacToe_score = playTicTacToe();
        saveScore(player);
    case 3:
        intro();
        player.storyGame = relation_house_owner;
        saveScore(player);
        break;
    }
}

int main()
{
    char username[50];
    char choice;

    printf("Good Day! from RetroTriad\n");
    printf("Please enter your username: ");
    scanf("%s", username);

    while (1)
    {
        printf("\nSelect a game %s:\n", username);
        printf("A. Quiz Game\n");
        printf("B. TIC TAC TOE\n");
        printf("C. STORY GAME\n");
        printf("# Press X see your score\n");
        printf("# Press Q to quit\n");

        scanf(" %c", &choice);
        choice = toupper(choice);

        switch (choice)
        {
        case 'A':
            launchGame(username, 1);
            break;
        case 'B':
            launchGame(username, 2);
            break;
        case 'C':
            launchGame(username, 3);
            break;
        case 'X':
            displayScore(username);
            break;
        case 'Q':
            printf("Thanks for playing!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

int intro()
{
    int choice;
    printf("\nNow Playing: Time Walker\n");
    printf("[NARRATOR]: You wake up in the middle of the road. Your head pounds, and your vision is blurry. You try to remember who you are.");
    printf("\nEnter your name: ");
    scanf("%s", name);
    printf("\n[NARRATOR]: You feel a sharp pain in your head. There's a house nearby.");
    printf("\n1. Go to the house.\n");
    printf("2. Stay here.\n");
    getInput(&choice);

    if (choice == 2)
    {
        printf("\n[NARRATOR]: A shadow looms over you. A figure appears.");
        printf("\n[FIGURE]: Lost, are we? Too bad, you've found me instead.");
        printf("\n[NARRATOR]: The figure transforms into a hideous monster and attacks you. (-50 health)");
        health -= 50;
        checkHealth();
    }
    else if (choice == 1)
    {
        house();
    }
    return 0;
}

void checkHealth()
{
    if (health <= 0)
    {
        printf("\nYou died.\n");
    }
    else
    {
        printf("\nYour health is: %d\n", health);
    }
}

void house()
{
    int choice;
    printf("\n[NARRATOR]: You approach the house cautiously.");
    printf("\n1. Knock on the door.\n");
    printf("2. Open the door.\n");
    getInput(&choice);
    if (choice == 2)
    {
        printf("\n[NARRATOR]: The door creaks open, and a startled family inside screams.");
        printf("\n[FAMILY]: Who are you? Thief! Intruder!");
        printf("\n[NARRATOR]: They shoot you. (-30 health)");
        health -= 30;
        checkHealth();
    }
    else if (choice == 1)
    {
        insideHouse();
    }
}

void insideHouse()
{
    int choice, inner, cinner;
    printf("\n[NARRATOR]: A middle-aged man opens the door.");
    printf("\n[HOUSE OWNER]: Who are you, and why are you here in the middle of the night?");
    printf("\n1. I need medicine.\n");
    printf("2. I need a weapon.\n");
    getInput(&choice);
    if (choice == 2)
    {
        printf("\n[HOUSE OWNER]: You'll need to prove yourself first. Beat me in a game of tic-tac-toe.");
        printf("\n[NARRATOR]: A tic-tac-toe board appears.\n");
        int result = playTicTacToe();
        if (result >= 1)
        {
            printf("\n[HOUSE OWNER]: Well done! Here's your weapon. What are you doing here?");
            printf("\n1. I am lost. Someone tried to kill me.\n");
            printf("2. I don't know. Maybe I sleepwalk.\n");
            getInput(&inner);
            if (inner == 1)
            {
                ++relation_house_owner;
                printf("\n[HOUSE OWNER]: Hmm, interesting. How may I help you with that?");
                printf("\n1. Can you help me find a vehicle?\n");
                printf("2. I don't know. Maybe just give me some food.\n");
                getInput(&cinner);
                if (cinner == 2)
                {
                    printf("\n[HOUSE OWNER]: You need food at this time? Let's get into my car; I'll drive you home.");
                    inCar();
                }
                else
                {
                    inCar();
                }
            }
            else
            {
                --relation_house_owner;
                printf("\n[HOUSE OWNER]: Sleepwalking, huh? That's strange.");
            }
        }
        else
        {
            printf("\n[HOUSE OWNER]: You've lost the game. Goodbye.");
        }
    }
    else if (choice == 1)
    {
        printf("\n[HOUSE OWNER]: Here, take this medicine. (+50 health)");
        health += 50;
        checkHealth();
    }
}

void inCar()
{
    int choice;
    printf("\n[NARRATOR]: You get into the car, and the man begins driving you home.");
    printf("\n[HOUSE OWNER]: Let's pass the time with a quiz. Play with me?\n");
    printf("1. Sure, let's play.\n");
    printf("2. No thanks.\n");
    getInput(&choice);
    if (choice == 1)
    {
        ++relation_house_owner;
        printf("\n[NARRATOR]: You play a quick quiz and bond with the house owner. (+1 relationship)");
        int result = playQuizGame();
        if (result < 2)
        {
            printf("\nSuch a shame! You have lost the QUIZ.");
            --relation_house_owner;
        }
        else
        {
            ++relation_house_owner;
            printf("\nYou have won! and you have earned my trust (+1 Relationship)");
        }
    }
    else
    {
        --relation_house_owner;
        printf("\n[HOUSE OWNER]: Fine, be that way. Get out of my car!\n");
        printf("\n[NARRATOR]: He leaves you on the road. You die.");
        health = 0;
        checkHealth();
        return;
    }

    printf("\n[NARRATOR]: You arrive at your home. A suspicious figure is pacing around with a bat in hand.");
    finalScene();
}

void finalScene()
{
    int choice;
    printf("\n[NARRATOR]: The house owner looks at you.");
    printf("\n[HOUSE OWNER]: What now? That doesn't look good.");
    printf("\n1. Ask the house owner to help capture the person.\n");
    printf("2. Ask the house owner to help kill the person.\n");
    getInput(&choice);

    if (choice == 1)
    {
        if (relation_house_owner >= 2)
        {
            s_score++;
            printf("\n[NARRATOR]: The house owner helps you capture the intruder. You've won!\n");
        }
        else
        {
            printf("\n[HOUSE OWNER]: I don't trust you enough to help. Goodbye.");
            printf("\n[NARRATOR]: The intruder attacks you. You die.\n");
            health = 0;
            checkHealth();
        }
    }
    else if (choice == 2)
    {
        if (relation_house_owner < 2)
        {
            printf("\n[NARRATOR]: The house owner smirks. Turns out he's a time-walker. He rewinds time, sending you back to the beginning.\n");
            intro();
        }
        else
        {
            s_score++;
            printf("\n[NARRATOR]: The house owner helps you eliminate the intruder. You survive, but at a cost.\n");
        }
    }
}
