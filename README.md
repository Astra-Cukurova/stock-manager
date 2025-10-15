# stock-manager
A minimal stock manager with CLI.
Build command for feature-cli:
g++ main.cpp cli.cpp password_hasher.cpp -o stock-manager -L./lib -lssl -lcrypto