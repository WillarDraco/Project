#include <iostream>
#include <string>
#include <limits>
#include <unistd.h>
#include "Monster.h"
#include "Goblin.h"
#include "Player.h"
#include "Barbarian.h"
#include "Wizard.h"
#include "Archer.h"
#include "Slime.h"
#include "Skeleton.h"



int main() {
    int standard_kill_count = 0; // keeps track of amount of normal monsters killed
    int boss_kill_count = 0; // keeps track of amount of bosses killed

    std::cout << "Welcome to Crawler!" << "\n" << "Crawler is a turn-based "
        "rogue-like game where you take control of a player and defeat as many " 
        "monsters as you can,\nlevelling up and unlocking weapons along the way.\n";
    sleep(2);

    // openGL start button and maybe highscores?
    // black screen, text pops up - character creation -
    std::string name;
    std::string _class;

    std::cout << "Enter a name: ";
    std::cin >> name;

    sleep(0.5);

    // create an array of pointers to pointers of each class type
    // player selects one to use and that pointer/index is used throughout the game
    Player** classes = new Player*[3];

    Barbarian* barbarian = new Barbarian(1, name);
    Archer* archer = new Archer(1, name);
    Wizard* wizard = new Wizard(1, name);

    classes[0] = barbarian;
    classes[1] = archer;
    classes[2] = wizard;

    int classes_index;
    bool valid_class = false;
    while (valid_class == false) {
        std::cout << "Select a class, you may choose:\nBarbarian\nArcher\nWizard\n";
        std::cin >> _class;
 
        if (_class == ("Barbarian") || _class == "barbarian") {
            classes_index = 0;
            valid_class = true;
            _class = "Barbarian";
        } else if (_class == ("Archer") || _class == ("archer")) {
            classes_index = 1;
            valid_class = true;
            _class = "Archer";
        } else if (_class == ("Wizard") || _class == ("wizard")) {
            classes_index = 2;
            valid_class = true;
            _class = "Wizard";
        } else {
            std::cout << "Your selection is not valid, try again\n";
        }
    }

    sleep(0.5);

    std::cout << "You are " << name << " the " << _class << "\n" << "Press enter to continue\n";
    std::cin.get();
    std::cin.get();

    std::cout << "You open your eyes\n"; 
    sleep(2);
    std::cout << "The room is pitch black, your head hurts\n";
    sleep(2);
    std::cout << "You hear a growl, and you scramble to your feet as a goblin approaches...\n"; 
    sleep(2);

    Goblin tutorial_enemy = Goblin(classes[classes_index]); 
    // openGL fight scene appears

    // text boxes pop up explaining punch/defend/rest

    std::cout << "\nIn a fight, until you have a weapon you may Attack, Defend, Rest or perform a special action\n";
    sleep(2);
    std::cout << "Once an option is selected, the selected option occurs and it is now the enemys turn\n";
    sleep(2);
    std::cout << "Attack is a basic attack that does damage to the enemy. It won't do much until you get a weapon!\n";
    sleep(2);
    std::cout << "Defend reduces a small amount of damage taken on enemy's next turn\n";
    sleep(2);
    std::cout << "Rest recovers a small amount of health\n";
    sleep(2);
    std::cout << "Your special action depends on your class type FINISH THIS BEFORE SUBMIT\n";
    sleep(2);

    // While loop until fight is over
    bool victory = false;
    bool player_death = false;
    while (victory == false && player_death == false) {
        // Loop to ensure valid selection
        bool valid = false;
        while (valid == false) {
            std::string selection;
            std::cout << "\nWill you attack, defend or rest?\n";
            std::cin >> selection;           
            if (selection == "Attack" || (selection == "attack")) {
                classes[classes_index]->attack(&tutorial_enemy);
                valid = true;
            } else if (selection == "Defend" || (selection == "defend")) {
                classes[classes_index]->block();
                valid = true;
            } else if (selection == "Rest" || (selection == "rest")) {
                //classes[classes_index]->rest();
                valid = true;
            } else {
                std::cout << "Your selection is not valid, try again\n";
            }            
        }
        if (tutorial_enemy.get_current_health() == 0) {
            std::cout << "\nYou defeated the goblin!\n";
            victory = true;
            standard_kill_count++;
            break;
        }
        tutorial_enemy.attack(classes[classes_index]);

        if (classes[classes_index]->get_current_health() <= 0) {
            std::cout << "\nYou died\n";
            player_death = true;
        }
    }

    // if player health reaches 0, trigger gameover and display playthrough statistics
    if (player_death == true) {
        std::string name = classes[classes_index]->get_name();
        std::cout << "Unfortunately " << name << " the " << _class << " has failed in their quest to reach the exit.\n";
        sleep(2);
        std::cout << name << " killed " << standard_kill_count << " monsters and " << boss_kill_count << " bosses.\n";
        sleep(2);
        std::cout << name << " reached level " << classes[classes_index]->get_level() << ".\n";
        sleep(2);
        std::cout << "While " << name << " may have failed in his quest, another may succeed...\n";
        sleep(2);
        std::cout << "Will you try again?\n";
        
        return 0;
    }

    // tutorial enemy drops weapon depending on class
    if (_class == "Barbarian") {
        std::cout << "\nYou notice a dirty blade tucked in the the goblins belt...\n";
        sleep(2);
        std::cout << "You take the blade from the body and see it's a sword, rusty and dirty but sharp\n";
        sleep(2);
        std::cout << "Gratefully, you tuck the sword into your own belt, and as you begin to look around you\nnotice and old wooden shield in the corner of the room\n";
        sleep(2);
        std::cout << "\nCongratulations! you have acquired a sword and shield!\n";
        sleep(2);
    } else if (_class == "Archer") {
        std::cout << "\nYou notice a leather strap across the goblins chest, and upon closer insepction you realise\nthere is a quiver full of arrows across the goblins back...\n";
        sleep(2);
        std::cout << "The tips on the arrows look worn but still sharp enough to cut\n";
        sleep(2);
        std::cout << "Gratefully, you strap the quiver to your own back, and as you begin to look around you notice\nan old hunting bow in the corner of the room\n";
        sleep(2);
        std::cout << "\nCongratulations! You have acquired a Bow and Quiver!\n";
        sleep(2);
    } else if (_class == "Wizard") {
        std::cout << "\nYou notice a strange old book in the goblins small satchel\n";
        sleep(2);
        std::cout << "You take the book and as you attempt to read it, you realise while most of it is in a language\nyou cannot understand\n";
        sleep(2);
        std::cout << "You look around the room and find it completely empty and decide to take a moment to glean\nwhat you can from this book\n";
        sleep(2);
        std::cout << "Several moments later you realise its a book about spellcraft! For now you can only understand\none spell but that is enough for now\n";
        sleep(2);
        std::cout << "You put the book back in the satchel and attach the satchel to your belt\n";
        sleep(2);
        std::cout << "\nCongratulation! You have acquired a spellbook!\n";
    }
    std::cout << "\nNow that you have a weapon, your attack will do more damage, and each type of weapon has\nunique effects!\n";
    sleep(2);
    std::cout << "You may find other weapons in your travels, but be warned, you can only carry one type at a time\n";
    sleep(2);
    std::cout << "\nStanding breathless over the dead body of the goblin, you look into the darkness\n";
    sleep(2);
    std::cout << "You decide the only way out is forwards, and with a grimace\n"
        "you take your first step into what seem to be an endless darkness...\n";
    sleep(2);
    std::cout << "\nPress Enter to continue...\n";
    std::cin.get();
    std::cin.get();


// tutorial victory level stuff

// main gameplayer loop
    Monster** standard_monsters = new Monster*[3]; // fill arrays inside loop to account for changing player level
    Monster** boss_monsters = new Monster*[3];
    while (player_death == false) {

        
        /* if (standard_kill_count % 3 == 0) {  // after every 3rd normal enemy, fight boss
            Ogre* ogre = new Ogre(classes[classes_index]);
            Dragon* dragon = new Dragon(classes[classes_index]);
            Lich* lich = new Lich(classes[classes_index]);

            boss_monsters[0] = ogre;
            boss_monsters[1] = dragon;
            boss_monsters[2] = lich;

            delete ogre;
            delete lich;
            delete dragon;
        } else */
            Goblin* goblin = new Goblin(classes[classes_index]);
            Slime* slime = new Slime(classes[classes_index]);
            Skeleton* skeleton = new Skeleton(classes[classes_index]);

            standard_monsters[0] = goblin;
            standard_monsters[1] = slime;
            standard_monsters[2] = skeleton;

            int monster_select = rand() % 3 + 1;

            if (monster_select == 0) {
                std::cout << "You stumble across a goblin"
            }
            delete goblin;
            delete slime;
            delete skeleton;
// else run standard enemy loop

// combat - 2 enemy arrays, one boss one standard, generate rand enemy from array
    }
}



// if victory - STDKC++/BKC++, check level, if Boss upgrades or heal