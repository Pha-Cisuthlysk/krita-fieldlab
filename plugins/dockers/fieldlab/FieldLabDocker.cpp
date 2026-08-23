/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "FieldLabDocker.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include <klocalizedstring.h>

FieldLabDocker::FieldLabDocker(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(i18n("Field Lab"));

    QWidget *contents = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(contents);

    QLabel *title = new QLabel(i18n("Field Lab"), contents);

    QLabel *status = new QLabel(
        i18n("Procedural field graph engine initialized.\n"
             "Next: graph model, preview, and FastNoise2."),
        contents);

    status->setWordWrap(true);

    layout->addWidget(title);
    layout->addWidget(status);
    layout->addStretch();

    setWidget(contents);
}

FieldLabDocker::~FieldLabDocker() = default;
