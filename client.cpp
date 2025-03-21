#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/aes.h>
#include "aes_utils.h"

using namespace std;

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define AES_KEY_SIZE 16  // 128-bit AES key
#define AES_IV_SIZE 16   // IV size for AES-CBC
#define BUFFER_SIZE 1024

unsigned char key[AES_KEY_SIZE];
unsigned char iv[AES_IV_SIZE];

// Handle errors
void handleError(const string& msg) {
    cerr << "[Client] Error: " << msg << " | " << strerror(errno) << endl;
    exit(EXIT_FAILURE);
}

// Load AES key from file
void loadAESKey() {
    FILE *keyFile = fopen("aes_key.bin", "rb");
    if (!keyFile) {
        handleError("Failed to open key file");
    }
    fread(key, 1, AES_KEY_SIZE, keyFile);
    fread(iv, 1, AES_IV_SIZE, keyFile);
    fclose(keyFile);
}

// Encrypt message
void encryptMessage(const unsigned char *message, int messageLen, unsigned char *encryptedMsg, int &encryptedLen) {
    encryptAES(message, messageLen, key, iv, encryptedMsg, encryptedLen);
}

int main() {
    loadAESKey();

    int sock = 0;
    struct sockaddr_in serv_addr;
    unsigned char message[] = "Hello Server!";
    unsigned char encryptedMsg[BUFFER_SIZE] = {0};
    int encryptedLen = 0;

    encryptMessage(message, strlen((char*)message), encryptedMsg, encryptedLen);

    cout << "[Client] Original message: " << message << endl;
    cout << "[Client] Encrypted message: ";
    for (int i = 0; i < encryptedLen; i++) {
        printf("%02x", encryptedMsg[i]);
    }
    cout << endl;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handleError("Socket creation failed");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        handleError("Invalid address/Address not supported");
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        handleError("Connection failed");
    }

    if (send(sock, encryptedMsg, encryptedLen, 0) < 0) {
        handleError("Failed to send encrypted message");
    }

    cout << "[Client] Encrypted message sent to server!\n";

    close(sock);
    return 0;
}
