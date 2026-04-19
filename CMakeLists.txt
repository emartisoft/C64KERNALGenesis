cmake_minimum_required(VERSION 3.19)
project(C64KERNALGenesis LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(C64KERNALGenesis
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    colorcombobox.h colorcombobox.cpp
    coloritemdelegate.h coloritemdelegate.cpp
    cardwidget.h cardwidget.cpp
    cardlistwidget.h cardlistwidget.cpp
    detailpage.h detailpage.cpp
    carditem.h
    pictures.qrc
    app.rc
    gifwidget.h
    singleapplication.cpp singleapplication.h
    modules.h
    paths.h paths.cpp
    BouncingSprite.cpp BouncingSprite.h
    advancedsettingsdialog.h advancedsettingsdialog.cpp advancedsettingsdialog.ui
    jiffydoslogosettings.h jiffydoslogosettings.cpp jiffydoslogosettings.ui
    commodorelogosettings.h commodorelogosettings.cpp commodorelogosettings.ui
    commodore64logosettings.h commodore64logosettings.cpp commodore64logosettings.ui
    changecolor.h
    ultimatesettings.h ultimatesettings.cpp ultimatesettings.ui
    commodoretextsettings.h commodoretextsettings.cpp commodoretextsettings.ui
    about.h about.cpp about.ui
    horizontalcolorbarssettings.h horizontalcolorbarssettings.cpp horizontalcolorbarssettings.ui
    splashscreen.h splashscreen.cpp
)

include(GNUInstallDirs)

install(TARGETS C64KERNALGenesis
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET C64KERNALGenesis
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# Build sonrası klasörü kopyala
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/modules"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/modules"
)

add_library(patch STATIC IMPORTED)
add_library(gen_license STATIC IMPORTED)

set_target_properties(patch PROPERTIES
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG;MINSIZEREL"
    IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/Release/libpatch.a"
    IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/Debug/libpatch.a"
    IMPORTED_LOCATION_MINSIZREL "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/Minimum-Size-Release/libpatch.a"
)

set_target_properties(gen_license PROPERTIES
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG;MINSIZEREL"
    IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/Release/libpatch_license.a"
    IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/Debug/libpatch_license.a"
    IMPORTED_LOCATION_MINSIZREL "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/Minimum-Size-Release/libpatch_license.a"
)

target_include_directories(C64KERNALGenesis
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/patch
        ${CMAKE_CURRENT_SOURCE_DIR}/gen_license
)

target_link_libraries(C64KERNALGenesis
    PRIVATE
        Qt::Core
        Qt::Widgets
        patch
        gen_license
)