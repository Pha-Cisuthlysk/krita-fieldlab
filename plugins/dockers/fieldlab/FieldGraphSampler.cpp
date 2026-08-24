/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldGraphSampler.h"

#include "FieldGraphEvaluator.h"

#include <algorithm>
#include <cmath>
#include <limits>

FieldGridEvaluationResult FieldGraphReferenceSampler::sampleScalarReference(
    const FieldGraph &graph,
    int outputNodeId,
    int width,
    int height) const
{
    if (width <= 0 || height <= 0) {
        return {
            false,
            {},
            QStringLiteral("Sample dimensions must be positive.")
        };
    }

    const qint64 sampleCount = qint64(width) * qint64(height);

    if (sampleCount > std::numeric_limits<int>::max()) {
        return {
            false,
            {},
            QStringLiteral("Sample dimensions are too large.")
        };
    }

    FieldScalarGrid grid;
    grid.width = width;
    grid.height = height;
    grid.values.reserve(int(sampleCount));

    FieldGraphEvaluator evaluator;
    bool hasValue = false;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const FieldEvaluationContext context {
                width > 1
                    ? double(x) / double(width - 1)
                    : 0.0,
                height > 1
                    ? double(y) / double(height - 1)
                    : 0.0
            };

            const FieldEvaluationResult evaluation =
                evaluator.evaluateScalar(
                    graph,
                    outputNodeId,
                    context);

            if (!evaluation.ok) {
                return {
                    false,
                    {},
                    evaluation.error
                };
            }

            if (!std::isfinite(evaluation.value)) {
                return {
                    false,
                    {},
                    QStringLiteral(
                        "Node evaluated to a non-finite value at sample (%1, %2).")
                        .arg(x)
                        .arg(y)
                };
            }

            grid.values.append(evaluation.value);

            if (!hasValue) {
                grid.minimum = evaluation.value;
                grid.maximum = evaluation.value;
                hasValue = true;
            } else {
                grid.minimum =
                    std::min(grid.minimum, evaluation.value);
                grid.maximum =
                    std::max(grid.maximum, evaluation.value);
            }
        }
    }

    return {
        true,
        grid,
        QString()
    };
}
