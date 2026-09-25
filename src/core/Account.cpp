#include "Account.h"

#include <QDateTime>

namespace core {

// CONSTRUCTORS
Account::Account(QString name, std::vector<Credential> credentials) :
    id_(),
    name_(std::move(name)),
    credentials_(std::move(credentials)),
    created_at_(QDateTime::currentDateTimeUtc()),
    updated_at_(created_at_) {
    Q_ASSERT(!name_.isEmpty());
}

Account::Account(AccountId id, QString name, std::vector<Credential> credentials, QDateTime created_at,
                 QDateTime updated_at) :
    id_(std::move(id)),
    name_(std::move(name)),
    credentials_(std::move(credentials)),
    created_at_(std::move(created_at)),
    updated_at_(std::move(updated_at)) {
    Q_ASSERT(!name_.isEmpty());
}

// ACCOUNT RESTORATION
Account Account::restore(AccountId id, QString name, std::vector<Credential> credentials, QDateTime created_at,
                         QDateTime updated_at) {

    return Account{std::move(id), std::move(name), std::move(credentials), std::move(created_at),
                   std::move(updated_at)};
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
void Account::touch() noexcept { updated_at_ = QDateTime::currentDateTimeUtc(); }

// GETTERS
const AccountId& Account::id() const noexcept { return id_; }
const QString& Account::name() const noexcept { return name_; }
const std::vector<Credential>& Account::credentials() const noexcept { return credentials_; }
const QDateTime& Account::created_at() const noexcept { return created_at_; }
const QDateTime& Account::updated_at() const noexcept { return updated_at_; }

} // namespace core
