#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);
int TakeUserId();
void Registration(struct User *u);
int Check_excit_user(struct User u);
void ChechExistAcount(struct User u);
//char *USERS = "./data/users.txt";

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void clear();
void SaveUser(struct User u);
int CheckTypeAccount(const char type[10]);
int getAccountFromFile(FILE *pf , char name[50] , struct Record *r);
float Calc(float amount, float num);
void Update(struct User u);
void cleanFile();
void UpdatePhone(struct User u, int nbracc);
void UpdateCountry(struct User u , int nbb);
void Removeaccount(struct User u);

