#include "header.h"
#include <stdlib.h>

const char *RECORDS = "./data/records.txt";
const char *Change = "./data/change.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            r.userId,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        clear();
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
        clear();
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    clear();
    printf("%d", option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    int valid = 0;
    system("clear");
noAccount:
    r.id = 0;
    printf("\t\t\t===== New record =====\n");

    while (!valid)
    {
        printf("\nEnter today's date(mm/dd/yyyy):");
        valid = scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
        //  printf("%d",valid);
        clear();
        if (r.deposit.month > 12 || r.deposit.month < 0 || r.deposit.day < 0 || r.deposit.day > 31 || r.deposit.year < 0 || valid != 3)
        {
            printf("This input is invalide");
            valid = 0;
        }
    }
    valid = 0;
    while (!valid)
    {
        printf("\nEnter the account number:");
        valid = scanf("%d", &r.accountNbr);
        clear();
        if (!valid)
        {
            printf("This input is invalide");
        }
    }

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
        r.id++;
    }
    do
    {
        printf("\nEnter the country:");
        scanf("%s", r.country);
        clear();

    } while (chechInput(r.country));

    valid = 0;
    while (!valid)
    {
        printf("\nEnter the phone number:");
        valid = scanf("%d", &r.phone);
        clear();
        if (!valid || r.phone <= 0)
        {
            valid = 0;
            printf("This input is invalide");
        }
    }
    valid = 0;
    while (!valid)
    {
        printf("\nEnter amount to deposit: $");
        valid = scanf("%lf", &r.amount);
        clear();
        if (!valid)
        {
            printf("This input is invalide");
        }
    }
    do
    {
        printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
        scanf("%s", r.accountType);
        clear();

    } while (CheckTypeAccount(r.accountType));
    r.userId = u.id;

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void clear()
{
    char l;
    while ((l = getchar()) != EOF && l != '\n')
    {
    }
}

int CheckTypeAccount(const char type[10])
{
    if (strcmp(type, "saving") == 0 || strcmp(type, "current") == 0 || strcmp(type, "fixed01") == 0 || strcmp(type, "fixed02") == 0 || strcmp(type, "fixed03") == 0)
        return 0;
    return 1;
}

void ChechExistAcount(struct User u)
{
    int accountNbr;
    char name[50];
    float num;
    char accept[3];
    int found;
notValid:
    printf("entre Account numbre : ");
    if (scanf("%d", &accountNbr) != 1)
    {
        clear();
        printf("put numbre not string... \n");
        goto notValid;
    }
    clear();
    FILE *pf = fopen(RECORDS, "r");
    struct Record r;
    while (getAccountFromFile(pf, name, &r))
    {
        if (strcmp(name, u.name) == 0 && r.accountNbr == accountNbr)
        {
            found = 1;
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
            if (strcmp(r.accountType, "saving") == 0)
            {
                num = r.amount * 7.00 / 100;
                printf("You will get $%.2f as interest on day %d of every month\n", num / 12, r.deposit.day);
            }
            else if ((strcmp(r.accountType, "fixed01") == 0))
            {
                num = r.amount * 4.00 / 100;
                printf("You will get $%.2f as interest on day %d/%d/%d\n", num, r.deposit.month, r.deposit.day, r.deposit.year + 1);
            }
            else if ((strcmp(r.accountType, "fixed02") == 0))
            {
                num = r.amount * 5.00 / 100;
                printf("You will get $%.2f as interest on day %d/%d/%d\n", num * 2, r.deposit.month, r.deposit.day, r.deposit.year + 2);
            }
            else if ((strcmp(r.accountType, "fixed03") == 0))
            {
                num = r.amount * 8.00 / 100;
                printf("You will get $%.2f as interest on day %d/%d/%d\n", num * 3, r.deposit.month, r.deposit.day, r.deposit.year + 3);
            }
        }
    }
    fclose(pf);
    if (!found)
        printf("user not found \n");
    printf("hit entre to return Menu...");
    clear();
    mainMenu(u);
}

float Calc(float amount, float num)
{
    return (amount * num) / 12;
}

void Update(struct User u)
{
    int accountNbr, chois;
notValid:
    printf("entre Account numbre : ");
    if (scanf("%d", &accountNbr) != 1)
    {
        clear();
        printf("invalid forma \n");
        goto notValid;
    }
    clear();
    if (!CheckEXictAcc(u, accountNbr))
    {
        printf("account not found...\nhit entre to entre the menu ");
        clear();
        mainMenu(u);
    }
    printf("what would you want update \n1)->phone numbre\n2)->country\n enter you chois : ");
NoOption:
    scanf("%d", &chois);
    clear();
    switch (chois)
    {
    case 1:
        UpdatePhone(u, accountNbr);

        break;
    case 2:
        UpdateCountry(u, accountNbr);
        break;
    default:
        printf("invalid option... \n");
        goto NoOption;
    }
}

void cleanFile()
{
    FILE *fp = fopen(RECORDS, "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file for truncation\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

void UpdatePhone(struct User u, int nbracc)
{
    int phone;
    int validInput = 0;
    int found = 0;
notValid:
    while (!validInput)
    {
        printf("Enter new phone number: ");
        if (scanf("%d", &phone) == 1)
        {
            validInput = 1;
        }
        else
        {
            clear();
        }
    }
    clear();
    struct User user;
    struct Record r;
    FILE *fp = fopen(RECORDS, "a+");
    FILE *chang = fopen(Change, "r+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    cleanFile();
    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == nbracc)
        {
            r.phone = phone;
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

void UpdateCountry(struct User u, int nbracc)
{
    int found = 0;
    char newcountry[100];
    printf("enter new country : ");
    scanf("%s", newcountry);
    clear();
    FILE *chang = fopen(Change, "r+");
    if (chang == NULL)
    {
        fprintf(stderr, "Failed to open change file\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open records file\n");
        fclose(chang);
        exit(EXIT_FAILURE);
    }
    cleanFile();
    struct User user;
    struct Record r;
    while (getAccountFromFile(chang, u.name, &r))
    {
        if (r.accountNbr == nbracc)
        {
            strcpy(r.country, newcountry);
        }
        saveAccountToFile(fp, u, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

void Removeaccount(struct User u)
{
    int validInput = 0;
    int numbreacc;
    int found = 0;
    while (!validInput)
    {
        printf("Enter numbre account ");
        validInput = scanf("%d", &numbreacc);
        clear();
    }
    if (!CheckEXictAcc(u, numbreacc))
    {
        printf("this account not exist\nPress entre to return to mune.");
        clear();
        mainMenu(u);
    }

    FILE *chang = fopen(Change, "r+");
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    struct User user;
    struct Record r;
    cleanFile();
    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == numbreacc)
        {
            continue;
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

void MakeTrans(struct User u)
{
    int option;
    printf("1) Withdrawing\n2) Depositing money\n3) Create transactions\nChoose one of these options: ");

    scanf("%d", &option);

    clear();
    switch (option)
    {
    case 1:
        printf("withdrawing\n");
        Withd(u);
        break;
    case 2:
        printf("depositing money\n");
        Deposit(u);
        break;
    case 3:
        printf("make  transactions\n");
        Trans(u);
        break;
    default:
        printf("invalid optiones\n");
        break;
    }
}

void Withd(struct User u)
{
    int nmbAcc;
    int valid = 0;
    int found = 0;
    double mony;
    while (!valid)
    {
        printf("Enter the account number you want to withdraw from: ");
        valid = scanf("%d", &nmbAcc);
        clear();
        if (!valid)
        {
            printf("Invalid input for account number.\n");
        }
    }
    if (!CheckEXictAcc(u, nmbAcc))
    {
        printf("account not found...\nhit entre to entre the menu ");
        clear();
        mainMenu(u);
    }

    valid = 0;
    while (!valid)
    {
        printf("Enter how much you want to withdraw: ");
        valid = scanf("%lf", &mony);
        clear();
        if (!valid)
        {
            printf("Invalid input for withdrawal amount.\n");
        }
    }
    FILE *chang = fopen(Change, "r+");
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    struct User user;
    struct Record r;
    cleanFile();
    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == nmbAcc)
        {
            if (r.amount - mony < 0)
            {
                printf("You don't have enough money in this account.\nPress Enter to return to the menu...");
                cleanFile();
                Return();
                clear();
                mainMenu(u);
            }
            else
            {
                r.amount -= mony;
            }
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

void Deposit(struct User u)
{
    int nmbAcc;
    int valid = 0;
    int found = 0;
    double mony;
    while (!valid)
    {
        printf("Enter the account number you want to deposit into: ");
        valid = scanf("%d", &nmbAcc);
        clear();
        if (!valid)
        {
            printf("Invalid input for account number.\n");
        }
    }
    if (!CheckEXictAcc(u, nmbAcc))
    {
        printf("account not found\nPress Enter to return to the menu...");
        clear();
        mainMenu(u);
    }
    valid = 0;
    while (!valid)
    {
        printf("Enter how much you want to deposit: ");
        valid = scanf("%lf", &mony);
        clear();
        if (!valid)
        {
            printf("Invalid input for deposit amount.\n");
        }
    }
    FILE *chang = fopen(Change, "r+");
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    struct User user;
    struct Record r;
    cleanFile();
    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == nmbAcc)
        {
            r.amount += mony;
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

void Trans(struct User u)
{
    int from, to, foundform = 0, foundto = 0, mony;
    int valid = 0;
    while (!valid)
    {
        printf("entre numbre account you want take from it: ");
        valid = scanf("%d", &from);
        clear();
        if (!valid)
        {
            printf("Invalid input for numbre account.\n");
        }
    }
    if (!CheckEXictAcc(u, from))
    {
        printf("this account dones't exist\nPress Enter to return to the menu.");
        clear();
        mainMenu(u);
    }
    else if (CheckAccType(from))
    {
        printf("This account has no right to make transaction\nPress Enter to return to the menu...");
        remove(Change);
        clear();
        mainMenu(u);
    }
    valid = 0;
    while (!valid)
    {
        printf("entre numbre account you want send to it: ");
        valid = scanf("%d", &to);
        clear();
        if (!valid)
        {
            printf("Invalid input for numbre account.\n");
        }
    }
    if (CheckAcc(to))
    {
        printf("The user you want to send to doesn't exist.\nPress Enter to return to the menu.");
        remove(Change);
        clear();
        mainMenu(u);
    }
    valid = 0;
    while (!valid)
    {
        printf("entre how much you want send: ");
        valid = scanf("%d", &mony);
        clear();
        if (!valid)
        {
            printf("Invalid input for  amount.\n");
        }
    }
    FILE *chang = fopen(Change, "r+");
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    struct User user;
    struct Record r;
    cleanFile();

    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == from)
        {
            if (r.amount - mony < 0)
            {
                printf("You don't have enough money in this account.\nPress Enter to return to the menu...");
                cleanFile();
                Return();
                clear();
                mainMenu(u);
            }
            else
            {
                r.amount -= mony;
            }
        }
        else if (r.accountNbr == to)
        {
            r.amount += mony;
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

int NotAllow(char type[10])
{
    if (strcmp(type, "fixed01") == 0 || strcmp(type, "fixed03") == 0 || strcmp(type, "fixed02") == 0)
        return 1;
    return 0;
}

void TranOwen(struct User u)
{
    int numacc;
    int valid = 0;
    char toname[50];
    int userid;
    while (!valid)
    {
        printf("entre numbre account you want to give: ");
        valid = scanf("%d", &numacc);
        if (!valid)
        {
            printf("invalid input for numbre acount\n");
        }
        clear();
    }
    if (!CheckEXictAcc(u, numacc))
    {
        printf("this account dones't exist\nPress Enter to return to the menu.");
        clear();
        mainMenu(u);
    }
    valid = 0;
    printf("entre name user you want give him account: ");
    scanf("%s", toname);
    clear();
    userid = Take_id_User(toname);
    if (userid == -1)
    {
        printf("user you want give him account dones't exist\nPress entre to return to menu...");
        remove(Change);
        clear();
        mainMenu(u);
    }

    FILE *chang = fopen(Change, "r+");
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    struct User user;
    struct Record r;
    cleanFile();

    while (getAccountFromFile(chang, user.name, &r))
    {
        if (r.accountNbr == numacc)
        {
            r.userId = userid;
            strcpy(user.name, toname);
        }
        saveAccountToFile(fp, user, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(u);
}

int Take_id_User(char name[50])
{
    struct User userChecker;
    FILE *fp;
    fp = fopen("./data/users.txt", "r+");
    if ((fp == NULL))
    {
        printf("Error! opening file\n");
        exit(1);
    }
    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, name) == 0)
        {
            return userChecker.id;
        }
    }

    return -1;
}

int CheckEXictAcc(struct User u, int nbacc)
{
    // char user[50];
    struct Record r;
    struct User user;
    int found = 0;
    FILE *fp, *chang;
    remove(Change);
    fp = fopen(RECORDS, "r");
    chang = fopen(Change, "a+");
    if (fp == NULL || chang == NULL)
    {
        fprintf(stderr, "can't open file");
        exit(1);
    }
    while (getAccountFromFile(fp, user.name, &r))
    {
        if (strcmp(user.name, u.name) == 0 && nbacc == r.accountNbr)
        {
            found = 1;
        }
        saveAccountToFile(chang, user, r);
    }
    fclose(fp);
    fclose(chang);
    if (!found)
        remove(Change);
    return found;
}

void Return()
{
    FILE *chang = fopen(Change, "r+");
    if (chang == NULL)
    {
        fprintf(stderr, "Failed to open change file\n");
        exit(EXIT_FAILURE);
    }
    FILE *fp = fopen(RECORDS, "a+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open records file\n");
        fclose(chang);
        exit(EXIT_FAILURE);
    }
    struct User u;
    cleanFile();
    struct User user;
    struct Record r;
    while (getAccountFromFile(chang, u.name, &r))
    {

        saveAccountToFile(fp, u, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
}

int CheckAcc(int acc)
{
    struct Record r;
    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open records file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    char user[50];
    while (getAccountFromFile(fp, user, &r))
    {
        if (r.accountNbr == acc)
        {
            return 0;
        }
    }
    return 1;
}

int CheckAccType(int accnb)
{
    FILE *fp = fopen(RECORDS, "r+");
    struct Record r;
    if (fp == NULL)
    {
        fclose(fp);
        fprintf(stderr, "can't open file");
        exit(1);
    }
    char user[50];
    while (getAccountFromFile(fp, user, &r))
    {
        if (r.accountNbr == accnb)
        {
            return NotAllow(r.accountType);
        }
    }
    return -1;
}