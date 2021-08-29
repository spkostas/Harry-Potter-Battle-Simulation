#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
class Wizard;
class Spell;
class stack;
vector <Wizard*> wizards;
vector <Spell*> spells;
vector <stack*> rounds;
Wizard *Targettolearn;
int DmgOrHeal = 0;
string p1, p2;
//updates
string attacker,defender;
int round2 = 0;

//Colours
#define RESET   "\033[0m"
#define GREEN   "\033[32m"




enum Types { STRING, INTEGER, FUNC };

class MyType {
public:
	void(*fun_ptr)(void);
	Types type;
	int intval;
	const char* stringval;
	MyType() {}
	MyType(const char* s){
		type = STRING;
		stringval = s;
	}
	MyType(int i){
		type = INTEGER;
		intval = i;
	}
	MyType(void(*action_ptr)(void)) {
		type = FUNC;
		fun_ptr = action_ptr;
	}
	
};

class Spell {
public:
	vector <MyType*> *attributes;
	Spell() {}
	Spell(vector<MyType> typer) {
		attributes = new vector<MyType*>();
		for (unsigned int i = 0; i < typer.size(); i++) {
			MyType *m = new MyType();
			m->type = typer[i].type;
			m->intval = typer[i].intval;
			m->stringval = typer[i].stringval;
			m->fun_ptr = typer[i].fun_ptr;
			attributes->push_back(m);
		}
		spells.push_back(this);
	}
};


class Wizard {
public:
	int ID;
	int dmgheal;
	int hasWand = 1;
	int wand; // xrisimopoieitai gia tin equip mono
	int selected = 0; //gia tin while select player mesa stin duel
	int maxhealth;
	vector <MyType*> *attributes;
	vector <Spell*> spellsknown;
	Wizard() {}
	Wizard(int i) {
		wand = i;
	}
	Wizard(vector<MyType> typer) {
		attributes = new vector<MyType*>();
		for (unsigned int i = 0; i < typer.size(); i++) {
			MyType *m = new MyType();
			m->type = typer[i].type;
			m->intval = typer[i].intval;
			m->stringval = typer[i].stringval;
			attributes->push_back(m);
		}
		this->maxhealth=this->attributes[0][2]->intval;
		wand = 1;
		wizards.push_back(this);
	}
	Wizard& operator,(Wizard& w) {
		return *this;
	}

	Wizard& operator+(int i) {
		this->dmgheal= i;
		return *this;
	}
	Wizard& operator+=(int _x) {
		int t;
		t=this->attributes[0][2]->intval + _x;
		if(t>this->maxhealth)this->attributes[0][2]->intval=this->maxhealth;
				return *this;
			}
	Wizard& operator,(int x) {
			//playing==attacker
			//notplaying==defender
			if (DmgOrHeal == 1) {
				if(attacker=="Gryffindor"){
					if(defender=="Gryffindor"){
						x-=x*0.20;
					}else if(defender=="Hufflepuff"){
						x-=x*0.07;
					}
				}else if(attacker=="Slytherin"){
					if(defender=="Gryffindor"){
						x-=x*0.10;
					}else if(defender=="Slytherin"){
						x+=x*0.15;
				    }else if(defender=="Hufflepuff"){
				    	x+=x*0.08;
					}else if(defender=="Ravenclaw"){
						x+=x*0.15;
					}
				}else if(attacker=="Hufflepuff"){
					if(defender=="Gryffindor"){
						x-=x*0.013;
					}else if(defender=="Slytherin"){
						x+=x*0.07;
					}else if(defender=="Ravenclaw"){
						x+=x*0.07;
					}
				}else if(attacker=="Ravenclaw"){
					if(defender=="Gryffindor"){
						if(!(round2%2)){
							x-=x*0.13;
						}else x-=x*0.20;
					}else if(defender=="Slytherin"){
						if(!round2%2)x+=x*0.07;
					}else if(defender=="Hufflepuff"){
						if(round2%2)x-=x*0.07;
					}else if(defender=="Ravenclaw"){
						if(!round2%2)x+=x*0.07;
					}
				}
				this->attributes[0][2]->intval -= x;
			}else {

				cout << "O kyrios    "<<this->attributes[0][0]->stringval<<this->maxhealth<<endl;
				int t;
				t=this->attributes[0][2]->intval + x;
				if(t>this->maxhealth){
					this->attributes[0][2]->intval=this->maxhealth;
				}else this->attributes[0][2]->intval += x;
			}
			return *this;
		}
	Wizard& operator--(int) {
		return *this;
	}
	friend Wizard& operator-(Wizard& w1,Wizard& w2) {		
		if (w2.wand == 1) {
			w1.hasWand = 1;
		}
		else if(w2.wand == 0){
			w1.hasWand = 0;
		}
		return w1;
	}
	
	Wizard(Wizard* w) {
		attributes = new vector<MyType*>();
		for (unsigned int i = 0; i < w->attributes->size(); i++) {
			MyType *m = new MyType();
			m->type = w->attributes[0][i]->type;
			m->intval = w->attributes[0][i]->intval;
			m->stringval = w->attributes[0][i]->stringval;
			attributes->push_back(m);
		}
		this->maxhealth=this->attributes[0][2]->intval;
		for (unsigned int i = 0; i < w->spellsknown.size(); i++) {
			spellsknown.push_back(w->spellsknown[i]);
		}
	}
};

enum Stack_Types { AFTER, FOR, IF, ELSE_IF, ELSE };
//struct for stack
struct stack {
	stack() {}
	Stack_Types type;
	int RemainingRounds = -1;
	bool tf;
	Wizard attacker, defender;
	int ID = -1;
	void(*fun_ptr)(void);
	stack(Stack_Types t) {
		type = t;
	}
};
//

class Wizards {
public:
	Wizards& operator[](Wizard& w) {
		return *this;
	}

};

Wizard *lookupwiz(string name) {
	for (unsigned int i = 0; i < wizards.size(); i++) {
		if (wizards[i]->attributes[0][0]->stringval == name) {
			return wizards[i];
		}
	}
}

class Learn {
public:
	Learn(string name) {
		for (unsigned int i = 0; i < spells.size(); i++) {
			if (spells[i]->attributes[0][0]->stringval == name) {
				Targettolearn->spellsknown.push_back(spells[i]);
				/*Wizard *w = lookupwiz(Targettolearn->attributes[0][0]->stringval);
				w->spellsknown.push_back(spells[i]);*/
				break;
			}
		}
	}
	Learn& operator,(Learn w) {
		return *this;
	}
};
class Learns {
public:
	Learns& operator[](Learn w) {
		return *this;
	}
};


class Spells {
public:
	Spells& operator[](Spell& w) {
		return *this;
	}
};

void equip(Wizard w) {
	return;
}
void duplicate(Wizard w1, Wizard *w2) {
	for (unsigned int i = 0; i < w2->attributes->size(); i++) {
		MyType *m = new MyType();
		m->type = w2->attributes[0][i]->type;
		m->intval = w2->attributes[0][i]->intval;
		m->stringval = w2->attributes[0][i]->stringval;
		w1.attributes->push_back(m);
	}
	for (unsigned int i = 0; i < w2->spellsknown.size(); i++) {
		w1.spellsknown.push_back(w2->spellsknown[i]);
	}
	w1.ID = w2->ID;
	w1.hasWand = w2->hasWand;
	w1.selected = w2->selected;
}
Wizard Playing;
Wizard NotPlaying;
void duel() {
	Wizard wand1 = 1;
	Wizard wand2 = 0;
	Wizard player1, player2;
	cout << GREEN << "\nPlayer 1 select Wizard\n";
	cout << GREEN <<"-----------------------\n"<<RESET;
	for (unsigned int i = 0; i < wizards.size(); i++) {
		cout << GREEN << wizards[i]->attributes[0][0]->stringval << RESET<<"\n";
	}
	cout << GREEN << "-----------------------\n" << RESET;
	while (player1.selected == 0) {
		getline(cin, p1);
		for (unsigned int i = 0; i < wizards.size(); i++) {
			if (p1.compare(wizards[i]->attributes[0][0]->stringval) == 0) {
				cout << GREEN << "-----------------------\n" << wizards[i]->attributes[0][0]->stringval << "\n" << RESET;
				player1 = *(new Wizard(wizards[i]));
				player1.selected = 1;
			}
		}
	}
	cout << GREEN << "\nPlayer 2 select Wizard\n";
	cout << GREEN << "-----------------------\n" << RESET;
	for (unsigned int i = 0; i < wizards.size(); i++) {
		cout << GREEN << wizards[i]->attributes[0][0]->stringval << RESET << "\n";
	}
	cout << GREEN << "-----------------------\n" << RESET;
	while (player2.selected == 0) {
		getline(cin, p2);
		for (unsigned int i = 0; i < wizards.size(); i++) {
			if (p2.compare(wizards[i]->attributes[0][0]->stringval) == 0) {
				cout << GREEN << "-----------------------\n" << wizards[i]->attributes[0][0]->stringval << "\n" << RESET;
				player2 = new Wizard(wizards[i]);
				player2.selected = 1;
			}
		}
	}
	//test gia spells
	player1.ID = 1;
	player2.ID = 2;
	int playing = 2;
	while (1) {
		if(round2%2){
			if (player1.attributes[0][1]->stringval == "Ravenclaw") {
				player1.attributes[0][2]->intval += 0.05*player1.maxhealth;
				if (player1.attributes[0][2]->intval > player1.maxhealth)player1.attributes[0][2]->intval = player1.maxhealth;
			}
			if (player2.attributes[0][1]->stringval == "Ravenclaw") {
				player2.attributes[0][2]->intval += 0.05*player2.maxhealth;
				if (player2.attributes[0][2]->intval > player2.maxhealth)player2.attributes[0][2]->intval = player2.maxhealth;
			}
		}
		//Elegxos gia liksi tou duel
		if (player1.attributes[0][2]->intval <= 0) {
			cout << GREEN << "\n\n\n PLAYER 2 WINS!\n" << RESET;
			break;
		}
		if (player2.attributes[0][2]->intval <= 0) {
			cout << GREEN << "\n\n\n PLAYER 1 WINS!\n" << RESET;
			break;
		}
		//diatrexw to stack na dw ta dot,hot kai wands return
		for (unsigned int i = 0; i < rounds.size(); i++) {
			Playing = rounds[i]->attacker;
			NotPlaying = rounds[i]->defender;
			rounds[i]->RemainingRounds--;
			if (rounds[i]->RemainingRounds == -1) continue;
			if (rounds[i]->type == IF && rounds[i]->RemainingRounds == 0 && rounds[i]->tf == true) {
				rounds[i]->fun_ptr();
				if (player1.ID == Playing.ID) {
					player1.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
				}
				if (player2.ID == Playing.ID) {
					player2.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
				}
				if (player1.ID == NotPlaying.ID) {
					player1.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
				}
				if (player2.ID == NotPlaying.ID) {
					player2.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
				}
			}
			if (rounds[i]->type == ELSE_IF && rounds[i]->RemainingRounds == 0 && rounds[i]->tf == true) {
				if ((rounds[i - 1]->type == IF && rounds[i - 1]->tf == false)) {
					rounds[i]->fun_ptr();
					if (player1.ID == Playing.ID) {
						player1.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
					}
					if (player2.ID == Playing.ID) {
						player2.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
					}
					if (player1.ID == NotPlaying.ID) {
						player1.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
					}
					if (player2.ID == NotPlaying.ID) {
						player2.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
					}
				}
			}
			if (rounds[i]->type == ELSE && rounds[i]->RemainingRounds == 0) {
				if ((rounds[i - 1]->type == IF || rounds[i - 1]->type == ELSE_IF) && rounds[i - 1]->tf == false) {
					rounds[i]->fun_ptr();
					if (player1.ID == Playing.ID) {
						player1.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
					}
					if (player2.ID == Playing.ID) {
						player2.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
					}
					if (player1.ID == NotPlaying.ID) {
						player1.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
					}
					if (player2.ID == NotPlaying.ID) {
						player2.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
					}
				}
			}
			if (rounds[i]->type == AFTER && rounds[i]->RemainingRounds == 0) {
				rounds[i]->fun_ptr();
				if (player1.ID == Playing.ID) {
					player1.hasWand = Playing.hasWand;
				}
				if (player2.ID == Playing.ID) {
					player2.hasWand = Playing.hasWand;
				}
				if (player1.ID == NotPlaying.ID) {
					player1.hasWand = NotPlaying.hasWand;
				}
				if (player2.ID == NotPlaying.ID) {
					player2.hasWand = NotPlaying.hasWand;
				}
			}
			if (rounds[i]->type == FOR && rounds[i]->RemainingRounds >= 0) {
				rounds[i]->fun_ptr();
				if (player1.ID == Playing.ID) {
					player1.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
				}
				if (player2.ID == Playing.ID) {
					player2.attributes[0][2]->intval = Playing.attributes[0][2]->intval;
				}
				if (player1.ID == NotPlaying.ID) {
					player1.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
				}
				if (player2.ID == NotPlaying.ID) {
					player2.attributes[0][2]->intval = NotPlaying.attributes[0][2]->intval;
				}
			}
		}
		//
		round2++;
		string spelltocast;
		cout << GREEN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << "Round "<<round2<< "\n" << RESET;
		cout << GREEN << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		//player1 select spells
		if (player1.hasWand == 1) {
			cout << GREEN << player1.attributes[0][0]->stringval << "(Player 1) select spell\n" << RESET;
			Playing = player1;
			NotPlaying = player2;
			attacker=player1.attributes[0][1]->stringval;
			defender=player2.attributes[0][1]->stringval;
			for (unsigned int i = 0; i < player1.spellsknown.size(); i++) {
				cout << GREEN << player1.spellsknown[i]->attributes[0][0]->stringval << "\n" << RESET;
			}
			cout << GREEN << "-----------------------\n" << RESET;
			getline(cin, spelltocast);
			for (unsigned int i = 0; i < player1.spellsknown.size(); i++) {
				if (spelltocast == player1.spellsknown[i]->attributes[0][0]->stringval) {
					cout << GREEN << player1.spellsknown[i]->attributes[0][0]->stringval << "\n" << RESET;
					player1.spellsknown[i]->attributes[0][1]->fun_ptr();
					cout << GREEN << "-----------------------\n" << RESET;
				}
			}
			player1.hasWand = Playing.hasWand;
			player2.hasWand = NotPlaying.hasWand;
		}else cout << GREEN << "Player 1 doesn't have a wand!\n";
		//player2 select spells
		if (player2.hasWand == 1) {
			cout << GREEN << player2.attributes[0][0]->stringval << "(Player 2) select spell\n" << RESET;
			Playing = player2;
			NotPlaying = player1;
			attacker=player2.attributes[0][1]->stringval;
			defender=player1.attributes[0][1]->stringval;
			for (unsigned int i = 0; i < player2.spellsknown.size(); i++) {
				cout << GREEN << player2.spellsknown[i]->attributes[0][0]->stringval << "\n" << RESET;
			}
			getline(cin, spelltocast);
			for (unsigned int i = 0; i < player2.spellsknown.size(); i++) {
				if (spelltocast == player2.spellsknown[i]->attributes[0][0]->stringval) {
					cout << GREEN << player2.spellsknown[i]->attributes[0][0]->stringval << "\n" << RESET;
					player2.spellsknown[i]->attributes[0][1]->fun_ptr();
					cout << GREEN << "-----------------------\n" << RESET;
				}
			}
			player2.hasWand = Playing.hasWand;
			player1.hasWand = NotPlaying.hasWand;
		}
		else cout << GREEN << "Player 2 doesn't have a wand!\n";
		//print player1 stats
		cout << GREEN << "\n########################\n" << RESET;
		cout << GREEN << "NAME: " << player1.attributes[0][0]->stringval << "\n" << RESET;
		cout << GREEN << "HP: " << player1.attributes[0][2]->intval << "\n" << RESET;
		cout << GREEN << "wand "<<RESET;
		if (player1.hasWand == 1) {
			cout << GREEN << "equiped" << RESET;
		}
		else {
			cout << GREEN << "not equiped" << RESET;
		}
		cout << GREEN << "\n########################\n" << RESET;
		//print player2 stats
		cout << GREEN << "\n########################\n" << RESET;
		cout << GREEN << "NAME: " << player2.attributes[0][0]->stringval << "\n" << RESET;
		cout << GREEN << "HP: " << player2.attributes[0][2]->intval << "\n" << RESET;
		cout << GREEN << "wand " << RESET;
		if (player2.hasWand == 1) {
			cout << GREEN << "equiped" << RESET;
		}
		else {
			cout << GREEN << "not equiped" << RESET;
		}
		cout << GREEN << "\n########################\n\n" << RESET;
	}
}

//DEFINES
int a, counter = 1;
int b;
int DmgHealval = 0;

int j = 0;
Wizard *Target = new Wizard();
Wizard *temp;
Wizard wand1 = 1;
Wizard wand2 = 0;
stack *s[1000];

vector <MyType> attributes;

int get_hp(Wizard w) {
	return w.attributes[0][2]->intval;
}

//Start/End of programm
#define START_GAME int main(){cout<<GREEN<<"-------------------------------------Harry Potter the Game-------------------------------------"<<RESET<<"\n\n";
#define END_GAME ;cout<<GREEN<<"-------------------------------------Game is Over-------------------------------------"<<RESET<<"\n\n";return 0;}
//Create Wizard
#define CREATE ;
#define WIZARD Wizard() = attributes = 
#define WIZARDS Wizards()
#define SPELL Spell() = attributes =
#define SPELLS Spells()
#define NAME MyType() = false?"" 
#define HOUSE MyType() = false?""
#define HP MyType() = false?0
void aa() {} //dummy function gia na to kanei skip
#define ACTION MyType() = false?&aa
#define START [](){ 
#define DAMAGE DmgOrHeal = 1;
#define ATTACKER Playing
#define DEFENDER NotPlaying 
#define HEAL DmgOrHeal = 2;
#define END ;}
#define GET_HP get_hp
#define EQUIP ;equip(
#define a wand1);
#define _ ---wand2);
#define AFTER ;j++;s[j] = new stack(AFTER);s[j]->defender = NotPlaying;s[j]->attacker = Playing;s[j]->RemainingRounds =
#define ROUNDS ;rounds.push_back(s[j]);
#define FOR ;s[j] = new stack(FOR);s[j]->defender = NotPlaying;s[j]->attacker = Playing;s[j]->RemainingRounds =
#define DO ;s[j]->fun_ptr = [](){
#define MR ;Targettolearn = lookupwiz(
#define LEARN ); Learns()
#define SPELL_NAME(x) Learn(#x)
#define IF j++;s[j] = new stack(IF);s[j]->defender = NotPlaying;s[j]->attacker = Playing;s[j]->RemainingRounds = 1;rounds.push_back(s[j]);s[j]->tf =
#define ELSE_IF ;};j++;s[j] = new stack(ELSE_IF);s[j]->defender = NotPlaying;s[j]->attacker = Playing;s[j]->RemainingRounds = 1;rounds.push_back(s[j]);s[j]->tf =
#define ELSE ;};j++;s[j] = new stack(ELSE);s[j]->defender = NotPlaying;s[j]->attacker = Playing;s[j]->RemainingRounds = 1;rounds.push_back(s[j]);s[j]->fun_ptr = [](){
#define AND(x, ...) (x&& __VA_ARGS__)
#define OR(x, ...) (x|| __VA_ARGS__)
#define NOT !
//Print
#define SHOW ;cout
#define ALL_WIZARDS <<GREEN<<"Player "<<counter<<" Select Wizard:\n-----------------------\n"<<"\n"<<wizards[1]->attributes[0][0]->stringval<<RESET<<"\n\n";counter++;
//duel
#define DUEL ;duel();
//ENDIF
