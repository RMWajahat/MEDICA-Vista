#include <iostream>
#include <fstream>
#include <typeinfo>
using namespace std;

// node class
template <typename NodeType>
class DbNode
{
public:
    NodeType data;
    DbNode *prev;
    DbNode *next;
    DbNode()
    {
        this->data = NodeType();
        this->next = NULL;
        this->next = NULL;
    }
    DbNode(NodeType data)
    {
        this->data = data;
        this->next = NULL;
        this->next = NULL;
    }

    ~DbNode()
    {
        this->next = NULL;
        this->prev = NULL;
    }
};

// PRocduct class
class Product
{
private:
    string medicinename, medicinedose, medicinecompany, fordisease;
    int medicineprice, medicinequantity;

public:
    string getmedname()
    {
        return this->medicinename;
    }
    int getmedprice()
    {
        return this->medicineprice;
    }
    int getmedquantity()
    {
        return this->medicinequantity;
    }

    Product()
    {
        medicinename = "";
        medicineprice = 0;
        medicinedose = "";
        fordisease = "";
        medicinequantity = 0;
        medicinecompany = "";
    }

    Product(string medicinename, int medicineprice, string medicinedose, int medicinequantity, string medicinecompany, string fordisease)
    {
        this->medicinename = medicinename;
        this->medicineprice = medicineprice;
        this->medicinedose = medicinedose;
        this->fordisease = fordisease;
        this->medicinequantity = medicinequantity;
        this->medicinecompany = medicinecompany;
    }

    void UpdateProductList()
    {
        ofstream newusers;
        newusers.open("medicine.csv", ios::app);
        newusers << "\n"
                 << this->medicinename << "," << this->medicineprice << "," << this->fordisease << "," << this->medicinecompany << "," << this->medicinedose << "," << this->medicinequantity;
        cout << "Medicine Added" << endl;
        newusers.close();
    }

    void DisplayProduct()
    {
        cout << "Name : " << this->medicinename << endl;
        cout << "Company : " << this->medicinecompany << endl;
        cout << "Disease : " << this->fordisease << endl;
        cout << "Dose : " << this->medicinedose << endl;
        cout << "Price : " << this->medicineprice << endl;
        cout << "Quantity : " << this->medicinequantity << endl;
    }

    void DisplayAllMedicines()
    {
        string getname;
        string price;
        string disease;
        string company;
        string dose;
        string quantity;

        ifstream allmedicines;
        allmedicines.open("medicine.csv", ios::in);
        cout << "\t\t---All Medicines Database---" << endl
             << endl;
        while (!allmedicines.eof())
        {
            getline(allmedicines, getname, ',');
            getline(allmedicines, price, ',');
            getline(allmedicines, disease, ',');
            getline(allmedicines, company, ',');
            getline(allmedicines, dose, ',');
            getline(allmedicines, quantity, '\n');

            cout << "Name : " << getname << endl;
            cout << "Company : " << company << endl;
            cout << "Disease : " << disease << endl;
            cout << "Dose : " << dose << endl;
            cout << "Price : " << price << endl;
            cout << "Quantity : " << quantity << endl;
            cout << " -------------------------- " << endl
                 << endl;
        }

        allmedicines.close();
    }
};

// product list and actions
template <typename NodeType>
class productlist : public Product
{
    int size = 0;

public:
    DbNode<NodeType> *head = new DbNode<NodeType>();

    productlist()
    {
        this->head = NULL;
    }

    void insertMedicine(NodeType data)
    {

        DbNode<NodeType> *newNode = new DbNode<NodeType>(data);

        newNode->next = head;

        if (head != NULL)
        {
            head->prev = newNode;
        }

        head = newNode;
        this->size += 1;
    }

    void deleteRecord(string medicinename)
    {
        ofstream newmedicinedata;
        newmedicinedata.open("newmedicaldata.csv", ios::app);
        ifstream medicinedata;
        medicinedata.open("medicine.csv", ios::in);

        string getname;
        string price;
        string disease;
        string company;
        string dose;
        string quantity;

        while (!medicinedata.eof())
        {
            getline(medicinedata, getname, ',');
            getline(medicinedata, price, ',');
            getline(medicinedata, disease, ',');
            getline(medicinedata, company, ',');
            getline(medicinedata, dose, ',');
            getline(medicinedata, quantity, '\n');
            if (getname == medicinename)
            {
                cout << "Data Deletion Success." << endl;
                continue;
            }
            else
            {
                //    move the cursor to the end of file
                newmedicinedata.seekp(0, std::ios::end);
                // btae ga kahan hai cursor in character size
                streampos fileSize = newmedicinedata.tellp();
                if (fileSize != 0)
                {
                    newmedicinedata << "\n";
                }
                newmedicinedata << getname << "," << price << "," << disease << "," << company << "," << dose << "," << quantity;
            }
        }
        medicinedata.close();
        newmedicinedata.close();
        remove("medicine.csv");
        rename("newmedicaldata.csv", "medicine.csv");
    }
    void UpdateMedicineData(string medicinename)
    {
        ofstream newmedicinedata;
        newmedicinedata.open("newmedicaldata.csv", ios::app);
        ifstream medicinedata;
        medicinedata.open("medicine.csv", ios::in);

        string getname;
        string price;
        string disease;
        string company;
        string dose;
        string quantity;

        while (!medicinedata.eof())
        {
            getline(medicinedata, getname, ',');
            getline(medicinedata, price, ',');
            getline(medicinedata, disease, ',');
            getline(medicinedata, company, ',');
            getline(medicinedata, dose, ',');
            getline(medicinedata, quantity, '\n');
            if (getname == medicinename)
            {
                cout << "\nMedicine Name : ";
                cin >> getname;
                cout << "Medicine Company : ";
                cin >> company;
                cout << "Medicine Dose : ";
                cin >> dose;
                cout << "Medicine for Disease : ";
                cin >> disease;
                cout << "Medicine Price : ";
                cin >> price;
                cout << "Medicine Quantity : ";
                cin >> quantity;
            }
            //    move the cursor to the end of file
            newmedicinedata.seekp(0, std::ios::end);
            // btae ga kahan hai cursor in character size
            streampos fileSize = newmedicinedata.tellp();
            if (fileSize != 0)
            {
                newmedicinedata << "\n";
            }
            newmedicinedata << getname << "," << price << "," << disease << "," << company << "," << dose << "," << quantity;
        }
        medicinedata.close();
        newmedicinedata.close();
        remove("medicine.csv");
        rename("newmedicaldata.csv", "medicine.csv");
    }

    void CartItems()
    {

        if (head == NULL)
        {
            cout << "Cart is empty" << endl;
            return;
        }

        DbNode<NodeType> *temp = head;

        cout << "-------------------- Cart data --------------------" << endl;
        while (temp != NULL)
        {
            NodeType Data = temp->data;
            Data.DisplayProduct();
            temp = temp->next;

            cout << "---------------------------" << endl
                 << endl;
        }

        delete temp;
    }
    void CashOutCart()
    {

        if (head == NULL)
        {
            cout << "Cart Total($) = 0 " << endl;
            return;
        }
        int totalPrice = 0;
        DbNode<NodeType> *temp = head;
        int i = 1;
        while (temp != NULL)
        {
            NodeType Data = temp->data;
            cout << i << " - " << Data.getmedname() << endl;
            totalPrice = totalPrice + (Data.getmedprice() * Data.getmedquantity());
            temp = temp->next;
            i++;
        }
        cout << "-----Total Payment = " << totalPrice << "------" << endl
             << endl;

        delete temp;
    }

    bool isempty()
    {
        return this->size == 0;
    }
};

// -----------------------------------------------------------------------------------

// user class
class User
{
private:
    string name;
    bool isAdmin;
    string password;
    string department;
    string email;

public:
    User()
    {
        name = "";
        isAdmin = false;
        password = "";
        department = "";
        email = "";
    }

    User(string name, int isAdmin, string password, string department, string email)
    {
        this->name = name;
        this->isAdmin = isAdmin;
        this->password = password;
        this->department = department;
        this->email = email;
    }

    void DisplayUser()
    {
        cout << "Name : " << this->name << endl;
        cout << "Department : " << this->department << endl;
        cout << "Email : " << this->email << endl;
        string encriptedpass = this->password;
        for (char &c : encriptedpass)
        {
            c = c << 3;
        }
        cout << "Password : " << encriptedpass << "\t\tEncrypted pass for safety reasons." << endl;
        cout << "Admin : " << this->isAdmin << endl;
    }

    void UpdateUserList()
    {
        ofstream newusers;
        newusers.open("admin.csv", ios::app);
        newusers << "\n"
                 << this->name << "," << this->password << "," << this->department << "," << this->email << "," << this->isAdmin;
        newusers.close();
    }

    bool IsAdmin()
    {
        string getname;
        string getisAdmin;
        string getpassword;
        string getdepartment;
        string getemail;

        ifstream allusers;
        allusers.open("admin.csv", ios::in);

        while (!allusers.eof())
        {
            getline(allusers, getname, ',');
            getline(allusers, getpassword, ',');
            getline(allusers, getdepartment, ',');
            getline(allusers, getemail, ',');
            getline(allusers, getisAdmin, '\n');

            if ((this->name == getname) && (this->password == getpassword))
            {
                allusers.close();
                return true;
            }
        }

        allusers.close();
        return false;
    }

    void DisplayDataBaseUsers()
    {
        string getname;
        string getisAdmin;
        string getpassword;
        string getdepartment;
        string getemail;

        ifstream allusers;
        allusers.open("admin.csv", ios::in);
        cout << "\t\t---MEDICA VISTA Database---" << endl
             << endl;
        while (!allusers.eof())
        {
            getline(allusers, getname, ',');
            getline(allusers, getpassword, ',');
            getline(allusers, getdepartment, ',');
            getline(allusers, getemail, ',');
            getline(allusers, getisAdmin, '\n');

            cout << "Name : " << getname << endl;
            cout << "Department : " << getdepartment << endl;
            cout << "Email : " << getemail << endl;
            cout << "Password : " << getpassword << endl;
            cout << "Admin : " << getisAdmin << endl
                 << endl;
            cout << " -------------------------- " << endl
                 << endl;
        }

        allusers.close();
    }
};

// User lsit and actions
template <typename NodeType>
class doubly_linkedlist : public User
{
    int size = 0;

public:
    DbNode<NodeType> *head = new DbNode<NodeType>();

    doubly_linkedlist()
    {
        this->head = NULL;
    }

    void insertBack(NodeType data)
    {
        DbNode<NodeType> *newNode = new DbNode<NodeType>(data);

        if (head == NULL)
        {
            head = newNode;
            return;
        }

        DbNode<NodeType> *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        newNode->prev = temp;
        temp->next = newNode;

        temp = NULL;
        this->size += 1;
    }

    void addAllSessionUsersToDB()
    {
        if (head == NULL)
        {
            cout << "No session users added" << endl;
            return;
        }

        while (head != NULL)
        {
            this->size -= 1;
            NodeType Data = head->data;
            Data.UpdateUserList();
            head = head->next;
            if (head != NULL)
            {
                head->prev = NULL;
            }
        }
    }

    void printNewSessionUsers()
    {

        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        DbNode<NodeType> *temp = head;

        cout << "List data: " << endl;
        while (temp != NULL)
        {
            NodeType Data = temp->data;
            Data.DisplayUser();
            temp = temp->next;

            cout << "---------------------------" << endl
                 << endl;
        }

        delete temp;
    }

    bool isempty()
    {
        return this->size == 0;
    }
};

void MEDICA_VISTA();
void CHOICES();

int main()
{
    MEDICA_VISTA();

    // variables
    bool exitSession = false;
    int usercommands = 0;
    string adminname = "", adminpassword = "";
    string newusername, newuseremail, newuserpass, newuserdep;
    int newuserIsAdmin = -1;
    string newmedicinename, newmedicinedisease, newmedicinecompany, newmedicineDose;
    int newmedicineQuantity = 0, newmedicineprice = 0;
    bool correct = false;

    // objects
    User newUser;
    User tempUser;
    Product newProduct;
    Product tempProduct;

    // lists depending data
    doubly_linkedlist<User> *userlist = new doubly_linkedlist<User>();
    productlist<Product> *Cart = new productlist<Product>();

    system("pause");
    while (!exitSession)
    {
        // reset credentials
        adminname = "", adminpassword = "";
        newusername = "", newuseremail = "", newuserpass = "", newuserdep = "";
        newuserIsAdmin = -1;
        newmedicinename = "", newmedicinedisease = "", newmedicinecompany = "", newmedicineDose = "";
        newmedicineQuantity = 0, newmedicineprice = 0;
        correct = false;

        system("cls");
        CHOICES();
        // make choice
        cout << "Enter your choice : ";
        cin >> usercommands;

        switch (usercommands)
        {
        case 1:

            cout << "\tNote(--Only admins can add users--)\nEnter Your credentials for verification : ";
            cout << "\nName : ";
            cin >> adminname;
            cout << "Password : ";
            cin >> adminpassword;

            tempUser = User(adminname, 0, adminpassword, "", "");
            if (tempUser.IsAdmin())
            {

                cout << "\t--Proceed to User Credentials--\nEnter User credentials for Creating User : ";
                cout << "\nUser's Name : ";
                cin >> newusername;
                cout << "User's Password : ";
                cin >> newuserpass;
                cout << "User's Department : ";
                cin >> newuserdep;
                cout << "User's Email : ";
                cin >> newuseremail;
                while (!correct)
                {
                    // cout<<typeid(newuserIsAdmin).name();
                    if ((newuserIsAdmin == 1) || (newuserIsAdmin == 0))
                    {
                        correct = true;
                    }
                    else
                    {
                        cout << "User's Authority [1=Admin -- 0=Not-Admin]: ";
                        cin >> newuserIsAdmin;
                    }
                }

                newUser = User(newusername, newuserIsAdmin, newuserpass, newuserdep, newuseremail);
                userlist->insertBack(newUser);
                cout << "New User " << newusername << " added." << endl;
            }
            else
            {
                cout << "Your don't have admin access to add user." << endl;
            }
            system("pause");
            break;
        case 2:
            cout << "Session Users" << endl;
            userlist->printNewSessionUsers();
            system("pause");

            break;
        case 3:
            if (!userlist->isempty())
            {
                cout << "Updating Database" << endl;
                userlist->addAllSessionUsersToDB();
                cout << "------OPERATION----SUCCESS------" << endl
                     << endl;
            }
            else
            {
                cout << "Database is Up-to-date " << endl;
            }
            system("pause");
            break;
        case 4:
            cout << "\tNote(--Only admins can Visit Database--)\nEnter Your credentials for verification : ";
            cout << "\nName : ";
            cin >> adminname;
            cout << "Password : ";
            cin >> adminpassword;

            tempUser = User(adminname, 0, adminpassword, "", "");
            if (tempUser.IsAdmin())
            {
                tempUser.DisplayDataBaseUsers();
            }
            else
            {
                cout << "Your don't have permissions to access to visit database." << endl;
            }
            system("pause");
            break;

        case 5:
            cout << "\tNote(--Only admins can add Medicines to stock--)\nEnter Your credentials for verification : ";
            cout << "\nName : ";
            cin >> adminname;
            cout << "Password : ";
            cin >> adminpassword;

            tempUser = User(adminname, 0, adminpassword, "", "");
            if (tempUser.IsAdmin())
            {

                cout << "\t--Proceed to Medicine Details--\nEnter Medicine data : ";
                cout << "\nMedicine Name : ";
                cin >> newmedicinename;
                cout << "Medicine Company : ";
                cin >> newmedicinecompany;
                cout << "Medicine Dose : ";
                cin >> newmedicineDose;
                cout << "Medicine for Disease : ";
                cin >> newmedicinedisease;
                cout << "Medicine Price : ";
                cin >> newmedicineprice;
                cout << "Medicine Quantity : ";
                cin >> newmedicineQuantity;

                tempProduct = Product(newmedicinename, newmedicineprice, newmedicineDose, newmedicineQuantity, newmedicinecompany, newmedicinedisease);
                if ((newmedicinename != "") && ((newmedicineQuantity != 0 && newmedicinecompany != "")))
                {
                    tempProduct.UpdateProductList();
                    cout << "New Medicine " << newmedicinename << " added to stock" << endl;
                }
            }
            else
            {
                cout << "Your don't have admin access to add medicine." << endl;
            }
            system("pause");
            break;
        case 6:
            tempProduct.DisplayAllMedicines();
            system("pause");
            break;
        case 7:
            cout << "\tNote(--Only admins can delete Medicines from stock--)\nEnter Your credentials for verification : ";
            cout << "\nName : ";
            cin >> adminname;
            cout << "Password : ";
            cin >> adminpassword;

            tempUser = User(adminname, 0, adminpassword, "", "");
            if (tempUser.IsAdmin())
            {
                cout << "\t--Proceed to Medicine Details--\n";
                cout << "\nMedicine Name [to-be deleted] : ";
                cin >> newmedicinename;

                Cart->deleteRecord(newmedicinename);
                cout << "Medicine " << newmedicinename << " deleted from stock" << endl;
            }
            else
            {
                cout << "Your don't have admin access to delete medicine record." << endl;
            }
            system("pause");
            break;
        case 8:
            cout << "\tNote(--Only admins can update Medicines from stock--)\nEnter Your credentials for verification : ";
            cout << "\nName : ";
            cin >> adminname;
            cout << "Password : ";
            cin >> adminpassword;

            tempUser = User(adminname, 0, adminpassword, "", "");
            if (tempUser.IsAdmin())
            {
                cout << "\t--Proceed to Medicine Details--\n";
                cout << "\nMedicine Name  [to-be updated] : ";
                cin >> newmedicinename;

                Cart->UpdateMedicineData(newmedicinename);
                cout << "Medicine " << newmedicinename << " updated from stock" << endl;
            }
            else
            {
                cout << "Your don't have admin access medicine record." << endl;
            }
            system("pause");
            break;
        case 9:
            cout << "----- Enter Medicine data -------";
            cout << "\nMedicine Name : ";
            cin >> newmedicinename;
            cout << "Medicine Dose : ";
            cin >> newmedicineDose;
            cout << "Medicine for Disease : ";
            cin >> newmedicinedisease;
            cout << "Medicine Price : ";
            cin >> newmedicineprice;
            cout << "Medicine Quantity : ";
            cin >> newmedicineQuantity;

            newProduct = Product(newmedicinename, newmedicineprice, newmedicineDose, newmedicineQuantity, " ", newmedicinedisease);

            Cart->insertMedicine(newProduct);
            cout << "-----------------  " << newmedicinename << " added to cart.-----------------" << endl;
            system("pause");
            break;
        case 10:
            Cart->CartItems();
            system("pause");
            break;
        case 11:
            Cart->CashOutCart();
            system("pause");
            break;
        case 12:
            cout << "Exiting session .:.:. " << endl;
            exitSession = !exitSession;
            cout << "Session exited" << endl;
            break;
        default:
            cout << "Invalid action\t\tNote: Read Instructions Carefully" << endl
                 << endl;
            system("pause");
        }
    }
}

// other actions
void CHOICES()
{
    cout << R"""(
        -----------ADMIN and USER commands-----------
        1- Create New User                       [A]
        2- List Session Users                    [*]
        3- Add Session Users to Database         [*]
        4- Visit Users Database                  [A]

        -----------Product Actions-----------
        
        5- Add Medicine                          [A]
        6- Display Medicines                     [*]
        7- Delete Medicine from record           [A]
        8- Update Medicine record                [A]
        
        -----------Cart Actions-----------
        
        9- Add to Cart                           [*]
        10- Display Cart Items                   [*]
        11- Cash Out Cart                        [*]
        
        -----------Destroy Session-----------
        
        12- Exit Session                         [*]
    )""" << endl
         << endl;
}

// art
void MEDICA_VISTA()
{
    cout << endl
         << endl
         << R"""('##::::'##:'########:'########::'####::'######:::::'###::::::::'##::::'##:'####::'######::'########::::'###::::\
 ###::'###: ##.....:: ##.... ##:. ##::'##... ##:::'## ##::::::: ##:::: ##:. ##::'##... ##:... ##..::::'## ##:::\
 ####'####: ##::::::: ##:::: ##:: ##:: ##:::..:::'##:. ##:::::: ##:::: ##:: ##:: ##:::..::::: ##:::::'##:. ##::\
 ## ### ##: ######::: ##:::: ##:: ##:: ##:::::::'##:::. ##::::: ##:::: ##:: ##::. ######::::: ##::::'##:::. ##:\
 ##. #: ##: ##...:::: ##:::: ##:: ##:: ##::::::: #########:::::. ##:: ##::: ##:::..... ##:::: ##:::: #########:\
 ##:.:: ##: ##::::::: ##:::: ##:: ##:: ##::: ##: ##.... ##::::::. ## ##:::: ##::'##::: ##:::: ##:::: ##.... ##:\
 ##:::: ##: ########: ########::'####:. ######:: ##:::: ##:::::::. ###::::'####:. ######::::: ##:::: ##:::: ##:\
..:::::..::........::........:::....:::......:::..:::::..:::::::::...:::::....:::......::::::..:::::..:::::..::)"""
         << endl;
}