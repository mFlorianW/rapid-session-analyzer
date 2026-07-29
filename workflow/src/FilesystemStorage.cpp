// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/FilesystemStorage.hpp>

#include <Common/Json.hpp>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>
#include <algorithm>

namespace RapidSessionAnalyzer::Workflow
{
namespace
{

std::expected<void, QString> ensureDirectoryExists(QDir const& directory)
{
    if (directory.exists()) {
        return {};
    }

    if (QDir{}.mkpath(directory.absolutePath())) {
        return {};
    }

    return std::unexpected(QStringLiteral("Failed to create session library directory at '%1'.")
                               .arg(directory.absolutePath()));
}

std::expected<void, QString> writeFile(QString const& filePath, QByteArray const& contents)
{
    QFile file{filePath};
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        return std::unexpected(QStringLiteral("Failed to open '%1' for writing: %2")
                                   .arg(filePath, file.errorString()));
    }

    if (file.write(contents) != contents.size()) {
        return std::unexpected(QStringLiteral("Failed to write complete session data to '%1': %2")
                                   .arg(filePath, file.errorString()));
    }

    return {};
}

} // namespace

FilesystemStorage::FilesystemStorage(QDir sessionLibraryDirectory)
    : mSessionLibraryDirectory(std::move(sessionLibraryDirectory))
{
}

std::expected<QVector<Common::SessionInfo>, QString> FilesystemStorage::getSessionInfos() const
{
    auto directoryReady = ensureDirectoryExists(mSessionLibraryDirectory);
    if (!directoryReady) {
        return std::unexpected(directoryReady.error());
    }

    QVector<Common::SessionInfo> infos;
    QFileInfoList const files = mSessionLibraryDirectory.entryInfoList(
        {QStringLiteral("*.json")},
        QDir::Files | QDir::Readable,
        QDir::Name);

    infos.reserve(files.size());
    for (QFileInfo const& fileInfo : files) {
        auto loadedSession = load(fileInfo.completeBaseName());
        if (!loadedSession) {
            return std::unexpected(loadedSession.error());
        }

        infos.append(Common::makeSessionInfo(fileInfo.completeBaseName(), *loadedSession));
    }

    std::ranges::sort(infos, [](Common::SessionInfo const& left, Common::SessionInfo const& right) {
        return left.id < right.id;
    });

    return infos;
}

std::expected<Common::Session, QString> FilesystemStorage::load(QStringView sessionId) const
{
    auto filePath = sessionFilePath(sessionId);
    if (!filePath) {
        return std::unexpected(filePath.error());
    }

    QFile file{*filePath};
    if (!file.open(QIODevice::ReadOnly)) {
        return std::unexpected(QStringLiteral("Failed to open '%1' for reading: %2")
                                   .arg(*filePath, file.errorString()));
    }

    return Common::sessionFromJson(file.readAll());
}

std::expected<void, QString> FilesystemStorage::store(QStringView sessionId, Common::Session const& session) const
{
    auto directoryReady = ensureDirectoryExists(mSessionLibraryDirectory);
    if (!directoryReady) {
        return std::unexpected(directoryReady.error());
    }

    auto filePath = sessionFilePath(sessionId);
    if (!filePath) {
        return std::unexpected(filePath.error());
    }

    return writeFile(*filePath, Common::toJson(session));
}

std::expected<QString, QString> FilesystemStorage::sessionFilePath(QStringView sessionId) const
{
    static QRegularExpression const allowedIdPattern{QStringLiteral("^[A-Za-z0-9._-]+$")};

    QString const id = sessionId.toString();
    if (id.isEmpty()) {
        return std::unexpected(QStringLiteral("Session id must not be empty."));
    }

    if (!allowedIdPattern.match(id).hasMatch()) {
        return std::unexpected(QStringLiteral("Session id '%1' contains unsupported characters.").arg(id));
    }

    return mSessionLibraryDirectory.filePath(QStringLiteral("%1.json").arg(id));
}

} // namespace RapidSessionAnalyzer::Workflow
