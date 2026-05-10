#include "Account.h"

#include <QDateTime>
#include <QUuid>

namespace core {

// Constructors
Account::Account(QString name) :
    id_(QUuid::createUuid()),
    name_(std::move(name)),
    credentials_(),
    time_created_(QDateTime::currentDateTimeUtc()),
    time_updated_(time_created_) {
    Q_ASSERT(!name_.isEmpty());
}

Account::Account(QString name, std::vector<Credential> credentials) :
    id_(QUuid::createUuid()),
    name_(std::move(name)),
    credentials_(std::move(credentials)),
    time_created_(QDateTime::currentDateTimeUtc()),
    time_updated_(time_created_) {
    Q_ASSERT(!name_.isEmpty());
}

// Methods
void Account::update_name(const QString& name) {
    Q_ASSERT(!name.isEmpty());

    name_ = name;
    time_updated_ = QDateTime::currentDateTimeUtc();
}

void Account::update_credentials(const std::vector<Credential>& credentials) {
    credentials_ = credentials;
    time_updated_ = QDateTime::currentDateTimeUtc();
}

// Getters
const QString& Account::name() const noexcept { return name_; }

const std::vector<Credential>& Account::credentials() const noexcept { return credentials_; }
const QDateTime& Account::created_at() const noexcept { return time_created_; }
const QDateTime& Account::updated_at() const noexcept { return time_updated_; }

} // namespace core
