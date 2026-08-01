// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_IDEVICESESSIONMANAGEMENT_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_IDEVICESESSIONMANAGEMENT_HPP

#include <Common/Session.hpp>
#include <Common/SessionInfo.hpp>
#include <QVector>
#include <QString>
#include <expected>

namespace RapidSessionAnalyzer::Workflow
{

class IDeviceSessionManagement
{
public:
    virtual ~IDeviceSessionManagement() = default;

    [[nodiscard]] virtual std::expected<QVector<Common::SessionInfo>, QString> getSessionInfos() const = 0;
    [[nodiscard]] virtual std::expected<Common::Session, QString> load(QStringView sessionId) const = 0;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_IDEVICESESSIONMANAGEMENT_HPP
