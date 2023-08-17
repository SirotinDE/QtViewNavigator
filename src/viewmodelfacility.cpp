#include "viewmodelfacility.h"
#include <stdexcept>

ViewModelFacility::ViewModelFacility(std::function<QPointer<QObject> ()> createViewModel,
                                     std::function<void (QPointer<QObject>)> deleteViewModel)
    : createViewModel(createViewModel)
    , deleteViewModel(deleteViewModel)
{
    if(!createViewModel){
        throw std::runtime_error(   "ViewModelFacility::ViewModelFacility "
                                    "std::function<QPointer<QObject> ()> createViewModel is empty");
    }
}
