#pragma once

#include "Account.h"
#include "ids/EntityIds.h"

#include <QDateTime>
#include <QString>

namespace core {

struct AccountSummary {
    AccountId id;
    QString name;
    QString identifier;
    QDateTime updated_at;
};

AccountSummary to_account_summary(const Account& account);

} // namespace core
