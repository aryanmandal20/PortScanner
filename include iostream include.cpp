#include <iostream>
#include <sys/socket.h>  // For socket programming (Linux)
#include <netinet/in.h>  // For sockaddr_in structure (Linux)
#include <arpa/inet.h>   // For inet_addr()
#include <unistd.h>      // For close()
#include <cstring>       // For memset()

void scanPorts(const char* ip, int startPort, int endPort) {
    for (int port = startPort; port <= endPort; port++) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Error creating socket\n";
            return;
        }

        struct sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        target.sin_addr.s_addr = inet_addr(ip);

        if (connect(sock, (struct sockaddr*)&target, sizeof(target)) == 0) {
            std::cout << "[+] Port " << port << " is open!\n";
        }

        close(sock);
    }
}

int main() {
    std::string targetIP;
    int startPort, endPort;

    std::cout << "Enter Target IP: ";
    std::cin >> targetIP;
    std::cout << "Enter Start Port: ";
    std::cin >> startPort;
    std::cout << "Enter End Port: ";
    std::cin >> endPort;

    scanPorts(targetIP.c_str(), startPort, endPort);
    return 0;
}

