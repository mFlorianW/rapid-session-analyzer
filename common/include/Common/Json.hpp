// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_JSON_HPP
#define RAPIDSESSIONANALYZER_COMMON_JSON_HPP

#include <Common/GnssPosition.hpp>
#include <Common/Lap.hpp>
#include <Common/Position.hpp>
#include <Common/Session.hpp>
#include <Common/SessionInfo.hpp>
#include <Common/Track.hpp>
#include <QByteArray>
#include <QString>
#include <expected>

namespace RapidSessionAnalyzer::Common
{

[[nodiscard]] QByteArray toJson(Position const& position);
[[nodiscard]] std::expected<Position, QString> positionFromJson(QByteArray const& json);

[[nodiscard]] QByteArray toJson(GnssPosition const& position);
[[nodiscard]] std::expected<GnssPosition, QString> gnssPositionFromJson(QByteArray const& json);

[[nodiscard]] QByteArray toJson(Lap const& lap);
[[nodiscard]] std::expected<Lap, QString> lapFromJson(QByteArray const& json);

[[nodiscard]] QByteArray toJson(Track const& track);
[[nodiscard]] std::expected<Track, QString> trackFromJson(QByteArray const& json);

[[nodiscard]] QByteArray toJson(Session const& session);
[[nodiscard]] std::expected<Session, QString> sessionFromJson(QByteArray const& json);

[[nodiscard]] QByteArray toJson(SessionInfo const& sessionInfo);
[[nodiscard]] std::expected<SessionInfo, QString> sessionInfoFromJson(QByteArray const& json);

[[nodiscard]] SessionInfo makeSessionInfo(QString id, Session const& session) noexcept;

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_JSON_HPP
