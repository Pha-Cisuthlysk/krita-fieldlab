/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_DATA_TYPES_H
#define FIELDLAB_FIELD_DATA_TYPES_H

#include <QString>
#include <QVector>

enum class FieldDataKind {
    ScalarField2D,
    VectorField2D,
    RasterSource,
    PointSet,
    PathSet
};

struct FieldDomain2D {
    int width{0};
    int height{0};
    double minimumX{0.0};
    double minimumY{0.0};
    double maximumX{1.0};
    double maximumY{1.0};

    bool isValid() const;
    qint64 sampleCount() const;
};

struct FieldVector2D {
    double x{0.0};
    double y{0.0};
};

struct ScalarField2D {
    FieldDomain2D domain;
    QVector<double> samples;

    bool isConsistent() const;
};

struct VectorField2D {
    FieldDomain2D domain;
    QVector<FieldVector2D> samples;

    bool isConsistent() const;
};

struct RasterSource {
    // The host resolves this semantic identifier to raster data through an adapter.
    QString sourceId;
    QString channelId;

    bool isValid() const;
};

struct FieldPoint2D {
    double x{0.0};
    double y{0.0};
    double weight{1.0};
};

struct PointSet {
    QVector<FieldPoint2D> points;
};

struct FieldPath2D {
    QVector<FieldPoint2D> points;
    bool closed{false};
};

struct PathSet {
    QVector<FieldPath2D> paths;
};

const QVector<FieldDataKind> &fieldCoreDataKinds();
QString fieldDataKindId(FieldDataKind kind);

#endif
