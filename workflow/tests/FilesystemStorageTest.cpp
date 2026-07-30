// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Json.hpp>
#include <QFile>
#include <QTemporaryDir>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>
#include <Workflow/FilesystemStorage.hpp>

using namespace RapidSessionAnalyzer;

class FilesystemStorageTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void storeWritesCompactSessionJsonAndLoadReadsItBack()
    {
        QTemporaryDir temporaryDir;
        QVERIFY2(temporaryDir.isValid(), "Expected a writable temporary directory.");

        Workflow::FilesystemStorage storage{QDir{temporaryDir.path()}};

        auto storeResult = storage.store(TestHelper::oscherslebenSessionInfo().id, TestHelper::oscherslebenSession());
        QVERIFY(storeResult.has_value());

        QFile file{temporaryDir.filePath(QStringLiteral("%1.json").arg(TestHelper::oscherslebenSessionInfo().id))};
        QVERIFY(file.open(QIODevice::ReadOnly));
        QCOMPARE(file.readAll(), Common::toJson(TestHelper::oscherslebenSession()));

        auto loaded = storage.load(TestHelper::oscherslebenSessionInfo().id);
        QVERIFY(loaded.has_value());
        QCOMPARE(*loaded, TestHelper::oscherslebenSession());
    }

    void getSessionInfosReflectsStoredSessions()
    {
        QTemporaryDir temporaryDir;
        QVERIFY2(temporaryDir.isValid(), "Expected a writable temporary directory.");

        Workflow::FilesystemStorage storage{QDir{temporaryDir.path()}};
        QVERIFY(storage.store(TestHelper::oscherslebenSessionInfo().id, TestHelper::oscherslebenSession()).has_value());

        auto infos = storage.getSessionInfos();

        QVERIFY(infos.has_value());
        QCOMPARE(infos->size(), 1);
        QCOMPARE(infos->front(), TestHelper::oscherslebenSessionInfo());
    }
};

QTEST_MAIN(FilesystemStorageTest)
#include "FilesystemStorageTest.moc"
