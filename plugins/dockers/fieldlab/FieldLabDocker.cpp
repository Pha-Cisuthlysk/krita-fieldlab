/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldLabDocker.h"

#include "FieldCapabilityCatalog.h"
#include "FieldCapabilityView.h"
#include "FieldDataTypes.h"
#include "FieldGraph.h"
#include "FieldGraphEvaluator.h"
#include "FieldGraphValidator.h"
#include "NodeDescriptor.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QFormLayout>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QSizePolicy>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QWidget>

#include <cmath>

#include <klocalizedstring.h>

FieldLabDocker::FieldLabDocker(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(i18n("Field Lab"));

    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);

    QLabel *title = new QLabel(
        i18n("Field Lab Workspace"),
        contents);

    title->setWordWrap(true);

    const QVector<NodeDescriptor> descriptors =
        NodeDescriptor::builtInScalarNodes();

    QLabel *catalog = new QLabel(
        i18n("Built-in node descriptors: %1",
             descriptors.size()),
        contents);

    catalog->setWordWrap(true);

    const QVector<FieldCapabilityDescriptor> &capabilities =
        FieldCapabilityCatalog::all();

    QLabel *scaffold = new QLabel(
        i18n(
            "Semantic scaffold: %1 tracked families\n"
            "Core interchange types: %2\n"
            "Roadmap: %3 active + %4 dependent | %5 deferred | %6 rejected\n"
            "Protected near-term: %7 retained",
            capabilities.size(),
            fieldCoreDataKinds().size(),
            FieldCapabilityCatalog::count(FieldRequirementState::Active),
            FieldCapabilityCatalog::count(FieldRequirementState::Dependent),
            FieldCapabilityCatalog::count(FieldRequirementState::Deferred),
            FieldCapabilityCatalog::count(FieldRequirementState::Rejected),
            FieldCapabilityCatalog::protectedNearTermCount()),
        contents);

    scaffold->setWordWrap(true);

    QTabWidget *workspace = new QTabWidget(contents);
    QWidget *previewPage = new QWidget(workspace);
    QVBoxLayout *previewLayout = new QVBoxLayout(previewPage);

    QFormLayout *form = new QFormLayout();

    m_inputA = new QDoubleSpinBox(previewPage);
    m_inputA->setRange(-1000000.0, 1000000.0);
    m_inputA->setDecimals(4);
    m_inputA->setValue(4.0);

    m_inputB = new QDoubleSpinBox(previewPage);
    m_inputB->setRange(-1000000.0, 1000000.0);
    m_inputB->setDecimals(4);
    m_inputB->setValue(3.0);

    m_operation = new QComboBox(previewPage);
    m_operation->addItem(
        i18n("Multiply"),
        QStringLiteral("fieldlab.multiply"));
    m_operation->addItem(
        i18n("Add"),
        QStringLiteral("fieldlab.add"));

    form->addRow(i18n("A:"), m_inputA);
    form->addRow(i18n("B:"), m_inputB);
    form->addRow(i18n("Operation:"), m_operation);

    QLabel *previewTitle = new QLabel(
        i18n("2D grayscale preview"),
        previewPage);

    previewTitle->setWordWrap(true);

    m_preview = new QLabel(
        i18n("Preview updates automatically."),
        previewPage);

    m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setFrameShape(QFrame::StyledPanel);
    m_preview->setMinimumSize(192, 192);
    m_preview->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding);

    m_result = new QLabel(
        i18n("Adjust the controls to evaluate the graph."),
        previewPage);

    m_result->setWordWrap(true);

    connect(
        m_inputA,
        qOverload<double>(&QDoubleSpinBox::valueChanged),
        this,
        [this](double) {
            refreshGraphPreview();
        });

    connect(
        m_inputB,
        qOverload<double>(&QDoubleSpinBox::valueChanged),
        this,
        [this](double) {
            refreshGraphPreview();
        });

    connect(
        m_operation,
        qOverload<int>(&QComboBox::currentIndexChanged),
        this,
        [this](int) {
            refreshGraphPreview();
        });

    previewLayout->addLayout(form);
    previewLayout->addWidget(previewTitle);
    previewLayout->addWidget(m_preview, 1);
    previewLayout->addWidget(m_result);

    workspace->addTab(previewPage, i18n("Preview"));
    workspace->addTab(
        new FieldCapabilityView(workspace),
        i18n("Systems"));

    layout->addWidget(title);
    layout->addWidget(catalog);
    layout->addWidget(scaffold);
    layout->addWidget(workspace, 1);

    setWidget(contents);

    refreshGraphPreview();
}

FieldLabDocker::~FieldLabDocker() = default;

int FieldLabDocker::buildPreviewGraph(FieldGraph &graph) const
{
    const int inputA = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {
            {
                QStringLiteral("value"),
                m_inputA->value()
            }
        });

    const int inputB = graph.addNode(
        QStringLiteral("fieldlab.constant"),
        {
            {
                QStringLiteral("value"),
                m_inputB->value()
            }
        });

    const int sampleX =
        graph.addNode(QStringLiteral("fieldlab.position_x"));

    const int sampleY =
        graph.addNode(QStringLiteral("fieldlab.position_y"));

    const int scaledX =
        graph.addNode(QStringLiteral("fieldlab.multiply"));

    graph.connectNodes(
        inputA,
        QStringLiteral("value"),
        scaledX,
        QStringLiteral("a"));

    graph.connectNodes(
        sampleX,
        QStringLiteral("value"),
        scaledX,
        QStringLiteral("b"));

    const int scaledY =
        graph.addNode(QStringLiteral("fieldlab.multiply"));

    graph.connectNodes(
        inputB,
        QStringLiteral("value"),
        scaledY,
        QStringLiteral("a"));

    graph.connectNodes(
        sampleY,
        QStringLiteral("value"),
        scaledY,
        QStringLiteral("b"));

    const QString operationType =
        m_operation->currentData().toString();

    const int operation =
        graph.addNode(operationType);

    graph.connectNodes(
        scaledX,
        QStringLiteral("value"),
        operation,
        QStringLiteral("a"));

    graph.connectNodes(
        scaledY,
        QStringLiteral("value"),
        operation,
        QStringLiteral("b"));

    return operation;
}

QImage FieldLabDocker::renderPreview(
    const FieldGraph &graph,
    int outputNodeId,
    QString *error) const
{
    constexpr int previewSize = 128;

    const FieldGridEvaluationResult sampling =
        FieldGraphEvaluator().evaluateGrid(
            graph,
            outputNodeId,
            previewSize,
            previewSize);

    if (!sampling.ok) {
        if (error) {
            *error = sampling.error;
        }

        return QImage();
    }

    QImage preview(
        sampling.grid.width,
        sampling.grid.height,
        QImage::Format_Grayscale8);

    const double range =
        sampling.grid.maximum - sampling.grid.minimum;
    int sampleIndex = 0;

    for (int y = 0; y < sampling.grid.height; ++y) {
        uchar *scanLine = preview.scanLine(y);

        for (int x = 0; x < sampling.grid.width; ++x) {
            const double value =
                sampling.grid.values.at(sampleIndex++);

            const int gray =
                std::abs(range) < 1e-9
                    ? 127
                    : qBound(
                        0,
                        int(std::lround(
                            ((value - sampling.grid.minimum) / range) *
                                255.0)),
                        255);

            scanLine[x] = uchar(gray);
        }
    }

    return preview;
}

void FieldLabDocker::refreshGraphPreview()
{
    FieldGraph graph;
    const int outputNodeId =
        buildPreviewGraph(graph);

    const FieldGraphValidationResult validation =
        FieldGraphValidator().validate(graph);

    if (!validation.isValid()) {
        m_preview->clear();
        m_preview->setText(i18n("Preview unavailable."));

        m_result->setText(
            i18n("Graph error: %1", validation.errors.first()));

        return;
    }

    FieldGraphEvaluator evaluator;

    const FieldBatchEvaluationResult result =
        evaluator.evaluatePositions(
            graph,
            outputNodeId,
            {{
                0.5,
                0.5
            }});

    if (!result.ok) {
        m_preview->clear();
        m_preview->setText(i18n("Preview unavailable."));

        m_result->setText(
            i18n("Graph error: %1", result.error));

        return;
    }

    QString previewError;
    const QImage preview =
        renderPreview(
            graph,
            outputNodeId,
            &previewError);

    if (preview.isNull()) {
        m_preview->clear();
        m_preview->setText(i18n("Preview unavailable."));

        m_result->setText(
            i18n("Graph error: %1", previewError));

        return;
    }

    m_preview->setPixmap(
        QPixmap::fromImage(preview).scaled(
            192,
            192,
            Qt::KeepAspectRatio,
            Qt::FastTransformation));

    const QString operationName =
        m_operation->currentText();

    m_result->setText(
        i18n(
            "Auto preview formula: %1(A*x, B*y)\n"
            "Center sample (x=0.5, y=0.5): %2\n"
            "Nodes: %3   Connections: %4",
            operationName,
            QString::number(result.values.first(), 'f', 4),
            graph.nodes().size(),
            graph.connections().size()));
}
