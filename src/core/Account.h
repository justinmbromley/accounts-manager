#pragma once

#include "Credential.h"
#include "ids/EntityIds.h"

#include <QDateTime>
#include <QString>
#include <optional>
#include <qdatetime.h>
#include <vector>

namespace core {

class Account {
public:
    // Constructors
    explicit Account(QString name, std::vector<Credential> credentials = {});

    // Restoring an account
    static Account restore(AccountId id, QString name, std::vector<Credential> credentials, QDateTime created_at,
                           QDateTime updated_at);

    // Methods
    void update_name(const QString& name);

    // Credential methods
    void add_credential(Credential credential);
    bool update_credential(const CredentialId& credential_id, const Credential& updated_credential);
    bool remove_credential(const CredentialId& credential_id);
    std::optional<Credential> find_credential(const CredentialId& credential_id) const;

    // Getters
    const AccountId& id() const noexcept;
    const QString& name() const noexcept;
    const std::vector<Credential>& credentials() const noexcept;
    const QDateTime& created_at() const noexcept;
    const QDateTime& updated_at() const noexcept;

private:
    Account(AccountId id, QString name, std::vector<Credential> credentials, QDateTime created_at,
            QDateTime updated_at);

    void touch() noexcept;

    AccountId id_;
    QString name_;
    std::vector<Credential> credentials_;
    QDateTime created_at_;
    QDateTime updated_at_;
};

} // namespace core
