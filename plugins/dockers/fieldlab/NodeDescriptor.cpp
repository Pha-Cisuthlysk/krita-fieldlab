/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "NodeDescriptor.h"

QVector<NodeDescriptor> NodeDescriptor::builtInScalarNodes()
{
    QVector<NodeDescriptor> descriptors;

    NodeDescriptor constant;
    constant.typeId = QStringLiteral("fieldlab.constant");
    constant.displayName = QStringLiteral("Constant");
    constant.category = QStringLiteral("Scalar");
    constant.outputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Output
    });
    descriptors.append(constant);

    NodeDescriptor add;
    add.typeId = QStringLiteral("fieldlab.add");
    add.displayName = QStringLiteral("Add");
    add.category = QStringLiteral("Math");
    add.inputs.append({
        QStringLiteral("a"),
        QStringLiteral("A"),
        FieldValueType::Scalar,
        FieldPortDirection::Input
    });
    add.inputs.append({
        QStringLiteral("b"),
        QStringLiteral("B"),
        FieldValueType::Scalar,
        FieldPortDirection::Input
    });
    add.outputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Output
    });
    descriptors.append(add);

    NodeDescriptor multiply;
    multiply.typeId = QStringLiteral("fieldlab.multiply");
    multiply.displayName = QStringLiteral("Multiply");
    multiply.category = QStringLiteral("Math");
    multiply.inputs.append({
        QStringLiteral("a"),
        QStringLiteral("A"),
        FieldValueType::Scalar,
        FieldPortDirection::Input
    });
    multiply.inputs.append({
        QStringLiteral("b"),
        QStringLiteral("B"),
        FieldValueType::Scalar,
        FieldPortDirection::Input
    });
    multiply.outputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Output
    });
    descriptors.append(multiply);

    return descriptors;
}