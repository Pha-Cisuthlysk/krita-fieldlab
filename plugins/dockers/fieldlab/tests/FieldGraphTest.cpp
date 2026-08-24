/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphTest.h"

#include <QSet>
#include <QTest>

#include <limits>

#include "FieldCapabilityCatalog.h"
#include "FieldDataTypes.h"
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

void FieldGraphTest::testGraphMutation()
{
    FieldGraph graph;

    const int first = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 2.0}});
    const int second = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 3.0}});
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));

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

    QVERIFY(graph.setNodeParameter(
        first,
        QStringLiteral("value"),
        4.0));
    QVERIFY(!graph.setNodeParameter(
        99,
        QStringLiteral("value"),
        1.0));

    const FieldEvaluationResult updated =
        FieldGraphEvaluator().evaluateScalar(graph, add);
    QVERIFY2(updated.ok, qPrintable(updated.error));
    QCOMPARE(updated.value, 7.0);

    QVERIFY(graph.disconnectInput(add, QStringLiteral("a")));
    QVERIFY(!graph.disconnectInput(add, QStringLiteral("a")));
    QCOMPARE(graph.connections().size(), 1);

    const FieldEvaluationResult disconnected =
        FieldGraphEvaluator().evaluateScalar(graph, add);
    QVERIFY(!disconnected.ok);
    QCOMPARE(
        disconnected.error,
        QStringLiteral("Input 'a' is not connected."));

    QVERIFY(graph.connectNodes(
        first,
        QStringLiteral("value"),
        add,
        QStringLiteral("a")));
    QVERIFY(graph.removeNode(first));
    QVERIFY(!graph.removeNode(first));
    QVERIFY(!graph.node(first));
    QCOMPARE(graph.connections().size(), 1);
    QCOMPARE(
        graph.connectionTo(add, QStringLiteral("b"))->fromNode,
        second);

    const int next = graph.addNode(QStringLiteral("fieldlab.constant"));
    QCOMPARE(next, 4);
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

void FieldGraphTest::testPositionBatchEvaluation()
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

    const FieldBatchEvaluationResult result =
        FieldGraphEvaluator().evaluatePositions(
            graph,
            add,
            {
                {0.25, 0.75},
                {1.0, 0.5},
                {-2.0, 3.0}
            });

    QVERIFY2(result.ok, qPrintable(result.error));
    QCOMPARE(result.values.size(), 3);
    QCOMPARE(result.values.at(0), 1.0);
    QCOMPARE(result.values.at(1), 1.5);
    QCOMPARE(result.values.at(2), 1.0);

    const FieldBatchEvaluationResult empty =
        FieldGraphEvaluator().evaluatePositions(graph, add, {});

    QVERIFY2(empty.ok, qPrintable(empty.error));
    QVERIFY(empty.values.isEmpty());
}

void FieldGraphTest::testGridBatchEvaluation()
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

    const FieldGridEvaluationResult result =
        FieldGraphEvaluator().evaluateGrid(graph, add, 3, 2);

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

    const FieldGridEvaluationResult singleSample =
        FieldGraphEvaluator().evaluateGrid(
            constantGraph,
            constant,
            1,
            1);

    QVERIFY2(singleSample.ok, qPrintable(singleSample.error));
    QCOMPARE(singleSample.grid.minimum, 7.0);
    QCOMPARE(singleSample.grid.maximum, 7.0);
    QCOMPARE(singleSample.grid.valueAt(0, 0), 7.0);
}

void FieldGraphTest::testBatchEvaluationErrors()
{
    FieldGraph graph;
    const int add = graph.addNode(QStringLiteral("fieldlab.add"));

    const FieldBatchEvaluationResult missingNode =
        FieldGraphEvaluator().evaluatePositions(
            graph,
            99,
            {{0.0, 0.0}});
    QVERIFY(!missingNode.ok);
    QCOMPARE(
        missingNode.error,
        QStringLiteral("Node does not exist."));

    const FieldGridEvaluationResult invalidDimensions =
        FieldGraphEvaluator().evaluateGrid(graph, add, 0, 16);
    QVERIFY(!invalidDimensions.ok);
    QCOMPARE(
        invalidDimensions.error,
        QStringLiteral("Grid dimensions must be positive."));

    const FieldGridEvaluationResult oversized =
        FieldGraphEvaluator().evaluateGrid(
            graph,
            add,
            std::numeric_limits<int>::max(),
            2);
    QVERIFY(!oversized.ok);
    QCOMPARE(
        oversized.error,
        QStringLiteral("Grid dimensions are too large."));

    const FieldGridEvaluationResult evaluationError =
        FieldGraphEvaluator().evaluateGrid(graph, add, 2, 2);
    QVERIFY(!evaluationError.ok);
    QCOMPARE(
        evaluationError.error,
        QStringLiteral("Input 'a' is not connected."));

    FieldGraph unknownGraph;
    const int unknown =
        unknownGraph.addNode(QStringLiteral("fieldlab.unknown"));

    const FieldBatchEvaluationResult unknownNode =
        FieldGraphEvaluator().evaluatePositions(
            unknownGraph,
            unknown,
            {{0.0, 0.0}});
    QVERIFY(!unknownNode.ok);
    QCOMPARE(
        unknownNode.error,
        QStringLiteral("Unknown node type: fieldlab.unknown"));

    FieldGraph cyclicGraph;
    const int constant = cyclicGraph.addNode(
        QStringLiteral("fieldlab.constant"),
        {{QStringLiteral("value"), 1.0}});
    const int cyclicAdd =
        cyclicGraph.addNode(QStringLiteral("fieldlab.add"));
    const int cyclicMultiply =
        cyclicGraph.addNode(QStringLiteral("fieldlab.multiply"));

    QVERIFY(cyclicGraph.connectNodes(
        cyclicMultiply,
        QStringLiteral("value"),
        cyclicAdd,
        QStringLiteral("a")));
    QVERIFY(cyclicGraph.connectNodes(
        constant,
        QStringLiteral("value"),
        cyclicAdd,
        QStringLiteral("b")));
    QVERIFY(cyclicGraph.connectNodes(
        cyclicAdd,
        QStringLiteral("value"),
        cyclicMultiply,
        QStringLiteral("a")));
    QVERIFY(cyclicGraph.connectNodes(
        constant,
        QStringLiteral("value"),
        cyclicMultiply,
        QStringLiteral("b")));

    const FieldGridEvaluationResult cycle =
        FieldGraphEvaluator().evaluateGrid(
            cyclicGraph,
            cyclicAdd,
            2,
            2);
    QVERIFY(!cycle.ok);
    QCOMPARE(
        cycle.error,
        QStringLiteral("Cycle detected in graph."));

    FieldGraph nonFiniteGraph;
    const int infinity = nonFiniteGraph.addNode(
        QStringLiteral("fieldlab.constant"),
        {
            {
                QStringLiteral("value"),
                std::numeric_limits<double>::infinity()
            }
        });

    const FieldGridEvaluationResult nonFinite =
        FieldGraphEvaluator().evaluateGrid(
            nonFiniteGraph,
            infinity,
            1,
            1);
    QVERIFY(!nonFinite.ok);
    QCOMPARE(
        nonFinite.error,
        QStringLiteral(
            "Node evaluated to a non-finite value at sample (0, 0)."));

    const FieldBatchEvaluationResult nonFinitePosition =
        FieldGraphEvaluator().evaluatePositions(
            nonFiniteGraph,
            infinity,
            {{0.0, 0.0}});
    QVERIFY(!nonFinitePosition.ok);
    QCOMPARE(
        nonFinitePosition.error,
        QStringLiteral(
            "Node evaluated to a non-finite value at position 0."));
}

void FieldGraphTest::testReferenceSamplerMatchesBatch()
{
    FieldGraph graph;

    const int x = graph.addNode(QStringLiteral("fieldlab.position_x"));
    const int y = graph.addNode(QStringLiteral("fieldlab.position_y"));
    const int multiply =
        graph.addNode(QStringLiteral("fieldlab.multiply"));

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

    const FieldGridEvaluationResult batch =
        FieldGraphEvaluator().evaluateGrid(graph, multiply, 4, 3);
    const FieldGridEvaluationResult reference =
        FieldGraphReferenceSampler().sampleScalarReference(
            graph,
            multiply,
            4,
            3);
    const FieldGridEvaluationResult repeated =
        FieldGraphEvaluator().evaluateGrid(graph, multiply, 4, 3);

    QVERIFY2(batch.ok, qPrintable(batch.error));
    QVERIFY2(reference.ok, qPrintable(reference.error));
    QVERIFY2(repeated.ok, qPrintable(repeated.error));
    QCOMPARE(reference.grid.width, batch.grid.width);
    QCOMPARE(reference.grid.height, batch.grid.height);
    QCOMPARE(reference.grid.minimum, batch.grid.minimum);
    QCOMPARE(reference.grid.maximum, batch.grid.maximum);
    QCOMPARE(reference.grid.values, batch.grid.values);
    QCOMPARE(repeated.grid.values, batch.grid.values);
}

void FieldGraphTest::testCoreDataScaffold()
{
    const FieldDomain2D domain{2, 2, -1.0, -1.0, 1.0, 1.0};

    QVERIFY(domain.isValid());
    QCOMPARE(domain.sampleCount(), qint64(4));

    ScalarField2D scalarField{domain, {0.0, 0.25, 0.5, 1.0}};
    QVERIFY(scalarField.isConsistent());
    scalarField.samples.removeLast();
    QVERIFY(!scalarField.isConsistent());

    const VectorField2D vectorField{domain, {{1.0, 0.0}, {0.0, 1.0}, {-1.0, 0.0}, {0.0, -1.0}}};
    QVERIFY(vectorField.isConsistent());

    RasterSource rasterSource;
    QVERIFY(!rasterSource.isValid());
    rasterSource.sourceId = QStringLiteral("document.layer:42");
    rasterSource.channelId = QStringLiteral("luminance");
    QVERIFY(rasterSource.isValid());

    PointSet points;
    points.points.append({0.25, 0.75, 0.5});
    QCOMPARE(points.points.first().weight, 0.5);

    PathSet paths;
    paths.paths.append({points.points, true});
    QVERIFY(paths.paths.first().closed);
    QCOMPARE(paths.paths.first().points.size(), 1);

    const QVector<FieldDataKind> &kinds = fieldCoreDataKinds();
    QCOMPARE(kinds.size(), 5);

    QSet<QString> kindIds;
    for (FieldDataKind kind : kinds) {
        const QString id = fieldDataKindId(kind);
        QVERIFY(!id.isEmpty());
        QVERIFY(!kindIds.contains(id));
        kindIds.insert(id);
    }
}

void FieldGraphTest::testCapabilityCatalog()
{
    const QVector<FieldCapabilityDescriptor> &capabilities = FieldCapabilityCatalog::all();

    QCOMPARE(capabilities.size(), 38);
    QCOMPARE(FieldCapabilityCatalog::count(FieldRequirementState::Active), 27);
    QCOMPARE(FieldCapabilityCatalog::count(FieldRequirementState::Dependent), 1);
    QCOMPARE(FieldCapabilityCatalog::count(FieldRequirementState::Deferred), 8);
    QCOMPARE(FieldCapabilityCatalog::count(FieldRequirementState::Rejected), 2);
    QCOMPARE(FieldCapabilityCatalog::protectedNearTermCount(), 5);

    QSet<QString> requirementIds;
    QSet<QString> capabilityIds;
    QSet<int> capabilityAreas;
    QSet<QString> protectedRequirementIds;

    for (const FieldCapabilityDescriptor &descriptor : capabilities) {
        QVERIFY(!descriptor.requirementId.isEmpty());
        QVERIFY(!descriptor.capabilityId.isEmpty());
        QVERIFY(!descriptor.displayName.isEmpty());
        QVERIFY(!requirementIds.contains(descriptor.requirementId));
        QVERIFY(!capabilityIds.contains(descriptor.capabilityId));
        requirementIds.insert(descriptor.requirementId);
        capabilityIds.insert(descriptor.capabilityId);
        capabilityAreas.insert(int(descriptor.area));

        if (descriptor.protectedNearTerm) {
            protectedRequirementIds.insert(descriptor.requirementId);
        }

        if (descriptor.requirementState == FieldRequirementState::Rejected) {
            QCOMPARE(descriptor.implementationStage, FieldImplementationStage::Rejected);
        }
    }

    const QSet<QString> expectedRequirementIds{
        QStringLiteral("FL-PROD"),    QStringLiteral("FL-PLAT"),      QStringLiteral("FL-UI"),
        QStringLiteral("FL-CURVE"),   QStringLiteral("FL-SMARTFILL"), QStringLiteral("FL-COLOR"),
        QStringLiteral("FL-TABLET"),  QStringLiteral("FL-GRAPH"),     QStringLiteral("FL-PREVIEW"),
        QStringLiteral("FL-BAKE"),    QStringLiteral("FL-SCALAR"),    QStringLiteral("FL-VECTOR"),
        QStringLiteral("FL-DIST"),    QStringLiteral("FL-LINE-DIST"), QStringLiteral("FL-SDF"),
        QStringLiteral("FL-FRACTAL"), QStringLiteral("FL-WARP"),      QStringLiteral("FL-CONTOUR"),
        QStringLiteral("FL-STREAM"),  QStringLiteral("FL-HATCH"),     QStringLiteral("FL-FLOW"),
        QStringLiteral("FL-OPS"),     QStringLiteral("FL-ICOLOR"),    QStringLiteral("FL-PARAM"),
        QStringLiteral("FL-RASTER"),  QStringLiteral("FL-POINT"),     QStringLiteral("FL-PATH"),
        QStringLiteral("FL-MASK"),    QStringLiteral("FL-MATH-IR"),   QStringLiteral("FL-MATH-VIZ"),
        QStringLiteral("FL-EXPR"),    QStringLiteral("FL-GMIC"),      QStringLiteral("FL-3DREF"),
        QStringLiteral("FL-3DRIG"),   QStringLiteral("FL-EROSION"),   QStringLiteral("FL-WET"),
        QStringLiteral("FL-ANIM"),    QStringLiteral("FL-GPU")};

    QVERIFY(requirementIds == expectedRequirementIds);
    QCOMPARE(capabilityAreas.size(), 8);

    const QSet<QString> expectedProtectedRequirementIds {
        QStringLiteral("FL-CURVE"),
        QStringLiteral("FL-SMARTFILL"),
        QStringLiteral("FL-COLOR"),
        QStringLiteral("FL-TABLET"),
        QStringLiteral("FL-GRAPH")
    };
    QVERIFY(protectedRequirementIds == expectedProtectedRequirementIds);

    QVERIFY(FieldCapabilityCatalog::find(QStringLiteral("FL-VECTOR")));
    QVERIFY(FieldCapabilityCatalog::find(QStringLiteral("FL-BAKE")));
    QVERIFY(!FieldCapabilityCatalog::find(QStringLiteral("FL-MISSING")));
}

QTEST_GUILESS_MAIN(FieldGraphTest)
