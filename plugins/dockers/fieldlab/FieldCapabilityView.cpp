/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldCapabilityView.h"

#include "FieldCapabilityCatalog.h"
#include "FieldDataTypes.h"

#include <QComboBox>
#include <QFont>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include <klocalizedstring.h>

namespace
{
constexpr int RequirementStateRole = Qt::UserRole;
constexpr int SearchTextRole = Qt::UserRole + 1;

QString areaLabel(FieldCapabilityArea area)
{
    switch (area) {
    case FieldCapabilityArea::Product:
        return i18n("Product");
    case FieldCapabilityArea::Platform:
        return i18n("Platform and UI");
    case FieldCapabilityArea::ArtistWorkflow:
        return i18n("Artist workflows");
    case FieldCapabilityArea::SemanticCore:
        return i18n("Semantic core");
    case FieldCapabilityArea::FieldProcessing:
        return i18n("Field processing");
    case FieldCapabilityArea::Geometry:
        return i18n("Geometry and paths");
    case FieldCapabilityArea::RasterIntegration:
        return i18n("Raster and Krita integration");
    case FieldCapabilityArea::OptionalBackend:
        return i18n("Deferred and optional systems");
    }

    return i18n("Other");
}

QString requirementStateLabel(FieldRequirementState state)
{
    switch (state) {
    case FieldRequirementState::Active:
        return i18n("Active");
    case FieldRequirementState::Dependent:
        return i18n("Dependent");
    case FieldRequirementState::Deferred:
        return i18n("Deferred");
    case FieldRequirementState::Rejected:
        return i18n("Not planned");
    }

    return i18n("Unknown");
}

QString implementationStageLabel(FieldImplementationStage stage)
{
    switch (stage) {
    case FieldImplementationStage::Baseline:
        return i18n("Krita baseline");
    case FieldImplementationStage::Partial:
        return i18n("Partial");
    case FieldImplementationStage::Scaffolded:
        return i18n("Scaffold only");
    case FieldImplementationStage::ReuseIdentified:
        return i18n("Reuse identified");
    case FieldImplementationStage::Researched:
        return i18n("Researched");
    case FieldImplementationStage::Deferred:
        return i18n("Deferred");
    case FieldImplementationStage::Rejected:
        return i18n("Not planned");
    }

    return i18n("Unknown");
}

QString dataKindLabel(FieldDataKind kind)
{
    switch (kind) {
    case FieldDataKind::ScalarField2D:
        return i18n("Scalar field");
    case FieldDataKind::VectorField2D:
        return i18n("Vector field");
    case FieldDataKind::RasterSource:
        return i18n("Raster source");
    case FieldDataKind::PointSet:
        return i18n("Point set");
    case FieldDataKind::PathSet:
        return i18n("Path set");
    }

    return i18n("Unknown");
}
}

FieldCapabilityView::FieldCapabilityView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *intro = new QLabel(
        i18n(
            "Every canonical system is retained here. Status describes "
            "architecture readiness, not a completed artist tool."),
        this);
    intro->setWordWrap(true);

    QStringList dataKinds;
    for (FieldDataKind kind : fieldCoreDataKinds()) {
        dataKinds.append(dataKindLabel(kind));
    }

    QLabel *contracts = new QLabel(
        i18n("Interchange contracts: %1", dataKinds.join(QStringLiteral(" | "))),
        this);
    contracts->setWordWrap(true);

    QHBoxLayout *filters = new QHBoxLayout();

    m_search = new QLineEdit(this);
    m_search->setPlaceholderText(i18n("Find a system..."));
    m_search->setClearButtonEnabled(true);
    m_search->setAccessibleName(i18n("Search Field Lab systems"));

    m_stateFilter = new QComboBox(this);
    m_stateFilter->addItem(i18n("All states"), -1);
    m_stateFilter->addItem(
        i18n("Active"),
        int(FieldRequirementState::Active));
    m_stateFilter->addItem(
        i18n("Dependent"),
        int(FieldRequirementState::Dependent));
    m_stateFilter->addItem(
        i18n("Deferred"),
        int(FieldRequirementState::Deferred));
    m_stateFilter->addItem(
        i18n("Not planned"),
        int(FieldRequirementState::Rejected));
    m_stateFilter->setAccessibleName(i18n("Filter Field Lab roadmap state"));

    filters->addWidget(m_search, 1);
    filters->addWidget(m_stateFilter);

    m_tree = new QTreeWidget(this);
    m_tree->setColumnCount(3);
    m_tree->setHeaderLabels({
        i18n("System"),
        i18n("Implementation"),
        i18n("Requirement")
    });
    m_tree->setAlternatingRowColors(true);
    m_tree->setRootIsDecorated(true);
    m_tree->setUniformRowHeights(true);
    m_tree->setAccessibleName(i18n("Field Lab implementation scaffold"));
    m_tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_tree->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_tree->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    layout->addWidget(intro);
    layout->addWidget(contracts);
    layout->addLayout(filters);
    layout->addWidget(m_tree, 1);

    populateTree();

    connect(
        m_search,
        &QLineEdit::textChanged,
        this,
        [this](const QString &) {
            applyFilter();
        });

    connect(
        m_stateFilter,
        qOverload<int>(&QComboBox::currentIndexChanged),
        this,
        [this](int) {
            applyFilter();
        });
}

void FieldCapabilityView::populateTree()
{
    static const QVector<FieldCapabilityArea> areas {
        FieldCapabilityArea::Product,
        FieldCapabilityArea::Platform,
        FieldCapabilityArea::ArtistWorkflow,
        FieldCapabilityArea::SemanticCore,
        FieldCapabilityArea::FieldProcessing,
        FieldCapabilityArea::Geometry,
        FieldCapabilityArea::RasterIntegration,
        FieldCapabilityArea::OptionalBackend
    };

    for (FieldCapabilityArea area : areas) {
        QTreeWidgetItem *group = new QTreeWidgetItem(m_tree);
        group->setText(0, areaLabel(area));
        group->setFirstColumnSpanned(true);
        QFont groupFont = group->font(0);
        groupFont.setBold(true);
        group->setFont(0, groupFont);

        for (const FieldCapabilityDescriptor &descriptor :
             FieldCapabilityCatalog::all()) {
            if (descriptor.area != area) {
                continue;
            }

            const QString state =
                requirementStateLabel(descriptor.requirementState);
            const QString stage =
                implementationStageLabel(descriptor.implementationStage);

            QTreeWidgetItem *item = new QTreeWidgetItem(group);
            item->setText(0, descriptor.displayName);
            item->setText(1, stage);
            item->setText(2, descriptor.requirementId);
            item->setData(
                0,
                RequirementStateRole,
                int(descriptor.requirementState));
            item->setData(
                0,
                SearchTextRole,
                QStringLiteral("%1 %2 %3 %4 %5")
                    .arg(
                        descriptor.displayName,
                        descriptor.requirementId,
                        descriptor.capabilityId,
                        state,
                        stage));
            item->setToolTip(
                0,
                i18n(
                    "Roadmap state: %1\nImplementation: %2\nStable ID: %3",
                    state,
                    stage,
                    descriptor.capabilityId));
        }

        group->setExpanded(true);
    }
}

void FieldCapabilityView::applyFilter()
{
    const QString query = m_search->text().trimmed();
    const int selectedState = m_stateFilter->currentData().toInt();

    for (int groupIndex = 0;
         groupIndex < m_tree->topLevelItemCount();
         ++groupIndex) {
        QTreeWidgetItem *group = m_tree->topLevelItem(groupIndex);
        int visibleChildren = 0;

        for (int childIndex = 0;
             childIndex < group->childCount();
             ++childIndex) {
            QTreeWidgetItem *item = group->child(childIndex);
            const bool stateMatches =
                selectedState < 0 ||
                item->data(0, RequirementStateRole).toInt() == selectedState;
            const bool searchMatches =
                query.isEmpty() ||
                item->data(0, SearchTextRole)
                    .toString()
                    .contains(query, Qt::CaseInsensitive);
            const bool visible = stateMatches && searchMatches;

            item->setHidden(!visible);
            visibleChildren += visible ? 1 : 0;
        }

        group->setHidden(visibleChildren == 0);
    }
}
