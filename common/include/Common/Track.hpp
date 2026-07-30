// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_TRACK_HPP
#define RAPIDSESSIONANALYZER_COMMON_TRACK_HPP

#include <Common/Position.hpp>
#include <QString>
#include <QVector>
#include <optional>

namespace RapidSessionAnalyzer::Common
{

struct Track
{
    QString name;
    Position startline;
    std::optional<Position> finishline;
    QVector<Position> sectors;

    bool operator==(Track const& other) const noexcept = default;
    bool operator!=(Track const& other) const noexcept = default;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_TRACK_HPP
