include(ECMAddTests)

ecm_add_test(
    urltest.cpp ../src/onedriveurl.cpp
    LINK_LIBRARIES Qt5::Test
    TEST_NAME urltest
    NAME_PREFIX kio_onedrive-)

# FIXME: this test is currently broken for Jenkins
#ecm_add_test(
#    listtest.cpp
#    LINK_LIBRARIES Qt5::Test KF5::KIOCore
#    TEST_NAME listtest
#    NAME_PREFIX kio_onedrive-)
