// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/LapListModel.hpp>
#include <QVariantMap>

namespace RapidSessionAnalyzer::Workflow
{

LapListModel::LapListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void LapListModel::setLaps(QVector<LapOverview> const& laps)
{
    beginResetModel();
    mLaps = laps;
    endResetModel();
}

int LapListModel::rowCount(QModelIndex const& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return mLaps.size();
}

QVariant LapListModel::data(QModelIndex const& index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    int row = index.row();
    if (row < 0 || row >= mLaps.size()) {
        return {};
    }

    const auto& lap = mLaps.at(row);
    switch (role) {
    case IdRole:
        return lap.id;
    case LaptimeRole:
        return lap.laptime.toString(Qt::ISODateWithMs);
    case SectorsRole: {
        QVariantList list;
        for (auto const& s : lap.sectors) {
            list.append(s.toString());
        }
        return list;
    }
    case Qt::DisplayRole:
        return lap.laptime.toString();
    default:
        return {};
    }
}

QHash<int, QByteArray> LapListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[LaptimeRole] = "laptime";
    roles[SectorsRole] = "sectors";
    return roles;
}

} // namespace RapidSessionAnalyzer::Workflow
