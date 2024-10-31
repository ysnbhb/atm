#include "header.h"
#include <stdlib.h>

const char *RECORDS = "./data/records.txt";
const char *Change = "./data/change.txt";

int getAccountFromFile(FILE *ptr, char name[50], Record *r)
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

void saveAccountToFile(FILE *ptr, User u, Record r)
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

void success(User u)
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

void createNewAcc(User u)
{
    Record r;
    Record cr;
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
        if (r.deposit.month > 12 || r.deposit.month <= 0 || r.deposit.day <= 0 || r.deposit.day > 31 || r.deposit.year < 1900 || valid != 3)
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
        if (!valid || r.amount <= 0)
        {
            valid = 0;
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

void checkAllAccounts(User u)
{
    char userName[100];
    Record r;

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

void ChechExistAcount(User u)
{
    int accountNbr;
    char name[50];
    float num;
    char accept[3];
    int found = 0;
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
    Record r;
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
    if (!found)
        printf("user not found \n");

    fclose(pf);
    printf("hit entre to return Menu...");
    clear();
    mainMenu(u);
}

float Calc(float amount, float num)
{
    return (amount * num) / 12;
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

void MakeTrans(User u)
{
    int option = 200;
    printf("1) Depositing\n2) Withdrawing\n3) Create transactions\nChoose one of these options: ");
notOption:
    scanf("%d", &option);
    clear();
    if (option <= 3 && option > 0)
    {
        MakeTranc(u, option - 1);
    }
    else
    {
        printf("invalid optiones\n");
        goto notOption;
    }
}

int NotAllow(char type[10])
{
    if (strcmp(type, "fixed01") == 0 || strcmp(type, "fixed03") == 0 || strcmp(type, "fixed02") == 0)
        return 1;
    return 0;
}

int Take_id_User(char name[50])
{
    User userChecker;
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

Valid CheckEXictAcc(User u, int nbacc)
{
    // char user[50];
    Record r;
    User user;
    Valid found;
    found.found = 0;
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
            found.found = 1;
            strcpy(found.type, r.accountType);
        }
        saveAccountToFile(chang, user, r);
    }
    fclose(fp);
    fclose(chang);
    if (!found.found)
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
    User u;
    Record r;
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
    Record r;
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

void MakeTranc(User user, int type)
{
    int from, to, mony, phone, chois = 0;
    int valid = 0;
    char toname[50], newCountry[50];
    while (!valid)
    {
        printMessage(type);
        valid = scanf("%d", &from);
        clear();
        if (!valid)
        {
            printf("Invalid input for numbre account.\n");
        }
    }
    Valid valide = CheckEXictAcc(user, from);
    if (!valide.found)
    {
        printf("this account dones't exist\nPress Enter to return to the menu.");
        clear();
        mainMenu(user);
    }
    if (type == 0 || type == 1 || type == 2)
        if (NotAllow(valide.type))
        {
            printf("This account has no right to make transaction\nPress Enter to return to the menu...");
            remove(Change);
            clear();
            mainMenu(user);
        }
    int validInput = 0;
    if (type == 7)
    {
        while (!chois)
        {
            printf("what would you want update \n1)->phone numbre\n2)->country\n enter you chois : ");
            scanf("%d", &chois);
            clear();
            if (chois == 1)
            {
                while (!validInput)
                {
                    printf("Enter new phone number: ");
                    if (scanf("%d", &phone) == 1 && phone > 0)
                    {
                        validInput = 1;
                    }
                    else
                    {
                        clear();
                    }
                }
                type = 5;
            }
            else if (chois == 2)
            {
                do
                {
                    printf("enter new country : ");
                    scanf("%s", newCountry);

                } while (chechInput(newCountry));
                type = 6;
            }
            else
            {
                printf("invalid Option");
                chois = 0;
            }
        }
    }
    int userid;
    valid = 0;
    if (type == 2)
    {
        to = FindTo(user);
    }
    else if (type == 3)
    {
        printf("entre name user you want give him account: ");
        scanf("%s", toname);
        clear();
        userid = Take_id_User(toname);
        if (userid == -1)
        {
            printf("user you want give him account dones't exist\nPress entre to return to menu...");
            remove(Change);
            clear();
            mainMenu(user);
        }
    }
    if (type == 0 || type == 1 || type == 2)
        while (!valid)
        {
            printf("entre how much mony : ");
            valid = scanf("%d", &mony);
            if (mony <= 0)
            {
                valid = 0;
            }
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
    User userCheck;
    Record r;
    cleanFile();

    while (getAccountFromFile(chang, userCheck.name, &r))
    {
        if (r.accountNbr == from)
        {
            if (type == 5)
            {
                r.phone = phone;
            }
            else if (type == 6)
            {
                strcpy(r.country, newCountry);
            }
            if (type == 4)
            {
                continue;
            }
            else if (type == 3)
            {
                r.userId = userid;
                strcpy(userCheck.name, toname);
            }
            else if (type == 0)
            {
                r.amount += mony;
            }
            else
            {
                if (r.amount - mony < 0)
                {
                    printf("You don't have enough money in this account.\nPress Enter to return to the menu...");
                    cleanFile();
                    Return();
                    clear();
                    mainMenu(user);
                }
                r.amount -= mony;
            }
        }
        else if (r.accountNbr == to && type == 2)
        {
            r.amount += mony;
        }
        saveAccountToFile(fp, userCheck, r);
    }
    fclose(fp);
    fclose(chang);
    remove(Change);
    success(user);
}

int FindTo(User user)
{
    int valid = 0, to;
    printf("entre numbre account you want send to");
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
        mainMenu(user);
    }
    return to;
}

void printMessage(int type)
{
    if (type == 1)
    {
        printf("Enter the account number you want to withdraw from: ");
    }
    else if (type == 0)
    {
        printf("Enter the account number you want to deposit into: ");
    }
    else if (type == 2)
    {
        printf("entre numbre account you want take from it: ");
    }
    else if (type == 3)
    {
        printf("entre numbre account you want to give: ");
    }
    else if (type == 4)
    {
        printf("Enter numbre account you want delete : ");
    }
    else
    {
        printf("entre Account numbre : ");
    }
}
