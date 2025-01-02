#include<stdio.h>
#include<string.h>
#define MAX_ITEMS 100

typedef struct
{
    int register_number;
    char name[100];
    char gender[21];
    int year;
    char department[100];
    char email[101];
    long phone_number;   
    int dob;             
    char father_name[100];
    char mother_name[100];
    long father_number;  
    long mother_number;  
    char caste[51];
    char community[51];
    char nationality[51];
    char mother_tongue[51];
    char address[101];
    char city[101];
    char province[101];
    int postal_code;
} information;

information students[MAX_ITEMS];
int stucount = 0;

// Function to add a new student's information
void addition()
{
    if (stucount == MAX_ITEMS)
    {
        printf("Inventory is filled\n");
        return;
    }

    
    getchar();  
    printf("Enter Student register number: ");
    scanf("%d", &students[stucount].register_number);
    
    getchar();  

    printf("Enter Student Name: ");
    fgets(students[stucount].name, 100, stdin);
    students[stucount].name[strcspn(students[stucount].name, "\n")] = '\0';  

    printf("Enter Student Gender(M/F/Transgender): ");
    fgets(students[stucount].gender, 21, stdin);
    students[stucount].gender[strcspn(students[stucount].gender, "\n")] = '\0'; 

    printf("Enter Year of pursuing: ");
    scanf("%d", &students[stucount].year);

    getchar();  

    printf("Enter Student Department: ");
    fgets(students[stucount].department, 100, stdin);
    students[stucount].department[strcspn(students[stucount].department, "\n")] = '\0';  

    printf("Enter Student E-Mail id: ");
    scanf("%s", students[stucount].email);

    printf("Enter Student Phone number: ");
    scanf("%ld", &students[stucount].phone_number);  

    printf("Enter Student Date Of Birth (ddmmyyyy): ");
    scanf("%d", &students[stucount].dob);

    getchar();  

    printf("Enter Father's Name: ");
    fgets(students[stucount].father_name, 100, stdin);
    students[stucount].father_name[strcspn(students[stucount].father_name, "\n")] = '\0';  

    printf("Enter Father's Phone Number: ");
    scanf("%ld", &students[stucount].father_number);  

    getchar();  

    printf("Enter Mother's Name: ");
    fgets(students[stucount].mother_name, 100, stdin);
    students[stucount].mother_name[strcspn(students[stucount].mother_name, "\n")] = '\0';  

    printf("Enter Mother's Phone Number: ");
    scanf("%ld", &students[stucount].mother_number);  

    getchar();  

    printf("Enter Caste: ");
    fgets(students[stucount].caste, 51, stdin);
    students[stucount].caste[strcspn(students[stucount].caste, "\n")] = '\0';  

    printf("Enter Community: ");
    fgets(students[stucount].community, 51, stdin);
    students[stucount].community[strcspn(students[stucount].community, "\n")] = '\0';  

    printf("Enter Nationality: ");
    fgets(students[stucount].nationality, 51, stdin);
    students[stucount].nationality[strcspn(students[stucount].nationality, "\n")] = '\0';  

    printf("Enter Mother Tongue: ");
    fgets(students[stucount].mother_tongue, 51, stdin);
    students[stucount].mother_tongue[strcspn(students[stucount].mother_tongue, "\n")] = '\0';  
    
    printf("Enter Address: ");
    fgets(students[stucount].address, 101, stdin);
    students[stucount].address[strcspn(students[stucount].address, "\n")] = '\0';  

    printf("Enter City: ");
    fgets(students[stucount].city, 101, stdin);
    students[stucount].city[strcspn(students[stucount].city, "\n")] = '\0';  

    printf("Enter Province: ");
    fgets(students[stucount].province, 101, stdin);
    students[stucount].province[strcspn(students[stucount].province, "\n")] = '\0';  

    printf("Enter Postal code: ");
    scanf("%d", &students[stucount].postal_code);

    stucount++;
    printf("Information stored\n");
}

int main()
{
    int choice;
    do
    {
        printf("Enter Your Choice:\n");
        printf("1. Addition\n");
        printf("0. Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addition();
            break;
        case 0:
            break;
        default:
            printf("Enter a valid choice\n");
        }
    } while (choice != 0);

    return 0;
}
