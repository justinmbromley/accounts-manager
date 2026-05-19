#include "AccountService.h"

namespace core {

// CONSTRUCTOR
AccountService::AccountService(AccountRepository& respository) :
    respository_(respository) {}

// CREATE
std::expected<QUuid, CreateAccountError> AccountService::create_account(const QString& name,
                                                                        const std::vector<Credential>& credentials) {
    return std::unexpected(CreateAccountError::AlreadyExists);
}

// RETRIEVE
std::optional<Account> AccountService::find_account_by_id(const QUuid& id) const { return std::nullopt; }

std::vector<AccountSummary> AccountService::find_accounts_by_name(const QString& query) const { return {}; }

std::vector<Account> AccountService::list_accounts() const { return {}; }

// UPDATE
std::expected<void, UpdateAccountError> AccountService::update_account_name(const QUuid& id, const QString& name) {
    return std::unexpected(UpdateAccountError::NotFound);
}

std::expected<void, UpdateAccountError>
AccountService::update_account_credentials(const QUuid& id, const std::vector<Credential>& credentials) {
    return std::unexpected(UpdateAccountError::NotFound);
}

// DELETE
std::expected<void, DeleteAccountError> AccountService::delete_account(const QUuid& id) {
    return std::unexpected(DeleteAccountError::NotFound);
}

} // namespace core
