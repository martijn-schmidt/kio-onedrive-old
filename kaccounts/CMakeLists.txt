find_package(KF5Notifications ${KF5_MIN_VERSION} REQUIRED)
find_package(Intltool REQUIRED)

kaccounts_add_service(${CMAKE_CURRENT_SOURCE_DIR}/microsoft-onedrive.service.in)

kcoreaddons_add_plugin(kaccounts_onedrive
    SOURCES kaccountsplugin.cpp
    INSTALL_NAMESPACE kaccounts/daemonplugins)

set_target_properties(kaccounts_onedrive PROPERTIES OUTPUT_NAME "onedrive")
target_link_libraries(kaccounts_onedrive
    KAccounts
    KF5::KIOWidgets
    KF5::I18n
    KF5::Notifications)

install(FILES onedrive.notifyrc DESTINATION ${KDE_INSTALL_KNOTIFY5RCDIR})
