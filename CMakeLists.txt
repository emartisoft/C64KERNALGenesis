cmake_minimum_required(VERSION 3.19)
project(C64KERNALGenesis LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.11 REQUIRED COMPONENTS Core Widgets)

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

if(APPLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/modules"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/modules"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/modules"
    )
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/modules"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/modules"
    )
endif()

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE c64kernalgenesis.icns)

    set_source_files_properties(${CMAKE_SOURCE_DIR}/c64kernalgenesis.icns
        PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/c64kernalgenesis.icns)
endif()

# --- Patch library ---
add_library(patch STATIC IMPORTED)

set_target_properties(patch PROPERTIES
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG;MINSIZEREL"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/patch/include"
)

# --- Patch lib paths ---
if(WIN32)
    set_target_properties(patch PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/windows/Release/libpatch.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/windows/Debug/libpatch.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/windows/Minimum-Size-Release/libpatch.a"
    )
elseif(APPLE)
    set_target_properties(patch PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/macos/Release/libpatch.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/macos/Debug/libpatch.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/macos/Minimum-Size-Release/libpatch.a"
    )
elseif(UNIX)
    set_target_properties(patch PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/linux/Release/libpatch.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/linux/Debug/libpatch.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/patch/lib/linux/Minimum-Size-Release/libpatch.a"
    )
endif()

# --- gen_license library ---
add_library(gen_license STATIC IMPORTED)

set_target_properties(gen_license PROPERTIES
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG;MINSIZEREL"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/include"
)

# --- gen_license lib paths ---
if(WIN32)
    set_target_properties(gen_license PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/windows/Release/libpatch_license.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/windows/Debug/libpatch_license.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/windows/Minimum-Size-Release/libpatch_license.a"
    )
elseif(APPLE)
    set_target_properties(gen_license PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/macos/Release/libpatch_license.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/macos/Debug/libpatch_license.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/macos/Minimum-Size-Release/libpatch_license.a"
    )
elseif(UNIX)
    set_target_properties(gen_license PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/linux/Release/libpatch_license.a"
        IMPORTED_LOCATION_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/linux/Debug/libpatch_license.a"
        IMPORTED_LOCATION_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/gen_license/lib/linux/Minimum-Size-Release/libpatch_license.a"
    )
endif()

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
