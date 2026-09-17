#pragma

#include "AccountRepository.h"
#include <QSqlDatabase>

namespace data {

class SqliteAccountRepository : public core::AccountRepository {
public:
    // CONSTRUCTOR
    explicit SqliteAccountRepository(QSqlDatabase db);

    // CREATE
    std::expected<void, core::CreateAccountError> add(const core::Account& account) override;

    // RETRIEVE
    std::optional<core::Account> find_by_id(const core::AccountId& id) const override;
    std::vector<core::AccountSummary> find_accounts_by_name(const QString& query) const override;
    std::vector<core::Account> list() const override;

    // UPDATE
    std::expected<void, core::UpdateAccountError> update(const core::Account& account) override;

    // DELETE
    std::expected<void, core::DeleteAccountError> remove(const core::AccountId& id) override;

private:
    QSqlDatabase db_;
};

} // namespace data
