/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include <QSet>
#include <QTest>

#include <algorithm>
#include <cmath>
#include <vector>

#include <FastNoise/FastNoise.h>
#include <FastNoise/Metadata.h>

class FastNoise2Probe : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testMetadataDiscovery();
    void testBatchGeneration();
};

void FastNoise2Probe::testMetadataDiscovery()
{
    const auto &metadata = FastNoise::Metadata::GetAll();

    QVERIFY(metadata.size() > 0);

    QSet<QString> names;

    for (size_t i = 0; i < metadata.size(); ++i) {
        const FastNoise::Metadata *node = metadata[i];

        QVERIFY(node);
        QCOMPARE(size_t(node->id), i);
        QVERIFY(node->name);

        const QString name = QString::fromUtf8(node->name);
        QVERIFY(!name.isEmpty());
        QVERIFY(!names.contains(name));
        names.insert(name);

        QVERIFY(!FastNoise::Metadata::FormatMetadataNodeName(node).empty());

        for (const FastNoise::Metadata::MemberVariable &member :
             node->memberVariables) {
            QVERIFY(member.name);
            QVERIFY(*member.name);
        }

        for (const FastNoise::Metadata::MemberNodeLookup &member :
             node->memberNodeLookups) {
            QVERIFY(member.name);
            QVERIFY(*member.name);
        }

        for (const FastNoise::Metadata::MemberHybrid &member :
             node->memberHybrids) {
            QVERIFY(member.name);
            QVERIFY(*member.name);
        }

        const FastNoise::SmartNode<> instance = node->CreateNode();
        QVERIFY(instance);
    }

    qInfo() << "FastNoise2 metadata nodes discovered:" << metadata.size();
}

void FastNoise2Probe::testBatchGeneration()
{
    const auto &metadata = FastNoise::Metadata::GetAll();
    const FastNoise::Metadata *simplexMetadata = nullptr;

    // A single known node anchors the runtime smoke test; discovery remains
    // metadata-driven and does not create a production catalog.
    for (const FastNoise::Metadata *node : metadata) {
        if (QString::fromUtf8(node->name) == QStringLiteral("Simplex")) {
            simplexMetadata = node;
            break;
        }
    }

    QVERIFY(simplexMetadata);

    const FastNoise::SmartNode<> generator =
        simplexMetadata->CreateNode();
    QVERIFY(generator);

    constexpr int width = 32;
    constexpr int height = 16;
    std::vector<float> grid(size_t(width * height));
    std::vector<float> repeatedGrid(grid.size());

    const FastNoise::OutputMinMax gridRange =
        generator->GenUniformGrid2D(
            grid.data(),
            0.0f,
            0.0f,
            width,
            height,
            0.05f,
            0.05f,
            1337);
    const FastNoise::OutputMinMax repeatedRange =
        generator->GenUniformGrid2D(
            repeatedGrid.data(),
            0.0f,
            0.0f,
            width,
            height,
            0.05f,
            0.05f,
            1337);

    QVERIFY(std::all_of(
        grid.cbegin(),
        grid.cend(),
        [](float value) {
            return std::isfinite(value);
        }));
    QCOMPARE(grid, repeatedGrid);
    QCOMPARE(gridRange.min, repeatedRange.min);
    QCOMPARE(gridRange.max, repeatedRange.max);
    QVERIFY(gridRange.min < gridRange.max);

    const std::vector<float> xPositions {
        0.0f,
        0.25f,
        1.0f,
        2.0f
    };
    const std::vector<float> yPositions {
        0.0f,
        0.75f,
        -1.0f,
        3.0f
    };
    std::vector<float> positionValues(xPositions.size());

    const FastNoise::OutputMinMax positionRange =
        generator->GenPositionArray2D(
            positionValues.data(),
            int(positionValues.size()),
            xPositions.data(),
            yPositions.data(),
            0.0f,
            0.0f,
            1337);

    QVERIFY(std::all_of(
        positionValues.cbegin(),
        positionValues.cend(),
        [](float value) {
            return std::isfinite(value);
        }));
    QVERIFY(positionRange.min <= positionRange.max);

    qInfo() << "FastNoise2 active feature set:"
            << FastSIMD::GetFeatureSetString(
                   generator->GetActiveFeatureSet());
}

QTEST_GUILESS_MAIN(FastNoise2Probe)

#include "FastNoise2Probe.moc"
