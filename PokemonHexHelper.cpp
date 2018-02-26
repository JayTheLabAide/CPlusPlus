/*
	A thing to make hex-edit hacking of Pokemon Red easier.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstdio>
using namespace std;



string randomHexForMon();

string asciiToPKMNHex(string str);

//the first places to paste the mon's ID
const unsigned MON_PARTY_ID_STARTS[6] = { 0xD164, 0xd165, 0xd166, 0xd167, 0xd168, 0xd169};
//places to paste the mon's data
const unsigned MON_DATA_STARTS[6] = {0xd16b, 0xd197, 0xd1c3, 0xd1ef, 0xd21b, 0xd247 };
//places to paste mon's Original Trainer name
const unsigned MON_TNAME_STARTS[6] = { 0xd273, 0xd27e, 0xd289, 0xd294, 0xd29f, 0xd2aa};
//places to paste mon's nickname
const unsigned MON_NAME_STARTS[6] = { 0xd2b5, 0xd2c0, 0xd2cb, 0xd2d6, 0xd2e1, 0xd2ec };

int main(){
	srand(time(0));
	
	bool exit=false;
	do{
		cout<<"Enter Pokemon Nickname (max length 10): ";
		string pname;
		getline(cin, pname);
		//will be converted with asciiToPKMNHex
		//cout<< asciiToPKMNHex( pname );
		
		
		cout<<"Enter Original Trainer Name (max length 10): ";
		string tname;
		getline(cin, tname);
		//will be converted with asciiToPKMNHex
		//cout<<asciitoPKMNHex( tname );
		
		cout<<"Enter Pokemon Slot Number (1-6):";
		short slot;
		cin>>slot;
		--slot;
		if(slot<1||slot>5)slot=0;
		cin.ignore(BUFSIZ, '\n');
		bool isAtEnd;
		if (slot==5)isAtEnd=true;
		else{
			cout<<"Is Pokemon being added to end of the party and/or is alone? (Y/N):";
			string endPartyYN;
			getline(cin, endPartyYN);
			isAtEnd = (endPartyYN[0]=='y'||endPartyYN[0]=='Y');
		}
		
		//generate the actual data block for the random pokemon
		string monHex = randomHexForMon();
		
		cout<<"\nFor random Pokemon at slot "<<slot+1<<":\n";
		
		if (isAtEnd) {
			
			cout<<"\nParty Count, Paste at 0XD163:\n";
			cout<<"0"<< slot+1 <<endl;
		}
		
		//cout<<"Paste at 0x"<< MON_PARTY_ID_STARTS[slot]<<":\n";
		printf("ID, Paste at %#X:\n", MON_PARTY_ID_STARTS[slot] );
		cout<<monHex.substr(0, 2);
		if (isAtEnd)cout<<"FF";
		cout<<"\n";
		
		
		//cout<<"Paste at 0x"<< MON_DATA_STARTS[slot] <<":\n";
		printf("Data, Paste at %#X:\n", MON_DATA_STARTS[slot] );
		cout<<monHex<<"\n";
		
		//cout<<"Paste at 0x"<< MON_TNAME_STARTS[slot] <<":\n";
		printf("Trainer Name, Paste at %#X:\n", MON_TNAME_STARTS[slot] );
		cout<< asciiToPKMNHex( tname ) <<"\n";
		
		//cout<<"Paste at 0x"<< MON_NAME_STARTS[slot] <<":\n";
		printf("Pokemon Name, Paste at %#X:\n", MON_NAME_STARTS[slot] );	
		cout<< asciiToPKMNHex( pname ) <<endl;
		
		
	
		cout<<"Exit?(Y/N):";
		string qyn;
		getline(cin,qyn);
		if ( qyn[0]=='Y'||qyn[0]=='y')exit=true; 
		if(!cin.good()){cin.clear(); cin.ignore(BUFSIZ, '\n');}
	}while(!exit);
}

const unsigned short STATS=30;
const unsigned short STATOFFSETS[ STATS ]={
	0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 17, 19, 21,
	23, 25, 27, 28, 29, 30, 31, 32, 33, 34, 36, 38, 40, 42 };

const unsigned short TYPES=15;
const unsigned short TYPEIDS[TYPES]={ 0, 1, 2, 3, 4, 5, 7, 8, 
	0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A};

//WORKS!!!
string randomHexForMon(){
	
	const unsigned short MONBYTESZ = 44*2;
	char buf[MONBYTESZ]{};
	
	//short id = rand()%191;
	
//	cout<<"Enter an ID (0-190):";
//	cin>>id;

	//write hex digits as chars into buffer which will be returned as string
	const unsigned int OB = 255, TWB = 65535, THB = 16777215 ;
	unsigned maxAndCurrHP = 20+rand()%(999-20);
	
//	ID: 0
	sprintf( &buf[ STATOFFSETS[0]*2 ] , "%02X", rand()%191 ); //%x gives hex digits, %#x gives 0x__
//	Current HP: 1
	sprintf( &buf[ STATOFFSETS[1]*2 ] , "%04X", maxAndCurrHP );
	
//	'Level': 3
	sprintf( &buf[ STATOFFSETS[2]*2 ] , "01");
//	Status: 4
	sprintf( &buf[ STATOFFSETS[3]*2 ] , "00");
	
	//TYPES //todo- look up proper types
	
//	Type 1: 5
	sprintf( &buf[ STATOFFSETS[4]*2 ] , "%02X", TYPEIDS[ rand()%TYPES] );
//	Type 2: 6
	sprintf( &buf[ STATOFFSETS[5]*2] , "%02X", TYPEIDS[ rand()%TYPES] );
	
	
//	Catch rate: 7
	sprintf( &buf[ STATOFFSETS[6]*2 ] , "%02X", 1+rand()%(OB-1) );
	
	//MOVES //todo - look up proper moves
	
//	Move 1: 8
	sprintf( &buf[ STATOFFSETS[7]*2 ] , "%02X", 1+rand()%(164) );
//	Move 2: 9
	sprintf( &buf[ STATOFFSETS[8]*2 ] , "%02X", 1+rand()%(164) );
//	Move 3: 10
	sprintf( &buf[ STATOFFSETS[9]*2 ] , "%02X", 1+rand()%(164) );
//	Move 4: 11
	sprintf( &buf[ STATOFFSETS[10]*2 ] , "%02X", 1+rand()%(164) );
	
	
//	Trainer ID: 12
	sprintf( &buf[ STATOFFSETS[11]*2 ] , "%04X", rand()%TWB );
	
//	EXP: 14
	sprintf( &buf[ STATOFFSETS[12]*2 ] , "%06X", rand()%THB );
	
	
	//EVS AND IVS
	
//	HP EV: 17
	sprintf( &buf[ STATOFFSETS[13]*2 ] , "%04X", rand()%TWB );
//	ATK EV: 19
	sprintf( &buf[ STATOFFSETS[14]*2 ] , "%04X", rand()%TWB );
//	Def EV: 21
	sprintf( &buf[ STATOFFSETS[15]*2 ] , "%04X", rand()%TWB );
//	SPD EV: 23
	sprintf( &buf[ STATOFFSETS[16]*2 ] , "%04X", rand()%TWB );
//	SPC EV: 25
	sprintf( &buf[ STATOFFSETS[17]*2 ] , "%04X", rand()%TWB );
//	ATK/DEF IV: 27
	sprintf( &buf[ STATOFFSETS[18]*2 ] , "%02X", rand()%OB );
//	SPD/SPC IV: 28
	sprintf( &buf[ STATOFFSETS[19]*2 ] , "%02X", rand()%OB );
	
	//CURRENT MOVE PP LEVELS
	
//	PP Move 1: 29
	sprintf( &buf[ STATOFFSETS[20]*2 ] , "%02X", 30 );
//	PP Move 2: 30
	sprintf( &buf[ STATOFFSETS[21]*2 ] , "%02X", 30 );
//	PP Move 3: 31
	sprintf( &buf[ STATOFFSETS[22]*2 ] , "%02X", 30 );
//	PP Move 4: 32
	sprintf( &buf[ STATOFFSETS[23]*2 ] , "%02X", 30 );
	
	//LEVEL AND KNOWN STATS
	
//	Level: 33
	sprintf( &buf[ STATOFFSETS[24]*2 ] , "%02X", 1+rand()%OB );
//	Max HP: 34
	sprintf( &buf[ STATOFFSETS[25]*2 ] , "%04X", maxAndCurrHP );
//	ATK: 36
	sprintf( &buf[ STATOFFSETS[26]*2 ] , "%04X", 5+rand()%(200-5) );
//	DEF: 38
	sprintf( &buf[ STATOFFSETS[27]*2 ] , "%04X", 5+rand()%(200-5) );
//	SPD: 40
	sprintf( &buf[ STATOFFSETS[28]*2 ] , "%04X", 5+rand()%(200-5) );
//	SPC: 42
	sprintf( &buf[ STATOFFSETS[29]*2 ] , "%04X", 5+rand()%(200-5) );
	
	
	return string( buf, MONBYTESZ);

}

/*
	Pokestats offsets
	ID: 0
	Curr HP: 1
	'Level': 3
	Status: 4
	Type 1: 5
	Type 2: 6
	Catch rate: 7
	Move 1: 8
	Move 2: 9
	Move 3: 10
	Move 4: 11
	Trainer ID: 12
	EXP: 14
	HP EV: 17
	ATK EV: 19
	Def EV: 21
	SPD EV: 23
	SPC EV: 25
	ATK/DEF IV: 27
	SPD/SPC IV: 28
	PP Move 1: 29
	PP Move 2: 30
	PP Move 3: 31
	PP Move 4: 32
	Level: 33
	Max HP: 34
	ATK: 36
	DEF: 38
	SPD: 40
	SPC: 42
	
*/

//WORKS!
string asciiToPKMNHex(string str){
	//Made with "The Big Hex List" as reference from:
	//https://glitchcity.info/wiki/The_Big_HEX_List
	//hex 80: A, hex 99: Z,
	//hex A0: a, hex B9: z
	//hex F6: 0
	string result="";
	char hexByte[2];
	for(int i = 0; i < 11; i++ ){
		if (i < str.length() && i<10 ){
			char letter = str[i];
			if (letter >='A'&&letter<='Z'){
				sprintf(hexByte, "%02X", 0x80+ letter-'A' );
				result.append(hexByte, 2);
			}
			else if(letter >='a'&&letter<='z'){
				sprintf(hexByte, "%02X", 0xA0+letter-'a' );
				result.append(hexByte, 2);
			}
			else if (letter >='0'&&letter<='9'){
				sprintf(hexByte, "%02X", 0xF6+letter-'0' );
				result.append(hexByte, 2);
			}
			else{
				result+="7F"; //space character
			}
		}
		else{
			result+="50"; //control character, end of name marker
		}
	}
	return result;
}

/*
From: https://github.com/pret/pokered/blob/master/constants/pokemon_constants.asm
	const RHYDON       ; $01
	const KANGASKHAN   ; $02
	const NIDORAN_M    ; $03
	const CLEFAIRY     ; $04
	const SPEAROW      ; $05
	const VOLTORB      ; $06
	const NIDOKING     ; $07
	const SLOWBRO      ; $08
	const IVYSAUR      ; $09
	const EXEGGUTOR    ; $0A
	const LICKITUNG    ; $0B
	const EXEGGCUTE    ; $0C
	const GRIMER       ; $0D
	const GENGAR       ; $0E
	const NIDORAN_F    ; $0F
	const NIDOQUEEN    ; $10
	const CUBONE       ; $11
	const RHYHORN      ; $12
	const LAPRAS       ; $13
	const ARCANINE     ; $14
	const MEW          ; $15
	const GYARADOS     ; $16
	const SHELLDER     ; $17
	const TENTACOOL    ; $18
	const GASTLY       ; $19
	const SCYTHER      ; $1A
	const STARYU       ; $1B
	const BLASTOISE    ; $1C
	const PINSIR       ; $1D
	const TANGELA      ; $1E
	const MISSINGNO_1F ; $1F
	const MISSINGNO_20 ; $20
	const GROWLITHE    ; $21
	const ONIX         ; $22
	const FEAROW       ; $23
	const PIDGEY       ; $24
	const SLOWPOKE     ; $25
	const KADABRA      ; $26
	const GRAVELER     ; $27
	const CHANSEY      ; $28
	const MACHOKE      ; $29
	const MR_MIME      ; $2A
	const HITMONLEE    ; $2B
	const HITMONCHAN   ; $2C
	const ARBOK        ; $2D
	const PARASECT     ; $2E
	const PSYDUCK      ; $2F
	const DROWZEE      ; $30
	const GOLEM        ; $31
	const MISSINGNO_32 ; $32
	const MAGMAR       ; $33
	const MISSINGNO_34 ; $34
	const ELECTABUZZ   ; $35
	const MAGNETON     ; $36
	const KOFFING      ; $37
	const MISSINGNO_38 ; $38
	const MANKEY       ; $39
	const SEEL         ; $3A
	const DIGLETT      ; $3B
	const TAUROS       ; $3C
	const MISSINGNO_3D ; $3D
	const MISSINGNO_3E ; $3E
	const MISSINGNO_3F ; $3F
	const FARFETCHD    ; $40
	const VENONAT      ; $41
	const DRAGONITE    ; $42
	const MISSINGNO_43 ; $43
	const MISSINGNO_44 ; $44
	const MISSINGNO_45 ; $45
	const DODUO        ; $46
	const POLIWAG      ; $47
	const JYNX         ; $48
	const MOLTRES      ; $49
	const ARTICUNO     ; $4A
	const ZAPDOS       ; $4B
	const DITTO        ; $4C
	const MEOWTH       ; $4D
	const KRABBY       ; $4E
	const MISSINGNO_4F ; $4F
	const MISSINGNO_50 ; $50
	const MISSINGNO_51 ; $51
	const VULPIX       ; $52
	const NINETALES    ; $53
	const PIKACHU      ; $54
	const RAICHU       ; $55
	const MISSINGNO_56 ; $56
	const MISSINGNO_57 ; $57
	const DRATINI      ; $58
	const DRAGONAIR    ; $59
	const KABUTO       ; $5A
	const KABUTOPS     ; $5B
	const HORSEA       ; $5C
	const SEADRA       ; $5D
	const MISSINGNO_5E ; $5E
	const MISSINGNO_5F ; $5F
	const SANDSHREW    ; $60
	const SANDSLASH    ; $61
	const OMANYTE      ; $62
	const OMASTAR      ; $63
	const JIGGLYPUFF   ; $64
	const WIGGLYTUFF   ; $65
	const EEVEE        ; $66
	const FLAREON      ; $67
	const JOLTEON      ; $68
	const VAPOREON     ; $69
	const MACHOP       ; $6A
	const ZUBAT        ; $6B
	const EKANS        ; $6C
	const PARAS        ; $6D
	const POLIWHIRL    ; $6E
	const POLIWRATH    ; $6F
	const WEEDLE       ; $70
	const KAKUNA       ; $71
	const BEEDRILL     ; $72
	const MISSINGNO_73 ; $73
	const DODRIO       ; $74
	const PRIMEAPE     ; $75
	const DUGTRIO      ; $76
	const VENOMOTH     ; $77
	const DEWGONG      ; $78
	const MISSINGNO_79 ; $79
	const MISSINGNO_7A ; $7A
	const CATERPIE     ; $7B
	const METAPOD      ; $7C
	const BUTTERFREE   ; $7D
	const MACHAMP      ; $7E
	const MISSINGNO_7F ; $7F
	const GOLDUCK      ; $80
	const HYPNO        ; $81
	const GOLBAT       ; $82
	const MEWTWO       ; $83
	const SNORLAX      ; $84
	const MAGIKARP     ; $85
	const MISSINGNO_86 ; $86
	const MISSINGNO_87 ; $87
	const MUK          ; $88
	const MISSINGNO_8A ; $8A
	const KINGLER      ; $8A
	const CLOYSTER     ; $8B
	const MISSINGNO_8C ; $8C
	const ELECTRODE    ; $8D
	const CLEFABLE     ; $8E
	const WEEZING      ; $8F
	const PERSIAN      ; $90
	const MAROWAK      ; $91
	const MISSINGNO_92 ; $92
	const HAUNTER      ; $93
	const ABRA         ; $94
	const ALAKAZAM     ; $95
	const PIDGEOTTO    ; $96
	const PIDGEOT      ; $97
	const STARMIE      ; $98
	const BULBASAUR    ; $99
	const VENUSAUR     ; $9A
	const TENTACRUEL   ; $9B
	const MISSINGNO_9C ; $9C
	const GOLDEEN      ; $9D
	const SEAKING      ; $9E
	const MISSINGNO_9F ; $9F
	const MISSINGNO_A0 ; $A0
	const MISSINGNO_A1 ; $A1
	const MISSINGNO_A2 ; $A2
	const PONYTA       ; $A3
	const RAPIDASH     ; $A4
	const RATTATA      ; $A5
	const RATICATE     ; $A6
	const NIDORINO     ; $A7
	const NIDORINA     ; $A8
	const GEODUDE      ; $A9
	const PORYGON      ; $AA
	const AERODACTYL   ; $AB
	const MISSINGNO_AC ; $AC
	const MAGNEMITE    ; $AD
	const MISSINGNO_AE ; $AE
	const MISSINGNO_AF ; $AF
	const CHARMANDER   ; $B0
	const SQUIRTLE     ; $B1
	const CHARMELEON   ; $B2
	const WARTORTLE    ; $B3
	const CHARIZARD    ; $B4
	const MISSINGNO_B5 ; $B5
	const FOSSIL_KABUTOPS   ; $B6
	const FOSSIL_AERODACTYL ; $B7
	const MON_GHOST    ; $B8
	const ODDISH       ; $B9
	const GLOOM        ; $BA
	const VILEPLUME    ; $BB
	const BELLSPROUT   ; $BC
	const WEEPINBELL   ; $BD
	const VICTREEBEL   ; $BE
*/

/*
From: https://github.com/pret/pokered/blob/master/constants/type_constants.asm
; Elemental types
NORMAL   EQU $00
FIGHTING EQU $01
FLYING   EQU $02
POISON   EQU $03
GROUND   EQU $04
ROCK     EQU $05
BUG      EQU $07
GHOST    EQU $08
FIRE     EQU $14
WATER    EQU $15
GRASS    EQU $16
ELECTRIC EQU $17
PSYCHIC  EQU $18
ICE      EQU $19
DRAGON   EQU $1A
*/

/*

MOVES

const POUND        ; 01
	const KARATE_CHOP  ; 02
	const DOUBLESLAP   ; 03
	const COMET_PUNCH  ; 04
	const MEGA_PUNCH   ; 05
	const PAY_DAY      ; 06
	const FIRE_PUNCH   ; 07
	const ICE_PUNCH    ; 08
	const THUNDERPUNCH ; 09
	const SCRATCH      ; 0a
	const VICEGRIP     ; 0b
	const GUILLOTINE   ; 0c
	const RAZOR_WIND   ; 0d
	const SWORDS_DANCE ; 0e
	const CUT          ; 0f
	const GUST         ; 10
	const WING_ATTACK  ; 11
	const WHIRLWIND    ; 12
	const FLY          ; 13
	const BIND         ; 14
	const SLAM         ; 15
	const VINE_WHIP    ; 16
	const STOMP        ; 17
	const DOUBLE_KICK  ; 18
	const MEGA_KICK    ; 19
	const JUMP_KICK    ; 1a
	const ROLLING_KICK ; 1b
	const SAND_ATTACK  ; 1c
	const HEADBUTT     ; 1d
	const HORN_ATTACK  ; 1e
	const FURY_ATTACK  ; 1f
	const HORN_DRILL   ; 20
	const TACKLE       ; 21
	const BODY_SLAM    ; 22
	const WRAP         ; 23
	const TAKE_DOWN    ; 24
	const THRASH       ; 25
	const DOUBLE_EDGE  ; 26
	const TAIL_WHIP    ; 27
	const POISON_STING ; 28
	const TWINEEDLE    ; 29
	const PIN_MISSILE  ; 2a
	const LEER         ; 2b
	const BITE         ; 2c
	const GROWL        ; 2d
	const ROAR         ; 2e
	const SING         ; 2f
	const SUPERSONIC   ; 30
	const SONICBOOM    ; 31
	const DISABLE      ; 32
	const ACID         ; 33
	const EMBER        ; 34
	const FLAMETHROWER ; 35
	const MIST         ; 36
	const WATER_GUN    ; 37
	const HYDRO_PUMP   ; 38
	const SURF         ; 39
	const ICE_BEAM     ; 3a
	const BLIZZARD     ; 3b
	const PSYBEAM      ; 3c
	const BUBBLEBEAM   ; 3d
	const AURORA_BEAM  ; 3e
	const HYPER_BEAM   ; 3f
	const PECK         ; 40
	const DRILL_PECK   ; 41
	const SUBMISSION   ; 42
	const LOW_KICK     ; 43
	const COUNTER      ; 44
	const SEISMIC_TOSS ; 45
	const STRENGTH     ; 46
	const ABSORB       ; 47
	const MEGA_DRAIN   ; 48
	const LEECH_SEED   ; 49
	const GROWTH       ; 4a
	const RAZOR_LEAF   ; 4b
	const SOLARBEAM    ; 4c
	const POISONPOWDER ; 4d
	const STUN_SPORE   ; 4e
	const SLEEP_POWDER ; 4f
	const PETAL_DANCE  ; 50
	const STRING_SHOT  ; 51
	const DRAGON_RAGE  ; 52
	const FIRE_SPIN    ; 53
	const THUNDERSHOCK ; 54
	const THUNDERBOLT  ; 55
	const THUNDER_WAVE ; 56
	const THUNDER      ; 57
	const ROCK_THROW   ; 58
	const EARTHQUAKE   ; 59
	const FISSURE      ; 5a
	const DIG          ; 5b
	const TOXIC        ; 5c
	const CONFUSION    ; 5d
	const PSYCHIC_M    ; 5e
	const HYPNOSIS     ; 5f
	const MEDITATE     ; 60
	const AGILITY      ; 61
	const QUICK_ATTACK ; 62
	const RAGE         ; 63
	const TELEPORT     ; 64
	const NIGHT_SHADE  ; 65
	const MIMIC        ; 66
	const SCREECH      ; 67
	const DOUBLE_TEAM  ; 68
	const RECOVER      ; 69
	const HARDEN       ; 6a
	const MINIMIZE     ; 6b
	const SMOKESCREEN  ; 6c
	const CONFUSE_RAY  ; 6d
	const WITHDRAW     ; 6e
	const DEFENSE_CURL ; 6f
	const BARRIER      ; 70
	const LIGHT_SCREEN ; 71
	const HAZE         ; 72
	const REFLECT      ; 73
	const FOCUS_ENERGY ; 74
	const BIDE         ; 75
	const METRONOME    ; 76
	const MIRROR_MOVE  ; 77
	const SELFDESTRUCT ; 78
	const EGG_BOMB     ; 79
	const LICK         ; 7a
	const SMOG         ; 7b
	const SLUDGE       ; 7c
	const BONE_CLUB    ; 7d
	const FIRE_BLAST   ; 7e
	const WATERFALL    ; 7f
	const CLAMP        ; 80
	const SWIFT        ; 81
	const SKULL_BASH   ; 82
	const SPIKE_CANNON ; 83
	const CONSTRICT    ; 84
	const AMNESIA      ; 85
	const KINESIS      ; 86
	const SOFTBOILED   ; 87
	const HI_JUMP_KICK ; 88
	const GLARE        ; 89
	const DREAM_EATER  ; 8a
	const POISON_GAS   ; 8b
	const BARRAGE      ; 8c
	const LEECH_LIFE   ; 8d
	const LOVELY_KISS  ; 8e
	const SKY_ATTACK   ; 8f
	const TRANSFORM    ; 90
	const BUBBLE       ; 91
	const DIZZY_PUNCH  ; 92
	const SPORE        ; 93
	const FLASH        ; 94
	const PSYWAVE      ; 95
	const SPLASH       ; 96
	const ACID_ARMOR   ; 97
	const CRABHAMMER   ; 98
	const EXPLOSION    ; 99
	const FURY_SWIPES  ; 9a
	const BONEMERANG   ; 9b
	const REST         ; 9c
	const ROCK_SLIDE   ; 9d
	const HYPER_FANG   ; 9e
	const SHARPEN      ; 9f
	const CONVERSION   ; a0
	const TRI_ATTACK   ; a1
	const SUPER_FANG   ; a2
	const SLASH        ; a3
	const SUBSTITUTE   ; a4
*/

/*
From: https://datacrystal.romhacking.net/wiki/Pok%C3%A9mon_Red/Blue:RAM_map#Items

Player

D158-D162 - Your Name

D163 - # Pokémon In Party
D164 - Pokémon 1
D165 - Pokémon 2
D166 - Pokémon 3
D167 - Pokémon 4
D168 - Pokémon 5
D169 - Pokémon 6
D16A - End of list

Pokémon 1

D16B - Pokémon (Again)
D16C-D16D - Current HP
D16E - 'Level' (not the actual level, see the notes article)
D16F - Status (Poisoned, Paralyzed, etc.)
D170 - Type 1
D171 - Type 2
D172 - Catch rate/Held item (When traded to Generation II)
D173 - Move 1
D174 - Move 2
D175 - Move 3
D176 - Move 4
D177-D178 - Trainer ID
D179-D17B - Experience
D17C-D17D - HP EV
D17E-D17F - Attack EV
D180-D181 - Defense EV
D182-D183 - Speed EV
D184-D185 - Special EV
D186 - Attack/Defense IV
D187 - Speed/Special IV
D188 - PP Move 1
D189 - PP Move 2
D18A - PP Move 3
D18B - PP Move 4
D18C - Level (actual level)
D18D-D18E - Max HP
D18F-D190 - Attack
D191-D192 - Defense
D193-D194 - Speed
D195-D196 - Special

Pokémon 2

D197 - Pokémon
D198-D199 - Current HP
D19A - 'Level' (not the actual level, see the notes article)
D19B - Status
D19C - Type 1
D19D - Type 2
D19E - Catch rate/Held item (When traded to Generation II)
D19F - Move 1
D1A0 - Move 2
D1A1 - Move 3
D1A2 - Move 4
D1A3-D1A4 - Trainer ID
D1A5-D1A7 - Experience 
D1A8-D1A9 - HP EV
D1AA-D1AB - Attack EV
D1AC-D1AD - Defense EV
D1AE-D1AF - Speed EV
D1B0-D1B1 - Special EV
D1B2 - Attack/Defense IV
D1B3 - Speed/Special IV
D1B4 - PP Move 1
D1B5 - PP Move 2
D1B6 - PP Move 3
D1B7 - PP Move 4
D1B8 - Level (actual)
D1B9-D1BA - Max HP
D1BB-D1BC - Attack
D1BD-D1BE - Defense
D1BF-D1C0 - Speed
D1C1-D1C2 - Special

Pokémon 3

D1C3 - Pokémon
D1C4-D1C5 - Current HP
D1C6 - 'Level' (not the actual level, see the notes article)
D1C7 - Status
D1C8 - Type 1
D1C9 - Type 2
D1CA - Catch rate/Held item (When traded to Generation II)
D1CB - Move 1
D1CC - Move 2
D1CD - Move 3
D1CE - Move 4
D1CF-D1D0 - Trainer ID
D1D1-D1D3 - Experience
D1D4-D1D5 - HP EV
D1D6-D1D7 - Attack EV
D1D8-D1D9 - Defense EV
D1DA-D1DB - Speed EV
D1DC-D1DD - Special EV
D1DE - Attack/Defense IV
D1DF - Speed/Special IV
D1E0 - PP Move 1
D1E1 - PP Move 2
D1E2 - PP Move 3
D1E3 - PP Move 4
D1E4 - Level
D1E5-D1E6 - Max HP
D1E7-D1E8 - Attack
D1E9-D1EA - Defense
D1EB-D1EC - Speed
D1ED-D1EE - Special

Pokémon 4

D1EF - Pokémon
D1F0-D1F1 - Current HP
D1F2 - 'Level' (not the actual level, see the notes article)
D1F3 - Status
D1F4 - Type 1
D1F5 - Type 2
D1F6 - Catch rate/Held item (When traded to Generation II)
D1F7 - Move 1
D1F8 - Move 2
D1F9 - Move 3
D1FA - Move 4
D1FB-D1FC - Trainer ID
D1FD-D1FF - Experience 
D200-D201 - HP EV
D202-D203 - Attack EV
D204-D205 - Defense EV
D206-D207 - Speed EV
D208-D209 - Special EV
D20A - Attack/Defense IV
D20B - Speed/Special IV
D20C - PP Move 1
D20D - PP Move 2
D20E - PP Move 3
D20F - PP Move 4
D210 - Level
D211-D212 - Max HP
D213-D214 - Attack
D215-D216 - Defense
D217-D218 - Speed
D219-D21A - Special

Pokémon 5

D21B - Pokémon
D21C-D21D - Current HP
D21E - 'Level' (not the actual level, see the notes article)
D21F - Status
D220 - Type 1
D221 - Type 2
D222 - Catch rate/Held item (When traded to Generation II)
D223 - Move 1
D224 - Move 2
D225 - Move 3
D226 - Move 4
D227-D228 - Trainer ID
D229-D22B - Experience 
D22C-D22D - HP EV
D22E-D22F - Attack EV
D230-D231 - Defense EV
D232-D233 - Speed EV
D234-D235 - Special EV
D236 - Attack/Defense IV
D237 - Speed/Special IV
D238 - PP Move 1
D239 - PP Move 2
D23A - PP Move 3
D23B - PP Move 4
D23C - Level
D23D-D23E - Max HP
D23F-D240 - Attack
D241-D242 - Defense
D243-D244 - Speed
D245-D246 - Special

Pokémon 6

D247 - Pokémon
D248-D249 - Current HP
D24A - 'Level' (not the actual level, see the notes article)
D24B - Status
D24C - Type 1
D24D - Type 2
D24E - Catch rate/Held item (When traded to Generation II)
D24F - Move 1
D250 - Move 2
D251 - Move 3
D252 - Move 4
D253-D254 - Trainer ID
D255-D257 - Experience 
D258-D259 - HP EV
D25A-D25B - Attack EV
D25C-D25D - Defense EV
D25E-D25F - Speed EV
D260-D261 - Special EV
D262 - Attack/Defense IV
D263 - Speed/Special IV
D264 - PP Move 1
D265 - PP Move 2
D266 - PP Move 3
D267 - PP Move 4
D268 - Level
D269-D26A - Max HP
D26B-D26C - Attack
D26D-D26E - Defense
D26F-D270 - Speed
D271-D272 - Special

Trainer Name

D273-D27D - Trainer name for 1st
D27E-D288 - Trainer name for 2nd
D289-D293 - Trainer name for 3rd
D294-D29E - Trainer name for 4th
D29F-D2A9 - Trainer name for 5th
D2AA-D2B4 - Trainer name for 6th

Nickname

D2B5-D2BF - Nickname for 1st
D2C0-D2CA - Nickname for 2nd
D2CB-D2D5 - Nickname for 3rd
D2D6-D2E0 - Nickname for 4th
D2E1-D2EB - Nickname for 5th
D2EC-D2F6 - Nickname for 6th

Pokedex

    D2F7 - Own 1-8
    D2F8 - Own 9-16
    D2F9 - Own 17-24
    D2FA - Own 25-32
    D2FB - Own 33-40
    D2FC - Own 41-48
    D2FD - Own 49-56
    D2FE - Own 57-64
    D2FF - Own 65-72
    D300 - Own 73-80
    D301 - Own 81-88
    D302 - Own 89-96
    D303 - Own 97-104
    D304 - Own 105-112
    D305 - Own 113-120
    D306 - Own 121-128
    D307 - Own 129-136
    D308 - Own 137-144
    D309 - Own 145-152 
    D30A - Seen 1-8
    D30B - Seen 9-16
    D30C - Seen 17-24
    D30D - Seen 25-32
    D30E - Seen 33-40
    D30F - Seen 41-48
    D310 - Seen 49-56
    D311 - Seen 57-64
    D312 - Seen 65-72
    D313 - Seen 73-80
    D314 - Seen 81-88
    D315 - Seen 89-96
    D316 - Seen 97-104
    D317 - Seen 105-112
    D318 - Seen 113-120
    D319 - Seen 121-128
    D31A - Seen 129-136
    D31B - Seen 137-144
    D31C - Seen 145-152

Items

    D31D - Total Items
    D31E - Item 1
    D31F - Item 1 Quantity
    D320 - Item 2 
    D321 - Item 2 Quantity
    D322 - Item 3
    D323 - Item 3 Quantity
    D324 - Item 4
    D325 - Item 4 Quantity
    D326 - Item 5
    D327 - Item 5 Quantity
    D328 - Item 6
    D329 - Item 6 Quantity
    D32A - Item 7
    D32B - Item 7 Quantity
    D32C - Item 8
    D32D - Item 8 Quantity
    D32E - Item 9
    D32F - Item 9 Quantity
    D330 - Item 10
    D331 - Item 10 Quantity
    D332 - Item 11
    D333 - Item 11 Quantity
    D334 - Item 12
    D335 - Item 12 Quantity
    D336 - Item 13
    D337 - Item 13 Quantity
    D338 - Item 14 
    D339 - Item 14 Quantity
    D33A - Item 15
    D33B - Item 15 Quantity
    D33C - Item 16
    D33D - Item 16 Quantity
    D33E - Item 17
    D33F - Item 17 Quantity
    D340 - Item 18
    D341 - Item 18 Quantity
    D342 - Item 19
    D343 - Item 19 Quantity
    D344 - Item 20
    D345 - Item 20 Quantity
    D346 - Item End of List

Money

    D347 - Money Byte 1
    D348 - Money Byte 2
    D349 - Money Byte 3

Rival

    D34A-D351 - Rival's Name
    
    ------
    
    Game Coins

    D5A4 - Casino Chips Byte 1
    D5A5 - Casino Chips Byte 2
    --------
    
    /// Here would go the data for all the event flags,
    /// but this isn't meant to be an event hacker, just a
    /// party and item hacker.
    
    --------
    Wild Pokémon

D887 - Wild Pokémon encounter rates

Common Battles:

    D888 - Level of Encounter 1
    D889 - Pokémon Data Value 1
    D88A - Level of Encounter 2
    D88B - Pokémon Data Value 2
    D88C - Level of Encounter 3
    D88D - Pokémon Data Value 3
    D88E - Level of Encounter 4
    D88F - Pokémon Data Value 4

Uncommon Battles:

    D890 - Level of Encounter 1
    D891 - Pokémon Data Value 1
    D892 - Level of Encounter 2
    D893 - Pokémon Data Value 2
    D894 - Level of Encounter 3
    D895 - Pokémon Data Value 3
    D896 - Level of Encounter 4
    D897 - Pokémon Data Value 4

Rare Battles:

    D898 - Level of Encounter 1
    D899 - Pokémon Data Value 1
    D89A - Level of Encounter 2 
    D89B - Pokémon Data Value 2

Opponent Trainer’s Pokémon

    D89C - Total enemy Pokémon
    D89D - Pokémon 1
    D89E - Pokémon 2
    D89F - Pokémon 3
    D8A0 - Pokémon 4
    D8A1 - Pokémon 5
    D8A2 - Pokémon 6
    D8A3 - End of list

Pokémon 1

    D8A4 - Pokémon
    D8A5-D8A6 - Current HP
    D8A7 - 
    D8A8 - Status
    D8A9 - Type 1
    D8AA - Type 2
    D8AB - 
    D8AC - Move 1
    D8AD - Move 2
    D8AE - Move 3
    D8AF - Move 4
    D8B0-D8B1 - Trainer ID
    D8B2-D8B4 - Experience
    D8B5-D8B6 - HP EV
    D8B7-D8B8 - Attack EV
    D8B9-D8BA - Defense EV
    D8BB-D8BC - Speed EV
    D8BD-D8BE - Special EV
    D8BF - Attack/Defense IV
    D8C0 - Speed/Special IV
    D8C1 - PP Move 1
    D8C2 - PP Move 2
    D8C3 - PP Move 3
    D8C4 - PP Move 4
    D8C5 - Level
    D8C6-D8C7 - Max HP
    D8C8-D8C9 - Attack
    D8CA-D8CB - Defense
    D8CC-D8CD - Speed
    D8CE-D8CF - Special

Pokémon 2

    D8D0 - Pokémon
    D8D1-D8D2 - Current HP
    D8D3 - 
    D8D4 - Status
    D8D5 - Type 1
    D8D6 - Type 2
    D8D7 - 
    D8D8 - Move 1
    D8D9 - Move 2
    D8DA - Move 3
    D8DB - Move 4
    D8DC-D8DD - Trainer ID
    D8DE-D8E0 - Experience
    D8E1-D8E2 - HP EV
    D8E3-D8E4 - Attack EV
    D8E5-D8E6 - Defense EV
    D8E7-D8E8 - Speed EV
    D8E9-D8EA - Special EV
    D8EB - Attack/Defense IV
    D8EC - Speed/Special IV
    D8ED - PP Move 1
    D8EE - PP Move 2
    D8EF - PP Move 3
    D8F0 - PP Move 4
    D8F1 - Level
    D8F2-D8F3 - Max HP
    D8F4-D8F5 - Attack
    D8F6-D8F7 - Defense
    D8F8-D8F9 - Speed
    D8FA-D8FB - Special

Pokémon 3

    D8FC - Pokémon
    D8FD-D8FE - Current HP
    D8FF - 
    D900 - Status
    D901 - Type 1
    D902 - Type 2
    D903 - 
    D904 - Move 1
    D905 - Move 2
    D906 - Move 3
    D907 - Move 4
    D908-D909 - Trainer ID
    D90A-D90C - Experience
    D90D-D90E - HP EV
    D90F-D910 - Attack EV
    D911-D912 - Defense EV
    D913-D914 - Speed EV
    D915-D916 - Special EV
    D917 - Attack/Defense IV
    D918 - Speed/Special IV
    D919 - PP Move 1
    D91A - PP Move 2
    D91B - PP Move 3
    D91C - PP Move 4
    D91D - Level
    D91E-D91F - Max HP
    D920-D921 - Attack
    D922-D923 - Defense
    D924-D925 - Speed
    D926-D927 - Special

Pokémon 4

    D928 - Pokémon
    D929-D92A - Current HP
    D92B - 
    D92C - Status
    D92D - Type 1
    D92E - Type 2
    D92F - 
    D930 - Move 1
    D931 - Move 2
    D932 - Move 3
    D933 - Move 4
    D934-D935 - Trainer ID
    D936-D938 - Experience
    D939-D93A - HP EV
    D93B-D93C - Attack EV
    D93D-D93E - Defense EV
    D93F-D940 - Speed EV
    D941-D942 - Special EV
    D943 - Attack/Defense IV
    D944 - Speed/Special IV
    D945 - PP Move 1
    D946 - PP Move 2
    D947 - PP Move 3
    D948 - PP Move 4
    D949 - Level
    D94A-D94B - Max HP
    D94C-D94D - Attack
    D94E-D94F - Defense
    D950-D951 - Speed
    D952-D953 - Special

Pokémon 5

    D954 - Pokémon
    D955-D956 - Current HP
    D957 - 
    D958 - Status
    D959 - Type 1
    D95A - Type 2
    D95B - 
    D95C - Move 1
    D95D - Move 2
    D95E - Move 3
    D95F - Move 4
    D960-D961 - Trainer ID
    D962-D964 - Experience
    D965-D966 - HP EV
    D967-D968 - Attack EV
    D969-D96A - Defense EV
    D96B-D96C - Speed EV
    D96D-D96E - Special EV
    D96F - Attack/Defense IV
    D970 - Speed/Special IV
    D971 - PP Move 1
    D972 - PP Move 2
    D973 - PP Move 3
    D974 - PP Move 4
    D975 - Level
    D976-D977 - Max HP
    D978-D979 - Attack
    D97A-D97B - Defense
    D97C-D97D - Speed
    D97E-D97F - Special

Pokémon 6

    D980 - Pokémon
    D981-D982 - Current HP
    D983 - 
    D984 - Status
    D985 - Type 1
    D986 - Type 2
    D987 - 
    D988 - Move 1
    D989 - Move 2
    D98A - Move 3
    D98B - Move 4
    D98C-D98D - Trainer ID
    D98E-D990 - Experience
    D991-D992 - HP EV
    D993-D994 - Attack EV
    D995-D996 - Defense EV
    D997-D998 - Speed EV
    D999-D99A - Special EV
    D99B - Attack/Defense IV
    D99C - Speed/Special IV
    D99D - PP Move 1
    D99E - PP Move 2
    D99F - PP Move 3
    D9A0 - PP Move 4
    D9A1 - Level
    D9A2-D9A3 - Max HP
    D9A4-D9A5 - Attack
    D9A6-D9A7 - Defense
    D9A8-D9A9 - Speed
    D9AA-D9AB - Special

Trainer Name

    D9AC-D9B6 - Trainer name for 1st
    D9B7-D9C1 - Trainer name for 2nd
    D9C2-D9CC - Trainer name for 3rd
    D9CD-D9D7 - Trainer name for 4th
    D9D8-D9E2 - Trainer name for 5th
    D9E3-D9ED - Trainer name for 6th

Nickname

    D9EE-D9F8 - Nickname for 1st
    D9F9-DA03 - Nickname for 2nd
    DA04-DA0E - Nickname for 3rd
    DA0F-DA19 - Nickname for 4th
    DA1A-DA24 - Nickname for 5th
    DA25-DA2F - Nickname for 6th

Etc.

Game Time

    DA40 - Hours, two bytes
    DA42 - Minutes, two bytes
    DA44 - Seconds, one byte
    DA45 - Frames, one byte

DA47 - Safari Balls


	Stored Pokémon

This is for the current box that's in use.

    DA80 - Number of Pokémon in current box
    DA81-CA94 - Pokémon 1-20
    DA95 - End of list

Pokémon 1

    DA96 - Pokémon
    DA97-DA98 - HP
    DA99 - Level
    DA9A - Status
    DA9B-DA9C - Types
    DA9D - Held Item (When traded to Generation II)
    DA9E-DAA1 - Moves
    DAA2-DAA3 - Trainer ID
    DAA4-DAA6 - Experience
    DAA7-DAA8 - HP EV
    DAA9-DAAA - Attack EV
    DAAB-DAAC - Defense EV
    DAAD-DAAE - Speed EV
    DAAF-DAB0 - Special EV
    DAB1 - Attack/Defense IV
    DAB2 - Speed/Special IV
    DAB3-DAB6 - PP Moves

Pokémon 2

    DAB7 - Pokémon
    DAB8-DAB9 - HP
    DABA - Level
    DABB - Status
    DABC-DABD - Types
    DABE - Held Item (When traded to Generation II)
    DABF-DAC2 - Moves
    DAC2-DAC4 - Trainer ID
    DAC4-DAC7 - Experience
    DAC8-DAC9 - HP EV
    DACA-DACB - Attack EV
    DACC-DACD - Defense EV
    DACE-DACF - Speed EV
    DAD0-DAD1 - Special EV
    DAD2 - Attack/Defense IV
    DAD3 - Speed/Special IV
    DAD4-DAD7 - PP Moves

Pokémon 3

    DAD8 - Pokémon
    DAD9-DADA - HP
    DADB - Level
    DADC - Status
    DADD-DADE - Types
    DADF - Held Item (When traded to Generation II)
    DAE0-DAE3 - Moves
    DAE4-DAE5 - Trainer ID
    DAE6-DAE8 - Experience
    DAE9-DAEA - HP EV
    DAEB-DAEC - Attack EV
    DAED-DAEE - Defense EV
    DAEF-DAF0 - Speed EV
    DAF1-DAF2 - Special EV
    DAF3 - Attack/Defense IV
    DAF4 - Speed/Special IV
    DAF5-DAF8 - PP Moves

Pokémon 4

    DAF9 - Pokémon
    DAFA-DAFB - HP
    DAFC - Level
    DAFD - Status
    DAFE-DAFF - Types
    DB00 - Held Item (When traded to Generation II)
    DB01-DB04 - Moves
    DB05-DB06 - Trainer ID
    DB07-DB09 - Experience
    DB0A-DB0B - HP EV
    DB0C-DB0D - Attack EV
    DB0E-DB0F - Defense EV
    DB10-DB11 - Speed EV
    DB12-DB13 - Special EV
    DB14 - Attack/Defense IV
    DB15 - Speed/Special IV
    DB16-DB19 - PP Moves

Pokémon 5

    DB1A - Pokémon
    DB1B-DB1C - HP
    DB1D - Level
    DB1E - Status
    DB1F-DB20 - Types
    DB21 - Held Item (When traded to Generation II)
    DB22-DB25 - Moves
    DB26-DB27 - Trainer ID
    DB28-DB2A - Experience
    DB2B-DB2C - HP EV
    DB2D-DB2E - Attack EV
    DB2F-DB30 - Defense EV
    DB31-DB32 - Speed EV
    DB33-DB34 - Special EV
    DB35 - Attack/Defense IV
    DB36 - Speed/Special IV
    DB37-DB3A - PP Moves

Pokémon 6

    DB3B - Pokémon
    DB3C-DB3D - HP
    DB3E - Level
    DB3F - Status
    DB40-DB41 - Types
    DB42 - Held Item (When traded to Generation II)
    DB43-DB46 - Moves
    DB47-DB48 - Trainer ID
    DB4A-DB4B - Experience
    DB4C-DB4D - HP EV
    DB4E-DB4F - Attack EV
    DB50-DB51 - Defense EV
    DB52-DB53 - Speed EV
    DB54-DB55 - Special EV
    DB56 - Attack/Defense IV
    DB57 - Speed/Special IV
    DB58-DB5B - PP Moves

Pokémon 7

    DB5C - Pokémon
    DB5D-DB5E - HP
    DB5F - Level
    DB60 - Status
    DB61-DB62 - Types
    DB63 - Held Item (When traded to Generation II)
    DB64-DB67 - Moves
    DB68-DB69 - Trainer ID
    DB6A-DB6C - Experience
    DB6D-DB6E - HP EV
    DB6F-DB70 - Attack EV
    DB71-DB72 - Defense EV
    DB73-DB74 - Speed EV
    DB75-DB76 - Special EV
    DB77 - Attack/Defense IV
    DB78 - Speed/Special IV
    DB79-DB7C - PP Moves

Pokémon 8

    DB7D - Pokémon
    DB7E-DB7F - HP
    DB80 - Level
    DB81 - Status
    DB82-DB83 - Types
    DB84 - Held Item (When traded to Generation II)
    DB85-DB88 - Moves
    DB89-DB8A - Trainer ID
    DB8B-DB8D - Experience
    DB8E-DB8F - HP EV
    DB90-DB91 - Attack EV
    DB92-DB93 - Defense EV
    DB94-DB95 - Speed EV
    DB96-DB97 - Special EV
    DB98 - Attack/Defense IV
    DB99 - Speed/Special IV
    DB9A-DB9D - PP Moves

Pokémon 9

    DB9E - Pokémon
    DB9F-DBA0 - HP
    DBA1 - Level
    DBA2 - Status
    DBA3-DBA4 - Types
    DBA5 - Held Item (When traded to Generation II)
    DBA6-DBA9 - Moves
    DBAA-DBAB - Trainer ID
    DBAC-DBAE - Experience
    DBAF-DBB0 - HP EV
    DBB1-DBB2 - Attack EV
    DBB3-DBB4 - Defense EV
    DBB5-DBB6 - Speed EV
    DBB7-DBB8 - Special EV
    DBB9 - Attack/Defense IV
    DBBA - Speed/Special IV
    DBBB-DBBE - PP Moves

Pokémon 10

    DBBF - Pokémon
    DBC0-DBC1 - HP
    DBC2 - Level
    DBC3 - Status
    DBC4-DBC5 - Types
    DBC6 - Held Item (When traded to Generation II)
    DBC7-DBCA - Moves
    DBCB-DBCC - Trainer ID
    DBCD-DBCF - Experience
    DBD0-DBD1 - HP EV
    DBD2-DBD3 - Attack EV
    DBD4-DBD5 - Defense EV
    DBD6-DBD7 - Speed EV
    DBD8-DBD9 - Special EV
    DBDA - Attack/Defense IV
    DBDB - Speed/Special IV
    DBDC-DBDF - PP Moves

Pokémon 11

    DBE0 - Pokémon
    DBE1-DBE2 - HP
    DBE3 - Level
    DBE4 - Status
    DBE5-DBE6 - Types
    DBE7 - Held Item (When traded to Generation II)
    DBE8-DBEB - Moves
    DBEC-DBED - Trainer ID
    DBEE-DBF0 - Experience
    DBF1-DBF2 - HP EV
    DBF3-DBF4 - Attack EV
    DBF5-DBF6 - Defense EV
    DBF7-DBF8 - Speed EV
    DBF9-DBFA - Special EV
    DBFB - Attack/Defense IV
    DBFC - Speed/Special IV
    DBFD-DC00 - PP Moves

Pokémon 12

    DC01 - Pokémon
    DC02-DC03 - HP
    DC04 - Level
    DC05 - Status
    DC06-DC07 - Types
    DC08 - Held Item (When traded to Generation II)
    DC09-DC0C - Moves
    DC0D-DC0E - Trainer ID
    DC0F-DC11 - Experience
    DC12-DC13 - HP EV
    DC14-DC15 - Attack EV
    DC16-DC17 - Defense EV
    DC18-DC19 - Speed EV
    DC1A-DC1B - Special EV
    DC1C - Attack/Defense IV
    DC1D - Speed/Special IV
    DC1E-DC21 - PP Moves

Pokémon 13

    DC22 - Pokémon
    DC23-DC24 - HP
    DC25 - Level
    DC26 - Status
    DC27-DC28 - Types
    DC29 - Held Item (When traded to Generation II)
    DC2A-DC2D - Moves
    DC2E-DC2F - Trainer ID
    DC30-DC32 - Experience
    DC33-DC34 - HP EV
    DC35-DC36 - Attack EV
    DC37-DC38 - Defense EV
    DC39-DC3A - Speed EV
    DC3B-DC3C - Special EV
    DC3D - Attack/Defense IV
    DC3E - Speed/Special IV
    DC3F-DC42 - PP Moves

Pokémon 14

    DC43 - Pokémon
    DC44-DC45 - HP
    DC46 - Level
    DC47 - Status
    DC48-DC49 - Types
    DC4A - Held Item (When traded to Generation II)
    DC4B-DC4E - Moves
    DC4F-DC50 - Trainer ID
    DC51-DC53 - Experience
    DC54-DC55 - HP EV
    DC56-DC57 - Attack EV
    DC58-DC59 - Defense EV
    DC5A-DC5B - Speed EV
    DC5C-DC5D - Special EV
    DC5E - Attack/Defense IV
    DC5F - Speed/Special IV
    DC60-DC63 - PP Moves

Pokémon 15

    DC64 - Pokémon
    DC65-CC66 - HP
    DC67 - Level
    DC68 - Status
    DC69-DC6A - Types
    DC6B - Held Item (When traded to Generation II)
    DC6C-DC6F - Moves
    DC70-DC71 - Trainer ID
    DC72-DC74 - Experience
    DC75-DC76 - HP EV
    DC77-DC78 - Attack EV
    DC79-DC7A - Defense EV
    DC7B-DC7C - Speed EV
    DC7D-DC7E - Special EV
    DC7F - Attack/Defense IV
    DC80 - Speed/Special IV
    DC81-DC84 - PP Moves

Pokémon 16

    DC85 - Pokémon
    DC86-DC87 - HP
    DC88 - Level
    DC89 - Status
    DC8A-DC8B - Types
    DC8C - Held Item (When traded to Generation II)
    DC8D-DC90 - Moves
    DC91-DC92 - Trainer ID
    DC93-DC95 - Experience
    DC96-DC97 - HP EV
    DC98-DC99 - Attack EV
    DC9A-DC9B - Defense EV
    DC9C-DC9D - Speed EV
    DC9E-DC9F - Special EV
    DCA0 - Attack/Defense IV
    DCA1 - Speed/Special IV
    DCA2-DCA5 - PP Moves

Pokémon 17

    DCA6 - Pokémon
    DCA7-DCA8 - HP
    DCA9 - Level
    DCAA - Status
    DCAB-DCAC - Types
    DCAD - Held Item (When traded to Generation II)
    DCAE-DCB1 - Moves
    DCB2-DCB3 - Trainer ID
    DCB4-DCB6 - Experience
    DCB7-DCB8 - HP EV
    DCB9-DCBA - Attack EV
    DCBB-DCBC - Defense EV
    DCBD-DCBE - Speed EV
    DCBF-DCC0 - Special EV
    DCC1 - Attack/Defense IV
    DCC2 - Speed/Special IV
    DCC3-DCC6 - PP Moves

Pokémon 18

    DCC7 - Pokémon
    DCC8-DCC9 - HP
    DCCA - Level
    DCCB - Status
    DCCC-DCCD - Types
    DCCE - Held Item (When traded to Generation II)
    DCCF-DCD2 - Moves
    DCD3-DCD4 - Trainer ID
    DCD5-DCD7 - Experience
    DCD8-DCD9 - HP EV
    DCDA-DCDB - Attack EV
    DCDC-DCDD - Defense EV
    DCDE-DCDF - Speed EV
    DCE0-DCE1 - Special EV
    DCE2 - Attack/Defense IV
    DCE3 - Speed/Special IV
    DCE4-DCE7 - PP Moves

Pokémon 19

    DCE8 - Pokémon
    DCE9-DCEA - HP
    DCEB - Level
    DCEC - Status
    DCED-DCEE - Types
    DCEF - Held Item (When traded to Generation II)
    DCF0-DCF3 - Moves
    DCF4-DCF5 - Trainer ID
    DCF6-DCF8 - Experience
    DCF9-DCFA - HP EV
    DCFB-DCFC - Attack EV
    DCFD-DCFE - Defense EV
    DCFF-DD00 - Speed EV
    DD01-DD02 - Special EV
    DD03 - Attack/Defense IV
    DD04 - Speed/Special IV
    DD05-DD08 - PP Moves

Pokémon 20

    DD09 - Pokémon
    DD0A-DD0B - HP
    DD0C - Level
    DD0D - Status
    DD0E-DD0F - Types
    DD10 - Held Item (When traded to Generation II)
    DD11-DD14 - Moves
    DD15-DD16 - Trainer ID
    DD17-DD19 - Experience
    DD1A-DD1B - HP EV
    DD1C-DD1D - Attack EV
    DD1E-DD1F - Defense EV
    DD20-DD21 - Speed EV
    DD22-DD23 - Special EV
    DD24 - Attack/Defense IV
    DD25 - Speed/Special IV
    DD26-DD29 - PP Moves

Trainer name

    DD2A-DD34 - Trainer name for 1st
    DD35-DD3F - Trainer name for 2nd
    DD40-DD4A - Trainer name for 3rd
    DD4B-DD55 - Trainer name for 4th
    DD56-DD60 - Trainer name for 5th
    DD61-DD6B - Trainer name for 6th
    DD6C-DD76 - Trainer name for 7th
    DD77-DD81 - Trainer name for 8th
    DD82-DD8C - Trainer name for 9th
    DD8D-DD97 - Trainer name for 10th
    DD98-DDA2 - Trainer name for 11th
    DDA3-DDAD - Trainer name for 12th
    DDAE-DDB8 - Trainer name for 13th
    DDB9-DDC3 - Trainer name for 14th
    DDC4-DDCE - Trainer name for 15th
    DDCF-DDD9 - Trainer name for 16th
    DDDA-DDE4 - Trainer name for 17th
    DDE5-DDEF - Trainer name for 18th
    DDF0-DDFA - Trainer name for 19th
    DDFB-DE05 - Trainer name for 20th

Nickname

    DE06-DE10 - Nickname for 1st
    DE11-DE1B - Nickname for 2nd
    DE1C-DE26 - Nickname for 3rd
    DE27-DE31 - Nickname for 4th
    DE32-DE3C - Nickname for 5th
    DE3D-DE47 - Nickname for 6th
    DE48-DE52 - Nickname for 7th
    DE53-DE5D - Nickname for 8th
    DE5E-DE68 - Nickname for 9th
    DE69-DE73 - Nickname for 10th
    DE74-DE7E - Nickname for 11th
    DE7F-DED9 - Nickname for 12th
    DE8A-DE94 - Nickname for 13th
    DE95-DE9F - Nickname for 14th
    DEA0-DEAA - Nickname for 15th
    DEAB-DEB5 - Nickname for 16th
    DEB6-DEC0 - Nickname for 17th
    DEC1-DECB - Nickname for 18th
    DECC-DED6 - Nickname for 19th
    DED7-DEE1 - Nickname for 20th
*/

/*

	ITEM IDS
From: https://github.com/pret/pokered/blob/master/constants/item_constants.asm

	const MASTER_BALL   ; $01
	const ULTRA_BALL    ; $02
	const GREAT_BALL    ; $03
	const POKE_BALL     ; $04
	const TOWN_MAP      ; $05
	const BICYCLE       ; $06
	const SURFBOARD     ; $07 buggy?
	const SAFARI_BALL   ; $08
	const POKEDEX       ; $09
	const MOON_STONE    ; $0A
	const ANTIDOTE      ; $0B
	const BURN_HEAL     ; $0C
	const ICE_HEAL      ; $0D
	const AWAKENING     ; $0E
	const PARLYZ_HEAL   ; $0F
	const FULL_RESTORE  ; $10
	const MAX_POTION    ; $11
	const HYPER_POTION  ; $12
	const SUPER_POTION  ; $13
	const POTION        ; $14
	const BOULDERBADGE  ; $15
	const CASCADEBADGE  ; $16
SAFARI_BAIT           EQU $15 ; overload
SAFARI_ROCK           EQU $16 ; overload
	const THUNDERBADGE  ; $17
	const RAINBOWBADGE  ; $18
	const SOULBADGE     ; $19
	const MARSHBADGE    ; $1A
	const VOLCANOBADGE  ; $1B
	const EARTHBADGE    ; $1C
	const ESCAPE_ROPE   ; $1D
	const REPEL         ; $1E
	const OLD_AMBER     ; $1F
	const FIRE_STONE    ; $20
	const THUNDER_STONE ; $21
	const WATER_STONE   ; $22
	const HP_UP         ; $23
	const PROTEIN       ; $24
	const IRON          ; $25
	const CARBOS        ; $26
	const CALCIUM       ; $27
	const RARE_CANDY    ; $28
	const DOME_FOSSIL   ; $29
	const HELIX_FOSSIL  ; $2A
	const SECRET_KEY    ; $2B
	const UNUSED_ITEM   ; $2C "?????"
	const BIKE_VOUCHER  ; $2D
	const X_ACCURACY    ; $2E
	const LEAF_STONE    ; $2F
	const CARD_KEY      ; $30
	const NUGGET        ; $31
	const PP_UP_2       ; $32
	const POKE_DOLL     ; $33
	const FULL_HEAL     ; $34
	const REVIVE        ; $35
	const MAX_REVIVE    ; $36
	const GUARD_SPEC    ; $37
	const SUPER_REPEL   ; $38
	const MAX_REPEL     ; $39
	const DIRE_HIT      ; $3A
	const COIN          ; $3B
	const FRESH_WATER   ; $3C
	const SODA_POP      ; $3D
	const LEMONADE      ; $3E
	const S_S_TICKET    ; $3F
	const GOLD_TEETH    ; $40
	const X_ATTACK      ; $41
	const X_DEFEND      ; $42
	const X_SPEED       ; $43
	const X_SPECIAL     ; $44
	const COIN_CASE     ; $45
	const OAKS_PARCEL   ; $46
	const ITEMFINDER    ; $47
	const SILPH_SCOPE   ; $48
	const POKE_FLUTE    ; $49
	const LIFT_KEY      ; $4A
	const EXP_ALL       ; $4B
	const OLD_ROD       ; $4C
	const GOOD_ROD      ; $4D
	const SUPER_ROD     ; $4E
	const PP_UP         ; $4F
	const ETHER         ; $50
	const MAX_ETHER     ; $51
	const ELIXER        ; $52
	const MAX_ELIXER    ; $53
	const FLOOR_B2F     ; $54
	const FLOOR_B1F     ; $55
	const FLOOR_1F      ; $56
	const FLOOR_2F      ; $57
	const FLOOR_3F      ; $58
	const FLOOR_4F      ; $59
	const FLOOR_5F      ; $5A
	const FLOOR_6F      ; $5B
	const FLOOR_7F      ; $5C
	const FLOOR_8F      ; $5D
	const FLOOR_9F      ; $5E
	const FLOOR_10F     ; $5F
	const FLOOR_11F     ; $60
	const FLOOR_B4F     ; $61

	const HM_01         ; $C4
	const HM_02         ; $C5
	const HM_03         ; $C6
	const HM_04         ; $C7
	const HM_05         ; $C8
	const TM_01         ; $C9
	const TM_02         ; $CA
	const TM_03         ; $CB
	const TM_04         ; $CC
	const TM_05         ; $CD
	const TM_06         ; $CE
	const TM_07         ; $CF
	const TM_08         ; $D0
	const TM_09         ; $D1
	const TM_10         ; $D2
	const TM_11         ; $D3
	const TM_12         ; $D4
	const TM_13         ; $D5
	const TM_14         ; $D6
	const TM_15         ; $D7
	const TM_16         ; $D8
	const TM_17         ; $D9
	const TM_18         ; $DA
	const TM_19         ; $DB
	const TM_20         ; $DC
	const TM_21         ; $DD
	const TM_22         ; $DE
	const TM_23         ; $DF
	const TM_24         ; $E0
	const TM_25         ; $E1
	const TM_26         ; $E2
	const TM_27         ; $E3
	const TM_28         ; $E4
	const TM_29         ; $E5
	const TM_30         ; $E6
	const TM_31         ; $E7
	const TM_32         ; $E8
	const TM_33         ; $E9
	const TM_34         ; $EA
	const TM_35         ; $EB
	const TM_36         ; $EC
	const TM_37         ; $ED
	const TM_38         ; $EE
	const TM_39         ; $EF
	const TM_40         ; $F0
	const TM_41         ; $F1
	const TM_42         ; $F2
	const TM_43         ; $F3
	const TM_44         ; $F4
	const TM_45         ; $F5
	const TM_46         ; $F6
	const TM_47         ; $F7
	const TM_48         ; $F8
	const TM_49         ; $F9
	const TM_50         ; $FA
*/

