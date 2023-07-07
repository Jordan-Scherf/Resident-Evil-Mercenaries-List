#include <iostream>
#include "PriorityQ.h"
#include <fstream>
#include <iomanip>
int main() {
    struct mercType {
// tracks how many of each monsters is
// defeated and civilian saved for a
// mercenary
        int zombies;
        int spiders;
        int drainDeimos;
        int zombieDogs;
        int hunters;
        int nemesis;
        int civilians;

// default constructor , optional but can
// be helpful
        mercType() {
            zombies =0, spiders = 0, drainDeimos = 0, zombieDogs = 0, hunters = 0, nemesis = 0, civilians = 0;
        }

// do not actual try to overload the
// question mark operator , you can overload
// any comparison operator you like and it will
// be used in your bubbleUp and bubbleDown
        bool operator<(const mercType &rhs) const {
            float points1 = zombies * 1.0f + spiders * 1.1f + drainDeimos * 1.2f + zombieDogs * 1.3f + hunters * 1.4f +
                            nemesis * 1.5f + civilians * 2.0f;
            float points2 = rhs.zombies * 1.0f + rhs.spiders * 1.1f + rhs.drainDeimos * 1.2f + rhs.zombieDogs * 1.3f +
                            rhs.hunters * 1.4f + rhs.nemesis * 1.5f + rhs.civilians * 2.0f;
            return points1 < points2;
        }
// You might need to overload + or +=
// operators , would
// be needed in the
// increaseKey function

        void operator += (const mercType &rhs){
            zombies = zombies + rhs.zombies;
            zombieDogs = zombieDogs + rhs.zombieDogs;
            drainDeimos = drainDeimos + rhs.drainDeimos;
            spiders = spiders + rhs.spiders;
            hunters = hunters + rhs.hunters;
            nemesis = nemesis + rhs.nemesis;
            civilians = civilians + rhs.civilians;

        }

        float get_points(){
            return zombies * 1.0f + spiders * 1.1f + drainDeimos * 1.2f + zombieDogs * 1.3f + hunters * 1.4f +
                   nemesis * 1.5f + civilians * 2.0f;
        }
    };

    priorityQ<std::string, mercType> mercenaries;

// Lets open the file
    std::string line;
    std::string name;
    std::string monster;
    int numOfMercs = 0;
    float amount;
    std::cout << "\nEnter mercenaries file: ";
    std::cin >> line;
    std::ifstream infile(line);

    std::setprecision(2);

    while (std::getline(infile, line)) {
        mercenaries.push_back(line, mercType());
        numOfMercs++;
    }


    std::cout << "\n\nEnter simulation file: ";
    std::cin >> line;
    std::cout << '\n';

    std::ifstream ifile(line);

    mercType leader;
    std::string leaderName;
    while(ifile >> name >> monster >> amount){

       mercType defaults;
       /*
        * int zombies;
        int spiders;
        int drainDeimos;
        int zombieDogs;
        int hunters;
        int nemesis;
        int civilians;
        */
       if(monster == "zombies"){
           defaults.zombies = amount;
           mercenaries.increaseKey(name, defaults);
       }

        if(monster == "spiders"){
            defaults.spiders = amount;
            mercenaries.increaseKey(name, defaults);
        }

        if(monster == "drainDeimos"){
            defaults.drainDeimos = amount;
            mercenaries.increaseKey(name, defaults);
        }

        if(monster == "zombieDogs"){
            defaults.zombieDogs = amount;
            mercenaries.increaseKey(name, defaults);
        }

        if(monster == "hunters"){
            defaults.hunters = amount;
            mercenaries.increaseKey(name, defaults);
        }
        if(monster == "nemesis"){
            defaults.nemesis = amount;
            mercenaries.increaseKey(name, defaults);
        }
        if(monster == "civilians"){
            defaults.civilians = amount;
            mercenaries.increaseKey(name, defaults);
        }
        if ((leader.get_points() < mercenaries.get_front_priority().get_points() ) &&  mercenaries.get_front_key() != leaderName){
            leader = mercenaries.get_front_priority();
            leaderName = mercenaries.get_front_key();
            std::cout << std::fixed << std::setprecision(1 ) << "We have a new leader: "
                      << mercenaries.get_front_key() << " Score: "
                      << mercenaries.get_front_priority().get_points() << "\n\n";

        }
    }

    // Lets display the rankings
    for( int i = 1; i < numOfMercs + 1; i++){
        std::cout << "\nRank " << i << '\n';
        std::cout << std::fixed << std::setprecision(1) << "Name: "
                  << mercenaries.get_front_key() << " Score: "
                  << mercenaries.get_front_priority().get_points() << '\n' << '\n';

        mercenaries.pop_front();
    }

    return 0;
}


