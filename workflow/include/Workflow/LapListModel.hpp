// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RAPIDSESSIONANALYZER_WORKFLOW_LAPLISTMODEL_HPP
#define RAPIDSESSIONANALYZER_WORKFLOW_LAPLISTMODEL_HPP

#include <QAbstractListModel>
#include <Workflow/SessionAnalyzer.hpp>
#include <QVector>

namespace RapidSessionAnalyzer::Workflow
{

class LapListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        IdRole = Qt::UserRole + 1,
        LaptimeRole,
        SectorsRole,
    };

    explicit LapListModel(QObject* parent = nullptr);

    void setLaps(QVector<LapOverview> const& laps);

    int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<LapOverview> mLaps;
};

} // namespace RapidSessionAnalyzer::Workflow

#endif // RAPIDSESSIONANALYZER_WORKFLOW_LAPLISTMODEL_HPP
