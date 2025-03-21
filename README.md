# Implementing Secure Client-Server Communication using Sockets and AES Encryption

This project implements secure communication between a **client** and a **server** using **AES-128 CBC encryption** with OpenSSL.

## 📌 Features
- **AES Encryption**: Encrypts messages with AES-128-CBC.
- **Secure Key Storage**: Uses a key file (`aes_key.bin`) for encryption and decryption.
- **Client-Server Communication**: The client encrypts a message, sends it to the server, and the server decrypts it.

---

## 🖥️ Relevance to Operating Systems
This project directly relates to **Operating Systems (OS)** in the following ways:

### 1️. Secure Inter-Process Communication (IPC)
- Processes in an OS talk to each other using **sockets, pipes, or shared memory**.
- This project ensures that **messages sent between processes stay private** by encrypting them.

### 2️. Encryption in OS Security
- Modern OSes use **encryption** to protect sensitive data.
- Here, we use **AES encryption** to demonstrate how an OS can secure **network-based IPC**.

### 3️. Network Security & Safe Communication
- OSes protect network communication from hackers.
- This project adds an extra **security layer** so data can’t be **read or altered** during transmission.

---

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

## 🚀 How to Compile & Run
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

## 🔍 How It Works

### **1. AES Utility (`aes_utils.h`)**
- **`generateAESKey()`** → Creates a new AES key & IV.
- **`encryptAES()`** → Encrypts messages with AES-128-CBC.
- **`decryptAES()`** → Decrypts AES-128-CBC messages.

### **2. Server (`server.cpp`)**
- Listens on **port 8080** for client messages.
- Loads the **AES key** from `aes_key.bin` (or generates a new one).
- Receives the **encrypted message** from the client.
- **Decrypts & prints** the original message.

### **3. Client (`client.cpp`)**
- Loads the **AES key** from `aes_key.bin`.
- **Encrypts** a message ("Hello Server!") using AES.
- Connects to **127.0.0.1:8080**.
- Sends the **encrypted message** to the server.

---

## 🔧 Troubleshooting
- **Executable permission issues?** Run:
  ```bash
  chmod +x client server
  ```
- **Missing OpenSSL?** Install it with:
  ```bash
  sudo apt install libssl-dev
  ```
- **Port 8080 in use?** Change it in **server.cpp** & **client.cpp**.

---

## 🔒 Future Enhancements
- **Mutual Authentication** between client & server.
- **File Encryption & Secure Transfer**.
- **Diffie-Hellman Key Exchange** for secure key distribution.




