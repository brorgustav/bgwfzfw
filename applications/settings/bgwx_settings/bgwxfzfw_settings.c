#include "bgwxfzfw_settings.h"
#include <bgwxfzfw/bgwxfzfw.h>

const char *const speaker_pin_text[] = {
    "Default (PB8)",
    "Custom (PA6)",
};

// Startup function to initialize BGWX settings
void bgwx_on_system_start(void) { bgwx_load_settings(); }

static void speaker_pin_changed(VariableItem *item) {
  uint8_t index = variable_item_get_current_value_index(item);
  variable_item_set_current_value_text(item, speaker_pin_text[index]);
  bgwx_set_speaker_mode(index == 1);
}

static uint32_t bgwx_settings_exit(void *context) {
  UNUSED(context);
  return VIEW_NONE;
}

BgwxSettings *bgwx_settings_alloc(void) {
  BgwxSettings *app = malloc(sizeof(BgwxSettings));

  app->gui = furi_record_open(RECORD_GUI);
  app->view_dispatcher = view_dispatcher_alloc();
  view_dispatcher_attach_to_gui(app->view_dispatcher, app->gui,
                                ViewDispatcherTypeFullscreen);

  app->var_item_list = variable_item_list_alloc();

  VariableItem *item;
  item = variable_item_list_add(app->var_item_list, "Speaker Pin", 2,
                                speaker_pin_changed, app);

  uint8_t current_mode = bgwx_get_speaker_mode() ? 1 : 0;
  variable_item_set_current_value_index(item, current_mode);
  variable_item_set_current_value_text(item, speaker_pin_text[current_mode]);

  view_set_previous_callback(variable_item_list_get_view(app->var_item_list),
                             bgwx_settings_exit);

  view_dispatcher_add_view(app->view_dispatcher, BgwxSettingsViewVarItemList,
                           variable_item_list_get_view(app->var_item_list));

  view_dispatcher_switch_to_view(app->view_dispatcher,
                                 BgwxSettingsViewVarItemList);

  return app;
}

void bgwx_settings_free(BgwxSettings *app) {
  furi_assert(app);
  view_dispatcher_remove_view(app->view_dispatcher,
                              BgwxSettingsViewVarItemList);
  variable_item_list_free(app->var_item_list);
  view_dispatcher_free(app->view_dispatcher);
  furi_record_close(RECORD_GUI);
  free(app);
}

int32_t bgwx_settings_app(void *p) {
  UNUSED(p);
  BgwxSettings *app = bgwx_settings_alloc();
  view_dispatcher_run(app->view_dispatcher);
  bgwx_settings_free(app);
  return 0;
}
