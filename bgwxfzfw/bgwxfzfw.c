#include "bgwxfzfw.h"

// Runtime speaker pin selection - shared across all compilation units
bool bgwx_use_custom_speaker = true; // true = PA6, false = PB8

bool bgwx_get_speaker_mode(void) { return bgwx_use_custom_speaker; }

void bgwx_save_settings(void) {
  BgwxStorageSettings settings = {.magic = BGWX_SETTINGS_MAGIC,
                                  .version = BGWX_SETTINGS_VERSION,
                                  .use_custom_speaker = bgwx_use_custom_speaker,
                                  .reserved = {0}};

  Storage *storage = furi_record_open(RECORD_STORAGE);
  File *file = storage_file_alloc(storage);

  if (storage_file_open(file, BGWX_SETTINGS_PATH, FSAM_WRITE,
                        FSOM_CREATE_ALWAYS)) {
    storage_file_write(file, &settings, sizeof(BgwxStorageSettings));
    storage_file_close(file);
  }

  storage_file_free(file);
  furi_record_close(RECORD_STORAGE);
}

void bgwx_load_settings(void) {
  Storage *storage = furi_record_open(RECORD_STORAGE);
  File *file = storage_file_alloc(storage);

  BgwxStorageSettings settings = {0};
  bool loaded = false;

  if (storage_file_open(file, BGWX_SETTINGS_PATH, FSAM_READ,
                        FSOM_OPEN_EXISTING)) {
    if (storage_file_read(file, &settings, sizeof(BgwxStorageSettings)) ==
        sizeof(BgwxStorageSettings)) {
      if (settings.magic == BGWX_SETTINGS_MAGIC &&
          settings.version == BGWX_SETTINGS_VERSION) {
        bgwx_use_custom_speaker = settings.use_custom_speaker;
        loaded = true;
      }
    }
    storage_file_close(file);
  }

  storage_file_free(file);
  furi_record_close(RECORD_STORAGE);

  // If not loaded, use default and save
  if (!loaded) {
    bgwx_use_custom_speaker = true; // Default to PA6
    bgwx_save_settings();
  }
}

void bgwx_set_speaker_mode(bool use_custom) {
  bgwx_use_custom_speaker = use_custom;
  bgwx_save_settings();
}
