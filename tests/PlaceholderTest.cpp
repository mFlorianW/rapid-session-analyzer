// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <QTest>

// Placeholder test used to verify the CMake configure/build/test pipeline is
// correctly wired end-to-end. Real test suites are added starting with the
// common/ domain model.
class PlaceholderTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void buildPipelineIsWired()
    {
        QVERIFY(true);
    }
};

QTEST_MAIN(PlaceholderTest)
#include "PlaceholderTest.moc"
