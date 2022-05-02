#include<iostream>
#include<string.h>
using namespace std;

void XORCipher(char orignalString[], char xorKey) {
   int len = strlen(orignalString);
   for (int i = 0; i < len; i++){
      orignalString[i] = orignalString[i] ^ xorKey;
      cout<<orignalString[i];
   }
}

int main(){
   char sampleString[] = "white";
   // cout<<"The string is: "<<sampleString<<endl;

   XORCipher(sampleString, 'l');
   return 0;
}