// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Lap.hpp>

namespace RapidSessionAnalyzer::Common
{

QTime Lap::laptime() const noexcept
{
    auto totalMilliseconds = 0;
    for (QTime const& sector : sectors) {
        totalMilliseconds += QTime{0, 0}.msecsTo(sector);
    }

    return QTime{0, 0}.addMSecs(totalMilliseconds);
}

} // namespace RapidSessionAnalyzer::Common
