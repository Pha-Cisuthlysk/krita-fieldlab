/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_H
#define FIELDLAB_FIELD_GRAPH_H

#include <QHash>
#include <QString>
#include <QVariant>
#include <QVector>

struct FieldNode
{
    int id {-1};
    QString typeId;
    QHash<QString, QVariant> parameters;
};

struct FieldConnection
{
    int fromNode {-1};
    QString fromPort;

    int toNode {-1};
    QString toPort;
};

class FieldGraph
{
public:
    int addNode(
        const QString &typeId,
        const QHash<QString, QVariant> &parameters = {});

    bool removeNode(int nodeId);

    bool setNodeParameter(
        int nodeId,
        const QString &name,
        const QVariant &value);

    bool connectNodes(
        int fromNode,
        const QString &fromPort,
        int toNode,
        const QString &toPort);

    bool disconnectInput(
        int nodeId,
        const QString &inputPort);

    const FieldNode *node(int nodeId) const;

    const FieldConnection *connectionTo(
        int nodeId,
        const QString &inputPort) const;

    const QVector<FieldNode> &nodes() const;
    const QVector<FieldConnection> &connections() const;

private:
    int m_nextNodeId {1};

    QVector<FieldNode> m_nodes;
    QVector<FieldConnection> m_connections;
};

#endif
