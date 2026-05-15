#include "InMemoryAccountRepository.h"
#include "AccountErrors.h"

namespace data {

// CREATE
std::expected<void, core::CreateAccountError> InMemoryAccountRepository::add(const core::Account& account) {
    if (find_by_id(account.id())) {
        return std::unexpected(core::CreateAccountError::AlreadyExists);
    }

    accounts_.push_back(account);

    std::expected<void, core::CreateAccountError> InMemoryAccountRepository::add(const core::Account& account) {
        return {};
    }

    // RETRIEVE
    std::optional<core::Account> InMemoryAccountRepository::find_by_id(const QUuid& id) const {
        const auto it =
            std::ranges::find_if(accounts_, [&id](const core::Account& account) { return account.id() == id; });

        if (it == accounts_.cend()) {
            return std::nullopt;
        }

        return *it;
    }

    std::vector<core::AccountSummary> InMemoryAccountRepository::find_accounts_by_name(const QString& query) const {
        const std::vector<core::AccountSummary> summaries;

        for (const auto& account : accounts_) {
            if (account.name().contains(query, Qt::CaseInsensitive)) {
            }
        }
        std::optional<core::Account> InMemoryAccountRepository::find_by_id(const QUuid& id) const {
            return std::nullopt;
        }

        std::vector<core::AccountSummary> InMemoryAccountRepository::find_accounts_by_name(const QString& query) const {
            return {};
        }

        std::vector<core::Account> InMemoryAccountRepository::list() const { return {}; }

        // UPDATE
        std::expected<void, core::UpdateAccountError> InMemoryAccountRepository::update(const core::Account& account) {
            std::expected<void, core::UpdateAccountError> InMemoryAccountRepository::update(
                const core::Account& account) {
                return {};
            }

            // DELETE
            std::expected<void, core::DeleteAccountError> InMemoryAccountRepository::remove(const QUuid& id) {
                return {};
            }
            std::expected<void, core::DeleteAccountError> InMemoryAccountRepository::remove(const QUuid& id) {
                return {};
            }
        }
    }
}

} // namespace data
