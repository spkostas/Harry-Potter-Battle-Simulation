#define AND(x, ...) (x&& __VA_ARGS__)
#define OR(x, ...) (x|| __VA_ARGS__)
#define NOT !
#define IF if(
#define	DO ){
//#define END }
#define ELSE_IF }else if (
#define ELSE }else{
#define FOR for(auto i=0;i<
#define ROUNDS ;i++

#define ATTACKER (Playing)
#define DEFENDER (NotPlaying)

#define GET_HP(p) (p[0]->attributes[0][2]->intval)
#define GET_HOUSE(p)(p[0]->attributes[0][1]->stringval)
#define GET_NAME(p) (p[0]->attributes[0][0]->strval)
#define HAS_WAND(p)(p.wand_val;)		//einai wand.val??? + member: bool wand_val

//#define DAMAGE(b,x)(&b-=x) b##x		thelei allagh
//#define HEAL(b,x)(&b+=x) b##x

//to member target na ginei apo string-> Wizard gia na exoume ka8e fora shalow copy tou target kai na paizoume me to hp tou ktl
//to equip wand kai to damage/heal den doulevoun swsta de kserw ti allo na kanw kai 8a ta dw ayrio

//updated for houses
Wizard& operator,(int x) {
		//playing==attacker
		//notplaying==defender
		if (DmgOrHeal == 1) {
			if(Playing.attributes[0][1]->stringval=="Gryffindor"){
				if(NotPlaying.attributes[0][1]->stringval=="Gryffindor"){
					x-=x*0.20;
				}else if(NotPlaying.attributes[0][1]->stringval=="Hufflepuff"){
					x-=x*0.07;
				}
			}else if(Playing.attributes[0][1]->stringval=="Slytherin"){
				if(NotPlaying.attributes[0][1]->stringval=="Gryffindor"){
					x-=x*0.10;
				}else if(NotPlaying.attributes[0][1]->stringval=="Slytherin"){
					x+=x*0.15;
			    }else if(NotPlaying.attributes[0][1]->stringval=="Hufflepuff"){
			    	x+=x*0.08;
				}else if(NotPlaying.attributes[0][1]->stringval=="Ravenclaw"){
					x+=x*0.15;
				}
			}else if(Playing.attributes[0][1]->stringval=="Hufflepuff"){
				if(NotPlaying.attributes[0][1]->stringval=="Gryffindor"){
					x-=x*0.013;
				}else if(NotPlaying.attributes[0][1]->stringval=="Slytherin"){
					x+=x*0.07;
				}else if(NotPlaying.attributes[0][1]->stringval=="Ravenclaw"){
					x+=x*0.07;
				}
			}else if(Playing.attributes[0][1]->stringval=="Ravenclaw"){
				if(NotPlaying.attributes[0][1]->stringval=="Gryffindor"){
					if(!(rounds.size()%2)){
						x-=x*0.13;
					}else x-=x*0.20;
				}else if(NotPlaying.attributes[0][1]->stringval=="Slytherin"){
					if(!rounds.size()%2)x+=x*0.07;
				}else if(NotPlaying.attributes[0][1]->stringval=="Hufflepuff"){
					if(rounds.size()%2)x-=x*0.07;
				}else if(NotPlaying.attributes[0][1]->stringval=="Ravenclaw"){
					if(!rounds.size()%2)x+=x*0.07;
				}
			}
		NotPlaying.attributes[0][2]->intval -= x*bonus;
			}else {
			this->attributes[0][2]->intval += x;
		}
		return *this;
	}

//while(1)
if(player1.attributes[0][1]->stringval=="Ravenclaw"){
  player1.hp+=player1.maxhealth*0.05;
  if(player1.hp>maxhealth)player1.hp=player1.maxhealth
}
if(player2.attributes[0][1]->stringval=="Ravenclaw"){
  player2.hp+=player2.maxhealth*0.05;
  if(player2.hp>maxhealth)player2.hp=player2.maxhealth
}
