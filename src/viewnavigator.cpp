#include "viewnavigator.h"

ViewNavigator::ViewNavigator(QObject *parent)
    :QObject(parent)
{

}

void ViewNavigator::setViewModel(Pages::EnPages enPage, ViewModelFacility &&factory)
{
    m_viewModelsFacilities.insert(enPage, std::move(factory));
}


QObject *ViewNavigator::getViewModel(int enPage, const QString &qmlObjectName)
{
    QObject * answer = nullptr;

    auto qmlObjectsIter = m_qmlObjectViewModels.find(qmlObjectName);

    //if qmlObject not in m_qmlObjectViewModels, create needed viewModel
    if(qmlObjectsIter == m_qmlObjectViewModels.end()){
        QPointer<QObject> viewModel = createViewModel(enPage);

        if(viewModel){
            answer = viewModel.data();
            m_qmlObjectViewModels.insert(qmlObjectName, {{enPage, viewModel}});
        }

    }else{
        //check existance of ViewModel
        auto& qmlObjectViewModels = qmlObjectsIter.value();
        auto viewModelIter = qmlObjectViewModels.find(enPage);

        if(viewModelIter != qmlObjectViewModels.end()){
            answer = viewModelIter.value().data();
        }else{
            QPointer<QObject> viewModel = createViewModel(enPage);

            if(viewModel){
                answer = viewModel.data();
                qmlObjectViewModels.insert(enPage, viewModel);
            }
        }
    }

    return answer;
}

void ViewNavigator::eraseQmlObject(const QString &qmlObjectName)
{
    auto qmlObjectViewModels = m_qmlObjectViewModels.find(qmlObjectName);

    if(qmlObjectViewModels != m_qmlObjectViewModels.end()){
        const QHash<Pages::EnPages, QPointer<QObject>>& viewModels = qmlObjectViewModels.value();

        auto viewModelsIter = viewModels.begin();

        for(; viewModelsIter != viewModels.end(); viewModelsIter++){
            Pages::EnPages enPage = viewModelsIter.key();
            auto facility = m_viewModelsFacilities.find(enPage);

            if(facility != m_viewModelsFacilities.end()){

                if(facility->deleteViewModel){

                    auto& pViewModel = qmlObjectViewModels.value()[enPage];

                    if(pViewModel){
                        facility->deleteViewModel(pViewModel);

                        if(pViewModel){
                            pViewModel.clear();
                        }
                    }
                }
            }
        }

        m_qmlObjectViewModels.erase(qmlObjectViewModels);
    }
}

QPointer<QObject> ViewNavigator::createViewModel(Pages::EnPages enPage)
{
    QPointer<QObject> answer = nullptr;
    auto facilityIter = m_viewModelsFacilities.find(enPage);
    //if have facility
    if(facilityIter != m_viewModelsFacilities.end()){
        //create viewModel for qmlObject
        answer = facilityIter.value().createViewModel();
    }

    return answer;
}
