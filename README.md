# Implementing Secure Client-Server Communication using Sockets and AES Encryption

This project implements secure communication between a **client** and a **server** using **AES-128 CBC encryption** with OpenSSL.

## 📌 Features
- **AES Encryption**: Uses AES-128-CBC for encrypting and decrypting messages.
- **Secure Key Management**: Generates and loads an AES key and IV from a file (`aes_key.bin`).
- **Client-Server Communication**: A client encrypts a message and sends it to the server, which then decrypts it.

---

## Relevance to Operating Systems
This project directly relates to **Operating Systems (OS)** in the following ways:

### **1️. Secure Inter-Process Communication (IPC)**
- In **multi-process environments**, processes often communicate using IPC mechanisms such as **sockets, pipes, shared memory, and message queues**.
- This project enhances IPC security by **encrypting data before transmission**, ensuring that unauthorized processes cannot intercept or modify it.

### **2️. Cryptographic Security in OS**
- Modern operating systems implement **encryption mechanisms** to protect data in transit and at rest.
- This project demonstrates how **AES encryption** can be integrated into an OS-level security mechanism for securing **network-based** IPC.

### **3️. Network Security & Secure Communication**
- OS-level network security ensures **confidentiality and integrity** of transmitted data.
- By implementing **AES encryption over sockets**, this project ensures that data exchanged between processes remains secure against **eavesdropping & tampering**.


```

## 📂 Project Structure
```
.
├── aes_utils.h    # AES encryption & decryption utility functions
├── server.cpp     # Server application (decrypts messages)
├── client.cpp     # Client application (encrypts and sends messages)
├── aes_key.bin    # AES key and IV (generated if not present)
```

---

## ⚙️ Dependencies
### Required Libraries:
- **OpenSSL**: Used for AES encryption
- **Sockets API**: Used for client-server communication

### Install OpenSSL on Linux:
```bash
sudo apt update && sudo apt install libssl-dev
```

---

## How to Compile & Run
### 1. Compile the Server & Client
```bash
# Compile server
g++ server.cpp -o server -lssl -lcrypto

# Compile client
g++ client.cpp -o client -lssl -lcrypto
```

### 2️. Run the Server
```bash
./server
```

### 3️. Run the Client
```bash
./client
```

---

## How It Works
### **1. `aes_utils.h` (AES Utility Functions)**
- `generateAESKey()`: Generates a random AES key and IV.
- `encryptAES()`: Encrypts data using AES-128-CBC.
- `decryptAES()`: Decrypts AES-128-CBC encrypted data.

### **2. `server.cpp` (Server Application)**
- Listens on **port 8080** for incoming connections.
- Loads the AES key from `aes_key.bin` (or generates a new one if missing).
- Receives an **encrypted message** from the client and decrypts it.
- Prints the **decrypted message** to the console.

### **3. `client.cpp` (Client Application)**
- Loads the AES key from `aes_key.bin`.
- Encrypts a message ("Hello Server!") using AES-128-CBC.
- Connects to the server on **127.0.0.1:8080**.
- Sends the **encrypted message** to the server.

---

## Troubleshooting
- If `client` or `server` fails to run:
  ```bash
  chmod +x client server
  ```
- If OpenSSL is missing:
  ```bash
  sudo apt install libssl-dev
  ```
- If port 8080 is in use, change it in **server.cpp** and **client.cpp**.

---




