// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_SESSIONLISTMODEL_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_SESSIONLISTMODEL_HPP

#include <QAbstractListModel>
#include <Common/SessionInfo.hpp>
#include <QVector>
#include <memory>

namespace RapidSessionAnalyzer::Workflow
{

class ISessionStorage;

class SessionListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole + 1,
        DateRole,
        TrackNameRole,
        LapsRole,
    };

    explicit SessionListModel(std::shared_ptr<ISessionStorage> storage, QObject* parent = nullptr);

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    [[nodiscard]] QVector<Common::SessionInfo> sessionInfos() const;

private:
    QVector<Common::SessionInfo> mSessionInfos;
    std::shared_ptr<ISessionStorage> mStorage;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_SESSIONLISTMODEL_HPP
