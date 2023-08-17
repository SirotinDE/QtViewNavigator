project(ru.auroraos.QtViewNavigator CXX)
cmake_minimum_required(VERSION 3.5)

find_package (Qt5 COMPONENTS Core Network Qml Gui Quick LinguistTools REQUIRED)

include(FindPkgConfig)
pkg_search_module(AURORA auroraapp REQUIRED)
pkg_search_module(AURORA auroraapp_i18n REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)


set(short_name QtViewNavigator)

FILE(GLOB TsFiles "translations/*.ts")
qt5_add_translation(QmFiles ${TsFiles})

add_executable(ru.auroraos.QtViewNavigator
    src/main.cpp
    src/viewnavigator.h src/viewnavigator.cpp
    src/viewmodelfacility.h src/viewmodelfacility.cpp
    src/viewmodels/loginvm.h src/viewmodels/loginvm.cpp
    src/enums/enum_pages.h
    ${QmFiles})

target_compile_definitions(ru.auroraos.QtViewNavigator PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
target_include_directories(ru.auroraos.QtViewNavigator PRIVATE
    $<BUILD_INTERFACE:
    ${AURORA_INCLUDE_DIRS}
>)
target_link_libraries(ru.auroraos.QtViewNavigator
    Qt5::Quick
    ${AURORA_LDFLAGS}
)

install(TARGETS ru.auroraos.QtViewNavigator
    RUNTIME DESTINATION bin
)
install(DIRECTORY qml
    DESTINATION share/ru.auroraos.QtViewNavigator
)

foreach(_file IN LISTS QmFiles)
    get_filename_component(_filename "${_file}" NAME)
    string(REPLACE "${short_name}" "${PROJECT_NAME}" _full_filename "${_filename}")
    install(FILES ${_file} DESTINATION share/ru.auroraos.QtViewNavigator/translations RENAME ${_full_filename})
endforeach()

install(FILES ru.auroraos.QtViewNavigator.desktop
    DESTINATION share/applications
)
install(FILES icons/86x86/ru.auroraos.QtViewNavigator.png
    DESTINATION share/icons/hicolor/86x86/apps
)
install(FILES icons/108x108/ru.auroraos.QtViewNavigator.png
    DESTINATION share/icons/hicolor/108x108/apps
)
install(FILES icons/128x128/ru.auroraos.QtViewNavigator.png
    DESTINATION share/icons/hicolor/128x128/apps
)
install(FILES icons/172x172/ru.auroraos.QtViewNavigator.png
    DESTINATION share/icons/hicolor/172x172/apps
)

# Get the other files reachable from the project tree in Qt Creator
FILE(GLOB TsFiles "translations/*.ts")
add_custom_target(distfiles
    SOURCES
        AUTHORS.md
        CODE_OF_CONDUCT.md
        CONTRIBUTING.md
        LICENSE.BSD-3-CLAUSE.md
        README.md
        ru.auroraos.QtViewNavigator.desktop
        qml/QtViewNavigator.qml
        qml/cover/DefaultCoverPage.qml
        qml/pages/MainPage.qml
        qml/pages/LoginPage.qml
        rpm/ru.auroraos.QtViewNavigator.spec
        rpm/ru.auroraos.QtViewNavigator.changes.in
        rpm/ru.auroraos.QtViewNavigator.changes.run.in
        ${TsFiles})

file(WRITE "${CMAKE_BINARY_DIR}/QtCreatorDeployment.txt"
    "${CMAKE_INSTALL_PREFIX}
${CMAKE_BINARY_DIR}/ru.auroraos.QtViewNavigator:bin
")

