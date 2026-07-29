// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Session.hpp>

namespace RapidSessionAnalyzer::Common
{

Session::Session()
    : mData(new SessionData{})
{
}

Session::~Session() = default;
Session::Session(Session const& other) = default;
Session& Session::operator=(Session const& other) = default;
Session::Session(Session&& other) noexcept = default;
Session& Session::operator=(Session&& other) noexcept = default;

quint64 Session::getId() const noexcept
{
    return mData->id;
}

void Session::setId(quint64 id) noexcept
{
    mData->id = id;
}

QDate Session::getDate() const noexcept
{
    return mData->date;
}

void Session::setDate(QDate const& date) noexcept
{
    mData->date = date;
}

QTime Session::getTime() const noexcept
{
    return mData->time;
}

void Session::setTime(QTime const& time) noexcept
{
    mData->time = time;
}

Track Session::getTrack() const noexcept
{
    return mData->track;
}

void Session::setTrack(Track const& track) noexcept
{
    mData->track = track;
}

QVector<Lap> Session::getLaps() const noexcept
{
    return mData->laps;
}

void Session::setLaps(QVector<Lap> const& laps) noexcept
{
    mData->laps = laps;
}

} // namespace RapidSessionAnalyzer::Common
