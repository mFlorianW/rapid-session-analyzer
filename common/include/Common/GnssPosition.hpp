// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_GNSSPOSITION_HPP
#define RAPIDSESSIONANALYZER_COMMON_GNSSPOSITION_HPP

#include <QDate>
#include <QTime>

namespace RapidSessionAnalyzer::Common
{

struct GnssPosition
{
    double latitude{0.0};
    double longitude{0.0};
    double velocity{0.0};
    QTime time;
    QDate date;

    bool operator==(GnssPosition const& other) const noexcept = default;
    bool operator!=(GnssPosition const& other) const noexcept = default;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_GNSSPOSITION_HPP
