#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <cmath>
#include <sstream>
#include <vector>
#include <array>
#include <iomanip>
#include <deque>


#include <windows.h>
#include <ppl.h>
#include <concurrent_vector.h>

#include<cmath>

using namespace std;
using namespace concurrency;


//kontrola
void kontrola(bool Pole[], int size)
{

for(int i=0; i < size; i++)
{
	cout << Pole[i]; 
}
cout << endl;

}



int main(int argc, char* argv[])
{
///////////////////////////
const size_t sizeOfNumber=10;

//obsahuje pole - prvni dimenze skupiny, druha dimenze pocet prvku, couter pole
struct fields {
	bool arrayWT[2*sizeOfNumber][sizeOfNumber];
	int velocityWT[sizeOfNumber];
	int counterWT;
} primaryArray,helpArray,helpArrayHigherOrder;

///

//cislo A ---help
bool NumberA[sizeOfNumber];
NumberA[0]=1;
NumberA[1]=0;
NumberA[2]=0;
NumberA[3]=1;

//cislo B --- help
bool NumberB[sizeOfNumber];
NumberB[0]=1;
NumberB[1]=0;
NumberB[2]=0;
NumberB[3]=1;


//pokus

cout << primaryArray.velocityWT[sizeOfNumber] << endl;
//

//kogge stone prvni okruh
//mozna bychom meli vynechat prvni pole 



//protoze soucet indexu a[x]b[x] urcuje vahu vytvorime skupiny dle vah
//nejdelsi skupina bude mit delku nasobenych cisel max delka jednotlivych poli je a, prvni dimenze predstavuje pocet skupin, druha pocet clenu
//int field[2*sizeOfNumber][sizeOfNumber];

//potrebujeme rozmer pole abychom neukladaly na stejne prvky a*b-1
//int velocityOfField[2*sizeOfNumber]={0,0,0,0,0,0,0};


//soucin kazdeho bitu s kazdym, reverse
//cislo A
for(int i=0; i < sizeOfNumber; i++)
{
//cislo B
	for(int j=0; j < sizeOfNumber ; j++)
	{ 
//nasobeni jako and, rozdeleni cisel do trid podle vah
//
		primaryArray.arrayWT[(2*sizeOfNumber-1)-(i+j)][primaryArray.velocityWT[(2*sizeOfNumber-1)-(i+j)]]=NumberA[i]&NumberB[j];
		primaryArray.velocityWT[(2*sizeOfNumber-1)-(i+j)]+=1;

//
//		field[(2*sizeOfNumber-1)-(i+j)][velocityOfField[(2*sizeOfNumber-1)-(i+j)]]=NumberA[i]&NumberB[j];
//		velocityOfField[(2*sizeOfNumber-1)-(i+j)]+=1;
	}
}
//dve pole, jedno pomocne ve stejnem radu, druhe pro prirayeni do vyssiho radu 

//tisk 
/*
for(int i=0; i < 8; i++)
{
//cislo B
	for(int j=0; j < velocityOfField[i]; j++)
	{
//pomocna promenna, urcujicici skupinu 
//nasobeni jako and
		cout << field[i][j] ;
	}
	cout << endl;
}
*/


int maxint = 0;
//pokud bude existovat nejaka skupina s vetsim poctem clenu nez tri
do 
{


//tyto pole se spoji az po vypoctu kola radu
//vynulujeme pomocne pole, otazka jestli by nemelo byt mensi
// int helpField[2*sizeOfNumber][sizeOfNumber];
// int velocityOfHelpField[2*sizeOfNumber]={0,0,0,0,0,0,0,0};


//int helpFieldHigherOrder[2*sizeOfNumber][sizeOfNumber];
//zatim nepouzite, ale bude potreba ?
// int velocityOfHelpFieldHigherOrder[2*sizeOfNumber]={0,0,0,0,0,0,0,0};

	//pro jednotlive skupiny
	for(int i=(2*sizeOfNumber-1); i >= 0 ; i--)
	{

// na konci lokalniho by se melo ulozit do pomocneho, na konci pomocneho by se melo ulozit do hlavniho

		//pocitadla v radu, jedno pro pomocne, jedno pro vyssi rad - lokalni
		int counterHelp = 0;
		// lokalni
		int couterHelpHigherOrder = 0;
		//ukazatel na prvke v poli, je roven delce pole minus 1
		//
		primaryArray.counterWT=primaryArray.velocityWT[i]-1;
		//
//		int couterField = velocityOfField[i]-1; 

//cyklus pro kazdy rad
		//
		while(primaryArray.velocityWT[i]  > 0)
		//
//		while(velocityOfField[i]  > 0)
		{
		//pokud je delka dane skupiny vetsi nez nula budeme dosazovat scitacky
			//full adder
			//
			if((primaryArray.velocityWT[i] % 3) == 0)
			//
//			if((velocityOfField[i] % 3) == 0)
			{
				//stejny rad podminka s, tri predchazejici prvky a xor, A xor B xor C[in]
				//
				helpArray.arrayWT[i][helpArray.counterWT]=primaryArray.arrayWT[i][primaryArray.counterWT-2] ^ primaryArray.arrayWT[i][primaryArray.counterWT-1]
					^ primaryArray.arrayWT[i][primaryArray.counterWT];
				//
//				helpField[i][counterHelp]=field[i][couterField-2]^field[i][couterField-1]^field[i][couterField];
				//
				helpArray.counterWT +=1;
				//
//				counterHelp += 1;
				//preneseme do vyssiho radu (A and B) xor (C[in] and (A xor B))
				//
				helpArrayHigherOrder.arrayWT[i-1][helpArrayHigherOrder.counterWT]=(primaryArray.arrayWT[i][primaryArray.counterWT-2] 
					& primaryArray.arrayWT[i][primaryArray.counterWT-1]) ^ (primaryArray.arrayWT[i][primaryArray.counterWT]
					& (primaryArray.arrayWT[i][primaryArray.counterWT-2] ^ primaryArray.arrayWT[i][primaryArray.counterWT-1]));
				//
//				helpFieldHigherOrder[i-1][couterHelpHigherOrder]=(field[i][couterField-2] & field[i][couterField-1]) 
//					^ (field[i][couterField] & (field[i][couterField-2] ^ field[i][couterField-1]));
				//
				helpArrayHigherOrder.counterWT +=1;
				//
//				couterHelpHigherOrder += 1;
				//
				helpArray.velocityWT[i] +=1;
				//
//				velocityOfHelpField[i]+=1;
				//
				helpArrayHigherOrder.velocityWT[i-1] +=1;
				//
//				velocityOfHelpFieldHigherOrder[i-1]+=1;				
								
				//snizeni poctu clenu v radu
				//
				primaryArray.velocityWT[i] -=3;
				//
//				velocityOfField[i]-=3;
				//snizeni couteru pole, tedy posunuti o tri pole k zacatku
				//
				primaryArray.counterWT -=3;
				//
//				couterField-=3;

			}
			//half adder
			//
			if((primaryArray.velocityWT[i] % 3) == 2)
			//
//			if((velocityOfField[i] % 3) == 2)
			{
				//stejny rad podminka s, tri predchazejici prvky a xor, A xor B xor C[in]		
				//
				helpArray.arrayWT[i][helpArray.counterWT]=primaryArray.arrayWT[i][primaryArray.counterWT-1] ^ primaryArray.arrayWT[i][primaryArray.counterWT]; 
				//
//				helpField[i][counterHelp]=field[i][couterField-1]^field[i][couterField];	
				//
				helpArray.counterWT +=1;
				//
//				counterHelp += 1;
				//vyssi rad
				//
				helpArrayHigherOrder.arrayWT[i-1][helpArrayHigherOrder.counterWT]=(primaryArray.arrayWT[i][primaryArray.counterWT-1] & primaryArray.arrayWT[i][primaryArray.counterWT]);
				//
//				helpFieldHigherOrder[i-1][couterHelpHigherOrder]=(field[i][couterField-1] & field[i][couterField]); 
				//
				helpArrayHigherOrder.counterWT +=1;
				//
//				couterHelpHigherOrder += 1;
				//
				helpArray.velocityWT[i] +=1;
				//
//				velocityOfHelpField[i]+=1;
				//
				helpArrayHigherOrder.velocityWT[i-1]+=1;
				//
//				velocityOfHelpFieldHigherOrder[i-1]+=1;				
								
				//snizeni dimenze pole
				//
				primaryArray.velocityWT[i] -=2;
				//
//				velocityOfField[i]-=2;
				//snizeni couteru pole
				//
				primaryArray.counterWT -=3;
				//
//				couterField-=3;
			}
			//pouze prenost v danem rade
			//
			if((primaryArray.velocityWT[i] % 3) == 1)
			//
//			if((velocityOfField[i] % 3) == 1)
			{
				//pouze presuneme dal, tedy ulozime
				//
				helpArray.arrayWT[i][helpArray.counterWT]=primaryArray.arrayWT[i][primaryArray.counterWT];
				//
//				helpField[i][counterHelp]=field[i][couterField];
				//zvysime couterHelp pomocneho pole	
				//
				helpArray.counterWT += 1;
				//
//				counterHelp += 1;
				//zvysime ukazatel poctu prvku v pomocnem poli
				//
				helpArray.velocityWT[i] +=1;
				//
//				velocityOfHelpField[i] +=1;
				//snizime ukazatel delky
				//
				primaryArray.velocityWT[i] -=1;
				//
//				velocityOfField[i]-=1;
				//snizeni couteru pole
				//
				primaryArray.counterWT -=1;
				//
//				couterField-=1;
			}
		}
	}
//vynulovani vsechny prvky
for(int i = 0; i < 2*sizeOfNumber; i++)
{
	for(int j = 0; j < sizeOfNumber; j++)
	{
		//
		primaryArray.arrayWT[i][j]=0;
		//
//		field[i][j]=0;
	}
}
//slouceni pomocnych poli
for(int i = 0; i < 2*sizeOfNumber; i++)
{
	//pomocne pole
	//
	for(int j = 0; j < helpArray.velocityWT[i]; j++)
	//
//	for(int j = 0; j < velocityOfHelpField[i]; j++)
	{
		//
		primaryArray.arrayWT[i][j]=helpArray.arrayWT[i][j];
		//
//		field[i][j]=helpField[i][j];
	}
	//pole vyssich radu
	//
	for(int j = helpArray.velocityWT[i]; j < helpArray.velocityWT[i] + helpArrayHigherOrder.velocityWT[i]; j++)
	//
//	for(int j = velocityOfHelpField[i]; j < velocityOfHelpField[i]+velocityOfHelpFieldHigherOrder[i]; j++)
	{
		//druha dimenze pole musi byt od nuly, je tam plus jedna kvuli zmene radu
		//
		primaryArray.arrayWT[i][j]= helpArrayHigherOrder.arrayWT[i][j - helpArray.velocityWT[i]];
		//
//		field[i][j]=helpFieldHigherOrder[i][j-velocityOfHelpField[i]];	
	}
//
primaryArray.velocityWT[i] = helpArray.velocityWT[i] + helpArrayHigherOrder.velocityWT[i]; 
//
//velocityOfField[i]=velocityOfHelpField[i]+velocityOfHelpFieldHigherOrder[i];
}

//nalezeni max cisla
//najit nejvyssi prvek velocity max
maxint = 0;

for(int i =0; i < 2*sizeOfNumber; i++)
{
	//
	if(primaryArray.velocityWT[i] > maxint)
	//
//	if(velocityOfField[i] > maxint)
	{
		//
		maxint = primaryArray.velocityWT[i];
		//
//		maxint = velocityOfField[i];
	}
}
}
while(maxint > 2);

//secist posledni dvojice bitu, musi se uz udelat seriove


/*
for(int i =0; i < 8; i++)
{
	if(velocityOfField[i] > 1)
	{
		int x = field[i][0];
		int y = field[i][1];
		field[i][0]= x ^ y;
		// overflow
		//zvedneme pole dalsiho radu o jednu 
		velocityOfField[i+1]+=1;
		
		//soucasny rad snizime o jednicku
		velocityOfField[i]=1;
	}
}
*/




/*
cout << "maximalni cislo" << maxint << endl;

for(int i=0; i< 8; i++)
{
	cout << "delka skupiny " << velocityOfField[i] << endl;
	for(int j=0; j< velocityOfField[i]; j++)
	{
		cout << field[i][j];
	}
	cout << endl;
}
*/

//prni ca

//posuny


}