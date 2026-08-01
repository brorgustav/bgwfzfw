#pragma once

#include "bgwxfzfw_defines.h"
#include <dialogs/dialogs.h>
#include <gui/modules/empty_screen.h>
#include <furi_hal_info.h>
#include <furi.h>
#include <storage/storage.h>

/**
 * @file bgwx.h
 * @brief BGWX custom UI components and utilities
 */

// Storage path for BGWX settings
#define BGWX_SETTINGS_PATH INT_PATH(".bgwxfzfw.settings")
#define BGWX_SETTINGS_MAGIC 0xBEEF
#define BGWX_SETTINGS_VERSION 1

typedef struct {
    uint16_t magic;
    uint16_t version;
    bool use_custom_speaker; // true = PA6, false = PB8
    uint8_t reserved[3];     // For future use, total 8 bytes
} BgwxStorageSettings;

// Runtime speaker pin selection - extern declaration
extern bool bgwx_use_custom_speaker;

/**
 * @brief Get current speaker pin mode
 * @return true if using custom speaker (PA6), false if using default (PB8)
 */
bool bgwx_get_speaker_mode(void);

/**
 * @brief Save settings to storage
 */
void bgwx_save_settings(void);

/**
 * @brief Load settings from storage
 */
void bgwx_load_settings(void);

/**
 * @brief Set speaker pin mode and save to persistent storage
 * @param use_custom true to use custom speaker (PA6), false for default (PB8)
 */
void bgwx_set_speaker_mode(bool use_custom);

/**
 * @brief Toggle speaker pin mode
 * @return new mode (true = custom, false = default)
 */
static inline bool bgwx_toggle_speaker_mode(void) {
    bgwx_use_custom_speaker = !bgwx_use_custom_speaker;
    return bgwx_use_custom_speaker;
}

/**
 * @brief About screen showing BGWX custom firmware info
 * @param dialogs DialogsApp pointer
 * @param message DialogMessage pointer
 * @return DialogMessageButton
 */
static inline DialogMessageButton bgwx_about_screen_info(DialogsApp* dialogs, DialogMessage* message) {
    DialogMessageButton result;
    FuriString* buffer;
    buffer = furi_string_alloc();

    const char* speaker_pin = bgwx_use_custom_speaker ? "PB3 (GPIO External)" : "PB8 (Internal)";
    
    furi_string_cat_printf(
        buffer,
        "Speaker: %s\nFW Build: %s %s",
        speaker_pin,
        __DATE__,
        __TIME__
    );

    dialog_message_set_header(message, "BGWXFZFW", 0, 0, AlignLeft, AlignTop);
    dialog_message_set_text(message, furi_string_get_cstr(buffer), 0, 13, AlignLeft, AlignTop);
    result = dialog_message_show(dialogs, message);
    furi_string_free(buffer);

    return result;
}
