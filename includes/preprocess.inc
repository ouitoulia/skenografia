<?php

/**
 * @file
 * Hook THEME_preprocess.
 */

use Drupal\node\Entity\Node;

/**
 * Implements hook_preprocess_HOOK() for all templates.
 */
function skenografia_preprocess(&$variables): void {

}

/**
 * Implements hook_preprocess_oembed_lazyload().
 */
function skenografia_preprocess_oembed_lazyload(&$variables): void {
  $variables['privacy_path'] =
    null !== theme_get_setting('privacy_policy') ?
    Drupal::service('path_alias.manager')->getAliasByPath('/node/' . theme_get_setting('privacy_policy')[0]['target_id']) : '#';
}
