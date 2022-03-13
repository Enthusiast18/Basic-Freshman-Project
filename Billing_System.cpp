#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <conio.h>

using namespace std;

/*Global declaration so that details can be accessed anywhere*/

/*Constants used so that user can increase size of array easily if more data needs to be added*/
const int EMPLOYEE_ROWS = 20; 
const int EMPLOYEE_COLUMNS = 4; 
string employee_accounts[EMPLOYEE_ROWS][EMPLOYEE_COLUMNS];
/*Array to store employee details*/

const int PRODUCT_ROWS = 20;
const int PRODUCT_COLUMNS = 4;
string product_details[PRODUCT_ROWS][PRODUCT_COLUMNS];
/*Array to store product details*/

void Initialise_Arrays()/*Initialise arrays to get rid of junk values*/
{
    int i, j;

    for (i = 0; i < EMPLOYEE_ROWS; i++)
    {
        for (j = 0; j < EMPLOYEE_COLUMNS; j++)
        {
            employee_accounts[i][j] = "";
        }
    }

    for (i = 0; i < PRODUCT_COLUMNS; i++)
    {
        for(j = 0; j < PRODUCT_ROWS; j++)
        {
            product_details[i][j] = "";
        }
    }
}

void Read_Employee_Accounts() /*Reads employee details from file and stores them in an array*/  
{
    int i = 0;
    int j = 0;
    ifstream employee_file;
    employee_file.open("Employees.csv");
    while(!employee_file.eof())
    {
        for(j = 0; j < EMPLOYEE_COLUMNS; j++)
        {
            employee_file >> employee_accounts[i][j];
        }
        i = i + 1;
    }
    employee_file.close();
}

void Read_Product_Details()/*Reads product details from file and stores them in an array*/
{
    int i = 0;
    int j = 0;
    ifstream product_file;
    product_file.open("Products.csv");
    for (i = 0; i < PRODUCT_ROWS; i++)
    {
        for(j = 0; j < PRODUCT_COLUMNS; j++)
        {
            product_file >> product_details[i][j];
        }
    }
    product_file.close();
}

void Write_to_Employee_File()/*Updates employee file*/
{   
    int i,j;
    ofstream employee_file;
    employee_file.open("Employees.csv");
    for (i = 0; i < EMPLOYEE_ROWS; i++)
    {
        for (j = 0; j < EMPLOYEE_COLUMNS; j++)
        {
            employee_file << employee_accounts[i][j] << " ";
        }
        employee_file << endl;
    }
    employee_file.close();
}

void Write_to_Product_File()/*Updates product file*/
{
    int i,j;
    ofstream product_file;
    product_file.open("Products.csv");
    for (i = 0; i < PRODUCT_ROWS; i++)
    {
        for (j = 0; j < PRODUCT_COLUMNS; j++)
        {
            product_file << product_details[i][j] << " ";
        }
        product_file << endl;
    }
    product_file.close();
}

bool Check_User(string user_ID, string user_password, int &employee_index) /*Checks if entered user ID and Password are valid and notes the index of array down in main function if the account is found*/ 
{
    bool user_ID_check = false;
    bool user_password_check = false;
    bool user_check = false;

    for (int i = 0; i < EMPLOYEE_ROWS; i++)
    {
        if (user_ID == employee_accounts[i][1]) /*Checking if correct ID*/
        {
            user_ID_check = true;
            employee_index= i; /*Note index of employee_accounts array for further use*/
            i = EMPLOYEE_ROWS; /*Exit loop*/
        }
    }

    for (int j = 0; j < EMPLOYEE_ROWS; j++)
    {
        if (user_password == employee_accounts[j][2]) /*Checking if correct password*/
        {
            user_password_check = true;
            j = EMPLOYEE_ROWS; /*Exit loop*/
        }
    }

    if (user_ID_check && user_password_check) /*Checking if valid user*/
    {
        user_check = true;
    }
    else
    {
        cout << "Invalid Username or Password\n";
    }
    
    return user_check;
}

void Bill()/*Prints Bill*/
{
    string product_ID;
    string dummy;
    int product_index[100][2];
    double total = 0;
    double product_price = 0;
    int product_quantity = 0;
    int quantity = 0;
    int index = 0;
    int temp = 0;
    char key;
    int asciiValue;
    cout << "Enter product IDs and write end to print bill\n";
    cout << endl;
    cout << "Product ID: ";
    cin >> product_ID;
    while (product_ID != "end")
    {
        for (int i = 0; i < PRODUCT_ROWS; i++)
        {
            if (product_ID == product_details[i][1]) // Checks for the product in the Database
            {
                product_index[index][0] = i;
                product_quantity = stoi(product_details[i][3]);
                cout << "Product details:\n";
                cout << "Product Name: " << product_details[i][0] << "\t Product ID: " << product_details[i][1] << "\t Product Price: " << product_details[i][2] << "\tAvailable Quantity: " << product_details[i][3] << endl;
                if (product_quantity > 0)
                {
                    cout << "Enter Quantity: ";
                    cin >> quantity;
                    cout << endl;
                    product_quantity = product_quantity - quantity;
                    product_details[i][3] = to_string(product_quantity);
                    product_index[index][1] = quantity;
                    index = index + 1; 
                    product_price = stod(product_details[i][2]);
                    total = total + (quantity * product_price);
                    i = PRODUCT_ROWS;
                }
                else
                {
                    cout << "Out of stock\n"; //Prints out of stock if Product Quantity = 0
                    cout << endl;
                }
                
            }
        }
        cout << "Product ID: ";
        cin >> product_ID;
    }

    Write_to_Product_File();

    time_t ttime = time(0); /*Assigns the local time to dt. These two lines were taken from: https://www.softwaretestinghelp.com/date-and-time-in-cpp/ */
    char* dt = ctime(&ttime);

    cout << "$___________________________________________________________________________________________________$\n";
    cout << "                                       Final Bill\n";
    cout << endl;
    cout << setw(20) << "Product Name" << setw(20) << "Product ID" << setw(20) << "Price" << setw(20) << "Quantity\n";
    cout << endl;
    for (int j = 0; j < index; j++ )
    {
        temp = product_index[j][0];
        cout << setw(20) << product_details[temp][0] << setw(20) << product_details[temp][1] <<setw(20) << product_details[temp][2] << setw(20) << product_index[j][1] << endl;
    }
    cout << endl;
    cout << setw(20) << "Total Amount: " << total << setw(20) << "Time: " << dt << endl << endl;
    cout << "$____________________________________________________________________________________________________$\n";
    cout << endl;
    cout << "Move on after clearing screen ? Y/N\n";
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    cout << endl;
    key=getch(); 
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)
    {
        cout << flush; // This clears the screen to move onto the next screen
        system("CLS");
    }
}

void Print_Inventory()/*Prints inventory*/
{
    string dummy;
    char key;
    int asciiValue;

    cout << setw(20) << "Product Name" << setw(20) << "Product ID" << setw(20) << "Product Price" << setw(20) << "Quantity in Stock" << endl;
    cout << endl;
    for(int i = 0; i < PRODUCT_ROWS; i++)
    {
        if (product_details[i][0] != "")
        {
            for (int j = 0; j < PRODUCT_COLUMNS; j++)
            {
                cout << setw(20) << product_details[i][j];
            }
            cout << endl;
        } 
    }
    cout << endl;

    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); // getch() takes input from the user but doesn't display it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;
        system("CLS");
    }
}

void Print_Employee_Database() // Prints the Employee Database
{
    string dummy;
    char key;
    int asciiValue;

    cout << setw(20) << "Employee Name" << setw(20) << "Employee ID" << setw(20) << "Employee Password" << setw(20) << "Employee Position" << endl;
    cout << endl;

    for (int i = 0; i < EMPLOYEE_ROWS; i++) // It reads the Employee Database
    {
        if (employee_accounts[i][0] != "")
        {
            for (int j = 0; j < EMPLOYEE_COLUMNS; j++)
            {
                cout << setw(20) << employee_accounts[i][j];
            }
            cout << endl;
        }
    } 
     cout << endl;

    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); // getch() takes input from the user but doesn't display it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)
    {
        cout << flush;
        system("CLS");
    }
}

void Add_Employee() // This function is used to add a new employee to the database
{
    string employee_name, employee_ID, employee_password, employee_position;
    string input;
    string dummy;
    bool end_addition = false;
    bool ID_check = false;
    int i = 0;
    int j;
    char key;
    int asciiValue;

    while (!end_addition)
    {
        cout << "Enter Employee Name: ";
        cin >> employee_name;
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        while (!ID_check)
        {
            for (i = 0; i < EMPLOYEE_ROWS; i++)
            {
                if (employee_accounts[i][1] == employee_ID) // It checks if the entered new Employee ID matches any existing employee ID in the Database
                {
                    cout << "An employee with this ID already exists. Try again with another ID: ";
                    cin >> employee_ID;
                    i = EMPLOYEE_ROWS;
                    ID_check = false;
                }
                else 
                {
                    ID_check = true;
                }
            }
        }
        ID_check = false;
        cout << "Enter Employee Password: ";
        cin >> employee_password;
        cout << "Enter Employee Position (Manager/Employee): ";
        cin >> employee_position;
        while(employee_position != "Manager" && employee_position != "Employee")
        {
            cout << "Enter valid position (Manager/Employee): ";
            cin >> employee_position;
        }
        cout << endl;

        for (i = 0; i < EMPLOYEE_ROWS; i++)
        {
            if (employee_accounts[i][0] == "") // This Adds the new Employee Details to the Database
            {
                employee_accounts[i][0] = employee_name;
                employee_accounts[i][1] = employee_ID;
                employee_accounts[i][2] = employee_password;
                employee_accounts[i][3] = employee_position;
                cout << "Employee added successfully\n" << endl;
                i = EMPLOYEE_ROWS;
            }
            else if(i == EMPLOYEE_ROWS-1)
            {
                cout << "Addition unsuccessful\n";
                cout << "Array full: Increase array size\n";
            }
        }
        cout << "Add another employee ? Y/N ?\n";
        cout << "Note: Any input other than Y will terminate adding employees\n";
        cin >> input;
        cout << endl;
        if (input != "Y")
        {
            end_addition = true;
        }
    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); // getch() takes input from the user but doesn't display it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;
        system("CLS");
    }
    cout << endl;
    
}

void Delete_Employee() // This function deletes an existing employee from database
{
    string delete_ID;
    string input;
    string dummy;
    int i, x, j;
    bool employee_delete = false;
    bool end_delete = false;
    char key;
    int asciiValue;

    while (!end_delete)
    {
        cout << "Enter ID of employee to be deleted: ";
        cin >> delete_ID;
    
        for (i = 0; i < EMPLOYEE_ROWS; i++)
        {
            if (employee_accounts[i][1] == delete_ID) // It checks for the entered employee ID in the Database
            {
                for (x = 0; x < EMPLOYEE_COLUMNS; x++)
                {
                    employee_accounts[i][x] = "";
                }
                cout << "Employee deleted successfully\n" << endl;
                i = EMPLOYEE_ROWS;
                employee_delete = true;
            }
        
        }
        if (employee_delete == false) // If Employee Deletion is not possible this if statement prints out
        {
            cout << "Entered ID is invalid\n" << endl;
        }

        cout << "Would you like to delete another employee ? Y/N ?\n";
        cout << "Note: Any input other than Y will terminate deleting employees\n";
        cin >> input;
        if (input != "Y")
        {
            end_delete = true;
        }

    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); // getch() takes input from the user but doesn't display it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;
        system("CLS");
    }
}

void Edit_Name(int index) //This edits the existing Name in Database
{
    string update;
    cout << "Enter new name: ";
    cin >> update;
    employee_accounts[index][0] = update;
    cout << "Edit successful\n" << endl;
}
void Edit_ID(int index) //This edits the existing ID in Database
{
    string update;
    bool ID_check = false;
    cout << "Enter new ID: ";
    cin >> update;
    while(!ID_check)
    {
        for (int i = 0; i < EMPLOYEE_ROWS; i++)
        {
            if (employee_accounts[i][1] == update) // This checks if the entered ID matches any other ID in the Database
            {
                cout << "ID already exists. Try again: ";
                cin >> update;
                ID_check = false;
                i = EMPLOYEE_ROWS;
            }
            else 
            {
                ID_check = true;
            }
        }
    }
    employee_accounts[index][1] = update;
    cout << "Edit successful\n" << endl;
}
void Edit_Password(int index) //This edits the existing password in Database
{
    string update;
    cout << "Enter new password: ";
    cin >> update;
    employee_accounts[index][2] = update;
    cout << "Edit successful\n" << endl;
}
void Edit_Position(int index) //This function changes the postion of the existing employee
{
    string update;
    bool position_check = false;
    cout << "Enter new position (Manager/Employee): ";
    cin >> update;
    while (!position_check)
    {       
        if (update != "Manager" && update != "Employee")
        {
            cout << "Invalid position. Try again: ";
            cin >> update;
        }
        else if (update == "Manager" || update == "Employee")
        {
            position_check = true;
        }
    }
    employee_accounts[index][3] = update;
    cout << "Edit successful\n" << endl;
}
void Update_Employee_Details() // This function is used to edit employee details
{
    string employee_ID;
    string input;
    string dummy;
    string clear;
    bool employee_exists = false;
    bool end_edit = false;
    bool exit_program = false;
    int index = 0;
    int edit = 0;
    char key, key2;
    int asciiValue, asciiValue2;

    while (!exit_program)
    {
        end_edit = false;
        employee_exists = false;
        cout << "Enter ID of the employee whose details you want to edit: ";
        cin >> employee_ID;
        while(!employee_exists)
        {
            for (int i = 0; i < EMPLOYEE_ROWS; i++)
            {
                if (employee_accounts[i][1] == employee_ID) // This checks if the Entered ID is already in the Database
                {
                    employee_exists = true;
                    index = i;
                    i = EMPLOYEE_ROWS;
                }
            }
            if (employee_exists == false)
            {
                cout << "Invalid ID entered. Employee does not exist. Try again: "; // If the entered ID is not in the Database then this is printed out
                cin >> employee_ID;
            }
        }
    
        while (!end_edit)
        {
            cout << "Enter 1 to edit name\n";
            cout << "Enter 2 to edit ID\n";
            cout << "Enter 3 to edit password\n";
            cout << "Enter 4 to edit position\n";
            cout << "Enter any other input to exit\n" << endl;
            cout << "Input: ";
            cout << endl;
            key2=getch();  // getch() takes input from the user but doesn't dsiplay it on the screen
            asciiValue2=key2;
            switch (asciiValue2)
            {
                case 49: Edit_Name(index); break; // This calls the Edit_Name() Function
                case 50: Edit_ID(index); break; // This calls the Edit_ID() Function
                case 51: Edit_Password(index); break;   // This calls the Edit_Password() Function
                case 52: Edit_Position(index); break;   // This calls the Edit_Position() Function
                default: end_edit = true; cin.clear(); getline(cin, clear); break;
            }
        }
        cout << "Would you like to edit another employee's details ? Y/N ?\n";
        cout << "Note: Any input other than Y will exit editing\n";
        cout << "Input: ";
        cin >> input;
        cout << endl;
        cout << "$_______________________________$\n";
        cout << endl;
        if (input !="Y")
        {
            exit_program = true;
        }

    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch();    // getch() takes input from the user but doesn't dsiplay it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush; // This clears the screen
        system("CLS");
    }

}

void Update_Employee_Database() // This function uses the other edit functions used before to edit the emplyee database
{
    int input = 0;
    char key;
    int asciiValue;

    cout << "Enter 1 to add new employee\n";
    cout << "Enter 2 to delete existing employee\n";
    cout << "Enter 3 to edit employee details\n";
    cout << "Enter any other input to exit\n" << endl;
    cout << "Input: ";
    cout << "$_______________________________$\n";
    cout << endl;
    key=getch(); 
    asciiValue=key;
    switch (asciiValue)
    {
        case 49: Add_Employee(); break; // This calls the Add_Employee() Function
        case 50: Delete_Employee(); break;  // This calls the Delete_Employee() Function
        case 51: Update_Employee_Details(); break;  //This calls the Update_Employee_Details() Function
        default: break;
    }

    Write_to_Employee_File(); // This calls the function for File Writing
}

void Price_Check(double &price) // This function checks the price
{
    string garbage;
    cin >> price;
    while(cin.fail())
    {
        cin.clear();
        getline(cin, garbage);
        cout << "Invalid Price. Try again: ";
        cin >> price;
    }
    
}
void Quantity_Check(int &quantity) // This function is a check for the Quantity of the Product entered in the Bill() Function
{
   string garbage;
   cin >> quantity;
   while(cin.fail())
   {
       cin.clear();
       getline(cin,garbage);
       cout << "Invalid Quantity. Try again: ";
       cin >> quantity;
   }
}
void Add_Product() // This function is used to add product to existing database of products
{
    string product_name, product_ID;
    int product_quantity;
    double product_price;
    string input;
    string dummy;
    bool end_addition = false;
    bool ID_check = false;
    int i = 0;
    int j;
    char key;
    int asciiValue;

    while (!end_addition)
    {
        cout << "Enter Product Name: ";
        cin >> product_name;
        cout << "Enter Product ID: ";
        cin >> product_ID;
        while (!ID_check)
        {
            for (i = 0; i < PRODUCT_ROWS; i++)
            {
                if (product_details[i][1] == product_ID) // This checks if the Product ID entered is in the Database
                {
                    cout << "A product with this ID already exists. Try again with another ID: ";
                    cin >> product_ID;
                    i = PRODUCT_ROWS;
                    ID_check = false;
                }
                else 
                {
                    ID_check = true;
                }
            }
        }
        ID_check = false;
        cout << "Enter Product Price: ";
        Price_Check(product_price);
        cout << "Enter Product Quantity: ";
        Quantity_Check(product_quantity);

        for (i = 0; i < PRODUCT_ROWS; i++)
        {
            if (product_details[i][0] == "") // This writes the Product Details to the Products Database file
            {
                product_details[i][0] = product_name;
                product_details[i][1] = product_ID;
                product_details[i][2] = to_string(product_price);
                product_details[i][3] = to_string(product_quantity);
                cout << "Product added successfully\n" << endl;
                i = PRODUCT_ROWS;
            }
            else if(i == PRODUCT_ROWS-1)
            {
                cout << "Addition unsuccessful\n";
                cout << "Array full: Increase array size\n";
            }
        }
        cout << "Add another product ? Y/N ?\n";
        cout << "Note: Any input other than Y will terminate adding employees\n";
        cin >> input;
        cout << endl;
        if (input != "Y")
        {
            end_addition = true;
        }
    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); // getch() takes input from the user but doesn't display it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;  // It clears the screen
        system("CLS");
    }
    cout << endl;
}

void Delete_Product() // This function is used to delete a product from the existing database
{
    string delete_ID;
    string input;
    string dummy;
    int i, x, j;
    bool product_delete = false;
    bool end_delete = false;
    char key;
    int asciiValue;

    while (!end_delete)
    {
        cout << "Enter ID of product to be deleted: ";
        cin >> delete_ID;
    
        for (i = 0; i < PRODUCT_ROWS; i++)
        {
            if (product_details[i][1] == delete_ID)     //This modifies the Array for the Products
            {
                for (x = 0; x < PRODUCT_COLUMNS; x++)
                {
                    product_details[i][x] = "";
                }
                cout << "Product deleted successfully\n" << endl;
                i = EMPLOYEE_ROWS;
                product_delete = true;
            }
        
        }
        if (product_delete == false) // It checks If the Product Deletion had an Invalid id
        {
            cout << "Entered ID is invalid\n" << endl;
        }

        cout << "Would you like to delete another product ? Y/N ?\n";
        cout << "Note: Any input other than Y will terminate deleting employees\n";
        cin >> input;
        if (input != "Y")
        {
            end_delete = true;
        }

    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch();    // getch() takes input from the user but doesn't dsiplay it on the screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;
        system("CLS");
    }
}

void Edit_Product_Name(int index) // This function is used to edit the name of an existing product
{
    string update;
    cout << "Enter new product name: "; // This takes the new Product name for the product already in database
    cin >> update;
    product_details[index][0] = update;
    cout << "Edit successful\n" << endl;
}
void Edit_Product_ID(int index) // This function is used to edit the ID of an existing product
{
    string update;
    bool ID_check = false;
    cout << "Enter new product ID: "; // This takes the new Product ID for the Product already in database
    cin >> update;
    while(!ID_check)
    {
        for (int i = 0; i < PRODUCT_ROWS; i++)
        {
            if (product_details[i][1] == update) // This checks if the newly entered Product ID is in the Database
            {
                cout << "ID already exists. Try again: ";
                cin >> update;
                ID_check = false;
                i = PRODUCT_ROWS;
            }
            else 
            {
                ID_check = true;
            }
        }
    }
    product_details[index][1] = update;
    cout << "Edit successful\n" << endl;
}
void Edit_Product_Price(int index) // This function is used to edit the Price of an existing product
{
    double product_price;
    cout << "Enter new price: ";
    Price_Check(product_price);     // Price_Check() Function is called here
    product_details[index][2] = to_string(product_price);   // Array is modified here
    cout << "Edit successful\n" << endl;
}
void Edit_Product_Quantity(int index) // This function is used to edit the Quantity of an existing product
{
    int quantity;
    cout << "Enter quantity: ";
    Quantity_Check(quantity);   // Quantity_Check() Function is called
    product_details[index][3] = to_string(quantity); // Array is modified here
    cout << "Edit successful\n" << endl;
}
void Edit_Product_Details() // This function uses all the edit product functions made before
{
    string product_ID;
    string input;
    string dummy;
    string clear;
    bool product_exists = false;
    bool end_edit = false;
    bool exit_program = false;
    int index = 0;
    int edit = 0;
    char key, key2;
    int asciiValue, asciiValue2;

    while (!exit_program)   // This loop continues while the program is not exited
    {
        end_edit = false;
        product_exists = false;
        cout << "Enter ID of the product for which you want to edit the details: ";
        cin >> product_ID;
        while(!product_exists)  
        {
            for (int i = 0; i < PRODUCT_ROWS; i++)
            {
                if (product_details[i][1] == product_ID)
                {
                    product_exists = true;
                    index = i;
                    i = PRODUCT_ROWS;
                }
            }
            if (product_exists == false) // This part is printed if the the Product ID entered is not in the database
            {
                cout << "Invalid ID entered. Product does not exist. Try again: ";
                cin >> product_ID;
            }
        }
    
        while (!end_edit)
        {
            cout << "Enter 1 to edit product name\n";
            cout << "Enter 2 to edit product ID\n";
            cout << "Enter 3 to edit price\n";
            cout << "Enter 4 to edit quantit\n";
            cout << "Enter any other input to exit\n" << endl;
            cout << "Input: ";
            cout << endl;
            key2=getch();   //getch() takes input from user but doesn't display it on screen
            asciiValue2=key2;
            switch (asciiValue2)
            {
                case 49: Edit_Product_Name(index); break;   // This calls the Edit_Product_Name() Function
                case 50: Edit_Product_ID(index); break;     // This calls the Edit_Product_ID() Function
                case 51: Edit_Product_Price(index); break;  // This calls the Edit_Product_Price() Function
                case 52: Edit_Product_Quantity(index); break;   // This calls the Edit_Product_Quantity() Function
                default: end_edit = true; cin.clear(); getline(cin, clear); break; 
            }
        }
        cout << "Would you like to edit another product's details ? Y/N ?\n";
        cout << "Note: Any input other than Y will exit editing\n";
        cout << "Input: ";
        cin >> input;
        cout << endl;
        cout << "$_______________________________$\n";
        cout << endl;
        if (input !="Y")
        {
            exit_program = true;
        }

    }
    cout << "Clear Screen ? Y/N ?" << endl;
    cout << "Note: Any input other than Y will result in you moving on without clearing screen\n";
    key=getch(); //getch() takes input from user but doesn't display it on screen
    asciiValue=key;
    if (asciiValue == 121 || asciiValue == 89)

    {
        cout << flush;  // This clears the screen to prevent others from viewing the previous details
        system("CLS");
    }
}

void Update_Inventory() // This function uses the functions made before for writing the Product Database
{
    char key;
    int asciiValue;
    int input = 0;

    cout << "Enter 1 to add new product\n";
    cout << "Enter 2 to delete existing product\n";
    cout << "Enter 3 to edit product details\n";
    cout << "Enter any other input to exit\n" << endl;
    cout << "$_______________________________$\n";
    cout << endl;
    key=getch();    //getch() takes input from user but doesn't display it on screen
    asciiValue=key;
    switch (asciiValue)
    {
        case 49: Add_Product(); break;
        case 50: Delete_Product(); break;
        case 51: Edit_Product_Details(); break;
        default: break;
    }

    Write_to_Product_File(); // This calls the Write_to_Product_File() Function
}

int main() // Main body of the Program
{
    // The Portion below is used for Initialization
    char key1;
    int asciiValue1;
    string user_ID;
    string user_password;
    int employee_index;
    int input;
    bool employee_signin_complete = false;
    bool end_program = false;

    Initialise_Arrays();
    Read_Employee_Accounts();
    Read_Product_Details();

    while(!employee_signin_complete) /*Take sign in details from user and check with array using function Check_User. Keep asking until user found*/
    {
        cout << "Please Sign In to Continue\n";
        cout << endl;
        cout << "Enter User ID: ";;
        cin >> user_ID;
        cout << "Enter Password: ";
        cin >> user_password;
        cout << endl;
        employee_signin_complete = Check_User(user_ID, user_password, employee_index); // This calls the Check_User() Function
    }

    cout << flush;/*Clear screen to prevent others from seeing log in details*/
    system("CLS");

    // The interface below displays the Name, ID and Position of the Person who logged in

    cout << "$______________________________$\n";
    cout << "  Welcome " << employee_accounts[employee_index][0] << endl;
    cout << "  ID: " << user_ID <<  endl;
    cout << "  Position: " << employee_accounts[employee_index][3] << endl;
    cout << "$______________________________$\n"; 
    cout << endl;
    while(!end_program)
    {
        if (employee_accounts[employee_index][3] == "Manager")
        {
            cout << "What can I help you with today, Manager ?\n" << endl;
            cout << "Enter 1 to form a bill\n";
            cout << "Enter 2 to view employee database\n";
            cout << "Enter 3 to view inventory\n";
            cout << "Enter 4 to update inventory\n";
            cout << "Enter 5 to update employee database\n";
            cout << "Enter any other input to end program\n";
            cout << "Note: You will be automatically signed out when program ends\n" << endl;
            cout << "Input: \n";
            cout << "$_______________________________$\n";
            cout << endl;
            key1=getch();    // getch() takes character from the user but doesn't display it on screen  
            asciiValue1=key1;
            switch (asciiValue1)
            {
                case 49: Bill(); break; // This calls the Bill() function
                case 50: Print_Employee_Database(); break; // This calls the Print_Employee_Database() Function
                case 51: Print_Inventory(); break; // This calls the Print_Inventory() Function
                case 52: Update_Inventory();break; // This calls the Update_Inventory() Function
                case 53: Update_Employee_Database(); break; // This calls the Update_Employee_Database() Function
                default: end_program = true; break; // This ends the program
            }
        }
        else 
        {
            cout << "What can I help you with today, Employee ?\n" << endl;
            cout << "Enter 1 to form a bill\n"; 
            cout << "Enter 2 to view inventory\n";
            cout << "Enter any other input to end program\n";
            cout << "Note: You will be automatically signed out when program ends\n" << endl;
            cout << "Input: ";
            cout << "$_______________________________$\n";
            cout << endl;
            key1=getch();
            asciiValue1=key1;
            switch (asciiValue1)
            {
                case 49: Bill(); break; // This calls the bill() function  
                case 50: Print_Inventory(); break; // This calls the Print_Inventory() function
                default: end_program = true; break; // This ends the program
            }
        }
    }
}