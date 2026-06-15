#include "Member.h"
#include "Instructor.h"
#include "Lesson.h"
#include "Date.h"
#include "Car.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Here are some methods to help format our console output
int consoleWidth = 200; // Should we decide on a different size for console, we just change this value
int consoleClear = 100; // the amount of empty lines we print before showing a new screen
int consoleDelay = 3;	// the amount of time before a new screen is shown

void partition()
{
	for (int i = 0; i < consoleWidth; i++)
	{
		cout << "-";
	}
}
void centreText(string text)
{
	int padding = (consoleWidth - text.length()) / 2;
	for (int i = 0; i < padding; i++)
	{
		cout << " ";
	}
	cout << text << endl;
}
void newScreen()
{
	for (int i = 0; i < consoleClear; i++)
	{
		cout << endl;
	}
}
// Function prototypes to allow for function call before declaration
void startUpMenu();
vector<Instructor> loadRegisteredInstructors();
void learnerHomePage();
vector<Member> loadRegisteredMembers();
void saveMemberDetails(int memberId, string firstName, string lastName, string email, string telephone, string password, string transmission, int instructorId, int packageHours);
void instructorHomePage();


// These two vector will hold the details of our logged in user
vector<Instructor> loggedInInstructor;
vector<Member> loggedInLearner;

// Function to update instructor.csv after changing the details
void updateInstructorCSV(const vector<Instructor> &instructors)
{

	ofstream file("instructors.csv", ios::trunc); // Open file for writing and truncate it

	if (file.is_open())
	{
		// Write the header
		file << "InstructorID,FirstName,LastName,Email,Telephone,Password,CarMake,CarModel,CarTransmission,CarReg,Day1,Day2,Day3,Day4,Day5,Day6,Day7\n";

		// Write each instructor to the CSV
		for (const Instructor &instructor : instructors)
		{
			file << instructor.getInstructorID() << ','
				 << instructor.getFirstName() << ','
				 << instructor.getLastName() << ','
				 << instructor.getEmail() << ','
				 << instructor.getTelephone() << ','
				 << instructor.getPassword() << ','
				 << instructor.getCar().getCarMake() << ','
				 << instructor.getCar().getCarModel() << ','
				 << instructor.getCar().getCarTransmission() << ','
				 << instructor.getCar().getCarReg() << ',';
			// Writing days available, assuming vector<string> daysAvailable is available
			const auto &daysAvailable = instructor.getDaysAvailable();
			for (size_t i = 0; i < daysAvailable.size(); ++i)
			{
				file << daysAvailable[i];
				if (i < daysAvailable.size() - 1)
					file << ',';
			}
			file << '\n';
		}
		cout << "File written successfully." << endl;
		file.close();
	}
	else
	{
		cerr << "Failed to open instructors.csv for writing." << endl;
	}
}

// Function to update member.csv after changing the details
void updateMemberCSV(const vector<Member> &members)
{

	ofstream file("members.csv", ios::trunc); // Open file for writing and truncate it

	if (file.is_open())
	{
		// Write the header
		file << "memberID,firstName,lastName,email,telephone,password,transmission,instructorID,packageHours\n";

		
		for (const Member &member : members)
		{
			file << member.getMemberID() << ','
				 << member.getFirstName() << ','
				 << member.getLastName() << ','
				 << member.getEmail() << ','
				 << member.getTelephone() << ','
				 << member.getPassword() << ','
				 << member.getTransmission() << ','
				 << member.getInstructor().getInstructorID() << ','
				 << member.getPackageHours() << '\n';
		}
		cout << "File written successfully." << endl;
		file.close();
	}
	else
	{
		cerr << "Failed to open members.csv for writing." << endl;
	}
}


// Function to validate email format
bool emailValidation(string email)
{
	int at = email.find('@');
	int dot = email.find('.');

	if (at == string::npos || dot == string::npos)
	{
		return false;
	}
	if (at > dot)
	{
		return false;
	}
	if (dot - at < 2)
	{
		return false;
	}
	if (dot == email.length() - 1)
	{
		return false;
	}
	return true;
}

// Function to validates user input to not include a comma
bool inputValidation(string input)
{
	if (input.find(',') != string::npos)
	{
		return false;
	}
	return true;
}

// Functions to update instructor details
void updateFirstNameInstructor(Instructor &instructor)
{
	cout << "Enter new first name: ";
	string firstName;
	cin >> firstName;
	if (inputValidation(firstName))
	{
			instructor.setFirstName(firstName);
			cout << "First name updated successfully." << endl;
	} else
		{
			cout << "First name cannot contain a comma. Please try again." << endl;
		}
}

void updateLastNameInstructor(Instructor &instructor)
{
	cout << "Enter new last name: ";
	string lastName;
	cin >> lastName;
	if (inputValidation(lastName))
	{
		instructor.setLastName(lastName);
		cout << "Last name updated successfully." << endl;
	} else
		{
			cout << "Last name cannot contain a comma. Please try again." << endl;
		}
}

void updateEmailInstructor(Instructor &instructor)
{
	cout << "Enter new email: ";
	string email;
	cin >> email;
	
		if (emailValidation(email))
		{
			if (inputValidation(email))
			{
				
					instructor.setEmail(email);
					cout << "Email updated successfully." << endl;
			}
			else
			{
				cout << "Email cannot contain a comma. Please try again." << endl;
			}
		}
		else
		{
			cout << "Invalid email format. Please try again." << endl;
		}
}

void updateTelephoneInstructor(Instructor &instructor)
{
	cout << "Enter new telephone: ";
	string telephone;
	cin >> telephone;
	
	if (inputValidation(telephone))
	{
		
		instructor.setTelephone(telephone);
		cout << "Telephone updated successfully." << endl;
		
	}
	else
	{
		cout << "Telephone cannot contain a comma. Please try again." << endl;
	}
}

void updateCarMake(Instructor &instructor)
{
	cout << "Enter new car make: ";
	string carMake;
	cin >> carMake;
	
		if (inputValidation(carMake))
		{
			instructor.getCar().setCarMake(carMake);
			cout << "Car make updated successfully." << endl;
		}
		else
		{
			cout << "Car make cannot contain a comma. Please try again." << endl;
		}
	
}

void updateCarModel(Instructor &instructor)
{
	cout << "Enter new car model: ";
	string carModel;
	cin >> carModel;
	
		if (inputValidation(carModel))
		{
			instructor.getCar().setCarModel(carModel);
			cout << "Car model updated successfully." << endl;
		}
		else
		{
			cout << "Car model cannot contain a comma. Please try again." << endl;
		}
	
	
}

void updateCarTransmission(Instructor &instructor)
{
	cout << "Enter new car transmission (Automatic or Manual): ";
	string carTransmission;
	cin >> carTransmission;
	if ((carTransmission == "Automatic" || carTransmission == "Manual"))
	{
		instructor.getCar().setCarTransmission(carTransmission);
		cout << "Car transmission updated successfully." << endl;
	}
	else
	{
		cout << "Car transmission should be Automaic or Manual. Please try again." << endl;
	}
}

void updateCarReg(Instructor &instructor)
{
	cout << "Enter new car registration: ";
	string carReg;
	cin >> carReg;
	
		if (inputValidation(carReg))
		{
			instructor.getCar().setCarReg(carReg);
			cout << "Car registration updated successfully." << endl;
		}
		else
		{
			cout << "Car registration cannot contain a comma. Please try again." << endl;
		}

}


// Function to update personal details for Instructor
void updatePersonalInstructorDetails()
{

	vector<Instructor> instructors = loadRegisteredInstructors();
	bool instructorFound = false;

	for (Instructor &i : instructors)
	{
		if (i.getInstructorID() == loggedInInstructor[0].getInstructorID())
		{
			instructorFound = true;

			cout << "Please select the field you would like to update: " << endl;
			cout << "1. First Name" << endl;
			cout << "2. Last Name" << endl;
			cout << "3. Email" << endl;
			cout << "4. Telephone" << endl;
			cout << "5. Car Make" << endl;
			cout << "6. Car Model" << endl;
			cout << "7. Car Transmission" << endl;
			cout << "8. Car Registration" << endl;
			

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				updateFirstNameInstructor(i);
				break;

			case 2:
				updateLastNameInstructor(i);
				break;

			case 3:
				updateEmailInstructor(i);
				break;
				
			case 4:
				updateTelephoneInstructor(i);
				break;

			case 5:
				updateCarMake(i);
				break;

			case 6:
				updateCarModel(i);
				break;

			case 7:
				updateCarTransmission(i);
				break;

			case 8:
				updateCarReg(i);
				break;


			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
			}

			updateInstructorCSV(instructors);
			cout << "Details updated successfully." << endl;
			break;
		}
	}

	if (!instructorFound)
	{
		cout << "Instructor not found. Please try again." << endl;
	}
}

// Function to chnage the password of the instructor
void changePassword(Instructor &instructor)
{
	vector<Instructor> instructors = loadRegisteredInstructors();
	bool instructorFound = false;

	cout << "Please enter your current password: ";
	string currentPassword;
	cin >> currentPassword;

	if (currentPassword == loggedInInstructor[0].getPassword())
	{
		for (Instructor &i : instructors)
		{
			if (i.getInstructorID() == loggedInInstructor[0].getInstructorID())
			{
				instructorFound = true;

				cout << "Please enter your new password: ";
				string newPassword;
				cin >> newPassword;

				cout << "Please confirm your new password: ";
				string confirmPassword;
				cin >> confirmPassword;

				if (inputValidation(newPassword) && inputValidation(confirmPassword))
				{
					if (newPassword == confirmPassword)
					{
						i.setPassword(newPassword);
						updateInstructorCSV(instructors);
						cout << "Password changed successfully!" << endl;
					}
					else
					{
						cout << "Passwords do not match. Please try again." << endl;
					}
					break;
				} else {
					cout << "Password cannot contain a comma. Please try again." << endl;
				}
			}
		}
		if (!instructorFound)
		{
			cout << "Instructor not found. Please try again." << endl;
		}
	}
	else
	{
		cout << "Incorrect password. Please try again." << endl;
	}
}

// Function to save lessons to the lessons.csv
void saveLessonDetails(int lessonID, Instructor instruc, Member learner, Date date, string lessonType, string lessonStatus, string lessonNote)
{
	ofstream file("lessons.csv", ios::app);
	file << lessonID << "," << instruc.getInstructorID() << "," << learner.getMemberID() << "," << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << ","
		 << date.getTimeSlot() << "," << lessonType << "," << lessonStatus << ",\"" << lessonNote << "\"" << endl;
	file.close();
}

vector<Lesson> loadLessons()
{
	vector<Lesson> allLessons;
	ifstream file("lessons.csv");
	if (file.is_open())
	{
		string line;
		getline(file, line); // skip the header is needed
		while (getline(file, line))
		{
			stringstream ss(line);
			int lessonId, memberId, instructorId, day, month, year, timeSlot;
			string lessonIdStr, instructorIdStr, timeSlotStr, memberIdStr, dayStr, monthStr, yearStr, lessonType, lessonStatus, lessonNote, trash;
			getline(ss, lessonIdStr, ',');
			lessonId = stoi(lessonIdStr);
			getline(ss, instructorIdStr, ',');
			instructorId = stoi(instructorIdStr);
			getline(ss, memberIdStr, ',');
			memberId = stoi(memberIdStr);
			getline(ss, dayStr, '/');
			day = stoi(dayStr);
			getline(ss, monthStr, '/');
			month = stoi(monthStr);
			getline(ss, yearStr, ',');
			year = stoi(yearStr);
			getline(ss, timeSlotStr, ',');
			timeSlot = stoi(timeSlotStr);
			getline(ss, lessonType, ',');
			getline(ss, lessonStatus, ',');
			getline(ss, trash, '"');
			getline(ss, lessonNote, '"');
			Date date(timeSlot, day, month, year);
			Lesson lesson(lessonId, date, lessonType, lessonStatus, lessonNote, instructorId, memberId);
			allLessons.emplace_back(lesson);
		}
		file.close();
	}

	return allLessons;
}

// Function to save details into csv file (original with file-opening code
// and some attributes being saved in written by Neomi (this is included in
// the comments section for the Login function task in Azure please check for
// the original there), changes and implementation into main by Abdurahmon)
void saveMemberDetails(int memberId, string firstName, string lastName,
					   string email, string telephone, string password,
					   string transmission, int instructorId, int packageHours)
{
	ofstream file("members.csv", ios::app);
	file << memberId << "," << firstName << "," << lastName << "," << email << "," << telephone << "," << password << "," << transmission << "," << instructorId << "," << packageHours << endl;
	file.close();
}

// original with file-opening code and some attributes being saved in written
// by Neomi (this is included in the comments section for the Login function
// task in Azure please check for the original there), changes and implementation into main by Abdurahmon
void saveInstructorDetails(int instructorId, string firstName, string lastName,
						   string email, string telephone, string password,
						   string carMake, string carModel, string carTransmission,
						   string carReg, vector<string> daysAvailable)
{
	ofstream file("instructors.csv", ios::app);
	file << instructorId << "," << firstName << "," << lastName << "," << email << "," << telephone << "," << password << "," << carMake << "," << carModel << "," << carTransmission << "," << carReg << "," << daysAvailable[0] << "," << daysAvailable[1] << "," << daysAvailable[2] << "," << daysAvailable[3] << "," << daysAvailable[4] << "," << daysAvailable[5] << daysAvailable[6] << endl; // this was changed and added by abdurahmon
	file.close();
}

// original with file-opening code and some attributes being read in written by
// Neomi (this is included in comments section for the Login function task in
// Azure please check for the original there), changes and implementation into main by Abdurahmon
vector<Member> loadRegisteredMembers()
{
	vector<Member> registeredMembers;
	ifstream file("members.csv");
	if (file.is_open())
	{
		string line;
		getline(file, line); // skip the header is needed
		while (getline(file, line))
		{
			stringstream ss(line);
			int memberId, instructorId, packageHours;
			string memberIdStr, firstName, lastName, email, telephone, password, transmission, instructorIdStr, packageHoursStr;
			getline(ss, memberIdStr, ',');
			memberId = stoi(memberIdStr);
			getline(ss, firstName, ',');
			getline(ss, lastName, ',');
			getline(ss, email, ',');
			getline(ss, telephone, ',');
			getline(ss, password, ',');
			getline(ss, transmission, ',');
			getline(ss, instructorIdStr, ',');
			instructorId = stoi(instructorIdStr);
			getline(ss, packageHoursStr, ',');
			packageHours = stoi(packageHoursStr);
			vector<Instructor> instructorVec = loadRegisteredInstructors();
			Instructor instructor;
			if (instructorId != -1)
			{
				for (int i = 0; i < instructorVec.size(); i++)
				{
					if (instructorVec[i].getInstructorID() == instructorId)
					{
						instructor = instructorVec[i];
					}
				}
			}
			else
			{
				instructor.setFirstName("No instructor assigned.");
				instructor.setLastName("No instructor assigned.");
			}
			Member member(memberId, firstName, lastName, email, password, telephone);
			member.setInstructor(instructor);
			member.setTransmission(transmission);
			member.setPackageHours(packageHours);
			registeredMembers.emplace_back(member);
		}
		file.close();
	}

	return registeredMembers;
}

// Function to load in the instructors we have stored in our instructors.csv
// (original with file-opening code and some attributes being read in written
// by Neomi (this is included in comments section for the Login function task
// in Azure please check for the original there), changes and implementation into main by Abdurahmon)
vector<Instructor> loadRegisteredInstructors()
{
	vector<Instructor> registeredInstructors;
	ifstream file("instructors.csv");

	if (file.is_open())
	{
		string line;
		getline(file, line); // skip the header is needed
		while (getline(file, line))
		{
			stringstream ss(line);
			int instructorId;
			string instructorIdStr, firstName, lastName, email, telephone, password, carMake, carModel, carTransmission, carReg; // the attributes were added by abdurahmon with the part parsing the added attributes and daysAvaible vector
			vector<string> daysAvailable = {"1", "1", "1", "1", "1", "1", "1"};
			getline(ss, instructorIdStr, ',');
			instructorId = stoi(instructorIdStr);
			getline(ss, firstName, ',');
			getline(ss, lastName, ',');
			getline(ss, email, ',');
			getline(ss, telephone, ',');
			getline(ss, password, ',');
			getline(ss, carMake, ',');
			getline(ss, carModel, ',');
			getline(ss, carTransmission, ',');
			getline(ss, carReg, ',');
			getline(ss, daysAvailable[0], ',');
			getline(ss, daysAvailable[1], ',');
			getline(ss, daysAvailable[2], ',');
			getline(ss, daysAvailable[3], ',');
			getline(ss, daysAvailable[4], ',');
			getline(ss, daysAvailable[5], ',');
			getline(ss, daysAvailable[6], ',');
			Car car(carMake, carModel, carReg, carTransmission);
			Instructor instructor(instructorId, firstName, lastName, email, password, telephone, car, daysAvailable);
			registeredInstructors.emplace_back(instructor);
		}
		file.close();
	}

	return registeredInstructors;
}

void registrationPage()
{
	partition();
	cout << endl;
	centreText("Rana Systems");
	cout << endl;
	centreText("Register as a new learner or as an instructor by simply entering your");
	centreText("unique details below.");
	for (int i = 0; i < 5; i++)
	{
		cout << endl;
	}
	int registerChoice;
	cout << "Please specify what account you wish to open with us - \n"
		 << endl;
	cout << "    1 - Learner\n"
		 << "    2 - Instructor\n"
		 << "    0 - Go back to main menu\n"
		 << endl;
	cout << "Enter your choice here > ";
	cin >> registerChoice;
	while (!cin)
	{
		cout << "Not a valid choice, please pick from the previous options" << endl;
		cin.clear();  // clear the error
		cin.ignore(); // ignore the non integer inputted
		cin >> registerChoice;
	}
	while ((registerChoice < 0) || (registerChoice > 2))
	{
		cout << endl
			 << "Not a valid choice, please pick from the previous options." << endl;
		cin.clear();  // clear the error
		cin.ignore(); // ignore the previously inputted string
		cin >> registerChoice;
	}
	switch (registerChoice)
	{
	case 0:
	{ // Back to start menu
		cout << endl;
		partition();
		cout << endl;
		centreText("Returning to main menu...");
		cout << endl;
		partition();
		chrono::seconds delay(consoleDelay);
		this_thread::sleep_for(delay);
		newScreen();
		startUpMenu();
		break;
	}
	case 1:
	{ // Register as a learner
		cout << endl;
		partition();
		cout << endl;
		centreText("Learner registration");
		partition();
		cout << endl;
		string inFName;
		string inLName;
		string inEmail;
		string inTelephone;
		string inPassword;
		string inConfirmPassword;
		int transChoice;
		string inTransmission;
		bool emailCheck = false;
		bool telephoneCheck = false;
		bool confirmPassword = false;
		cout << endl
			 << "Please provide your first name (or preferred name).\n";
		cout << "> ";
		cin >> inFName;
		cout << endl
			 << "Please provide your last name (surname).\n";
		cout << "> ";
		cin >> inLName;
		cout << endl
			 << "Please provide your email address.\n";
		cout << "> ";
		cin >> inEmail;
		cout << endl
			 << "Please provide your telephone number (in the format of 075674532876).\n";
		cout << "> ";
		cin >> inTelephone;
		cout << endl
			 << endl
			 << "Please choose which type of lesson you wish to take.\n";
		cout << "    1 - Manual\n";
		cout << "    2 - Automatic\n"
			 << endl;
		cout << "> ";
		cin >> transChoice;
		while (!cin)
		{
			cout << "Not a valid choice, please pick from the previous options" << endl;
			cin.clear();  // clear the error
			cin.ignore(); // ignore the non integer inputted
			cin >> transChoice;
		}
		while ((transChoice < 1) || (transChoice > 2))
		{
			cout << endl
				 << "Not a valid choice, please pick from the previous options." << endl;
			cin.clear();  // clear the error
			cin.ignore(); // ignore the previously inputted string
			cin >> transChoice;
		}
		switch (transChoice)
		{
		case 1:
		{
			inTransmission = "Manual";
			break;
		}
		case 2:
		{
			inTransmission = "Automatic";
			break;
		}
		}
		cout << endl
			 << "Please enter a password for your account.\n";
		cout << "> ";
		cin >> inPassword;
		cout << endl
			 << "Please confirm your password.\n";
		cout << "> ";
		cin >> inConfirmPassword;

		if (inPassword == inConfirmPassword)
		{
			confirmPassword = true;
		}

		/*
		  Here we will check if the inputted identifying details are unique
		  and if they confirmed their password correctly and set the flags
		  accordingly
		*/
		vector<Member> memVec = loadRegisteredMembers();
		vector<Instructor> instrucVec = loadRegisteredInstructors();
		for (Member mem : memVec)
		{
			if (mem.getEmail() == inEmail)
			{
				emailCheck = false;
				break;
			}
			else
			{
				emailCheck = true;
			}
			if (mem.getTelephone() == inTelephone)
			{
				telephoneCheck = false;
				break;
			}
			else
			{
				telephoneCheck = true;
			}
		}
		for (Instructor instruc : instrucVec)
		{
			if (emailCheck == true)
			{
				if (instruc.getEmail() == inEmail)
				{
					emailCheck = false;
					break;
				}
				else
				{
					emailCheck = true;
				}
			}
			if (telephoneCheck == true)
			{
				if (instruc.getTelephone() == inTelephone)
				{
					telephoneCheck = false;
					break;
				}
				else
				{
					telephoneCheck = true;
				}
			}
		}

		if (confirmPassword == false)
		{
			// if the user did not match their password a second time then they would have to resubmit the form
			cout << endl
				 << "Your passwords do not match. Please resubmit your registration form.\n";
			cout << endl;
			partition();
			cout << endl
				 << endl;
			centreText("Returning to registration page");
			chrono::seconds delay(consoleDelay);
			this_thread::sleep_for(delay);
			newScreen();
			registrationPage();
		}
		else if ((emailCheck == false) || (telephoneCheck == false))
		{ // If the inputted email or telephone is in use already then we reject the form
			cout << endl
				 << "Your contact details are already registered to an existing account. Please review your details and resubmit your registration form.\n";
			cout << endl;
			partition();
			cout << endl
				 << endl;
			centreText("Returning to registration page");
			chrono::seconds delay(consoleDelay);
			this_thread::sleep_for(delay);
			newScreen();
			registrationPage();
		}
		else
		{ // registration successful
			cout << endl;
			partition();
			cout << endl;
			centreText("Detail review");
			partition();
			cout << endl
				 << endl
				 << "Review your account details carefully before account creation.\n";
			cout << endl
				 << "  Name: " << inFName << " " << inLName << endl;
			cout << "  Email: " << inEmail << endl;
			cout << "  Telephone: " << inTelephone << endl;
			cout << "  Password: " << inPassword << endl;
			cout << endl
				 << "Please select an option from the following: \n";
			cout << "    1 - Create account\n";
			cout << "    2 - Cancel registration\n"
				 << endl;
			cout << "Enter choice here > ";
			int createChoice;
			cin >> createChoice;
			while (!cin)
			{
				cout << "Not a valid choice, please pick from the previous options" << endl;
				cin.clear();  // clear the error
				cin.ignore(); // ignore the non integer inputted
				cin >> createChoice;
			}
			while ((createChoice < 1) || (createChoice > 2))
			{
				cout << endl
					 << "Not a valid choice, please pick from the previous options." << endl;
				cin.clear();  // clear the error
				cin.ignore(); // ignore the previously inputted string
				cin >> createChoice;
			}
			switch (createChoice)
			{
			case 1:
			{

				int id = loadRegisteredMembers().size() + 1;
				saveMemberDetails(id, inFName, inLName, inEmail, inTelephone, inPassword, inTransmission, -1, 0);
				partition();
				cout << endl;
				centreText("Registration successful!");
				cout << endl;
				centreText("Returning to start menu...");
				cout << endl;
				partition();
				chrono::seconds delay(consoleDelay);
				this_thread::sleep_for(delay);
				newScreen();
				startUpMenu();
				break;
			}
			case 2:
			{ // Go back to registration page
				cout << endl;
				partition();
				cout << endl;
				centreText("Registration terminated");
				partition();
				cout << endl
					 << endl;
				centreText("Returning to registration page...");
				partition();
				chrono::seconds delay(consoleDelay);
				this_thread::sleep_for(delay);
				newScreen();
				registrationPage();
				break;
			}
			}
		}

		break;
	}
	case 2:
	{ // Register as an instructor
		cout << endl;
		partition();
		cout << endl;
		centreText("Instructor registration");
		partition();
		cout << endl;
		string inFName;
		string inLName;
		string inEmail;
		string inTelephone;
		string inPassword;
		string inConfirmPassword;
		string carMake;
		string carModel;
		string carReg;
		int transChoice;
		string carTrans;
		bool emailCheck = false;
		bool telephoneCheck = false;
		bool confirmPassword = false;

		cout << endl
			 << "Please provide your first name (or preferred name).\n";
		cout << "> ";
		cin >> inFName;
		cout << endl
			 << "Please provide your last name (surname).\n";
		cout << "> ";
		cin >> inLName;
		cout << endl
			 << "Please provide your email address.\n";
		cout << "> ";
		cin >> inEmail;
		cout << endl
			 << "Please provide your telephone number (in the format of 075674532876).\n";
		cout << "> ";
		cin >> inTelephone;

		cout << endl
			 << endl;
		centreText("FOR YOUR INFORMATION:");
		centreText("Please understand that all lessons taught by yourself will be conducted in your personal vehicle (all costs incurred during a lesson are covered by the company).");
		cout << endl
			 << "Please provide your car make (FYI - the company that made the car)\n";
		cout << "> ";
		cin >> carMake;
		cout << endl
			 << "Please provide your car model (FYI - the name of the car)\n";
		cout << "> ";
		cin >> carModel;
		cout << endl
			 << endl;
		centreText("FOR YOUR INFORMATION:");
		centreText("The type of lesson you can teach will be restricted to the transmission of your car.");
		cout << endl
			 << "Please provide the transmission of your car (manual or automatic)\n"
			 << "    1 - Manual\n"
			 << "    2 - Automatic\n"
			 << endl;
		cout << "> ";
		cin >> transChoice;
		while (!cin)
		{
			cout << "Not a valid choice, please pick from the previous options" << endl;
			cin.clear();  // clear the error
			cin.ignore(); // ignore the non integer inputted
			cin >> transChoice;
		}
		while ((transChoice < 1) || (transChoice > 2))
		{
			cout << endl
				 << "Not a valid choice, please pick from the previous options." << endl;
			cin.clear();  // clear the error
			cin.ignore(); // ignore the previously inputted string
			cin >> transChoice;
		}
		switch (transChoice)
		{
		case 1:
		{
			carTrans = "Manual";
			break;
		}
		case 2:
		{
			carTrans = "Automatic";
			break;
		}
		}
		cout << endl
			 << "Please provide your car registration number\n";
		cout << "> ";
		cin >> carReg;
		cout << endl
			 << "Please enter a password for your account.\n";
		cout << "> ";
		cin >> inPassword;
		cout << endl
			 << "Please confirm your password.\n";
		cout << "> ";
		cin >> inConfirmPassword;

		if (inPassword == inConfirmPassword)
		{
			confirmPassword = true;
		}

		/*
		  Here we will check if the inputted identifying details are unique
		  by pulling in info from the csv files and check if they exist
		  and if they confirmed their password correctly and set the flags
		  accordingly
		*/
		vector<Member> memVec = loadRegisteredMembers();
		vector<Instructor> instrucVec = loadRegisteredInstructors();
		for (Instructor instruc : instrucVec)
		{
			if (instruc.getEmail() == inEmail)
			{
				emailCheck = false;
				break;
			}
			else
			{
				emailCheck = true;
			}
			if (instruc.getTelephone() == inTelephone)
			{
				telephoneCheck = false;
				break;
			}
			else
			{
				telephoneCheck = true;
			}
		}
		for (Member mem : memVec)
		{
			if (emailCheck == true)
			{
				if (mem.getEmail() == inEmail)
				{
					emailCheck = false;
					break;
				}
				else
				{
					emailCheck = true;
				}
			}
			if (telephoneCheck == true)
			{
				if (mem.getTelephone() == inTelephone)
				{
					telephoneCheck = false;
					break;
				}
				else
				{
					telephoneCheck = true;
				}
			}
		}

		if (confirmPassword == false)
		{
			// if the user did not match their password a second time then they would have to resubmit the form
			cout << endl
				 << "Your passwords do not match. Please resubmit your registration form.\n";
			cout << endl;
			partition();
			cout << endl
				 << endl;
			centreText("Returning to registration page");
			chrono::seconds delay(consoleDelay);
			this_thread::sleep_for(delay);
			newScreen();
			registrationPage();
		}
		else if ((emailCheck == false) || (telephoneCheck == false))
		{ // If the inputted email or telephone is in use already then we reject the form
			cout << endl
				 << "Your contact details are already registered to an existing account. Please review your details and resubmit your registration form.\n";
			cout << endl;
			partition();
			cout << endl
				 << endl;
			centreText("Returning to registration page");
			chrono::seconds delay(consoleDelay);
			this_thread::sleep_for(delay);
			newScreen();
			registrationPage();
		}
		else
		{ // registration successful
			cout << endl;
			partition();
			cout << endl;
			centreText("Detail review");
			partition();
			cout << endl
				 << endl
				 << "Review your account details carefully before account creation.\n";
			cout << endl
				 << "  Name: " << inFName << " " << inLName << endl;
			cout << "  Email: " << inEmail << endl;
			cout << "  Telephone: " << inTelephone << endl;
			cout << "  Password: " << inPassword << endl
				 << endl;
			cout << "  Car details: " << endl;
			cout << "  Make: " << carMake << endl;
			cout << "  Model: " << carModel << endl;
			cout << "  Transmission: " << carTrans << endl;
			cout << "  Registration: " << carReg << endl;
			cout << endl
				 << "Please select an option from the following: \n";
			cout << "    1 - Create account\n";
			cout << "    2 - Cancel registration\n"
				 << endl;
			cout << "Enter choice here > ";
			int createChoice;
			cin >> createChoice;
			while (!cin)
			{
				cout << "Not a valid choice, please pick from the previous options" << endl;
				cin.clear();  // clear the error
				cin.ignore(); // ignore the non integer inputted
				cin >> createChoice;
			}
			while ((createChoice < 1) || (createChoice > 2))
			{
				cout << endl
					 << "Not a valid choice, please pick from the previous options." << endl;
				cin.clear();  // clear the error
				cin.ignore(); // ignore the previously inputted string
				cin >> createChoice;
			}
			switch (createChoice)
			{
			case 1:
			{
				int id = loadRegisteredInstructors().size() + 1;
				vector<string> daysAvail = {"1", "1", "1", "1", "1", "1", "1"};
				saveInstructorDetails(id, inFName, inLName, inEmail, inTelephone, inPassword, carMake, carModel, carTrans, carReg, daysAvail);
				partition();
				cout << endl;
				centreText("Registration successful!");
				cout << endl;
				centreText("Returning to start menu...");
				cout << endl;
				partition();
				chrono::seconds delay(consoleDelay);
				this_thread::sleep_for(delay);
				newScreen();
				startUpMenu();
				break;
			}
			case 2:
			{ // Go back to registration page
				cout << endl;
				partition();
				cout << endl;
				centreText("Registration terminated");
				partition();
				cout << endl
					 << endl;
				centreText("Returning to registration page...");
				partition();
				chrono::seconds delay(consoleDelay);
				this_thread::sleep_for(delay);
				newScreen();
				registrationPage();
				break;
			}
			}
		}
	}
	}
}

void startUpMenu()
{
	partition();
	cout << endl
		 << endl;
	centreText("Welcome to Rana Systems!");
	cout << endl;
	centreText("A cutting-edge driving lesson booking system that can be implemented");
	centreText("into driving schools worldwide.");
	cout << endl
		 << endl
		 << endl
		 << "Please pick from the following options - \n"
		 << endl;
	cout << "    1 - Login \n"
		 << "    2 - Registration\n"
		 << "    3 - Exit Rana Systems\n"
		 << endl;
	cout << "Enter your desired action here (e.g enter 1 if you wish to login) > ";
	int startChoice;
	cin >> startChoice;
	while (!cin)
	{
		cout << "Not a valid choice, please pick from the previous options" << endl;
		cin.clear();  // clear the error
		cin.ignore(); // ignore the non integer inputted
		cin >> startChoice;
	}
	while ((startChoice < 1) || (startChoice > 3))
	{
		cout << endl
			 << "Not a valid choice, please pick from the previous options." << endl;
		cin.clear();  // clear the error
		cin.ignore(); // ignore the previously inputted string
		cin >> startChoice;
	}
	switch (startChoice)
	{
	case 1:
	{
		partition();
		newScreen();
		cout << endl;
		partition();
		cout << endl
			 << endl;
		centreText("Rana Systems");
		cout << endl;
		centreText("Login to your existing account with us, as either an instructor or a learner to access your dashboard.");
		for (int i = 0; i < 5; i++)
		{
			cout << endl;
		}
		string inputEmail;
		string inputPassword;
		cout << "Please enter your registered email address > ";
		cin >> inputEmail;
		cout << "Please enter your password > ";
		cin >> inputPassword;
		bool emailCheck = false;
		bool passwordCheck = false;
		bool instructorCheck = false;
		bool memberCheck = false;
		vector<Member> memVec = loadRegisteredMembers();
		Member member;
		vector<Instructor> instructorVec = loadRegisteredInstructors();
		Instructor instructor;
		for (Member mem : memVec)
		{
			if (mem.getEmail() == inputEmail)
			{
				emailCheck = true;
				if (mem.getPassword() == inputPassword)
				{
					passwordCheck = true;
					memberCheck = true;
					member = mem;
				}
			}
		}
		for (Instructor instruc : instructorVec)
		{
			if (instruc.getEmail() == inputEmail)
			{
				emailCheck = true;
				if (instruc.getPassword() == inputPassword)
				{
					passwordCheck = true;
					instructorCheck = true;
					instructor = instruc;
				}
			}
		}
		if (emailCheck == true)
		{
			if (passwordCheck == true)
			{
				if (memberCheck == true)
				{
					loggedInLearner.emplace_back(member);
					cout << endl
						 << "Successfully logged in as " << loggedInLearner[0].getFirstName() << " " << loggedInLearner[0].getLastName() << "."
						 << endl;
					partition();
					cout << endl
						 << endl;
					centreText("Entering home menu...");
					cout << endl;
					partition();
					chrono::seconds delay(consoleDelay);
					this_thread::sleep_for(delay);
					newScreen();
					learnerHomePage();
				}
				else if (instructorCheck == true)
				{
					loggedInInstructor.emplace_back(instructor);
					cout << endl
						 << "Successfully logged in as " << loggedInInstructor[0].getFirstName() << " " << loggedInInstructor[0].getLastName() << "."
						 << endl;
					partition();
					cout << endl
						 << endl;
					centreText("Entering home menu...");
					cout << endl;
					partition();
					chrono::seconds delay(consoleDelay);
					this_thread::sleep_for(delay);
					newScreen();
					instructorHomePage();
				}
			}
			else
			{
				cout << endl
					 << "That email and password combination did not match any of our accounts. Please double check your entries.\n"
					 << endl;
				partition();
				cout << endl;
				centreText("Returning to start menu...");
				cout << endl;
				partition();
				chrono::seconds delay(consoleDelay);
				this_thread::sleep_for(delay);
				newScreen();
				startUpMenu();
			}
		}
		else
		{
			cout << endl
				 << "That email did not match any accounts registered. Do you have an account?\n"
				 << endl;
			partition();
			cout << endl
				 << endl;
			centreText("Returning to start menu...");
			cout << endl;
			partition();
			chrono::seconds delay(consoleDelay);
			this_thread::sleep_for(delay);
			newScreen();
			startUpMenu();
		}
		break;
	}
	case 2:
	{
		partition();
		newScreen();
		registrationPage();
		break;
	}
	case 3:
	{
		partition();
		cout << endl
			 << endl;
		centreText("Closing Rana Systems..");
		cout << endl;
		centreText("Goodbye!");
		cout << endl;
		partition();
		break;
	}
	}
}

void updateInstructor(int memberID, int newInstrucID)
{
	ifstream file("members.csv"); // Open CSV file for reading
	string header;
	getline(file, header);
	vector<string> lines; // Vector to store lines from CSV file
	// Read each line from the CSV file and store it in the vector
	string line;
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	file.close(); // Close the file
	ofstream outfile("members.csv");
	// Write the header line back to the file
	outfile << header << endl;
	for (string line : lines)
	{
		stringstream ss(line);
		string token;
		getline(ss, token, ','); // memberID
		if (stoi(token) == memberID)
		{																   // Check if it's the specified member
			int packHours = stoi(line.substr(line.find_last_of(',') + 1)); // extract the packageHours
			int commaCount = 0;
			int secondToLastCommaIndex;
			for (int i = line.size() - 1; i >= 0; --i)
			{
				if (line[i] == ',')
				{
					++commaCount;
					if (commaCount == 2)
					{
						secondToLastCommaIndex = i;
						break;
					}
				}
			}
			for (int i = 0; i < 6; ++i)
				getline(ss, token, ','); // Skip the first 6 fields
			outfile << line.substr(0, secondToLastCommaIndex + 1) << newInstrucID << "," << packHours << endl;
		}
		else
		{
			outfile << line << endl; // unchanged line to file
		}
	}
}

void updatePackageHours(int memberID, int newHours)
{
	ifstream file("members.csv"); // Open CSV file for reading
	string header;
	getline(file, header);
	vector<string> lines; // Vector to store lines from CSV file
	// Read each line from the CSV file and store it in the vector
	string line;
	while (getline(file, line))
	{
		lines.push_back(line);
	}
	file.close(); // Close the file
	ofstream outfile("members.csv");
	// Write the header line back to the file
	outfile << header << endl;
	for (string line : lines)
	{
		stringstream ss(line);
		string token;
		getline(ss, token, ','); // memberID
		if (stoi(token) == memberID)
		{ // Check if it's the specified member
			// Update packageHours
			for (int i = 0; i < 7; ++i)
				getline(ss, token, ','); // Skip the first 7 fields
			outfile << line.substr(0, line.find_last_of(',') + 1) << newHours << endl;
		}
		else
		{
			outfile << line << endl; // unchanged line to file
		}
	}
	outfile.close(); // Close the file
}

bool isValidDate(int day, int month, int year)
{
	// basic validation for day, month, and year ranges
	if (year < 0 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}
	if (month == 2)
	{
		// check for leap year
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			if (day > 29)
				return false;
		}
		else
		{
			if (day > 28)
				return false;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			return false;
		}
	}
	else
	{
		if (day > 31)
		{
			return false;
		}
	}
	// get the current date
	Date currentDate;
	int currentDay = currentDate.getDay();
	int currentMonth = currentDate.getMonth();
	int currentYear = currentDate.getYear();

	// check if the inputted date is today's date or earlier as we only want them to book a lesson in the future
	if (year < currentYear || (year == currentYear && month < currentMonth) || (year == currentYear && month == currentMonth && day < currentDay) || (year == currentYear && month == currentMonth && day == currentDay))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool isInstructorFree(Date inputDate)
{
	vector<string> instrucDaysAvail = loggedInLearner[0].getInstructor().getDaysAvailable(); // a 7 element long vector representing availibility on days "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" with 0 meaning not available and 1 meaning is available
	int day, month, year;
	day = inputDate.getDay();
	month = inputDate.getMonth();
	year = inputDate.getYear();
	// zellers congruence
	if (month < 3)
	{
		month += 12;
		year -= 1;
	}

	int k = year % 100;
	int j = year / 100;

	int dayOfWeek = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;

	if (instrucDaysAvail[dayOfWeek] == "1")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isTimeSlotFree(int timeSlot)
{
	vector<Lesson> allLessons = loadLessons();
	vector<Lesson> lessonVec;
	for (Lesson less : allLessons)
	{
		if ((less.getInstructorID() == loggedInLearner[0].getInstructor().getInstructorID()) && (less.getLessonDate().getTimeSlot() == timeSlot) && (less.getLessonStatus() == "Booked"))
		{
			lessonVec.emplace_back(less);
		}
	}
	if (lessonVec.size() == 0)
	{ // the timeslot is free
		return true;
	}
	else
	{
		return false;
	}
}

void bookLesson()
{
	if (loggedInLearner[0].getInstructor().getInstructorID() == 0)
	{ // doesn't yet have an instructor
		centreText("You currently do not have an instructor assigned to you.\n");
		centreText("Simply navigate to the home menu, and choose option 6 (named Change instructor) to pick");
		centreText("out an instructor of your liking.\n");
		partition();
		cout << endl;
	}
	else
	{ // has an instructor already
		if (loggedInLearner[0].getPackageHours() == 0)
		{ // if has no more hours
			centreText("You currently have zero lesson hours remaining and are therefore");
			centreText("unable to book a lesson. Please purchase a new lesson package to buy more lessons");
			partition();
			cout << endl;
		}
		else
		{
			centreText("You currently have " + to_string(loggedInLearner[0].getPackageHours()) + " hours");
			centreText("remaining on your purchased package.\n");
			int day, month, year;
			Date inputDate;
			inputDate.setDay(inputDate.getDay() - 1);
			cout << endl
				 << "Enter the day of the date that you wish to book a lesson on.\nFYI: You can only book a lesson on a date later than today, we do not accept same-day bookings.\n";
			while (isValidDate(inputDate.getDay(), inputDate.getMonth(), inputDate.getYear()) == false)
			{
				cout << "\nEnter day here > ";
				cin >> day;
				while (!cin)
				{
					cout << "Not a valid day, please enter a valid day." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the non integer inputted
					cin >> day;
				}

				cout << "\nEnter the month of the date that you wish to book a lesson.\n"
					 << "Enter month here > ";
				cin >> month;
				while (!cin)
				{
					cout << "Not a valid month, please enter a valid month." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the non integer inputted
					cin >> month;
				}

				cout << "\nEnter the year of the date that you wish to book a lesson.\n"
					 << "Enter year here > ";
				cin >> year;
				while (!cin)
				{
					cout << "Not a valid year, please enter a valid year." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the non integer inputted
					cin >> month;
				}
				inputDate.setDay(day);
				inputDate.setMonth(month);
				inputDate.setYear(year);
				if (!isValidDate(inputDate.getDay(), inputDate.getMonth(), inputDate.getYear()))
				{
					cout << endl;
					centreText("Date selection unsuccessful. The entered date is invalid, please enter a valid date.");
					centreText("FYI: We don't not accept same day bookings.\n");
				}
			}
			if (isInstructorFree(inputDate))
			{ // the instructor is free on the day (checking against daysAvailable vector)
				// we then check if the instructor doesn't already have a lesson in the slot that our user wants to book in.
				cout << endl
					 << endl;
				partition();
				cout << endl
					 << endl
					 << "Date chosen: " << inputDate.displayDate() << "\n\n"
					 << "Please pick from the times below:\n"
					 << "    1 - 07:00 - 09:00\n"
					 << "    2 - 09:00 - 11:00\n"
					 << "    3 - 11:00 - 13:00\n"
					 << "    4 - 13:00 - 15:00\n"
					 << "    5 - 15:00 - 17:00\n\n"
					 << "Enter your choice here > ";
				int timeChoice;
				cin >> timeChoice;
				while (!cin)
				{
					cout << "Not a valid option, please pick from the previous time-slots." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the non integer inputted
					cin >> timeChoice;
				}
				while ((timeChoice < 1) || (timeChoice > 5))
				{
					cout << endl
						 << "Not a valid choice, please pick from the previous options." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the previously inputted string
					cin >> timeChoice;
				}
				if (isTimeSlotFree(timeChoice))
				{ // time slot is free to book
					cout << endl
						 << endl;
					partition();
					cout << endl
						 << endl
						 << "Date : " << inputDate.displayDate() << endl
						 << "Time : ";
					inputDate.displayTimeSlot(timeChoice);
					cout << endl
						 << endl
						 << "Do you wish to confirm this booking?\n"
						 << "   1 - Yes\n"
						 << "   2 - No, take me back to home menu\n\n"
						 << "Enter your choice here > ";
					int finalBookChoice;
					cin >> finalBookChoice;
					while (!cin)
					{
						cout << "Not a valid option, please pick from the previous time-slots." << endl;
						cin.clear();  // clear the error
						cin.ignore(); // ignore the non integer inputted
						cin >> finalBookChoice;
					}
					while ((finalBookChoice < 1) || (finalBookChoice > 2))
					{
						cout << endl
							 << "Not a valid choice, please pick from the previous options." << endl;
						cin.clear();  // clear the error
						cin.ignore(); // ignore the previously inputted string
						cin >> finalBookChoice;
					}
					switch (finalBookChoice)
					{
					case 1:
					{
						cout << endl
							 << endl;
						partition();
						cout << endl
							 << endl;
						centreText("Booking successful.\n");
						cout << "Your " << loggedInLearner[0].getTransmission() << " lesson booking details are as follows :\n"
							 << "   Date: " << inputDate.displayDate() << endl
							 << "   Time: ";
						inputDate.setTimeSlot(timeChoice);
						inputDate.getTimeSlot();
						cout << endl
							 << endl
							 << "   Instructor: " << loggedInLearner[0].getInstructor().getFirstName() << " " << loggedInLearner[0].getInstructor().getLastName() << endl
							 << "   Car details: " << loggedInLearner[0].getInstructor().getCar().getCarMake() << " " << loggedInLearner[0].getInstructor().getCar().getCarModel() << endl
							 << "   Registration: " << loggedInLearner[0].getInstructor().getCar().getCarReg() << "\n\n\n";
						partition();
						cout << endl
							 << endl;
						centreText("Please aim to arrive at the facility 15 mins before your allotted time for your lesson, so as to");
						centreText("make full use of your lesson time.\n\n");
						partition();
						chrono::seconds delay(consoleDelay);
						this_thread::sleep_for(delay);
						int newHours = loggedInLearner[0].getPackageHours() - 2;
						loggedInLearner[0].setPackageHours(newHours);
						updatePackageHours(loggedInLearner[0].getMemberID(), newHours);
						int id = loadLessons().size() + 1;
						saveLessonDetails(id, loggedInLearner[0].getInstructor(), loggedInLearner[0], inputDate, loggedInLearner[0].getTransmission(), "Booked", "");
						break;
					}
					case 2:
					{
						cout << endl
							 << endl;
						partition();
						cout << endl
							 << endl;
						centreText("Booking cancelled.\n");
						break;
					}
					}
				}
				else
				{ // timeslot is not free
					partition();
					cout << endl
						 << endl;
					centreText("This slot is currently unavailable due to your instructor teaching another student at this time.\n");
					cout << "Date: " << inputDate.displayDate() << endl
						 << "Time: ";
					inputDate.displayTimeSlot(timeChoice);
					cout << endl
						 << endl
						 << "Do you wish to rebook?\n"
						 << "  1 - Yes\n"
						 << "  2 - No\n\n"
						 << "Enter your choice here > ";
					int rebookChoice;
					cin >> rebookChoice;
					while (!cin)
					{
						cout << "Not a valid choice, please pick from the previous options." << endl;
						cin.clear();  // clear the error
						cin.ignore(); // ignore the non integer inputted
						cin >> rebookChoice;
					}
					while ((rebookChoice < 1) || (rebookChoice > 2))
					{
						cout << endl
							 << "Not a valid choice, please pick from the previous options." << endl;
						cin.clear();  // clear the error
						cin.ignore(); // ignore the previously inputted string
						cin >> rebookChoice;
					}
					switch (rebookChoice)
					{
					case 1:
					{
						bookLesson();
						break;
					}
					case 2:
					{
						cout << endl
							 << endl;
						partition();
						cout << endl;
						break;
					}
					}
				}
			}
			else
			{ // instructor is unavailable on the day
				cout << endl
					 << endl
					 << "Your instructor " << loggedInLearner[0].getInstructor().getFirstName() << " " << loggedInLearner[0].getInstructor().getLastName() << " is unavailable on this day.\n\n"
					 << "Do you wish to rebook?\n"
					 << "  1 - Yes\n"
					 << "  2 - No\n\n"
					 << "Enter your choice here > ";
				int rebookChoice;
				cin >> rebookChoice;
				while (!cin)
				{
					cout << "Not a valid choice, please pick from the previous options." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the non integer inputted
					cin >> rebookChoice;
				}
				while ((rebookChoice < 1) || (rebookChoice > 2))
				{
					cout << endl
						 << "Not a valid choice, please pick from the previous options." << endl;
					cin.clear();  // clear the error
					cin.ignore(); // ignore the previously inputted string
					cin >> rebookChoice;
				}
				switch (rebookChoice)
				{
				case 1:
				{
					bookLesson();
					break;
				}
				case 2:
				{
					cout << endl
						 << endl;
					partition();
					cout << endl;
					break;
				}
				}
			}
		}
	}
}


//Functions to update learner details
void updateFirstNameMember(Member &member) {
	cout << "Enter new first name: ";
	string firstName;
	cin >> firstName;
	if (inputValidation(firstName))
	{
			member.setFirstName(firstName);
			cout << "First name updated successfully." << endl;
	} else
		{
			cout << "First name cannot contain a comma. Please try again." << endl;
		}
}

void updateLastNameMember(Member &member) {
	cout << "Enter new last name: ";
	string lastName;
	cin >> lastName;
	if (inputValidation(lastName))
	{
			member.setLastName(lastName);
			cout << "Last name updated successfully." << endl;
	} else
		{
			cout << "Last name cannot contain a comma. Please try again." << endl;
		}
}

void updateEmailMember(Member &member) {
	cout << "Enter new email: ";
	string email;
	cin >> email;
	
		if (emailValidation(email))
		{
			if (inputValidation(email))
			{
				
					member.setEmail(email);
					cout << "Email updated successfully." << endl;
			}
			else
			{
				cout << "Email cannot contain a comma. Please try again." << endl;
			}
		}
		else
		{
			cout << "Invalid email format. Please try again." << endl;
		}
}

void updateTelephoneMember(Member &member) {
	cout << "Enter new telephone number: ";
	string telephone;
	cin >> telephone;
	if (inputValidation(telephone))
	{
			member.setTelephone(telephone);
			cout << "Telephone number updated successfully." << endl;
	} else
		{
			cout << "Invalid telephone number. Please try again." << endl;
		}
}

void updateTransmissionMember(Member &member) {
	cout << "Enter new car transmission (Automatic or Manual): ";
	string carTransmission;
	cin >> carTransmission;
	if ((carTransmission == "Automatic" || carTransmission == "Manual"))
	{
		member.setTransmission(carTransmission);
		cout << "Car transmission updated successfully." << endl;
	}
	else
	{
		cout << "Car transmission should be Automaic or Manual. Please try again." << endl;
	}
}

void updatePersonalMemberDetails() {

	vector<Member> members = loadRegisteredMembers();
	bool memberFound = false;

	for(Member &m : members)
	{
		if (m.getMemberID() == loggedInLearner[0].getMemberID()) {
			memberFound = true;

			cout << "Please select the field you would like to update: " << endl;
			cout << "1. First Name" << endl;
			cout << "2. Last Name" << endl;
			cout << "3. Email" << endl;
			cout << "4. Telephone" << endl;
			cout << "5. Transmission" << endl;

			int choice;
			cin >> choice;

			switch(choice)
			{
				case 1:
					updateFirstNameMember(m);
					break;
				case 2:
					updateLastNameMember(m);
					break;
				case 3:
					updateEmailMember(m);
					break;
				case 4:
					updateTelephoneMember(m);
					break;
				case 5:
					updateTransmissionMember(m);
					break;
				default:
					cout << "Invalid choice. Please try again." << endl;
					break;
			}

			updateMemberCSV(members);
			cout << "Details updated successfully." << endl;
			break;
		}
	}

	if(!memberFound)
	{
		cout << "Member not found." << endl;
	}
}

void signOut()
{
	loggedInLearner.clear();	// Clear the vector of logged-in learners
	loggedInInstructor.clear(); // Clear the vector of logged-in learners
	cout << endl
		 << endl;
	partition();
	cout << endl
		 << endl;
	centreText("You have successfully signed out. Goodbye!\n");
	partition();
	chrono::seconds delay(consoleDelay);
	this_thread::sleep_for(delay);
	newScreen();
	startUpMenu(); // return to the login screen
}

void viewLessonsMember(std::vector<Lesson> lessons, int loggedInMemberID)
{
	cout << setw(10) << "Lesson ID" << setw(15) << "Date" << setw(15) << "Lesson Type" << setw(15) << "Status" << setw(15) << "Note" << setw(15) << "Instructor ID" << setw(15) << "Learner ID" << endl;
	for (Lesson lesson : lessons)
	{
		// Check if the lesson involves the logged-in member
		if (lesson.getLearnerID() == loggedInMemberID)
		{
			cout << setw(10) << lesson.getLessonID() << setw(15) << lesson.getLessonDate().displayDate() << setw(15) << lesson.getLessonType() << setw(15) << lesson.getLessonStatus() << setw(15) << lesson.getLessonNote() << setw(15) << lesson.getInstructorID() << setw(15) << lesson.getLearnerID() << endl;
		}
	}
}
void viewLessonsInstructor(vector<Lesson> lessons, int loggedInInstructorID){
  	cout << setw(10) << "Lesson ID" << setw(15) << "Date" << setw(15) << "Lesson Type" << setw(15) << "Status" << setw(15) << "Note" << setw(15) << "Instructor ID" << setw(15) << "Learner ID" << endl;
	for (Lesson lesson : lessons)
	{
		// Check if the lesson involves the logged-in member
		if (lesson.getInstructorID() == loggedInInstructorID)
		{
			cout << setw(10) << lesson.getLessonID() << setw(15) << lesson.getLessonDate().displayDate() << setw(15) << lesson.getLessonType() << setw(15) << lesson.getLessonStatus() << setw(15) << lesson.getLessonNote() << setw(15) << lesson.getInstructorID() << setw(15) << lesson.getLearnerID() << endl;
		}
	}
}

void displayInstructors(string transmission)
{
	vector<Instructor> instructors;
	for (Instructor instruc : loadRegisteredInstructors())
	{
		if (transmission == instruc.getCar().getCarTransmission())
		{
			instructors.emplace_back(instruc);
		}
	}
	cout << "-------------------\n\n";
	for (Instructor instructor : instructors)
	{
		vector<string> daysAvailStr;
		for (string day : loggedInLearner[0].getInstructor().getDaysAvailable())
		{
			string availability;
			if ((day == "1") || (day == "1\r"))
			{
				availability = "Available";
			}
			else if ((day == "0") || (day == "0\r"))
			{
				availability = "Off";
			}
			daysAvailStr.emplace_back(availability);
		}
		cout << " ID: " << instructor.getInstructorID() << endl
			 << " Name: " << instructor.getFirstName() << " " << instructor.getLastName() << endl
			 << " Email: " << instructor.getEmail() << endl
			 << " Car: " << instructor.getCar().getCarMake() << " " << instructor.getCar().getCarModel() << endl
			 << " Weekly Schedule:" << endl
			 << " Monday - " << daysAvailStr[2] << "  |  " << " Tuesday - " << daysAvailStr[3] << "  |  " << " Wednesday - " << daysAvailStr[4] << "  |  " << " Thursday - " << daysAvailStr[5] << "  |  " << " Friday - " << daysAvailStr[6] << "  |  " << " Saturday - " << daysAvailStr[0] << "  |  " << " Sunday - " << daysAvailStr[1] << endl
			 << endl
			 << "-------------------\n\n";
	}
}


void updateLearnerTransmission(int memberID, string newTrans){
  ifstream file("members.csv"); // Open CSV file for reading
    string header;
    getline(file, header);
    vector<string> lines; // Vector to store lines from CSV file
    // Read each line from the CSV file and store it in the vector
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close(); // Close the file
    ofstream outfile("members.csv");
    // Write the header line back to the file
    outfile << header << endl;
    for (string line : lines) {
      stringstream ss(line);
      string token;
      getline(ss, token, ','); // memberID
      if (stoi(token) == memberID){ // Check if it's the specified member
	int commaCount = 0;
	int lastCommaIndex, secondToLastCommaIndex, thirdToLastCommaIndex;
	lastCommaIndex = line.find_last_of(',');
	for (int i = line.size() - 1; i >= 0; --i) {
	  if (line[i] == ',') {
            ++commaCount;
            if (commaCount == 2) {
	      secondToLastCommaIndex = i;
            } else if (commaCount == 3){
	      thirdToLastCommaIndex = i;
	      break;
	    }
	  }
	}
	int length = lastCommaIndex - secondToLastCommaIndex;
	int instrucID = stoi(line.substr(secondToLastCommaIndex + 1, length - 1));
	for (int i = 0; i < 5; ++i) getline(ss, token, ','); // Skip the first 5 fields
	outfile << line.substr(0, thirdToLastCommaIndex + 1) << newTrans << "," << instrucID << "," << 0 << endl;
	} else {
           outfile << line << endl; //unchanged line to file
        }
    }
    outfile.close();
}
void updateInstructorAvailability(int instrucID, vector<string> daysAvail){
   ifstream file("instructors.csv"); // Open CSV file for reading
    string header;
    getline(file, header);
    vector<string> lines; // Vector to store lines from CSV file
    // Read each line from the CSV file and store it in the vector
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close(); // Close the file
    ofstream outfile("instructors.csv");
    // Write the header line back to the file
    outfile << header << endl;
    for (string line : lines) {
        stringstream ss(line);
        string token;
        getline(ss, token, ','); // instrucID
        if (stoi(token) == instrucID){ // Check if it's the specified instruc
            // Update packageHours
	  int commaCount = 0;
	  int commaIndex;
	  for (int i = line.size() - 1; i >= 0; --i) {
	    if (line[i] == ',') {
	      ++commaCount;
	      if (commaCount == 7) {
	        commaIndex = i;
		break;
	      }
	    }
	  }
            for (int i = 0; i < 9; ++i) getline(ss, token, ','); // Skip the first 9 fields
            outfile << line.substr(0, commaIndex + 1) << daysAvail[0] << "," << daysAvail[1] << "," << daysAvail[2] << "," << daysAvail[3] << "," << daysAvail[4] << "," << daysAvail[5] << "," << daysAvail[6] << endl;
        } else {
            outfile << line << endl; //unchanged line to file
        }
    }
    outfile.close(); // Close the file
}

void updateDaysAvailChoice(){
      cout << endl << endl;
      partition();
      cout << endl << endl <<
	" Which day do you wish to update the availability of?\n" <<
	"     1 - Monday\n" <<
	"     2 - Tuesday\n" <<
	"     3 - Wednesday\n" <<
	"     4 - Thursday\n" <<
	"     5 - Friday\n" <<
	"     6 - Saturday\n" <<
	"     7 - Sunday\n" << endl <<
	"Enter your choice here > ";
      int dayChoice;
      cin >> dayChoice;
      while (!cin)
	{
	  cout << "Not a valid option, please pick from the previous actions." << endl;
	  cin.clear();  // clear the error
	  cin.ignore(); // ignore the non integer inputted
	  cin >> dayChoice;

	}
      while ((dayChoice < 1) || (dayChoice > 7))
	{
	  cout << endl
	       << "Not a valid choice, please pick from the previous options." << endl;
	  cin.clear();  // clear the error
	  cin.ignore(); // ignore the previously inputted string
	  cin >> dayChoice;
	}
      cout << endl << endl;
      vector<string> daysAvailStr;
      for (string day : loggedInInstructor[0].getDaysAvailable()){
	string availability;
	if ((day == "1") || (day == "1\r")){
	  availability = "Available";
	} else if ((day == "0") || (day == "0\r")){
	  availability = "Off";
	}
	daysAvailStr.emplace_back(availability);
      }
      vector<string> ogDaysAvail = loggedInInstructor[0].getDaysAvailable();
      switch(dayChoice){
      case 1:{
	centreText("You are currently " + daysAvailStr[2] + " on Mondays.");
	if(loggedInInstructor[0].getDaysAvailable()[2] == "1"){
	  ogDaysAvail[2] = "0";
	  centreText("You have now been updated as unavailable on Mondays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[2] == "0"){
	  ogDaysAvail[2] = "1";
	  centreText("You have now been updated as available on Mondays.\n");
	}
	break;}
      case 2:{
	centreText("You are currently " + daysAvailStr[3] + " on Tuesdays.");
	if(loggedInInstructor[0].getDaysAvailable()[3] == "1"){
	  ogDaysAvail[3] = "0";
	  centreText("You have now been updated as unavailable on Tuesdays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[3] == "0"){
	  ogDaysAvail[3] = "1";
	  centreText("You have now been updated as available on Tuesdays.\n");
	}
	break;}
      case 3:{
	centreText("You are currently " + daysAvailStr[4] + " on Wednesdays.");
	if(loggedInInstructor[0].getDaysAvailable()[4] == "1"){
	  ogDaysAvail[4] = "0";
	  centreText("You have now been updated as unavailable on Wednesdays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[4] == "0"){
	  ogDaysAvail[4] = "1";
	  centreText("You have now been updated as available on Wednesdays.\n");
	}
	break;}
      case 4:{
	centreText("You are currently " + daysAvailStr[5] + " on Thursdays.");
	if(loggedInInstructor[0].getDaysAvailable()[5] == "1"){
	  ogDaysAvail[5] = "0";
	  centreText("You have now been updated as unavailable on Thursdays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[5] == "0"){
	  ogDaysAvail[5] = "1";
	  centreText("You have now been updated as available on Thursdays.\n");
	}
	break;}
      case 5:{
	centreText("You are currently " + daysAvailStr[6] + " on Fridays.");
	if((loggedInInstructor[0].getDaysAvailable()[6] == "1") || (loggedInInstructor[0].getDaysAvailable()[6] == "1\r")){
	  ogDaysAvail[6] = "0";
	  centreText("You have now been updated as unavailable on Fridays.\n");
	} else if ((loggedInInstructor[0].getDaysAvailable()[6] == "0") || (loggedInInstructor[0].getDaysAvailable()[6] == "0\r")){
	  ogDaysAvail[6] = "1";
	  centreText("You have now been updated as available on Fridays.\n");
	}
	break;}
      case 6:{
	centreText("You are currently " + daysAvailStr[0] + " on Saturdays.");
	if(loggedInInstructor[0].getDaysAvailable()[0] == "1"){
	  ogDaysAvail[0] = "0";
	  centreText("You have now been updated as unavailable on Saturdays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[0] == "0"){
	  ogDaysAvail[0] = "1";
	  centreText("You have now been updated as available on Saturdays.\n");
	}
	break;}
      case 7:{
	centreText("You are currently " + daysAvailStr[1] + " on Sundays.");
	if(loggedInInstructor[0].getDaysAvailable()[1] == "1"){
	  ogDaysAvail[1] = "0";
	  centreText("You have now been updated as unavailable on Sundays.\n");
	} else if (loggedInInstructor[0].getDaysAvailable()[1] == "0"){
	  ogDaysAvail[1] = "1";
	  centreText("You have now been updated as available on Sundays.\n");
	}
	break;}
      }
      loggedInInstructor[0].setDaysAvailable(ogDaysAvail);
      updateInstructorAvailability(loggedInInstructor[0].getInstructorID(), ogDaysAvail);
      vector<string> daysAvailStr2;
      for (string day : loggedInInstructor[0].getDaysAvailable()){
	string availability;
	if ((day == "1") || (day == "1\r")){
	  availability = "Available";
	} else if ((day == "0") || (day == "0\r")){
	  availability = "Off";
	}
	daysAvailStr2.emplace_back(availability);
      }
      cout <<
	"Your new weekly schedule is as follows:\n" << endl <<
	"     Monday - " << daysAvailStr2[2] << endl <<
	"     Tuesday - " << daysAvailStr2[3] << endl <<
	"     Wednesday - " << daysAvailStr2[4] << endl <<
	"     Thursday - " << daysAvailStr2[5] << endl <<
	"     Friday - " << daysAvailStr2[6] << endl <<
	"     Saturday - " << daysAvailStr2[0] << endl <<
	"     Sunday - " << daysAvailStr2[1] << endl << endl <<
	"Do you wish to make another change to your availability?\n" <<
	"    1 - Yes\n" <<
	"    2 - No\n\n" <<
	"Enter your choice here > ";
      int pickChoice;
      cin >> pickChoice;
      while (!cin)
	{
	  cout << "Not a valid option, please pick from the previous actions." << endl;
	  cin.clear();  // clear the error
	  cin.ignore(); // ignore the non integer inputted
	  cin >> pickChoice;

	}
      while ((pickChoice < 1) || (pickChoice > 2))
	{
	  cout << endl
	       << "Not a valid choice, please pick from the previous options." << endl;
	  cin.clear();  // clear the error
	  cin.ignore(); // ignore the previously inputted string
	  cin >> pickChoice;
	}
      switch(pickChoice){
      case 1:{
	updateDaysAvailChoice();
	break;}
      case 2:{
	cout << endl << endl;
	break;}
      }
}

void updateMemberPassword(int memberID, string newPass){
   ifstream file("members.csv"); // Open CSV file for reading
    string header;
    getline(file, header);
    vector<string> lines; // Vector to store lines from CSV file
    // Read each line from the CSV file and store it in the vector
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close(); // Close the file
    ofstream outfile("members.csv");
    // Write the header line back to the file
    outfile << header << endl;
    for (string line : lines) {
      stringstream ss(line);
      string token;
      getline(ss, token, ','); // memberID
      if (stoi(token) == memberID){ // Check if it's the specified member
	int commaCount = 0;
	int fourthToLastCommaIndex;
	for (int i = line.size() - 1; i >= 0; --i) {
	  if (line[i] == ',') {
            ++commaCount;
            if (commaCount == 4) {
	      fourthToLastCommaIndex = i;
	      break;
	    }
	  }
	}
	for (int i = 0; i < 4; ++i) getline(ss, token, ','); // Skip the first 4 fields
	outfile << line.substr(0, fourthToLastCommaIndex + 1) << newPass << "," << loggedInLearner[0].getTransmission() << "," << loggedInLearner[0].getInstructor().getInstructorID() << "," << loggedInLearner[0].getPackageHours() << endl;
	} else {
           outfile << line << endl; //unchanged line to file
        }
    }
    outfile.close();
}

void cancelLesson(int lessonID, string cancelReason){
  ifstream file("lessons.csv"); // Open CSV file for reading
    string header;
    getline(file, header);
    vector<string> lines; // Vector to store lines from CSV file
    // Read each line from the CSV file and store it in the vector
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close(); // Close the file
    ofstream outfile("lessons.csv");
    // Write the header line back to the file
    outfile << header << endl;
    for (string line : lines) {
      stringstream ss(line);
      string token;
      getline(ss, token, ','); // lessonID
      if (stoi(token) == lessonID){ // Check if it's the specified lesson
	int commaCount = 0;
	int secondToLastCommaIndex;
	for (int i = line.size() - 1; i >= 0; --i) {
	  if (line[i] == ',') {
            ++commaCount;
            if (commaCount == 2) {
	      secondToLastCommaIndex = i;
	      break;
	    }
	  }
	}
	for (int i = 0; i < 4; ++i) getline(ss, token, ','); // Skip the first 4 fields
	outfile << line.substr(0, secondToLastCommaIndex + 1) << "Cancelled" << ",\"" << cancelReason << "\"" << endl;
	} else {
           outfile << line << endl; //unchanged line to file
        }
    }
    outfile.close();
}



void learnerHomePage()
{
  vector<Lesson> lessons = loadLessons();
  partition();
  cout << endl;
  centreText("Learner Home");
  cout << endl;
  centreText("Welcome " + loggedInLearner[0].getFirstName() + " " + loggedInLearner[0].getLastName() + "!");
  partition();
  cout << endl << endl << endl <<
    "  Please choose from the actions below: \n" <<
    "     1 - Buy lesson course\n" <<
    "     2 - Book lesson\n" <<
    "     3 - View my lessons\n" <<
    "     4 - Cancel lesson\n" <<
    "     5 - Refund hours\n" <<
    "     6 - Change my instructor\n" <<
    "     7 - Change lesson type\n" <<
    "     8 - Update my personal details\n" <<
    "     9 - Change password\n" <<
    "    10 - Sign out\n\n";
  cout << "Enter choice here > ";
  int homeChoice;
  cin >> homeChoice;
  while (!cin)
    {
      cout << "Not a valid option, please pick from the previous actions." << endl;
      cin.clear();  // clear the error
      cin.ignore(); // ignore the non integer inputted
      cin >> homeChoice;

    }
  while ((homeChoice < 1) || (homeChoice > 10))
    {
      cout << endl
	   << "Not a valid choice, please pick from the previous options." << endl;
      cin.clear();  // clear the error
      cin.ignore(); // ignore the previously inputted string
      cin >> homeChoice;
    }
  switch (homeChoice)
    {
    case 1:{
      cout << endl << endl;
      partition();
      if(loggedInLearner[0].getInstructor().getInstructorID() != 0){ //the learner is assigned an instructor
	if(loggedInLearner[0].getPackageHours() == 0){
	  cout << endl;
	  centreText("Driving course Shop:\n");
	  centreText("FYI: One lesson is two hours long and we expect payment for the package before booking lessons.");
	  centreText("Any unused hours will be refunded at our standard refund rate of £40 per lesson (2 hours) should you choose to refund your hours.");
	  cout << endl << endl;
	  partition();
	  int singleLessonPrice,  standardTotal, standardSingle, halfTotal, halfSingle, fullTotal, fullSingle, refresherTotal, refresherSingle;
	  if (loggedInLearner[0].getTransmission() == "Manual"){
	    singleLessonPrice = 60; //manual rrate
	  } else {
	    singleLessonPrice = 80; //automatic rate
	  }
	  standardSingle = singleLessonPrice * 1.2;
	  standardTotal = standardSingle * 20;
	  halfSingle = singleLessonPrice * 1.4;
	  halfTotal = halfSingle * 10;
	  fullSingle = singleLessonPrice;
	  fullTotal = singleLessonPrice * 30;
	  refresherSingle = singleLessonPrice * 1.6;
	  refresherTotal = refresherSingle * 5;
    
	  cout << endl << endl << endl <<
	    "     Please pick from the following packages:\n" <<
	    "        1 - Standard course ( 40 hours )\n" <<
	    "            Total cost:        Price per lesson:\n" <<
	    "            £" << standardTotal << "              £" << standardSingle << "\n" <<
	    "        2 - Half course ( 20 hours )\n"
	    "            Total cost:        Price per lesson:\n" <<
	    "            £" << halfTotal << "              £" << halfSingle << "\n" <<
	    "        3 - Full course ( 60 hours )\n" <<
	    "            Total cost:        Price per lesson:\n" <<
	    "            £" << fullTotal << "              £" << fullSingle << "\n" <<
	    "        4 - Refresher course ( 10 hours )\n"
	    "            Total cost:        Price per lesson:\n" <<
	    "            £" << refresherTotal << "               £" << refresherSingle << "\n" <<
	    endl;
	  cout << "Enter your package here > ";
	  int packageChoice;
	  cin >> packageChoice;
	  while (!cin)
	    {
	      cout << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the non integer inputted
	      cin >> packageChoice;

	    }
	  while ((packageChoice < 1) || (packageChoice > 4))
	    {
	      cout << endl
		   << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the previously inputted string
	      cin >> packageChoice;
	    }
	  int hours;
	  int price;
	  switch (packageChoice)
	    {
	    case 1:{
	      hours = 40;
	      price = standardTotal;
		
	      break;}
	    case 2:{
	      hours = 20;
	      price = halfTotal;
		
	      break;}
	    case 3:{
	      hours = 60;
	      price = fullTotal;
		
	      break;}
	    case 4:{
	      hours = 10;
	      price = refresherTotal;
		
	      break;}
	    }
	  cout << endl << endl;
	  partition();
	  cout << endl << endl;
	  centreText("Cart:");
	  cout<< endl;
	  centreText("Please review the following details then proceed to pay.");
	  cout << endl << endl <<
	    "Package chosen:\n" <<
	    "  Total hours: " << hours << " hours\n" <<
	    "  Price per lesson: £" << price/(hours/2) << "\n" <<
	    "  Total Price: £" << price << "\n\n";
	  cout << "Do you wish to buy the chosen package?\n" <<
	    "   1 - Yes\n" <<
	    "   2 - No, return to home menu\n" <<
	    "Enter choice here > ";
	  int buyChoice;
	  cin >> buyChoice;
	  while (!cin)
	    {
	      cout << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the non integer inputted
	      cin >> buyChoice;

	    }
	  while ((buyChoice < 1) || (buyChoice > 2))
	    {
	      cout << endl
		   << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the previously inputted string
	      cin >> buyChoice;
	    }
	  switch (buyChoice){
	  case 1:
		{
	      //set the packagehours and sort payment for the user (fake one ofcourse)
	      cout << endl << endl;
	      partition();
	      cout << endl << endl;
	      string priceStr, hoursStr;
	      priceStr = to_string(price);
	      hoursStr = to_string(hours);
	      centreText("Payment of £" + priceStr + " confirmed. You have purchased " + hoursStr + " hours of driving lessons.");
	      centreText("You can now book lessons from the home menu.\n");
	      loggedInLearner[0].setPackageHours(hours);
	      updatePackageHours(loggedInLearner[0].getMemberID(), hours);
	      partition();
	      break;
	    }
	  case 2:
	    {
	      cout << endl << endl;
	      centreText("Cart abandoned, purchase cancelled...");
	      partition();
	      break;
	    }

	  }
	} else {
	  cout << endl << endl;
	  string hoursStr = to_string(loggedInLearner[0].getPackageHours());
	  centreText("You currently have " + hoursStr + " hours left as apart of your purchased package.\n");
	  centreText("You can choose to book more lessons, or choose to refund these hours at a rate of £40 a lesson.");
	  centreText("Both options can be found on your home menu.");
	  cout << endl << endl;
	  partition();
	}
      } else { // the learner doesnt have an instructor assigned to them
	cout << endl << endl;
	centreText("You currently don't have a driving instructor assigned to yourself.");
	centreText("Please return to the home menu and pick the 'Change my instructor' to choose one");
      }
		cout << endl;
		centreText("Returning to home menu...\n");
		partition();
		chrono::seconds delay(consoleDelay);
		this_thread::sleep_for(delay);
		newScreen();
		learnerHomePage();
		break;
		}
		case 2:
		{//book lesson
		cout << endl << endl;
		partition();
		cout << endl << endl;
		bookLesson();
		cout << endl;
		centreText("Returning to home menu...\n");
		partition();
		chrono::seconds delay(consoleDelay);
		this_thread::sleep_for(delay);
		newScreen();
		learnerHomePage();
      break;}
    case 3:{ //view my lessons
		cout << endl;
		partition();
		cout << endl;
		viewLessonsMember(lessons, loggedInLearner[0].getMemberID());
		cout << endl;
		centreText("Returning to home menu...\n");
		partition();
		chrono::seconds delay(consoleDelay);
		this_thread::sleep_for(delay);
		newScreen();
		learnerHomePage();
		break;     
    }
    case 4: //cancel lesson
      {
	 //Cancel Lesson
	int lessonID;
	string cancellationReason = "";
	cout << endl << endl;
	partition();
	cout << endl << endl;
	centreText("Cancel a lesson:\n");
	centreText("FYI: Should you cancel your booking within 2 days of the lesson, you will not be refunded your hours.\n");
	bool hasLesson = false;
	for (Lesson lesson : loadLessons()){
	  if (lesson.getLearnerID() == loggedInLearner[0].getMemberID()){
	    hasLesson = true;
	    break;
	  }
	}
	if(hasLesson){ // has at least one lesson booked to cancel.
	  cout <<
	    "Enter the lesson ID of the lesson you wish to cancel:\n\n";
	  bool idMatch = false;
	  Date date;
	  Lesson chosenLesson(0,date,"","","",0,0);
	  while(!idMatch){
	    cout << "Enter ID here > ";
	    cin >> lessonID;
	    if (!cin) {
	      cout << "Not a valid ID. Please enter a valid lesson ID." << endl;
	      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
	      cin.clear();  // clear the error
	      
	      continue; 
	    }
	    for(Lesson lesson : loadLessons()){
	      if (lesson.getLessonID() == lessonID && 
		  lesson.getLearnerID() == loggedInLearner[0].getMemberID() && lesson.getLessonStatus() == "Booked") {
		idMatch = true;
		chosenLesson = lesson;
		break;
	      }
	    }
	    if(!idMatch){
	      cout << endl <<
		"No lesson assigned to you with ID " << to_string(lessonID) << " found. Please choose a lesson that is currently booked.\nFor information on the specific ID of the lesson you should consult the view my lessons option in the home menu." << endl;
	    }
	  }
	  cout << endl << endl <<
	    "You must provide reason for cancelling a lesson.";
	  while(!inputValidation(cancellationReason) || cancellationReason.empty()){
	     cout << endl <<
	    "Enter your reason for cancelling your lesson:\n";
	     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	     std::cin.clear();
	     getline(cin, cancellationReason);
	     if(!inputValidation(cancellationReason) || cancellationReason.empty()){
	       cout << "You must include a reason for your cancellation. You also cannot have special character ',' in your input.\n";
	       cin.clear();
	       cin.ignore();
	       cout << endl <<
		  "Enter your reason for cancelling your lesson:\n ";
	       getline(cin, cancellationReason);
	     }
	     
	     continue;
	  }
	  cout <<  endl << endl <<
	    "You have chosen to cancel the following booking:\n" <<
	    "Date: " << chosenLesson.getLessonDate().displayDate() << endl <<
	    "Time: ";
	  chosenLesson.getLessonDate().displayTimeSlot(chosenLesson.getLessonDate().getTimeSlot());
	  cout << endl <<
	    "Reason for cancelling: " << cancellationReason << ".\n\n" <<
	    "Do you wish to finalise changes?\n" <<
	    "   1 - Yes, cancel the lesson.\n" <<
	    "   2 - No, keep the lesson\n\n" <<
	    "Enter choice here > ";
	  int finalCancelChoice;
	  cin >> finalCancelChoice;
	  while (!cin)
	    {
	      cout << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the non integer inputted
	      cin >> finalCancelChoice;

	    }
	  while ((finalCancelChoice < 1) || (finalCancelChoice > 2))
	    {
	      cout << endl
		   << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the previously inputted string
	      cin >> finalCancelChoice;
	    }
	  switch (finalCancelChoice){
	  case 1:{
	    Date today;
	    if ((chosenLesson.getLessonDate().getDay() - today.getDay()) <= 2){ //will not get a refund
	      cout << endl << endl;
	      centreText("Selected lesson has been cancelled and lesson hours will not be refunded as you cancelled within 2 days of the lesson.\n");
	      cancelLesson(lessonID, cancellationReason);
	      updatePackageHours(loggedInLearner[0].getMemberID() , loggedInLearner[0].getPackageHours()); 
	    }else{ //will get a refund
	      cout << endl << endl;
	      centreText("Selected lesson has been cancelled and lesson hours have been refunded to you.\n");
	      cancelLesson(lessonID, cancellationReason);
	      loggedInLearner[0].setPackageHours( loggedInLearner[0].getPackageHours() + 2);
	      updatePackageHours(loggedInLearner[0].getMemberID() , loggedInLearner[0].getPackageHours()); // give back 2 hours to the member
	    }
	    break;}
	  case 2:{
	    cout << endl << endl;
	    centreText("Cancellation of chosen lesson dropped. No changes made.\n");
	    break;}
	  }
	} else { // has no lessons booked to cancel
	  cout << endl << endl;
	  centreText("You currently have no lessons booked that you could cancel.\n");
	  cout << endl;
	}
	cout << endl;
	centreText("Returning to home menu...\n");
	partition();
	chrono::seconds delay(consoleDelay);
	this_thread::sleep_for(delay);
	newScreen();
	learnerHomePage();
	break;
      }
    case 5:{ // refund hours
      cout << endl << endl;
      partition();
      cout << endl << endl;
      if (loggedInLearner[0].getPackageHours() == 0){
	centreText("You currently have no lesson hours to refund.");
	centreText("You can return to the home menu to purchase a lesson package which will");
	centreText("enable you to book driving lessons for your chosen dates and times.");
      } else {
	centreText("Refund lesson hours\n");
	partition();
	cout << endl << endl;
	string hoursStr = to_string(loggedInLearner[0].getPackageHours());
	int refund = (loggedInLearner[0].getPackageHours() / 2) * 40;
	centreText("You currently have " + hoursStr + " hours left on your package.\n");
	centreText("You have chosen to refund your remaining lesson hours for the base rate of");
	centreText("£40 a lesson (2 hours) to the payment card that was used to purchase your previous package.\n");
	cout << "Do you wish to refund your remaining hours for a total of £" << to_string(refund) << "?\n" <<
	  "WARNING: THIS ACTION CANNOT BE REVERSED AND WILL RESULT IN YOU TRADING YOUR REMAINING LESSON HOURS.\n\n" <<
	  "   1 - Yes, I want to trade my " << hoursStr << " hours of lessons for the sum of £" << to_string(refund) << ".\n" <<
	  "   2 - No, I wish to keep my hours.\n" << endl;
	cout << "Enter your choice here > ";
	int refundChoice;
	cin >> refundChoice;
	while (!cin)
	  {
	    cout << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the non integer inputted
	    cin >> refundChoice;

	  }
	while ((refundChoice < 1) || (refundChoice > 2))
	  {
	    cout << endl << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the previously inputted string
	    cin >> refundChoice;
	  }
	switch(refundChoice){
	case 1:{
	  cout << endl << endl;
	  partition();
	  cout << endl;
	  centreText("Refund processing...\n");
	  partition();
	  chrono::seconds delay(consoleDelay);
	  this_thread::sleep_for(delay);
	  cout << endl << endl;
	  centreText("Your refund for the amount of £" + to_string(refund) + " has been accepted.");
	  centreText("Please expect the transaction to show in 1-3 business days.");
	  loggedInLearner[0].setPackageHours(0);
	  updatePackageHours(loggedInLearner[0].getMemberID(), 0);
	  break;}
	case 2:{
	  cout << endl << endl;
	  partition();
	  cout << endl;
	  centreText("Refund cancelled. You still have " + hoursStr + " hours remaining on your package.\n");
	  break;}
	}

      }
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      learnerHomePage();
      break;
	}
    case 6:{ //change instructor 
      cout << endl << endl;
      partition();
      cout << endl << endl;
      centreText("Driver Change\n");
      centreText("As our valued student you have no obligation to stay with a specific instructor");
      centreText("and you may change your instructor at any time.\n");
      centreText("FYI: Please understand you are still expected to attend your booked lessons with the instructor");
      centreText("that are teaching any of your booked lessons should you change your instructor.\n");
      cout << endl << endl;
      bool wantToChange = false;
      centreText("Current Instructor details:\n");
      if(loggedInLearner[0].getInstructor().getInstructorID() == 0){ //if student doesnt have an assigned teacher
	wantToChange = true;
	cout << endl;
	centreText("You currently have no instructor assigned to yourself.\n\n");
      } else { // if the student has one already
	vector<string> daysAvailStr;
	for (string day : loggedInLearner[0].getInstructor().getDaysAvailable()){
	  string availability;
	  if ((day == "1") || (day == "1\r")){
	    availability = "Available";
	  } else if ((day == "0") || (day == "0\r")){
	    availability = "Off";
	  }
	  daysAvailStr.emplace_back(availability);
	}
	cout << endl <<
	  "  Name: " << loggedInLearner[0].getInstructor().getFirstName() << " " << loggedInLearner[0].getInstructor().getLastName() << endl <<
	  "  Email: " << loggedInLearner[0].getInstructor().getEmail() << endl <<
	  "  Telephone: " << loggedInLearner[0].getInstructor().getTelephone() << endl  << endl <<
	  "  Car details: " << endl <<
	  "  Make and Model: " << loggedInLearner[0].getInstructor().getCar().getCarMake() << " " << loggedInLearner[0].getInstructor().getCar().getCarModel() << endl <<
	  "  Registration: " << loggedInLearner[0].getInstructor().getCar().getCarReg() << endl << endl <<
	  "  Weekly Schedule:" << endl <<
	  "     Monday - " << daysAvailStr[2] << endl <<
	  "     Tuesday - " << daysAvailStr[3] << endl <<
	  "     Wednesday - " << daysAvailStr[4] << endl <<
	  "     Thursday - " << daysAvailStr[5] << endl <<
	  "     Friday - " << daysAvailStr[6] << endl <<
	  "     Saturday - " << daysAvailStr[0] << endl <<
	  "     Sunday - " << daysAvailStr[1] << endl << endl <<
	  "Do you still wish to change your instructor for all future lessons?" << endl <<
	  "    1 - Yes\n" <<
	  "    2 - No\n" <<
	  "Enter your choice here > ";
	int changeChoice;
	cin >> changeChoice;
	while (!cin)
	  {
	    cout << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the non integer inputted
	    cin >> changeChoice;

	  }
	while ((changeChoice < 1) || (changeChoice > 2))
	  {
	    cout << endl
		 << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the previously inputted string
	    cin >> changeChoice;
	  }
	switch (changeChoice){
	case 1:{ //wish to change instructor
	  wantToChange = true;
	  break;}
	case 2:{ //wish to keep
	  cout << endl << endl << endl;
	  break;}
	}
      }
      if(wantToChange){
	//Display all instructors that teach the type of lesson that the learner needs (manual or auto)
	centreText("Please browse from the list below and choose an instructor that");
	centreText("you wish to have teach you on all future lessons.\n\n\n");
	displayInstructors(loggedInLearner[0].getTransmission());
	cout << endl << endl <<
	  "Enter the ID of the instructor that you wish to change to below." << endl << endl;
	int idChoice;
	bool idMatch = false;
	Instructor chosenInstructor;
	while(!idMatch){
	  cout << "Enter ID here > ";
	  cin >> idChoice;
	  if (!cin) {
            cout << "Not a valid ID. Please enter a valid ID from the table above." << endl;
            cin.clear();  // clear the error
            cin.ignore(); // ignore the invalid input
            continue; 
	  }
	  for(Instructor instructor : loadRegisteredInstructors()){
	    if (instructor.getInstructorID() == idChoice && 
                loggedInLearner[0].getTransmission() == instructor.getCar().getCarTransmission()) {
                idMatch = true;
		chosenInstructor = instructor;
                break;
            }
	  }
	  if(!idMatch){
	    cout << endl <<
	      "No instructor found with ID " << to_string(idChoice) << ". Please choose a valid instructor ID." << endl;
	  }
	}
	cout << endl << endl;
	partition();
	cout << endl << endl;
	centreText("You have chosen the following instructor to be your driving instructor:\n");
	vector<string> daysAvailStr2;
	for (string day : chosenInstructor.getDaysAvailable()){
	   string availability;
	  if ((day == "1") || (day == "1\r")){
	    availability = "Available";
	  } else if ((day == "0") || (day == "0\r")){
	    availability = "Off";
	  }
	  daysAvailStr2.emplace_back(availability);
	}
	cout << endl <<
	  "  Name: " << chosenInstructor.getFirstName() << " " << chosenInstructor.getLastName() << endl <<
	  "  Email: " << chosenInstructor.getEmail() << endl <<
	  "  Telephone: " << chosenInstructor.getTelephone() << endl  << endl <<
	  "  Car details: " << endl <<
	  "  Make and Model: " << chosenInstructor.getCar().getCarMake() << " " << chosenInstructor.getCar().getCarModel() << endl <<
	  "  Registration: " << chosenInstructor.getCar().getCarReg() << endl << endl <<
	  "  Weekly Schedule:" << endl <<
	  "     Monday - " << daysAvailStr2[2] << endl <<
	  "     Tuesday - " << daysAvailStr2[3] << endl <<
	  "     Wednesday - " << daysAvailStr2[4] << endl <<
	  "     Thursday - " << daysAvailStr2[5] << endl <<
	  "     Friday - " << daysAvailStr2[6] << endl <<
	  "     Saturday - " << daysAvailStr2[0] << endl <<
	  "     Sunday - " << daysAvailStr2[1] << endl << endl <<
	  " Do you wish to set " << chosenInstructor.getFirstName() << " " << chosenInstructor.getLastName() << "as your new driving instructor?\n" <<
	  "   1 - Yes\n" <<
	  "   2 - No\n" << endl <<
	  "Enter your choice here > ";
	int finalChangeChoice;
	cin >> finalChangeChoice;
	while (!cin)
	  {
	    cout << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the non integer inputted
	    cin >> finalChangeChoice;

	  }
	while ((finalChangeChoice < 1) || (finalChangeChoice > 2))
	  {
	    cout << endl
		 << "Not a valid choice, please pick from the previous options." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the previously inputted string
	    cin >> finalChangeChoice;
	  }
	switch (finalChangeChoice){
	case 1:{ // update the csv file with this members new instructor
	  updateInstructor(loggedInLearner[0].getMemberID(), chosenInstructor.getInstructorID());
	  loggedInLearner[0].setInstructor(chosenInstructor);
	  cout << endl << endl;
	  centreText("Driving instructor successfully changed.\n");
	  break;}
	case 2:{
	  cout << endl << endl;
	  centreText("Change cancelled.");
	  cout << endl;
	  break;}
	}
	
      }
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      learnerHomePage();
      break;
    }
    case 7: // change lesson type (ie transmission being learnt, either manual or transmission)
      {
	cout << endl << endl;
	partition();
	cout << endl << endl;
	if (loggedInLearner[0].getPackageHours() == 0){ //only if the learner hasn't purchased a package can we let them change the type of lesson they have
	  string newTrans;
	  if (loggedInLearner[0].getTransmission() == "Manual"){
	    newTrans = "Automatic";
	  } else if (loggedInLearner[0].getTransmission() == "Automatic"){
	    newTrans = "Manual";
	  }
	  centreText("Change transmission of lessons:\n");
	  centreText("You have chosen to change the transmission of all your future lessons from " + loggedInLearner[0].getTransmission() + " to " + newTrans + ".\n");
	  cout <<
	    "Do you wish to continue with this change?\n" <<
	    "   1 - Yes\n" <<
	    "   2 - No\n\n" <<
	    "Enter your choice here > ";
	  int changeChoice;
	  cin >> changeChoice;
	  while (!cin)
	    {
	      cout << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the non integer inputted
	      cin >> changeChoice;
	    }
	  while ((changeChoice < 1) || (changeChoice > 2))
	    {
	      cout << endl
		   << "Not a valid choice, please pick from the previous options." << endl;
	      cin.clear();  // clear the error
	      cin.ignore(); // ignore the previously inputted string
	      cin >> changeChoice;
	    }
	  switch(changeChoice){
	  case 1:{
	    cout << endl << endl;
	    loggedInLearner[0].setTransmission(newTrans);
	    updateLearnerTransmission(loggedInLearner[0].getMemberID(), newTrans);
	    centreText("Your choice has been recorded successfully.\n");
	    centreText("All packages purchased from this point will be for " + loggedInLearner[0].getTransmission() + " lessons.");
	    break;}
	  case 2:{
	    cout << endl << endl;
	    break;}
	  }
	    } else { //if they have hours left on their previously purchased package
	  centreText("You currently have " + to_string(loggedInLearner[0].getPackageHours()) + " hours of " + loggedInLearner[0].getTransmission() + " lessons left of your previously purchased package.");
	  centreText("You could either book lessons until you have no more left or refund your remaining lesson hours");
	  centreText("in order to be able to change the transmission of your future lessons.\n\n");
	  partition();
	  chrono::seconds delay(consoleDelay);
	  this_thread::sleep_for(delay);
	}
	cout << endl << endl;
	centreText("Returning to home menu...\n");
	partition();
	chrono::seconds delay(consoleDelay);
	this_thread::sleep_for(delay);
	newScreen();
	learnerHomePage();
		break;
      }
    case 8:{ //updatePersonal details
      
      std::cout << std::endl << std::endl;
      partition();
      std::cout << std::endl << std::endl;
      centreText("Update Personal Details:\n");
      updatePersonalMemberDetails();
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      learnerHomePage();
      break;}
    case 9:{ //update pass
      cout << endl << endl;
      partition();
      cout << endl << endl;
      centreText("Change password:\n");
      cout << endl <<
	"Please enter your current password.\n\n" <<
	"Enter here > ";
      string currentPass;
      bool canChange = false;
      cin >> currentPass;
      if(currentPass == loggedInLearner[0].getPassword()){ // if their password is correct
	string newPass, confirmPass;
	bool theyMatch = false;
        cout << endl << endl <<
	  "Enter your desired new password. FYI: It cannot contain special character ',' (comma) or exceed 20 characters!\n\n" <<
	  "Enter new password here > ";
	cin >> newPass;
	if (newPass == currentPass){
	  cout << endl << endl <<
	    "New password cannot be the same as old password. Abandoning password change...\n";
	} else if (!inputValidation(newPass)){
	  cout << endl << endl <<
	    "New password cannot contain a comma. Abandoning password change...\n";
	} else if(newPass.length() > 20){
	  cout << endl << endl <<
	    "New password cannot exceed 20 characters. Abandoning password change...\n\n";
	} else {
	  cout << endl << endl <<
	    "Please confirm your new password below.\n\n" <<
	    "Confirm password here > ";
	  cin >> confirmPass;
	  if (newPass == confirmPass ){
	    //update the password
	    loggedInLearner[0].setPassword(newPass);
	    updateMemberPassword(loggedInLearner[0].getMemberID(), newPass);
	    cout << endl << endl;
	    centreText("You have successfully changed your password.\n");
	  } else {
	    cout << endl << endl <<
	      "Password confirmation failed. Abandoning password change...\n";
	  }
	}
      } else { //incorrect pass
	cout << endl << endl <<
	  "Incorrect. Abandoning password change ...\n";
      }
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      learnerHomePage();
      break;}
    case 10:{//signout 
      signOut();
      break;}
    }
}

void instructorHomePage(){
  int instructorChoice;
  vector<Lesson> lessons = loadLessons();
  do {
    partition();
    cout << endl;
    centreText("Instructor Home");
    cout << endl;
    centreText("Welcome " + loggedInInstructor[0].getFirstName() + " " + loggedInInstructor[0].getLastName() + "!");
    partition();
    cout << endl << endl << endl <<
            "Please choose from one of the options below:\n"
         << "   1 - Update Availability\n"
	 << "   2 - View my Lessons\n"
	 << "   3 - Cancel Lesson\n"
	 << "   4 - Update Personal Details\n"
	 << "   5 - Change Password\n"
	 << "   6 - Sign Out\n\n"
	 << "Enter choice here > ";
    if (!(cin >> instructorChoice)) {
      cin.clear(); 
      cin.ignore();
      cout << "Invalid input. Please pick from the above choices.\n";
      newScreen();
    }
  } while (instructorChoice < 1 || instructorChoice > 6);

  switch (instructorChoice) {
  case 1:{
    //Update Availability
    cout << endl << endl;
    partition();
    cout << endl << endl;
    centreText("Update your weekly availability:\n\n");
    centreText("The following is your current weekly schedule:\n");
    vector<string> daysAvailStr;
    for (string day : loggedInInstructor[0].getDaysAvailable()){
      string availability;
      if ((day == "1") || (day == "1\r")){
	availability = "Available";
      } else if ((day == "0") || (day == "0\r")){
	availability = "Off";
      }
      daysAvailStr.emplace_back(availability);
    }
    cout <<
      "     Monday - " << daysAvailStr[2] << endl <<
      "     Tuesday - " << daysAvailStr[3] << endl <<
      "     Wednesday - " << daysAvailStr[4] << endl <<
      "     Thursday - " << daysAvailStr[5] << endl <<
      "     Friday - " << daysAvailStr[6] << endl <<
      "     Saturday - " << daysAvailStr[0] << endl <<
      "     Sunday - " << daysAvailStr[1] << endl << endl <<
      "Do you wish to make changes to your availability?\n" <<
      "   1 - Yes\n" <<
      "   2 - No\n" <<
      "Enter your choice here > ";
    int updateChoice;
    cin >> updateChoice;
    while (!cin)
      {
	cout << "Not a valid option, please pick from the previous actions." << endl;
	cin.clear();  // clear the error
	cin.ignore(); // ignore the non integer inputted
	cin >> updateChoice;

      }
    while ((updateChoice < 1) || (updateChoice > 2))
      {
	cout << endl
	     << "Not a valid choice, please pick from the previous options." << endl;
	cin.clear();  // clear the error
	cin.ignore(); // ignore the previously inputted string
	cin >> updateChoice;
      }
    switch(updateChoice){
    case 1:{
      updateDaysAvailChoice();
      break;}
    case 2:{
      cout << endl << endl ;
      centreText("No changes were made.");
      break;}
    }
    cout << endl;
    centreText("Returning to home menu...\n");
    partition();
    chrono::seconds delay(consoleDelay);
    this_thread::sleep_for(delay);
    newScreen();
    instructorHomePage();
    break;}
    case 2:{
      //View my Lessons
      cout << endl;
      partition();
      cout << endl;
      viewLessonsInstructor(lessons, loggedInInstructor[0].getInstructorID());
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      instructorHomePage();
      break;}
    case 3:{
      //Cancel Lesson
      int lessonID;
      string cancellationReason;
      cout << endl << endl;
      partition();
      cout << endl << endl;
      centreText("Cancel a lesson:\n");
      bool hasLesson = false;
      for (Lesson lesson : loadLessons()){
	if (lesson.getInstructorID() == loggedInInstructor[0].getInstructorID()){
	  hasLesson = true;
	  break;
	}
      }
      if(hasLesson){ // has at least one lesson booked to cancel.
	cout <<
	  "Enter the lesson ID of the lesson you wish to cancel:\n\n";
	bool idMatch = false;
	Date date;
	Lesson chosenLesson(0,date,"","","",0,0);
	while(!idMatch){
	  cout << "Enter ID here > ";
	  cin >> lessonID;
	  if (!cin) {
	    cout << "Not a valid ID. Please enter a valid lesson ID." << endl;
	    cin.clear();  // clear the error
	    cin.ignore(); // ignore the invalid input
	    continue; 
	  }
	  for(Lesson lesson : loadLessons()){
	    if (lesson.getLessonID() == lessonID && 
		lesson.getInstructorID() == loggedInInstructor[0].getInstructorID()) {
	      idMatch = true;
	      chosenLesson = lesson;
	      break;
	    }
	  }
	  if(!idMatch){
	    cout << endl <<
	      "No lesson assigned to you with ID " << to_string(lessonID) << " found. Please choose a valid lesson ID." << endl;
	  }
	}
	cout << endl <<
	  "Enter your reason for cancelling your lesson > ";
	cin >> cancellationReason;
	while(!inputValidation(cancellationReason) || cancellationReason.empty()){
	  cout << "You must include a reason for your cancellation. You also cannot have special character ',' in your input.\n";
	  cin.clear();
	  cin.ignore();
	  continue;
	}
	cout <<  endl << endl;
	centreText("Selected lesson has been cancelled and lesson hours refunded to the student.\n");
	cancelLesson(lessonID, cancellationReason);
	Member learner;
	for (Member mem : loadRegisteredMembers() ){//retrieve the member
	  if(mem.getMemberID() == chosenLesson.getLearnerID()){
	    learner = mem;
	    break;
	  }
	}
	updatePackageHours(chosenLesson.getLearnerID() , learner.getPackageHours() + 2); // give back 2 hours to the member
      } else { // has no lessons booked to cancel
	cout << endl << endl;
	centreText("You currently have no lessons booked that you could cancel.\n");
	cout << endl;
      }
      cout << endl;
      centreText("Returning to home menu...\n");
      partition();
      chrono::seconds delay(consoleDelay);
      this_thread::sleep_for(delay);
      newScreen();
      instructorHomePage();
    break;}
  case 4:{
    //Update Personal Details
    updatePersonalInstructorDetails();
    cout << endl;
    centreText("Returning to home menu...\n");
    partition();
    chrono::seconds delay(consoleDelay);
    this_thread::sleep_for(delay);
    newScreen();
    instructorHomePage();
    break;}
  case 5:{
    changePassword(loggedInInstructor[0]);
    cout << endl;
    centreText("Returning to home menu...\n");
    partition();
    chrono::seconds delay(consoleDelay);
    this_thread::sleep_for(delay);
    newScreen();
    instructorHomePage();
    break;}
  case 6:{
    signOut();
    break;}
  }
}


int main()
{
	startUpMenu();
}
