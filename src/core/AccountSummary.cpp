#include "AccountSummary.h"
#include "Account.h"

#include <QString>

namespace {

QString identifier_from(const std::vector<core::Credential>& credentials) {
    for (const auto& credential : credentials) {
        if (credential.type == core::CredentialType::Email &&
            std::holds_alternative<QString>(credential.value)) {

            return std::get<QString>(credential.value);
        }
    }

    for (const auto& credential : credentials) {
        if (credential.type == core::CredentialType::Username &&
            std::holds_alternative<QString>(credential.value)) {

            return std::get<QString>(credential.value);
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
