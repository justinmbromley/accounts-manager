#pragma once

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

} // namespace core


