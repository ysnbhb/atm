#include "header.h"
#include <stdlib.h>

const char *RECORDS = "./data/records.txt";

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
                num = Calc(r.amount, 7.00 / 100);
                printf("You will get $%.2f as interest on day %d of every month\n", num, r.deposit.day);
            }
            else if ((strcmp(r.accountType, "fixed01") == 0))
            {
                num = Calc(r.amount, 4.00 / 100);
                printf("You will get $%.2f as interest on day %d of every month\n", num, r.deposit.day);
            }
            else if ((strcmp(r.accountType, "fixed02") == 0))
            {
                num = Calc(r.amount, 5.00 / 100);
                printf("You will get $%.2f as interest on day %d of every month\n", num, r.deposit.day);
            }
            else if ((strcmp(r.accountType, "fixed03") == 0))
            {
                num = Calc(r.amount, 8.00 / 100);
                printf("You will get $%.2f as interest on day %d of every month\n", num, r.deposit.day);
            }
        }
    }
    fclose(pf);
    if (found)
        stayOrReturn(1, NULL, u);
    stayOrReturn(0, ChechExistAcount, u);
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
    printf("what would you want update \n1) ->phone nubre\n2)->country\n enter you chois : ");
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
    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (strcmp(user[i].name, u.name) == 0 && r[i].accountNbr == nbracc)
        {
            found = 1;
            r[i].phone = phone;
        }
        i++;

        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < i; j++)
        {
            r[i].userId = user[i].id;
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Update, u);
    }
}

void UpdateCountry(struct User u, int nbracc)
{
    int found = 0;
    char nercountry[100];
notValid:
    printf("enter new country : ");
    scanf("%s", nercountry);
    clear();

    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }

    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (strcmp(user[i].name, u.name) == 0 && r[i].accountNbr == nbracc)
        {
            found = 1;
            strcpy(r[i].country, nercountry);
        }
        i++;

        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < i; j++)
        {
            r[i].userId = user[i].id;
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Update, u);
    }
}

void Removeaccount(struct User u)
{
    int validInput = 0;
    int numbreacc;
    int found = 0;
    while (!validInput)
    {
        printf("Enter numbre account ");
        if (scanf("%d", &numbreacc) == 1)
        {
            validInput = 1;
        }
        else
        {
            clear();
        }
    }
    clear();
    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    struct Record checkRec;
    // struct User checkUser ;
    char name[50];

    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (getAccountFromFile(fp, name, &checkRec))
    {
        if (strcmp(name, u.name) == 0 && checkRec.id == numbreacc)
        {
            found = 1;
        }
        else
        {
            r[i].deposit.day = checkRec.deposit.day;
            r[i].deposit.month = checkRec.deposit.month;
            r[i].deposit.year = checkRec.deposit.year;
            strcpy(r[i].country, checkRec.country);
            strcpy(user[i].name, name);
            strcpy(r[i].accountType, checkRec.accountType);
            r[i].amount = checkRec.amount;
            r[i].phone = checkRec.phone;
            r[i].userId = checkRec.userId;
            i++;

            if (i >= capacity)
            {
                capacity *= 2;
                r = realloc(r, sizeof(struct Record) * capacity);
                user = realloc(user, sizeof(struct User) * capacity);
                if (r == NULL || user == NULL)
                {
                    fprintf(stderr, "Memory reallocation failed\n");
                    fclose(fp);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++)
        {
            r[j].id = j;
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Removeaccount, u);
    }
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
nomony:
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
    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (r[i].accountNbr == nmbAcc && strcmp(u.name, user[i].name) == 0)
        {
            if (r[i].amount - mony < 0)
            {
                printf("you don't have this mony this you account...\n");
                goto nomony;
            }
            else
            {
                found = 1;
                r[i].amount -= mony;
            }
        }
        i++;
        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++)
        {
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Withd, u);
    }
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
nomony:
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
    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (r[i].accountNbr == nmbAcc && strcmp(u.name, user[i].name) == 0)
        {

            found = 1;
            r[i].amount += mony;
        }
        i++;
        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++)
        {
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Withd, u);
    }
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
nomony:
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

    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (r[i].accountNbr == from && strcmp(u.name, user[i].name) == 0)
        {
            if (NotAllow(r[i].accountType) == 1)
            {
                printf("sorrey but you can't make transactions whit this account...\n");
                return;
            }
            if (r[i].amount - mony < 0)
            {
                printf("you don't have this mony this you account...\n");
                goto nomony;
            }
            else
            {
                foundform = 1;
                r[i].amount -= mony;
            }
        }
        else if (r[i].accountNbr == to)
        {
            foundto = 1;
            r[i].amount += mony;
        }
        i++;
        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (foundform && foundto)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++)
        {
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, Trans, u);
    }
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
    int valid = 0, found = 0;
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
    printf("entre the name of user you want send your account to : ");
    scanf("%s", toname);
    clear();
    userid = Take_id_User(toname);
    if (userid == -1)
    {
        printf("user not found\n");
        stayOrReturn(1, NULL, u);
    }

    FILE *fp = fopen(RECORDS, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    int capacity = 10;
    struct Record *r = malloc(sizeof(struct Record) * capacity);
    struct User *user = malloc(sizeof(struct User) * capacity);
    if (r == NULL || user == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (getAccountFromFile(fp, user[i].name, &r[i]))
    {
        if (strcmp(u.name, user[i].name) == 0 && r[i].accountNbr == numacc)
        {
            r[i].userId = userid;
            strcpy(user[i].name, toname);
            found = 1;
        }

        i++;
        if (i >= capacity)
        {
            capacity *= 2;
            r = realloc(r, sizeof(struct Record) * capacity);
            user = realloc(user, sizeof(struct User) * capacity);
            if (r == NULL || user == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                fclose(fp);
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found)
    {
        cleanFile(); // Clear the file before writing updated records

        fp = fopen(RECORDS, "a"); // Reopen file in append mode to add records
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file for writing\n");
            free(r);
            free(user);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < i; j++)
        {
            saveAccountToFile(fp, user[j], r[j]);
        }
        free(r);
        free(user);
        fclose(fp);
        success(u);
    }
    else
    {
        free(r);
        free(user);
        fclose(fp);
        stayOrReturn(0, TranOwen, u);
    }
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