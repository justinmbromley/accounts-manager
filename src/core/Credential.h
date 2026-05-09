#pragma once

#include "CredentialType.h"

#include <QString>

namespace core {

struct Credential {
    CredentialType type = CredentialType::None;
    QString details{};
};

} // namespace core
