// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/SessionAnalyzer.hpp>

namespace RapidSessionAnalyzer::Workflow
{

QVector<LapOverview> SessionAnalyzer::analyze(Common::Session const& session) noexcept
{
    QVector<LapOverview> result;
    const QVector<Common::Lap> laps = session.getLaps();
    result.reserve(laps.size());

    for (int i = 0; i < laps.size(); ++i) {
        LapOverview overview;
        overview.id = QString::number(i);
        overview.laptime = laps.at(i).laptime();
        overview.sectors = laps.at(i).sectors;
        result.append(std::move(overview));
    }

    return result;
}

QMap<QString, QVector<QVector<LapOverview>>> SessionAnalyzer::compareByTrack(QList<Common::Session> const& sessions) noexcept
{
    QMap<QString, QVector<QVector<LapOverview>>> result;

    for (auto const& session : sessions) {
        const QString trackName = session.getTrack().name;
        const auto overviews = analyze(session);
        // Ensure there is a slot for this session in the vector
        if (!result.contains(trackName)) {
            result.insert(trackName, {});
        }
        result[trackName].append(overviews);
    }

    return result;
}

} // namespace RapidSessionAnalyzer::Workflow
