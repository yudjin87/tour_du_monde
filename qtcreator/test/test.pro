include (../carousel.pri)

TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += \
    booting_test \
    componentsystem_test \
    componentsystem_test_libs \
    componentsystemui_test \
    interactivity_test \
    #interactivityUI_test \
    logging_test \
    utils_test
