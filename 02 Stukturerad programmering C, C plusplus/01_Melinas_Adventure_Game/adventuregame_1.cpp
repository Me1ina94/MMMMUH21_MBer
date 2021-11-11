// AdventureGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::to_string;

const string x = "empty";
const string yellowStone = "Yellow stone", purpleStone = "Purple stone", blueStone = "Blue stone", redStone = "Red stone";

string bag[15] = { x, x, x, x, x, x, x, x, x, x ,x, x, x, x, x };
const string places[5]{ "Underground Catatombs", "Arrendyll's Mountain", "Phantom forrest", "Ruined city", "Wolf Realm" };
const string stones[4]{ yellowStone, purpleStone, blueStone, redStone };
string abilities[5];
string letters[5];

vector <string> weapon;
vector <int> weaponDamage;

string quest_1 = "Villige quest!\n\tThere is a villige that has a problem with a goblin that attacks \n\t"
                 "people going back and forth from the village.\n\t[Reward: 25 gold.]\n",
       quest_2 = "Concered neighbor.\n\tThere's something that's been attacking my cattle for days now. I have\n\t"
                 "not been able to see what it is, but it need's to be dealt with ASAP!\n\tSeeking a brave worrior!\n\t"
                 "[Reward: 100 gold.]\n",
       quest_3 = "Wolf problem.\n\tWe've killed almost all the wolf, but it is one that keep's getting \n\taway. Urgent help needed!\n\t[Reward: 50 gold].\n";

string quests[3] = {quest_1, quest_2, quest_3};

//Get size of arrays
const int numberOfPlaces = sizeof(places) / sizeof(bag[0]);
const int sizeOfBag = sizeof(bag) / sizeof(bag[0]);
const int numberOfAbilities = sizeof(abilities) / sizeof(abilities[0]);
const int numberOfLetters = sizeof(letters) / sizeof(letters[0]);

//Person and weapon
int fistAttack = 2; //Attack power without weapon
int firePower = 10; //Fire damage
int ExplosivePower = 30;
int gold = 1000; //Start with no money

struct player
{
    string name;
    int health;
    int attack;
};
player Player;

struct item
{
    string sword_name;
    int attackPower;
    int cost;
    bool weapon;
};

//Items and abilities
const string healthPotion = "Health Potion", attackPotion = "Attack Potion", rustySword = "Rusty Sword", 
        sword = "Sword", longSword = "Long Sword", greatSword = "Great Sword", crystalSword = "Crystal Sword",
        bow = "Bow", fire = "Fire",explosiveFire = "Explosive Fire";

item item_array[9] = 
{
    {healthPotion, 0, 20, false},
    {attackPotion, 0, 20, false},
    {rustySword, 4, 5, true},
    {sword, 6, 20, true},
    {longSword, 8, 50, true},
    {greatSword, 10, 100, true},
    {crystalSword, 15, 500, true},
    {bow, 50, 100, true},
    {stones[0], 0, 1000, false}
};

//Merch
string swordItems[6] = { rustySword, sword, longSword, greatSword, crystalSword, bow };
string allItems[9]{ rustySword, sword, longSword, greatSword, crystalSword, healthPotion, attackPotion, bow, stones[0] };
int swordAttackPower[6] = { 4, 6, 8, 10, 15, 8 };
int itemCost[9] = { 5, 20, 50, 100 ,500, 20, 40, 50, 1000 };

vector <string> merchItems;
vector <int> merchCost;

const int sizeAllItemsList = sizeof(allItems) / sizeof(allItems[0]);

string aroundNeck = ""; //If playes has something around the neck.
bool neck = false;

struct monster
{
    string monster_name;
    int monster_health;
    int monster_attack;
};

monster monster_arr[4] = 
{  
    {"Goblin", 10, 1},
    {"Wolf", 15, 2},
    {"Werewolf", 25, 4},
    {"Wyvern", 40, 6}  
};

bool hiddenStone = false; //Hidden stone in the Underground


bool allStonesFound();
void getPlaces();
//Bag
void CheckBag();
void removeFromBag(string remove);
void putInBag(string item);
bool fullBag();
//Letters
void checkLetters();
void foundLetter(string str);
//Abilities
void checkAbilities();
//Fighting functions
int randomEnemie();
int weapons();
bool fight(int enemieInFight, string playerName);
bool lookForPotion(string potion);
void getReward(int enemieInFight);
string randomItem();
//Quest functions
int getQuests();
bool quest(string playerName, int QuestNumber);
//Merchant
void merchantItems();
void sellItemToMerchant();
//Explore functions
bool undergroundDarkRoom(int seeInTheDark, bool first, bool treasure);
//Help Functions
int i_inputWithClear();
string s_inputWithClear();


int main()
{
    /*
    INIT start
    */
    srand(time(0));
    Player.health = 15;
    bool startGame = false;
    string play = "", s_choice;

    //Treasures found in the places and persons you can meet.
    bool treasure_underground = false, treasure_mountain = false, treasure_forrest = false,
        treasure_ruinedCity = false, treasure_animalKingdom = false,
        person_mountain = false, person_forrest = false, person_ruinedCity = false;
    //Treasures, keys, items
    string  treasure_und = "Purple Gem", treasure_mou = "Unique stone - mountain", treasure_forr = "",
        treasure_rui = "", treasure_ani = "",
        key_und = "It seems to be some sort of code, what is it for?", key_mou = "Necklace - " + places[1], key_forr = "Big key",
        map_rui = "Map of a forrest", key_ani = "", flashlight = "Flashlight";
    bool keyUnder = false, keyForrest = false, chestForrest = false, chestForrestSword = false, _map_ruin = false;

    //Letters
    string undLetter = "\"Brother, i did what you said. I Found the brick with the symbol.\nIt was easy to pull out.\"";

    bool  bag_full = false, firstTime = true,
        firstTimeUnder = true, firstTimeWallUnder = true, firstTimePathUnder = true, firstTimeRoomUnder = true, 
        leaveUnderground = false, abilityUnder = false, foundSecretWallunder = false,
        firstTimeCave = false, exploreMountain = true, necklacesMountain = false,
        firstTimeForrest = true, exploreForrest = true, searchTentForrest = true, tentFirstTimeForrest = true, 
        firstTimePathForrest = true, firstTimePathForrest_ = true, firstTimeHidden = true,
        firstTimeruins = true, safe = false, goBackSafe = false, firstTimeSafe = true,
        firstTimeWolf = true,
        ifLetter = false;

    //Loops
    bool goBackPathUnder = true, continueFight = true, exploring = true;

    int explore = 0, go = 0, choice = 0;

    //Fighting
    bool firstTimeFight = true;
    bool IfBagFull = false;

    cout << "Welcome to the Adventure Game!\n\n[PLAY] / [P]\n\n[EXIT] / [E]\n";
    cin >> play;
    system("cls");

    if (play == "PLAY" || play == "P" || play == "play" || play == "p")
    {
        cout << "Hello adventurer! \nWhats you name?\n: ";
        cin >> Player.name;
        cout << endl;
        startGame = true;
        system("cls");
    }
    else
    {
        startGame = false;
    }
    /*
    INIT END
    */

    while (startGame)
    {
        if (firstTime)
        {
            cout << "Hello " << Player.name << ". \nYou can choose to explore the world!"
                    " Or you can fight monsters! \nIt's all up to you!\n\n"
                    "[1] Explore!\n[2] Fight!\n[3] Check Bag\n[4] Check letters\n[5] End Game\n";

        }
        else
        {
            cout << Player.name << endl << "Health = " << Player.name << "\n\n" <<
                    "[1] Explore The World!\n[2] Fight Monsters!\n[3] Talk to Merchant\n"
                    "[4] Check Bag\n[5] Check letters\n[6] End Game\n";
        }
        explore = i_inputWithClear();
        if (firstTime && explore > 2)
        {
            ++explore;
        }
        firstTime = false;

        if (explore == 1)
        {
            exploring = true;
            while (exploring)
            {

                cout << "Where do you want to explore " << Player.name << "?\n\n";
                getPlaces();
                go = i_inputWithClear();
                --go;

                switch (go)
                {
                case 0: //Underground
                    cout << "Welcome to the " << places[go] << "!\nYou feel the cold air on your skin and shivers"
                        "length your spine. The \nheavy air fill your lungs.\n\n";
                    leaveUnderground = false;
                    while (!leaveUnderground)
                    {
                        //Print out diffrent text depending on if its your first time or not
                        if (firstTimeUnder)
                        {
                            cout << "You walk around and step into a room. There's a small passage to the left.\n\n"
                                << "[1] Go left\n[2] Inspect the room\n[3] Check bag\n[4] Check letters\n[B] ack\n" << endl;
                            firstTimeUnder = false;
                        }
                        else
                        {
                            cout << "You're standing inside a room. There is a small passage to the left.\n\n"
                                << "[1] Go left\n[2] Inspect the room\n[3] Check bag\n[4] Check letters\n[B] ack" << endl;
                        }
                        
                        s_choice = s_inputWithClear();

                        if( s_choice == "b" || s_choice == "B")
                        {
                            choice = 5;
                        }
                        else
                        {
                            choice = stoi(s_choice);
                        }
                        switch (choice)
                        {
                        case 1://Small passage
                            if (firstTimePathUnder) //First time
                            {
                                cout << "You walk down the path, feeling intimidated from all of the skulls looking at you.\n"
                                    "Determined, you continue down the end of the path.\n .  .  . \n";
                                firstTimePathUnder = false;
                            }
                            else
                            {
                                cout << "It's not like it's your first time walking down this path, but it sure is creepy!\n";
                            }
                            goBackPathUnder = true;
                            while (goBackPathUnder)
                            {
                                cout << "To the left side there's a cell where the light comes from and to \n"
                                    "the right lays a room in total darkness.\n\n"
                                    "[1] Left\n[2] Right\n[3] Go back!\n\n";
                                choice = i_inputWithClear();
                                if (choice == 1)
                                {
                                    if (firstTimeRoomUnder)
                                    {
                                        cout << "You walk around in the cell, alot of skulls cover the walls, giving of \n"
                                            "a creepy feeling. You see something poke out from between two of the heads, \n"
                                            "you hesitate but still take it.\n"
                                            "It's a letter:\n" << undLetter << "\n\n"
                                            "You keep the letter, maybe it can be useful.\n\n";

                                        foundLetter(undLetter);
                                        ifLetter = true;
                                        firstTimeRoomUnder = false;
                                    }
                                    else
                                    {
                                        cout << "You walk around the room trying to find something more of interest.\n"
                                            "A couple of things look intresting, but nothing worth taking.\n\n";
                                    }
                                }
                                else if (choice == 2)
                                {
                                    bool foundFlashlight = false;
                                    bool foundFire = false;

                                    for (int i = 0; i < sizeOfBag; i++)
                                    {
                                        if (bag[i] == "Flashlight")
                                        {
                                            foundFlashlight = true;
                                        }
                                    }
                                    for (int i = 0; i < numberOfAbilities; i++)
                                    {
                                        if (abilities[i] == fire)
                                        {
                                            foundFire = true;
                                        }
                                    }
                                    if (foundFlashlight || foundFire)
                                    {
                                        cout << "It's to dark to see.\nUse:\n\n";
                                    }
                                    if (foundFlashlight && foundFire)
                                    {
                                        cout << "[1] " << flashlight << "\n[2] " << fire << "\n[3] Go back" << endl;
                                        cin >> choice;
                                        system("cls");
                                        if (choice == 1 || choice == 2)
                                        {
                                            undergroundDarkRoom(choice, abilityUnder, treasure_underground);
                                        }
                                        else if (choice == 3)
                                        {
                                            cout << "You decide not to do anything and turn around.\n\n";
                                        }
                                        else
                                        {
                                            cout << "You cant do that\n\n";
                                        }
                                        if (hiddenStone && !treasure_underground)
                                        {
                                            cout << "[1] Take the stone \n[2] Leave it\n";
                                            cin >> choice;
                                            system("cls");
                                            if (choice == 1)
                                            {
                                                bool ifFull = fullBag();
                                                if (ifFull)
                                                {
                                                    cout << "Your bag is full so you cant take the stone.\n";
                                                }
                                                else if (!ifFull)
                                                {
                                                    cout << "You take the stone.\n";
                                                    for (int i = 0; i < sizeOfBag; i++)
                                                    {
                                                        if (bag[i] == x)
                                                        {
                                                            bag[i] = stones[1];
                                                            treasure_underground = true;
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else if (foundFlashlight)
                                    {
                                        cout << "[1] " << flashlight << "\n[2] Go back\n" << endl;
                                        cin >> choice;
                                        system("cls");
                                        if (choice == 1)
                                        {
                                            undergroundDarkRoom(choice, abilityUnder, treasure_underground);
                                            for (int i = 0; i < numberOfAbilities; i++)
                                            {
                                                if (abilities[i] == "")
                                                {
                                                    abilities[i] = fire;
                                                    break;
                                                }
                                            }
                                            abilityUnder = true;
                                        }
                                        else if (choice == 2)
                                        {
                                            cout << "You decide not to do anything and turn around.\n\n";
                                        }
                                        else
                                        {
                                            cout << "You cant do that\n\n";
                                        }

                                    }
                                    else
                                    {
                                        cout << "You dont have anything that can be used to see in the dark.\n"
                                            "If you continue to explore you might find something.\n\n";
                                    }

                                }
                                else if (choice == 3)
                                {
                                    cout << "You realize this might've been a bad idea and quickly turn around and go back!\n\n";
                                    goBackPathUnder = false;
                                }
                            }
                            break;

                        case 2://Wall

                            for (int i = 0; i < numberOfLetters; i++)
                            {
                                if (letters[i] == undLetter)
                                {
                                    ifLetter = true;
                                    break;
                                }
                            }
                            if (ifLetter && !foundSecretWallunder)
                            {
                                cout << "You look at the wall and remember the letter you found:\n\n" << undLetter << endl << endl <<
                                    "Could it be this wall the letter mentioned? You closely inspect the wall for \n"
                                    "the symbol. You try moving one of them. Hmmm. . . maybe they were talking about\n"
                                    "another wall. You search some more and find another brick with a symbol on it.\n"
                                    "It moves! You start trying to pull it out, but it's hard. After some time you\n"
                                    "manage to get it out. Inside you find a pice of paper. Looks like some kind of\n"
                                    "code written on it. You put it in your bag.\n\n";

                                foundLetter(key_und);
                                keyUnder = true;
                                foundSecretWallunder = true;
                            }
                            else if (ifLetter && foundSecretWallunder)
                            {
                                cout << "Nothing more to find here.\n\n";
                            }
                            else if (firstTimeWallUnder == true)//First time
                            {
                                cout << "You inspect the room, it's empty. You look at the wall, the bricks looks old and dusty.\n"
                                    "On some of the bricks you can see symbols. You feel around not sure what you're looking for.\n"
                                    "But you don't find it.\n\n";
                                firstTimeWallUnder = false;
                            }
                            else if (firstTimeWallUnder == false)//Not the first time
                            {
                                cout << "I hope the wall doesn't fall! Sure looks old.\n\n";
                            }
                            break;
                        case 3:
                            CheckBag();
                            break;
                        case 4:
                            checkLetters();
                            break;
                        case 5:
                            cout << "You leave the Underground and feel the pressure fade away.\n\n";
                            leaveUnderground = true;
                            break;
                        default:
                            cout << "WHAT! I CANT GO THERE!\n";
                            break;
                        }
                    }
                    break;

                case 1://Mountain
                    exploreMountain = true;
                    cout << "Welcome to the " << places[go] << "!\n" <<
                        "You feel energizd from the fresh air and the beautiful view of the mountain.\n\n";
                    while (exploreMountain)
                    {
                        cout << "[1] Explore!\n[2] Leave\n\n[3] Check Bag\n[4] Check letters\n";
                        choice = i_inputWithClear();
                        if (choice == 1)
                        {
                            cout << "You walk alongside a cliff on the mountian road. You stop and look up.\n";
                            while (true)
                            {
                                cout << "You're standing in front of a big tree.\n\n"
                                    << "[1]Climb the tree\n[2]Pass the tree\n[3]Leave the mountain" << endl;

                                choice = i_inputWithClear();

                                if (choice == 1)
                                {
                                    if (treasure_mountain == false)
                                    {
                                        cout << "You climb the tree, it looks like there's something "
                                            "on one of the branches. \nYou find a stone with a unique pattern.\n\n"
                                            "[1] Take the stone\n[2] Leave the stone\n";
                                        choice = i_inputWithClear();
                                        if (choice == 1)
                                        {
                                            IfBagFull = fullBag();
                                            if (!IfBagFull)
                                            {
                                                for (int i = 0; i < sizeOfBag; i++)
                                                {
                                                    if (bag[i] == x)
                                                    {
                                                        bag[i] = stones[2];
                                                        cout << "You take the stone and put it in your backpack and climb back down again\n";
                                                        treasure_mountain = true;
                                                        break;
                                                    }
                                                }
                                            }
                                            if (IfBagFull)
                                            {
                                                cout << "You dont have space in your bag and have to leave the stone\n";
                                            }
                                        }
                                        else if (choice == 2)
                                        {
                                            cout << "You leave the stone where you found it and climb down.\n\n";
                                        }
                                        else
                                        {
                                            cout << "You cant do that!\n\n";
                                        }
                                    }
                                    else
                                    {
                                        cout << "You find nothing new, but sit down and enjoy the view.\n"
                                            "After a while you climb down again, feeling refreshed.\n\n";
                                    }
                                }
                                else if (choice == 2)
                                {
                                    cout << "You pass the tree and see a cave entrance!\n";
                                    while (true)
                                    {
                                        cout << "You're standing in front of the cave\n\n[1]Explore the cave.\n[2]Go back\n\n";
                                        choice = i_inputWithClear();

                                        if (choice == 1)
                                        {
                                            if (firstTimeCave == false)
                                            {
                                                cout << "You decide you're brave enough to face the cave and walk in.\n"
                                                    "Strange noises can be heard from deep inside the cave. You walk \n"
                                                    "slowly forward and look around the corner. A boy no more than 10 \n"
                                                    "years old is crying. Looks like he's stuck between two rocks.\n\n"
                                                    "[1] Help the poor boy\n[2] Pretend you didnt see anything and stealthy walk away.\n\n";
                                                choice = i_inputWithClear();
                                                if (choice == 1)
                                                {
                                                    cout << "You walk up to the boy with your hand out. You ask him if he's \n"
                                                        "okej and if you can help him. You gain the boy's trust and are able \n"
                                                        "to free him. He thanks you, crying of relif, and wants to give you a \n"
                                                        "necklace as a thank you gift.\n\n"
                                                        "[1] Accept the gift and the gratitude from the boy\n"
                                                        "[2] Tell him you cant possibly accept such a precius gift\n\n";
                                                    choice = i_inputWithClear();
                                                    if (choice == 1)
                                                    {
                                                        cout << "You see the boy out and wave him goodbye\n\n";
                                                    }
                                                    else if (choice == 2)
                                                    {
                                                        cout << "While you hesitate you look down at the necklace in your hand.\n"
                                                            "You look up to tell him that you cant accept the necklace, but \n"
                                                            "the boy is nowhere in sight. Bewildered, you walk out from the cave.\n\n";
                                                    }
                                                    cout << "You study the necklace carefully... it kind of looks like a. . . Key?\n\n";
                                                    bag_full = true;
                                                    for (int i = 0; i < sizeOfBag; i++)
                                                    {
                                                        if (bag[i] == x)
                                                        {
                                                            cout << "You put the neckless in your bag.\n\n";
                                                            bag[i] = key_mou;
                                                            necklacesMountain = true;
                                                            bag_full = false;
                                                            break;
                                                        }
                                                    }
                                                    if (bag_full)
                                                    {
                                                        if (!neck)
                                                        {
                                                            cout << "Your bag is too full, you hang it around your neck instead.\n";
                                                            aroundNeck = key_mou;
                                                            neck = true;
                                                        }
                                                        else
                                                        {
                                                            cout << "Your bag is too full, you hide the neckless near the cave.\n";
                                                        }
                                                    }
                                                    person_mountain = true;
                                                }
                                                else if (choice == 2)
                                                {
                                                    cout << "You slowly turn around and walk out\nBetter to explore the cave another time.\n\n";
                                                }
                                                else
                                                {
                                                    cout << "Not sure what i was trying to do.\n\n";
                                                }

                                                firstTimeCave = true;
                                            }
                                            else
                                            {
                                                cout << "You went into the cave.\n\n";
                                                if (person_mountain)
                                                {
                                                    std::cout << "You explore the cave to your hearts content and walk out with your"
                                                        "\nadventure spirit fired up!!\n\n";
                                                }
                                                else if (!person_mountain)
                                                {
                                                    cout << "While you exlore you abruptly stop, almost tripping over your own feet."
                                                        "\nThe boy! The boy's still here!\n\n"
                                                        "[1] Help him\n[2] Quickly leave before the boy see you!\n";
                                                    choice = i_inputWithClear();
                                                    if (choice == 1)
                                                    {
                                                        cout << "Walking out like you didnt know he was there and gasp in surprise\n"
                                                            "You ask him what he's doing. The boy sniffles and says he needs help to\n"
                                                            "get free from the rocks.He got stuck while he was playing. You help him \n"
                                                            "quickly and lead him out of the cave. When you're outside, the boy suddently\n"
                                                            "realize how late it's gotten and shove a necklace into your hand. You study \n"
                                                            "the necklace carefully... it kind of looks like a. ..Key ? \n";
                                                        bag_full = true;
                                                        for (int i = 0; i < sizeOfBag; i++)
                                                        {
                                                            if (bag[i] == "")
                                                            {
                                                                cout << "You put the neckless in your bag.\n";
                                                                bag[i] = key_mou;
                                                                bag_full = false;
                                                                break;
                                                            }
                                                        }
                                                        if (bag_full)
                                                        {
                                                            if (!neck)
                                                            {
                                                                cout << "Your bag is too full, you hang it around your neck instead.\n\n";
                                                                aroundNeck = key_mou;
                                                                neck = true;
                                                            }
                                                            else
                                                            {
                                                                std::cout << "Your bag is too full, you hide the neckless near the cave.\n";
                                                            }
                                                        }
                                                        person_mountain = true;
                                                    }
                                                    else if (choice == 2)
                                                    {
                                                        cout << "You run out.\n\n";
                                                        //ignore_person_mountain += 1;
                                                    }
                                                    else
                                                    {
                                                        cout << "You cant do that.\n";
                                                    }
                                                }
                                            }
                                        }
                                        else if (choice == 2)
                                        {
                                            cout << "You go back.\n";
                                            break;
                                        }
                                        else
                                        {
                                            cout << "What are you trying to do!?\n";
                                        }
                                    }
                                }
                                else if (choice == 3)
                                {
                                    cout << "You leave the mountain.\n";
                                    exploreMountain = false;
                                    break;
                                }
                                else
                                {
                                    cout << "WHAT! I CANT GO THERE!\n";
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            cout << "You leave the mountain to explore somewhere else!\n";
                            break;
                        }
                        else if (choice == 3)
                        {
                            CheckBag();
                        }
                        else if (choice == 4)
                        {
                            checkLetters();
                        }
                    }
                    break;
                case 2://Phantom Forrest

                    exploreForrest = true;
                    cout << "Welcome to the " << places[go] << "!\n" <<
                        "This is the place where the dead comes to play! Or so they say.\n\n";

                    while (exploreForrest)
                    {
                        cout << "[1] Explore the forrest\n[2] Leave\n\n[3] Check Bag\n[4] Check letters\n";
                        cin >> choice;
                        system("cls");
                        if (choice == 1)
                        {
                            cout << "The moment you step into the forrest you feel watched.\n\n";
                            if (firstTimeForrest)
                            {
                                cout << "You trample around in the forrest searching for something intresting.\n"
                                    "You find a tent. After a quick look around, you realize it has probobly\n"
                                    "been abandoned for quite some time.\n\n";
                            }
                            else
                            {
                                cout << "You start your exploration and come to the familiar tent.\n\n";
                            }

                            while (true)
                            {
                                if (_map_ruin && firstTimeHidden)
                                {
                                    cout << "You take the map you found and see that there's a hidden path.\n";
                                }
                                cout << "You're standing infront of the tent.\n\n";
                                cout << "[1] Search the tent\n[2] Continue exploring\n[3] Check bag\n[4] Leave\n" << endl;
                                if (_map_ruin)
                                {
                                    cout << "[5] Hidden path.\n";
                                }

                                cin >> choice;
                                system("cls");

                                if (choice == 1)//Search tent
                                {
                                    if (searchTentForrest)
                                    {
                                        if (tentFirstTimeForrest)
                                        {
                                            cout << "You carefully zip open the tent and step in. You search through\n"
                                                "the tent meticulously. You find moldy food and old clothes. Nothing\n"
                                                "of real value. When you turn around and is about to leave the tent, you\n"
                                                "almost hit you head on a flashligt thats been tied to the cealing.\n"
                                                "You push the button on it and it works! Some of the times at least.\n\n";
                                            tentFirstTimeForrest = false;
                                        }
                                        else
                                        {
                                            cout << "You walk into the tent again, you find nothing new. The flashlight\n"
                                                "still hangs from the ceiling.\n\n";
                                        }
                                        cout << "[1] Take the flashlight\n[2] Leave the flashlight\n";
                                        cin >> choice;
                                        system("cls");
                                        bool _fullBag = fullBag();

                                        if (choice == 1)
                                        {
                                            if (!_fullBag)
                                            {
                                                for (int i = 0; i < sizeOfBag; i++)
                                                {
                                                    if (bag[i] == x)
                                                    {
                                                        bag[i] = flashlight;
                                                        cout << "You put the flashlight into your backback, maybe it could be useful.\n";
                                                        searchTentForrest = false;
                                                        break;
                                                    }
                                                }
                                                if (_fullBag)
                                                {
                                                    cout << "You dont have space in your bag and have to leave the flashlight\n\n";
                                                }
                                            }
                                            else
                                            {
                                                cout << "You couldn't take the flashlight because you dont have space in your bag.\n\n";
                                            }
                                        }
                                        else if (choice == 2)
                                        {
                                            cout << "You leave the flashlight where it is and walk out.\n\n";
                                        }
                                        else
                                        {
                                            cout << "You cant do that!\n\n";
                                        }
                                    }
                                    else
                                    {
                                        cout << "You decide to take one more look in the tent, maybe there's something \n"
                                            "you've missed. You find nothing you want and walk out again.\n\n";
                                    }
                                }
                                else if (choice == 2)//Continue exploring
                                {
                                    while (true)
                                    {
                                        if (firstTimePathForrest)
                                        {
                                            cout << "You walk further into the forrest and find a path you start to follow.\n"
                                                "Suddenly it starts getting colder and colder the further down the path\n"
                                                "you go. While you continue to walk you come a cross a pond. Above a big\n"
                                                "stone you see a shadow hovering.\n\n[1] Go to the shadow\n[2] Go back\n";
                                            firstTimePathForrest = false;
                                        }
                                        else if (!firstTimePathForrest && firstTimePathForrest_)
                                        {
                                            cout << "You come to the pond again. The shadow is still there.\n[1] Go to the shadow\n[2] Go back\n";

                                        }
                                        if (firstTimePathForrest || firstTimePathForrest_)
                                        {
                                            cin >> choice;
                                            system("cls");

                                            if (choice == 1)
                                            {
                                                cout << "You decide to find out what the shadow could be. The closer you get,\n"
                                                    "the more of the shadow you can see. You start hearing a voice.\n"
                                                    "You look around, you never really thought you would see a ghost. But\n"
                                                    "the thing in front of you definitly is a ghost. You start to talk to \n"
                                                    "it. You use a soothing voice and explain that you're an adventurer. \n"
                                                    "The ghost stop mumbeling to it self and turn around to face you. You\n"
                                                    "bravely stand still and let the ghost examine you from head to toe.\n"
                                                    "You can see that the ghost was once a young woman. She smiles at you.\n\n"
                                                    "The ghost wants to give you something\n[1] Accept\n[2] Refuse.\n";

                                                firstTimePathForrest_ = false;

                                                cin >> choice;
                                                system("cls");

                                                if (choice == 1)
                                                {
                                                    cout << "You accept the gift and watch while the young girl disappears infront\n"
                                                        "of you. The ghost gave you a big strange looking key.\n\n";
                                                    IfBagFull = fullBag();
                                                    if (!IfBagFull)
                                                    {
                                                        putInBag(key_forr);
                                                        keyForrest = true;
                                                        for (int i = 0; i < sizeOfBag; i++)
                                                        {
                                                            if (bag[i] == key_forr)
                                                            {
                                                                bag[i] = key_forr + " - " + places[2];
                                                                break;
                                                            }
                                                        }
                                                        cout << "You go back.\n";
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        cout << "Your bag is full and you couldn't take the key. You go back.\n\n";
                                                        keyForrest = false;
                                                        break;
                                                    }
                                                }
                                                else if (choice == 2)
                                                {
                                                    cout << "You put the key on the rock and leave.\n\n";
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << "something want wrong.\n\n";
                                                }
                                            }
                                            else if (choice == 2)
                                            {
                                                cout << "You go back to the tent.\n\n";
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Something went wrong.\n\n";
                                            }
                                        }
                                        else
                                        {
                                            cout << "How much you try to exploring the forrest you somehow always end up\n"
                                                "at the pond.\n\n";
                                            if (!keyForrest)
                                            {
                                                cout << "The ghost is back and stand close to the stone, you kan see the\n"
                                                    "big key on the stone.\n\n[1] Take key\n[2] Go back\n";
                                                cin >> choice;
                                                if (choice == 1)
                                                {
                                                    IfBagFull = fullBag();
                                                    if (!IfBagFull)
                                                    {
                                                        putInBag(key_forr);
                                                        keyForrest = true;
                                                        cout << "You go back.\n\n";
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        cout << "You couldn't take the key and go back.\n";
                                                        keyForrest = false;
                                                        break;
                                                    }
                                                }
                                                else if (choice == 2)
                                                {
                                                    cout << "You ignore the ghost and the key and go back.\n";
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                cout << "You watch the pond and feel a sence of peace. When your done\n"
                                                    "you go back.\n";
                                                break;
                                            }
                                        }
                                    }
                                }
                                else if (choice == 3)
                                {
                                    CheckBag();
                                }
                                else if (choice == 4)//Leave
                                {
                                    cout << "You leave the forrest.\n\n";
                                    exploreForrest = false;
                                    break;
                                }
                                else if (choice == 5 && _map_ruin)  // Hidden path, you need kod from underground and map from ruins.
                                {
                                    if (!chestForrest)
                                    {
                                        if (firstTimeHidden)
                                        {
                                            cout << "You go down the hidden path. It was covered with alot if vegetation and was\n"
                                                "hard to see. In the end of the path there's a chest. It has strange symbols\n"
                                                "on it.\n\n";
                                            firstTimeHidden = false;
                                        }
                                        else
                                        {
                                            cout << "You go down the path again and see the chest.\n\n";
                                        }

                                        if (keyUnder)
                                        {
                                            cout << "You recognize the symbols on the chest and take up the kod you found in\n"
                                                "the " << places[0] << ". You feel the symbols on the chest and realize\n"
                                                "they are lika buttons. You push the symbols in the right order and you \n"
                                                "hear a pop. The chest opened!\n\nYou find 300 gold and a Crystal sword!\n\n"
                                                "Crystal swords are one of the best swords that can be made.\n\n"
                                                "[1] Take the sword\n[2] Leave the sword\n";

                                            chestForrest = true;

                                            gold += 300;
                                            cin >> choice;
                                            system("cls");

                                            if (choice == 1)
                                            {
                                                IfBagFull = fullBag();
                                                if (!IfBagFull)
                                                {
                                                    putInBag(swordItems[4]);
                                                    chestForrestSword = true;
                                                    cout << "You go back.\n";
                                                }
                                                else
                                                {
                                                    cout << "Your bag is full and you cant take the sword.\n\n";
                                                }
                                            }
                                            if (choice == 2)
                                            {
                                                cout << "You choose not to take the word.\n\n";
                                                chestForrestSword = false;
                                            }
                                        }
                                        else
                                        {
                                            cout << "You cant recognize the symbols. How much you try, you cant get the chest to open.\n"
                                                "You go back\n\n";
                                        }
                                    }
                                    else
                                    {
                                        if (!chestForrestSword && keyUnder)
                                        {
                                            cout << "You follow the path and come to the chest again. You open it and\n"
                                                "the sword is still there.\n\n[1] Take the sword\n[2] Leave it\n";
                                            cin >> choice;
                                            if (choice == 1)
                                            {
                                                IfBagFull = fullBag();
                                                if (!IfBagFull)
                                                {
                                                    putInBag(swordItems[4]);
                                                }
                                                else
                                                {
                                                    cout << "You can't take the sword and leave it.\n\n";
                                                }
                                            }
                                            else if (choice == 2)
                                            {
                                                cout << "You leave the sword in the chest and go back.\n\n";
                                            }
                                            else
                                            {
                                                cout << "You can't do that.\n\n";
                                            }
                                        }
                                        else if (chestForrestSword)
                                        {
                                            cout << "There's nothing new in the chest. You go back.\n\n";
                                        }
                                        else if (!keyUnder)
                                        {
                                            cout << "You come to the chest but theres nothing new. You cant open it.\n"
                                                "You go back.\n\n";
                                        }
                                        else
                                        {
                                            cout << "Something went wrong!\n\n";
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "WHAT! I CANT GO THERE!\n";
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            cout << "You leave the mountain to explore somewhere else!\n";
                            break;
                        }
                        else if (choice == 3)
                        {
                            CheckBag();
                        }
                        else if (choice == 4)
                        {
                            checkLetters();
                        }
                    }

                    break;
                case 3://Ruined city
                    cout << "Welcome to the " << places[go] << "!\n" <<
                        "The " << places[go] << " is a very restricted area. It's a place left\n"
                        "behind after war. ";

                    while (true)
                    {
                        cout << "You're standing in one of the safe zones, \nthere's rubble everywere.\n";
                        cout << "\n[1] Search ruins\n[2] Check bag\n[3] Check Letters\n[4] Leave\n" << endl;
                        choice = i_inputWithClear();
                        bool back = false;

                        if (choice == 1)
                        {
                            if (goBackSafe)
                            {
                                cout << "[1] Explore a new area\n[2] Go to safe\n[3] Go back\n";
                                choice = i_inputWithClear();
                                if (choice == 1)
                                {
                                    int diffrentText = rand() % 3 + 1;
                                    if (diffrentText == 1)
                                    {
                                        int _gold = rand() % 50 + 1;
                                        gold += _gold;
                                        cout << "You explore a new area. You find " << _gold << " gold in the rubble.\n\n";

                                    }
                                    else if (diffrentText == 2)
                                    {
                                        cout << "Walking around looking for something interesting you stumble upon a\n"
                                            "old teddybear. You look at it with a sence of sadness. You go back.\n\n";
                                    }
                                    else if (diffrentText == 3)
                                    {
                                        cout << "You walk around looking at the ruins. You find nothing you want to \n"
                                            "take. You go back.\n\n";
                                    }
                                }
                                if (choice == 2)
                                {
                                    back = true;
                                }
                                else if (choice == 3)
                                {
                                    cout << "You go back.\n\n";
                                }
                            }
                            if (firstTimeruins || back)
                            {
                                if (firstTimeruins)
                                {
                                    cout << "You decide to explore the ruins. There's a lot of rubble everywhere.\n"
                                        "You go to the most interesting looking pile. While you go through the\n"
                                        "rubble you find that the rubble had hidden a safe!\n\n";
                                    goBackSafe = true;
                                    firstTimeruins = false;
                                }
                                else if (back)
                                {
                                    cout << "You go back to the safe.\n\n";
                                }

                                if (necklacesMountain && firstTimeSafe)
                                {
                                    cout << "You recognize the strange looking keyhole, it has the same form as the\n"
                                        "neckless you got from the little boy. You find a " << stones[3] << " and\n"
                                        "a map of a forrest.\n\n"
                                        "[1] Take the " << stones[3] << "\n[2] Leave it\n";
                                    firstTimeSafe = false;
                                    _map_ruin = true;
                                    foundLetter(map_rui);
                                    choice = i_inputWithClear();
                                    if (choice == 1)
                                    {
                                        IfBagFull = fullBag();
                                        if (!IfBagFull)
                                        {
                                            putInBag(stones[3]);
                                            safe = true;
                                        }
                                        else
                                        {
                                            cout << "Your bag is full, you couldn't take the stone.\n\n";
                                            safe = false;
                                        }
                                    }
                                    else if (choice == 2)
                                    {
                                        cout << "You don't take the stone and go back.\n\n";
                                    }
                                }
                                else if (necklacesMountain && !firstTimeSafe && !safe)
                                {
                                    cout << "You see the stone in the safe.\n\n[1] Take stone\n[2] leave it\n\n";
                                    choice = i_inputWithClear();
                                    if (choice == 1)
                                    {
                                        IfBagFull = fullBag();
                                        if (IfBagFull)
                                        {
                                            putInBag(stones[3]);
                                            cout << endl;
                                        }
                                        else
                                        {
                                            cout << "You couldn't take the stone.\n\n";
                                        }
                                    }
                                    else
                                    {
                                        cout << "You go back.\n\n";
                                    }
                                }
                                else if (!necklacesMountain)
                                {
                                    cout << "What a strange looking keyhole, you try to open it, but seems\n"
                                        "impossible. You go back.\n\n";
                                }
                                else if (safe)
                                {
                                    cout << "You see nothing new in the safe or around it. You go back.\n\n";
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            CheckBag();
                        }
                        else if (choice == 3)
                        {
                            checkLetters();
                        }
                        else if (choice == 4)
                        {
                            cout << "You leave the " << places[go] << ".\n\n";
                            break;
                        }
                    }
                    break;
                case 4: //Wolf Realm
                    cout << "Welcome to the " << places[go] << "!\n" <<
                        "Not many people has ever visit the " << places[go] << " as it's not rumored to be a\n"
                        "safe place.\n\n";
                    while (true)
                    {
                        cout << "You standing in a big hall. There's a big door infron of you.\n\n"
                            "[1] Open door\n[2] Check bag\n[3] Check Letters\n[4] leave\n" << endl;
                        choice = i_inputWithClear();
                        if (choice == 1)
                        {
                            cout << "You walk to the big door and try the handle. It's locked.\n\n";
                            if (keyForrest)
                            {
                                cout << "You take out the " << key_forr << ". It goes in och unlocks the\n"
                                    "door!\n\n";
                                cout << "You walk in and se a big statue of a wolf. It has two holes in \n"
                                    "the two front paws.\n\n";
                                bool stonesFound = allStonesFound();
                                if (stonesFound)
                                {
                                    if (firstTimeWolf)
                                    {
                                        cout << "You remember all the stones you have found, looks like it fit. You taken\n"
                                            "out the stones and place them in the holes. The statue moves and a hidden\n"
                                            "room is revealed, you go in there.\n\n";
                                        for (int i = 0; i < 5; i++)
                                        {
                                            cout << "  .  ";
                                            Sleep(500);
                                        }
                                        cout << "\n\nIt's a big room, to one side there's a pile of gold and on the other side\n"
                                            "there's a podium with a book in center. You take the book.\n\n";
                                        gold += 1000;
                                        cout << "Light flashes around you!\n\nYou just learnd the ultimate skill \n\n"
                                            "[Explosive fire]\n\n";

                                        abilities[0] = explosiveFire;
                                        firstTimeWolf = false;
                                    }
                                    else
                                    {
                                        cout << "You have already taken everything in here.\n\n";
                                    }
                                }
                                if (!stonesFound)
                                {
                                    int numberStones = 0;
                                    for (int i = 0; i < sizeOfBag; i++)
                                    {
                                        if (bag[i] == stones[0])
                                        {
                                            ++numberStones;
                                        }
                                        else if (bag[i] == stones[1])
                                        {
                                            ++numberStones;
                                        }
                                        else if (bag[i] == stones[2])
                                        {
                                            ++numberStones;
                                        }
                                        else if (bag[i] == stones[3])
                                        {
                                            ++numberStones;
                                        }
                                    }
                                    cout << "You have found " << numberStones << " stones. You try putting them in\n"
                                            "but nothing happens. You need all four stones.\n\n";
                                }
                            }
                            else if (!keyForrest)
                            {
                                cout << "There's a big keyhole, you have to explore more to find it. You\n"
                                    "go back\n\n";
                                break;
                            }

                        }
                        else if (choice == 2)
                        {
                            CheckBag();
                        }
                        else if (choice == 3)
                        {
                            checkLetters();
                        }
                        else if (choice == 4)
                        {
                            cout << "You leave " << places[go] << "\n\n";
                            break;
                        }
                    }

                    break;
                case 5://Loop throuh you bag 
                    CheckBag();
                    break;
                case 6://Letters
                    checkLetters();
                    break;
                case 7:
                    cout << "You decied you've explored enough today and go back\n\n";
                    exploring = false;
                    break;
                default:
                    cout << "You have to choose a place that exist!\n" << endl;
                    break;
                }
            }
        }
        else if (explore == 2)
        {
            continueFight = true;
            cout << "You choose to fight monsters!\n";
            if (firstTimeFight)
            {
                cout << "It's your first time fighting, might be good to have something to fight with!\n"
                    "Here's a [" << rustySword << "] and a [" << healthPotion << "] to help you out in time of need.\n\n";
                putInBag(rustySword);
                putInBag(healthPotion);
                firstTimeFight = false;
            }
            while (continueFight)
            {
                int enemie1 = 0;

                cout << "Ask around or go to the quest board to find monsters to fight.\n\n"
                    "[1] Ask around\n[2] Quest board\n[3] Check bag\n[4] Leave\n";
                choice = i_inputWithClear();
                if (choice == 1)
                {
                    int changeText = rand() % 2 + 1;
                    if (changeText == 1)
                    {
                        cout << "You ask around and find information of a place where monsters often frequent.\n\n";
                    }
                    else if (changeText == 2)
                    {
                        cout << "While you ask around a little girl showes up and hurriedly tell you about a\n"
                            "dangerouse place her father almost got killed at.\n\n";
                    }
                    cout << "[1] Go there!\n[2] Go back\n\n[3] check bag\n";
                    choice = i_inputWithClear();
                    if (choice == 1)
                    {

                        cout << "You get ready and quickly leave to fight monsters!\n\n";
                        enemie1 = randomEnemie();
                        int monsterHealth = monster_arr[enemie1].monster_health;

                        int interact = rand() % 2;
                        if (interact == 0)
                        {
                            cout << "A " << monster_arr[enemie1].monster_name << " | " << monsterHealth << "/" << monster_arr[enemie1].monster_health
                                << " came!\n\n";
                        }
                        else if (interact == 1)
                        {
                            cout << "You come across a " << monster_arr[enemie1].monster_name << " | " << monsterHealth << "/" << monster_arr[enemie1].monster_health
                                << ".\n\n";
                        }
                        continueFight = fight(enemie1, Player.name);
                        startGame = continueFight;
                    }
                    else if (choice == 2)
                    {
                        cout << "You go back, let's fight another day!\n\n";
                    }
                    else if (choice == 3)
                    {
                        CheckBag();
                    }
                }
                else if (choice == 2)
                {
                    int quest_1 = 0, quest_2 = 0, randomQuest = rand() % 2 + 1, questNumber;
                    string quest1 = "", quest2 = "";
                    string questList[2];
                    string chooseQuest = "";

                    cout << "You go to the questboard\n";
                    for (int i = 0; i < randomQuest; i++)
                    {
                        questList[i] = quests[getQuests()];

                        if (questList[0] == questList[1])
                        {
                            questList[1] = quests[getQuests()];
                        }
                    }
                    cout << "[" << 1 << "] " << questList[0] << "\n\n";
                    if (questList[1] != "")
                    {
                        cout << "[" << 2 << "] " << questList[1];
                    }
                    choice = i_inputWithClear();
                    if (choice == 1)
                    {
                        chooseQuest = questList[0];
                    }
                    else if (choice == 2)
                    {
                        chooseQuest = questList[1];
                    }

                    if (chooseQuest == quests[0])
                    {
                        questNumber = 0;
                        //questVillige(name);
                    }
                    else if (chooseQuest == quests[1])
                    {
                        questNumber = 1;
                        //questNeighbor(name);
                    }
                    else if (chooseQuest == quests[2])
                    {
                        questNumber = 2;
                        //questWolfs(name);
                    }
                    continueFight = quest(Player.name, questNumber);
                    if (!continueFight)
                    {
                        startGame = false;
                    }
                }
                else if (choice == 3)
                {
                    CheckBag();
                }
                else
                {
                    continueFight = false;
                }
            }
        }
        else if (explore == 3)
        {
            while (true)
            {
                cout << "You're inside the merchant's store.\n\n[1] Buy \n[2] Sell\n[3] Leave\n";
                choice = i_inputWithClear();
                if (choice == 1) // Buy 
                {
                    merchantItems();
                }
                else if (choice == 2) // Sell
                {
                    sellItemToMerchant();
                }
                else if (choice == 3)
                {
                    cout << "You thank the merchant and walk out.\n";
                    break;
                }
                else
                {
                    cout << "You cant do that.\n\n";
                }
            }
        }
        else if (explore == 4)
        {
            CheckBag();
        }
        else if (explore == 5)
        {
            checkLetters();
        }
        else if (explore == 6)
        {
            startGame = false;
            break;
        }
        else
        {
            cout << "You have to write a command that exist.\n";
        }
    }
}

bool allStonesFound()
{
    bool allFound = false;
    int found = 0;
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == stones[0])
        {
            ++found;
        }
        else if (bag[i] == stones[1])
        {
            ++found;
        }
        else if (bag[i] == stones[2])
        {
            ++found;
        }
        else if (bag[i] == stones[3])
        {
            ++found;
        }
    }
    if (found == 4)
    {
        cout << "You've found all stones!";
        allFound = true;
    }
    return allFound;
}
void getPlaces()
{
    for (int i = 0; i < numberOfPlaces; i++)
    {
        cout << "[" << i + 1 << "] " << places[i] << endl;
    }
    cout << "\n[6] Check your bag\n[7] Check letters\n[8] Stop exploring\n\n";
}
//Bag functions
void CheckBag()
{
    while (true)
    {
        int slots = 0;
        bool empty = true;
        int _choice = 0;

        cout << "Gold: " << gold << "\n-------------------------------------------------------\n";
        for (int i = 0; i < sizeOfBag; i++)
        {
            if (bag[i] != x)
            {
                cout << i + 1 << ". " << bag[i] << endl;
                empty = false;
            }
            else if (bag[i] == x)
            {
                slots++;
            }
        }
        cout << "-------------------------------------------------------\n";
        if (empty == true)
        {
            cout << "Your bag is empty\n";
        }
        cout << "Empty slots [" << slots << "]\n\n";
        if (empty == true)
        {
            break;
        }
        if (empty == false)
        {
            cout << "[1] Throw something\n[2] Go back\n";
            cin >> _choice;
            system("cls");

            if (_choice == 1)
            {
                cout << "What do you want to throw? Item [1 - " << sizeOfBag - slots << "]\n";
                cin >> _choice;
                bag[_choice - 1] = x;
                system("cls");
            }
            else
            {
                break;
            }
        }

    }
}
void removeFromBag(string remove)
{
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == remove)
        {
            bag[i] = x;
            break;
        }
    }
}
void putInBag(string item) {
    bool ifBagEmpty = true;
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == x)
        {
            bag[i] = item;
            cout << "You put " << item << " in your bag.\n\n";
            ifBagEmpty = false;
            break;
        }
    }
    if (ifBagEmpty)
    {
        cout << "Your bag is full and couldn't take the " << item << "\n\n";
    }
}
bool fullBag()
{
    int throwAway;
    bool ifBagFull = true;
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == x)
        {
            ifBagFull = false;
            break;
        }
    }
    if (ifBagFull)
    {
        cout << "Your bag is full, do you want to throw something away?\n[1] Throw\n[2] Dont throw\n";
        cin >> throwAway;
        if (throwAway == 1)
        {
            for (int i = 0; i < sizeOfBag; i++)
            {
                cout << "[" << i + 1 << "]" << bag[i] << endl;

            }
            cout << "What do you want to throw? Item [1 - " << sizeOfBag << "]\n";
            cin >> throwAway;
            bag[throwAway - 1] = x;
            system("cls");
            ifBagFull = false;
        }
        else if (throwAway == 2)
        {
            cout << "You dont want to throw anything away.\n";
            ifBagFull = true;
        }
    }
    return ifBagFull;
}

void checkLetters()
{
    int youHave = 0;
    cout << "--------------------------------------------------------------------------------------\n";
    for (int i = 0; i < numberOfLetters; i++)
    {
        if (letters[i] != "")
        {
            cout << i + 1 << ". " << letters[i] << "\n\n";
            youHave += 1;
        }
    }
    cout << "--------------------------------------------------------------------------------------\n";
    if (youHave != 0)
    {
        cout << "You have found " << youHave << " letters.\n\n";
    }
    else
    {
        cout << "You have not found any letters yet! Continue to explore to find them!\n\n";
    }

}
void foundLetter(string str)
{
    int i;
    for (i = 0; i < numberOfLetters; i++)
    {
        if (letters[i] == "")
        {
            letters[i] = str;
            break;
        }
    }
}

void checkAbilities()
{
    for (int i = 0; i < numberOfAbilities; i++)
    {
        if (abilities[i] != "")
        {
            cout << i << ". " << abilities[i] << endl;
        }
    }
}
//Fighting
string randomItem()
{
    string randomItem = "";
    int randomValue;

    randomValue = rand() % 5;

    switch (randomValue)
    {
    case 0:
        randomItem = "Gold";
        break;
    case 1:
        randomItem = "Gold";
        break;
    case 2:
        randomItem = rustySword;
        break;
    case 3:
        randomItem = healthPotion;
        break;
    case 4:
        randomItem = sword;
        break;
    case 5:
        randomItem = "Nothing";
        break;
    default:
        randomItem = "Nothing";
        break;
    }

    return randomItem;
}
int randomEnemie()
{
    int monster = 0;
    monster = rand() % 4;
    return monster;
}
int weapons()
{
    int nr = 2;
    int wChoice;
    weapon.clear();
    weaponDamage.clear();

    cout << "What weapon do you wanna use?\n\n[1] Fist(" << fistAttack << ")\n";
    weapon.push_back("Fist");
    weaponDamage.push_back(fistAttack);
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == swordItems[0])
        {

            cout << "[" << nr << "] " << swordItems[0] << "(" << swordAttackPower[0] << ")\n";
            weapon.push_back(bag[i]);
            weaponDamage.push_back(swordAttackPower[0]);
            ++nr;

        }
        else if (bag[i] == swordItems[1])
        {
            cout << "[" << nr << "] " << swordItems[1] << "(" << swordAttackPower[1] << ")\n";
            weaponDamage.push_back(swordAttackPower[1]);
            weapon.push_back(bag[i]);
            ++nr;
        }
        else if (bag[i] == swordItems[2])
        {
            cout << "[" << nr << "] " << swordItems[2] << "(" << swordAttackPower[2] << ")\n";
            weaponDamage.push_back(swordAttackPower[2]);
            weapon.push_back(bag[i]);
            ++nr;
        }
        else if (bag[i] == swordItems[3])
        {
            cout << "[" << nr << "] " << swordItems[3] << "(" << swordAttackPower[3] << ")\n";
            weaponDamage.push_back(swordAttackPower[3]);
            weapon.push_back(bag[i]);
            ++nr;
        }
        else if (bag[i] == swordItems[4])
        {
            cout << "[" << nr << "] " << swordItems[4] << "(" << swordAttackPower[4] << ")\n";
            weaponDamage.push_back(swordAttackPower[4]);
            weapon.push_back(bag[i]);
            ++nr;
        }
        else if (bag[i] == swordItems[5])
        {
            cout << "[" << nr << "] " << swordItems[5] << "(" << swordAttackPower[5] << ")\n";
            weaponDamage.push_back(swordAttackPower[5]);
            weapon.push_back(bag[i]);
            ++nr;
        }
    }
    for (int j = 0; j < numberOfAbilities; j++)
    {
        if (abilities[j] == fire)
        {
            cout << "[" << nr << "] " << fire << "(" << firePower << ")\n";
            weapon.push_back(abilities[j]);
            weaponDamage.push_back(firePower);
            ++nr;
        }
        else if (abilities[j] == explosiveFire)
        {
            cout << "[" << nr << "] " << explosiveFire << "(" << ExplosivePower << ")\n";
            weapon.push_back(explosiveFire);
            weaponDamage.push_back(ExplosivePower);
            ++nr;
        }
    }
    wChoice = i_inputWithClear();

    return wChoice;
}
bool lookForPotion(string potion)
{
    bool foundPotion = false;
    for (int i = 0; i < sizeOfBag; i++)
    {
        if (bag[i] == potion)
        {
            foundPotion = true;
            break;
        }
    }
    return foundPotion;
}
int getQuests()
{

    int numberQue = rand() % 3;
    return numberQue;

}
bool quest(string playerName, int QuestNumber)
{
    int fightMonster;
    bool startGame = true;
    int fightingEnemie = 0;

    if (QuestNumber == 0)//Villedge quest
    {
        fightingEnemie = 0;
        cout << "You go to the village. As soon as you get there, you come face to face with the goblin!\n"
            "[1] Fight\n[2] Run away\n[3] Check bag\n";

    }
    else if(QuestNumber == 1)//Neigbor quest
    {
        fightingEnemie = 3;
        cout << "You go to the neighbor and talk to her. She's very upset about her cattle and \n"
            "happy you came to help. You get the location from her and set out to find clues and\n"
            "hopefully to kill a monster. You carefully inspect the ground were the last sheep\n"
            "got taken. You find tracks from something with big feet. You suspect it might be a\n"
            "Wyvern. You hide and keep a close watch over the animals from a tree. As you suspected\n"
            "a Wyvern shows up. Time to fix the problem!\n\n";
        cout << "[1] Attack Wyvern\n[2] Run away\n[3] Check bag\n";
    }
    else if (QuestNumber == 2) //Wolf quest
    {
        fightingEnemie = 1;
        cout << "You prepare well and decide to hunt some wolfs. You search and find paw \n"
            "prints on the ground. You track the wolf and find it's den. You can see\n"
            "the wold´f in the distance!\n"
            "\n[1] Fight\n[2] Run away\n[3] Check bag\n";

    }

    //function for fighting
    fightMonster = i_inputWithClear();

    //Reward for quest
    if (fightMonster == 1)
    {
        startGame = fight(fightingEnemie, playerName);
        if (startGame)
        {
            if (QuestNumber == 0)
            {
                cout << "The villagers are very grateful and give you 25 gold in reward.\n\n";
                gold += 25;
            }
            else if (QuestNumber == 1)
            {
                cout << "The neighbor is very grateful and give you the 100 gold reward.\n\n";
                gold += 100;
            }
            else if (QuestNumber == 2)
            {
                cout << "The hunters are very grateful for your help and give you 50 gold in reward.\n\n";
                gold += 50;
            }
        }
    }
    if (fightMonster == 2)
    {
        cout << "You run away";
    }
    if (fightMonster == 3)
    {
        CheckBag();
    }
    return startGame;
}
bool fight(int enemieInFight, string playerName)
{
    int attack = 0;
    int fightingHealth = Player.health;
    string weapon_damage;
    bool startGame = true;
    int your_weapon, fighting, monsterHealth;

    monsterHealth = monster_arr[enemieInFight].monster_health;
    cout << "Prepare to fight!\n\n";
    your_weapon = weapons();
    cout << "You choose " << weapon[your_weapon - 1] << "(" << weaponDamage[your_weapon - 1] << ")\n\n";
    attack = weaponDamage[your_weapon - 1];
    weapon_damage = weapon[your_weapon - 1];

    while (true)
    {
        cout << "[1] Attack " << monster_arr[enemieInFight].monster_name << "\n[2] Run away\n\n";
        bool foundHealthPotion = lookForPotion(healthPotion);
        if (foundHealthPotion)
        {
            cout << "[3] " << healthPotion << "\n";
        }
        bool foundAttackPotion = lookForPotion(attackPotion);
        if (foundAttackPotion)
        {
            cout << "[4] " << attackPotion << "\n";
        }
        fighting = i_inputWithClear();
        if (fighting == 1)
        {
            cout << "You hit the " << monster_arr[enemieInFight].monster_name << ", giving " << attack << " damage\n";
            monsterHealth -= attack;

            if (monsterHealth > 0)
            {
                cout << monster_arr[enemieInFight].monster_name << " | " << monsterHealth << "/" << monster_arr[enemieInFight].monster_health
                    << "\n\n";
                if (monsterHealth < monster_arr[enemieInFight].monster_health / 2)
                {
                    cout << "The " << monster_arr[enemieInFight].monster_name << " get frantic and hits harder!\n\n"
                        "You take " << monster_arr[enemieInFight].monster_attack + 1 << " damage\n";

                    fightingHealth -= (monster_arr[enemieInFight].monster_attack + 1);
                }
                else
                {
                    cout << monster_arr[enemieInFight].monster_name << " hits you!\nYou take " << monster_arr[enemieInFight].monster_attack << " damage.\n\n";
                    fightingHealth -= monster_arr[enemieInFight].monster_attack;
                }

                cout << playerName << " | Health : " << fightingHealth << "\n\n";

                if (fightingHealth < 1)
                {
                    cout << " YOU DIED!\n\n\"GAME OVER\"\n\n";
                    startGame = false;
                    break;
                }
            }
            else
            {
                cout << "You defeated the " << monster_arr[enemieInFight].monster_name << "!\n\n";
                getReward(enemieInFight);
                break;
            }
        }
        else if (fighting == 2)
        {
            cout << "You realize you might've not been fully prepered. You run away.\n\n";
            break;
        }
        else if (fighting == 3)
        {
            fightingHealth = Player.health;
            cout << "You get your full health back!\n\n" << playerName << " | " << fightingHealth << endl;
            removeFromBag(healthPotion);

        }
        else if (fighting == 4 && foundAttackPotion)
        {
            attack += attack;
            cout << "You get double the attack power!\nYou now do " << attack << " damage.\n\n";
            removeFromBag(attackPotion);

        }
        else
        {
            cout << "You cant do that, try again\n\n";
        }
    }
    return startGame;
}
void getReward(int enemieInFight)
{
    int getMoney;
    string winning;
    winning = randomItem();

    if (winning != "Gold" && winning != "Nothing")
    {
        cout << "You find a " << winning << "\n";
        bool ifFull = fullBag();
        if (ifFull)
        {
            cout << "You cant take the " << winning << ". Your bag is full.\n";
        }
        else
        {
            putInBag(winning);
        }
    }
    else
    {
        if (winning == "Gold")
        {
            getMoney = rand() % 21 + 1;
            cout << "You found " << getMoney << " gold on the " << monster_arr[enemieInFight].monster_name << "\n\n";
            gold += getMoney;

        }
        else if (winning == "Nothing")
        {
            cout << "You dont find anything on the " << monster_arr[enemieInFight].monster_name << "\n\n";
        }
    }
}

//Merchant
void merchantItems()
{
    int theItems = rand() % 5 + 3; //hur många items som ska visas /"kan köpas"
    int choosenItem;
    bool canBuy = true, buyMode = true;
    string itemOfChoice;
    int enoughMoney = 0;
    merchItems.clear();
    merchCost.clear();

    for (int i = 0; i < theItems; i++)
    {
        int randomItems = rand() % 9 + 1;

        switch (randomItems)
        {
        case 1:
            merchItems.push_back(allItems[0]); //The worst sword              ca 5 gold
            merchCost.push_back(itemCost[0]);
            break;
        case 2:
            merchItems.push_back(allItems[1]); //Better than "Rosty sword"          ca 20 gold
            merchCost.push_back(itemCost[1]);
            break;
        case 3:
            merchItems.push_back(allItems[2]);  //Better than "Sword"          ca 50 gold 
            merchCost.push_back(itemCost[2]);
            break;
        case 4:
            merchItems.push_back(allItems[3]); //Better than "Long sword"     ca 100 gold
            merchCost.push_back(itemCost[3]);
            break;
        case 5:
            merchItems.push_back(allItems[4]); //The best sword             ca 500 gold
            merchCost.push_back(itemCost[4]);
            break;
        case 6:
            merchItems.push_back(allItems[5]); //Regain health                 ca 20 gold      
            merchCost.push_back(itemCost[5]);
            break;
        case 7:
            merchItems.push_back(allItems[6]);//gain the double amount attackpower. ca 40 gold
            merchCost.push_back(itemCost[6]);
            break;
        case 8:
            merchItems.push_back(allItems[7]); //                                     ca 100 gold
            merchCost.push_back(itemCost[7]);
            break;
        case 9:
            merchItems.push_back(allItems[8]);    //                          ca 500 gold
            merchCost.push_back(itemCost[8]);
            break;
        default:
            merchItems.push_back("Empty spot");
            merchCost.push_back(0);
            break;
        }
    }
    while (buyMode)
    {
        cout << "What do you want to buy?\n"
        "Gold: [" << gold << "]\n\n";
        for (int j = 0; j < merchItems.size(); j++)
        {
            cout << "[" << j + 1 << "] " << merchItems[j] << "\n    " << merchCost[j] << " gold\n\n";
        }
        cout << "\n[" << merchItems.size() + 1 << "] Exit\n";
        cin >> choosenItem;
        system("cls");

        if (choosenItem == merchItems.size() + 1)
        {
            break;
        }
        else
        {
            itemOfChoice = merchItems[choosenItem - 1]; //. . . 
            if (itemOfChoice == allItems[0])
            {
                choosenItem = 1;
                enoughMoney = itemCost[0];
            }
            else if (itemOfChoice == allItems[1])
            {
                choosenItem = 2;
                enoughMoney = itemCost[1];
            }
            else if (itemOfChoice == allItems[2])
            {
                choosenItem = 3;
                enoughMoney = itemCost[2];
            }
            else if (itemOfChoice == allItems[3])
            {
                choosenItem = 4;
                enoughMoney = itemCost[3];
            }
            else if (itemOfChoice == allItems[4])
            {
                choosenItem = 5;
                enoughMoney = itemCost[4];
            }
            else if (itemOfChoice == allItems[5])
            {
                choosenItem = 6;
                enoughMoney = itemCost[5];
            }
            else if (itemOfChoice == allItems[6])
            {
                choosenItem = 7;
                enoughMoney = itemCost[6];
            }
            else if (itemOfChoice == allItems[7])
            {
                choosenItem = 8;
                enoughMoney = itemCost[7];
            }
            else if (itemOfChoice == allItems[8])
            {
                choosenItem = 9;
                enoughMoney = itemCost[8];
            }
            canBuy = fullBag();
            if (!canBuy)
            {
                string buyItem;

                switch (choosenItem)
                {
                case 1:
                    buyItem = allItems[0]; //The worst sword              ca 5 gold
                    break;
                case 2:
                    buyItem = allItems[1]; //Better than "Rosty sword"    ca 20 gold
                    break;
                case 3:
                    buyItem = allItems[2];  //Better than "Sword"         ca 50 gold 
                    break;
                case 4:
                    buyItem = allItems[3]; //Better than "Long sword"     ca 100 gold
                    break;
                case 5:
                    buyItem = allItems[4]; //The best sword               ca 500 gold
                    break;
                case 6:
                    buyItem = allItems[5]; //Regain health                 ca 20 gold
                    break;
                case 7:
                    buyItem = allItems[6]; //gain the double amount attackpower. ca 40 gold
                    break;
                case 8:
                    buyItem = allItems[7];                                    //  ca 100 gold
                    break;
                case 9:
                    buyItem = allItems[8];                             //  ca 500 gold
                    break;
                default:
                    buyItem = "Empty spot";
                    break;
                }

                if (gold >= enoughMoney)
                {
                    putInBag(buyItem);
                    gold -= enoughMoney;
                }
                else
                {
                    cout << "You don't have enough money, buy something else.\n";
                }
            }
            else
            {
                cout << "Your bag is full, you can't buy anything.\n";
            }
        }
    }
}
void sellItemToMerchant()
{
    vector <string> sellItem;
    int sell;
    int costOfItem;
    string itemToSell;
    int i;
    int _sell = 0;
    int itemSold = 0;
    int j = 0;

    while (true)
    {
        sellItem.clear();
        cout << "What do you want to sell?:\n";
        cout << "Gold: [" << gold << "]\n\n";
        for (i = 0; i < sizeOfBag; i++)
        {
            if (_sell == 1 && j == 0)
            {
                if (i == sell)
                {
                    sellItem.push_back("");
                    ++j;
                }
                else
                {
                    if (bag[i] != x)
                    {
                        cout << "[" << i + 1 << "] " << bag[i] << " \n";
                        sellItem.push_back(bag[i]);

                    }
                }
            }
            else
            {
                if (bag[i] != x)
                {
                    cout << "[" << i + 1 << "] " << bag[i] << " \n";
                    sellItem.push_back(bag[i]);

                }
            }

        }
        cout << "[" << sellItem.size() + 1 + _sell << "] Go back\n";
        cin >> sell;
        system("cls");
        if (sell == sellItem.size() + 1 + _sell)
        {
            break;
        }
        --sell;
        itemToSell = sellItem[sell];
        bool noPrice = false;
        for (i = 0; i < sizeAllItemsList; i++)
        {
            if (itemToSell == "")
            {
                cout << "You can't sell that.";
            }
            else
            {
                if (itemToSell == allItems[i])
                {
                    costOfItem = itemCost[i] * 0.8;
                    noPrice = true;
                    break;
                }
            }

        }
        if (itemToSell != "")
        {
            if (!noPrice)
            {
                costOfItem = rand() % 100 + 20;
            }
            bag[sell] = x;
            gold += costOfItem;
            cout << "You sold the " << itemToSell << " for " << costOfItem << "\n\n";
            ++_sell;
            itemSold = sell;
        }

    }
}
//Explore
bool undergroundDarkRoom(int seeInTheDark, bool first, bool treasure)
{
    bool gotAbility = false;
    if (seeInTheDark == 1 && first == false)
    {
        cout << "After hitting the flashlight a couple of times, it lights up. You look around\n"
            "the room, it looks like it has been deserted for a long time. There's a lot of\n"
            "spiderwebs and the thick layer of dust makes it hard for you to breath. You see\n"
            "a big desk to one side of the room, on it there are many strange looking books.\n"
            "One book in particularly stand out. You pick it up and skimm through it . . . \n"
            "Suddenly you feel heat engulf your skin, you drop the book as flames surrounds you.\n"
            "As fast as it appeard it vanished.\n\n[You just learned the fire ability!] \n\n"
            "You can now use it in certain situations while exploring and of course to fight monsters!\n\n";
        gotAbility = true;
    }
    else if (seeInTheDark == 1 && first == true)
    {
        cout << "You use the flashlight again to look in the room. Everything's a mess, you\n"
            "start lifting things.\nYou sift through the books, but dont find anything special.\n"
            "You realise you might have made a bigger mess, than how you found it.\n\n";
    }
    else if (seeInTheDark == 2 && !treasure)
    {

        cout << "You use your fire ability to create a fire in the palm of your hand. It lights\n"
            "up the room completely. What a handy ability! You can now see everything more clearly.\n"
            "On the desk, what you couldn't see before, in one corner there's like a crack. Looks \n"
            "like it could be a hidden compartment. You start lirking it open and find a purple gem.\n";
        hiddenStone = true;
    }
    else if (seeInTheDark == 2 && treasure)
    {
        cout << "You use your fire ability to create a fire in the palm of your hand. It lights\n"
            "up the room completely. You take your time to search the room, but you already \n"
            "found everything worth taking.\n";
    }
    else
    {
        cout << "You cant use that.\n";
    }
    return gotAbility;
}
//Help functions
int i_inputWithClear()
{
    int returnInput;
    cin >> returnInput;
    system("cls");
    return returnInput;
}
string s_inputWithClear()
{
    string returnString;
    cin >> returnString;
    system("cls");
    return returnString;
}