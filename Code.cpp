#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <iterator>
#include <iomanip>

using namespace std;

int main() {
    string userResponse;
    string userName;
    string passWord;
    vector<string> pairs;
    vector<vector<string>> userLoginInfo; //maybe hashmaps
    bool successful = false;

    // Open a text file
    ifstream MyFile("StatisticsData.txt");

    // Read the file and store data in a map
    string state;
    string crimeRate;
    map<string, int> stats;
    while(getline(MyFile, state, ','))
    {
        getline(MyFile, crimeRate);
        stats.insert({state, stoi(crimeRate)});
    }

    //Open crimedata file
    ifstream MyFile2("CrimeData.txt");

    string temp;
    vector<string> State;
    vector<string> crimeType1;
    vector<string> crimeType2;
    vector<string> crimeType3;
    while(getline(MyFile2, temp, ','))
    {
        State.push_back(temp);
        getline(MyFile2, temp, ',');
        crimeType1.push_back(temp);
        getline(MyFile2, temp, ',');
        crimeType2.push_back(temp);
        getline(MyFile2, temp);
        crimeType3.push_back(temp);
    }

    MyFile2.close();
    //reading the file saved with all users' usernames and passwords from all previous runs
    ifstream readLoginFile("userLoginInformation.txt");
    while(getline(readLoginFile, userName, ','))
    {
        getline(readLoginFile, passWord);
        pairs.push_back(userName);
        pairs.push_back(passWord);
        userLoginInfo.push_back(pairs);
        pairs.clear();

    }
    //reading closed

    cout<< "Welcome to Crime Fighters!" << endl;
    cout<< "Do you already have an account set up with us?" << endl;
    cout << "Yes or No: ";
    cin >> userResponse;
    if (userResponse == "Yes" || userResponse == "yes"){//user has an account
        if(userLoginInfo.empty()){//if the login file is empty user is forced to create a login account(user does not have an account)
            cout << "There is no saved information within our database at this time. Please create a username and password." << endl;
            cout << "Username: ";
            cin >> userName;
            cout << "Password: ";
            cin >> passWord;
            while(passWord.length() < 8){//password must be less than 8 characters
                cout << "The password you have entered is less than 8 characters! Please re-enter. " << endl;
                cout << "Password: ";
                cin >> passWord;
            }
            pairs.push_back(userName);
            pairs.push_back(passWord);
            userLoginInfo.push_back(pairs);//save username and password in this vector as a pair
            pairs.clear();
            successful = true;

            //writing file with new login information to be saved for future runs
            ofstream myLoginFile("userLoginInformation.txt");

            for(int i = 0; i < userLoginInfo.size(); i++) {
                myLoginFile << userLoginInfo[i].at(0) << "," << userLoginInfo[i].at(1) << endl;

            }
            myLoginFile.close();
            //writing closed

        } else {//there is information in the login file(it is not empty)
            cout << "Great! Please sign in." << endl;
            while (successful == false) {
                cout << "Username: ";
                cin >> userName;
                cout << "Password: ";
                cin >> passWord;


                for (int i = 0; i < userLoginInfo.size(); i++) {//checking to see if login exists and has been saved
                    if (userName == userLoginInfo[i].at(0)) {
                        if (passWord == userLoginInfo[i].at(1)) {
                            successful = true;
                        }
                    }
                }

                if(successful == false){
                    cout << "Incorrect login information. Try again." << endl;//username and password inputted does not exist(or typed incorrectly)
                }
            }
        }


    } else if (userResponse == "No" || userResponse == "no"){//user does not have an account, therefore creating new username and password
        bool repeated = false;//boolean to check if the username and password are unique
        cout << "Don't worry! Let's get you signed up." << endl;
        cout << "Input New Username: ";
        cin >> userName;
        cout << "Input New Password: ";
        cin >> passWord;
        while(passWord.length() < 8){//password must be less than 8 characters
            cout << "The password you have entered is less than 8 characters! Please re-enter. " << endl;
            cout << "Password: ";
            cin >> passWord;
        }
        for (int i = 0; i < userLoginInfo.size(); i++) {//check for if the username and/or password are repeated
            if (userName == userLoginInfo[i].at(0)) {
                repeated = true;
                if (passWord == userLoginInfo[i].at(1)) {
                    repeated = true;
                }
            }
        }
        while(repeated == true){//if they are repeated and already saved in login file, prompt for new username and password
            cout << "This username and/or password already exist. Please input new login information. " << endl;
            cout << "Input New Username: ";
            cin >> userName;
            cout << "Input New Password: ";
            cin >> passWord;

            while(passWord.length() < 8){//password must be less than 8 characters
                cout << "The password you have entered is less than 8 characters! Please re-enter. " << endl;
                cout << "Password: ";
                cin >> passWord;
            }
            repeated = false;//back to false to check the new login information inputted
            for (int i = 0; i < userLoginInfo.size(); i++) {
                if (userName == userLoginInfo[i].at(0)) {
                    repeated = true;
                    if (passWord == userLoginInfo[i].at(1)) {
                        repeated = true;
                    }
                }
            }
        }
        pairs.push_back(userName);
        pairs.push_back(passWord);
        userLoginInfo.push_back(pairs);
        pairs.clear();
        successful = true;

        //writing file with new login information to be saved for future runs
        ofstream myLoginFile("userLoginInformation.txt");

        for(int i = 0; i < userLoginInfo.size(); i++) {
            myLoginFile << userLoginInfo[i].at(0) << "," << userLoginInfo[i].at(1) << endl;

        }
        myLoginFile.close();
        //writing closed

    }

    if(successful == true){
        cout << "Login Successful!!!" << endl;
    }

//showing the menu options to the user
    int menuOption=0;
    while(menuOption!=7)
    {
        cout<<"\n";
        cout << "~~~~~~MENU OPTIONS~~~~~~" << endl;
        cout << "1. Statistics " << endl;
        cout << "2. Crime " << endl;
        cout << "3. Demographics " << endl;
        cout << "4. Time " << endl;
        cout << "5. State " << endl;
        cout << "6. Re-login" << endl;
        cout << "7. Exit/Log Out " << endl;
        cin>> menuOption;

        //statistics
        if(menuOption==1)
        {
            cout<< setw(14) << "State" << setw(16) << "Crime Rate %\n";
            cout<<"------------------------------\n";
            for(auto it = stats.begin(); it != stats.end(); ++it)
            {
                cout << setw(14) << it->first << setw(9) << it->second << "\n";
            }
            cout<<endl;
        }

        //Crime
        if(menuOption==2)
        {
            cout<< setw(14) << "State" << setw(32) << "Top 3 Crime Types\n";
            cout<<"----------------------------------------------------------\n";
            for(int i=0; i<50; i++)
            {
                cout << setw(14) << State[i] << setw(16) << crimeType1[i] << ", " << crimeType2[i] << ", " << crimeType3[i] << "\n";
            }
            cout<<endl;
        }

        //Demographics
        if(menuOption==3)
        {
            cout<<"Work in Progress for Demographics\n";
        }

        //Time
        if(menuOption==4)
        {
            cout<<"Work in Progress for Time\n";
        }

        //State
        if(menuOption==5)
        {
            cout<<"Work in Progress for State\n";
        }

        if(menuOption==6)
        {
            cout<<"User logged out successfully!!!\n";
            cout<<"Username: "<<endl;
            cout<<"Password: "<<endl;
        }
    }

    // Close the file
    MyFile.close();
}
