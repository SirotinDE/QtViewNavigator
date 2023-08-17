#pragma once

#include <QObject>
#include <functional>
#include <unordered_map>
#include <QHash>
#include <QSet>
#include <QSharedPointer>
#include <QPointer>
#include "viewmodelfacility.h"
#include "enums/enum_pages.h"

class ViewNavigator : public QObject
{
    Q_OBJECT

public:
    ViewNavigator(QObject *parent = nullptr);
    void setViewModel(Pages::EnPages enPage, ViewModelFacility&& factory);

public slots:
    QObject* getViewModel(int enPage, const QString& qmlObjectName);
    void eraseQmlObject(const QString& qmlObjectName);

private:
    QHash<Pages::EnPages, ViewModelFacility>            m_viewModelsFacilities;
    QHash<QString, QHash<Pages::EnPages, QPointer<QObject>>>   m_qmlObjectViewModels;

    QPointer<QObject> createViewModel(Pages::EnPages enPage);
};


