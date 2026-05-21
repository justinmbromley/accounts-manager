#pragma once

#include "Account.h"
#include "AccountErrors.h"
#include "AccountSummary.h"

#include <QString>
#include <QUuid>

#include <expected>
#include <optional>
#include <vector>

namespace core {

class AccountRepository {
public:
    virtual ~AccountRepository() = default;

    // CREATE
    virtual std::expected<void, CreateAccountError> add(const Account& account) = 0;

    // RETRIEVE
    virtual std::optional<Account> find_by_id(const QUuid& id) const = 0;
    virtual std::vector<AccountSummary> find_accounts_by_name(const QString& query) const = 0;
    virtual std::vector<Account> list() const = 0;

    // UPDATE
    virtual std::expected<void, UpdateAccountError> update(const Account& account) = 0;

    // DELETE
    virtual std::expected<void, DeleteAccountError> remove(const QUuid& id) = 0;
};

} // namespace core
