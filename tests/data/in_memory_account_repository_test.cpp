#include "Account.h"
#include "AccountErrors.h"
#include "Credential.h"
#include "InMemoryAccountRepository.h"
#include <QtTest/QtTest>

class InMemoryAccountRepositoryTest : public QObject {
    Q_OBJECT

private slots:
    void dummy();

    void add_account_success_test();
    void add_account_duplicate_id_fails_test();

    void find_account_by_id_success_test();
    void find_account_by_id_not_found_test();

    void find_accounts_by_name_success_test();
    void find_accounts_by_name_no_matches_test();

    void list_accounts_success_test();
    void list_accounts_empty_test();

    void update_account_success_test();
    void update_account_not_found_test();

    void remove_account_success_test();
    void remove_account_not_found_test();
};

void InMemoryAccountRepositoryTest::dummy() { QVERIFY(true); }

void InMemoryAccountRepositoryTest::add_account_success_test() {
    const QString name = "Gmail";

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "jfitzgerald1998@gmail.com"},
        {core::CredentialType::Password, "theSWAGLord()!!"},
    };

    // Creating account
    const core::Account account(name, credentials);

    // Creating repository
    data::InMemoryAccountRepository repository{};

    const auto result = repository.add(account);

    QVERIFY(result.has_value());

    const auto found_account = repository.find_by_id(account.id());

    QVERIFY(found_account.has_value());
    QCOMPARE(found_account->id(), account.id());
    QCOMPARE(found_account->name(), account.name());
    QCOMPARE(found_account->credentials(), account.credentials());
}

void InMemoryAccountRepositoryTest::add_account_duplicate_id_fails_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account account("Gmail");

    QVERIFY(repository.add(account).has_value());

    const auto result = repository.add(account);

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::CreateAccountError::AlreadyExists);
}

void InMemoryAccountRepositoryTest::find_account_by_id_success_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account account_1("Gmail", {});
    const core::Account account_2("GitHub", {});

    QVERIFY(repository.add(account_1).has_value());
    QVERIFY(repository.add(account_2).has_value());

    const auto found_account = repository.find_by_id(account_2.id());

    QVERIFY(found_account.has_value());
    QCOMPARE(found_account->id(), account_2.id());
    QCOMPARE(found_account->name(), account_2.name());
}

void InMemoryAccountRepositoryTest::find_account_by_id_not_found_test() {
    data::InMemoryAccountRepository repository{};

    const auto found_account = repository.find_by_id(QUuid::createUuid());

    QVERIFY(!found_account.has_value());
}

void InMemoryAccountRepositoryTest::find_accounts_by_name_success_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account gmail("Gmail");
    const core::Account github("GitHub");
    const core::Account outlook("Outlook");

    QVERIFY(repository.add(gmail).has_value());
    QVERIFY(repository.add(github).has_value());
    QVERIFY(repository.add(outlook).has_value());

    const auto results = repository.find_accounts_by_name("it");

    QCOMPARE(results.size(), 1);
    QCOMPARE(results[0].id, github.id());
    QCOMPARE(results[0].name, github.name());
}

void InMemoryAccountRepositoryTest::find_accounts_by_name_no_matches_test() {
    data::InMemoryAccountRepository repository{};

    QVERIFY(repository.add(core::Account("Gmail")).has_value());
    QVERIFY(repository.add(core::Account("GitHub")).has_value());

    const auto results = repository.find_accounts_by_name("Outlook");

    QVERIFY(results.empty());
}

void InMemoryAccountRepositoryTest::list_accounts_success_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account gmail("Gmail");
    const core::Account github("GitHub");

    QVERIFY(repository.add(gmail).has_value());
    QVERIFY(repository.add(github).has_value());

    const auto accounts = repository.list();

    QCOMPARE(accounts.size(), 2);
    QCOMPARE(accounts[0].id(), gmail.id());
    QCOMPARE(accounts[1].id(), github.id());
}

void InMemoryAccountRepositoryTest::list_accounts_empty_test() {
    data::InMemoryAccountRepository repository{};

    const auto accounts = repository.list();

    QVERIFY(accounts.empty());
}

void InMemoryAccountRepositoryTest::update_account_success_test() {
    data::InMemoryAccountRepository repository{};

    core::Account account("Gmail");

    QVERIFY(repository.add(account).has_value());

    const std::vector<core::Credential> updated_credentials{
        {core::CredentialType::Email, "user@example.com"},
        {core::CredentialType::Password, "password"},
    };

    account.update_name("Personal Gmail");
    account.update_credentials(updated_credentials);

    const auto result = repository.update(account);

    QVERIFY(result.has_value());

    const auto found_account = repository.find_by_id(account.id());

    QVERIFY(found_account.has_value());
    QCOMPARE(found_account->name(), "Personal Gmail");
    QCOMPARE(found_account->credentials(), updated_credentials);
}

void InMemoryAccountRepositoryTest::update_account_not_found_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account account("Gmail");

    const auto result = repository.update(account);

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::UpdateAccountError::NotFound);
}

void InMemoryAccountRepositoryTest::remove_account_success_test() {
    data::InMemoryAccountRepository repository{};

    const core::Account account("Gmail");

    QVERIFY(repository.add(account).has_value());

    const auto result = repository.remove(account.id());

    QVERIFY(result.has_value());

    const auto found_account = repository.find_by_id(account.id());

    QVERIFY(!found_account.has_value());
}

void InMemoryAccountRepositoryTest::remove_account_not_found_test() {
    data::InMemoryAccountRepository repository{};

    const auto result = repository.remove(QUuid::createUuid());

    QVERIFY(!result.has_value());
    QCOMPARE(result.error(), core::DeleteAccountError::NotFound);
}

QTEST_MAIN(InMemoryAccountRepositoryTest)

#include "in_memory_account_repository_test.moc"
