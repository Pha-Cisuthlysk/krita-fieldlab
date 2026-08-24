/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldCapabilityCatalog.h"

namespace
{
using Area = FieldCapabilityArea;
using State = FieldRequirementState;
using Stage = FieldImplementationStage;

struct CapabilitySeed
{
    const char *requirementId;
    const char *capabilityId;
    const char *displayName;
    Area area;
    State state;
    Stage stage;
    bool protectedNearTerm;
};

const CapabilitySeed seeds[] {
    {"FL-PROD", "fieldlab.product", "Painting-first product", Area::Product, State::Active, Stage::Baseline, false},
    {"FL-PLAT", "fieldlab.platforms", "Windows and Android", Area::Platform, State::Active, Stage::Partial, false},
    {"FL-UI", "fieldlab.ui", "Accessible and customizable UI", Area::Platform, State::Active, Stage::Scaffolded, false},
    {"FL-CURVE", "fieldlab.passing-point-curves", "Passing-point curves", Area::ArtistWorkflow, State::Active, Stage::Scaffolded, true},
    {"FL-SMARTFILL", "fieldlab.smart-fill", "Smart Fill controls", Area::ArtistWorkflow, State::Active, Stage::ReuseIdentified, true},
    {"FL-COLOR", "fieldlab.color-harmony", "Color Harmony controls", Area::ArtistWorkflow, State::Active, Stage::ReuseIdentified, true},
    {"FL-TABLET", "fieldlab.tablet-workspace", "Tablet workspace", Area::Platform, State::Active, Stage::Scaffolded, true},
    {"FL-GRAPH", "fieldlab.semantic-graph", "Semantic graph", Area::SemanticCore, State::Active, Stage::Partial, true},
    {"FL-PREVIEW", "fieldlab.preview", "Procedural preview", Area::RasterIntegration, State::Active, Stage::Partial, false},
    {"FL-BAKE", "fieldlab.bake", "Procedural bake", Area::RasterIntegration, State::Active, Stage::Scaffolded, false},
    {"FL-SCALAR", "fieldlab.scalar-fields", "Scalar fields", Area::FieldProcessing, State::Active, Stage::Partial, false},
    {"FL-VECTOR", "fieldlab.vector-fields", "Vector fields", Area::FieldProcessing, State::Active, Stage::Scaffolded, false},
    {"FL-DIST", "fieldlab.distance-fields", "Distance fields", Area::FieldProcessing, State::Active, Stage::Scaffolded, false},
    {"FL-LINE-DIST", "fieldlab.line-distance", "Line-art distance", Area::RasterIntegration, State::Active, Stage::ReuseIdentified, false},
    {"FL-SDF", "fieldlab.sdf", "SDF primitives", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-FRACTAL", "fieldlab.fractals", "Fractals", Area::FieldProcessing, State::Active, Stage::ReuseIdentified, false},
    {"FL-WARP", "fieldlab.domain-warp", "Domain warping", Area::FieldProcessing, State::Active, Stage::ReuseIdentified, false},
    {"FL-CONTOUR", "fieldlab.contours", "Contours", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-STREAM", "fieldlab.streamlines", "Streamlines", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-HATCH", "fieldlab.hatching", "Procedural hatching", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-FLOW", "fieldlab.field-flow", "Field-flow tools", Area::ArtistWorkflow, State::Active, Stage::Scaffolded, false},
    {"FL-OPS", "fieldlab.operators", "Procedural operators", Area::FieldProcessing, State::Active, Stage::Partial, false},
    {"FL-ICOLOR", "fieldlab.intelligent-color", "Intelligent coloring", Area::ArtistWorkflow, State::Active, Stage::ReuseIdentified, false},
    {"FL-PARAM", "fieldlab.parameter-modulation", "Input parameter modulation", Area::ArtistWorkflow, State::Active, Stage::ReuseIdentified, false},
    {"FL-RASTER", "fieldlab.raster-source", "Raster sources", Area::RasterIntegration, State::Active, Stage::Scaffolded, false},
    {"FL-POINT", "fieldlab.point-set", "Point sets", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-PATH", "fieldlab.path-set", "Path sets", Area::Geometry, State::Active, Stage::Scaffolded, false},
    {"FL-MASK", "fieldlab.image-masks", "Image-derived masks", Area::RasterIntegration, State::Dependent, Stage::ReuseIdentified, false},
    {"FL-MATH-IR", "fieldlab.math-ir", "Math representation", Area::SemanticCore, State::Deferred, Stage::Partial, false},
    {"FL-MATH-VIZ", "fieldlab.math-visualization", "Math visualization", Area::OptionalBackend, State::Deferred, Stage::Deferred, false},
    {"FL-EXPR", "fieldlab.kseexpr", "KSeExpr backend", Area::OptionalBackend, State::Deferred, Stage::Researched, false},
    {"FL-GMIC", "fieldlab.gmic", "G'MIC backend", Area::OptionalBackend, State::Deferred, Stage::Researched, false},
    {"FL-3DREF", "fieldlab.3d-reference", "Lightweight 3D reference", Area::OptionalBackend, State::Deferred, Stage::Researched, false},
    {"FL-3DRIG", "fieldlab.3d-rigging", "Advanced 3D rigging", Area::OptionalBackend, State::Rejected, Stage::Rejected, false},
    {"FL-EROSION", "fieldlab.erosion", "Advanced erosion", Area::OptionalBackend, State::Rejected, Stage::Rejected, false},
    {"FL-WET", "fieldlab.wet-media", "Physical wet media", Area::OptionalBackend, State::Deferred, Stage::Deferred, false},
    {"FL-ANIM", "fieldlab.animation", "Procedural animation tracking", Area::OptionalBackend, State::Deferred, Stage::Deferred, false},
    {"FL-GPU", "fieldlab.gpu-compiler", "GPU graph compiler", Area::OptionalBackend, State::Deferred, Stage::Deferred, false}
};
}

const QVector<FieldCapabilityDescriptor> &FieldCapabilityCatalog::all()
{
    static const QVector<FieldCapabilityDescriptor> capabilities = [] {
        QVector<FieldCapabilityDescriptor> result;
        result.reserve(int(sizeof(seeds) / sizeof(seeds[0])));

        for (const CapabilitySeed &seed : seeds) {
            result.append({
                QString::fromLatin1(seed.requirementId),
                QString::fromLatin1(seed.capabilityId),
                QString::fromLatin1(seed.displayName),
                seed.area,
                seed.state,
                seed.stage,
                seed.protectedNearTerm
            });
        }

        return result;
    }();

    return capabilities;
}

const FieldCapabilityDescriptor *FieldCapabilityCatalog::find(
    const QString &requirementId)
{
    for (const FieldCapabilityDescriptor &descriptor : all()) {
        if (descriptor.requirementId == requirementId) {
            return &descriptor;
        }
    }

    return nullptr;
}

int FieldCapabilityCatalog::count(FieldRequirementState state)
{
    int result = 0;

    for (const FieldCapabilityDescriptor &descriptor : all()) {
        if (descriptor.requirementState == state) {
            ++result;
        }
    }

    return result;
}

int FieldCapabilityCatalog::protectedNearTermCount()
{
    int result = 0;

    for (const FieldCapabilityDescriptor &descriptor : all()) {
        if (descriptor.protectedNearTerm) {
            ++result;
        }
    }

    return result;
}
