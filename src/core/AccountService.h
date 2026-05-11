#pragma once

#include "Account.h"
#include "Credential.h"

#include <QString>
#include <QUuid>

#include <expected>
#include <optional>
#include <vector>

namespace core {

struct AccountSummary {
    QUuid id;
    QString name;
    QDateTime updated_at;
};

enum class AddAccountError {};
enum class UpdateAccountError {};
enum class DeleteAccountError {};
enum class FindAccountByIdError {};

class AccountService {
public:
    // CREATE
    std::expected<QUuid, AddAccountError> add_account(const QString& name,
                                                      const std::vector<Credential>& credentials = {});

    // RETRIEVE
    std::optional<Account> find_account_by_id(const QUuid& id) const;

    std::vector<AccountSummary> find_accounts_by_name(const QString& query) const;

    std::vector<Account> list_accounts() const;

    // UPDATE
    std::expected<void, UpdateAccountError> update_account_name(const QUuid& id, const QString& name);

    std::expected<void, UpdateAccountError> update_account_credentials(const QUuid& id,
                                                                       const std::vector<Credential>& credentials);

    // DELETE
    std::expected<void, DeleteAccountError> delete_account(const QUuid& id);
};

} // namespace core
