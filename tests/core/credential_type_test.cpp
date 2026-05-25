#include <QtTest>

#include "CredentialType.h"

class CredentialTypeTest : public QObject {
    Q_OBJECT

private slots:
    void credential_type_to_string_test();
    void credential_type_from_string_test();
};

void CredentialTypeTest::credential_type_to_string_test() {
    QCOMPARE(core::credential_type_to_string(core::CredentialType::None), QString("NONE"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::Username), QString("USERNAME"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::Email), QString("EMAIL"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::Password), QString("PASSWORD"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::SecretQuestion), QString("SECRET_QUESTION"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::SecretAnswer), QString("SECRET_ANSWER"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::RecoveryPhrase), QString("RECOVERY_PHRASE"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::Pin), QString("PIN"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::ExpiryDate), QString("EXPIRY_DATE"));
    QCOMPARE(core::credential_type_to_string(core::CredentialType::PhoneNumber), QString("PHONE_NUMBER"));
}

void CredentialTypeTest::credential_type_from_string_test() {
    QCOMPARE(core::credential_type_from_string("NONE"), core::CredentialType::None);
    QCOMPARE(core::credential_type_from_string("USERNAME"), core::CredentialType::Username);
    QCOMPARE(core::credential_type_from_string("EMAIL"), core::CredentialType::Email);
    QCOMPARE(core::credential_type_from_string("PASSWORD"), core::CredentialType::Password);
    QCOMPARE(core::credential_type_from_string("SECRET_QUESTION"), core::CredentialType::SecretQuestion);
    QCOMPARE(core::credential_type_from_string("SECRET_ANSWER"), core::CredentialType::SecretAnswer);
    QCOMPARE(core::credential_type_from_string("RECOVERY_PHRASE"), core::CredentialType::RecoveryPhrase);
    QCOMPARE(core::credential_type_from_string("PIN"), core::CredentialType::Pin);
    QCOMPARE(core::credential_type_from_string("EXPIRY_DATE"), core::CredentialType::ExpiryDate);
    QCOMPARE(core::credential_type_from_string("PHONE_NUMBER"), core::CredentialType::PhoneNumber);

    QCOMPARE(core::credential_type_from_string("INVALID_TYPE"), core::CredentialType::None);
}

QTEST_MAIN(CredentialTypeTest)

#include "credential_type_test.moc"
