#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstring>

using namespace std;


void helper (ifstream& in_file, int len)
{
	if (len == 0) return;

	char c;
	in_file >> c;

	helper(in_file, len-1);

	cout << c;

}

int main (int argc, char* argv[])
{
	ifstream in_file;
	in_file.open(argv[1]);
	int value;
	in_file >> value;
	in_file >> noskipws;
	helper(in_file, value+1);
	in_file.close;
}
  
  