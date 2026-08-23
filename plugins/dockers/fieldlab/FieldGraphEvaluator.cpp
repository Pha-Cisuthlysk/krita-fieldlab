/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphEvaluator.h"

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
