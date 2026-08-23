/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_SAMPLER_H
#define FIELDLAB_FIELD_GRAPH_SAMPLER_H

#include <QString>
#include <QVector>

#include "FieldGraph.h"

struct FieldScalarGrid
{
    int width {0};
    int height {0};
    QVector<double> values;
    double minimum {0.0};
    double maximum {0.0};

    double valueAt(int x, int y) const
    {
        return values.at((y * width) + x);
    }
};

struct FieldGraphSamplingResult
{
    bool ok {false};
    FieldScalarGrid grid;
    QString error;
};

class FieldGraphSampler
{
public:
    FieldGraphSamplingResult sampleScalar(
        const FieldGraph &graph,
        int outputNodeId,
        int width,
        int height) const;
};

#endif
