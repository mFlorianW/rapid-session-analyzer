// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_RAPIDLAPTIMER_LAPTIMERSESSIONBROWSER_HPP
#define RAPIDSESSIONANALYZER_RAPIDLAPTIMER_LAPTIMERSESSIONBROWSER_HPP

#include <QList>
#include <QObject>
#include <QQmlEngine>
#include <QVariantList>

namespace RapidSessionAnalyzer::RapidLaptimer
{

class LaptimerSessionBrowser : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString laptimerAddress READ laptimerAddress WRITE setLaptimerAddress NOTIFY laptimerAddressChanged FINAL)
    Q_PROPERTY(QVariantList availableSessions READ availableSessions NOTIFY availableSessionsChanged FINAL)
    Q_PROPERTY(QString statusMessage READ statusMessage NOTIFY statusMessageChanged FINAL)

public:
    explicit LaptimerSessionBrowser(QObject* parent = nullptr);

    [[nodiscard]] QString laptimerAddress() const;
    void setLaptimerAddress(QString laptimerAddress);

    [[nodiscard]] QString sessionLibraryPath() const;
    void setSessionLibraryPath(QString sessionLibraryPath);

    [[nodiscard]] QVariantList availableSessions() const;
    [[nodiscard]] QString statusMessage() const;

    Q_INVOKABLE void connectToLaptimer();
    Q_INVOKABLE void downloadSession(QString const& sessionId);

Q_SIGNALS:
    void laptimerAddressChanged();
    void availableSessionsChanged();
    void statusMessageChanged();

private:
    QString mLaptimerAddress;
    QString mSessionLibraryPath;
    QVariantList mAvailableSessions;
    QString mStatusMessage;
};

} // namespace RapidSessionAnalyzer::RapidLaptimer

#endif // RAPIDSESSIONANALYZER_RAPIDLAPTIMER_LAPTIMERSESSIONBROWSER_HPP
