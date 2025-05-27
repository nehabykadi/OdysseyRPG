
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include "Characters.h"
// #include "Tiles.cpp"
//  #include "Board.cpp"
#include <vector>

using namespace std;

int split(string input_string, char separator, string arr[], const int ARR_SIZE)
{
    int num_splits = 0, delim = 0;
    if (input_string == "")
    {
        return 0;
    }

    for (size_t i = 0; i < input_string.length(); i++)
    {

        if (input_string[i] == separator)
        {
            num_splits++;
            if (num_splits >= ARR_SIZE)
            {
                return -1;
            }
            delim++;
        }
        else
        {
            arr[delim] += input_string[i];
        }
    }

    return num_splits + 1;
}

int main()
{

    ifstream file_input;
    string name;
    file_input.open("characters.txt");

    if (file_input.fail())
    {
        cout << "Could not open file." << endl;
        return -1;
    }
    else
    {
        string line = "";
        string splitter[6];       // stores the splitted data
        vector<Character> player; // stores players
        int line_num = 0;

        /*
            cout: How many players do you want? Maximum of 4 players. No two characters can be used in the same game
            cout Here are the players
            for number of players
            who would you like for player x
            cin name
            if name = name
            player x = split of stats

        */
        string player_to_num;
        int player_num;
        cout << "How many players would like to play in this game? (min. 2 players, max. 5 players)? " << endl;
        getline(cin, player_to_num);

        player_num = stoi(player_to_num); // Convert string to integer
        while (player_num < 2 || player_num > 5)
        {
            cout << "Invalid number of players. Please enter a number between 2 and 5: " << endl;
            getline(cin, player_to_num);
            player_num = stoi(player_to_num); // Convert string to integer again
        }
        cout << " Great! Choose your character from the list: (One character per player)" << endl;

        while (!file_input.eof())
        {
            getline(file_input, line);
            cout << line << endl;
            line_num++;
        }

        for (int i = 1; i <= player_num; i++)
        {
            string name;
            cout << "Player " << i << ": Select your character:" << endl;
            getline(cin, name); // takes the input of the name of the character ( the code stops here and will not let me choose the first character)

            bool characterChosen = false;

            for (int k = 0; k < i - 1; k++)
            {
                if (name == player[k].getName())
                {
                    cout << "Character already chosen, choose a different character" << endl;
                    characterChosen = true;
                    i--;
                }
            }
            if (!characterChosen)
            {
                bool characterFound = false;
                // Reset file pointer to the beginning for each new selection
                file_input.clear();  // Clear any flags
                file_input.seekg(0); // Go to the start of the file

                // Skip the header line again
                getline(file_input, line);

                // Read through the file to find the character
                while (getline(file_input, line))
                {
                    string splitters[6];
                    split(line, '|', splitters, 6);
                    if (name == splitters[0] && name != "playerName")
                    {
                        Character newPlayer;
                        newPlayer.setName(splitters[0]);
                        newPlayer.setAge(stoi(splitters[1]));
                        newPlayer.setStrength(stoi(splitters[2]));
                        newPlayer.setStamina(stoi(splitters[3]));
                        newPlayer.setWisdom(stoi(splitters[4]));
                        newPlayer.setPridePoints(stoi(splitters[5]));
                        player.push_back(newPlayer);
                        newPlayer.printStats();
                        characterFound = true;
                        break;
                    }
                }

                if (!characterFound)
                {
                    cout << "Character not found, choose a character from the list." << endl;
                    i--;
                }
            }
        }

        int path;
        string path_to_num;

        file_input.close();

        cout << "Select the path that you would like to take during this Journay! ( 1 or 2)" << endl;
        cout << "(1) Cub Training: This path will provide you with Leadership that will help you with your tasks." << endl;
        cout << "This path will cost you an investmnet of -5,000 Pride Points, but in return it will provid you with" << endl;
        cout << " + 500 stamina Points, + 500 strength points and + 1,000 wisdom points!" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        cout << "(2) Straight to the Pride Lands: This path allows you to directly Jump into the Savannah with " << endl;
        cout << "an additional boost of +1,500 Pride Points, it will also provid you with" << endl;
        cout << " + 200 stamina Points, + 200 strength points and + 200 wisdom points!" << endl;

        for (int i = 1; i <= player_num; i++)
        {
            cout << "Player " << i << " choose your path:" << endl;

            getline(cin, path_to_num);
            path = stoi(path_to_num);

            while (path != 1 && path != 2)
            {
                cout << "Incorrect input. Choose one out of the two options (1 or 2)" << endl;
                getline(cin, path_to_num);
                path = stoi(path_to_num);
            }
            string advisor;

            if (path == 1)
            {

                cout << "Player " << i << " you chose the Cub Training path!" << endl;
                cout << "You can now choose your advisor which will help you on your journey! " << endl;
                cout << "Available advisors: (name of the advisor)" << endl;
                // add list of advisors

                getline(cin, advisor);

                player[i - 1].setAdvisor(advisor);
                player[i - 1].trainCub(500, 500, 1000);
                player[i - 1].printStats();
                // point are not changed right
            }
            if (path == 2)
            {
                cout << "Player " << i << " you chose the Straight to the Pride Lands path!" << endl;

                player[i - 1].toPrideLands(200, 200, 200);
                player[i - 1].printStats();
                // points are not changed right
            }
        }
        // pick characters + pick track
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        vector<bool> player_at_orange; // this will be changed depending on if the character moved to the orange tile after moving forward


        for (int i = 0; i < player_num; i++)
        {
            // this sets a vector of players on the last tile if the character gets to the finish line the false in the place of the player turns true and skips its turn
            player_at_orange.push_back(false);
        }

        // int turn_count; // keeps track of the the turn
        for (int i = 0; i < player_num; i++)
        {
            if (!player_at_orange[i])
            {
                // Main menu code:
                string menu;
                string trade;
                int num_choice;
                bool main_menu = true;
                string go_back_menu;

                while (main_menu)
                {
                    cout << "1. Check Player Progress: Review Pride Point and Leadership Trait stats." << endl;
                    cout << "2. Review Character: Check your character name and age." << endl;
                    cout << "3. Check Position: Display board to view current position." << endl;
                    cout << "4. Review your Advisor: Check who your current advisor is on the game." << endl;
                    cout << "5. Move Forward: For each player’s turn, access this option to spin the virtual spinner." << endl;
                    cout << "Player " << i+1 << " Please select the option you would like to display (1/2/3/4/5)" << endl;
                    getline(cin, menu);

                    num_choice = stoi(menu);
                    while (num_choice != 1 && num_choice != 2 && num_choice != 3 && num_choice != 4 && num_choice != 5)
                    {
                        cout << "Invalid intiger, enter a valid value: (1/2/3/4/5)" << endl;
                        getline(cin, menu);
                        num_choice = stoi(menu);
                    }

                    if (num_choice == 1)
                    {
                        cout << "Player Progress: ";

                        cout << player[i].getPridePoints() << endl;

                        cout << "Would you like to make a trade for Moto Points? (yes/no)" << endl;
                        getline(cin, trade);

                        if (trade == "yes")
                        {
                            cout << "Leadership Points: " << endl;
                            cout << "Rest: " << player[i].getStrength() << endl;
                            cout << "Wisdom: " << player[i].getWisdom() << endl;
                            cout << "Customer Service: " << player[i].getStamina() << endl;
                            cout << "---------------------------------------" << endl;
                            cout << "You can exchange your points at a rate of: " << endl;
                            cout << "1,000 Rest = 500 Moto Points" << endl;
                            cout << "3,000 = Wisdom = 500 Moto Points" << endl;
                            cout << "5,000 Customer Service = 500 Moto Points" << endl;
                            cout << "Remember you can only convert full sets of points" << endl;
                            cout << "Which points would you like to exchange? (rest / wisdom / customer service)" << endl;

                            string trade_choice;
                            // int trading_points;
                            getline(cin, trade_choice);
                            while (trade_choice != "rest" && trade_choice != "wisdom" && trade_choice != "customer service")
                            {
                                cout << "Sorry, choose an option from the listed above: (rest / wisdom / customer service)" << endl;
                                getline(cin, trade_choice);
                            }
                            ///////////////////////////rest//////////////////////////////////////////////////
                            if (trade_choice == "rest")
                            {

                                if (player[i].getStrength() < 1000)
                                {
                                    main_menu = true;
                                    cout << "Sorry, you do not have enough points to exchange right now, try to exchage a diferrent type of points or come back on the next turn" << endl;
                                    cout << "Would you like to return to the main menu? (yes/no)" << endl;
                                    getline(cin, go_back_menu);
                                    while (go_back_menu != "yes" && go_back_menu != "no")
                                    {
                                        cout << "Sorry, choose a valid option: (yes/no)" << endl;
                                        getline(cin, go_back_menu);
                                    }
                                    if (go_back_menu == "yes")
                                    {
                                        // i--;
                                        continue;
// basically after this point the code does not go back to main menu at all the code just ends, does not go to the next player at all,

                                    }
                                    if (go_back_menu == "no")
                                    {
                                        cout << "Which points would you like to exchange? (wisdom / customer service)" << endl;
                                        getline(cin, trade_choice);
                                        if (trade_choice != "wisdom" && trade_choice != "customer service")
                                        {
                                            cout << "Sorry, choose an option from the listed above: (wisdom / customer service)" << endl;
                                            getline(cin, trade_choice);
                                        }
                                    }
                                }
                                else
                                {
                                    int conversion_rate_moto_points = 500; // 500 moto points = 1,000 rest points
                                    int conversion_rate_rest = 1000;

                                    // Calculate how many full conversions of 1000 rest points can be made
                                    int conversion_rest = player[i].getStrength() / conversion_rate_rest;

                                    // Calculate b points from full conversions
                                    int moto_points = conversion_rest * conversion_rate_moto_points;

                                    // Calculate remaining rest points (less than 1000)
                                    int remaining_rest_points = player[i].getStrength() % conversion_rate_rest;

                                    player[i].setPridePoints(player[i].getPridePoints() + moto_points);
                                    player[i].setStrength(remaining_rest_points);
                                    cout << "You now have: " << endl;
                                    cout << "Moto Points: " << player[i].getPridePoints() << endl;
                                    cout << "Rest Points: " << player[i].getStrength() << endl;

                                    cout << "Returning to main menu..." << endl;
                                    // i--;
                                    continue;
                                }
                            }
                            ///////////////////////////////////////wisdom///////////////////////////////////////////////////////////
                            if (trade_choice == "rest")
                            {

                                if (player[i].getStrength() < 1000)
                                {
                                    main_menu = true;
                                    cout << "Sorry, you do not have enough points to exchange right now, try to exchage a diferrent type of points or come back on the next turn" << endl;
                                    cout << "Would you like to return to the main menu? (yes/no)" << endl;
                                    getline(cin, go_back_menu);
                                    while (go_back_menu != "yes" && go_back_menu != "no")
                                    {
                                        cout << "Sorry, choose a valid option: (yes/no)" << endl;
                                        getline(cin, go_back_menu);
                                    }
                                    if (go_back_menu == "yes")
                                    {
                                        main_menu = false;
                                        continue;
                                    }
                                    if (go_back_menu == "no")
                                    {
                                        cout << "Which points would you like to exchange? (wisdom / customer service)" << endl;
                                        getline(cin, trade_choice);
                                        if (trade_choice != "wisdom" && trade_choice != "customer service")
                                        {
                                            cout << "Sorry, choose an option from the listed above: (wisdom / customer service)" << endl;
                                            getline(cin, trade_choice);
                                        }
                                    }
                                }
                                else
                                {
                                    int conversion_rate_moto_points = 500; // 500 moto points = 1,000 rest points
                                    int conversion_rate_rest = 1000;

                                    // Calculate how many full conversions of 1000 rest points can be made
                                    int conversion_rest = player[i].getStrength() / conversion_rate_rest;

                                    // Calculate b points from full conversions
                                    int moto_points = conversion_rest * conversion_rate_moto_points;

                                    // Calculate remaining rest points (less than 1000)
                                    int remaining_rest_points = player[i].getStrength() % conversion_rate_rest;

                                    player[i].setPridePoints(player[i].getPridePoints() + moto_points);
                                    player[i].setStrength(remaining_rest_points);
                                    cout << "You now have: " << endl;
                                    cout << "Moto Points: " << player[i].getPridePoints() << endl;
                                    cout << "Rest Points: " << player[i].getStrength() << endl;

                                    cout << "Returning to main menu..." << endl;
                                    main_menu = false;
                                }
                            }
                            ////////////////////////////////////////customer service///////////////////////////////////////////////////
                            if (trade_choice == "customer service")
                            {

                                if (player[i].getStrength() < 1000)
                                {
                                    main_menu = true;
                                    cout << "Sorry, you do not have enough points to exchange right now, try to exchage a diferrent type of points or come back on the next turn" << endl;
                                    cout << "Would you like to return to the main menu? (yes/no)" << endl;
                                    getline(cin, go_back_menu);
                                    while (go_back_menu != "yes" && go_back_menu != "no")
                                    {
                                        cout << "Sorry, choose a valid option: (yes/no)" << endl;
                                        getline(cin, go_back_menu);
                                    }
                                    if (go_back_menu == "yes")
                                    {
                                        main_menu = false;
                                        // does not work

                                    }
                                    if (go_back_menu == "no")
                                    {
                                        cout << "Which points would you like to exchange? (wisdom / customer service)" << endl;
                                        getline(cin, trade_choice);
                                        if (trade_choice != "wisdom" && trade_choice != "customer service")
                                        {
                                            cout << "Sorry, choose an option from the listed above: (wisdom / customer service)" << endl;
                                            getline(cin, trade_choice);
                                        }
                                    }
                                }
                                else
                                {
                                    int conversion_rate_moto_points = 500; // 500 moto points = 1,000 rest points
                                    int conversion_rate_rest = 1000;

                                    // Calculate how many full conversions of 1000 rest points can be made
                                    int conversion_rest = player[i].getStrength() / conversion_rate_rest;

                                    // Calculate b points from full conversions
                                    int moto_points = conversion_rest * conversion_rate_moto_points;

                                    // Calculate remaining rest points (less than 1000)
                                    int remaining_rest_points = player[i].getStrength() % conversion_rate_rest;

                                    player[i].setPridePoints(player[i].getPridePoints() + moto_points);
                                    player[i].setStrength(remaining_rest_points);
                                    cout << "You now have: " << endl;
                                    cout << "Moto Points: " << player[i].getPridePoints() << endl;
                                    cout << "Rest Points: " << player[i].getStrength() << endl;

                                    cout << "Returning to main menu..." << endl;
                                    main_menu = false;
                                }
                            }
                        }
                    }
                    //////////////////////////////////end of option 1///////////////////////////////////////////////////////////////////////////////////////
                    if (num_choice == 2)
                    {
                        cout << "Player's character review:" << endl;
                        cout << "Name: " << player[i].getName() << endl;
                        cout << "Age: " << player[i].getAge() << endl;
                        cout << "" << endl;

                        cout << "Returning to main menu..." << endl;
                      
                        //will not go back to main menu
                    }
                    if (num_choice == 3)
                    {
                        //.displayBoard();

                        cout << "Returning to main menu..." << endl;
                       
                    }
                    if (num_choice == 4)
                    {

                        cout << "Player's advisor review:" << endl;
                        cout << "Advisor: " << player[i].getAdvisor() << endl;

                        cout << "Returning to main menu..." << endl;
                        
                    }
                    // if (num_choice == 5 )
                    //{

                    // }
                }

                
            }
            
        }
    }
    return 0;
}