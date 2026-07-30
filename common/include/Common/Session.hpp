// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_SESSION_HPP
#define RAPIDSESSIONANALYZER_COMMON_SESSION_HPP

#include <Common/Lap.hpp>
#include <Common/Track.hpp>
#include <QDate>
#include <QSharedDataPointer>
#include <QTime>
#include <QVector>
#include <QtTypes>

namespace RapidSessionAnalyzer::Common
{

struct SessionData : public QSharedData
{
    quint64 id{0};
    QDate date;
    QTime time;
    Track track;
    QVector<Lap> laps;

    bool operator==(SessionData const& other) const noexcept
    {
        return id == other.id && date == other.date && time == other.time && track == other.track && laps == other.laps;
    }

    bool operator!=(SessionData const& other) const noexcept
    {
        return !(*this == other);
    }
};

class Session
{
public:
    Session();
    ~Session();

    Session(Session const& other);
    Session& operator=(Session const& other);
    Session(Session&& other) noexcept;
    Session& operator=(Session&& other) noexcept;

    [[nodiscard]] quint64 getId() const noexcept;
    void setId(quint64 id) noexcept;

    [[nodiscard]] QDate getDate() const noexcept;
    void setDate(QDate const& date) noexcept;

    [[nodiscard]] QTime getTime() const noexcept;
    void setTime(QTime const& time) noexcept;

    [[nodiscard]] Track getTrack() const noexcept;
    void setTrack(Track const& track) noexcept;

    [[nodiscard]] QVector<Lap> getLaps() const noexcept;
    void setLaps(QVector<Lap> const& laps) noexcept;

    bool operator==(Session const& other) const noexcept
    {
        return *mData == *other.mData;
    }

    bool operator!=(Session const& other) const noexcept
    {
        return !(*this == other);
    }

private:
    QSharedDataPointer<SessionData> mData;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_SESSION_HPP
