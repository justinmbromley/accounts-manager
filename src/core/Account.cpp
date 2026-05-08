#include "Account.h"
#include <qvariant.h>

namespace core {

// Constructors
Account::Account(QString name) {}

Account::Account(QString name, std::vector<Credential> credentials) {}

// Methods
void Account::update_name(const QString &name) {}

void Account::update_credentials(const std::vector<Credential> &credentials) {}

// Getters
const QString &Account::name() const noexcept { return name_; }

const std::vector<Credential> &Account::credentials() const noexcept {
  return credentials_;
}
const QDateTime &Account::created_at() const noexcept { return time_created_; }
const QDateTime &Account::updated_at() const noexcept { return time_updated_; }

} // namespace core
