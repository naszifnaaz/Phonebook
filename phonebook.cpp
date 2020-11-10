#include <iostream>
#include <fstream>
#include <string>
#include<cctype>

using namespace std;

// Maximum number of names in input file
const int MAX_NAMES = 100;

// Name of file containing names and phone numbers
const string PHONEBOOK_FILENAME = "phonebook.txt";


struct Person
{
	string name;
	string phone;


	Person()
	{
		name = "";
		phone = "";
	}

	bool Matches(string x)
	{
		
	   

		return (name.find(x) != string::npos);
	}

   

};

// Read all people in from data file.
// [out] people - Array that will contain all people from the data file
// [out] num_people - Number of people in the data file
void ReadAllPeople(Person people[], int &num_people)
{
	ifstream fin;
	fin.open(PHONEBOOK_FILENAME.c_str(), ios::app);
	if (fin.fail())
	{
		cout << "Unable to open file " << PHONEBOOK_FILENAME << endl;
		return;
	}

	int i = 0;
	getline(fin, people[i].name);
	while (!fin.eof() && i < MAX_NAMES)
	{
		getline(fin, people[i].phone);
	   
		i++;

		// Be careful not to read outside the array bounds
		if (i < MAX_NAMES)
			getline(fin, people[i].name);
	}

	num_people = i;

	fin.close();
}

// Save all the people in the array to the data file.
// [in] people - Array to write to file
// [in] num_people - Number of people in the array
void SaveToFile(const Person people[], int num_people)
{
	ofstream fout;

	fout.open(PHONEBOOK_FILENAME.c_str());

	for(int i = 0; i < num_people; i++)
	{
		fout << people[i].name<<endl;
		fout <<people[i].phone<<endl;
	}
   
}

// Append this person to the data file.
// [in] person - Person to be appended to the file
void AppendToFile(Person person)
{
	ofstream fin;
	fin.open(PHONEBOOK_FILENAME.c_str(),ios::app);

	fin << person.name<<endl;
	fin <<person.phone<<endl;

   
	fin.close();



   
}

// Read a name and phone number from the keyboard, add a new person to
// the array, and save the person to file using AppendToFile.
// [in/out] people - Array that the new person is added to
// [in/out] num_people - The number of people in the array (1 more once
//					   the new person is added)
void AddName(Person people[], int &num_people)
{
	Person person;
   

	cout <<"\nEnter a name to be added: ";
	getline(cin, person.name);
   
	cout <<"Enter the person's number: ";
	getline(cin, person.phone);

	for(int i = 0; i < num_people; i++)
	{
		if( i + 1  == num_people)
			people[num_people] = person;
	}
	num_people++;

   
	AppendToFile(person);
	cout <<"\n\nName has been added. "<<endl;

   

   
   
}

// Ask the for person's name to change, find the person in the array and
// change it to the new phone number.  Then save the new data to file by
// calling SaveToFile.
// [in/out] people - Array containing people
// [in]	 num_people - Number of people in the array
void ChangePhone(Person people[], int num_people)
{
	Person person;
	int count;

	cout <<"Enter name to change: ";
	getline(cin, person.name);


	for(count = 0; count < num_people; count++)
	{
		if(people[count].Matches(person.name))
		{	cout <<endl<< people[count].name<<endl;

		cout <<"Current number"<<people[count].phone;

		cout << "\nNew number: ";
		getline(cin, people[count].phone);

		SaveToFile(people,num_people);

		cout <<"\n\nNew number Saved.";   

		return;

		}

	}

	if(count = num_people)
		cout <<"\nName not found.";


}

// Ask the user for a name to find and show all occurrences of the name
// in the given array.
// [in] people - Array containing people
// [in] num_people - Number of people in the array
void FindName(Person people[], int num_people)
{
   
}

// Display all names and numbers.
// [in] people - Array containing people
// [in] num_people - Number of people in the array
void ListAllNames(const Person people[], int num_people)
{
	cout << "\n\nAll records:\n";
	for (int i = 0; i < num_people; i++)
		cout << people[i].name << " - " << people[i].phone << endl;
}

 main()
{
	Person people[MAX_NAMES];
	int num_people;

	// Get records from file
	ReadAllPeople(people, num_people);

	char choice;

	do
	{
		cout << "\n\nA - Add a name and phone number\n";
		cout << "C - Change a phone number\n";
		cout << "F - Find a name\n";
		cout << "L - List all names\n";
		cout << "Q - Quit\n\n";
		cout << "Choice? ";
		cin >> choice;
		cin.get();   // Read EOL

		choice = toupper(choice);

		switch(choice)
		{
			case 'A':	AddName(people, num_people);		break;
			case 'C':	ChangePhone(people, num_people);	break;
			case 'F':	FindName(people, num_people);		break;
			case 'L':	ListAllNames(people, num_people);	break;
		}
	} while (choice != 'Q' && choice != 'q');
}