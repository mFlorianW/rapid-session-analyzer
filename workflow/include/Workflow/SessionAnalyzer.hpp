// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_SESSIONANALYZER_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_SESSIONANALYZER_HPP

#include <Common/Session.hpp>
#include <Common/Lap.hpp>
#include <QVector>
#include <QTime>
#include <QString>
#include <QMap>

namespace RapidSessionAnalyzer::Workflow
{

struct LapOverview
{
    QString id; // optional identifier (e.g., index)
    QTime laptime;
    QVector<QTime> sectors;
};

class SessionAnalyzer
{
public:
    [[nodiscard]] static QVector<LapOverview> analyze(Common::Session const& session) noexcept;

    // Group laps by track name across multiple sessions. The returned map's key is the track name
    // and the value is a vector with one entry per session: each entry is the session's LapOverviews.
    [[nodiscard]] static QMap<QString, QVector<QVector<LapOverview>>> compareByTrack(QList<Common::Session> const& sessions) noexcept;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_SESSIONANALYZER_HPP
