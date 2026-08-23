/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphTest.h"

#include <QSet>
#include <QTest>

#include <limits>

#include "FieldGraph.h"
#include "FieldGraphEvaluator.h"
#include "FieldGraphSampler.h"
#include "FieldGraphValidator.h"
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

void FieldGraphTest::testGraphValidation()
{
    FieldGraph graph;

    const int constant = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 2.0}});
    const int x = graph.addNode(QStringLiteral("fieldlab.position_x"));
    const int multiply = graph.addNode(QStringLiteral("fieldlab.multiply"));

    QVERIFY(graph.connectNodes(
        constant,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        x,
        QStringLiteral("value"),
        multiply,
        QStringLiteral("b")));

    const FieldGraphValidationResult result =
        FieldGraphValidator().validate(graph);

    QVERIFY(result.isValid());
    QVERIFY(result.errors.isEmpty());

    NodeDescriptor optionalInput;
    optionalInput.typeId = QStringLiteral("test.optional_input");
    optionalInput.inputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Input,
        false
    });

    FieldGraph optionalGraph;
    optionalGraph.addNode(optionalInput.typeId);

    const FieldGraphValidationResult optionalResult =
        FieldGraphValidator({optionalInput}).validate(optionalGraph);

    QVERIFY(optionalResult.isValid());
}

void FieldGraphTest::testGraphValidationErrors()
{
    {
        FieldGraph graph;
        const int unknown =
            graph.addNode(QStringLiteral("fieldlab.unknown"));

        const FieldGraphValidationResult result =
            FieldGraphValidator().validate(graph);

        QVERIFY(!result.isValid());
        QVERIFY(result.errors.contains(
            QStringLiteral("Node %1 uses unknown type 'fieldlab.unknown'.")
                .arg(unknown)));
    }

    {
        FieldGraph graph;
        const int constant =
            graph.addNode(QStringLiteral("fieldlab.constant"));
        const int add = graph.addNode(QStringLiteral("fieldlab.add"));

        QVERIFY(graph.connectNodes(
            constant,
            QStringLiteral("missing"),
            add,
            QStringLiteral("a")));
        QVERIFY(graph.connectNodes(
            constant,
            QStringLiteral("value"),
            add,
            QStringLiteral("missing")));

        const FieldGraphValidationResult result =
            FieldGraphValidator().validate(graph);

        QVERIFY(!result.isValid());
        QVERIFY(result.errors.contains(
            QStringLiteral("Node %1 type 'fieldlab.constant' has no output 'missing'.")
                .arg(constant)));
        QVERIFY(result.errors.contains(
            QStringLiteral("Node %1 type 'fieldlab.add' has no input 'missing'.")
                .arg(add)));
        QVERIFY(result.errors.contains(
            QStringLiteral("Node %1 input 'b' is not connected.")
                .arg(add)));
    }

    {
        NodeDescriptor vectorSource;
        vectorSource.typeId = QStringLiteral("test.vector_source");
        vectorSource.outputs.append({
            QStringLiteral("value"),
            QStringLiteral("Value"),
            FieldValueType::Vector2,
            FieldPortDirection::Output
        });

        NodeDescriptor scalarDestination;
        scalarDestination.typeId = QStringLiteral("test.scalar_destination");
        scalarDestination.inputs.append({
            QStringLiteral("value"),
            QStringLiteral("Value"),
            FieldValueType::Scalar,
            FieldPortDirection::Input
        });

        FieldGraph graph;
        const int source = graph.addNode(vectorSource.typeId);
        const int destination = graph.addNode(scalarDestination.typeId);

        QVERIFY(graph.connectNodes(
            source,
            QStringLiteral("value"),
            destination,
            QStringLiteral("value")));

        const FieldGraphValidationResult result =
            FieldGraphValidator({vectorSource, scalarDestination})
                .validate(graph);

        QVERIFY(!result.isValid());
        QVERIFY(result.errors.contains(
            QStringLiteral(
                "Cannot connect %1.value to %2.value: port types differ.")
                .arg(source)
                .arg(destination)));
    }

    {
        FieldGraph graph;
        const int constant =
            graph.addNode(QStringLiteral("fieldlab.constant"));
        const int add = graph.addNode(QStringLiteral("fieldlab.add"));
        const int multiply =
            graph.addNode(QStringLiteral("fieldlab.multiply"));

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

        const FieldGraphValidationResult result =
            FieldGraphValidator().validate(graph);

        QVERIFY(!result.isValid());
        QVERIFY(result.errors.contains(
            QStringLiteral("Graph contains a cycle.")));
    }
}

void FieldGraphTest::testGridSampling()
{
    FieldGraph graph;

    const int x = graph.addNode(QStringLiteral("fieldlab.position_x"));
    const int y = graph.addNode(QStringLiteral("fieldlab.position_y"));
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));

    QVERIFY(graph.connectNodes(
        x,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(graph.connectNodes(
        y,
        QStringLiteral("value"),
        add,
        QStringLiteral("b")));

    const FieldGraphSamplingResult result =
        FieldGraphSampler().sampleScalar(graph, add, 3, 2);

    QVERIFY2(result.ok, qPrintable(result.error));
    QCOMPARE(result.grid.width, 3);
    QCOMPARE(result.grid.height, 2);
    QCOMPARE(result.grid.values.size(), 6);
    QCOMPARE(result.grid.minimum, 0.0);
    QCOMPARE(result.grid.maximum, 2.0);
    QCOMPARE(result.grid.valueAt(0, 0), 0.0);
    QCOMPARE(result.grid.valueAt(1, 0), 0.5);
    QCOMPARE(result.grid.valueAt(2, 0), 1.0);
    QCOMPARE(result.grid.valueAt(0, 1), 1.0);
    QCOMPARE(result.grid.valueAt(1, 1), 1.5);
    QCOMPARE(result.grid.valueAt(2, 1), 2.0);

    FieldGraph constantGraph;
    const int constant = constantGraph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 7.0}});

    const FieldGraphSamplingResult singleSample =
        FieldGraphSampler().sampleScalar(
            constantGraph,
            constant,
            1,
            1);

    QVERIFY2(singleSample.ok, qPrintable(singleSample.error));
    QCOMPARE(singleSample.grid.minimum, 7.0);
    QCOMPARE(singleSample.grid.maximum, 7.0);
    QCOMPARE(singleSample.grid.valueAt(0, 0), 7.0);
}

void FieldGraphTest::testGridSamplingErrors()
{
    FieldGraph graph;
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));

    const FieldGraphSamplingResult invalidDimensions =
        FieldGraphSampler().sampleScalar(graph, add, 0, 16);
    QVERIFY(!invalidDimensions.ok);
    QCOMPARE(
        invalidDimensions.error,
        QStringLiteral("Sample dimensions must be positive."));

    const FieldGraphSamplingResult evaluationError =
        FieldGraphSampler().sampleScalar(graph, add, 2, 2);
    QVERIFY(!evaluationError.ok);
    QCOMPARE(
        evaluationError.error,
        QStringLiteral("Input 'a' is not connected."));

    FieldGraph nonFiniteGraph;
    const int infinity = nonFiniteGraph.addNode(
        QStringLiteral("fieldlab.constant"),
        {
            {
                QStringLiteral("value"),
                std::numeric_limits<double>::infinity()
            }
        });

    const FieldGraphSamplingResult nonFinite =
        FieldGraphSampler().sampleScalar(
            nonFiniteGraph,
            infinity,
            1,
            1);
    QVERIFY(!nonFinite.ok);
    QCOMPARE(
        nonFinite.error,
        QStringLiteral(
            "Node evaluated to a non-finite value at sample (0, 0)."));
}

QTEST_GUILESS_MAIN(FieldGraphTest)
