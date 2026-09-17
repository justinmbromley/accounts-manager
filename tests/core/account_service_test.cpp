#include "AccountService.h"
#include "Credential.h"
#include "CredentialType.h"
#include "InMemoryAccountRepository.h"
#include "ids/EntityIds.h"

#include <QtTest>

class AccountServiceTest : public QObject {
    Q_OBJECT

private slots:
    void create_account_success_test();
    void create_account_credentials_success_test();
    void create_account_blank_name_fails_test();
    void create_account_invalid_credential_fails_test();

    void find_account_by_id_success_test();
    void find_account_by_id_not_found_test();

    void find_accounts_by_name_success_test();
    void find_accounts_by_name_multiple_matches_test();
    void find_accounts_by_name_no_matches_test();

    void list_accounts_success_test();
    void list_accounts_empty_test();

    void update_account_name_success_test();
    void update_account_name_id_not_found_test();
    void update_account_blank_name_fails_test();

    void delete_account_success_test();
    void delete_account_not_found_test();

    void add_credential_success_test();
    void add_credential_invalid_credential_fails_test();
    void add_credential_account_not_found_test();

    void update_credential_success_test();
    void update_credential_invalid_credential_fails_test();
    void update_credential_account_not_found_test();
    void update_credential_credential_not_found_test();

    void remove_credential_success_test();
    void remove_credential_account_not_found_test();
    void remove_credential_credential_not_found_test();
};

void AccountServiceTest::create_account_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const QString account_name = "Gmail";

    const auto result = service.create_account(account_name);

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(result.value());

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), account_name);
}

void AccountServiceTest::create_account_credentials_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const QString account_name = "Gmail";
    const std::vector<core::Credential> credentials{
        core::Credential{core::CredentialType::Email, "user@gmail.com"},
        core::Credential{core::CredentialType::Password, "password123"},
    };

    const auto result = service.create_account(account_name, credentials);

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(result.value());

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), account_name);
    QCOMPARE(account->credentials(), credentials);
}

void AccountServiceTest::create_account_blank_name_fails_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.create_account("");

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::CreateAccountError::EmptyName);
}

void AccountServiceTest::create_account_invalid_credential_fails_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const QString account_name = "Gmail";
    const std::vector<core::Credential> credentials{
        core::Credential{core::CredentialType::Email, "user@gmail.com"},
        core::Credential{core::CredentialType::None, "value"},
    };

    const auto result = service.create_account(account_name, credentials);

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::CreateAccountError::InvalidCredential);

    QCOMPARE(service.list_accounts().size(), 0);
}

void AccountServiceTest::find_account_by_id_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto gmail_id = service.create_account("Gmail").value();
    const auto github_id = service.create_account("GitHub").value();
    const auto outlook_id = service.create_account("Outlook").value();

    const auto account = service.find_account_by_id(github_id);

    QVERIFY(account.has_value());

    QCOMPARE(account->id(), github_id);
    QCOMPARE(account->name(), "GitHub");

    QVERIFY(account->id() != gmail_id);
    QVERIFY(account->id() != outlook_id);
}

void AccountServiceTest::find_account_by_id_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account = service.find_account_by_id(core::AccountId{});

    QVERIFY(!account.has_value());
}

void AccountServiceTest::find_accounts_by_name_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    QVERIFY(service.create_account("Gmail").has_value());

    const auto github_result = service.create_account("GitHub");
    QVERIFY(github_result.has_value());

    QVERIFY(service.create_account("Outlook").has_value());

    const auto github_id = github_result.value();

    const auto results = service.find_accounts_by_name("Git");

    QCOMPARE(results.size(), 1);
    QCOMPARE(results[0].id, github_id);
    QCOMPARE(results[0].name, "GitHub");
}

void AccountServiceTest::find_accounts_by_name_multiple_matches_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto gmail_id = service.create_account("Gmail").value();
    const auto gmail_personal_id = service.create_account("Gmail Personal").value();
    QVERIFY(service.create_account("GitHub").has_value());

    const auto results = service.find_accounts_by_name("Gmail");

    QCOMPARE(results.size(), 2);

    QCOMPARE(results[0].id, gmail_id);
    QCOMPARE(results[0].name, "Gmail");

    QCOMPARE(results[1].id, gmail_personal_id);
    QCOMPARE(results[1].name, "Gmail Personal");
}

void AccountServiceTest::find_accounts_by_name_no_matches_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    QVERIFY(service.create_account("Gmail").has_value());
    QVERIFY(service.create_account("GitHub").has_value());
    QVERIFY(service.create_account("Outlook").has_value());

    const auto results = service.find_accounts_by_name("Discord");

    QVERIFY(results.empty());
}

void AccountServiceTest::list_accounts_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto gmail_id = service.create_account("Gmail").value();
    const auto github_id = service.create_account("GitHub").value();

    const auto accounts = service.list_accounts();

    QCOMPARE(accounts.size(), 2);
    QCOMPARE(accounts[0].id(), gmail_id);
    QCOMPARE(accounts[1].id(), github_id);
}

void AccountServiceTest::list_accounts_empty_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto accounts = service.list_accounts();

    QVERIFY(accounts.empty());
}

void AccountServiceTest::update_account_name_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("Gmail").value();

    const auto result = service.update_account_name(id, "Personal Gmail");

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(id);

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), "Personal Gmail");
}

void AccountServiceTest::update_account_name_id_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.update_account_name(core::AccountId{}, "Personal Gmail");

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

void AccountServiceTest::update_account_blank_name_fails_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("Gmail").value();

    const auto result = service.update_account_name(id, "");

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::EmptyName);

    const auto account = service.find_account_by_id(id);

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), "Gmail");
}

void AccountServiceTest::delete_account_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("Gmail").value();

    const auto result = service.delete_account(id);

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(id);

    QVERIFY(!account.has_value());
}

void AccountServiceTest::delete_account_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.delete_account(core::AccountId{});

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::DeleteAccountError::NotFound);
}

void AccountServiceTest::add_credential_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto result =
        service.add_credential(account_id, core::Credential(core::CredentialType::Email, "user@gmail.com"));

    QVERIFY(result.has_value());

    const auto credential_id = result.value();

    const auto account = service.find_account_by_id(account_id);

    QVERIFY(account.has_value());
    QCOMPARE(account->credentials().size(), 1);

    const auto& credential = account->credentials()[0];

    QCOMPARE(credential.id, credential_id);
    QCOMPARE(credential.type, core::CredentialType::Email);
    QCOMPARE(std::get<QString>(credential.value), "user@gmail.com");
}

void AccountServiceTest::add_credential_invalid_credential_fails_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const core::Credential invalid_credential{core::CredentialType::None, "value"};

    const auto result = service.add_credential(account_id, invalid_credential);

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::InvalidCredential);

    const auto account = service.find_account_by_id(account_id);
    QVERIFY(account.has_value());
    QCOMPARE(account->credentials().size(), 0);
}

void AccountServiceTest::add_credential_account_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result =
        service.add_credential(core::AccountId{}, core::Credential(core::CredentialType::Email, "user@gmail.com"));

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

void AccountServiceTest::update_credential_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto add_result =
        service.add_credential(account_id, core::Credential(core::CredentialType::Email, "old@gmail.com"));

    QVERIFY(add_result.has_value());

    const auto credential_id = add_result.value();

    const auto update_result = service.update_credential(
        account_id, credential_id, core::Credential(core::CredentialType::Email, "new@gmail.com"));

    QVERIFY(update_result.has_value());

    const auto account = service.find_account_by_id(account_id);

    QVERIFY(account.has_value());
    QCOMPARE(account->credentials().size(), 1);
    QCOMPARE(account->credentials()[0].id, credential_id);
    QCOMPARE(account->credentials()[0].type, core::CredentialType::Email);
    QCOMPARE(std::get<QString>(account->credentials()[0].value), "new@gmail.com");
}

void AccountServiceTest::update_credential_invalid_credential_fails_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto add_result =
        service.add_credential(account_id, core::Credential(core::CredentialType::Email, "old@gmail.com"));

    QVERIFY(add_result.has_value());

    const auto credential_id = add_result.value();

    const auto result =
        service.update_credential(account_id, credential_id, core::Credential(core::CredentialType::None, "value"));

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::InvalidCredential);

    // Make sure the old credential wasn't modified.
    const auto account = service.find_account_by_id(account_id);

    QVERIFY(account.has_value());
    QCOMPARE(account->credentials().size(), 1);
    QCOMPARE(std::get<QString>(account->credentials()[0].value), "old@gmail.com");
}

void AccountServiceTest::update_credential_account_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.update_credential(core::AccountId{}, core::CredentialId{},
                                                  core::Credential(core::CredentialType::Email, "new@gmail.com"));

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

void AccountServiceTest::update_credential_credential_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto result = service.update_credential(account_id, core::CredentialId{},
                                                  core::Credential(core::CredentialType::Email, "new@gmail.com"));

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::CredentialNotFound);
}

void AccountServiceTest::remove_credential_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto add_result =
        service.add_credential(account_id, core::Credential(core::CredentialType::Email, "user@gmail.com"));

    QVERIFY(add_result.has_value());

    const auto credential_id = add_result.value();

    const auto remove_result = service.remove_credential(account_id, credential_id);

    QVERIFY(remove_result.has_value());

    const auto account = service.find_account_by_id(account_id);

    QVERIFY(account.has_value());
    QCOMPARE(account->credentials().size(), 0);
}

void AccountServiceTest::remove_credential_credential_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account_id = service.create_account("Gmail").value();

    const auto result = service.remove_credential(account_id, core::CredentialId{});

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::CredentialNotFound);
}

void AccountServiceTest::remove_credential_account_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.remove_credential(core::AccountId{}, core::CredentialId{});

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

QTEST_MAIN(AccountServiceTest)

#include "account_service_test.moc"
