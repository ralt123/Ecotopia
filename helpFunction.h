#include <iostream>

using namespace std;

void printMenu()
{
	for(int i=0; i < 50; i++){
		cout << "-";
	}
	
	cout << "\n\n\t \e[1m 1. Moving.  \e[0m \n";
	cout << "\t \e[1m 2. Combat. \e[0m \n";
	cout << "\t \e[1m 3. Aliens. \e[0m \n";
	cout << "\t \e[1m 4. Gameplay. \e[0m \n";
	cout << "\t \e[1m 5. Tower Defence. \e[0m \n";
	cout << "\t \e[1m 6. Game Interface. \e[0m \n";
	cout << "\t \e[1m 7. Running away from combat. \e[0m \n";
	
	cout << "\n\t \e[1m 0. Quit. \e[0m \n\n";
	for(int i=0; i < 50; i++){
		cout << "-";
	}
	cout << "\n\n";
}


int helpFunction()
{
	int userChoice;
	
	do{
		
		printMenu();
		cout << "Enter your choice: ";
		cin >> userChoice;
										//Call the specific function for each inputa
		if(userChoice == 1){				
			cout << "W and S control forward and backward movement, while A and D are left and right.\n ";
		}
		
		else if(userChoice == 2){				
			cout << "Aliens will attack you if you walk over them or start shooting at you if you shoot at them first, if you keep your distance and not attack, you could avoid them by sneaking away.\n";
			
		}
		
		else if(userChoice == 3){				
			cout << " A - Normal balanced alien \n"  " T - Tank with a focus on defence/health \n " "B - Berseker with a focus on attack\n";
			
		}
		
		else if(userChoice == 4){				
			cout << "Gameplay will consist of exploring an unknown open world planet and gathering resources whilst improving your character with player upgrades, with some of which those player upgrades will consist off, upgrading your Armour, so less damage is delt with when in combat, weapon upgrades, and more. As for exploring the open world for recourses you farm you could use them to expand and improve the defense from pending alien attacks.\n";
			
		}

		else if(userChoice == 5){				
			cout << "Defend your base, place your towers and defend against the horrendous aliens, you could also upgrade the towers and sell them before starting the round.\n";
			
		}
		
		else if(userChoice == 6){
			cout << "The open world is represented by characters with each character representing something. 'o' for example is the player, you. A/T/B are aliens and the map files are spaces/dots  \n";
		}
		
		else if(userChoice == 7){
			cout << "Running away from combat will be penalized towards your XP.\n";
		}
		
		else if(userChoice == 0){
			cout << "My Pleasure Helping You!\n";
		}

		else{
			cout << "Wrong Choice\n";			
		}
		
	}while(userChoice != 0);
	
	 
}
