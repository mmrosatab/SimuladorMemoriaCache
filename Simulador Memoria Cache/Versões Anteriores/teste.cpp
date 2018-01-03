#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
using namespace std;
using std::string;
using std::stringstream;

std::string dec2bin(unsigned n)
{
    std::string res;

    while (n)
    {
        res.push_back((n & 1) + '0');
        n >>= 1;
    }

    if (res.empty())
        res = "0";
    else
        std::reverse(res.begin(), res.end());
 
   return res;
}
  
int main(int argc, char const *argv[])
{
	
	cout << dec2bin(0) << endl;
	return 0;
}