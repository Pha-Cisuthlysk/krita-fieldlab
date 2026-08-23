/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldLabDocker.h"

#include "FieldGraph.h"
#include "FieldGraphEvaluator.h"
#include "NodeDescriptor.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <klocalizedstring.h>

FieldLabDocker::FieldLabDocker(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(i18n("Field Lab"));

    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);

    QLabel *title = new QLabel(
        i18n("Field Lab Graph Test"),
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

    QPushButton *evaluateButton =
        new QPushButton(
            i18n("Evaluate Graph"),
            contents);

    m_result = new QLabel(
        i18n("Change the values and evaluate the graph."),
        contents);

    m_result->setWordWrap(true);

    connect(
        evaluateButton,
        &QPushButton::clicked,
        this,
        [this]() {
            evaluateGraphTest();
        });

    layout->addWidget(title);
    layout->addWidget(catalog);
    layout->addLayout(form);
    layout->addWidget(evaluateButton);
    layout->addWidget(m_result);
    layout->addStretch();

    setWidget(contents);

    evaluateGraphTest();
}

FieldLabDocker::~FieldLabDocker() = default;

void FieldLabDocker::evaluateGraphTest()
{
    FieldGraph graph;

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

    const QString operationType =
        m_operation->currentData().toString();

    const int operation =
        graph.addNode(operationType);

    graph.connectNodes(
        inputA,
        QStringLiteral("value"),
        operation,
        QStringLiteral("a"));

    graph.connectNodes(
        inputB,
        QStringLiteral("value"),
        operation,
        QStringLiteral("b"));

    FieldGraphEvaluator evaluator;

    const FieldEvaluationResult result =
        evaluator.evaluateScalar(
            graph,
            operation);

    if (!result.ok) {
        m_result->setText(
            i18n("Graph error: %1", result.error));

        return;
    }

    const QString operationName =
        m_operation->currentText();

    m_result->setText(
        i18n(
            "%1(%2, %3) = %4\n"
            "Nodes: %5   Connections: %6",
            operationName,
            QString::number(m_inputA->value()),
            QString::number(m_inputB->value()),
            QString::number(result.value),
            graph.nodes().size(),
            graph.connections().size()));
}