// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_HTTPLAPTIMERSESSIONMANAGEMENT_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_HTTPLAPTIMERSESSIONMANAGEMENT_HPP

#include <Workflow/ILaptimerSessionManagement.hpp>
#include <QNetworkAccessManager>
#include <QScopedPointer>
#include <QUrl>

namespace RapidSessionAnalyzer::Workflow
{

class HttpLaptimerSessionManagement final : public ILaptimerSessionManagement
{
public:
    explicit HttpLaptimerSessionManagement(QUrl baseUrl, int requestTimeoutMs = 5000);
    HttpLaptimerSessionManagement(QUrl baseUrl, QNetworkAccessManager* networkAccessManager, int requestTimeoutMs = 5000);

    [[nodiscard]] std::expected<QVector<Common::SessionInfo>, QString> getSessionInfos() const override;
    [[nodiscard]] std::expected<Common::Session, QString> load(QStringView sessionId) const override;

private:
    QUrl mBaseUrl;
    QNetworkAccessManager* mNetworkAccessManager{nullptr};
    QScopedPointer<QNetworkAccessManager> mOwnedNetworkAccessManager;
    int mRequestTimeoutMs{5000};
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_HTTPLAPTIMERSESSIONMANAGEMENT_HPP
