// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Workflow/SessionAnalyzer.hpp>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>

using namespace RapidSessionAnalyzer;

class SessionAnalyzerTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void computesLapOverviews()
    {
        auto session = TestHelper::oscherslebenSession();
        auto overviews = Workflow::SessionAnalyzer::analyze(session);

        QVERIFY(overviews.size() == session.getLaps().size());
        QCOMPARE(overviews.front().laptime, session.getLaps().front().laptime());
        QCOMPARE(overviews.front().sectors, session.getLaps().front().sectors);
    }
};

QTEST_MAIN(SessionAnalyzerTest)
#include "SessionAnalyzerTest.moc"
