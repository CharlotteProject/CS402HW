

#include <stdio.h>
#include <string.h>
#include "library.h"
#define MAXNAME 64

// Declare a structure to represent an employee
extern FILE *file; //variable: read data file
struct employee  // Data structure used to store employees into the DB
{
    char fname[MAXNAME];
    char lname[MAXNAME];
    int id;
    int salary;
};

// Global variables
struct employee db[1024]; // An array to store employee records in the database
int employee_counter = 0; // Keeps track of the number of employees in the DB


// Function to look up a user from the DB by Employee ID using binary search
int LookupID(struct employee arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
      
        if (arr[mid].id == x) 
            return mid; 
  
        
        if (arr[mid].id > x) 
            return LookupID(arr, l, mid - 1, x); 
  
       
        return LookupID(arr, mid + 1, r, x); 
    } 
  
    
    return -1; // Element not found
} 

// Function to print the database        
void PrintDB (struct employee x[], int x_size)
{
    int i;

    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < x_size; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", x[i].fname,x[i].lname,x[i].salary, x[i].id);
    }
    printf("----------------------------------------------\n");
    printf(" Number of Employees (%d)\n", x_size);
}


// Function to add an employee to the DB
int AddEmployee(struct employee arr[])
{
    char newfname[MAXNAME];
    char newlname[MAXNAME];
    int newsalary;
    int confirm;

    printf("\nEnter the first name of the employee: ");
    scanf("%s", newfname);
    if (strlen(newfname) > 64)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("Enter the last name of the employee: ");
    scanf("%s", newlname);
    if (strlen(newfname) > 64)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &newsalary);
    if (newsalary < 30000 || newsalary > 150000)
    {
        printf("Invalid entry. Please try again.\n");
        return 0;
    }
    printf("\nDo you want to add the following employee to the DB?\n");
    printf("\t%s %s, \tSalary: %d\n", newfname, newlname, newsalary);
    printf("\nEnter 1 for yes, 0 for no: ");
    scanf("%d", &confirm);

    if (confirm == 1)
    {
        strcpy(db[employee_counter].fname, newfname);
        strcpy(db[employee_counter].lname, newlname);
        db[employee_counter].salary = newsalary;
        db[employee_counter].id = db[employee_counter -1].id + 1;
        employee_counter++;
        printf("New employee added!\n");
    }
    return 1;
}

// Function to look up a user from the DB by last name using linear search
int LookupLName (struct employee arr[], int m, char* name)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (strcmp(arr[i].lname, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to create the database by loading data from a file
void CreateDB(char* datafile)
{
    if (open_file(datafile) == 0)
    {
        char buffer[135];
        int ret;
        while (fgets(buffer, sizeof(buffer), file)) 
        {
            ret = read_int(buffer, 1, &db[employee_counter].id);
            ret = read_int(buffer, 2, &db[employee_counter].salary);
            ret = read_string(buffer, 1, db[employee_counter].fname);
            ret = read_string(buffer, 2, db[employee_counter].lname);
            employee_counter++; 
        }

        if (feof(file)) // hit end of file
        {
            close_file();
        } 
    }
}

// Swap two elements in the array
void Swap(struct employee* xp, struct employee* yp) 
{ 
    struct employee temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// Function to perform Selection Sort on Employee ID
void SelectionSort(struct employee arr[], int n) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < n - 1; i++) { 
   
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j].id < arr[min_idx].id) 
                min_idx = j; 
  
        Swap(&arr[min_idx], &arr[i]); 
    } 
} 

// Main function 
int main(int argc, char *argv[])
{
    if ( argc != 2 ) 
    {
        printf( "usage: %s filename\n", argv[0] );
    } else {   
        CreateDB(argv[1]);        
        SelectionSort(db, employee_counter); 

        int choice; 
        int x = 0; 
        
        while (1) {
            printf("\nEmployee DB Menu:\n");
            printf("----------------------------------\n");
            printf("\t(1) Print the Database\n");
            printf("\t(2) Lookup by ID\n");
            printf("\t(3) Lookup by Last Name\n");
            printf("\t(4) Add an Employee\n");
            printf("\t(5) Quit\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");

            scanf("%d", &choice); //Read user decision for DB 

            
            switch (choice) {
                case 1:            
                    PrintDB(db, employee_counter);
                    break;
                case 2: ;
                    int target_ID; //target employee ID to search
                    printf("\nPlease enter an employee ID: ");
                    scanf("%d", &target_ID);          
                    x = LookupID(db, 0, employee_counter, target_ID);
                    if (x == -1)
                    {
                        printf("\nUser with employee ID '%d' not found\n", target_ID);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("----------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[x].fname,db[x].lname,db[x].salary, db[x].id);
                        printf("----------------------------------------------\n");
                    }
                    
                    break;
                case 3: ;
                    char target_name[MAXNAME]; //target name to search                 
                    printf("\nPlease enter an employee's last name: ");
                    scanf("%s", target_name); 
                    x = LookupLName(db, employee_counter, target_name);
                    if (x == -1)
                    {
                        printf("\nUser with last name '%s' not found\n", target_name);
                    }
                    else
                    {
                        printf("\nName\t\t\t\tSALARY\t   ID\n");
                        printf("----------------------------------------------\n");
                        printf("%-15s\t%-15s\t%d\t%d\n", db[x].fname,db[x].lname,db[x].salary, db[x].id);
                        printf("----------------------------------------------\n");
                    }                    
                    break;
                case 4:        
                    AddEmployee(db);
                    break;
                case 5:
                    printf("\nLater!\n");      
                    return 0;
                    break;
                default:            
                    printf( "\nInvalid input. Please try again.\n" );
                    break;
            }
        }
    }
}
