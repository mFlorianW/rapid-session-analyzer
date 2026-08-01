// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_HTTPDEVICESESSIONMANAGEMENT_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_HTTPDEVICESESSIONMANAGEMENT_HPP

#include <Workflow/IDeviceSessionManagement.hpp>
#include <QNetworkAccessManager>
#include <QScopedPointer>
#include <QUrl>

namespace RapidSessionAnalyzer::Workflow
{

class HttpDeviceSessionManagement final : public IDeviceSessionManagement
{
public:
    explicit HttpDeviceSessionManagement(QUrl baseUrl, int requestTimeoutMs = 5000);
    HttpDeviceSessionManagement(QUrl baseUrl, QNetworkAccessManager* networkAccessManager, int requestTimeoutMs = 5000);

    [[nodiscard]] std::expected<QVector<Common::SessionInfo>, QString> getSessionInfos() const override;
    [[nodiscard]] std::expected<Common::Session, QString> load(QStringView sessionId) const override;

private:
    QUrl mBaseUrl;
    QNetworkAccessManager* mNetworkAccessManager{nullptr};
    QScopedPointer<QNetworkAccessManager> mOwnedNetworkAccessManager;
    int mRequestTimeoutMs{5000};
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_HTTPDEVICESESSIONMANAGEMENT_HPP
