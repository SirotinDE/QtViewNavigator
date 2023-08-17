#pragma once

#include <QObject>
#include <functional>
#include <QPointer>


struct ViewModelFacility{
public:
    ViewModelFacility(std::function<QPointer<QObject>()> createViewModel,
                      std::function<void(QPointer<QObject>)> deleteViewModel = nullptr);

    std::function<QPointer<QObject>()>      createViewModel;
    std::function<void(QPointer<QObject>)>  deleteViewModel = nullptr;
};
