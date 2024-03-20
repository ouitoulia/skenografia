<?php

/**
 * @file
 * Hook THEME_preprocess.
 */

/**
 * Implements hook_preprocess_HOOK() for all templates.
 */
function skenografia_preprocess(&$variables): void {
  // @todo: Ricordarsi di fare UI per permettere la modifica della variabile
  $variables['skenografia_libraries_path'] = '/libraries/ouitoulia-skenografia';

  // Restituisco l'anno scolastico corrente
  $data_di_cambio_anno_scolastico = ((int) date('n') * 100) + (int) date('j');
  if ($data_di_cambio_anno_scolastico > 831) {
    $variables['anno_scolastico_corrente'] = date('Y') . '/' . (int) date('Y') + 1;
  }
  else {
    $variables['anno_scolastico_corrente'] = (int) date('Y') - 1  . '/' . date('Y');
  }
}

/**
 * Implements hook_preprocess_node().
 */
function skenografia_preprocess_node(&$variables): void {
  if (
    isset($variables['node']) &&
    $variables['node']->hasField('field_persona_responsabile')
  ) {
    /** @var \Drupal\node\Entity\Node $node */
    $node = $variables['node'];

    // Get node submitter
    $uid = $node->getOwner()->id();

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
    } else {
      $variables['author_profile_nid'] = NULL;
    }
  } else {
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

/**
 * Implements hook_preprocess_file_link().
 */
function skenografia_preprocess_file_link(&$variables): void {
  /** @var Drupal\file\Entity\File $file */
  $file = $variables['file'];
  $variables['file_link_changed'] = $file->getChangedTime();
}
