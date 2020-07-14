#include <iostream>
#include <string>
// #include <cmath> // It's needed for the commented function
using namespace std;

// This function works but apperantly this is not how Albert Hoca wants it to be implemented as
//unsigned int P(int ch) { 
//	unsigned int temp = 0;
//	for(int i=7; i>-1; i--) {
//		if(ch-pow(2,i) >=0) {
//			ch -= pow(2,i);
//			if(i ==7) {temp += pow(2,5);}
//			else if(i ==6) {temp += pow(2,7);}
//			else if(i ==5) {temp += pow(2,4);}
//			else if(i ==4) {temp += pow(2,6);}
//			else if(i ==3) {temp += pow(2,1);}
//			else if(i ==2) {temp += pow(2,3);}
//			else if(i ==1) {temp += pow(2,0);}
//			else if(i ==0) {temp += pow(2,2);}
//		}
//	}
//	return temp;
//}

unsigned int P(unsigned char ch) {
	unsigned char temp = 0;
	for(int i=7; i>-1; i--) {
		unsigned char t;
		if     (i ==7) {t = 0x80& ch; temp += (t >> 2);}
		else if(i ==6) {t = 0x40 & ch; temp += (t << 1);}
		else if(i ==5) {t = 0x20 & ch; temp += (t >> 1);}
		else if(i ==4) {t = 0x10 & ch; temp += (t << 2);}
		else if(i ==3) {t = 0x8  & ch; temp += (t >> 2);}
		else if(i ==2) {t = 0x4  & ch; temp += (t << 1);}
		else if(i ==1) {t = 0x2  & ch; temp += (t >> 1);}
		else if(i ==0) {t = 0x1  & ch; temp += (t << 2);}
	}
	return temp;
}

int main() {
	string encryption_key, plaintext;
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl
		 << "Please enter the encryption key: ";
	getline(cin,encryption_key);

	cout << "Please enter the plaintext to be encrypted: ";
	while(getline(cin,plaintext)) {
		cout << "Ciphertext: ";
		unsigned char x,y;
		for(int i=0; i<plaintext.length(); i++) {
			x = encryption_key[i % encryption_key.length()];
			y = P(plaintext[i]);
			unsigned int z = x^y;
			cout << hex << z;
		}
		cout << endl << endl << "Please enter the plaintext to be encrypted: ";
	}
}