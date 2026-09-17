#include "Credential.h"
#include "CredentialType.h"
#include "CredentialValidator.h"

#include <QTest>

class CredentialValidatorTest : public QObject {
    Q_OBJECT

private slots:
    void valid_username_credential();
    void valid_password_credential();
    void valid_secretqa_credential();

    void invalid_none_type();
    void invalid_empty_string();
    void invalid_whitespace_string();

    void invalid_secretqa_empty_question();
    void invalid_secretqa_empty_answer();

    void invalid_secretqa_type_mismatch();
    void invalid_string_type_mismatch();
};

void CredentialValidatorTest::valid_username_credential() {
    const core::Credential credential{core::CredentialType::Username, "user123"};

    QVERIFY(core::is_valid_credential(credential));
}

void CredentialValidatorTest::valid_password_credential() {
    const core::Credential credential{core::CredentialType::Password, "password123"};

    QVERIFY(core::is_valid_credential(credential));
}

void CredentialValidatorTest::valid_secretqa_credential() {
    const core::Credential credential{core::CredentialType::SecretQA, core::SecretQA{"Favourite colour?", "blue"}};

    QVERIFY(core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_none_type() {
    const core::Credential credential{core::CredentialType::None, "value"};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_empty_string() {
    const core::Credential credential{core::CredentialType::Username, ""};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_whitespace_string() {
    const core::Credential credential{core::CredentialType::Username, "   "};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_secretqa_empty_question() {
    const core::Credential credential{core::CredentialType::SecretQA, core::SecretQA{"", "blue"}};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_secretqa_empty_answer() {
    const core::Credential credential{core::CredentialType::SecretQA, core::SecretQA{"Favourite colour?", ""}};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_secretqa_type_mismatch() {
    const core::Credential credential{core::CredentialType::SecretQA, "not a secret qa"};

    QVERIFY(!core::is_valid_credential(credential));
}

void CredentialValidatorTest::invalid_string_type_mismatch() {
    const core::Credential credential{core::CredentialType::Username, core::SecretQA{"Question", "Answer"}};

    QVERIFY(!core::is_valid_credential(credential));
}

QTEST_MAIN(CredentialValidatorTest)

#include "credential_validator_test.moc"
