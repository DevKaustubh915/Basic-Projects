#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Bank_Funds = 500000;

struct Account
{
    int Ac_Number;
    char Name[50];
    int Balance;
    int Loan;
};

struct Account account[50];
int count = 0;

void Create_Account()
{
    struct Account new_Account;
    char choice = '\0';
    srand(time(0));
    new_Account.Ac_Number = rand() % 10000;

    printf("Enter Your Name :- ");
    scanf(" %[^\n]s", new_Account.Name);
    printf("Do you want to deposit initial amount(Y/N) :- ");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y')
    {
        printf("Enter The Ammount :- ");
        scanf(" %d", &new_Account.Balance);
    }
    else if (choice == 'n' || choice == 'N')
    {
        new_Account.Balance = 0;
    }
    else
    {
        new_Account.Balance = 0;
        printf("Invalid Input\n");
    }

    new_Account.Loan = 0;

    printf("=================================================================\n");
    printf("Congratulations! You have sucessfully created account.\n");
    printf("-----------------------------------------------------------------\n");
    printf("Your account information is:\n");
    printf("Account Number :- %d\n", new_Account.Ac_Number);
    printf("Name :- %s\n", new_Account.Name);
    printf("Ac Balance :- %d\n", new_Account.Balance);
    printf("Loan :- %d\n", new_Account.Loan);
    printf("=================================================================\n");

    account[count] = new_Account;
    count++;
    return;
}

void Display_Account(int Number)
{

    for (int i = 0; i < count; i++)
    {

        if (Number == account[i].Ac_Number)
        {
            printf("===============================================================\n");

            printf("Your account information is:\n");
            printf("Account Number :- %d\n", account[i].Ac_Number);
            printf("Name :- %s\n", account[i].Name);
            printf("Ac Balance :- %d\n", account[i].Balance);
            printf("Loan :- %d\n", account[i].Loan);
            printf("===============================================================\n");

            return;
        }
    }

    printf("Account Not Found.\n");
    printf("===============================================================\n");

    return;
}

void Deposit_Money(int Number)
{
    int Amount = 0;
    for (int i = 0; i < count; i++)
    {
        if (Number == account[i].Ac_Number)
        {
            printf("Enter Deposit Amount :- ");
            scanf(" %d", &Amount);
            account[i].Balance += Amount;
            printf("\n");
            printf("Current Balance :- %d\n", account[i].Balance);
            printf("\n\n");
            printf("-----------------------------------------------------\n");

            return;
        }
    }
    printf("Account Not Found.\n");
    return;
}

void Withdraw_Money(int Number)
{
    int Amount = 0;
    for (int i = 0; i < count; i++)
    {
        if (Number == account[i].Ac_Number)
        {
            printf("Enter Withdraw Amount :- ");
            scanf(" %d", &Amount);
            if (account[i].Balance >= Amount)
            {
                account[i].Balance -= Amount;
                printf("\n");
                printf("Current Balance :- %d\n", account[i].Balance);
                printf("\n\n");
                printf("-----------------------------------------------------\n");
                return;
            }
            else
            {
                printf("Insufficient funds\n");
                printf("-----------------------------------------------------\n");
            }
        }
    }
    printf("Account Not Found.\n");
    return;
}

void View_All_Accounts()
{
    if (count == 0)
    {
        printf("No Account Records Found.\n");
        return;
    }
    else
    {
        printf("\n");
        printf("===============================================================\n");
        for (int i = 0; i < count; i++)
        {
            printf("%d.\n", i + 1);
            printf("Account Number :- %d\n", account[i].Ac_Number);
            printf("Name :- %s\n", account[i].Name);
            printf("Ac Balance :- %d\n", account[i].Balance);
            printf("Loan :- %d\n", account[i].Loan);
            printf("----------------------------------------------\n");
            printf("\n");
        }
        printf("===============================================================\n");
    }
    return;
}

void Apply_Loan(int number)
{
    int amount = 0;

    for (int i = 0; i < count; i++)
    {
        if (number == account[i].Ac_Number)
        {
            printf("The max limit for Loan is 100000\n");
            printf("Enter the loan ammount :- ");
            scanf(" %d", &amount);

            if (Bank_Funds >= amount)
            {
                account[i].Loan += amount;
                Bank_Funds -= amount;
                printf("\n");
                printf("your loan application granted sucessfully.\n ");
                printf("-----------------------------------------------------\n");

                return;
            }
            else
            {
                printf("Insufficient Bank Funds\n");
                printf("-----------------------------------------------------\n");

                return;
            }
        }
    }
}

void Pay_Loan(int number)
{
    int amount = 0;

    for (int i = 0; i < count; i++)
    {
        if (number == account[i].Ac_Number)
        {
            printf("Enter the ammount :- ");
            scanf(" %d", &amount);

            if (amount <= account[i].Loan)
            {
                account[i].Loan -= amount;
                Bank_Funds += amount;
                printf("\n");
                printf("current loan remaining :- %d\n", account[i].Loan);
                printf("-----------------------------------------------------\n");

                return;
            }
            else
            {
                printf("Invalid amount entered\n");
                printf("-----------------------------------------------------\n");

                return;
            }
        }
    }
}

void Save_Data()
{
    FILE *fp;
    fp = fopen("Bank_Data.csv", "wb");

    if (fp == NULL)
    {
        printf("File not Found or\n cant write to the file\n");
        exit(-1);
        return;
    }
    else
    {
        fwrite(&count, sizeof(int), 1, fp);
        fwrite(account, sizeof(struct Account), count, fp);
        printf("Data saved Sucessfully.");
        fclose(fp);
        return;
    }
}

void Load_Data()
{
    FILE *fp;
    fp = fopen("Bank_Data.csv", "rb");

    if (fp == NULL)
    {
        printf("File not Found\n");
        return;
    }
    else
    {
        fread(&count, sizeof(int), 1, fp);
        fread(account, sizeof(struct Account), count, fp);
        fclose(fp);
        return;
    }
}

int main()
{

    int choice = 0;
    int Ac_Number = 0;

    Load_Data();

    while (1)
    {
        printf("1. Create Account\n");
        printf("2. Display Account\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Apply Loan\n");
        printf("6. pay loan\n");
        printf("7. view all acounts\n");
        printf("8. exit\n");

        printf("Enter the function number :- ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            Create_Account();
            break;
        case 2:

            printf("Enter your Account Number :- ");
            scanf(" %d", &Ac_Number);
            Display_Account(Ac_Number);
            break;
        case 3:
            printf("Enter your Account Number :- ");
            scanf(" %d", &Ac_Number);
            Deposit_Money(Ac_Number);
            break;
        case 4:
            printf("Enter your Account Number :- ");
            scanf(" %d", &Ac_Number);
            Withdraw_Money(Ac_Number);
            break;
        case 5:
            printf("Enter your Account Number :- ");
            scanf(" %d", &Ac_Number);
            Apply_Loan(Ac_Number);
            break;
        case 6:
            printf("Enter your Account Number :- ");
            scanf(" %d", &Ac_Number);
            Pay_Loan(Ac_Number);
            break;
        case 7:
            View_All_Accounts();
            break;
        case 8:
            Save_Data();
            printf("Exting.....\n");
            exit(0);

        default:
            printf("Invalid Input.\n");
            break;
        }
    }

    return 0;
}