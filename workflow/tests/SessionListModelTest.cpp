// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/SessionListModel.hpp>
#include <Workflow/FilesystemStorage.hpp>
#include <QTemporaryDir>
#include <QFile>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>

using namespace RapidSessionAnalyzer;

class SessionListModelTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void showsStoredSessionInfos()
    {
        QTemporaryDir tmp;
        QVERIFY2(tmp.isValid(), "Expected writable temp dir");

        Workflow::FilesystemStorage storage{QDir{tmp.path()}};
        QVERIFY(storage.store(TestHelper::oscherslebenSessionId(), TestHelper::oscherslebenSession()).has_value());

        auto storagePtr = std::make_shared<Workflow::FilesystemStorage>(QDir{tmp.path()});
        Workflow::SessionListModel model{storagePtr};

        QCOMPARE(model.rowCount(), 1);
        QCOMPARE(model.data(model.index(0,0), Workflow::SessionListModel::IdRole).toString(), TestHelper::oscherslebenSessionId());
    }
};

QTEST_MAIN(SessionListModelTest)
#include "SessionListModelTest.moc"
