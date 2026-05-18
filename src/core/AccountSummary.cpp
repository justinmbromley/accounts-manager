#include "AccountSummary.h"
#include "Account.h"

#include <QString>

namespace {

QString identifier_from(const std::vector<core::Credential>& credentials) {
    for (const auto& credential : credentials) {
        if (credential.type == core::CredentialType::Email) {
            return credential.details;
        }
    }

    for (const auto& credential : credentials) {
        if (credential.type == core::CredentialType::Username) {
            return credential.details;
        }
    }

    return {};
}

} // namespace

namespace core {

AccountSummary to_account_summary(const Account& account) {
    return AccountSummary{
        .id = account.id(),
        .name = account.name(),
        .identifier = identifier_from(account.credentials()),
        .updated_at = account.updated_at(),
    };
}

} // namespace core
