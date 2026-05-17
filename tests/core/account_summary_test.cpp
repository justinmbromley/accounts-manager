#include <QtTest>

#include <QtTest>

#include "Account.h"
#include "AccountSummary.h"
#include "Credential.h"
#include "CredentialType.h"

class AccountSummaryTest : public QObject {
    Q_OBJECT

private slots:
    void to_account_summary_copies_basic_fields();
    void to_account_summary_prefers_email_over_username();
    void to_account_summary_uses_username_when_email_missing();
    void to_account_summary_identifier_is_empty_when_no_identifier_credentials();
};

void AccountSummaryTest::to_account_summary_copies_basic_fields() {
    const core::Account account{"GitHub"};

    const auto summary = core::to_account_summary(account);

    QCOMPARE(summary.id, account.id());
    QCOMPARE(summary.name, account.name());
    QCOMPARE(summary.updated_at, account.updated_at());
}

void AccountSummaryTest::to_account_summary_prefers_email_over_username() {
    const std::vector<core::Credential> credentials{
        {core::CredentialType::Username, "github_user"},
        {core::CredentialType::Email, "person@example.com"},
    };

    const core::Account account{"GitHub", credentials};

    const auto summary = core::to_account_summary(account);

    QCOMPARE(summary.identifier, QString{"person@example.com"});
}

void AccountSummaryTest::to_account_summary_uses_username_when_email_missing() {
    const std::vector<core::Credential> credentials{
        {core::CredentialType::Username, "github_user"},
    };

    const core::Account account{"GitHub", credentials};

    const auto summary = core::to_account_summary(account);

    QCOMPARE(summary.identifier, QString{"github_user"});
}

void AccountSummaryTest::to_account_summary_identifier_is_empty_when_no_identifier_credentials() {
    const std::vector<core::Credential> credentials{
        {core::CredentialType::None, "some value"},
    };

    const core::Account account{"GitHub", credentials};

    const auto summary = core::to_account_summary(account);

    QVERIFY(summary.identifier.isEmpty());
}

QTEST_MAIN(AccountSummaryTest)

#include "account_summary_test.moc"
