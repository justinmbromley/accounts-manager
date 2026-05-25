#pragma once

#include <QString>

namespace core {

enum class CredentialType {
    None,
    Username,
    Email,
    Password,
    SecretQuestion,
    SecretAnswer,
    RecoveryPhrase,
    Pin,
    ExpiryDate,
    PhoneNumber
};

QString credential_type_to_string(CredentialType type);

CredentialType credential_type_from_string(const QString& value);

} // namespace core
