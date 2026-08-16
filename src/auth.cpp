#include "auth.h"

#include <iostream>

AuthStore::AuthStore() {
    accounts_.push_back({"2026201055", "student", hash("portal123")});
    accounts_.push_back({"faculty01", "faculty", hash("teach456")});
    accounts_.push_back({"admin", "admin", hash("root789")});
}

const std::vector<Credential> &AuthStore::accounts() const {
    return accounts_;
}

const Credential *AuthStore::find(const std::string &username) const {
    for (const Credential &account : accounts_) {
        if (account.username == username) {
            return &account;
        }
    }
    return nullptr;
}

bool AuthStore::verify(const std::string &username, const std::string &password) const {
    const Credential *account = find(username);
    if (account == nullptr) {
        return false;
    }
    return account->passwordHash == hash(password);
}

Session AuthStore::authenticate() const {
    Session session;
    std::string username;
    std::string password;

    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);

        if (verify(username, password)) {
            session.username = username;
            session.role = find(username)->role;
            session.active = true;
            std::cout << "Signed in as " << session.username
                      << " (" << session.role << ").\n";
            return session;
        }

        int left = maxAttempts - attempt;
        std::cout << "Invalid credentials. " << left << " attempt(s) left.\n";
    }

    std::cout << "Account locked for this session.\n";
    return session;
}

long AuthStore::hash(const std::string &password) {
    long value = 7;
    for (char ch : password) {
        value = value * 31 + static_cast<long>(ch);
    }
    return value;
}
