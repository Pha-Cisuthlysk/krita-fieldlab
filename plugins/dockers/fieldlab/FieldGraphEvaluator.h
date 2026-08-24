/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_EVALUATOR_H
#define FIELDLAB_FIELD_GRAPH_EVALUATOR_H

#include <QHash>
#include <QSet>
#include <QString>
#include <QVector>

#include "FieldGraph.h"

struct FieldEvaluationContext
{
    double x {0.0};
    double y {0.0};
};

struct FieldEvaluationResult
{
    bool ok {false};
    double value {0.0};
    QString error;
};

struct FieldBatchEvaluationResult
{
    bool ok {false};
    QVector<double> values;
    QString error;
};

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

struct FieldGridEvaluationResult
{
    bool ok {false};
    FieldScalarGrid grid;
    QString error;
};

class FieldGraphEvaluator
{
public:
    FieldEvaluationResult evaluateScalar(
        const FieldGraph &graph,
        int nodeId,
        const FieldEvaluationContext &context = {}) const;

    FieldBatchEvaluationResult evaluatePositions(
        const FieldGraph &graph,
        int nodeId,
        const QVector<FieldEvaluationContext> &positions) const;

    FieldGridEvaluationResult evaluateGrid(
        const FieldGraph &graph,
        int nodeId,
        int width,
        int height) const;

private:
    FieldEvaluationResult evaluateScalarInternal(
        const FieldGraph &graph,
        int nodeId,
        const FieldEvaluationContext &context,
        QSet<int> &visiting) const;

    FieldEvaluationResult evaluateInput(
        const FieldGraph &graph,
        const FieldNode &node,
        const QString &port,
        const FieldEvaluationContext &context,
        QSet<int> &visiting) const;

    FieldBatchEvaluationResult evaluateBatch(
        const FieldGraph &graph,
        int nodeId,
        const QVector<FieldEvaluationContext> &positions) const;

    FieldBatchEvaluationResult evaluateBatchInternal(
        const FieldGraph &graph,
        int nodeId,
        const QVector<FieldEvaluationContext> &positions,
        QHash<int, QVector<double>> &cache,
        QSet<int> &visiting) const;

    FieldBatchEvaluationResult evaluateBatchInput(
        const FieldGraph &graph,
        const FieldNode &node,
        const QString &port,
        const QVector<FieldEvaluationContext> &positions,
        QHash<int, QVector<double>> &cache,
        QSet<int> &visiting) const;
};

#endif
