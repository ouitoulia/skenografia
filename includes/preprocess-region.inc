<?php

/**
 * @file
 * Preprocess region.
 */

use Drupal\bootstrap_italia\Helper\Helper;
use Drupal\skenografia\Helper\Helper as SHelper;
use Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException;
use Drupal\Component\Plugin\Exception\PluginNotFoundException;

/**
 * Implements hook_preprocess_region().
 */
function skenografia_preprocess_region(array &$variables): void {

  if ($variables['region'] == 'header_nav') {
    // Branding
    $variables['site_logo'] = Drupal::theme()->getActiveTheme()->getLogo();
    $variables['site_name'] = Drupal::config('system.site')->get('name');
    $variables['site_slogan'] = Drupal::config('system.site')->get('slogan');
    try {$variables = array_merge_recursive($variables, SHelper::getLocality());}
    catch (InvalidPluginDefinitionException|PluginNotFoundException $e) {}

    // Social.
    // NB queste due linee potrebbero sembrare duplicate ma non lo sono.
    // Servono per stampare la lista dei social nel menu mobile.
    $variables['social_new_window'] = (bool) theme_get_setting('social_new_window');
    $variables['socials'] = Helper::getActiveSocials();
  }
}
