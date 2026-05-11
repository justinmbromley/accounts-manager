#pragma once

#include "Credential.h"

#include <QDateTime>
#include <QString>
#include <QUuid>
#include <vector>

namespace core {

class Account {
public:
    // Constructors
    explicit Account(QString name, std::vector<Credential> credentials = {});

    // Methods
    void update_name(const QString& name);
    void update_credentials(const std::vector<Credential>& credentials);

    // Getters
    const QUuid& id() const noexcept;
    const QString& name() const noexcept;
    const std::vector<Credential>& credentials() const noexcept;
    const QDateTime& created_at() const noexcept;
    const QDateTime& updated_at() const noexcept;

private:
    void touch() noexcept;

    QUuid id_;
    QString name_;
    std::vector<Credential> credentials_;
    QDateTime time_created_;
    QDateTime time_updated_;
};

} // namespace core
