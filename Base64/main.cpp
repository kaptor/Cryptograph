#include <iostream>
#include <cstring>
#include "base64.h"

using namespace std;
int main()
{
    //std::cout << "Hello World!\n";
	// cryption without std::string
	char str[] =  "Hello World !";
	int len = strlen(str);

	int size = (len + 2) / 3 * 4;
	char* out = new char[size + 1];
	memset(out, 0, size + 1);
	toBase64(str, len, out);
	cout << "Encryption: "<< out << endl;

	int size2 = size * 3 / 4;
	char* out2 = new char[size2+1];
	memset(out2, 0, size2+1);
	int offset = fromBase64(out, size, out2);

	out2[offset] = '\0';
	cout << "Decryption: " << out2  << endl;

	delete [] out;
	delete [] out2;
}


