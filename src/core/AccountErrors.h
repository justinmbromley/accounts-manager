// AccountErrors.h
#pragma once

namespace core {

enum class CreateAccountError { EmptyName, AlreadyExists, StorageFailure };
enum class UpdateAccountError { EmptyName, NotFound };
enum class DeleteAccountError { NotFound };
enum class FindAccountByIdError {};

} // namespace core
