#include "Account.h"
#include "Credential.h"
#include "CredentialType.h"

#include <QString>
#include <QTest>

// HELPER FUNCTIONS
// Helper: compares two credential vectors field-by-field (better failure
// messages than operator==)
static void compare_credentials(const std::vector<core::Credential>& actual,
                                const std::vector<core::Credential>& expected) {
    QCOMPARE(static_cast<int>(actual.size()), static_cast<int>(expected.size()));
    for (size_t i = 0; i < expected.size(); ++i) {
        QCOMPARE(actual[i].type, expected[i].type);
        QCOMPARE(actual[i].details, expected[i].details);
    }
}

class AccountTest : public QObject {
    Q_OBJECT

private slots:
    void dummy();
    void create_account_with_credentials_test();
    void create_account_without_credentials_test();
    void create_account_time_test();
    void update_name_test();
    void update_credentials_test();
};

void AccountTest::dummy() { QVERIFY(true); }

void AccountTest::create_account_with_credentials_test() {
    const QString name = "Gmail";

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "jfitzgerald1998@gmail.com"},
        {core::CredentialType::Password, "theSWAGLord()!!"},
        {core::CredentialType::SecretQuestion, "What was your mother's maiden name?"},
        {core::CredentialType::SecretAnswer, "Williams"},
    };

    const core::Account account(name, credentials);

    QVERIFY(!account.id().isNull());
    // Test name
    QCOMPARE(account.name(), name);

    // Test credentials
    const auto& actual = account.credentials();
    QCOMPARE(static_cast<int>(actual.size()), static_cast<int>(credentials.size()));

    compare_credentials(actual, credentials);
}

void AccountTest::create_account_without_credentials_test() {
    const QString name = "Gmail";

    core::Account account(name);

    // Test id is valid
    QVERIFY(!account.id().isNull());

    // Test name
    QCOMPARE(account.name(), name);

    // Test credentials are empty
    QVERIFY(account.credentials().empty());
}

void AccountTest::create_account_time_test() {
    const QString name = "Gmail";

    core::Account account(name);

    QVERIFY(account.created_at().isValid());
    QVERIFY(account.updated_at().isValid());
    QCOMPARE(account.created_at(), account.updated_at());
}

void AccountTest::update_name_test() {
    core::Account account("Gmail");

    const auto updated_before = account.updated_at();

    QTest::qWait(5);
    account.update_name("Google Mail");

    QCOMPARE(account.name(), QString("Google Mail"));
    QVERIFY(account.updated_at() > updated_before);
}

void AccountTest::update_credentials_test() {
    const QString name = "Outlook";

    const std::vector<core::Credential> credentials{
        {core::CredentialType::Email, "jfitzgerald1998@gmail.com"},
        {core::CredentialType::Password, "theSWAGLord()!!"},
        {core::CredentialType::SecretQuestion, "What was your mother's maiden name?"},
        {core::CredentialType::SecretAnswer, "Williams"},
    };

    core::Account account(name, credentials);

    const auto updated_before = account.updated_at();

    const std::vector<core::Credential> new_credentials{{core::CredentialType::Email, "gregoryheffly01@outlook.com"},
                                                        {core::CredentialType::Password, "superC00L!!()"},
                                                        {core::CredentialType::PhoneNumber, "0535345834"},
                                                        {core::CredentialType::RecoveryPhrase, "Greetings"},
                                                        {core::CredentialType::Pin, "4021"}};

    // ACT
    QTest::qWait(5);
    account.update_credentials(new_credentials);

    // ASSERT — updated_at should move forward
    QVERIFY(account.updated_at() > updated_before);

    // ASSERT — credentials should match exactly
    compare_credentials(account.credentials(), new_credentials);
}

QTEST_MAIN(AccountTest)

#include "account_test.moc"
