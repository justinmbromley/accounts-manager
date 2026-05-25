#include "Account.h"
#include "Credential.h"
#include "CredentialType.h"
#include "SqliteAccountRepository.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtTest/QtTest>

class SqliteAccountRepositoryTest : public QObject {
    Q_OBJECT

private slots:
    void init();
    void cleanup();

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

private:
    QString connection_name_;
    QSqlDatabase db_;
};

// Database boilerplate
void SqliteAccountRepositoryTest::init() {
    connection_name_ = QString::fromLatin1(QTest::currentTestFunction());

    db_ = QSqlDatabase::addDatabase("QSQLITE", connection_name_);
    db_.setDatabaseName(":memory:");

    QVERIFY(db_.open());

    QSqlQuery query(db_);

    QVERIFY(query.exec(R"(
        CREATE TABLE accounts (
            id TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            created_at TEXT NOT NULL,
            updated_at TEXT NOT NULL
        )
    )"));

    QVERIFY(query.exec(R"(
        CREATE TABLE credentials (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            account_id TEXT NOT NULL,
            type TEXT NOT NULL,
            details TEXT NOT NULL,
            FOREIGN KEY (account_id)
                REFERENCES accounts(id)
                ON DELETE CASCADE
        )
    )"));
}

void SqliteAccountRepositoryTest::cleanup() {
    db_.close();
    db_ = QSqlDatabase();

    QSqlDatabase::removeDatabase(connection_name_);
}

// Tests
void SqliteAccountRepositoryTest::add_account_success_test() {
    data::SqliteAccountRepository repository{db_};

    const core::Account account("Gmail", {
                                             {core::CredentialType::Email, "example@gmail.com"},
                                             {core::CredentialType::Password, "password123"},
                                         });

    const auto result = repository.add(account);

    QVERIFY(result.has_value());

    // Account
    QSqlQuery account_query(db_);

    account_query.prepare(R"(
        SELECT id, name, created_at, updated_at
        FROM accounts
        WHERE id = :id
    )");

    account_query.bindValue(":id", account.id().toString());

    QVERIFY(account_query.exec());
    QVERIFY(account_query.next());

    QCOMPARE(QUuid::fromString(account_query.value("id").toString()), account.id());
    QCOMPARE(account_query.value("name").toString(), account.name());
    QVERIFY(account_query.value("created_at").isValid());
    QVERIFY(account_query.value("updated_at").isValid());

    QVERIFY(!account_query.next());

    // Credentials
    QSqlQuery credential_query(db_);

    credential_query.prepare(R"(
        SELECT type, details
        FROM credentials
        WHERE account_id = :account_id
        ORDER BY id
    )");

    credential_query.bindValue(":account_id", account.id().toString());

    QVERIFY(credential_query.exec());

    QVERIFY(credential_query.next());
    QCOMPARE(credential_query.value("type").toString(), QString::number(static_cast<int>(core::CredentialType::Email)));
    QCOMPARE(credential_query.value("details").toString(), QString("example@gmail.com"));

    QVERIFY(credential_query.next());
    QCOMPARE(credential_query.value("type").toString(),
             QString::number(static_cast<int>(core::CredentialType::Password)));
    QCOMPARE(credential_query.value("details").toString(), QString("password123"));

    QVERIFY(!credential_query.next());
}

void SqliteAccountRepositoryTest::add_account_duplicate_id_fails_test() {
    data::SqliteAccountRepository repository{db_};

    const core::Account account("Gmail", {
                                             {core::CredentialType::Email, "example@gmail.com"},
                                             {core::CredentialType::Password, "password123"},
                                         });

    const auto result_1 = repository.add(account);

    QVERIFY(result_1.has_value());

    const auto result_2 = repository.add(account);

    QVERIFY(!result_2.has_value());
}

void SqliteAccountRepositoryTest::find_account_by_id_success_test() {
    data::SqliteAccountRepository repository{db_};

    const core::Account account_1("Gmail", {
                                               {core::CredentialType::Email, "example@gmail.com"},
                                               {core::CredentialType::Password, "password123"},
                                           });

    const core::Account account_2("Outlook", {
                                                 {core::CredentialType::Email, "example@outlook.com"},
                                                 {core::CredentialType::Password, "password321"},
                                                 {core::CredentialType::PhoneNumber, "0535345834"},
                                             });

    // Setup DB state with raw SQL
    QSqlQuery query(db_);

    query.prepare(R"(
        INSERT INTO accounts (
            id,
            name,
            created_at,
            updated_at
        )
        VALUES (
            :id,
            :name,
            :created_at,
            :updated_at
        )
    )");

    query.bindValue(":id", account_1.id().toString());
    query.bindValue(":name", account_1.name());
    query.bindValue(":created_at", account_1.createdAt().toString(Qt::ISODate));
    query.bindValue(":updated_at", account_1.updatedAt().toString(Qt::ISODate));

    QVERIFY(query.exec());

    query.bindValue(":id", account_2.id().toString());
    query.bindValue(":name", account_2.name());
    query.bindValue(":created_at", account_2.createdAt().toString(Qt::ISODate));
    query.bindValue(":updated_at", account_2.updatedAt().toString(Qt::ISODate));

    QVERIFY(query.exec());

    // Method under test
    const auto result = repository.find_by_id(account_2.id());

    // Assertions
    QVERIFY(result.has_value());

    QCOMPARE(result->id(), account_2.id());
    QCOMPARE(result->name(), account_2.name());
}

void SqliteAccountRepositoryTest::find_account_by_id_not_found_test() {
    data::SqliteAccountRepository repository{db_};

    const auto result = repository.find_by_id(QUuid::createUuid());

    QVERIFY(!result.has_value());
}

void SqliteAccountRepositoryTest::find_accounts_by_name_success_test() {
    data::SqliteAccountRepository repository{db_};

    const core::Account account_1("Gmail", {
                                               {core::CredentialType::Email, "example@gmail.com"},
                                               {core::CredentialType::Password, "password123"},
                                           });

    const core::Account account_2("Outlook", {
                                                 {core::CredentialType::Email, "example@outlook.com"},
                                                 {core::CredentialType::Password, "password321"},
                                                 {core::CredentialType::PhoneNumber, "0535345834"},
                                             });

    const core::Account account_3("Gmail",
                                  {
                                      {core::CredentialType::Email, .details = "example2@gmail.com"},
                                      {core::CredentialType::Password, "password123"},
                                      {core::CredentialType::SecretQuestion, "What was your mother's maiden name?"},
                                      {core::CredentialType::SecretAnswer, "Williams"},
                                  });

    // Setup DB state with raw SQL
    QSqlQuery query(db_);

    query.prepare(R"(
        INSERT INTO accounts (
            id,
            name,
            created_at,
            updated_at
        )
        VALUES (
            :id,
            :name,
            :created_at,
            :updated_at
        )
    )");

    query.bindValue(":id", account_1.id().toString());
    query.bindValue(":name", account_1.name());
    query.bindValue(":created_at", account_1.createdAt().toString(Qt::ISODate));
    query.bindValue(":updated_at", account_1.updatedAt().toString(Qt::ISODate));

    QVERIFY(query.exec());

    query.bindValue(":id", account_2.id().toString());
    query.bindValue(":name", account_2.name());
    query.bindValue(":created_at", account_2.createdAt().toString(Qt::ISODate));
    query.bindValue(":updated_at", account_2.updatedAt().toString(Qt::ISODate));

    QVERIFY(query.exec());

    query.bindValue(":id", account_3.id().toString());
    query.bindValue(":name", account_3.name());
    query.bindValue(":created_at", account_3.createdAt().toString(Qt::ISODate));
    query.bindValue(":updated_at", account_3.updatedAt().toString(Qt::ISODate));
}

QTEST_MAIN(SqliteAccountRepositoryTest)

#include "sqlite_account_repository_test.moc"
