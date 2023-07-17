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
    // Branding
    $variables['site_logo'] = Drupal::theme()->getActiveTheme()->getLogo();
    $variables['site_name'] = Drupal::config('system.site')->get('name');
    $variables['site_slogan'] = Drupal::config('system.site')->get('slogan');
    $variables['comune'] = theme_get_setting('comune');
    $variables['provincia'] = theme_get_setting('provincia');
    // Social.
    $variables['social_new_window'] = (bool) theme_get_setting('social_new_window');
    $variables['socials'] = Helper::getActiveSocials();
  }
}
