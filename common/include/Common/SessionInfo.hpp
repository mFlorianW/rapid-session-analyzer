// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_COMMON_SESSIONINFO_HPP
#define RAPIDSESSIONANALYZER_COMMON_SESSIONINFO_HPP

#include <QDateTime>
#include <QObject>
#include <QString>
#include <QtTypes>

namespace RapidSessionAnalyzer::Common
{

struct SessionInfo
{
    Q_GADGET

    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QDateTime date MEMBER date)
    Q_PROPERTY(QString trackName MEMBER trackName)
    Q_PROPERTY(quint32 laps MEMBER laps)

public:
    QString id;
    QDateTime date;
    QString trackName;
    quint32 laps{0};

    bool operator==(SessionInfo const& other) const noexcept = default;
    bool operator!=(SessionInfo const& other) const noexcept = default;
};

} // namespace RapidSessionAnalyzer::Common

#endif // RAPIDSESSIONANALYZER_COMMON_SESSIONINFO_HPP
