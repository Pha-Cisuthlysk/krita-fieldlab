/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraph.h"

int FieldGraph::addNode(
    const QString &typeId,
    const QHash<QString, QVariant> &parameters)
{
    FieldNode node;

    node.id = m_nextNodeId++;
    node.typeId = typeId;
    node.parameters = parameters;

    m_nodes.append(node);

    return node.id;
}

bool FieldGraph::removeNode(int nodeId)
{
    int nodeIndex = -1;

    for (int i = 0; i < m_nodes.size(); ++i) {
        if (m_nodes.at(i).id == nodeId) {
            nodeIndex = i;
            break;
        }
    }

    if (nodeIndex < 0) {
        return false;
    }

    for (int i = m_connections.size() - 1; i >= 0; --i) {
        const FieldConnection &connection = m_connections.at(i);

        if (connection.fromNode == nodeId ||
            connection.toNode == nodeId) {
            m_connections.removeAt(i);
        }
    }

    m_nodes.removeAt(nodeIndex);
    return true;
}

bool FieldGraph::setNodeParameter(
    int nodeId,
    const QString &name,
    const QVariant &value)
{
    for (FieldNode &node : m_nodes) {
        if (node.id == nodeId) {
            node.parameters.insert(name, value);
            return true;
        }
    }

    return false;
}

bool FieldGraph::connectNodes(
    int fromNode,
    const QString &fromPort,
    int toNode,
    const QString &toPort)
{
    if (!node(fromNode) || !node(toNode)) {
        return false;
    }

    if (fromNode == toNode) {
        return false;
    }

    // One connection per input for now.
    for (int i = m_connections.size() - 1; i >= 0; --i) {
        const FieldConnection &existing = m_connections.at(i);

        if (existing.toNode == toNode &&
            existing.toPort == toPort) {
            m_connections.removeAt(i);
        }
    }

    FieldConnection connection;

    connection.fromNode = fromNode;
    connection.fromPort = fromPort;
    connection.toNode = toNode;
    connection.toPort = toPort;

    m_connections.append(connection);

    return true;
}

bool FieldGraph::disconnectInput(
    int nodeId,
    const QString &inputPort)
{
    bool disconnected = false;

    for (int i = m_connections.size() - 1; i >= 0; --i) {
        const FieldConnection &connection = m_connections.at(i);

        if (connection.toNode == nodeId &&
            connection.toPort == inputPort) {
            m_connections.removeAt(i);
            disconnected = true;
        }
    }

    return disconnected;
}

const FieldNode *FieldGraph::node(int nodeId) const
{
    for (const FieldNode &node : m_nodes) {
        if (node.id == nodeId) {
            return &node;
        }
    }

    return nullptr;
}

const FieldConnection *FieldGraph::connectionTo(
    int nodeId,
    const QString &inputPort) const
{
    for (const FieldConnection &connection : m_connections) {
        if (connection.toNode == nodeId &&
            connection.toPort == inputPort) {
            return &connection;
        }
    }

    return nullptr;
}

const QVector<FieldNode> &FieldGraph::nodes() const
{
    return m_nodes;
}

const QVector<FieldConnection> &FieldGraph::connections() const
{
    return m_connections;
}
