// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/SessionListModel.hpp>
#include <Workflow/ISessionStorage.hpp>

namespace RapidSessionAnalyzer::Workflow
{

SessionListModel::SessionListModel(std::shared_ptr<ISessionStorage> storage, QObject* parent)
    : QAbstractListModel(parent)
    , mStorage(std::move(storage))
{
    if (mStorage) {
        auto infos = mStorage->getSessionInfos();
        if (infos) {
            mSessionInfos = *infos;
        }
    }
}

int SessionListModel::rowCount(QModelIndex const& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return mSessionInfos.size();
}

QVariant SessionListModel::data(QModelIndex const& index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    const int row = index.row();
    if (row < 0 || row >= mSessionInfos.size()) {
        return {};
    }

    const auto& info = mSessionInfos.at(row);
    switch (role) {
    case IdRole:
        return info.id;
    case DateRole:
        return info.date.toString(Qt::ISODateWithMs);
    case TrackNameRole:
        return info.trackName;
    case LapsRole:
        return static_cast<int>(info.laps);
    case Qt::DisplayRole:
        return info.trackName;
    default:
        return {};
    }
}

QHash<int, QByteArray> SessionListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[DateRole] = "date";
    roles[TrackNameRole] = "trackName";
    roles[LapsRole] = "laps";
    return roles;
}

QVector<Common::SessionInfo> SessionListModel::sessionInfos() const
{
    return mSessionInfos;
}

} // namespace RapidSessionAnalyzer::Workflow
