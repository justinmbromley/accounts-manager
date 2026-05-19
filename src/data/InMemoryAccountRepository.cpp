#include "InMemoryAccountRepository.h"
#include "AccountErrors.h"

namespace data {

// CREATE
std::expected<void, core::CreateAccountError> InMemoryAccountRepository::add(const core::Account& account) {
    if (find_by_id(account.id())) {
        return std::unexpected(core::CreateAccountError::AlreadyExists);
    }

    accounts_.push_back(account);
    return {};
}

// RETRIEVE
std::optional<core::Account> InMemoryAccountRepository::find_by_id(const QUuid& id) const {
    const auto it = std::ranges::find_if(accounts_, [&id](const core::Account& account) { return account.id() == id; });

    if (it == accounts_.cend()) {
        return std::nullopt;
    }

    return *it;
}

std::vector<core::AccountSummary> InMemoryAccountRepository::find_accounts_by_name(const QString& query) const {
    std::vector<core::AccountSummary> summaries;

    for (const auto& account : accounts_) {
        if (account.name().contains(query, Qt::CaseInsensitive)) {
            summaries.push_back(core::to_account_summary(account));
        }
    }

    return summaries;
}

std::vector<core::Account> InMemoryAccountRepository::list() const { return accounts_; }

// UPDATE
std::expected<void, core::UpdateAccountError> InMemoryAccountRepository::update(const core::Account& account) {
    for (auto& stored_account : accounts_) {
        if (stored_account.id() == account.id()) {
            stored_account = account;
            return {};
        }
    }

    return std::unexpected(core::UpdateAccountError::NotFound);
}

// DELETE
std::expected<void, core::DeleteAccountError> InMemoryAccountRepository::remove(const QUuid& id) {
    for (auto it = accounts_.begin(); it != accounts_.end(); ++it) {
        if (it->id() == id) {
            accounts_.erase(it);
            return {};
        }
    }

    return std::unexpected(core::DeleteAccountError::NotFound);
}

} // namespace data
