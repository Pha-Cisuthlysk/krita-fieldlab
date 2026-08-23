/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphValidator.h"

#include <QHash>

#include <utility>

namespace
{
const NodePortDescriptor *findPort(
    const QVector<NodePortDescriptor> &ports,
    const QString &portId)
{
    for (const NodePortDescriptor &port : ports) {
        if (port.id == portId) {
            return &port;
        }
    }

    return nullptr;
}

bool visitForCycle(
    int nodeId,
    const QHash<int, QVector<int>> &outgoing,
    QHash<int, int> &states)
{
    const int state = states.value(nodeId, 0);

    if (state == 1) {
        return true;
    }

    if (state == 2) {
        return false;
    }

    states.insert(nodeId, 1);

    for (int destination : outgoing.value(nodeId)) {
        if (visitForCycle(destination, outgoing, states)) {
            return true;
        }
    }

    states.insert(nodeId, 2);
    return false;
}

bool containsCycle(const FieldGraph &graph)
{
    QHash<int, QVector<int>> outgoing;

    for (const FieldConnection &connection : graph.connections()) {
        outgoing[connection.fromNode].append(connection.toNode);
    }

    QHash<int, int> states;

    for (const FieldNode &node : graph.nodes()) {
        if (visitForCycle(node.id, outgoing, states)) {
            return true;
        }
    }

    return false;
}
}

FieldGraphValidator::FieldGraphValidator(
    QVector<NodeDescriptor> descriptors)
    : m_descriptors(std::move(descriptors))
{
}

const NodeDescriptor *FieldGraphValidator::descriptorFor(
    const QString &typeId) const
{
    for (const NodeDescriptor &descriptor : m_descriptors) {
        if (descriptor.typeId == typeId) {
            return &descriptor;
        }
    }

    return nullptr;
}

FieldGraphValidationResult FieldGraphValidator::validate(
    const FieldGraph &graph) const
{
    FieldGraphValidationResult result;

    for (const FieldNode &node : graph.nodes()) {
        const NodeDescriptor *descriptor =
            descriptorFor(node.typeId);

        if (!descriptor) {
            result.errors.append(
                QStringLiteral("Node %1 uses unknown type '%2'.")
                    .arg(node.id)
                    .arg(node.typeId));
            continue;
        }

        for (const NodePortDescriptor &input : descriptor->inputs) {
            if (input.required &&
                !graph.connectionTo(node.id, input.id)) {
                result.errors.append(
                    QStringLiteral("Node %1 input '%2' is not connected.")
                        .arg(node.id)
                        .arg(input.id));
            }
        }
    }

    for (const FieldConnection &connection : graph.connections()) {
        const FieldNode *source = graph.node(connection.fromNode);
        const FieldNode *destination = graph.node(connection.toNode);

        if (!source) {
            result.errors.append(
                QStringLiteral("Connection source node %1 does not exist.")
                    .arg(connection.fromNode));
            continue;
        }

        if (!destination) {
            result.errors.append(
                QStringLiteral("Connection destination node %1 does not exist.")
                    .arg(connection.toNode));
            continue;
        }

        const NodeDescriptor *sourceDescriptor =
            descriptorFor(source->typeId);
        const NodeDescriptor *destinationDescriptor =
            descriptorFor(destination->typeId);

        if (!sourceDescriptor || !destinationDescriptor) {
            continue;
        }

        const NodePortDescriptor *sourcePort =
            findPort(sourceDescriptor->outputs, connection.fromPort);
        const NodePortDescriptor *destinationPort =
            findPort(destinationDescriptor->inputs, connection.toPort);

        if (!sourcePort) {
            result.errors.append(
                QStringLiteral("Node %1 type '%2' has no output '%3'.")
                    .arg(source->id)
                    .arg(source->typeId)
                    .arg(connection.fromPort));
        }

        if (!destinationPort) {
            result.errors.append(
                QStringLiteral("Node %1 type '%2' has no input '%3'.")
                    .arg(destination->id)
                    .arg(destination->typeId)
                    .arg(connection.toPort));
        }

        if (sourcePort && destinationPort &&
            sourcePort->valueType != destinationPort->valueType) {
            result.errors.append(
                QStringLiteral(
                    "Cannot connect %1.%2 to %3.%4: port types differ.")
                    .arg(source->id)
                    .arg(connection.fromPort)
                    .arg(destination->id)
                    .arg(connection.toPort));
        }
    }

    if (containsCycle(graph)) {
        result.errors.append(QStringLiteral("Graph contains a cycle."));
    }

    return result;
}
