#pragma once

#include <QUuid>

namespace core {

struct AccountId {
    QUuid value;

    AccountId() :
        value(QUuid::createUuid()) {}

    explicit AccountId(QUuid value) :
        value(std::move(value)) {}

    [[nodiscard]]
    bool is_valid() const noexcept {
        return !value.isNull();
    }

    bool operator==(const AccountId& other) const = default;
};

struct CredentialId {
    QUuid value;

    CredentialId() :
        value(QUuid::createUuid()) {}

    explicit CredentialId(QUuid value) :
        value(std::move(value)) {}

    [[nodiscard]]
    bool is_valid() const noexcept {
        return !value.isNull();
    }

    bool operator==(const CredentialId& other) const = default;
};

} // namespace core
