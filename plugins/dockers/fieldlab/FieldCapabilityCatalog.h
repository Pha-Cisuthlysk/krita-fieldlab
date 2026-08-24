/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_CAPABILITY_CATALOG_H
#define FIELDLAB_FIELD_CAPABILITY_CATALOG_H

#include <QString>
#include <QVector>

enum class FieldCapabilityArea {
    Product,
    Platform,
    ArtistWorkflow,
    SemanticCore,
    FieldProcessing,
    Geometry,
    RasterIntegration,
    OptionalBackend
};

enum class FieldRequirementState {
    Active,
    Dependent,
    Deferred,
    Rejected
};

enum class FieldImplementationStage {
    Baseline,
    Partial,
    Scaffolded,
    ReuseIdentified,
    Researched,
    Deferred,
    Rejected
};

struct FieldCapabilityDescriptor {
    QString requirementId;
    QString capabilityId;
    QString displayName;
    FieldCapabilityArea area{FieldCapabilityArea::SemanticCore};
    FieldRequirementState requirementState{FieldRequirementState::Active};
    FieldImplementationStage implementationStage{FieldImplementationStage::Scaffolded};
    bool protectedNearTerm{false};
};

class FieldCapabilityCatalog
{
public:
    static const QVector<FieldCapabilityDescriptor> &all();
    static const FieldCapabilityDescriptor *find(const QString &requirementId);
    static int count(FieldRequirementState state);
    static int protectedNearTermCount();
};

#endif
