#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> 
#include <math.h>
#include <unistd.h>
#include "xor.h"
using namespace std;
#define CIPH_MAX 100000
#define CHOICE_CNT 2

char genRandom() {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return alphanum[rand() % (sizeof(alphanum) - 1)];
}

void swap(char *a, char *b)
{
    char temp[strlen(a)];
    for(int i = 0; i < strlen(a); i++) {
        temp[i] = a[i];
    }
    temp[strlen(a)] = '\0';

    for(int i = 0; i < strlen(b); i++) {
        a[i] = b[i];
    }
    a[(strlen(b))] = '\0';

    for(int i = 0; i < strlen(temp); i++) {
        b[i] = temp[i];
    }
    b[strlen(temp)] = '\0';
}

class Player 
{
private:
    char key;
    char indKeys[CHOICE_CNT];
public:
    string name;
    Player(string aName);
    char getKey();
    char* getKeys();
    void encrypt(char (*arr)[CIPH_MAX], int n);
    void decrypt(char (*arr)[CIPH_MAX], int n);
    void encryptInd(char (*arr)[CIPH_MAX], int n);
    void decryptInd(char (*arr)[CIPH_MAX], char keys[CHOICE_CNT], int n);
    void shuffle(char (*arr)[CIPH_MAX], int n);
};

Player::Player(string aName) : name(aName), key(genRandom())
{
}

char Player::getKey() {
    return this->key;
}

char* Player::getKeys() {
    return this->indKeys;
}

void Player::encrypt(char (*arr)[CIPH_MAX], int n) {
    for(int i = 0; i < n; i++) {
        XORCipher(arr[i], this->key);
    }
}

void Player::decrypt(char (*arr)[CIPH_MAX], int n) {
    for(int i = 0; i < n; i++) {
        XORCipher(arr[i], this->key);
    }
}

void Player::encryptInd(char (*arr)[CIPH_MAX], int n) {
    for(int i = 0; i < n; i++) {
        indKeys[i] = genRandom();
        XORCipher(arr[i], this->indKeys[i]);
        cout << "indKey: " << this->indKeys[i] << endl;
    }
}

void Player::decryptInd(char (*arr)[CIPH_MAX], char keys[CHOICE_CNT], int n) {
    for(int i = 0; i < n; i++) {
        XORCipher(arr[i], keys[i]);
    }
}

void Player::shuffle(char (*arr)[CIPH_MAX], int n) {
    // srand (time(NULL));
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        cout << "random: " << j << endl;
        swap(arr[i], arr[j]);
    }
}

void printChoices(char (*arr)[CIPH_MAX], int n) {
    cout << "[";
    for (int i = 0; i < n- 1; i++)
        cout << arr[i] << ", ";
    cout << arr[n - 1] << "]" << endl;
}

int main() 
{
    char choices[CHOICE_CNT][CIPH_MAX] = { "white", "black" };
    cout << "The available choices are: ";
    printChoices(choices, CHOICE_CNT);

    srand (time(NULL));
    Player* Alice = new Player("Alice");
    Player* Bob = new Player("Bob");

    // encrypt with own key
    Alice->encrypt(choices, CHOICE_CNT);
    cout << "Alice encrypted with key " << Alice->getKey() << ": ";
    printChoices(choices, CHOICE_CNT);

    Alice->shuffle(choices, CHOICE_CNT);
    cout << "Alice shuffled: ";
    printChoices(choices, CHOICE_CNT);

    Bob->encrypt(choices, CHOICE_CNT);
    cout << "Bob decrypted with key " << Bob->getKey() << ": ";
    printChoices(choices, CHOICE_CNT);

    Bob->shuffle(choices, CHOICE_CNT);
    cout << "Bob shuffled: ";
    printChoices(choices, CHOICE_CNT);

    // decrypt with own key and encrypt with individual keys
    Alice->decrypt(choices, CHOICE_CNT);
    cout << "Alice decrypted with key " << Alice->getKey() << ": ";
    printChoices(choices, CHOICE_CNT);

    Alice->encryptInd(choices, CHOICE_CNT);
    cout << "Alice encrypts them individually: "; 
    printChoices(choices, CHOICE_CNT);

    Bob->decrypt(choices, CHOICE_CNT);
    cout << "Bob decrypted with key " << Bob->getKey() << ": ";
    printChoices(choices, CHOICE_CNT);

    Bob->encryptInd(choices, CHOICE_CNT);
    cout << "Bob encrypts them individually: "; 
    printChoices(choices, CHOICE_CNT);

    int aliceChoice;
    cout << "Alice's ramdom choice: ";
    cin >> aliceChoice;


    Alice->decryptInd(choices, Alice->getKeys(), CHOICE_CNT);
    cout << "Alice decrypted with own individual keys: ";
    printChoices(choices, CHOICE_CNT);

    Alice->decryptInd(choices, Bob->getKeys(), CHOICE_CNT);
    cout << "Alice decrypted with Bob's individual keys: ";
    printChoices(choices, CHOICE_CNT);

    cout << "Result: " << choices[aliceChoice];
    return 0;
}