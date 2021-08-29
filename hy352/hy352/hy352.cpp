#include "wizSpells.h"
#include <iostream>
#include <vector>
using namespace std;

START_GAME
CREATE WIZARD{
NAME: "Harry Potter",
HOUSE : "Gryffindor",
HP : 120
}
CREATE WIZARD{
NAME: "Draco Malfoy",
HOUSE : "Slytherin",
HP : 100
}
CREATE WIZARDS[
	WIZARD{
	NAME: "Hermione Granger",
	HOUSE : "Gryffindor",
	HP : 120
	},
		WIZARD{
		NAME: "Luna Lovegood",
		HOUSE : "Ravenclaw",
		HP : 85
	}
]
CREATE SPELLS[
	SPELL{
		NAME: "Anapneo",
		ACTION : START
		END
	},
		SPELL{
			NAME: "Expulso",
			ACTION : START
				DAMAGE DEFENDER, 22
		END
	}
]CREATE SPELL{	NAME: "DEATH",		  ACTION : START				DAMAGE ATTACKER,500		END	}
		CREATE SPELL{
			NAME: "LOL2",
				ACTION : START
				DAMAGE DEFENDER, 20
				FOR 1 ROUNDS DO
					DAMAGE DEFENDER, 2
			END
			END
}
MR "Harry Potter" LEARN[
	SPELL_NAME(DEATH),
		SPELL_NAME(LOL2),
		SPELL_NAME(Expulso),
		SPELL_NAME(Anapneo)
]
MR "Draco Malfoy" LEARN[
	SPELL_NAME(LOL),
		SPELL_NAME(LOL2),
		SPELL_NAME(Expulso),
		SPELL_NAME(Anapneo)
]
DUEL
END_GAME
