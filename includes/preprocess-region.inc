<?php

/**
 * @file
 * Preprocess region.
 */

use Drupal\bootstrap_italia\Helper\Helper;

/**
 * Implements hook_preprocess_region().
 */
function skenografia_preprocess_region(array &$variables): void {

  if ($variables['region'] == 'header_nav') {
    // Social.
    $variables['social_new_window'] = (bool) theme_get_setting('social_new_window');
    $variables['socials'] = Helper::getActiveSocials();
  }
}
