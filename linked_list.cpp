#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ! ===================== Linked List Implementation =====================
// !    Class for create Node:
class Node
{
public:
    string name;
    string rollnum;
    float gpa;

    Node *next;

    // !  Constructor
    Node(string n, string r, float g)
    {
        name = n;
        rollnum = r;
        gpa = g;
        next = nullptr;
    }
};

// ! Check if Roll Number Exists
bool rollExist(Node *&head, string rollnum)
{
    Node *temp = head;

    // ! Check any roll Number Exists
    while (temp != nullptr)
    {
        if (temp->rollnum == rollnum)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

//  !======================= Helper Function =====================
bool isValidName(const string &name)
{
    for (char ch : name)
    {
        if (!isalpha(ch) && ch != ' ')
        {
            return false;
        }
    }
    return !name.empty(); // name should not be empty
}

// ! Create List
void createlist(Node *&head, string n, string r, float gpa)
{
    // !  Check Roll Number Exists
    if (rollExist(head, r))
    {
        cout << "Roll number already exists! Try a different one." << endl;

        return;
    }

    // ! Create Node & Enter Data
    Node *newnode = new Node(n, r, gpa);

    // ! linked list not available
    if (head == nullptr)
    {
        head = newnode;
    }
    else // !  If linked list available then connect new node with next node
    {
        // !  Temp point at head
        Node *temp = head;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newnode;
    }

    cout << "Student added successfully \n \n";
}

// ! Insert Node at any Position in Linked list
void insertAtPosition(Node *&head, string n, string r, float gpa, int pos)
{
    // ! Check if Roll Number Exist or not
    if (rollExist(head, r))
    {
        cout << "Roll number already exists! Try a different one." << endl;

        return;
    }

    // ! Create new node
    Node *newnode = new Node(n, r, gpa);

    // ! Case 1: Empty list
    if (head == nullptr)
    {
        head = newnode;
        cout << "List was empty. Student added at position 1." << endl;

        return;
    }

    // ! If position equal to 1 then create node
    if (pos == 1)
    {
        newnode->next = head;
        head = newnode;

        cout << "Student added successfully at the beginning!" << endl;
        return;
    }

    // !   Traverse to the node before the position
    Node *temp = head;
    int count = 1;

    // ! Temp Move in complete linked list and check size of linked list
    while (temp->next != nullptr && count < pos - 1)
    {
        temp = temp->next;
        count++;
    }

    // ! If position is beyond the current length → insert at end
    if (temp->next == nullptr && count < pos - 1)
    {
        cout << "Position beyond list length. Inserting at end." << endl;
    }

    // ! Node Add at any position
    newnode->next = temp->next;
    temp->next = newnode;

    cout << "Student added successfully \n";

    cout << "Inserted student: " << n << " (Roll: " << r << ") at position " << pos << endl;
}

// ! Delete Node Function
void deleteAtPosition(Node *&head, int pos)
{
    // !   if linked list not available
    if (head == nullptr)
    {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }

    // ! Delete first node
    if (pos == 1)
    {
        Node *temp = head;
        head = head->next;

        delete temp;
        cout << "Student record deleted successfully!" << endl;

        return;
    }

    // ! Traverse to the node before the position
    Node *prev = head;
    int count = 1;

    while (prev != nullptr && count < pos - 1)
    {
        prev = prev->next;
        count++;
    }

    // ! If position is invalid (too large)
    if (prev == nullptr || prev->next == nullptr)
    {
        cout << "Invalid position!" << endl;
        return;
    }

    // ! Delete the node at given position
    Node *deleteNode = prev->next;
    prev->next = deleteNode->next;
    delete deleteNode;

    cout << "Student record deleted successfully!" << endl;
}

// ! Update Student data With roll Number
void update(Node *&head, string rollnum)
{
    // ! if Linked list doesn't exist
    if (head == nullptr)
    {
        cout << "List is empty. No record to update" << endl;

        return;
    }

    // !    temp point at Head
    Node *temp = head;

    bool found = false;

    // ! Roll number check and update in linked list
    while (temp != nullptr)
    {
        if (temp->rollnum == rollnum)
        {
            found = true;

            // ! Without Update Data
            cout << "Record Found!" << endl;
            cout << "Current Details : " << endl;
            cout << "Name : " << temp->name << endl;
            cout << "Roll Number : " << temp->rollnum << endl;
            cout << "GPA/CGPA : " << temp->gpa << endl;

            // ! Now Update data of student with roll number
            cout << endl
                 << "Enter new details to update:" << endl;

            // ! Name Update
            string newname;
            cin.ignore();
            while (true)
            {
                cout << "Enter Student Name: ";
                getline(cin, newname);

                if (isValidName(newname))
                {
                    break; // valid name
                }
                else
                {
                    cout << "Invalid name! Only letters and spaces allowed.\n";
                }
            }
            temp->name = newname;

            cout << "Do u want to update Roll number? (y/n): ";
            char ch;
            cin >> ch;

            string newroll;

            // ! Roll number update
            cin.ignore();
            cout << "Enter new roll number: ";
            getline(cin, newroll);

            // !   Check new roll exist or not
            if (newroll != rollnum && rollExist(head, newroll))
            {
                cout << "Roll number already exists! Update cancelled." << endl;
                return;
            }
            temp->rollnum = newroll;

            // !  update Gpa
            float newgpa;
            cout << "Enter new GPA/CGPA : ";
            cin >> newgpa;

            // ! Gpa Validation
            while (cin.fail() || newgpa <= 0 || newgpa > 4)
            {
                // !  clear the fail state
                cin.clear();

                // ! discard invalid input
                cin.ignore(1000, '\n');

                cout << "Invalid GPA! Enter GPA between 0.1 and 4.0 : ";
                cin >> newgpa;
            }

            temp->gpa = newgpa;

            cout << "Student record updated successfully!" << endl
                 << endl;

            cout << "Updated Details:" << endl;
            cout << "Name         : " << temp->name << endl;
            cout << "Roll Number  : " << temp->rollnum << endl;
            cout << "GPA/CGPA     : " << temp->gpa << endl;
            cout << "--------------------------" << endl;

            // !  Returning to Main Menu
            cout << "Returning to Main Menu......" << endl;

            break;
        }

        // !  Node move
        temp = temp->next;
    }

    // !  If roll number is not available
    if (!found)
    {
        cout << "Student with roll number " << rollnum << " not found!" << endl;
    }
}

// ! Search Student data with roll Number
void searchWithRollnumber(Node *&head, string rollnum)
{

    // ! If Linked list not available
    if (head == nullptr)
    {
        cout << "List is empty. No records to Search!" << endl;
        return;
    }

    // !  Temp point at Head
    Node *temp = head;
    bool found = false;

    // !    Check if roll number exist then show result
    while (temp != nullptr)
    {
        if (temp->rollnum == rollnum)
        {
            found = true;

            cout << endl
                 << "Student record found successfully!" << endl;
            cout << "Student Detail : " << endl;
            cout << "Student Name : " << temp->name << endl;
            cout << "Student Roll Number : " << temp->rollnum << endl;
            cout << "Student GPA/CGPA : " << temp->gpa << endl;
            cout << "--------------------------" << endl;

            break;
        }
        temp = temp->next;
    }

    // ! If Student not found then show result
    if (!found)
    {
        cout << "No student found with Roll number : " << rollnum << endl;
    }

    cout << endl
         << "Returning to Main Menu......" << endl;

    return;
}

// ! Search Student with Name  Function
void searchWithName(Node *&head, string name)
{
    // !  check linked list available or not
    if (head == nullptr)
    {
        cout << "List is empty. No records to Search!" << endl;
        return;
    }

    // !    temp point at Head
    Node *temp = head;
    bool found = false;

    // !   Search student result with name & Show Student result
    while (temp != nullptr)
    {
        if (temp->name == name)
        {
            found = true;

            cout << endl
                 << "Student record found successfully!" << endl;
            cout << "Student Detail : " << endl;
            cout << "Student Name : " << temp->name << endl;
            cout << "Student Roll Number : " << temp->rollnum << endl;
            cout << "Student GPA/CGPA : " << temp->gpa << endl;
            cout << "------------------------------" << endl;

            break;
        }
        temp = temp->next;
    }

    // !   If Student not found
    if (!found)
    {
        cout << "No student found with name : " << name << endl;
    }

    cout << endl
         << "Returning to Main Menu ......." << endl;

    return;
}

// ! Display Function
void Display(Node *head)
{
    // ! If linked list not available
    if (head == nullptr)
    {
        cout << " No student records to display.\n";
        return;
    }

    //  !   temp point at head
    Node *temp = head;

    // !  Display all Student
    while (temp != NULL)
    {
        cout << "Student Name:" << temp->name << endl;
        cout << "Student RollNumber:" << temp->rollnum << endl;
        cout << "Student GPA:" << temp->gpa << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
    }
}

// ! Delete Complete Linked list function
void deleteLinkedList(Node *&head)
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;

    cout << "Linked list destroyed." << endl;
}

// ! ==================== Main ==========================
int main()
{
    Node *head;
    head = nullptr;

    int choice = -1;

    // ! ================ Menu of all Management ====================

    cout << "========== Student Record Management System ==============" << endl
         << endl;

    while (choice != 0)
    {
        cout << "1) Add Student." << endl;
        cout << "2) Add Student at any position." << endl;
        cout << "3) Delete Student Record." << endl;
        cout << "4) update Student Record. " << endl;
        cout << "5) Search Student. " << endl;
        cout << "6) Display all Students." << endl;
        cout << "0) Exit" << endl;
        cout << "Enter your choice : ";

        cin >> choice;

        // ! Add Student data
        if (choice == 1)
        {
            int num;
            cout << "How many students do you want to add? ";
            cin >> num;

            string n, r;
            float gpa;

            cout << "=========== Add Student ============" << endl;
            for (int i = 0; i < num; i++)
            {
                cout << "Entering details for student " << i + 1 << ":" << endl;

                cin.ignore();
                while (true)
                {
                    cout << "Enter Student Name: ";
                    getline(cin, n);

                    if (isValidName(n))
                    {
                        break; // valid name
                    }
                    else
                    {
                        cout << "Invalid name! Only letters and spaces allowed.\n";
                    }
                }

                cout << "Enter Student Roll Number : ";
                cin >> r;

                // ! Check Roll Number exist or not
                if (rollExist(head, r))
                {
                    cout << "Roll number already exists! Try a different one." << endl
                         << endl;

                    continue;
                }

                cout << "Enter Student GPA/CGPA : ";
                cin >> gpa;

                // ! Gpa Validation
                while (cin.fail() || gpa <= 0 || gpa > 4)
                {
                    // !  clear the fail state
                    cin.clear();

                    // ! discard invalid input
                    cin.ignore(1000, '\n');

                    cout << "Invalid GPA! Enter GPA between 0.1 and 4.0 : ";
                    cin >> gpa;
                }

                // !  Called student create list function
                createlist(head, n, r, gpa);
            }
        }
        //  !    Create Node at any position
        else if (choice == 2)
        {
            int pos;
            string n, r;
            float gpa;

            cout << "=========== Add Student at any position ============" << endl;

            cout << "Enter Position where you want add data : ";
            cin >> pos;

            // ! Invalid position
            if (pos < 1)
            {
                cout << "Invalid position! Please enter a position >= 1." << endl;

                continue;
            }

            cin.ignore();
            while (true)
            {
                cout << "Enter Student Name: ";
                getline(cin, n);

                if (isValidName(n))
                {
                    break; // valid name
                }
                else
                {
                    cout << "Invalid name! Only letters and spaces allowed.\n";
                }
            }

            cout << "Enter Student Roll Number : ";
            cin >> r;

            // ! Check Roll Number exist or not
            if (rollExist(head, r))
            {
                cout << "Roll number already exists! Try a different one." << endl
                     << endl;

                continue;
            }

            cout << "Enter Student GPA/CGPA : ";
            cin >> gpa;

            // ! Gpa Validation
            while (cin.fail() || gpa <= 0 || gpa > 4)
            {
                // !  clear the fail state
                cin.clear();

                // ! discard invalid input
                cin.ignore(1000, '\n');

                cout << "Invalid GPA! Enter GPA between 0.1 and 4.0 : ";
                cin >> gpa;
            }

            // !  Called function
            insertAtPosition(head, n, r, gpa, pos);
        }
        // !  Delete Student data
        else if (choice == 3)
        {

            int pos;

            cout << "=========== Delete Student Record ============" << endl;

            cout << "Enter Position for delete Node : ";
            cin >> pos;

            // ! Invalid position
            if (pos < 1)
            {
                cout << "Invalid position! Please enter a position >= 1." << endl;

                continue;
            }

            // !  Called Delete node at any position function
            deleteAtPosition(head, pos);
        }
        // !   Update Student data at any position
        else if (choice == 4)
        {
            string temp;

            cout << "=========== Update Student Record ============" << endl;

            cout << "Enter your Roll Number to update Student Details : ";
            cin >> temp;

            // !   called Update student function
            update(head, temp);
        }
        //  !    search student with roll number
        else if (choice == 5)
        {
            int num;
            string temp;

            cout << "============= Search Student Record ============" << endl;

            cout << "Enter 1 for search with Name or 2 for search with Roll Number : ";
            cin >> num;

            // ! If user eneter 1 then student search with name
            if (num == 1)
            {

                cin.ignore();
                cout << "Enter Name for Search student : ";
                getline(cin, temp);

                // ! Student searchwith name function called
                searchWithName(head, temp);
            }
            // !  If user eneter 2 then student search with roll number
            else if (num == 2)
            {
                cin.ignore();
                cout << "Enter Roll Number for Search student : ";
                getline(cin, temp);

                //  ! Search student with roll number
                searchWithRollnumber(head, temp);
            }
            //  ! If unknown command enter
            else
            {
                cout << "Invalid Number! Try again." << endl;
            }
        }
        // ! All Students data Display
        else if (choice == 6)
        {
            cout << "========== All Student Records Display =========" << endl;

            // ! Display function called
            Display(head);
        }
        // ! If user enter 0  then exit code
        else if (choice == 0)
        {
            cout << "Exiting Program......" << endl;

            cout << "All student records cleared before exit." << endl;

            // ! Linked list delete
            deleteLinkedList(head);

            head = nullptr;
        }
        // ! If enter any other number
        else
        {
            cout << "Invalid Choice! Try again" << endl;
        }
    }
    return 0;
}
