#include "CredentialValidator.h"

#include <QString>

namespace core {

bool is_valid_credential(const Credential& credential) {
    if (credential.type == CredentialType::None) {
        return false;
    }

    if (credential.type == CredentialType::SecretQA) {
        if (!std::holds_alternative<SecretQA>(credential.value)) {
            return false;
        }

        const auto& qa = std::get<SecretQA>(credential.value);

        return !qa.question.trimmed().isEmpty() && !qa.answer.trimmed().isEmpty();
    }

    if (!std::holds_alternative<QString>(credential.value)) {
        return false;
    }

    return !std::get<QString>(credential.value).trimmed().isEmpty();
}

} // namespace core
