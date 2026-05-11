#include "Account.h"
#include "Credential.h"
#include "CredentialType.h"

#include <QString>
#include <QTest>

// HELPER FUNCTIONS
static void compare_credentials(const std::vector<core::Credential>& actual,
                                const std::vector<core::Credential>& expected) {
    QCOMPARE(actual.size(), expected.size());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        QCOMPARE(actual[i].type, expected[i].type);
        QCOMPARE(actual[i].details, expected[i].details);
    }
}

class AccountTest : public QObject {
    Q_OBJECT

private slots:
    void create_account_with_credentials_test();
    void create_account_without_credentials_test();
    void create_account_time_test();
    void update_name_test();
    void update_credentials_test();
};

void AccountTest::create_account_with_credentials_test() {
    const QString name = "Email";

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "user@example.com"},
        {core::CredentialType::Password, "password123"},
        {core::CredentialType::SecretQuestion, "What is your security question?"},
        {core::CredentialType::SecretAnswer, "answer"},
    };

    const core::Account account(name, credentials);

    QVERIFY(!account.id().isNull());
    QCOMPARE(account.name(), name);
    compare_credentials(account.credentials(), credentials);
}

void AccountTest::create_account_without_credentials_test() {
    const QString name = "Email";

    const core::Account account(name);

    // Test id is valid
    QVERIFY(!account.id().isNull());

    // Test name
    QCOMPARE(account.name(), name);
    QVERIFY(account.credentials().empty());
}

void AccountTest::create_account_time_test() {
    const core::Account account("Email");

    QVERIFY(account.created_at().isValid());
    QVERIFY(account.updated_at().isValid());
    QCOMPARE(account.created_at(), account.updated_at());
}

void AccountTest::update_name_test() {
    core::Account account("Email");

    const auto updated_before = account.updated_at();

    QTest::qWait(5);
    account.update_name("Personal Email");

    QCOMPARE(account.name(), QString("Personal Email"));
    QVERIFY(account.updated_at() > updated_before);
}

void AccountTest::update_credentials_test() {
    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "user@example.com"},
        {core::CredentialType::Password, "password123"},
    };

    core::Account account("Email", credentials);

    const auto updated_before = account.updated_at();

    const std::vector<core::Credential> new_credentials{
        {core::CredentialType::Email, "new-user@example.com"},
        {core::CredentialType::Password, "new-password123"},
        {core::CredentialType::PhoneNumber, "0400000000"},
        {core::CredentialType::RecoveryPhrase, "example recovery phrase"},
        {core::CredentialType::Pin, "1234"},
    };

    QTest::qWait(5);
    account.update_credentials(new_credentials);

    QVERIFY(account.updated_at() > updated_before);
    compare_credentials(account.credentials(), new_credentials);
}

QTEST_MAIN(AccountTest)

#include "account_test.moc"
