/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldLabDocker.h"

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
#include <QVBoxLayout>
#include <QWidget>

#include <algorithm>
#include <cmath>

#include <klocalizedstring.h>

FieldLabDocker::FieldLabDocker(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(i18n("Field Lab"));

    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);

    QLabel *title = new QLabel(
        i18n("Field Lab Graph Preview"),
        contents);

    title->setWordWrap(true);

    const QVector<NodeDescriptor> descriptors =
        NodeDescriptor::builtInScalarNodes();

    QLabel *catalog = new QLabel(
        i18n("Built-in node descriptors: %1",
             descriptors.size()),
        contents);

    catalog->setWordWrap(true);

    QFormLayout *form = new QFormLayout();

    m_inputA = new QDoubleSpinBox(contents);
    m_inputA->setRange(-1000000.0, 1000000.0);
    m_inputA->setDecimals(4);
    m_inputA->setValue(4.0);

    m_inputB = new QDoubleSpinBox(contents);
    m_inputB->setRange(-1000000.0, 1000000.0);
    m_inputB->setDecimals(4);
    m_inputB->setValue(3.0);

    m_operation = new QComboBox(contents);
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
        contents);

    previewTitle->setWordWrap(true);

    m_preview = new QLabel(
        i18n("Preview updates automatically."),
        contents);

    m_preview->setAlignment(Qt::AlignCenter);
    m_preview->setFrameShape(QFrame::StyledPanel);
    m_preview->setMinimumSize(192, 192);
    m_preview->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding);

    m_result = new QLabel(
        i18n("Adjust the controls to evaluate the graph."),
        contents);

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

    layout->addWidget(title);
    layout->addWidget(catalog);
    layout->addLayout(form);
    layout->addWidget(previewTitle);
    layout->addWidget(m_preview);
    layout->addWidget(m_result);
    layout->addStretch();

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

    FieldGraphEvaluator evaluator;
    QVector<double> samples;

    samples.reserve(previewSize * previewSize);

    double minValue = 0.0;
    double maxValue = 0.0;
    bool hasSample = false;

    for (int y = 0; y < previewSize; ++y) {
        for (int x = 0; x < previewSize; ++x) {
            const FieldEvaluationContext context {
                previewSize > 1
                    ? double(x) / double(previewSize - 1)
                    : 0.0,
                previewSize > 1
                    ? double(y) / double(previewSize - 1)
                    : 0.0
            };

            const FieldEvaluationResult result =
                evaluator.evaluateScalar(
                    graph,
                    outputNodeId,
                    context);

            if (!result.ok) {
                if (error) {
                    *error = result.error;
                }

                return QImage();
            }

            samples.append(result.value);

            if (!hasSample) {
                minValue = result.value;
                maxValue = result.value;
                hasSample = true;
            } else {
                minValue = std::min(minValue, result.value);
                maxValue = std::max(maxValue, result.value);
            }
        }
    }

    QImage preview(
        previewSize,
        previewSize,
        QImage::Format_Grayscale8);

    const double range = maxValue - minValue;
    int sampleIndex = 0;

    for (int y = 0; y < previewSize; ++y) {
        uchar *scanLine = preview.scanLine(y);

        for (int x = 0; x < previewSize; ++x) {
            const double value = samples.at(sampleIndex++);

            const int gray =
                std::abs(range) < 1e-9
                    ? 127
                    : qBound(
                        0,
                        int(std::lround(
                            ((value - minValue) / range) * 255.0)),
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

    const FieldEvaluationResult result =
        evaluator.evaluateScalar(
            graph,
            outputNodeId,
            {
                0.5,
                0.5
            });

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
            QString::number(result.value, 'f', 4),
            graph.nodes().size(),
            graph.connections().size()));
}
