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

    NodeDescriptor positionX;
    positionX.typeId = QStringLiteral("fieldlab.position_x");
    positionX.displayName = QStringLiteral("Position X");
    positionX.category = QStringLiteral("Input");
    positionX.outputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Output
    });
    descriptors.append(positionX);

    NodeDescriptor positionY;
    positionY.typeId = QStringLiteral("fieldlab.position_y");
    positionY.displayName = QStringLiteral("Position Y");
    positionY.category = QStringLiteral("Input");
    positionY.outputs.append({
        QStringLiteral("value"),
        QStringLiteral("Value"),
        FieldValueType::Scalar,
        FieldPortDirection::Output
    });
    descriptors.append(positionY);

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
