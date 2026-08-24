/*
 * SPDX-FileCopyrightText: 2026 Pha-Cisuthlysk
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef FIELDLAB_FIELD_CAPABILITY_VIEW_H
#define FIELDLAB_FIELD_CAPABILITY_VIEW_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class QTreeWidget;

class FieldCapabilityView : public QWidget
{
public:
    explicit FieldCapabilityView(QWidget *parent = nullptr);

private:
    void populateTree();
    void applyFilter();

    QLineEdit *m_search {nullptr};
    QComboBox *m_stateFilter {nullptr};
    QTreeWidget *m_tree {nullptr};
};

#endif
