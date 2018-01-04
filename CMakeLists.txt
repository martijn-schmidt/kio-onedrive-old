cmake_minimum_required(VERSION 3.0)

set(ONEDRIVE_VERSION 1.2.70)
project(kio-onedrive VERSION ${ONEDRIVE_VERSION})

set(QT_MIN_VERSION 5.2.0)
set(KF5_MIN_VERSION 5.31.0)
set(KMGRAPH_MIN_VERSION 5.5.0)
set(KACCOUNTS_MIN_VERSION 17.04.0)
set(QTKEYCHAIN_MIN_VERSION 0.6.0)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Gui
    Network
    Widgets)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" ${ECM_MODULE_PATH})

include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMSetupVersion)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    DocTools
    KIO)

find_package(KPimMGraph ${KMGRAPH_MIN_VERSION} REQUIRED)

set(WITH_ACCOUNTMANAGER KACCOUNTS CACHE STRING "Choose the AccountManager backend for KIO-OneDrive.")
set_property(CACHE WITH_ACCOUNTMANAGER PROPERTY STRINGS KACCOUNTS)

if(WITH_ACCOUNTMANAGER STREQUAL "KACCOUNTS")
    find_package(KAccounts ${KACCOUNTS_MIN_VERSION} REQUIRED)
    set_package_properties(KAccounts PROPERTIES
        URL "https://commits.kde.org/kaccounts-integration"
        PURPOSE "Enables integration with system-wide accounts through the KAccounts backend.")
    message(STATUS "Building the KAccounts backend.")
else()
    message(FATAL_ERROR "FATAL: No AccountManager backend selected!")
endif()

find_package(Qt5Test QUIET)
set_package_properties(Qt5Test PROPERTIES
    TYPE OPTIONAL
    PURPOSE "Required for building tests.")

if(NOT Qt5Test_FOUND)
   set(BUILD_TESTING OFF CACHE BOOL "Build the testing tree.")
endif()

ecm_setup_version(PROJECT
    VARIABLE_PREFIX ONEDRIVE
    VERSION_HEADER onedriveversion.h)

add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_definitions(-DQT_STRICT_ITERATORS)
add_definitions(-DTRANSLATION_DOMAIN=\"kio5_onedrive\")

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
add_subdirectory(desktop)
add_subdirectory(doc)
add_subdirectory(src)

if (KAccounts_FOUND)
    add_subdirectory(kaccounts)
endif()


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
