// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_FILESYSTEMSTORAGE_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_FILESYSTEMSTORAGE_HPP

#include <Workflow/ISessionStorage.hpp>
#include <QDir>

namespace RapidSessionAnalyzer::Workflow
{

class FilesystemStorage final : public ISessionStorage
{
public:
    explicit FilesystemStorage(QDir sessionLibraryDirectory);

    [[nodiscard]] std::expected<QVector<Common::SessionInfo>, QString> getSessionInfos() const override;
    [[nodiscard]] std::expected<Common::Session, QString> load(QStringView sessionId) const override;
    std::expected<void, QString> store(QStringView sessionId, Common::Session const& session) const override;

private:
    [[nodiscard]] std::expected<QString, QString> sessionFilePath(QStringView sessionId) const;

    QDir mSessionLibraryDirectory;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_FILESYSTEMSTORAGE_HPP
