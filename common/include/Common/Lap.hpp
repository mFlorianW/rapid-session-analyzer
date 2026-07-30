// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_LAP_HPP
#define RAPIDSESSIONANALYZER_COMMON_LAP_HPP

#include <Common/GnssPosition.hpp>
#include <QTime>
#include <QVector>

namespace RapidSessionAnalyzer::Common
{

struct Lap
{
    QVector<QTime> sectors;
    QVector<GnssPosition> logPoints;

    [[nodiscard]] QTime laptime() const noexcept;

    bool operator==(Lap const& other) const noexcept = default;
    bool operator!=(Lap const& other) const noexcept = default;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_LAP_HPP
