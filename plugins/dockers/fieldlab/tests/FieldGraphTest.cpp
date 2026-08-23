/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphTest.h"

#include <QSet>
#include <QTest>

#include "FieldGraph.h"
#include "FieldGraphEvaluator.h"
#include "NodeDescriptor.h"

void FieldGraphTest::testGraphConnections()
{
    FieldGraph graph;

    const int first = graph.addNode(QStringLiteral("fieldlab.constant"));
    const int second = graph.addNode(QStringLiteral("fieldlab.constant"));
    const int replacement = graph.addNode(QStringLiteral("fieldlab.constant"));
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));

    QCOMPARE(first, 1);
    QCOMPARE(second, 2);
    QCOMPARE(graph.nodes().size(), 4);
    QCOMPARE(graph.node(second)->typeId, QStringLiteral("fieldlab.constant"));
    QVERIFY(!graph.node(99));

    QVERIFY(graph.connectNodes(
        first,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        second,
        QStringLiteral("value"),
        add,
        QStringLiteral("b")));
    QCOMPARE(graph.connections().size(), 2);

    QVERIFY(graph.connectNodes(
        replacement,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QCOMPARE(graph.connections().size(), 2);
    QCOMPARE(graph.connectionTo(add, QStringLiteral("a"))->fromNode, replacement);

    QVERIFY(!graph.connectNodes(
        99,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(!graph.connectNodes(
        add,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
}

void FieldGraphTest::testArithmeticEvaluation()
{
    FieldGraph graph;

    const int two = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 2.0}});
    const int three = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 3.0}});
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));
    const int multiply = graph.addNode(QStringLiteral("fieldlab.multiply"));

    QVERIFY(graph.connectNodes(
        two,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        three,
        QStringLiteral("value"),
        add,
        QStringLiteral("b")));
    QVERIFY(graph.connectNodes(
        add,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        three,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("b")));

    const FieldEvaluationResult result =
        FieldGraphEvaluator().evaluateScalar(graph, multiply);

    QVERIFY2(result.ok, qPrintable(result.error));
    QCOMPARE(result.value, 15.0);
}

void FieldGraphTest::testCoordinateEvaluation()
{
    FieldGraph graph;

    const int x = graph.addNode(QStringLiteral("fieldlab.position_x"));
    const int y = graph.addNode(QStringLiteral("fieldlab.position_y"));
    const int multiply = graph.addNode(QStringLiteral("fieldlab.multiply"));

    QVERIFY(graph.connectNodes(
        x,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        y,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("b")));

    const FieldEvaluationResult result =
        FieldGraphEvaluator().evaluateScalar(
            graph,
            multiply,
            {0.25, 0.8});

    QVERIFY2(result.ok, qPrintable(result.error));
    QCOMPARE(result.value, 0.2);
}

void FieldGraphTest::testEvaluationErrors()
{
    FieldGraph graph;
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));
    const int unknown = graph.addNode(QStringLiteral("fieldlab.unknown"));

    FieldGraphEvaluator evaluator;

    const FieldEvaluationResult missingNode =
        evaluator.evaluateScalar(graph, 99);
    QVERIFY(!missingNode.ok);
    QCOMPARE(missingNode.error, QStringLiteral("Node does not exist."));

    const FieldEvaluationResult missingInput =
        evaluator.evaluateScalar(graph, add);
    QVERIFY(!missingInput.ok);
    QCOMPARE(
        missingInput.error,
        QStringLiteral("Input 'a' is not connected."));

    const FieldEvaluationResult unknownNode =
        evaluator.evaluateScalar(graph, unknown);
    QVERIFY(!unknownNode.ok);
    QCOMPARE(
        unknownNode.error,
        QStringLiteral("Unknown node type: fieldlab.unknown"));
}

void FieldGraphTest::testCycleDetection()
{
    FieldGraph graph;

    const int constant = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 1.0}});
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));
    const int multiply = graph.addNode(QStringLiteral("fieldlab.multiply"));

    QVERIFY(graph.connectNodes(
        multiply,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        constant,
        QStringLiteral("value"),
        add,
        QStringLiteral("b")));
    QVERIFY(graph.connectNodes(
        add,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        constant,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("b")));

    const FieldEvaluationResult result =
        FieldGraphEvaluator().evaluateScalar(graph, add);

    QVERIFY(!result.ok);
    QCOMPARE(result.error, QStringLiteral("Cycle detected in graph."));
}

void FieldGraphTest::testBuiltInDescriptors()
{
    const QVector<NodeDescriptor> descriptors =
        NodeDescriptor::builtInScalarNodes();

    QCOMPARE(descriptors.size(), 5);

    QSet<QString> typeIds;

    for (const NodeDescriptor &descriptor : descriptors) {
        QVERIFY(!descriptor.typeId.isEmpty());
        QVERIFY(!typeIds.contains(descriptor.typeId));
        typeIds.insert(descriptor.typeId);

        QCOMPARE(descriptor.outputs.size(), 1);
        QCOMPARE(descriptor.outputs.first().id, QStringLiteral("value"));
        QCOMPARE(
            descriptor.outputs.first().valueType,
            FieldValueType::Scalar);
        QCOMPARE(
            descriptor.outputs.first().direction,
            FieldPortDirection::Output);
    }

    QVERIFY(typeIds.contains(QStringLiteral("fieldlab.constant")));
    QVERIFY(typeIds.contains(QStringLiteral("fieldlab.position_x")));
    QVERIFY(typeIds.contains(QStringLiteral("fieldlab.position_y")));
    QVERIFY(typeIds.contains(QStringLiteral("fieldlab.add")));
    QVERIFY(typeIds.contains(QStringLiteral("fieldlab.multiply")));
}

QTEST_GUILESS_MAIN(FieldGraphTest)
