#include "AccountService.h"

namespace core {

// CONSTRUCTOR
AccountService::AccountService(AccountRepository& repository) :
    repository_(repository) {}

// CREATE
std::expected<QUuid, CreateAccountError> AccountService::create_account(const QString& name,
                                                                        const std::vector<Credential>& credentials) {
    Account account{name, credentials};

    const auto result = repository_.add(account);

    if (!result.has_value()) {
        return std::unexpected(result.error());
    }

    return account.id();
}

// RETRIEVE
std::optional<Account> AccountService::find_account_by_id(const QUuid& id) const { return repository_.find_by_id(id); }

std::vector<AccountSummary> AccountService::find_accounts_by_name(const QString& query) const {
    return repository_.find_accounts_by_name(query);
}

std::vector<Account> AccountService::list_accounts() const { return repository_.list(); }

// UPDATE
std::expected<void, UpdateAccountError> AccountService::update_account_name(const QUuid& id, const QString& name) {
    auto account = repository_.find_by_id(id);

    if (!account.has_value()) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    account->update_name(name);

    return repository_.update(*account);
}

std::expected<void, UpdateAccountError>
AccountService::update_account_credentials(const QUuid& id, const std::vector<Credential>& credentials) {
    auto account = repository_.find_by_id(id);

    if (!account.has_value()) {
        return std::unexpected(UpdateAccountError::NotFound);
    }

    account->update_credentials(credentials);

    return repository_.update(*account);
}

// DELETE
std::expected<void, DeleteAccountError> AccountService::delete_account(const QUuid& id) {
    return repository_.remove(id);
}

} // namespace core
