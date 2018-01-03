#include <iostream>
#include <sstream>
using namespace std;

int encontrarLRU(int vet[], int n)
{
    int i, menor = vet[0], pos = 0;
 
    for(i = 1; i < n; ++i)
    {
        if(vet[i] < menor)
        {
            menor = vet[i];
            pos = i;
        }
    }
    
    return pos;
}

int encontrarFIFO(int vet[], int n)
{
    int i, menor = vet[0], pos = 0;
  
    return pos;
}


int pegarPotencia(int num)
{

	int pot=0;

	if (num == 1)
	{
		return 0;

	}else
	{
		while(num > 0)
		{
			if(num % 2 == 0)
			{
				pot++;

				num = num/2;

			}

			if (num == 1)
			{
				break;
			} 
		}
	}
	
	//cout<< pot << endl;
	return pot;
}


string intParaString(int num)
{

	stringstream ss;

	ss << num;

	string conv = ss.str();
	
	return conv;
}


string binario(int num)
{

	string b = "";

	if(num == 0)
	{
		for (int i = 0; i < 32; i++)
		{
			b = b + "0";
		}

		return b;
	}else
	{
		while(num!=0)
		{
			int aux = num % 2;
			num = num/2;

			//std::ostringstream stm;
        	//stm << aux;
        	string p = intParaString(aux);

			b = p + b;

		}

		while(num == 0 && b.length() < 32)
		{

			b = "0"+ b;
		}

		return b;	
	}
}

string tagMapAssoc(string endereco,int tamBloco)
{

	string tag;
	int x = pegarPotencia(tamBloco);

	int deslocamento = endereco.length() - x;

	tag = endereco.substr(0,deslocamento);

	return tag;
}


string bitsTag(string endereco,int numBlocos,int tamBloco)
{

	string tag;
	int x = pegarPotencia(tamBloco);
	//cout << x << endl;
	int y = pegarPotencia(numBlocos);
	//cout << y << endl;

	int deslocamento = endereco.length() - (x+y);

	tag = endereco.substr(0,deslocamento);

	return tag;
}

string bitsIndice(string endereco,int numBlocos,int tamBloco)
{
	string indice;
	int x = pegarPotencia(tamBloco);
	//cout << x << endl;
	int y = pegarPotencia(numBlocos);
	//cout << y << endl;

	int deslocamento = x+y;

	indice = endereco.substr(endereco.length()-deslocamento,y);

	return indice;
}

string bitsOffset(string endereco,int tamBloco)
{
	int x = pegarPotencia(tamBloco);
	string tag = endereco.substr (endereco.length()-x);
	return tag;
}


/*
int main(int argc, char const *argv[])
{
	
	cout << bitsIndice("10000000011111000000000001111100",4,4) <<endl;
	cout << bitsOffset("10000000011111000000000001111100",4) <<endl;
	cout << bitsTag("10000000011111000000000001111100",4,4) <<endl;
	
	return 0;
}
*/