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
 * Implements hook_preprocess_node().
 */
function skenografia_preprocess_node(&$variables, $hook): void {
  // Get node submitter
  $uid = $variables['node']->getOwner()->id();

  // Load submitter account
  $account = \Drupal\user\Entity\User::load($uid);

  if ($account->field_codice_fiscale->getValue()) {
    // get codice fiscale from submitter account
    $cf = $account->field_codice_fiscale->getValue()[0]['value'];

    // load profile (Persona), if exists return id else null
    // https://www.drupal.org/docs/drupal-apis/entity-api/working-with-the-entity-api#s-load-an-entity-from-the-database
    $nids = \Drupal::entityTypeManager()
      ->getStorage('node')
      ->loadByProperties([
        'field_codice_fiscale' => $cf,
      ]);
    // nid or null
    $variables['author_profile_nid'] = array_key_first($nids);
  }
  else {
    $variables['author_profile_nid'] = NULL;
  }
}

/**
 * Implements hook_preprocess_oembed_lazyload().
 */
function skenografia_preprocess_oembed_lazyload(&$variables): void {
  $variables['privacy_path'] =
    null !== theme_get_setting('privacy_policy') ?
    Drupal::service('path_alias.manager')->getAliasByPath('/node/' . theme_get_setting('privacy_policy')[0]['target_id']) : '#';
}
