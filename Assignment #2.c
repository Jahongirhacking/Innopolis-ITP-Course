#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ERR "Invalid inputs"
#define ATTACK "attack"
#define FLIP_VISIBILITY "flip_visibility"
#define HEAL "heal"
#define SUPER "super"
#define TRUE "True"
#define FALSE "False"

#define CANT_PLAY_MSG "This player can't play\n"
#define FROZEN_MSG "This player is frozen\n"
#define SAME_TEAM_MSG "Both players should be from the same team\n"
#define HEAL_ITSELF_MSG "The player cannot heal itself\n"
#define SUPER_ITSELF_MSG "The player cannot do super action with itself\n"

#define MAXX 1100
#define MAX_STR 1000
#define MAX_PLAYER 200
#define MAX_MAGICIAN 10
#define MAX_NAME 23
#define MAXIMUM_STR 256

void pureString(char *str){
    // Make the string be in the right form without '\n'
    for(int i=0; str[i]!='\0' && str[i]!='\n'; i++){
        if(str[i]=='\n') str[i]='\0';
    }
}

void showErrorMessage(){
    FILE *outFile;
    outFile = fopen("output.txt", "w");
    fprintf(outFile, ERR);

    printf(ERR);
    fclose(outFile);
}

bool isCapital(char c) {
    // Check whether string begins with Capital Latin Letter
    int pos = (int) c; // ASCII position of the character A -> 65, ... , Z -> 90
    if(pos >= 65 && pos <= 90) return true;
    return false;
}

bool isAllLatin(char s[]) {
    // Check whether all elements of the string is Latin Letter
    // in ASCII: a -> 97, ... z -> 122
    for(int i = 1; s[i]!='\0' && s[i]!='\n'; i++){
        // Loop through the string
        // If letter is not Latin then return false
        if(!(s[i] >= 97 && s[i] <= 122 || s[i] >= 65 && s[i] <= 90)) return false;
    }
    return true;
}

bool checkStringIsValid(char s[]) {
    for(int i = 1; s[i]!='\0' && s[i]!='\n'; i++) {
        if(!isalpha(s[0])) return false;
    }
    return true;
}

int strToInt(char s[]) {
    // Convert string to integer
    int n = 0;
    for(int i = 0; s[i]!='\0' && s[i]!='\n' ; i++) {
        // Check elements are number else return -1
        if(!(s[i]-'0' >= 0 && s[i]-'0' <= 9)) return -1;
        n*=10;
        n+=(s[i]-'0');
    }
    // Converted integer
    return n;
}

struct Player{
    char name[MAX_NAME];
    int team_number;
    int power;
    bool isVisible; // check visibility
    bool isExist; // Extra variable to check existance
};

int main()
{
    FILE *inFile;
    inFile = fopen("input.txt", "r");

    if(inFile == NULL) return showErrorMessage(), 0;

    // ************ DECLARATIONS ************* //

    char str[MAX_STR]; // variable to read every string in input.txt
    char magicians[MAX_MAGICIAN][MAX_NAME]; // Array which contains magicians' names
    char player_names[MAX_PLAYER][MAX_NAME]; // Array which contains players' names
    struct Player players[MAX_PLAYER]; // Array which contains ALL information about players (Main Array)
    int max_power=-1, winnerId, winnersNumber=0; // Information about the winner(s)
    //char actions[MAXX][MAX_STR];

    // Default Values
    for(int i=0; i<MAX_PLAYER; i++){
        strcpy(players[i].name, "");
        players[i].isExist=false;

        strcpy(player_names[i], "");
    }

    // Explicit variables

    int numberOfMagicians;
    int numberOfPlayers;
    char name[MAX_NAME];
    int teamNumber;
    int numberOfSupers=0;
    int power;
    bool isVisible;

    // ************ INIT OUT FILE ************* //

    FILE *outFile;
    outFile = fopen("output.txt", "w");


    // ************ INITIALIZING AND TESTING (INPUT) ************* //

    int control=0; // variable which controls to initialize
    while(fscanf(inFile, "%s\n", str)!=0) {

        if(control==0){
            // First Step is Magicians
            numberOfMagicians=strToInt(str);
            if(numberOfMagicians<1 || numberOfMagicians>10) return fclose(outFile), showErrorMessage(),0; // If number is not correct

            for(int i=0; i<numberOfMagicians; i++){

                fgets(str, MAXIMUM_STR, inFile);
                pureString(str); // Make string more clear (without \n)
                if((strlen(str)<2) || strlen(str)>20 || !isCapital(str[0]) || !isAllLatin(str)) return fclose(outFile), showErrorMessage(),0; // If NAME is not correct

                // *** Magicians Main Array *** //
                strcpy(magicians[i], str);
            }

            //for(int i=0; i<numberOfMagicians; i++) printf("%s %d\n", magicians[i], strlen(magicians[i])); // test
        }

        else if(control==1){
            // Second Step is Players
            numberOfPlayers=strToInt(str);
            if(numberOfPlayers<numberOfMagicians || numberOfPlayers>100) return fclose(outFile), showErrorMessage(),0; // If number is not correct

            for(int i=0; i<numberOfPlayers; i++){

                // Name
                fscanf(inFile, "%s\n", str);
                pureString(str); // Make string more clear (without \n)
                if(strlen(str)<2 || strlen(str)>20 || !checkStringIsValid(str) || !isCapital(str[0]) || !isAllLatin(str)) return fclose(outFile), showErrorMessage(),0; // If NAME is not correct
                strcpy(name,str);

                // The number of the Team
                fscanf(inFile, "%s\n", str);
                teamNumber=strToInt(str);
                if(teamNumber<0 || teamNumber>=numberOfMagicians) return fclose(outFile), showErrorMessage(),0; // If TEAM NUMBER doesn't exist

                // Power
                fscanf(inFile, "%s\n", str);
                power=strToInt(str);
                if(power<0 || power>1000) return fclose(outFile), showErrorMessage(),0; // If TEAM NUMBER doesn't exist

                // Visibilty
                fscanf(inFile, "%s\n", str);
                pureString(str); // Make string more clear (without \n)
                if(strcmp(str,TRUE)==0) isVisible=true;
                else if(strcmp(str,FALSE)==0) isVisible=false;
                else return fclose(outFile), showErrorMessage(),0;

                // ** All Players Name ** //
                strcpy(player_names[i], name);

                // *** PLAYERS INFO MAIN MAIN MAAAAAIIIIN ARRAY *** //
                strcpy(players[i].name, name);
                players[i].team_number = teamNumber;
                players[i].power = power;
                players[i].isVisible = isVisible;
                players[i].isExist = true;
            }
        }

        control++;

        if(control>1) break; // I don't want to increase memory by taking actions' info
    }


    // ************ END OF TEST CASES ************** //



    // ************ MAIN ALGORITHM ************* //

    char command[17], name1[MAX_NAME], name2[MAX_NAME];
    int cmd=0; // number of commands
    while(fscanf(inFile, "%s ", command)>0) {
        cmd++;
        if(cmd>1000) return fclose(outFile), showErrorMessage(), 0; // If exceed the limit
        pureString(str);

        if(strcmp(command, FLIP_VISIBILITY)==0){
            // *** $$$ &&&& FLIP VISIBILITY &&&& $$$$ *** // *********************************
            fscanf(inFile, "%s\n", name1);
            pureString(name1);

            // CHECK WHETHER NAME1 EXISTS OR NOT

            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name1)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0;
                    // If FROZEN then MSG @Console
                    if(players[i].power==0) fprintf(outFile, FROZEN_MSG), printf(FROZEN_MSG);
                    else {
                        // TEST FOR CONSOLE
                        printf("visibility: %s -> %d, ", players[i].name, players[i].isVisible); // for test

                        players[i].isVisible = !players[i].isVisible;

                        // TEST RESULT FOR CONSOLE
                        printf("visibility: %s -> %d\n", players[i].name, players[i].isVisible); // for test

                    }
                    break;
                }
            }

            //printf("%d\n",players[1].isVisible);
        }
        else if(strcmp(command, ATTACK)==0){
            // *** $$$ &&&& ATTACK &&&& $$$$ *** // *********************************

            fscanf(inFile, "%s %s\n", name1, name2);
            pureString(name1);
            pureString(name2);

            // CHECK WHETHER NAME1 and NAME2 EXIST OR NOT

            int name1_ID, name2_ID;
            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name1)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name1_ID = i;
                    break;
                }
            }

            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name2)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name2_ID = i;
                    break;
                }
            }

            // TEST FOR CONSOLE
            printf("attack: %s -> %d, %s -> %d ; ", players[name1_ID].name, players[name1_ID].power, players[name2_ID].name, players[name2_ID].power); // for test

            // Visible = False Case then MSG @Console
            if(!players[name1_ID].isVisible) fprintf(outFile, CANT_PLAY_MSG), printf(CANT_PLAY_MSG);
            // First player is Frozen Case @Console
            else if(players[name1_ID].power==0) fprintf(outFile, FROZEN_MSG), printf(FROZEN_MSG);
            // Second player is Frozen Case
            //else if(players[name2_ID].power==0) fprintf(outFile, FROZEN_MSG), printf(FROZEN_MSG);
            // Second is Frozen Case @Console
            else if(!players[name2_ID].isVisible){
                // if playerj is not visible, then the playeri will be frozen.
                players[name1_ID].power = 0;
                // MAYBE THE PROBLEM IS HERE
            }
            else if(players[name1_ID].power > players[name2_ID].power){
                // if pi>pj, then playeri will gain pi−pj power and playerj will have no power left and further will be called frozen.
                players[name1_ID].power += (players[name1_ID].power - players[name2_ID].power);
                if(players[name1_ID].power > 1000) players[name1_ID].power = 1000;
                players[name2_ID].power = 0;
            }
            else if(players[name2_ID].power > players[name1_ID].power){
                // if pi<pj, then playeri will be frozen and playerj will gain pj−pi power.
                players[name2_ID].power += (players[name2_ID].power - players[name1_ID].power);
                if(players[name2_ID].power > 1000) players[name2_ID].power = 1000;
                players[name1_ID].power = 0;
            }
            else if(players[name1_ID].power == players[name2_ID].power){
                // if pi=pj, then both players will be frozen.
                players[name1_ID].power = 0;
                players[name2_ID].power = 0;
            }
            else return fclose(outFile), showErrorMessage(),0;


            // RESULT TEST FOR CONSOLE
            printf("  then: %s -> %d, %s -> %d\n", players[name1_ID].name, players[name1_ID].power, players[name2_ID].name, players[name2_ID].power); // for test

        }
        else if(strcmp(command, HEAL)==0){
            // *** $$$ &&&& HEAL &&&& $$$$ *** // *********************************

            fscanf(inFile, "%s %s\n", name1, name2);
            pureString(name1);
            pureString(name2);

            // CHECK WHETHER NAME1 and NAME2 EXIST OR NOT

            int name1_ID, name2_ID;
            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name1)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name1_ID = i;
                    break;
                }
            }


            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name2)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name2_ID = i;
                    break;
                }
            }

            // TEST FOR CONSOLE
            printf("heal: %s -> %d, %s -> %d ; ", players[name1_ID].name, players[name1_ID].power, players[name2_ID].name, players[name2_ID].power); // for test


            // Visible = False Case then MSG @Console
            if(!players[name1_ID].isVisible) fprintf(outFile, CANT_PLAY_MSG), printf(CANT_PLAY_MSG);
            // Frozen Case @Console
            else if(players[name1_ID].power==0) fprintf(outFile, FROZEN_MSG), printf(FROZEN_MSG);
            // If not the same team @Console
            else if(players[name1_ID].team_number != players[name2_ID].team_number) fprintf(outFile, SAME_TEAM_MSG), printf(SAME_TEAM_MSG);
            // Heal itself Case @Console
            else if(name1_ID == name2_ID) fprintf(outFile, HEAL_ITSELF_MSG), printf(HEAL_ITSELF_MSG);
            // HEALING
            else {
                // Ceiling Problem
                players[name1_ID].power = (players[name1_ID].power+1)/2;
                players[name2_ID].power += players[name1_ID].power;
                if(players[name2_ID].power > 1000) players[name2_ID].power = 1000;
            }

             // RESULT TEST FOR CONSOLE
            printf("  then: %s -> %d, %s -> %d\n", players[name1_ID].name, players[name1_ID].power, players[name2_ID].name, players[name2_ID].power); // for test


            //printf("%d %d\n", players[name1_ID].power, players[name2_ID].power);

        }
        else if(strcmp(command, SUPER)==0){
            // *** $$$ &&&& SUPER &&&& $$$$ *** // *********************************


            fscanf(inFile, "%s %s\n", name1, name2);
            pureString(name1);
            pureString(name2);


            // CHECK WHETHER NAME1 and NAME2 EXIST OR NOT

            int name1_ID, name2_ID;
            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name1)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name1_ID = i;
                    break;
                }
            }

            for(int i=0; i<=numberOfPlayers; i++){
                if(strcmp(player_names[i],"")==0) return fclose(outFile), showErrorMessage(), 0; // If there is no player in this name

                if(strcmp(player_names[i], name2)==0){
                    if(!players[i].isExist) return fclose(outFile), showErrorMessage(),0; // If player doesn't exist
                    name2_ID = i;
                    break;
                }
            }


            // Visible = False Case then MSG @Console
            if(!players[name1_ID].isVisible) fprintf(outFile, CANT_PLAY_MSG), printf(CANT_PLAY_MSG);
            // Frozen Case @Console
            else if(players[name1_ID].power==0) fprintf(outFile, FROZEN_MSG), printf(FROZEN_MSG);
            // If not the same team @Console
            else if(players[name1_ID].team_number != players[name2_ID].team_number) fprintf(outFile, SAME_TEAM_MSG), printf(SAME_TEAM_MSG);
            // Super itself Case @Console
            else if(name1_ID == name2_ID) fprintf(outFile, SUPER_ITSELF_MSG), printf(SUPER_ITSELF_MSG);

            // MAKE SUPER $$$ The most DIFFICULT part for ME :(

            else {

                // TEST FOR CONSOLE
                printf("p1: %s -> %d, p2: %s -> %d; ", players[name1_ID].name, players[name1_ID].power, players[name2_ID].name, players[name2_ID].power); // for test


                // name S_k (k = 0++) push_back to player_names and players array
                char nameOfSuper[10] = "S_";
                char number[6];
                sprintf(number, "%d", numberOfSupers);
                strcat(nameOfSuper, number);

                strcpy(player_names[numberOfPlayers], nameOfSuper);

                // Name
                strcpy(players[numberOfPlayers].name, nameOfSuper);

                // Team Number

                players[numberOfPlayers].team_number = players[name1_ID].team_number;

                // Power <=1000 problem
                int sum = (players[name1_ID].power + players[name2_ID].power);
                if(sum > 1000) sum = 1000;
                players[numberOfPlayers].power = sum;

                // Visible
                players[numberOfPlayers].isVisible = true;

                // Exist
                players[numberOfPlayers].isExist = true;

                // make 2 players' isExist False, visible = false, power=0
                players[name1_ID].isVisible = false;
                players[name1_ID].power = 0;
                players[name1_ID].isExist = false;

                players[name2_ID].isVisible = false;
                players[name2_ID].power = 0;
                players[name2_ID].isExist = false; ///// TROUBLESHOOOTING POOOINT

                // TEST FOR CONSOLE
                printf("s_info: %s -> %d\n", players[numberOfPlayers].name, players[numberOfPlayers].power); // for test


                numberOfPlayers++; // increase players number because of new addition
                numberOfSupers++; // Increase supers number by 1

            }



            //printf("%d %d\n", players[name1_ID].power, players[name2_ID].power) //for test ;


        }
        else return fclose(outFile), showErrorMessage(), 0;

    }


    fclose(inFile); // Close the Read file



    // ************ DETECT THE WINNER ************* //

    // necessary variables:  int max_power=-1, winnerId, winnersNumber=0;
    // Information about the winner(s)
    int powers_box[numberOfMagicians]; // creating Array of powers to compare which team is the best
    for(int i=0; i<numberOfMagicians; i++) powers_box[i] = -1;

    // complete power_box
    for(int i=0; i<=numberOfPlayers; i++){
        if(strcmp(player_names[i],"")==0) break;

        if(players[i].isExist) {
            if(powers_box[players[i].team_number]==-1) powers_box[players[i].team_number]=0;
            powers_box[players[i].team_number] += players[i].power; // Add each existing players power to its corresponding power_box
        }
    }

    // compare each power inside the powers_box
    for(int i=0; i<numberOfMagicians; i++) {
        if(powers_box[i] > max_power){
            max_power = powers_box[i];
            winnerId = i;
            winnersNumber = 1;
        }
        else if(powers_box[i] == max_power) winnersNumber++;
    }


    // ************ OUTPUT ************* //

    if(winnersNumber==1) {
        fprintf(outFile, "The chosen wizard is %s", magicians[winnerId]);
        printf("The chosen wizard is %s", magicians[winnerId]);
    }
    else {
        fprintf(outFile, "It's a tie");
        printf("It's a tie");
    }

    fclose(outFile);

    // ***** THE END **** //

    return 0;
}
