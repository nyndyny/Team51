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
//Open statedata file
    ifstream MyFile3("StatesData.txt");
    string temp2;
    vector<string> state2;
    vector<string> population;
    vector<string> reported;
    vector<string> rate;
    vector<string> violent;
    vector<string> violentrate;
    vector<string> nonviolent;
    vector<string> nonviolentrate;
    while (getline(MyFile3, temp2, ',')) {
        state2.push_back(temp2);
        getline(MyFile3, temp2, ',');
        population.push_back(temp2);
        getline(MyFile3, temp2, ',');
        reported.push_back(temp2);
        getline(MyFile3, temp2, ',');
        rate.push_back(temp2);
        getline(MyFile3, temp2, ',');
        violent.push_back(temp2);
        getline(MyFile3, temp2, ',');
        violentrate.push_back(temp2);
        getline(MyFile3, temp2, ',');
        nonviolent.push_back(temp2);
        getline(MyFile3, temp2);
        nonviolentrate.push_back(temp2);

    }

    MyFile3.close();
    //read demographics file
    string s;
    vector<string> demoStates;
    vector<string> threeDemos;
    vector<vector<string>> demographics;


    ifstream readDemoFile("/Users/nivedhanatarajan/CLionProjects/Login/demographics.txt");
    while(getline(readDemoFile, s, ',')){
        demoStates.push_back(s);
        getline(readDemoFile, s, ',');
        threeDemos.push_back(s);
        getline(readDemoFile, s, ',');
        threeDemos.push_back(s);
        getline(readDemoFile, s);
        threeDemos.push_back(s);
        demographics.push_back(threeDemos);
    }

    //read time file
    ifstream timeSpan("/Users/sajani.panchal/CLionProjects/CrimeFighters/Time.txt");
    string temp3;
    vector<string> timeStates;
    vector<string> startTime;
    vector<string> endTime;
    while (getline(timeSpan, temp3, ','))
    {
        timeStates.push_back(temp3);
        getline(timeSpan, temp3, ',');
        startTime.push_back(temp3);
        getline(timeSpan, temp3);
        endTime.push_back(temp3);
    }
    timeSpan.close();

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
            int choice = 0;
            string stateChoice;
            cout << "What do you want to know?" << endl;
            cout << "You can learn about the typical age, gender, or ethnicity for victims of crime in that area!" << endl;
            cout << "Which would you like to know more about?" << endl;
            cout << "1. Age  2. Gender  3. Ethnicity 4. All Three" << endl;
            cout << "Option: ";
            cin >> choice;
            cout << "What state's information do you want to receive? : ";
            cin >> stateChoice;

            int num = 0;
            for(int i = 0; i < demoStates.size(); i++){
                if(stateChoice == demoStates.at(i)){
                    num = i;
                }
            }

            if(choice == 1){
                cout << stateChoice + "'s typical age for the victims of crime is" + demographics.at(num).at(0) + "." << endl;

            } else if (choice == 2){
                cout << stateChoice + "'s typical gender for the victims of crime is" + demographics.at(num).at(1) + "." << endl;

            } else if (choice == 3){
                cout << stateChoice + "'s typical ethnicity for the victims of crime is" + demographics.at(num).at(2) + "." << endl;
            } else if (choice == 4){
                cout << stateChoice + "'s typical age for the victims of crime is" + demographics.at(num).at(0) + "." << endl;
                cout << stateChoice + "'s typical gender for the victims of crime is" + demographics.at(num).at(1) + "." << endl;
                cout << stateChoice + "'s typical ethnicity for the victims of crime is" + demographics.at(num).at(2) + "." << endl;
            }
        }

        //Time
        if(menuOption==4)
        {
            string stateInput;
            cout << "Please enter the state you wish to find out about the most common time intervals of crime occurences:\n";
            cin >> stateInput;
            for(int j = 0; j < 50; j++)
            {
                if (timeStates.at(j) == stateInput)
                {
                    cout << "Most common time interval for crime occurrences in " << stateInput << " is " << startTime[j] << "-" << endTime[j] << "." "\n";

                }

            }

        }

        //State
        if(menuOption==5)
        {
            

            cout << "Please choose a command: " << endl;
            cout << " 1 - Search report on State " << endl;
            cout << " 2 - Rank State by highest crime rate " << endl;
            cout << " 3 - Rank State by highest violent crime rate " << endl;
            cout << " 4 - Rank State by highest nonviolent crime rate " << endl;


            cout << " 0 - Back to main menu " << endl;
            cout << endl;
            int statemenu;
            cin >> statemenu;

            if (statemenu < 0 || statemenu > 4) {
                cout << "Invalid command" << endl;
                cout << endl;
                continue;
            }

            if (statemenu == 1) {

                string state3;
                cout << "Enter a State: " << endl;
                cin >> state3;
                for (int i = 0; i < 50; i++) {

                    if (state2.at(i) == state3) {
                        cout << state2[i] << endl << "Population: " << population[i] << " Total Reports: "
                             << reported[i] << endl << "Rate: " << rate[i] << " Violent Reports: " << violent[i] << endl
                             << "Non-Violent Reports: " << nonviolent[i] << " Non-Violent Rates: " << nonviolentrate[i]
                             << endl;
                    }

                }

            } else if (statemenu == 2) {
                // search by location

                cout << "States ranking of highest crime rate: " << endl;
                for (int i = 0; i < 50; i++) {
                    cout << i + 1 << ". " << state2[i]<< ": " << rate[i] << endl;
                }
                cout << endl;


            } 
            

        
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
