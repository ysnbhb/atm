#include <termios.h>
#include <stdlib.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            char *buf = userChecker.password;
            fclose(fp);
            return buf;
        }
    }

    fclose(fp);
    return "user not excit";
}

void Registration(struct User *user)
{
    struct termios oflags, nflags;
    char pass[50];
    while (1){
        printf("\n\t\t\t\tUser Login \n");
        scanf("%s", user->name);
        if(Chech_excit_user(*user)==0){
            printf("this user name is realy used , try anthor user name ...\n");
        }else {
             break;
        }
    }


notSame:
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", user->password);

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login again :");
    scanf("%s", pass);
    if (strcmp(pass, user->password) != 0)
    {
        printf("not the same please try again : \n");
        if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
        {
            perror("tcsetattr");
            return exit(1);
        }
        goto notSame;
    }
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    user->id = TakeUserId() + 1;
    SaveUser(*user);
    createNewAcc(*user);
}

int TakeUserId()
{
    FILE *fp;
    struct User userChecker;
    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
    }
    return userChecker.id;
}

int Chech_excit_user(struct User u)
{
    FILE *fp;
    struct User userChecker;
    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(u.name, userChecker.name) == 0)
            return 0;
    }
    return 1;
}
