<?php

/**
 * @file
 * Hook form alter.
 */

use Drupal\Core\Form\FormStateInterface;

/**
 * Implements hook_form_alter()
 */
function skenografia_form_alter(&$form, FormStateInterface &$form_state,$form_id) {
  if (isset($form['#id']) && $form['#id'] == 'views-exposed-form-secondo-livello-servizi-personale-scolastico') {
    $tmp_array = [];
    $tmp_array[1202] = $form['field_tipologia_servizio_target_id']['#options'][1202];
    $tmp_array[1201] = $form['field_tipologia_servizio_target_id']['#options'][1201];
    $form['field_tipologia_servizio_target_id']['#options'] = $tmp_array;
  }
}
