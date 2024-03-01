<?php

/**
 * @file
 * Install file for Skenografia sub-theme.
 */

/**
 * @file
 * Post update functions for Skenografia.
 */

/**
 * Dalla 1.7.0 le informazioni rimosse vengono gestite con node.bundle['luogo'].
 * La numerazione a fine nome funzione serve solo se in futuro si aggiungerà
 * un'altra funzione che opera in modo simile e non impazzire a cercare nomi fantasiosi.
 * Non ha la stessa funzionalità dell'hook_update.
 */
function skenografia_post_update_delete_config_8001(&$sandbox = NULL) {
  $config = \Drupal::configFactory()->getEditable('skenografia.settings');
  $config->clear('codice_meccanografico');
  $config->clear('codice_fiscale');
  $config->clear('codice_ipa');
  $config->clear('indirizzo');
  $config->clear('cap');
  $config->clear('comune');
  $config->clear('provincia');
  $config->save();
  return t('Old theme configs deleted');
}
