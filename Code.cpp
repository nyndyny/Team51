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
  vector<vector<string>> userLoginInfo;
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

  cout<< "Welcome to Crime Fighters!" << endl;
  cout<< "Do you already have an account set up with us?" << endl;
  cout << "Yes or No: ";
  cin >> userResponse;
  if (userResponse == "Yes" || userResponse == "yes"){
    if(userLoginInfo.empty()){//USER IS FORCED CREATE LOGIN INFO BECAUSE NOTHING IS SAVED
        cout << "There is no saved information within our database at this time. Please create a username and password." << endl;
        cout << "Username: ";
        cin >> userName;
        cout << "Password: ";
        cin >> passWord;
        while(passWord.length() < 8){
            cout << "The password you have entered is less than 8 characters! Please re-enter. " << endl;
            cout << "Password: ";
            cin >> passWord;
        }
        pairs.push_back(userName);
        pairs.push_back(passWord);
        userLoginInfo.push_back(pairs);
        pairs.clear();
        successful = true;
    } else {
        cout << "Great! Please sign in." << endl;
        while (successful == false) {
            cout << "Username: ";
            cin >> userName;
            cout << "Password: ";
            cin >> passWord;

            for (int i = 0; i < userLoginInfo.size(); i++) {
                if (userName == userLoginInfo[0].at(0)) {
                    if (passWord == userLoginInfo[0].at(1)) {
                      successful = true;
                    }
                }
            }
            if(successful == false){
                cout << "Incorrect login information. Try again." << endl;
            }
        }
    }


  } else if (userResponse == "No" || userResponse == "no"){
      cout << "Don't worry! Let's get you signed up." << endl;
      cout << "Input New Username: ";
      cin >> userName;
      cout << "Input New Password: ";
      cin >> passWord;
      while(passWord.length() < 8){
          cout << "The password you have entered is less than 8 characters! Please re-enter. " << endl;
          cout << "Password: ";
          cin >> passWord;
      }
      pairs.push_back(userName);
      pairs.push_back(passWord);
      userLoginInfo.push_back(pairs);
      pairs.clear();
      successful = true;
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
      for(auto it = stats.cbegin(); it != stats.cend(); ++it)
      {
        cout << setw(14) << it->first << setw(9) << it->second << "\n";
      }
      cout<<endl;
    }

    //Crime
    if(menuOption==2)
    {
      cout<<"Work in Progress for Crime Type\n";
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