/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_DOCKER_H
#define FIELDLAB_DOCKER_H

#include <QDockWidget>

class QComboBox;
class QDoubleSpinBox;
class QImage;
class QLabel;
class FieldGraph;

class FieldLabDocker : public QDockWidget
{
    Q_OBJECT

public:
    explicit FieldLabDocker(QWidget *parent = nullptr);
    ~FieldLabDocker() override;

private:
    void refreshGraphPreview();
    int buildPreviewGraph(FieldGraph &graph) const;
    QImage renderPreview(
        const FieldGraph &graph,
        int outputNodeId,
        QString *error = nullptr) const;

    QDoubleSpinBox *m_inputA {nullptr};
    QDoubleSpinBox *m_inputB {nullptr};
    QComboBox *m_operation {nullptr};
    QLabel *m_preview {nullptr};
    QLabel *m_result {nullptr};
};

#endif
