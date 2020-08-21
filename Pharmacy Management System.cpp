#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "structer.h"

/**********************************************************/
using namespace std;
/**********************************************************/
#define w setw(20) << left
/**********************************************************/
int menu();        
void searchitem(); 
void add_inventory(); 
void sell();                                          
void list_stock();                                    
void print_recipet(vector<pair<string, int> >, double); 
void add_item();                                       
/**********************************************************/

/**********************************************************/
int main() 
{
    stock data;
    bool flag;
    string medcode, medname, temp, quantity, price;
    fstream inventory;
    inventory.open("inventory.csv", ios::in);
    do
    {
        while (getline(inventory, temp))
        {
            stringstream ss(temp);
            getline(ss, medcode, ',');  //read data upto the next comma
            getline(ss, medname, ',');  //read data upto the next comma
            getline(ss, quantity, ','); //read data upto the next comma
            getline(ss, price, ',');    //read data upto the next comma
            data.medname = medname;
            data.medcode = medcode;
            data.quantity = stoi(quantity); //cast from string to integer
            data.price = stod(price);       //cast from string to double
            info.push_back(data);           //add information taken from each line into the vector [info]
        }
        flag = menu();

    } while (flag); //keep the programme going until the user enters [0] in the menue
    return 0;
}
/**********************************************************/
int menu() //shows the menue of whatever the user can do in the programme
{
    system("clear"); //clears the screen
    int choice;
    cout << "**************************************************************************" << endl
         << "\t\t\tHealth care centre " << endl
         << "**************************************************************************" << endl
         << endl
         << "1- Search Item." << endl
         << "2- Update an item detail" << endl
         << "3- Sale Items." << endl
         << "4- Display List stock." << endl
         << "5- Add new Item" << endl

         << "0- Exit." << endl
         << endl;
    cout << "Enter your choice:"; //takes the user's choice
    cin >> choice;
    while (choice < 0 || choice > 5) //make sure that the user enters a number in the range
    {
        cout << "Enter a valid number *0-1-2-3-4-5*: ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        system("clear"); //clears the screen
        searchitem();
        break;
    case 2:
        system("clear"); //clears the screen
        add_inventory();
        break;
    case 3:
        system("clear"); //clears the screen
        sell();
        break;
    case 4:
        system("clear"); //clears the screen
        list_stock();
        break;
    case 5:
        system("clear"); //clears the screen
        add_item();
        break;
    }
    return choice;
}
/**********************************************************/
void searchitem() // looks for items in inventory file
{
    bool found = 0;
    string med;
    cout << "**************************************************************************" << endl
         << "\t\t\tSearch inventory " << endl
         << "**************************************************************************" << endl
         << endl;
    cout << "Enter the medicine name or code: ";
    cin >> med;
    for (int i = 0; i < info.size(); i++) //looks throgh the vector for the entered medname/code
    {
        if (med == info[i].medname || med == info[i].medcode)
        {
            found = 1;
            cout << "**********************************" << endl
                 << "\t\tFOUND" << endl
                 << "**********************************" << endl; //show the information of the found item
            cout << "Code: " << info[i].medcode << endl
                 << "Name: " << info[i].medname << endl
                 << "Quantity left: " << info[i].quantity << endl
                 << "price: " << info[i].price << endl;
            cout << "**********************************" << endl;
            system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
            break;
        }
    }
    if (!found)
    {
        cout << "**********************************" << endl
             << "\t\t\aItem not found.. " << endl
             << "**********************************" << endl;
        system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
    }
}
/**********************************************************/
void add_inventory() // adds to existing quantity
{
    fstream inventory("inventorey");
    ofstream temp;
    int quantity;
    string med;
    bool found = 0;
    char confirm;
    cout << "**************************************************************************" << endl
         << "\t\t\t Add to inventory" << endl
         << "**************************************************************************" << endl
         << endl;
    cout << "Enter the medicine Name or the Code: ";
    cin >> med;
    for (int i = 0; i < info.size(); i++) //looks for the item the user wants to edit it's quantity
    {
        if (med == info[i].medname || med == info[i].medcode)
        {
            found = 1;
            cout << "**********************************" << endl;
            cout << "Code: " << info[i].medcode << endl
                 << "Quantity left:" << info[i].quantity << endl;
            cout << "**********************************" << endl;
            cout << "Enter the Number of the added Items:";
            cin >> quantity;
            cout << "confirm [Y/N]: "; //confirms to add to database
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                info[i].quantity = info[i].quantity + quantity; //add the new quantity to the available stock
                temp.open("temp.csv");                          //open a new file named temp to add the new data into it
                for (int i = 0; i < info.size(); i++)
                    temp << info[i].medcode << "," << info[i].medname << "," << info[i].quantity << "," << info[i].price << endl; //wite the new data into into the file seperated by commas
                temp.close();
                remove("inventory.csv");             //delete the old file
                rename("temp.csv", "inventory.csv"); //rename the temp file as inventory
                cout << "Quantity updated." << endl;
            }
            else
            {
                cout << "declined.";
                system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
            }
        }
    }
    if (!found)
    {
        cout << "**********************************" << endl
             << "\t\t\aItem not found.. " << endl
             << "**********************************" << endl;
        system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
    }
}


/**********************************************************/
void list_stock() //lists all the medicines available in the stock
{
    cout << "**************************************************************************" << endl
         << "\t\t\t stock listings" << endl
         << "**************************************************************************" << endl
         << endl;
    cout << w << "no" << w << "code" << w << "name" << w << "Quantity" << w << "price" << endl; //[w] is defined to set width to 20 & allign to the left
    for (int i = 0; i < info.size(); i++)
        cout << w << i + 1 << w << info[i].medcode << w << info[i].medname << w << info[i].quantity << w << info[i].price << endl;
    cout << endl;
    system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
}
/**********************************************************/
void sell()
{
    fstream inventory("inventorey");
    ofstream temp;
    string med;
    pair<string, int> stuff;       // a pair to store the name & the quantity of each item
    vector<pair<string, int> > buy; // a vector of pairs to store all of the items bought
    double total;
    cout << "**************************************************************************" << endl
         << "\t\t\t sell item" << endl
         << "**************************************************************************" << endl
         << endl;
    cout << "**********************************" << endl
         << "\tpress '00' when done" << endl
         << "**********************************" << endl;
    do
    {

        bool found = 0, taken = 0;
        cout << "Enter the med Name or Code:";
        cin >> med;
        for (int i = 0; i < info.size(); i++) //looks for the that needs to be added to the cart
        {
            if (info[i].medcode == med || info[i].medname == med)
            {
                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;
                if (quantity > info[i].quantity)
                {
                    found = 1;
                    cout << "Insufficient amount\n\n"                         //in case of the user added items more than the available
                         << "Availible amount: " << info[i].quantity << endl; //shows the available quantity
                    continue;
                }
                total += info[i].price * quantity;
                stuff.first = info[i].medname;
                stuff.second = quantity;
                found = 1;
                if (i == 1)
                {
                    buy.push_back(stuff);
                    taken = 1;
                }
                else
                {
                    for (int j = 0; j < buy.size(); j++) //makes sure that the item added wasn't taken before in the same receipt
                    {
                        if (info[i].medname == buy[j].first)
                        {
                            buy[j].second += quantity;
                            taken = 1;
                        }
                    }
                }
                if (!taken)
                {
                    buy.push_back(stuff);
                }
                info[i].quantity -= quantity;
            }
        }
        if (!found && med != "00") //incase the user entered an item that isn't in the stock
        {
            cout << "**********************************" << endl
                 << "\t\t\a item not found.. " << endl
                 << "**********************************" << endl;
            continue;
        }
    } while (med != "00");
    temp.open("temp.csv");
    for (int i = 0; i < info.size(); i++)
    {
        temp << info[i].medcode << "," << info[i].medname << "," << info[i].quantity << "," << info[i].price << endl;
    }
    temp.close();
    remove("inventory.csv");             //delete the old file
    rename("temp.csv", "inventory.csv"); //rename the new file as the old file
    print_recipet(buy, total);
}
/**********************************************************/
void print_recipet(vector<pair<string, int> > items, double total)
{
    system("clear");
    cout << "**************************************************************************" << endl
         << "\t\t\t Receipt" << endl
         << "**************************************************************************" << endl
         << endl;
    cout << w << "Name" << w << "Quantity" << w << "total" << endl // [w] is defined to make to set width to 20 & allign it to the left
         << w << "****" << w << "********" << w << "*****" << endl;
    for (int i = 0; i < items.size(); i++) //shows the items bought
        cout << w << items[i].first << w << items[i].second << endl;
    cout << "______________________________________________" << endl;
    cout << setw(42) << right << "RM" << total << endl; //print the total
    system("read -p 'Press Enter to continue...' var"); //pause screan until the user press enter
}
/**********************************************************/
void add_item() // adds new item to inventory
{
    cout << "**************************************************************************" << endl
         << "\t\t\t Add Item" << endl
         << "**************************************************************************" << endl
         << endl;
    fstream inventory("inventory");
    ofstream temp;
    stock item;
    int code = 101 + info.size(); //makes sequential codes for all items
    item.medcode = to_string(code);
    cout << "Enter the medicine name: ";
    cin >> item.medname; //takes the new med name
    cout << "Enter the selling price: ";
    cin >> item.price; //take the new med price
    cout << "Enter the available quantity: ";
    cin >> item.quantity; //take the new quantitt added for the med
    info.push_back(item);

    temp.open("temp.csv");                //make a new file named temp
    for (int i = 0; i < info.size(); i++) //write the new data in the temp file
    {
        temp << info[i].medcode << "," << info[i].medname << "," << info[i].quantity << "," << info[i].price << endl;
    }
    temp.close();
    remove("inventory.csv");             //deletes the old file
    rename("temp.csv", "inventory.csv"); //rename the new file as inventory
}
/**********************************************************/
