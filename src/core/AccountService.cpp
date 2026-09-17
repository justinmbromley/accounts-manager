#include "AccountService.h"
#include "CredentialValidator.h"

namespace core {

// CONSTRUCTOR
AccountService::AccountService(AccountRepository& repository) :
    repository_(repository) {}

// CREATE
std::expected<AccountId, CreateAccountError>
AccountService::create_account(const QString& name, const std::vector<Credential>& credentials) {
    if (name.trimmed().isEmpty()) {
        return std::unexpected(CreateAccountError::EmptyName);
    }

    for (const auto& credential : credentials) {
        if (!is_valid_credential(credential)) {
            return std::unexpected(CreateAccountError::InvalidCredential);
        }
    }

    Account account{name.trimmed(), credentials};
    const auto id = account.id();

    auto result = repository_.add(account);
    if (!result) {
        return std::unexpected(result.error());
    }

    return id;
}

// RETRIEVE
std::optional<Account> AccountService::find_account_by_id(const AccountId& id) const {
    return repository_.find_by_id(id);
}

std::vector<AccountSummary> AccountService::find_accounts_by_name(const QString& query) const {
    return repository_.find_accounts_by_name(query.trimmed());
}

std::vector<Account> AccountService::list_accounts() const { return repository_.list(); }

// UPDATE
std::expected<void, UpdateAccountError> AccountService::update_account_name(const AccountId& id, const QString& name) {
    if (name.trimmed().isEmpty()) {
        return std::unexpected(UpdateAccountError::EmptyName);
    }

    auto account = repository_.find_by_id(id);
    if (!account) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    account->update_name(name.trimmed());

    return repository_.update(*account);
}

// DELETE
std::expected<void, DeleteAccountError> AccountService::delete_account(const AccountId& id) {
    return repository_.remove(id);
}

// CREDENTIALS
std::expected<CredentialId, UpdateAccountError> AccountService::add_credential(const AccountId& id,
                                                                               const Credential& credential) {
    if (!is_valid_credential(credential)) {
        return std::unexpected(UpdateAccountError::InvalidCredential);
    }

    auto account = repository_.find_by_id(id);
    if (!account) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    Credential credential_to_add = credential;
    credential_to_add.id = CredentialId{};

    const auto credential_id = credential_to_add.id;

    account->add_credential(std::move(credential_to_add));

    auto result = repository_.update(*account);
    if (!result) {
        return std::unexpected(result.error());
    }

    return credential_id;
}

std::expected<void, UpdateAccountError> AccountService::update_credential(const AccountId& account_id,
                                                                          const CredentialId& credential_id,
                                                                          const Credential& credential) {
    if (!is_valid_credential(credential)) {
        return std::unexpected(UpdateAccountError::InvalidCredential);
    }

    auto account = repository_.find_by_id(account_id);
    if (!account) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    Credential updated_credential = credential;
    updated_credential.id = credential_id;

    if (!account->update_credential(credential_id, updated_credential)) {
        return std::unexpected(UpdateAccountError::CredentialNotFound);
    }

    return repository_.update(*account);
}

std::expected<void, UpdateAccountError> AccountService::remove_credential(const AccountId& account_id,
                                                                          const CredentialId& credential_id) {
    auto account = repository_.find_by_id(account_id);
    if (!account) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    if (!account->remove_credential(credential_id)) {
        return std::unexpected(UpdateAccountError::CredentialNotFound);
    }

    return repository_.update(*account);
}

} // namespace core
