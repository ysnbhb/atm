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

noAccount:
    r.id = 0;
    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
        r.id++;
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    clear();

    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
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

void SaveUser(struct User user)
{
    FILE *fp;
    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }
    fprintf(fp, "%d %s %s\n",
            user.id,
            user.name,
            user.password);
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
notValid:
    printf("entre Account numbre : ");
    if (scanf("%d", &accountNbr) != 1)
    {
        clear();
        printf("put numbre not string... \n");
        goto notValid;
    }
    FILE *pf = fopen(RECORDS, "r");
    struct Record r;
    while (getAccountFromFile(pf, name, &r))
    {
        if (strcmp(name, u.name) == 0 && r.accountNbr == accountNbr)
        {
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
            }
            else if ((strcmp(r.accountType, "fixed01") == 0))
            {
                num = Calc(r.amount, 4.00 / 100);
            }
            else if ((strcmp(r.accountType, "fixed02") == 0))
            {
                num = Calc(r.amount, 5.00 / 100);
            }
            else if ((strcmp(r.accountType, "fixed03") == 0))
            {
                num = Calc(r.amount, 8.00 / 100);
            }
            else
            {
                return;
            }
            printf("You will get $%.2f as interest on day %d of every month\n", num, r.deposit.day);
            fclose(pf);
            success(u);
        }
    }
    printf("this account Not Exist... \ndo you want try again : \n(yes/no)");
    scanf("%s", accept);
    clear();

    if (strcmp(accept, "ok") == 0)
        goto notValid;
    fclose(pf);
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
    printf("what would you want update \n1) ->phone nubre\n2)->country\n enter you chois : ");
NoOption:
    if (scanf("%d", &chois))
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
        char ok[5];
        printf("use not found...\nwould you try again(yes/no) : ");
        scanf("%s", ok);
        clear();

        if (strcmp(ok, "yes") == 0)
            goto notValid;
        mainMenu(u);
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
        char ok[5];
        printf("use not found...\nwould you try again(yes/no) : ");
        scanf("%s", ok);
        if (strcmp(ok, "yes") == 0)
            goto notValid;
        mainMenu(u);
    }
}

void Removeaccount(struct User u)
{
    int validInput = 0;
    int numbreacc;
    int found = 0;
notValid:
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
        char ok[5];
        printf("use not found...\nwould you try again(yes/no) : ");
        scanf("%s", ok);
        if (strcmp(ok, "yes") == 0)
            goto notValid;
        mainMenu(u);
    }
}