// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Json.hpp>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QtGlobal>
#include <algorithm>

namespace RapidSessionAnalyzer::Common
{
namespace
{

constexpr auto DATE_FORMAT = "dd.MM.yyyy";
constexpr auto TIME_FORMAT = "HH:mm:ss.zzz";
constexpr auto DATETIME_FORMAT = "yyyy-MM-ddTHH:mm:ss.zzz";

template <typename T>
using ParseResult = std::expected<T, QString>;

ParseResult<QJsonObject> parseJsonObject(QByteArray const& json)
{
    QJsonParseError error;
    QJsonDocument const document = QJsonDocument::fromJson(json, &error);
    if (error.error != QJsonParseError::NoError) {
        return std::unexpected(QStringLiteral("Failed to parse JSON: %1").arg(error.errorString()));
    }

    if (!document.isObject()) {
        return std::unexpected(QStringLiteral("Expected a top-level JSON object."));
    }

    return document.object();
}

ParseResult<QString> requiredString(QJsonObject const& object, QStringView key)
{
    QJsonValue const value = object.value(key);
    if (!value.isString()) {
        return std::unexpected(QStringLiteral("Expected '%1' to be a string.").arg(key));
    }

    return value.toString();
}

ParseResult<double> requiredDouble(QJsonObject const& object, QStringView key)
{
    QJsonValue const value = object.value(key);
    if (!value.isDouble()) {
        return std::unexpected(QStringLiteral("Expected '%1' to be a number.").arg(key));
    }

    return value.toDouble();
}

ParseResult<QJsonArray> requiredArray(QJsonObject const& object, QStringView key)
{
    QJsonValue const value = object.value(key);
    if (!value.isArray()) {
        return std::unexpected(QStringLiteral("Expected '%1' to be an array.").arg(key));
    }

    return value.toArray();
}

ParseResult<QJsonObject> requiredObject(QJsonObject const& object, QStringView key)
{
    QJsonValue const value = object.value(key);
    if (!value.isObject()) {
        return std::unexpected(QStringLiteral("Expected '%1' to be an object.").arg(key));
    }

    return value.toObject();
}

ParseResult<QTime> parseTime(QString const& value, QStringView key)
{
    QTime const time = QTime::fromString(value, TIME_FORMAT);
    if (!time.isValid()) {
        return std::unexpected(QStringLiteral("Expected '%1' to use the %2 format.").arg(key, TIME_FORMAT));
    }

    return time;
}

ParseResult<QDate> parseDate(QString const& value, QStringView key)
{
    QDate const date = QDate::fromString(value, DATE_FORMAT);
    if (!date.isValid()) {
        return std::unexpected(QStringLiteral("Expected '%1' to use the %2 format.").arg(key, DATE_FORMAT));
    }

    return date;
}

ParseResult<QDateTime> parseDateTime(QString const& value, QStringView key)
{
    QDateTime dateTime = QDateTime::fromString(value, DATETIME_FORMAT);
    if (!dateTime.isValid()) {
        dateTime = QDateTime::fromString(value, Qt::ISODateWithMs);
    }
    if (!dateTime.isValid()) {
        dateTime = QDateTime::fromString(value, Qt::ISODate);
    }
    if (!dateTime.isValid()) {
        return std::unexpected(QStringLiteral("Expected '%1' to be an ISO datetime string.").arg(key));
    }

    return dateTime;
}

QByteArray asCompactJson(QJsonObject const& object)
{
    return QJsonDocument{object}.toJson(QJsonDocument::Compact);
}

QJsonObject toJsonObject(Position const& position)
{
    return QJsonObject{
        {QStringLiteral("latitude"), position.latitude},
        {QStringLiteral("longitude"), position.longitude},
    };
}

ParseResult<Position> positionFromJsonObject(QJsonObject const& object)
{
    Position position;
    auto latitude = requiredDouble(object, u"latitude");
    if (!latitude) {
        return std::unexpected(latitude.error());
    }

    auto longitude = requiredDouble(object, u"longitude");
    if (!longitude) {
        return std::unexpected(longitude.error());
    }

    position.latitude = *latitude;
    position.longitude = *longitude;
    return position;
}

QJsonObject toJsonObject(GnssPosition const& position)
{
    return QJsonObject{
        {QStringLiteral("latitude"), position.latitude},
        {QStringLiteral("longitude"), position.longitude},
        {QStringLiteral("velocity"), position.velocity},
        {QStringLiteral("time"), position.time.toString(TIME_FORMAT)},
        {QStringLiteral("date"), position.date.toString(DATE_FORMAT)},
    };
}

ParseResult<GnssPosition> gnssPositionFromJsonObject(QJsonObject const& object)
{
    GnssPosition position;

    auto latitude = requiredDouble(object, u"latitude");
    if (!latitude) {
        return std::unexpected(latitude.error());
    }

    auto longitude = requiredDouble(object, u"longitude");
    if (!longitude) {
        return std::unexpected(longitude.error());
    }

    auto velocity = requiredDouble(object, u"velocity");
    if (!velocity) {
        return std::unexpected(velocity.error());
    }

    auto timeString = requiredString(object, u"time");
    if (!timeString) {
        return std::unexpected(timeString.error());
    }

    auto dateString = requiredString(object, u"date");
    if (!dateString) {
        return std::unexpected(dateString.error());
    }

    auto time = parseTime(*timeString, u"time");
    if (!time) {
        return std::unexpected(time.error());
    }

    auto date = parseDate(*dateString, u"date");
    if (!date) {
        return std::unexpected(date.error());
    }

    position.latitude = *latitude;
    position.longitude = *longitude;
    position.velocity = *velocity;
    position.time = *time;
    position.date = *date;
    return position;
}

QJsonObject toJsonObject(Lap const& lap)
{
    QJsonArray sectorValues;
    for (QTime const& sector : lap.sectors) {
        sectorValues.append(sector.toString(TIME_FORMAT));
    }

    QJsonArray logPointValues;
    for (GnssPosition const& logPoint : lap.logPoints) {
        logPointValues.append(toJsonObject(logPoint));
    }

    return QJsonObject{
        {QStringLiteral("sectors"), sectorValues},
        {QStringLiteral("log_points"), logPointValues},
    };
}

ParseResult<Lap> lapFromJsonObject(QJsonObject const& object)
{
    Lap lap;

    auto sectors = requiredArray(object, u"sectors");
    if (!sectors) {
        return std::unexpected(sectors.error());
    }

    for (QJsonValue const& sectorValue : *sectors) {
        if (!sectorValue.isString()) {
            return std::unexpected(QStringLiteral("Expected lap sector values to be strings."));
        }

        auto time = parseTime(sectorValue.toString(), u"sectors");
        if (!time) {
            return std::unexpected(time.error());
        }

        lap.sectors.append(*time);
    }

    auto logPoints = requiredArray(object, u"log_points");
    if (!logPoints) {
        return std::unexpected(logPoints.error());
    }

    for (QJsonValue const& logPointValue : *logPoints) {
        if (!logPointValue.isObject()) {
            return std::unexpected(QStringLiteral("Expected lap log_points entries to be objects."));
        }

        auto logPoint = gnssPositionFromJsonObject(logPointValue.toObject());
        if (!logPoint) {
            return std::unexpected(logPoint.error());
        }

        lap.logPoints.append(*logPoint);
    }

    return lap;
}

QJsonObject toJsonObject(Track const& track)
{
    QJsonObject object{
        {QStringLiteral("name"), track.name},
        {QStringLiteral("startline"), toJsonObject(track.startline)},
    };

    if (track.finishline.has_value()) {
        object.insert(QStringLiteral("finishline"), toJsonObject(*track.finishline));
    } else {
        object.insert(QStringLiteral("finishline"), QJsonValue::Null);
    }

    QJsonArray sectors;
    for (Position const& sector : track.sectors) {
        sectors.append(toJsonObject(sector));
    }
    object.insert(QStringLiteral("sectors"), sectors);

    return object;
}

ParseResult<Track> trackFromJsonObject(QJsonObject const& object)
{
    Track track;

    auto name = requiredString(object, u"name");
    if (!name) {
        return std::unexpected(name.error());
    }

    auto startlineObject = requiredObject(object, u"startline");
    if (!startlineObject) {
        return std::unexpected(startlineObject.error());
    }

    auto startline = positionFromJsonObject(*startlineObject);
    if (!startline) {
        return std::unexpected(startline.error());
    }

    QJsonValue const finishlineValue = object.value(QStringLiteral("finishline"));
    std::optional<Position> finishline;
    if (!finishlineValue.isUndefined() && !finishlineValue.isNull()) {
        if (!finishlineValue.isObject()) {
            return std::unexpected(QStringLiteral("Expected 'finishline' to be an object or null."));
        }

        auto parsedFinishline = positionFromJsonObject(finishlineValue.toObject());
        if (!parsedFinishline) {
            return std::unexpected(parsedFinishline.error());
        }
        finishline = *parsedFinishline;
    }

    auto sectorsArray = requiredArray(object, u"sectors");
    if (!sectorsArray) {
        return std::unexpected(sectorsArray.error());
    }

    QVector<Position> sectors;
    sectors.reserve(sectorsArray->size());
    for (QJsonValue const& sectorValue : *sectorsArray) {
        if (!sectorValue.isObject()) {
            return std::unexpected(QStringLiteral("Expected track sectors to contain objects."));
        }

        auto sector = positionFromJsonObject(sectorValue.toObject());
        if (!sector) {
            return std::unexpected(sector.error());
        }

        sectors.append(*sector);
    }

    track.name = *name;
    track.startline = *startline;
    track.finishline = finishline;
    track.sectors = sectors;
    return track;
}

QJsonObject toJsonObject(Session const& session)
{
    QJsonArray laps;
    for (Lap const& lap : session.getLaps()) {
        laps.append(toJsonObject(lap));
    }

    return QJsonObject{
        {QStringLiteral("id"), static_cast<qint64>(session.getId())},
        {QStringLiteral("date"), session.getDate().toString(DATE_FORMAT)},
        {QStringLiteral("time"), session.getTime().toString(TIME_FORMAT)},
        {QStringLiteral("track"), toJsonObject(session.getTrack())},
        {QStringLiteral("laps"), laps},
    };
}

ParseResult<Session> sessionFromJsonObject(QJsonObject const& object)
{
    Session session;

    QJsonValue const idValue = object.value(QStringLiteral("id"));
    if (!idValue.isDouble()) {
        return std::unexpected(QStringLiteral("Expected 'id' to be a number."));
    }

    auto dateString = requiredString(object, u"date");
    if (!dateString) {
        return std::unexpected(dateString.error());
    }

    auto timeString = requiredString(object, u"time");
    if (!timeString) {
        return std::unexpected(timeString.error());
    }

    auto date = parseDate(*dateString, u"date");
    if (!date) {
        return std::unexpected(date.error());
    }

    auto time = parseTime(*timeString, u"time");
    if (!time) {
        return std::unexpected(time.error());
    }

    auto trackObject = requiredObject(object, u"track");
    if (!trackObject) {
        return std::unexpected(trackObject.error());
    }

    auto track = trackFromJsonObject(*trackObject);
    if (!track) {
        return std::unexpected(track.error());
    }

    auto lapsArray = requiredArray(object, u"laps");
    if (!lapsArray) {
        return std::unexpected(lapsArray.error());
    }

    QVector<Lap> laps;
    laps.reserve(lapsArray->size());
    for (QJsonValue const& lapValue : *lapsArray) {
        if (!lapValue.isObject()) {
            return std::unexpected(QStringLiteral("Expected session laps to contain objects."));
        }

        auto lap = lapFromJsonObject(lapValue.toObject());
        if (!lap) {
            return std::unexpected(lap.error());
        }

        laps.append(*lap);
    }

    session.setId(static_cast<quint64>(idValue.toInteger()));
    session.setDate(*date);
    session.setTime(*time);
    session.setTrack(*track);
    session.setLaps(laps);
    return session;
}

QJsonObject toJsonObject(SessionInfo const& sessionInfo)
{
    return QJsonObject{
        {QStringLiteral("id"), sessionInfo.id},
        {QStringLiteral("date"), sessionInfo.date.toString(DATETIME_FORMAT)},
        {QStringLiteral("track_name"), sessionInfo.trackName},
        {QStringLiteral("laps"), static_cast<qint64>(sessionInfo.laps)},
    };
}

ParseResult<SessionInfo> sessionInfoFromJsonObject(QJsonObject const& object)
{
    SessionInfo info;

    auto id = requiredString(object, u"id");
    if (!id) {
        return std::unexpected(id.error());
    }

    auto dateString = requiredString(object, u"date");
    if (!dateString) {
        return std::unexpected(dateString.error());
    }

    auto trackName = requiredString(object, u"track_name");
    if (!trackName) {
        return std::unexpected(trackName.error());
    }

    QJsonValue const lapsValue = object.value(QStringLiteral("laps"));
    if (!lapsValue.isDouble()) {
        return std::unexpected(QStringLiteral("Expected 'laps' to be a number."));
    }

    auto date = parseDateTime(*dateString, u"date");
    if (!date) {
        return std::unexpected(date.error());
    }

    info.id = *id;
    info.date = *date;
    info.trackName = *trackName;
    info.laps = static_cast<quint32>(lapsValue.toInteger());
    return info;
}

} // namespace

QByteArray toJson(Position const& position)
{
    return asCompactJson(toJsonObject(position));
}

std::expected<Position, QString> positionFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return positionFromJsonObject(*object);
}

QByteArray toJson(GnssPosition const& position)
{
    return asCompactJson(toJsonObject(position));
}

std::expected<GnssPosition, QString> gnssPositionFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return gnssPositionFromJsonObject(*object);
}

QByteArray toJson(Lap const& lap)
{
    return asCompactJson(toJsonObject(lap));
}

std::expected<Lap, QString> lapFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return lapFromJsonObject(*object);
}

QByteArray toJson(Track const& track)
{
    return asCompactJson(toJsonObject(track));
}

std::expected<Track, QString> trackFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return trackFromJsonObject(*object);
}

QByteArray toJson(Session const& session)
{
    return asCompactJson(toJsonObject(session));
}

std::expected<Session, QString> sessionFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return sessionFromJsonObject(*object);
}

QByteArray toJson(SessionInfo const& sessionInfo)
{
    return asCompactJson(toJsonObject(sessionInfo));
}

std::expected<SessionInfo, QString> sessionInfoFromJson(QByteArray const& json)
{
    auto object = parseJsonObject(json);
    if (!object) {
        return std::unexpected(object.error());
    }

    return sessionInfoFromJsonObject(*object);
}

SessionInfo makeSessionInfo(QString id, Session const& session) noexcept
{
    return SessionInfo{
        .id = std::move(id),
        .date = QDateTime{session.getDate(), session.getTime()},
        .trackName = session.getTrack().name,
        .laps = static_cast<quint32>(session.getLaps().size()),
    };
}

} // namespace RapidSessionAnalyzer::Common
