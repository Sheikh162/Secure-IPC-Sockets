#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <openssl/aes.h>
#include "aes_utils.h"  

using namespace std;

#define PORT 8080
#define BUFFER_SIZE 1024
#define AES_KEY_SIZE 16  
#define AES_IV_SIZE 16   

unsigned char key[AES_KEY_SIZE];
unsigned char iv[AES_IV_SIZE];

// Error handling function
void handleError(const string& msg) {
    cerr << "[Server] Error: " << msg << " | " << strerror(errno) << endl;
    exit(EXIT_FAILURE);
}

// Load AES key from file
void loadAESKey() {
    FILE *keyFile = fopen("aes_key.bin", "rb");
    
    if (!keyFile) {
        cout << "[Server] Key file not found. Generating new AES key...\n";

        // Generate key and IV
        generateAESKey(key, iv);

        // Save key and IV to file
        keyFile = fopen("aes_key.bin", "wb");
        if (!keyFile) {
            handleError("Failed to create key file");
        }
        fwrite(key, 1, AES_KEY_SIZE, keyFile);
        fwrite(iv, 1, AES_IV_SIZE, keyFile);
        fclose(keyFile);

        cout << "[Server] AES key saved to aes_key.bin\n";
        return;
    }

    // Read the key and IV if file exists
    fread(key, 1, AES_KEY_SIZE, keyFile);
    fread(iv, 1, AES_IV_SIZE, keyFile);
    fclose(keyFile);
    cout << "[Server] AES key loaded successfully.\n";
}


// Decrypt AES message
void decryptMessage(const unsigned char *encryptedMsg, int encryptedLen, unsigned char *decryptedMsg, int &decryptedLen) {
    decryptAES(encryptedMsg, encryptedLen, key, iv, decryptedMsg, decryptedLen);
}

int main() {
    loadAESKey();

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    unsigned char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        handleError("Socket creation failed");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        handleError("Bind failed");
    }

    if (listen(server_fd, 3) < 0) {
        handleError("Listen failed");
    }

    cout << "[Server] Waiting for connections...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        handleError("Accept failed");
    }

    ssize_t bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        handleError("Failed to receive data");
    }

    cout << "[Server] Received encrypted message: ";
    for (int i = 0; i < bytes_received; i++) {
        printf("%02x", buffer[i]);
    }
    cout << endl;

    unsigned char decryptedMsg[BUFFER_SIZE] = {0};
    int decryptedLen = 0;

    decryptMessage(buffer, bytes_received, decryptedMsg, decryptedLen);

    cout << "[Server] Decrypted message: " << string((char*)decryptedMsg, decryptedLen) << endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
