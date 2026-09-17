// AccountErrors.h
#pragma once

namespace core {

enum class CreateAccountError {
    EmptyName,
    AlreadyExists,
    StorageFailure,
    InvalidCredential
};
enum class UpdateAccountError {
    EmptyName,
    NotFound,
    InvalidCredential,
    CredentialNotFound
};
enum class DeleteAccountError {
    NotFound
};
enum class FindAccountByIdError {
};

} // namespace core
