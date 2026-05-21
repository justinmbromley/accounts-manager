#pragma once

#include "AccountRepository.h"

namespace data {

class InMemoryAccountRepository : public core::AccountRepository {
public:
    // CREATE
    std::expected<void, core::CreateAccountError> add(const core::Account& account) override;

    // RETRIEVE
    std::optional<core::Account> find_by_id(const QUuid& id) const override;
    std::vector<core::AccountSummary> find_accounts_by_name(const QString& query) const override;
    std::vector<core::Account> list() const override;

    // UPDATE
    std::expected<void, core::UpdateAccountError> update(const core::Account& account) override;

    // DELETE
    std::expected<void, core::DeleteAccountError> remove(const QUuid& id) override;

private:
    std::vector<core::Account> accounts_;
};

} // namespace data
