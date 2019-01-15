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
////////////////////////////////
const size_t size=4;
//cislo A
bool NumberA[size];
NumberA[0]=1;
NumberA[1]=1;
NumberA[2]=1;
NumberA[3]=1;

//cislo B
bool NumberB[size];
NumberB[0]=1;
NumberB[1]=1;
NumberB[2]=1;
NumberB[3]=1;

//Pi
bool Pi[size]={0,0,0,0};
//Gi
bool Gi[size]={0,0,0,0};
//Si
bool Si[size]={0,0,0,0};
//Digits
bool PiZero[size]={0,0,0,0};

//kogge stone prvni okruh
//mozna bychom meli vynechat prvni pole 

for(int i=0; i < size; i++)
{
		Pi[i] = NumberA[i] ^ NumberB[i];
		Gi[i] = NumberA[i] & NumberB[i];
		PiZero[i] = Pi[i];
}
//posuny
int w=1;
for(int j=size-1; j> 1; j--)
	{
	for(int i=0; i < j; i++)
	{
		bool PiHelp=Pi[i];

		Pi[i] = PiHelp & Pi[i+w];
		Gi[i] = (PiHelp & Gi[i+w]) | Gi[i];
		w=w+1;
	}
}
//Ci=Gi / bereme rovnou Gi, tady dame Si o jednu mensi protoze
//prodlouzime o jeden prvek
//bool Ci[5]={1,0,0,1,0};
bool GiNext[size+1]={0,0,0,0,0};

for(int i = 0; i< size; i++)
{
	GiNext[i]=Gi[i];
}

for(int i=0; i < size; i++)
{
		Si[i] = PiZero[i] ^ GiNext[i+1];
}

//preteceni a vysledek
if (Gi[0]==1)
{
	bool ResultNumber[size+1];
	ResultNumber[0]=1;
	for(int i = 1; i < size+1; i++)
	{
		ResultNumber[i]=Si[i-1];
	}
	kontrola(ResultNumber, size+1);
}
else
{
	bool ResultNumber[size];
	for(int i = 0; i < size; i++)
	{
		ResultNumber[i]=Si[i];
	}
	kontrola(ResultNumber, size);
}


cout << "Co sem uz naprogramoval v OpenCL" << endl;

/*
//Pi
Pi[size]={0,0,0,0};
//Gi
Gi[size]={0,0,0,0};
//Si
bool Si[size]={0,0,0,0};
//Digits
bool PiZero[size]={0,0,0,0};
*/

for(int i=0; i < size; i++)
{
		Pi[i] = NumberA[i] ^ NumberB[i];
		Gi[i] = NumberA[i] & NumberB[i];
		PiZero[i] = Pi[i];
}

for(int j=1; j < size - 1; j *=2)
{
	for(int i=0; i < size-j; i++)
	{
		bool PiHelp=Pi[i];
		Pi[i] = PiHelp & Pi[i+j];
		Gi[i] = (PiHelp & Gi[i+j]) | Gi[i];
	}
}

for(int i=0; i < size ; i++)
{
			Si[i] = PiZero[i] ^ Gi[i+1];
			if(i==size-1)
			{
				Si[i] = PiZero[i] ^ 0;
			}
}

/*
//rozsireni pole o overfloow
//preteceni a vysledek
if (Gi[0]==1)
{
	bool ResultNumber[size+1];
	ResultNumber[0]=1;
	for(int i = 1; i < size+1; i++)
	{
		ResultNumber[i]=Si[i-1];
	}
	kontrola(ResultNumber, size+1);
}
else
{
	bool ResultNumber[size];
	for(int i = 0; i < size; i++)
	{
		ResultNumber[i]=Si[i];
	}
	kontrola(ResultNumber, size);
}

*/


}