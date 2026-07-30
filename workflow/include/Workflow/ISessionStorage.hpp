// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_ISESSIONSTORAGE_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_ISESSIONSTORAGE_HPP

#include <Common/Session.hpp>
#include <Common/SessionInfo.hpp>
#include <QVector>
#include <QString>
#include <expected>

namespace RapidSessionAnalyzer::Workflow
{

class ISessionStorage
{
public:
    virtual ~ISessionStorage() = default;

    [[nodiscard]] virtual std::expected<QVector<Common::SessionInfo>, QString> getSessionInfos() const = 0;
    [[nodiscard]] virtual std::expected<Common::Session, QString> load(QStringView sessionId) const = 0;
    virtual std::expected<void, QString> store(QStringView sessionId, Common::Session const& session) const = 0;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_ISESSIONSTORAGE_HPP
