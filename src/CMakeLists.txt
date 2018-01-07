include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

set(kio_onedrive_SRCS
    kio_onedrive.cpp
    pathcache.cpp
    abstractaccountmanager.cpp
    onedrivehelper.cpp
    onedriveurl.cpp
    debug.cpp)

if (KAccounts_FOUND)
    set(BACKEND_SRC kaccountsmanager.cpp)
    set(BACKEND_HEADER kaccountsmanager.h)
    set(BACKEND_CLASSNAME KAccountsManager)
    set(BACKEND_LIBS KAccounts)
else()
    message(FATAL_ERROR "FATAL: No AccountManager backend selected!")
endif()

set(kio_onedrive_SRCS ${kio_onedrive_SRCS} ${BACKEND_SRC})
configure_file(onedrivebackend.h.in ${CMAKE_CURRENT_BINARY_DIR}/onedrivebackend.h)

ecm_qt_declare_logging_category(kio_onedrive_SRCS
    HEADER onedrivedebug.h
    IDENTIFIER ONEDRIVE
    CATEGORY_NAME kf5.kio.onedrive)

kcoreaddons_add_plugin(kio_onedrive
    SOURCES ${kio_onedrive_SRCS}
    INSTALL_NAMESPACE kf5/kio)

target_link_libraries(kio_onedrive
    Qt5::Core
    Qt5::Network
    KPim::MGraphCore
    KPim::MGraphOneDrive
    KF5::KIOCore
    KF5::KIOWidgets
    KF5::I18n
    ${BACKEND_LIBS})

set_target_properties(kio_onedrive PROPERTIES OUTPUT_NAME "onedrive")
