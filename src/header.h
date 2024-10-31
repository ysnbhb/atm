#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
typedef struct
{
    int id;
    int userId;
    char name[50];
    char country[50];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
} Record;

typedef struct
{
    int id;
    char name[50];
    char password[50];
} User;

typedef struct
{
    int found;
    char type[10];
} Valid;

// authentication functions
void loginMenu(char a[50], char pass[50]);
const char *getPassword(User *u);
int TakeUserId();
void Registration(User *u);
int Check_excit_user(char u[50]);
void ChechExistAcount(User u);
void SaveUser(User u);
int chechInput(const char r[50]);


// system function
void createNewAcc(User u);
void mainMenu(User u);
void checkAllAccounts(User u);
void clear();
int CheckTypeAccount(const char type[10]);
int getAccountFromFile(FILE *pf, char name[50], Record *r);
void cleanFile();
void MakeTrans(User u);
int NotAllow(char type[10]);
int Take_id_User(char toname[50]);
Valid CheckEXictAcc(User u, int nbacc);
void Return();
int CheckAcc(int acc);
void MakeTranc(User user, int type);
void printMessage(int type);
int FindTo(User user);