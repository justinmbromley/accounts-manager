#include "CredentialType.h"

#include <QString>

namespace core {

QString credential_type_to_string(CredentialType type) {
    switch (type) {
    case CredentialType::None:
        return "NONE";

    case CredentialType::Username:
        return "USERNAME";

    case CredentialType::Email:
        return "EMAIL";

    case CredentialType::Password:
        return "PASSWORD";

    case CredentialType::SecretQA:
        return "SECRET_QA";

    case CredentialType::RecoveryPhrase:
        return "RECOVERY_PHRASE";

    case CredentialType::Pin:
        return "PIN";

    case CredentialType::ExpiryDate:
        return "EXPIRY_DATE";

    case CredentialType::PhoneNumber:
        return "PHONE_NUMBER";

    default:
        return "INVALID_TYPE";
    }
}

CredentialType credential_type_from_string(const QString& value) {
    if (value == "NONE")
        return CredentialType::None;

    if (value == "USERNAME")
        return CredentialType::Username;

    if (value == "EMAIL")
        return CredentialType::Email;

    if (value == "PASSWORD")
        return CredentialType::Password;

    if (value == "SECRET_QA")
        return CredentialType::SecretQA;

    if (value == "RECOVERY_PHRASE")
        return CredentialType::RecoveryPhrase;

    if (value == "PIN")
        return CredentialType::Pin;

    if (value == "EXPIRY_DATE")
        return CredentialType::ExpiryDate;

    if (value == "PHONE_NUMBER")
        return CredentialType::PhoneNumber;

    return CredentialType::None;
}

} // namespace core
