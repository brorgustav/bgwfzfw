#pragma once

#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/variable_item_list.h>

typedef struct {
    Gui* gui;
    ViewDispatcher* view_dispatcher;
    VariableItemList* var_item_list;
} BgwxSettings;

typedef enum {
    BgwxSettingsViewVarItemList,
} BgwxSettingsView;
