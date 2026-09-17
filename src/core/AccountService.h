#pragma once

#include "Account.h"
#include "AccountErrors.h"
#include "AccountRepository.h"
#include "Credential.h"
#include "ids/EntityIds.h"

#include <QString>

#include <expected>
#include <optional>
#include <vector>

namespace core {

class AccountService {
public:
    // CONSTRUCTOR
    explicit AccountService(AccountRepository& repository);

    // CREATE
    std::expected<AccountId, CreateAccountError> create_account(const QString& name,
                                                                const std::vector<Credential>& credentials = {});

    // RETRIEVE
    std::optional<Account> find_account_by_id(const AccountId& id) const;
    std::vector<AccountSummary> find_accounts_by_name(const QString& query) const;
    std::vector<Account> list_accounts() const;

    // UPDATE
    std::expected<void, UpdateAccountError> update_account_name(const AccountId& id, const QString& name);

    // DELETE
    std::expected<void, DeleteAccountError> delete_account(const AccountId& id);

    // CREDENTIALS
    std::expected<CredentialId, UpdateAccountError> add_credential(const AccountId& id, const Credential& credential);

    std::expected<void, UpdateAccountError>
    update_credential(const AccountId& account_id, const CredentialId& credential_id, const Credential& credential);

    std::expected<void, UpdateAccountError> remove_credential(const AccountId& account_id,
                                                              const CredentialId& credential_id);

private:
    AccountRepository& repository_;
};

} // namespace core
