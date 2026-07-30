// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_POSITION_HPP
#define RAPIDSESSIONANALYZER_COMMON_POSITION_HPP

namespace RapidSessionAnalyzer::Common
{

struct Position
{
    double latitude{0.0};
    double longitude{0.0};

    bool operator==(Position const& other) const noexcept = default;
    bool operator!=(Position const& other) const noexcept = default;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_POSITION_HPP
