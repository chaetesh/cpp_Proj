#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
int Size = 0;

// Function used to split the marks string and convert into intgers
vector<int> split(string str, char delimiter)

{
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while (getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }
    vector<int> Data;
    transform(internal.begin(), internal.end(), std::back_inserter(Data), [](const std::string &str)
              { return std::stoi(str); });
    return Data;
}

char Grade(int sum)
{
    if(sum<=125 && sum>=115)
    {
        return 'O';
    }
    else if(sum>105)
    {
        return 'A';
    }
    else if(sum>85)
    {
        return 'B';
    }
    else if(sum>55)
    {
        return 'C';
    }
    else{
        return 'F';
    }
}

class Student
{
private:
    string name;
    vector<int> marks;
    int sum;
    char grade;

public:
    string roll_no;
    void add(string name, string roll_no, string mrks)
    {
        this->name = name;
        this->roll_no = roll_no;
        marks = split(mrks, ' ');
        sum = accumulate(marks.begin(), marks.end(), 0);
        this->grade = Grade(sum);
        for (int i = 0; i < marks.size(); i++)
        {
            if (marks[i] < 10)
            {
                this->grade = 'F';
            }
        }
    }

    void print()
    {
        cout << "Name: " << name << endl;
        cout << "Roll No: " << roll_no << endl;
        for (int i = 0; i < marks.size(); i++)
        {
            cout << marks[i] << " ";
        }
        cout << "\nSum: " << sum << endl;
        cout << "Grade: " << grade << endl;
        cout<<endl;
    }
    friend void modify();
    friend void del_st();
    friend void display();
    friend void display_particular();
    friend void topper();
    friend void updateFile();
} s[30];

void updateFile()
{
    cout << "Updating file" << endl;
    ofstream update;
    update.open("studentData.txt");
    for (int i = 0; i <= Size; i++)
    {
        if (s[i].name == "")
        {
            continue;
        }
        update << s[i].name << endl;
        update << s[i].roll_no << endl;
        for (int j = 0; j < s[i].marks.size(); j++)
        {
            update << s[i].marks[j] << " ";
        }
        update << endl;
    }
}

void topper()
{
    int max1, max2, max3;
    max1 = s[0].sum;
    max2 = s[0].sum;
    max3 = s[0].sum;
    int m = 0, p = 0, q = 0;
    for (int i = 0; i <= Size; i++)
    {
        // first max
        if (s[i].sum >= max1)
        {
            max1 = s[i].sum;
            m = i;
        }
        if (s[i].sum >= max2 && s[i].sum < max1)
        {
            p = i;
            max2 = s[i].sum;
        }
        if (s[i].sum > max3 && s[i].sum < max1 && s[i].sum < max2)
        {
            max3 = s[i].sum;
            q = i;
        }
    }
    printf("First Student: \n");
    s[m].print();
    printf("Second Student: \n");
    s[p].print();
    printf("Third Student: \n");
    s[q].print();
}

void display()
{
    for (int i = 0; i <= Size; i++)
    {
        if (s[i].name == "")
        {
            continue;
        }
        s[i].print();
        cout<<endl;
    }
}

void display_particular()
{
    cout << "Enter student name to display: ";
    string student_name;
    cin >> student_name;
    for (int i = 0; i <= Size; i++)
    {
        if (s[i].name == student_name)
        {
            cout << "1. Name: " << student_name << endl;
            cout << "2. Roll Nummber: " << s[i].roll_no << endl;
            cout << "3. Marks: " << endl;
            for (int j = 0; j < s[i].marks.size(); j++)
            {
                cout << s[i].marks[j] << " ";
            }
            cout << "\n";
            break;
        }
    }
}

void del_st()
{
    string find;
    cout << "Enter student name to delete: ";
    cin >> find;
    int flag = 1;
    for (int i = 0; i <= Size; i++)
    {
        if (s[i].name == find)
        {
            flag = 0;
            s[i].name = "";
        }
    }
    if (flag)
    {
        cout<<"Name not present in Records!!"<<endl;
        return;
    }
    updateFile();
}

void modify()
{
    string find;
    cout << "Enter student name to find: ";
    cin >> find;
    for (int i = 0; i <= Size; i++)
    {
        if (s[i].name == find)
        {
            cout << "Please Select which data you want to Change" << endl;
            cout << "1. Name" << endl;
            cout << "2. Roll Nummber" << endl;
            cout << "2. Marks" << endl;
            int choose;
            cin >> choose;
            switch (choose)
            {
            case 1:
            {
                string tempn;
                cout << "Enter New Name: ";
                cin >> tempn;
                s[i].name = tempn;
                break;
            }
            case 2:
            {
                string tempr;
                cout << "Enter New Roll Number: ";
                cin >> tempr;
                s[i].roll_no = tempr;
                break;
            }
            case 3:
            {
                vector<int> tempm;
                cout << "Enter Your New Marks: ";
                for (int i = 0; i < 5; i++)
                {
                    int temp;
                    cin >> temp;
                    tempm.push_back(temp);
                }
                s[i].marks = tempm;
                break;
            }
            }
            s[i].print();
        }
    }
}

int main()
{
    ifstream readFile("studentData.txt");

    for (int i = 0; i < 20; i++)
    {
        string name, roll_no;
        getline(readFile, name);
        getline(readFile, roll_no);
        string t;
        getline(readFile, t);
        Size++;
        s[i].add(name, roll_no, t);
    }
    int option;
    while (1)
    {
        cout << "\n\n";
        cout << "Please Enter your option to proceed:" << endl;
        cout << "1.Add Student Record" << endl;
        cout << "2.Delete a student record" << endl;
        cout << "3.Display a particular student record" << endl;
        cout << "4.Display all student records\n";
        cout << "5.Display all 3 toppers" << endl;
        cout << "6.Modify a student record " << endl;
        cout << "7.Exit" << endl;
        cout << "Your Input: ";
        cin >> option;
        cout << endl;
        switch (option)
        {
        case 1:
        {
            cout << "Enter Student Name: ";
            string name, roll_no;
            cin >> name;
            cout << "Enter Student RollNumber: ";
            cin >> roll_no;
            int flag = 0;
            for (int k = 0; k < Size; k++)
            {
                if (s[k].roll_no == roll_no)
                {
                    flag = 1;
                    cout<<"Same RollNumber Repeated!!!"<<endl;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
            string t;
            cout << "Enter Your Marks: ";
            fflush(stdin);
            getline(cin, t);
            Size++;
            s[Size].add(name, roll_no, t);
            cout << "Added Successfull" << endl;
            updateFile();
            break;
        }
        case 2:
        {
            del_st();
            cout << "Student Data deleted Succesfully from Record!!" << endl;
            Size--;
            break;
        }
        case 3:
        {
            display_particular();
            break;
        }
        case 4:
        {
            cout << "Details of all Students" << endl;
            display();
            break;
        }
        case 5:
        {
            cout << "Top 3 Students from the Data" << endl;
            topper();
            break;
        }
        case 6:
        {
            modify();
            cout << "Modification of data Successfull!!" << endl;
            break;
        }
        case 7:
        {
            cout << "Exited!!" << endl;
            return 0;
        }
        default:
        {
            cout << "Wrong Input!!" << endl;
        }
        }
    }

    return 0;
}