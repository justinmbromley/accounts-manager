#include "Account.h"
#include "Credential.h"
#include "CredentialType.h"
#include "ids/EntityIds.h"

#include <QString>
#include <QTest>
#include <qtestcase.h>
#include <vector>

class AccountTest : public QObject {
    Q_OBJECT

private slots:
    void create_account_with_credentials_test();
    void create_account_without_credentials_test();
    void create_account_time_test();
    void update_name_test();

    void add_credential_test();
    void update_credential_test();
    void update_missing_credential_test();
    void remove_credential_test();
    void remove_missing_credential_test();
    void find_credential_test();
    void find_missing_credential_test();
};

void AccountTest::create_account_with_credentials_test() {
    const QString name = "Gmail";

    const std::vector<core::Credential> credentials{
        core::Credential{core::CredentialType::Email, "jfitzgerald1998@gmail.com"},
        core::Credential{core::CredentialType::Password, "theSWAGLord()!!"},
        core::Credential{core::CredentialType::SecretQA, core::SecretQA{"What is your favorite color?", "Blue"}},
    };

    const core::Account account{name, credentials};

    QVERIFY(account.id().is_valid());
    QCOMPARE(account.name(), name);
    QCOMPARE(account.credentials(), credentials);
}

void AccountTest::create_account_without_credentials_test() {
    const QString name = "Gmail";

    const core::Account account{name};

    QVERIFY(account.id().is_valid());
    QCOMPARE(account.name(), name);
    QVERIFY(account.credentials().empty());
}

void AccountTest::create_account_time_test() {
    const QString name = "Gmail";

    const core::Account account{name};

    QVERIFY(account.created_at().isValid());
    QVERIFY(account.updated_at().isValid());
    QCOMPARE(account.created_at(), account.updated_at());
}

void AccountTest::update_name_test() {
    const QString name = "Gmail";
    const QString new_name = "Google Mail";

    core::Account account{"Gmail"};

    const auto time_created = account.updated_at();

    QTest::qWait(5);
    account.update_name(new_name);

    QCOMPARE(account.name(), new_name);
    QVERIFY(account.updated_at() > time_created);
}

void AccountTest::add_credential_test() {
    core::Account account("Gmail");

    const auto updated_before = account.updated_at();

    const core::Credential email{core::CredentialType::Email, "gregheffley@gmail.com"};

    QTest::qWait(5);
    account.add_credential(email);

    QVERIFY(account.credentials().front().id.is_valid());
    QCOMPARE(account.credentials().size(), std::size_t{1});
    QCOMPARE(account.credentials().front(), email);
    QVERIFY(account.updated_at() > updated_before);
}

void AccountTest::update_credential_test() {
    const core::Credential old_email{core::CredentialType::Email, "old@gmail.com"};

    core::Account account{"Gmail", {old_email}};

    const core::Credential new_email{core::CredentialType::Email, "new@gmail.com"};

    const auto updated_before = account.updated_at();

    QTest::qWait(5);
    const bool updated = account.update_credential(old_email.id, new_email);

    QVERIFY(updated);
    QCOMPARE(account.credentials().size(), std::size_t{1});
    QCOMPARE(account.credentials().front(), new_email);
    QVERIFY(account.updated_at() > updated_before);
}

void AccountTest::update_missing_credential_test() {
    const core::Credential email(core::CredentialType::Email, "old@gmail.com");
    const core::Credential new_email(core::CredentialType::Email, "new@gmail.com");

    core::Account account{"Gmail", {email}};

    const auto updated_before = account.updated_at();

    const core::CredentialId missing_id{};

    QTest::qWait(5);
    const bool updated = account.update_credential(missing_id, new_email);

    QVERIFY(!updated);
    QCOMPARE(account.credentials().size(), std::size_t{1});
    QCOMPARE(account.credentials().front(), email);
    QCOMPARE(account.updated_at(), updated_before);
}

void AccountTest::remove_credential_test() {
    const core::Credential email{core::CredentialType::Email, "gregheffley@gmail.com"};

    core::Account account{"Gmail", {email}};

    const auto updated_before = account.updated_at();

    QTest::qWait(5);
    const bool removed = account.remove_credential(email.id);

    QVERIFY(removed);
    QVERIFY(account.credentials().empty());
    QVERIFY(account.updated_at() > updated_before);
}

void AccountTest::remove_missing_credential_test() {
    const core::Credential email{core::CredentialType::Email, "gregheffley@gmail.com"};

    core::Account account{"Gmail", {email}};

    const auto updated_before = account.updated_at();

    QTest::qWait(5);
    const bool removed = account.remove_credential(core::CredentialId{});

    QVERIFY(!removed);
    QCOMPARE(account.credentials().size(), std::size_t{1});
    QCOMPARE(account.credentials().front(), email);
    QCOMPARE(account.updated_at(), updated_before);
}

void AccountTest::find_credential_test() {
    const core::Credential email{core::CredentialType::Email, "gregheffley@gmail.com"};

    core::Account account{"Gmail", {email}};

    const std::optional<core::Credential> found = account.find_credential(email.id);

    QVERIFY(found.has_value());
    QCOMPARE(found.value(), email);
}

void AccountTest::find_missing_credential_test() {
    const core::Credential email(core::CredentialType::Email, "gregheffley@gmail.com");

    core::Account account("Gmail", {email});

    const std::optional<core::Credential> found = account.find_credential(core::CredentialId{});

    QVERIFY(!found.has_value());
}

QTEST_MAIN(AccountTest)

#include "account_test.moc"
