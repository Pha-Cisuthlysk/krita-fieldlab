/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_DOCKER_H
#define FIELDLAB_DOCKER_H

#include <QDockWidget>

class FieldLabDocker : public QDockWidget
{
    Q_OBJECT

public:
    explicit FieldLabDocker(QWidget *parent = nullptr);
    ~FieldLabDocker() override;
};

#endif
