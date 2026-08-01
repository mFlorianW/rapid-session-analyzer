// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/SessionAnalyzer.hpp>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>

using namespace RapidSessionAnalyzer;

class SessionAnalyzerCompareTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void groupsLapsByTrackAcrossSessions()
    {
        auto sessionA = TestHelper::oscherslebenSession();
        auto sessionB = TestHelper::oscherslebenSession();

        QList<Common::Session> sessions{sessionA, sessionB};
        auto grouped = Workflow::SessionAnalyzer::compareByTrack(sessions);

        QVERIFY(grouped.contains(QStringLiteral("Oschersleben")));
        const auto& perTrack = grouped.value(QStringLiteral("Oschersleben"));
        // two sessions -> two entries
        QCOMPARE(perTrack.size(), 2);
        QCOMPARE(perTrack.at(0).size(), sessionA.getLaps().size());
        QCOMPARE(perTrack.at(1).size(), sessionB.getLaps().size());

        // check that lap data matches
        QCOMPARE(perTrack.at(0).front().laptime, sessionA.getLaps().front().laptime());
        QCOMPARE(perTrack.at(1).front().laptime, sessionB.getLaps().front().laptime());
    }
};

QTEST_MAIN(SessionAnalyzerCompareTest)
#include "SessionAnalyzerCompareTest.moc"
