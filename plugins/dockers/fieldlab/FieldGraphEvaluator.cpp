/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphEvaluator.h"

#include <algorithm>
#include <cmath>
#include <limits>

FieldEvaluationResult FieldGraphEvaluator::evaluateScalar(
    const FieldGraph &graph,
    int nodeId,
    const FieldEvaluationContext &context) const
{
    QSet<int> visiting;

    return evaluateScalarInternal(
        graph,
        nodeId,
        context,
        visiting);
}

FieldEvaluationResult FieldGraphEvaluator::evaluateInput(
    const FieldGraph &graph,
    const FieldNode &node,
    const QString &port,
    const FieldEvaluationContext &context,
    QSet<int> &visiting) const
{
    const FieldConnection *connection =
        graph.connectionTo(node.id, port);

    if (!connection) {
        return {
            false,
            0.0,
            QStringLiteral("Input '%1' is not connected.")
                .arg(port)
        };
    }

    return evaluateScalarInternal(
        graph,
        connection->fromNode,
        context,
        visiting);
}

FieldEvaluationResult FieldGraphEvaluator::evaluateScalarInternal(
    const FieldGraph &graph,
    int nodeId,
    const FieldEvaluationContext &context,
    QSet<int> &visiting) const
{
    const FieldNode *node = graph.node(nodeId);

    if (!node) {
        return {
            false,
            0.0,
            QStringLiteral("Node does not exist.")
        };
    }

    if (visiting.contains(nodeId)) {
        return {
            false,
            0.0,
            QStringLiteral("Cycle detected in graph.")
        };
    }

    visiting.insert(nodeId);

    auto finish =
        [&visiting, nodeId](const FieldEvaluationResult &result) {
            visiting.remove(nodeId);
            return result;
        };

    if (node->typeId == QStringLiteral("fieldlab.constant")) {
        return finish({
            true,
            node->parameters
                .value(QStringLiteral("value"), 0.0)
                .toDouble(),
            QString()
        });
    }

    if (node->typeId == QStringLiteral("fieldlab.position_x")) {
        return finish({
            true,
            context.x,
            QString()
        });
    }

    if (node->typeId == QStringLiteral("fieldlab.position_y")) {
        return finish({
            true,
            context.y,
            QString()
        });
    }

    if (node->typeId == QStringLiteral("fieldlab.add") ||
        node->typeId == QStringLiteral("fieldlab.multiply")) {

        FieldEvaluationResult a =
            evaluateInput(
                graph,
                *node,
                QStringLiteral("a"),
                context,
                visiting);

        if (!a.ok) {
            return finish(a);
        }

        FieldEvaluationResult b =
            evaluateInput(
                graph,
                *node,
                QStringLiteral("b"),
                context,
                visiting);

        if (!b.ok) {
            return finish(b);
        }

        if (node->typeId == QStringLiteral("fieldlab.add")) {
            return finish({
                true,
                a.value + b.value,
                QString()
            });
        }

        return finish({
            true,
            a.value * b.value,
            QString()
        });
    }

    return finish({
        false,
        0.0,
        QStringLiteral("Unknown node type: %1")
            .arg(node->typeId)
    });
}

FieldBatchEvaluationResult FieldGraphEvaluator::evaluatePositions(
    const FieldGraph &graph,
    int nodeId,
    const QVector<FieldEvaluationContext> &positions) const
{
    FieldBatchEvaluationResult result =
        evaluateBatch(graph, nodeId, positions);

    if (!result.ok) {
        return result;
    }

    for (int i = 0; i < result.values.size(); ++i) {
        if (!std::isfinite(result.values.at(i))) {
            return {
                false,
                {},
                QStringLiteral(
                    "Node evaluated to a non-finite value at position %1.")
                    .arg(i)
            };
        }
    }

    return result;
}

FieldGridEvaluationResult FieldGraphEvaluator::evaluateGrid(
    const FieldGraph &graph,
    int nodeId,
    int width,
    int height) const
{
    if (width <= 0 || height <= 0) {
        return {
            false,
            {},
            QStringLiteral("Grid dimensions must be positive.")
        };
    }

    const qint64 sampleCount = qint64(width) * qint64(height);

    if (sampleCount > std::numeric_limits<int>::max()) {
        return {
            false,
            {},
            QStringLiteral("Grid dimensions are too large.")
        };
    }

    QVector<FieldEvaluationContext> positions;
    positions.reserve(int(sampleCount));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            positions.append({
                width > 1
                    ? double(x) / double(width - 1)
                    : 0.0,
                height > 1
                    ? double(y) / double(height - 1)
                    : 0.0
            });
        }
    }

    const FieldBatchEvaluationResult evaluation =
        evaluateBatch(graph, nodeId, positions);

    if (!evaluation.ok) {
        return {
            false,
            {},
            evaluation.error
        };
    }

    FieldScalarGrid grid;
    grid.width = width;
    grid.height = height;
    grid.values = evaluation.values;

    bool hasValue = false;

    for (int i = 0; i < grid.values.size(); ++i) {
        const double value = grid.values.at(i);

        if (!std::isfinite(value)) {
            const int x = i % width;
            const int y = i / width;

            return {
                false,
                {},
                QStringLiteral(
                    "Node evaluated to a non-finite value at sample (%1, %2).")
                    .arg(x)
                    .arg(y)
            };
        }

        if (!hasValue) {
            grid.minimum = value;
            grid.maximum = value;
            hasValue = true;
        } else {
            grid.minimum = std::min(grid.minimum, value);
            grid.maximum = std::max(grid.maximum, value);
        }
    }

    return {
        true,
        grid,
        QString()
    };
}

FieldBatchEvaluationResult FieldGraphEvaluator::evaluateBatch(
    const FieldGraph &graph,
    int nodeId,
    const QVector<FieldEvaluationContext> &positions) const
{
    QHash<int, QVector<double>> cache;
    QSet<int> visiting;

    return evaluateBatchInternal(
        graph,
        nodeId,
        positions,
        cache,
        visiting);
}

FieldBatchEvaluationResult FieldGraphEvaluator::evaluateBatchInput(
    const FieldGraph &graph,
    const FieldNode &node,
    const QString &port,
    const QVector<FieldEvaluationContext> &positions,
    QHash<int, QVector<double>> &cache,
    QSet<int> &visiting) const
{
    const FieldConnection *connection =
        graph.connectionTo(node.id, port);

    if (!connection) {
        return {
            false,
            {},
            QStringLiteral("Input '%1' is not connected.")
                .arg(port)
        };
    }

    return evaluateBatchInternal(
        graph,
        connection->fromNode,
        positions,
        cache,
        visiting);
}

FieldBatchEvaluationResult FieldGraphEvaluator::evaluateBatchInternal(
    const FieldGraph &graph,
    int nodeId,
    const QVector<FieldEvaluationContext> &positions,
    QHash<int, QVector<double>> &cache,
    QSet<int> &visiting) const
{
    const auto cached = cache.constFind(nodeId);

    if (cached != cache.cend()) {
        return {
            true,
            cached.value(),
            QString()
        };
    }

    const FieldNode *node = graph.node(nodeId);

    if (!node) {
        return {
            false,
            {},
            QStringLiteral("Node does not exist.")
        };
    }

    if (visiting.contains(nodeId)) {
        return {
            false,
            {},
            QStringLiteral("Cycle detected in graph.")
        };
    }

    visiting.insert(nodeId);

    auto finish =
        [&cache, &visiting, nodeId](
            const FieldBatchEvaluationResult &result) {
            visiting.remove(nodeId);

            if (result.ok) {
                cache.insert(nodeId, result.values);
            }

            return result;
        };

    if (node->typeId == QStringLiteral("fieldlab.constant")) {
        return finish({
            true,
            QVector<double>(
                positions.size(),
                node->parameters
                    .value(QStringLiteral("value"), 0.0)
                    .toDouble()),
            QString()
        });
    }

    if (node->typeId == QStringLiteral("fieldlab.position_x") ||
        node->typeId == QStringLiteral("fieldlab.position_y")) {
        QVector<double> values;
        values.reserve(positions.size());

        const bool useX =
            node->typeId == QStringLiteral("fieldlab.position_x");

        for (const FieldEvaluationContext &position : positions) {
            values.append(useX ? position.x : position.y);
        }

        return finish({
            true,
            values,
            QString()
        });
    }

    if (node->typeId == QStringLiteral("fieldlab.add") ||
        node->typeId == QStringLiteral("fieldlab.multiply")) {
        const FieldBatchEvaluationResult a =
            evaluateBatchInput(
                graph,
                *node,
                QStringLiteral("a"),
                positions,
                cache,
                visiting);

        if (!a.ok) {
            return finish(a);
        }

        const FieldBatchEvaluationResult b =
            evaluateBatchInput(
                graph,
                *node,
                QStringLiteral("b"),
                positions,
                cache,
                visiting);

        if (!b.ok) {
            return finish(b);
        }

        QVector<double> values;
        values.reserve(positions.size());

        const bool add =
            node->typeId == QStringLiteral("fieldlab.add");

        for (int i = 0; i < positions.size(); ++i) {
            values.append(
                add
                    ? a.values.at(i) + b.values.at(i)
                    : a.values.at(i) * b.values.at(i));
        }

        return finish({
            true,
            values,
            QString()
        });
    }

    return finish({
        false,
        {},
        QStringLiteral("Unknown node type: %1")
            .arg(node->typeId)
    });
}
