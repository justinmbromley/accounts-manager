#pragma once

#include "CredentialType.h"

#include <QString>

namespace core {

struct Credential {
    CredentialType type = CredentialType::None;
    QString details{};

    bool operator==(const Credential& other) const = default;
};

} // namespace core
