/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_TEST_H
#define FIELDLAB_FIELD_GRAPH_TEST_H

#include <QObject>

class FieldGraphTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testGraphConnections();
    void testGraphMutation();
    void testArithmeticEvaluation();
    void testCoordinateEvaluation();
    void testEvaluationErrors();
    void testCycleDetection();
    void testBuiltInDescriptors();
    void testGraphValidation();
    void testGraphValidationErrors();
    void testPositionBatchEvaluation();
    void testGridBatchEvaluation();
    void testBatchEvaluationErrors();
    void testReferenceSamplerMatchesBatch();
};

#endif
