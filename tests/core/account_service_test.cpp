#include "AccountService.h"
#include "Credential.h"
#include "CredentialType.h"
#include "InMemoryAccountRepository.h"

#include <QtTest>

class AccountServiceTest : public QObject {
    Q_OBJECT

private slots:
    void create_account_success_test();
    void find_account_by_id_success_test();
    void find_account_by_id_not_found_test();
    void find_accounts_by_name_success_test();
    void list_accounts_success_test();
    void update_account_name_success_test();
    void update_account_name_not_found_test();
    void update_account_credentials_success_test();
    void update_account_credentials_not_found_test();
    void delete_account_success_test();
    void delete_account_not_found_test();
};

void AccountServiceTest::create_account_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.create_account("Gmail");

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(result.value());

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), QString{"Gmail"});
}

void AccountServiceTest::find_account_by_id_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("GitHub").value();

    const auto account = service.find_account_by_id(id);

    QVERIFY(account.has_value());
    QCOMPARE(account->id(), id);
    QCOMPARE(account->name(), QString{"GitHub"});
}

void AccountServiceTest::find_account_by_id_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto account = service.find_account_by_id(QUuid::createUuid());

    QVERIFY(!account.has_value());
}

void AccountServiceTest::find_accounts_by_name_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    service.create_account("Gmail");
    const auto github_id = service.create_account("GitHub").value();
    service.create_account("Outlook");

    const auto results = service.find_accounts_by_name("Git");

    QCOMPARE(results.size(), 1);
    QCOMPARE(results[0].id, github_id);
    QCOMPARE(results[0].name, QString{"GitHub"});
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

void AccountServiceTest::update_account_name_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("Gmail").value();

    const auto result = service.update_account_name(id, "Personal Gmail");

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(id);

    QVERIFY(account.has_value());
    QCOMPARE(account->name(), QString{"Personal Gmail"});
}

void AccountServiceTest::update_account_name_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto result = service.update_account_name(QUuid::createUuid(), "Personal Gmail");

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

void AccountServiceTest::update_account_credentials_success_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const auto id = service.create_account("Gmail").value();

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "user@example.com"},
        {core::CredentialType::Password, "password"},
    };

    const auto result = service.update_account_credentials(id, credentials);

    QVERIFY(result.has_value());

    const auto account = service.find_account_by_id(id);

    QVERIFY(account.has_value());
    QCOMPARE(account->credentials(), credentials);
}

void AccountServiceTest::update_account_credentials_not_found_test() {
    data::InMemoryAccountRepository repository{};
    core::AccountService service{repository};

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "user@example.com"},
    };

    const auto result = service.update_account_credentials(QUuid::createUuid(), credentials);

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
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

    const auto result = service.delete_account(QUuid::createUuid());

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::DeleteAccountError::NotFound);
}

QTEST_MAIN(AccountServiceTest)

#include "account_service_test.moc"
