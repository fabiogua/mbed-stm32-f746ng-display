SET(SOURCES components/ui_comp_homebar.c
    components/ui_comp.c
    screens/ui_screen1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
