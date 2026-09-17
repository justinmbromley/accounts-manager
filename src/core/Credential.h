#pragma once

#include "CredentialType.h"
#include "ids/EntityIds.h"

#include <QString>
#include <utility>
#include <variant>

namespace core {

struct SecretQA {
    QString question;
    QString answer;

    bool operator==(const SecretQA& other) const = default;
};

using CredentialValue = std::variant<QString, SecretQA>;

struct Credential {
    Credential() = default;

    explicit Credential(CredentialType type, CredentialValue value) :
        id{},
        type(type),
        value(std::move(value)) {}

    CredentialId id{};
    CredentialType type = CredentialType::None;
    CredentialValue value = QString{};

    bool operator==(const Credential& other) const = default;
};

} // namespace core
