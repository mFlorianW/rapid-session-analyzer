// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <Common/Json.hpp>
#include <QJsonDocument>
#include <QTest>
#include <TestHelper/SessionSamples.hpp>

using namespace RapidSessionAnalyzer;

namespace
{

void compareJsonDocuments(QByteArray const& actual, QByteArray const& expected)
{
    QCOMPARE(QJsonDocument::fromJson(actual), QJsonDocument::fromJson(expected));
}

} // namespace

class DomainModelJsonTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void positionRoundTripsJson()
    {
        Common::Position const position{.latitude = 52.0270889, .longitude = 11.2803483};

        auto deserialized = Common::positionFromJson(Common::toJson(position));

        QVERIFY(deserialized.has_value());
        QCOMPARE(*deserialized, position);
    }

    void gnssPositionRoundTripsJson()
    {
        Common::GnssPosition const position{
            .latitude = 52.0,
            .longitude = 11.0,
            .velocity = 100.0,
            .time = QTime{0, 0, 0, 0},
            .date = QDate{1970, 1, 1},
        };

        auto deserialized = Common::gnssPositionFromJson(Common::toJson(position));

        QVERIFY(deserialized.has_value());
        QCOMPARE(*deserialized, position);
    }

    void lapCalculatesAccumulatedLaptime()
    {
        Common::Lap const lap{
            .sectors = {QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}},
            .logPoints = {},
        };
        QTime const expectedLaptime{0, 1, 40, 576};

        QCOMPARE(lap.laptime(), expectedLaptime);
    }

    void trackRoundTripsJson()
    {
        Common::Track const track{
            .name = QStringLiteral("Oschersleben"),
            .startline = {.latitude = 52.0270889, .longitude = 11.2803483},
            .finishline = Common::Position{.latitude = 52.0270889, .longitude = 11.2803483},
            .sectors = {
                {.latitude = 52.0298205, .longitude = 11.2741851},
                {.latitude = 52.0299681, .longitude = 11.2772076},
            },
        };

        auto deserialized = Common::trackFromJson(Common::toJson(track));

        QVERIFY(deserialized.has_value());
        QCOMPARE(*deserialized, track);
    }

    void sessionDeserializesRapidRustySchema()
    {
        auto deserialized = Common::sessionFromJson(TestHelper::oscherslebenSessionJson());

        QVERIFY(deserialized.has_value());
        QCOMPARE(*deserialized, TestHelper::oscherslebenSession());
    }

    void sessionRoundTripsToEquivalentJson()
    {
        QByteArray const actual = Common::toJson(TestHelper::oscherslebenSession());

        compareJsonDocuments(actual, TestHelper::oscherslebenSessionJson());
    }

    void sessionInfoRoundTripsJson()
    {
        QByteArray const actual = Common::toJson(TestHelper::oscherslebenSessionInfo());

        auto deserialized = Common::sessionInfoFromJson(actual);

        compareJsonDocuments(actual, TestHelper::oscherslebenSessionInfoJson());
        QVERIFY(deserialized.has_value());
        QCOMPARE(*deserialized, TestHelper::oscherslebenSessionInfo());
    }
};

QTEST_MAIN(DomainModelJsonTest)
#include "DomainModelJsonTest.moc"
