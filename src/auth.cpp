#include "auth.h"

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

long AuthStore::hash(const std::string &password) {
    long value = 7;
    for (char ch : password) {
        value = value * 31 + static_cast<long>(ch);
    }
    return value;
}
