// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_TESTHELPER_SESSIONSAMPLES_HPP
#define RAPIDSESSIONANALYZER_TESTHELPER_SESSIONSAMPLES_HPP

#include <Common/Session.hpp>
#include <Common/SessionInfo.hpp>
#include <QByteArray>
#include <QString>

namespace RapidSessionAnalyzer::TestHelper
{

[[nodiscard]] QString oscherslebenSessionId() noexcept;
[[nodiscard]] QByteArray oscherslebenSessionJson() noexcept;
[[nodiscard]] QByteArray oscherslebenSessionInfoJson() noexcept;
[[nodiscard]] Common::Session oscherslebenSession() noexcept;
[[nodiscard]] Common::SessionInfo oscherslebenSessionInfo() noexcept;

} // namespace RapidSessionAnalyzer::TestHelper

#endif // RAPIDSESSIONANALYZER_TESTHELPER_SESSIONSAMPLES_HPP
