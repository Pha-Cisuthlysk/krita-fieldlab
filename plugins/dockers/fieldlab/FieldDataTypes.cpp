/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldDataTypes.h"

bool FieldDomain2D::isValid() const
{
    return width > 0 && height > 0 && maximumX > minimumX && maximumY > minimumY;
}

qint64 FieldDomain2D::sampleCount() const
{
    if (width <= 0 || height <= 0) {
        return 0;
    }

    return qint64(width) * qint64(height);
}

bool ScalarField2D::isConsistent() const
{
    return domain.isValid() && samples.size() == domain.sampleCount();
}

bool VectorField2D::isConsistent() const
{
    return domain.isValid() && samples.size() == domain.sampleCount();
}

bool RasterSource::isValid() const
{
    return !sourceId.trimmed().isEmpty();
}

const QVector<FieldDataKind> &fieldCoreDataKinds()
{
    static const QVector<FieldDataKind> kinds{FieldDataKind::ScalarField2D,
                                              FieldDataKind::VectorField2D,
                                              FieldDataKind::RasterSource,
                                              FieldDataKind::PointSet,
                                              FieldDataKind::PathSet};

    return kinds;
}

QString fieldDataKindId(FieldDataKind kind)
{
    switch (kind) {
    case FieldDataKind::ScalarField2D:
        return QStringLiteral("field.scalar2d");
    case FieldDataKind::VectorField2D:
        return QStringLiteral("field.vector2d");
    case FieldDataKind::RasterSource:
        return QStringLiteral("field.raster-source");
    case FieldDataKind::PointSet:
        return QStringLiteral("field.point-set");
    case FieldDataKind::PathSet:
        return QStringLiteral("field.path-set");
    }

    return QString();
}
