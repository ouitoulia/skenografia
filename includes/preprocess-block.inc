<?php

/**
 * @file
 * Hook THEME_preprocess_block_*.
 */

/**
 * Implements hook_preprocess_block() for block templates.
 */
function skenografia_preprocess_block(array &$variables): void {
  // Block 'system_brandig_block'.
  if ($variables['base_plugin_id'] == 'system_branding_block') {
    $variables['comune'] = theme_get_setting('comune');
    $variables['provincia'] = theme_get_setting('provincia');
  }
}
