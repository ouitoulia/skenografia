<?php

/**
 * @file
 * Hook THEME_preprocess_block_*.
 */

use Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException;
use Drupal\Component\Plugin\Exception\PluginNotFoundException;
use Drupal\skenografia\Helper\Helper;

/**
 * Implements hook_preprocess_block() for block templates.
 */
function skenografia_preprocess_block(array &$variables): void {
  // Block 'system_brandig_block'.
  if ($variables['base_plugin_id'] == 'system_branding_block') {
    try {
      $variables = array_merge_recursive($variables, Helper::getLocality());
    }
    catch (InvalidPluginDefinitionException|PluginNotFoundException $e) {
    }
  }
}
