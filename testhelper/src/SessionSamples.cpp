// SPDX-FileCopyrightText: 2026 All contributors
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include <TestHelper/SessionSamples.hpp>

namespace RapidSessionAnalyzer::TestHelper
{

QString oscherslebenSessionId() noexcept
{
    return QStringLiteral("oschersleben_01_01_1970_13_00_00_000");
}

QByteArray oscherslebenSessionJson() noexcept
{
    return R"json(
{
  "id": 0,
  "date": "01.01.1970",
  "time": "13:00:00.000",
  "track": {
    "name": "Oschersleben",
    "startline": {
      "latitude": 52.025833,
      "longitude": 11.279166
    },
    "finishline": {
      "latitude": 52.025833,
      "longitude": 11.279166
    },
    "sectors": [
      {
        "latitude": 52.025833,
        "longitude": 11.279166
      },
      {
        "latitude": 52.025833,
        "longitude": 11.279166
      }
    ]
  },
  "laps": [
    {
      "sectors": [
        "00:00:25.144",
        "00:00:25.144",
        "00:00:25.144",
        "00:00:25.144"
      ],
      "log_points": [
        {
          "velocity": 100.0,
          "longitude": 11.0,
          "latitude": 52.0,
          "time": "00:00:00.000",
          "date": "01.01.1970"
        },
        {
          "velocity": 100.0,
          "longitude": 11.0,
          "latitude": 52.0,
          "time": "00:00:00.000",
          "date": "01.01.1970"
        }
      ]
    }
  ]
}
)json";
}

QByteArray oscherslebenSessionInfoJson() noexcept
{
    return R"json(
{
  "id": "oschersleben_01_01_1970_13_00_00_000",
  "date": "1970-01-01T13:00:00.000",
  "track_name": "Oschersleben",
  "laps": 1
}
)json";
}

Common::Session oscherslebenSession() noexcept
{
    Common::Session session;
    session.setId(0);
    session.setDate(QDate{1970, 1, 1});
    session.setTime(QTime{13, 0, 0, 0});
    session.setTrack(Common::Track{
        .name = QStringLiteral("Oschersleben"),
        .startline = {.latitude = 52.025833, .longitude = 11.279166},
        .finishline = Common::Position{.latitude = 52.025833, .longitude = 11.279166},
        .sectors = {
            {.latitude = 52.025833, .longitude = 11.279166},
            {.latitude = 52.025833, .longitude = 11.279166},
        },
    });
    session.setLaps({
        Common::Lap{
            .sectors = {QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}, QTime{0, 0, 25, 144}},
            .logPoints = {
                Common::GnssPosition{
                    .latitude = 52.0,
                    .longitude = 11.0,
                    .velocity = 100.0,
                    .time = QTime{0, 0, 0, 0},
                    .date = QDate{1970, 1, 1},
                },
                Common::GnssPosition{
                    .latitude = 52.0,
                    .longitude = 11.0,
                    .velocity = 100.0,
                    .time = QTime{0, 0, 0, 0},
                    .date = QDate{1970, 1, 1},
                },
            },
        },
    });

    return session;
}

Common::SessionInfo oscherslebenSessionInfo() noexcept
{
    return Common::SessionInfo{
        .id = oscherslebenSessionId(),
        .date = QDateTime{QDate{1970, 1, 1}, QTime{13, 0, 0, 0}},
        .trackName = QStringLiteral("Oschersleben"),
        .laps = 1,
    };
}

} // namespace RapidSessionAnalyzer::TestHelper
