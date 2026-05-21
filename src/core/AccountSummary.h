#pragma once

#include "Account.h"

#include <QDateTime>
#include <QString>
#include <QUuid>

namespace core {

struct AccountSummary {
    QUuid id;
    QString name;
    QString identifier;
    QDateTime updated_at;
};

AccountSummary to_account_summary(const Account& account);

} // namespace core
