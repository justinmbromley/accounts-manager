#include "Account.h"

#include <QDateTime>

namespace core {

// CONSTRUCTORS
Account::Account(QString name, std::vector<Credential> credentials) :
    id_(),
    name_(std::move(name)),
    credentials_(std::move(credentials)),
    time_created_(QDateTime::currentDateTimeUtc()),
    time_updated_(time_created_) {
    Q_ASSERT(!name_.isEmpty());
}

// METHODS
void Account::update_name(const QString& name) {
    Q_ASSERT(!name.isEmpty());

    name_ = name;
    touch();
}

// CREDENTIAL METHODS
void Account::add_credential(Credential credential) {
    credentials_.push_back(std::move(credential));
    touch();
}

bool Account::update_credential(const CredentialId& credential_id, const Credential& updated_credential) {
    for (auto& credential : credentials_) {
        if (credential.id == credential_id) {
            credential = updated_credential;
            touch();
            return true;
        }
    }

    return false;
}

bool Account::remove_credential(const CredentialId& credential_id) {
    for (auto it = credentials_.begin(); it != credentials_.end(); ++it) {
        if (it->id == credential_id) {
            credentials_.erase(it);
            touch();
            return true;
        }
    }

    return false;
}

std::optional<Credential> Account::find_credential(const CredentialId& credential_id) const {
    for (const auto& credential : credentials_) {
        if (credential.id == credential_id) {
            return credential;
        }
    }

    return std::nullopt;
}

// PRIVATE METHODS
void Account::touch() noexcept { time_updated_ = QDateTime::currentDateTimeUtc(); }

// GETTERS
const AccountId& Account::id() const noexcept { return id_; }
const QString& Account::name() const noexcept { return name_; }
const std::vector<Credential>& Account::credentials() const noexcept { return credentials_; }
const QDateTime& Account::created_at() const noexcept { return time_created_; }
const QDateTime& Account::updated_at() const noexcept { return time_updated_; }

} // namespace core
