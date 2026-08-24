/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_GRAPH_SAMPLER_H
#define FIELDLAB_FIELD_GRAPH_SAMPLER_H

#include "FieldGraphEvaluator.h"

// Scalar-loop oracle for tests and debugging. Production callers use the
// batch contracts on FieldGraphEvaluator.
class FieldGraphReferenceSampler
{
public:
    FieldGridEvaluationResult sampleScalarReference(
        const FieldGraph &graph,
        int outputNodeId,
        int width,
        int height) const;
};

#endif
